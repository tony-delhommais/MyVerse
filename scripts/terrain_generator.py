import json

x_chunck_coord = 0
y_chunck_coord = 0

chunck_width = 50
chunck_height = 50

x_cell_count = 10
y_cell_count = 10


cell_width = chunck_width / x_cell_count
cell_height = chunck_height / y_cell_count

x_min_chunck_coord = (-1 * chunck_width / 2) + (x_chunck_coord * chunck_width)
y_min_chunck_coord = (-1 * chunck_height / 2) + (y_chunck_coord * chunck_height)

output_file_name = "land_" + str(x_chunck_coord) + "_" + str(y_chunck_coord) + ".terrain"


def generate_rectangular():
    data = {}
    land = []

    for i in range(x_cell_count):
        for y in range(y_cell_count):
            tri_1 = {}
            tri_2 = {}

            a = [x_min_chunck_coord + (i * cell_width), y_min_chunck_coord + (y * cell_height), 0.0]
            b = [a[0], a[1] + cell_height, a[2]]
            c = [a[0] + cell_width, a[1] + cell_height, a[2]]
            d = [a[0] + cell_width, a[1], a[2]]

            tri_1["coord_1"] = a
            tri_1["coord_2"] = b
            tri_1["coord_3"] = c

            tri_2["coord_1"] = a
            tri_2["coord_2"] = c
            tri_2["coord_3"] = d

            land.append(tri_1)
            land.append(tri_2)

    data["Land"] = land

    with open(output_file_name, "w", encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)


def generate_isoceles():
    data = {}
    land = []

    for i in range(x_cell_count):
        for y in range(y_cell_count):
            tri_1 = {}
            tri_2 = {}

            if y % 2 == 0:
                a = [x_min_chunck_coord + (i * cell_width), y_min_chunck_coord + (y * cell_height), 0.0]
                b = [a[0] + (cell_width / 2), a[1] + cell_height, a[2]]
                c = [a[0] + cell_width + (cell_width / 2), a[1] + cell_height, a[2]]
                d = [a[0] + cell_width, a[1], a[2]]

                tri_1["coord_1"] = a
                tri_1["coord_2"] = b
                tri_1["coord_3"] = d

                tri_2["coord_1"] = b
                tri_2["coord_2"] = c
                tri_2["coord_3"] = d
            else:
                a = [x_min_chunck_coord + (i * cell_width) + (cell_width / 2), y_min_chunck_coord + (y * cell_height), 0.0]
                b = [a[0] - (cell_width / 2), a[1] + cell_height, a[2]]
                c = [a[0] + cell_width - (cell_width / 2), a[1] + cell_height, a[2]]
                d = [a[0] + cell_width, a[1], a[2]]

                tri_1["coord_1"] = a
                tri_1["coord_2"] = b
                tri_1["coord_3"] = c

                tri_2["coord_1"] = a
                tri_2["coord_2"] = c
                tri_2["coord_3"] = d

            land.append(tri_1)
            land.append(tri_2)

    data["Land"] = land

    with open(output_file_name, "w", encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)


if __name__ == "__main__":
    generate_isoceles()
