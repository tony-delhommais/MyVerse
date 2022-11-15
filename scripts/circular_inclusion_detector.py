import glob
import re

src_folder = "../src/"

# col 0: file path
# col 1: array of includes
files_detected = []

graph_array = []

loop = []


def file_detection():
	print("Files detection ...")

	file_count = 0
	for filenamehugly in glob.iglob(src_folder + '**/*.h', recursive=True):

		filename = filenamehugly.replace("\\", "/")
		filename = filename.replace(src_folder, "")

		files_detected.append([filename, []])
		file_count += 1
	
	print(str(file_count) + " files detected")


def analyse_includes():
	print("\nAnalyse includes ...")
	wrong_includes_detected = False

	for i in range(len(files_detected)):
		filename = files_detected[i][0]
		if "Client/Utils/" in filename:
			continue
		
		filepath = src_folder + filename

		fileData = open(filepath, "r")

		fileText = fileData.read()

		fileData.close()

		lines = fileText.split("\n")

		includes = []
		for line in lines:
			if "#include" in line:
				
				if "<" in line:
					continue

				if not "Client/" in line:
					wrong_includes_detected = True

					print("Wrong include in file " + filename + ", include "+ line)
				else:
					included_file = line.split("\"")[1]
					files_detected[i][1].append(included_file)

	if not wrong_includes_detected:
		print("No wrong includes")
	else:
		print("Analysing includes done")
	
	return wrong_includes_detected


def get_include_id(include_name):
	for i in range(len(files_detected)):
		if include_name == files_detected[i][0]:
			return i
	
	return -1


def arborescence_creation():
	global graph_array
	print("\nArborescence creation ...")

	nb_file = len(files_detected)

	graph_array = [[0 for j in range(nb_file)] for i in range(nb_file)]
	
	for i in range(nb_file):
		includes = files_detected[i][1]

		for j in range(len(includes)):
			id_include = get_include_id(includes[j])

			if id_include != -1:
				graph_array[i][id_include] = 1

	print("Arborescence created")


def circular_inclusion_detection_recursif(current, target, max_loop):
	global loop
	for j in range(len(graph_array)):
		if graph_array[current][j] == 1:
			if j == target:
				loop.append(j)
				print("loop detected")
				return True
			elif max_loop > 0:
				loop.append(j)
				detected = circular_inclusion_detection_recursif(j, target, max_loop - 1)

				if detected:
					return True
				else:
					loop = loop[:-1]
	
	return False


def circular_inclusion_detection():
	global loop
	print("\nCircular inclusion detection ...")
	circular_inclusion_detected = False
	
	for i in range(len(graph_array)):
		loop = [i]
		circular_inclusion_detected = circular_inclusion_detection_recursif(i, i, 50)
		if circular_inclusion_detected:
			break

	if not circular_inclusion_detected:
		print("No circular inclusion detected")
	else:
		loopTxt = "'" + files_detected[loop[0]][0] + "'"

		for i in range(1, len(loop)):
			loopTxt += " => '" + files_detected[loop[i]][0] + "'"

		print(loopTxt)


def main_loop():
	file_detection()

	if not analyse_includes():
		arborescence_creation()
		
		circular_inclusion_detection()


if __name__ == "__main__":
  	main_loop()
