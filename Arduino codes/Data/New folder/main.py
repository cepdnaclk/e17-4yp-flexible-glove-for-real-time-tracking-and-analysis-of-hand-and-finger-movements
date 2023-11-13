# Define the filename for the input cleaned data and the three separate output files
input_file_path = 'out.txt'  # Replace with your actual file path
output_files = ['file1.txt', 'file2.txt', 'file3.txt']

# Read the cleaned data and separate the numbers into columns
with open(input_file_path, 'r') as file:
    lines = file.readlines()

# Assuming each line has three numbers separated by spaces
# Initialize lists to hold the separated numbers
numbers_col1 = []
numbers_col2 = []
numbers_col3 = []

# Process each line and append the numbers to their respective lists
for line in lines:
    numbers = line.strip().split()
    if len(numbers) == 3:  # Making sure there are exactly three numbers in the line
        numbers_col1.append(numbers[0])
        numbers_col2.append(numbers[1])
        numbers_col3.append(numbers[2])

# Write each list of numbers into a separate file
for idx, file_path in enumerate(output_files):
    with open(file_path, 'w') as file:
        if idx == 0:
            file.write("\n".join(numbers_col1))
        elif idx == 1:
            file.write("\n".join(numbers_col2))
        elif idx == 2:
            file.write("\n".join(numbers_col3))

print("The numbers have been written to their respective files.")
