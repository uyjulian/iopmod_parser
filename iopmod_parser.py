
import sys
import os

file_containing_dir = os.path.dirname(os.path.realpath(__file__)) + "/"

class Elf32_Ehdr:
	def __init__(self, g):
		self.e_ident = g.read(16)
		self.e_type = int.from_bytes(g.read(2), byteorder="little")
		self.e_machine = int.from_bytes(g.read(2), byteorder="little")
		self.e_version = int.from_bytes(g.read(4), byteorder="little")
		self.e_entry = int.from_bytes(g.read(4), byteorder="little")
		self.e_phoff = int.from_bytes(g.read(4), byteorder="little")
		self.e_shoff = int.from_bytes(g.read(4), byteorder="little")
		self.e_flags = int.from_bytes(g.read(4), byteorder="little")
		self.e_ehsize = int.from_bytes(g.read(2), byteorder="little")
		self.e_phentsize = int.from_bytes(g.read(2), byteorder="little")
		self.e_phnum = int.from_bytes(g.read(2), byteorder="little")
		self.e_shentsize = int.from_bytes(g.read(2), byteorder="little")
		self.e_shnum = int.from_bytes(g.read(2), byteorder="little")
		self.e_shstrndx = int.from_bytes(g.read(2), byteorder="little")

class Elf32_Phdr:
	def __init__(self, g):
		self.p_type = int.from_bytes(g.read(4), byteorder="little")
		self.p_offset = int.from_bytes(g.read(4), byteorder="little")
		self.p_vaddr = int.from_bytes(g.read(4), byteorder="little")
		self.p_paddr = int.from_bytes(g.read(4), byteorder="little")
		self.p_filesz = int.from_bytes(g.read(4), byteorder="little")
		self.p_memsz = int.from_bytes(g.read(4), byteorder="little")
		self.p_flags = int.from_bytes(g.read(4), byteorder="little")
		self.p_align = int.from_bytes(g.read(4), byteorder="little")

IRX_MAGIC_IMPORT = 0x41e00000
IRX_MAGIC_EXPORT = 0x41c00000
IRX_MAGIC_IMPORT_FUNCTION = 0x03E00008

def find_address(program_headers, addr):
	for program_header in program_headers:
		if program_header.p_type == 1: # PT_LOAD
			if ((addr >= program_header.p_offset) or (addr < (program_header.p_offset + program_header.p_filesz))):
				return (addr - program_header.p_offset) + program_header.p_vaddr
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

with open(sys.argv[1], "rb") as f:
	file_header = Elf32_Ehdr(f)
	if file_header.e_ident[:4] != b"\x7fELF":
		raise Exception("Not an ELF file")
	if file_header.e_machine != 8: # EM_MIPS
		raise Exception("Not a MIPS architecture file")
	program_headers = []
	for i in range(file_header.e_phnum):
		program_headers.append(Elf32_Phdr(f))
	imports = []
	exports = []
	while True:
		magic = f.read(4)
		if len(magic) < 4:
			break
		magic = int.from_bytes(magic, byteorder="little")
		if magic == IRX_MAGIC_IMPORT:
			f.seek(4, 1) # unused
			version = f.read(4)
			if len(version) < 4:
				break
			version = int.from_bytes(version, byteorder="little")
			modulename = f.read(8)
			if len(modulename) < 8:
				break
			modulename = modulename.rstrip(b"\x00")
			import_info = [version, modulename]
			import_iopmod = []
			while True:
				addr = f.tell()
				magic = f.read(4)
				if len(magic) < 4:
					break
				magic = int.from_bytes(magic, byteorder="little")
				if magic != IRX_MAGIC_IMPORT_FUNCTION:
					break
				number = f.read(4)
				if len(number) < 4:
					break
				number = int.from_bytes(number, byteorder="little")
				number = number & 0x00FFFFFF
				import_iopmod.append([modulename, number, find_address(program_headers, addr), find_function(importdb, modulename, number)])
			import_info.append(import_iopmod)
			imports.append(import_info)
		if magic == IRX_MAGIC_EXPORT:
			f.read(4) # unused
			version = f.read(4)
			if len(version) < 4:
				break
			version = int.from_bytes(version, byteorder="little")
			modulename = f.read(8)
			if len(modulename) < 8:
				break
			modulename = modulename.rstrip(b"\x00")
			export_info = [version, modulename]
			export_iopmod = []
			last_was_zero = False
			number = 0
			while True:
				offset = f.tell()
				addr = f.read(4)
				if len(addr) < 4:
					break
				addr = int.from_bytes(addr, byteorder="little")
				if last_was_zero:
					if addr == IRX_MAGIC_IMPORT_FUNCTION or addr == IRX_MAGIC_IMPORT or addr == IRX_MAGIC_EXPORT:
						export_iopmod.pop()
						f.seek(-4, 1)
						break
					last_was_zero = False
				if addr == 0:
					last_was_zero = True
				export_iopmod.append([modulename, number, find_address(program_headers, offset), find_function(importdb, modulename, number), addr])
				number += 1
			export_info.append(export_iopmod)
			exports.append(export_info)
	outfile = sys.stdout
	mapformat = 0
	if mapformat == 0:
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
		if 0 not in used_addresses:
			outfile.write("create_insn(0x%08x);\n" % (0))
			outfile.write("add_func(0x%08x);\n" % (0))
			outfile.write("set_name(0x%08x,\"%s\");\n" % (0, "irx_entry_point"))
		outfile.write("qexit(0);\n")
		outfile.write("}\n")
