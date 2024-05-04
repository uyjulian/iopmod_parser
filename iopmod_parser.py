
import sys
import os
import io

file_containing_dir = os.path.dirname(os.path.realpath(__file__)) + "/"

elf_ehdr_items = [
	["e_ident", 16],
	["e_type", 2, 2],
	["e_machine", 2, 2],
	["e_version", 4, 4],
	["e_entry", 4, 4],
	["e_phoff", 4, 4],
	["e_shoff", 4, 4],
	["e_flags", 4, 4],
	["e_ehsize", 2, 2],
	["e_phentsize", 2, 2],
	["e_phnum", 2, 2],
	["e_shentsize", 2, 2],
	["e_shnum", 2, 2],
	["e_shstrndx", 2, 2],
]

elf_phdr_items = [
	["p_type", 4, 4],
	["p_offset", 4, 4],
	["p_vaddr", 4, 4],
	["p_paddr", 4, 4],
	["p_filesz", 4, 4],
	["p_memsz", 4, 4],
	["p_flags", 4, 4],
	["p_align", 4, 4],
]

elf_iopmod_items = [
	["moduleinfo", 4, 4],
	["entry", 4, 4],
	["gp_value", 4, 4],
	["text_size", 4, 4],
	["data_size", 4, 4],
	["bss_size", 4, 4],
]

