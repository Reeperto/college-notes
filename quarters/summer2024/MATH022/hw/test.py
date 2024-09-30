from pprint import pprint

def pretty_print_matrix(matrix):
    pprint(matrix, width=len(matrix[0]) * 3 + 2)


bin_matrix = [
    [1, 1, 0, 0], 
    [1, 0, 1, 0], 
    [1, 1, 0, 0], 
    [0, 1, 0, 1]
]

for k, _ in enumerate(bin_matrix):
    pretty_print_matrix(bin_matrix)
    print()
    for i, row in enumerate(bin_matrix):
        for j, value in enumerate(row):
            if not value:
                bin_matrix[i][j] = bin_matrix[i][k] and bin_matrix[k][j]

pretty_print_matrix(bin_matrix)

