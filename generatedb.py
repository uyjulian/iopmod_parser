
import re
import sys

def main():
	for arg in sys.argv[1:]:
		content = ""
		with open(arg, "r") as f:
			content = f.read()
		module_pos = []
		for match_obj in re.finditer(r" ([^ ]*)_IMPORTS_start", content, flags=re.S):
			if module_pos:
				module_pos[len(module_pos) - 1][1] = match_obj.start(0)
			module_pos.append([match_obj.end(0), None, match_obj.group(1)])
		if module_pos:
			module_pos[len(module_pos) - 1][1] = len(content)
		import_pos = []
		for match_obj in re.finditer(r"DECLARE_IMPORT\(([0-9]*) *, *([^\)]*)", content, flags=re.S):
			import_pos.append([match_obj.end(0), match_obj.group(1), match_obj.group(2)])
		import_data = []
		for ix in import_pos:
			for mx in module_pos:
				if ix[0] > mx[0] and ix[0] < mx[1]:
					import_data.append([mx[2], ix[1], ix[2]])
		for ix in import_data:
			sys.stdout.write(" [\"" + ix[0] + "\", " + ix[1] + ", \"" + ix[2] + "\"],\n")


if __name__ == "__main__":
	main()