def read_items(in_bytes=None, in_items=None, in_dic=None):
	total_offset = 0
	for x in in_items:
		item_name = x[0]
		item_size = x[1]
		item_element_size = x[2] if len(x) > 2 else None
		if in_bytes != None:
			item_bytes = in_bytes[total_offset:total_offset + item_size]
			if len(item_bytes) != item_size:
				break
			item_data = item_bytes
			if item_element_size != None:
				item_arr = []
				for i in range(item_size // item_element_size):
					item_arr.append(int.from_bytes(item_bytes[i * item_element_size:(i + 1) * item_element_size], byteorder="little"))
				if len(item_arr) == 1:
					item_data = item_arr[0]
				else:
					item_data = item_arr
			if in_dic != None:
				in_dic[item_name] = item_data
		total_offset += item_size
	return total_offset

IRX_MAGIC_IMPORT = 0x41e00000
IRX_MAGIC_EXPORT = 0x41c00000
IRX_MAGIC_IMPORT_FUNCTION = 0x03E00008

def find_address(phdr_list, addr):
	for phdr in phdr_list:
		if phdr["p_type"] == 1: # PT_LOAD
			if ((addr >= phdr["p_offset"]) or (addr < (phdr.p_offset + phdr["p_filesz"]))):
				return (addr - phdr["p_offset"]) + phdr["p_vaddr"]
	return 0

import json
importdb = []
with open(file_containing_dir + "import.json", "r") as f:
	importdb = json.load(f)
	for x in importdb:
		x[0] = x[0].encode("ASCII")
		x[2] = x[2].encode("ASCII")

funcinfo = {}
with open(file_containing_dir + "funcinfo.json", "r") as f:
	funcinfo = json.load(f)

def find_function(importdb, modulename, nr):
	for x in importdb:
		if (x[0] == modulename or x[0][:-1] == modulename or x[0][1:] == modulename) and x[1] == nr:
			return x[2]
	return b""

in_bytes = b""
with open(sys.argv[1], "rb") as f:
	in_bytes = f.read()
if True:
	ehdr_dic = {}
	ehdr_size = read_items(None, elf_ehdr_items, None)
	read_items(in_bytes[0:ehdr_size], elf_ehdr_items, ehdr_dic)
	if ehdr_dic["e_ident"][:4] != b"\x7FELF":
		raise Exception("Not an ELF file")
	if ehdr_dic["e_machine"] != 8: # EM_MIPS
		raise Exception("Not a MIPS architecture file")
	if ehdr_dic["e_type"] not in [0xFF80, 0xFF81, 2]: # ET_SCE_IOPRELEXEC, ET_SCE_IOPRELEXEC2, ET_EXEC
		raise Exception("Not a valid ELF type")
	phdr_list = []
	for i in range(ehdr_dic["e_phnum"]):
		phdr_dic = {}
		read_items(in_bytes[ehdr_dic["e_phoff"] + (i * ehdr_dic["e_phentsize"]):ehdr_dic["e_phoff"] + ((i + 1) * ehdr_dic["e_phentsize"])], elf_phdr_items, phdr_dic)
		phdr_list.append(phdr_dic)
	iopmod_name = b""
	iopmod_version = [None, None]
	phdr_iopmod = phdr_list[0]
	phdr_main = phdr_list[1]
	if phdr_iopmod["p_type"] != 0x70000080:
		raise Exception("Not detected iopmod section")
	iopmod_dic = {}
	iopmod_size = read_items(None, elf_iopmod_items, None)
	main_data_offset = phdr_main["p_offset"]
	main_data = in_bytes[main_data_offset:main_data_offset + phdr_main["p_filesz"]]
	main_data_addroffset = phdr_main["p_vaddr"]
	read_items(in_bytes[phdr_iopmod["p_offset"]:phdr_iopmod["p_offset"] + iopmod_size], elf_iopmod_items, iopmod_dic)
	if iopmod_dic["moduleinfo"] != 0xFFFFFFFF:
		moduleinfo_offset = iopmod_dic["moduleinfo"] - main_data_addroffset
		modulename_offset = int.from_bytes(main_data[moduleinfo_offset:moduleinfo_offset + 4], byteorder="little") - main_data_addroffset
		modulename_offset_end = main_data.find(b"\x00", modulename_offset, modulename_offset + 64)
		if modulename_offset_end != -1:
			iopmod_name = bytes(main_data[modulename_offset:modulename_offset_end])
		iopmod_version[0] = int.from_bytes(main_data[moduleinfo_offset + 5:moduleinfo_offset + 6], byteorder="little")
		iopmod_version[1] = int.from_bytes(main_data[moduleinfo_offset + 4:moduleinfo_offset + 5], byteorder="little")
	imports = []
	exports = []
	bf = io.BytesIO(main_data)
	while True:
		magic = bf.read(4)
		if len(magic) < 4:
			break
		magic = int.from_bytes(magic, byteorder="little")
		if magic == IRX_MAGIC_IMPORT:
			bf.seek(4, 1) # unused
			version = bf.read(4)
			if len(version) < 4:
				break
			version = int.from_bytes(version, byteorder="little")
			modulename = bf.read(8)
			if len(modulename) < 8:
				break
			modulename = modulename.rstrip(b"\x00")
			import_info = [version, modulename]
			import_iopmod = []
			while True:
				addr = bf.tell() + main_data_offset
				magic = bf.read(4)
				if len(magic) < 4:
					break
				magic = int.from_bytes(magic, byteorder="little")
				if magic != IRX_MAGIC_IMPORT_FUNCTION:
					break
				number = bf.read(4)
				if len(number) < 4:
					break
				number = int.from_bytes(number, byteorder="little")
				number = number & 0x00FFFFFF
				import_iopmod.append([modulename, number, find_address(phdr_list, addr), find_function(importdb, modulename, number)])
			import_info.append(import_iopmod)
			imports.append(import_info)
		if magic == IRX_MAGIC_EXPORT:
			bf.read(4) # unused
			version = bf.read(4)
			if len(version) < 4:
				break
			version = int.from_bytes(version, byteorder="little")
			modulename = bf.read(8)
			if len(modulename) < 8:
				break
			modulename = modulename.rstrip(b"\x00")
			export_info = [version, modulename]
			export_iopmod = []
			last_was_zero = False
			number = 0
			while True:
				offset = bf.tell() + main_data_offset
				addr = bf.read(4)
				if len(addr) < 4:
					break
				addr = int.from_bytes(addr, byteorder="little")
				if last_was_zero:
					if addr == IRX_MAGIC_IMPORT_FUNCTION or addr == IRX_MAGIC_IMPORT or addr == IRX_MAGIC_EXPORT:
						export_iopmod.pop()
						bf.seek(-4, 1)
						break
					last_was_zero = False
				if addr == 0:
					last_was_zero = True
				export_iopmod.append([modulename, number, find_address(phdr_list, offset), find_function(importdb, modulename, number), addr])
				number += 1
			export_info.append(export_iopmod)
			exports.append(export_info)
	outfile = sys.stdout
	mapformat = 0
	if len(sys.argv) > 2:
		mapformat = int(sys.argv[2])
	if mapformat == 0:
		if iopmod_version[0] != None:
			outfile.write("\nIdentification: \"%s\", %d, %d\n" % (iopmod_name.decode("ASCII"), iopmod_version[0], iopmod_version[1]))
		outfile.write("\nGP value: 0x%x\n" % (iopmod_dic["gp_value"]))
		for x in exports:
			outfile.write("\nmodule %s %d.%d exported functions:\n" % (x[1].decode("ASCII"), (x[0] >> 8) & 0xff, x[0] & 0xff))
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					outfile.write("0x%08x %d at 0x%08x\n" % (xx[2], xx[1], xx[4]))
				else:
					outfile.write("0x%08x %d %s() at 0x%08x\n" % (xx[2], xx[1], funcname, xx[4]))
		for x in imports:
			outfile.write("\n%s %d.%d\n" % (x[1].decode("ASCII"), (x[0] >> 8) & 0xff, x[0] & 0xff))
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					outfile.write("0x%08x %d\n" % (xx[2], xx[1]))
				else:
					outfile.write("0x%08x %d %s()\n" % (xx[2], xx[1], funcname))
	if mapformat == 1:
		for x in exports:
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					funcname = "%s_%d" % (xx[0].decode("ASCII"), xx[1])
				outfile.write("0x%08x %s\n" % (xx[4], funcname))
		for x in imports:
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					funcname = "%s_%d" % (xx[0].decode("ASCII"), xx[1])
				outfile.write("0x%08x %s\n" % (xx[2], funcname))
	if mapformat == 2:
		used_addresses = []
		outfile.write("#include <idc.idc>\nstatic main(void) {\n")
		outfile.write("split_sreg_range(0X%X,\"gp\",0X%X,2);\n" % (main_data_addroffset, iopmod_dic["gp_value"]))
		for x in exports:
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					funcname = "%s_%d" % (xx[0].decode("ASCII"), xx[1])
				funcaddr = xx[4]
				if funcaddr not in used_addresses:
					used_addresses.append(funcaddr)
					outfile.write("create_insn(0x%08x);\n" % (funcaddr))
					outfile.write("add_func(0x%08x);\n" % (funcaddr))
					if funcname != "":
						outfile.write("set_name(0x%08x,\"%s\");\n" % (funcaddr, funcname))
						if funcname in funcinfo:
							outfile.write("SetType(0x%08x,\"%s\");\n" % (funcaddr, funcinfo[funcname]))
		for x in imports:
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					funcname = "%s_%d" % (xx[0].decode("ASCII"), xx[1])
				funcaddr = xx[2]
				if funcaddr not in used_addresses:
					used_addresses.append(funcaddr)
					outfile.write("create_insn(0x%08x);\n" % (funcaddr))
					outfile.write("add_func(0x%08x);\n" % (funcaddr))
					if funcname != "":
						outfile.write("set_name(0x%08x,\"%s\");\n" % (funcaddr, funcname))
						if funcname in funcinfo:
							outfile.write("SetType(0x%08x,\"%s\");\n" % (funcaddr, funcinfo[funcname]))
		outfile.write("qexit(0);\n")
		outfile.write("}\n")
	if mapformat == 3:
		if iopmod_version[0] != None:
			outfile.write("\nIRX_ID(\"%s\", %d, %d);\n" % (iopmod_name.decode("ASCII"), iopmod_version[0], iopmod_version[1]))
		for x in exports:
			outfile.write("\nDECLARE_EXPORT_TABLE(%s, %d, %d)\n" % (x[1].decode("ASCII"), (x[0] >> 8) & 0xff, x[0] & 0xff))
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					outfile.write("/* 0x%08x %d at 0x%08x */\n" % (xx[2], xx[1], xx[4]))
				else:
					outfile.write("DECLARE_EXPORT(%s) /* 0x%08x %d at 0x%08x */\n" % (funcname, xx[2], xx[1], xx[4]))
			outfile.write("END_EXPORT_TABLE\n")
		for x in imports:
			outfile.write("\n%s_IMPORTS_start\n" % (x[1].decode("ASCII")))
			for xx in x[2]:
				funcname = xx[3].decode("ASCII")
				if len(funcname) == 0:
					outfile.write("/* 0x%08x %d */\n" % (xx[2], xx[1]))
				else:
					outfile.write("I_%s\n" % (funcname))
			outfile.write("%s_IMPORTS_end\n" % (x[1].decode("ASCII")))
		for x in imports:
			outfile.write("#include <%s.h>\n" % (x[1].decode("ASCII")))
