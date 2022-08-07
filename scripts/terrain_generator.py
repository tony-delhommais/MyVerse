import json

x_chunck_coord = 0
y_chunck_coord = 0

chunck_width = 100
chunck_height = 100

x_cell_count = 20
y_cell_count = 20


cell_width = chunck_width / x_cell_count
cell_height = chunck_height / y_cell_count

x_min_chunck_coord = (-1 * chunck_width / 2) + (x_chunck_coord * chunck_width)
y_min_chunck_coord = (-1 * chunck_height / 2) + (y_chunck_coord * chunck_height)

output_file_name = "chunck_" + str(x_chunck_coord) + "_" + str(y_chunck_coord) + ".chunck"


def generate_rectangular():
    data = {}
    land = []

    for i in range(x_cell_count):
        for y in range(y_cell_count):
            a = [x_min_chunck_coord + (i * cell_width), y_min_chunck_coord + (y * cell_height), 0.0]
            b = [a[0], a[1] + cell_height, a[2]]
            c = [a[0] + cell_width, a[1] + cell_height, a[2]]
            d = [a[0] + cell_width, a[1], a[2]]
            
            land.append(a)
            land.append(b)
            land.append(c)
            
            land.append(a)
            land.append(c)
            land.append(d)

    data["Land"] = land

    with open(output_file_name, "w", encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)


def generate_isoceles():
    data = {}
    land = []

    for i in range(x_cell_count):
        for y in range(y_cell_count):
            if y % 2 == 0:
                a = [x_min_chunck_coord + (i * cell_width), y_min_chunck_coord + (y * cell_height), 0.0]
                b = [a[0] + (cell_width / 2), a[1] + cell_height, a[2]]
                c = [a[0] + cell_width + (cell_width / 2), a[1] + cell_height, a[2]]
                d = [a[0] + cell_width, a[1], a[2]]

                land.append(a)
                land.append(b)
                land.append(d)
                
                land.append(b)
                land.append(c)
                land.append(d)
            else:
                a = [x_min_chunck_coord + (i * cell_width) + (cell_width / 2), y_min_chunck_coord + (y * cell_height), 0.0]
                b = [a[0] - (cell_width / 2), a[1] + cell_height, a[2]]
                c = [a[0] + cell_width - (cell_width / 2), a[1] + cell_height, a[2]]
                d = [a[0] + cell_width, a[1], a[2]]

                land.append(a)
                land.append(b)
                land.append(c)
                
                land.append(a)
                land.append(c)
                land.append(d)

    data["Land"] = land

    with open(output_file_name, "w", encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)


if __name__ == "__main__":
    generate_isoceles()
