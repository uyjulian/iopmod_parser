
import re
import sys
import json

def main():
	funcinfo_data = {}
	for arg in sys.argv[1:]:
		content = ""
		with open(arg, "r") as f:
			content = f.read()
		for match_obj in re.finditer(r"extern .*?\);", content):
			cur_line = match_obj.group(0)
			srch = re.search(r"[ *\t]([a-zA-Z0-9_]+)\(", cur_line, flags=re.S)
			if srch:
				funcinfo_data[srch.group(1)] = cur_line
	sys.stdout.write(json.dumps(funcinfo_data, sort_keys=True, indent="\t") + "\n")

if __name__ == "__main__":
	main()
