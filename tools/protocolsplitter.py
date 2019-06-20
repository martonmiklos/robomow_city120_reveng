import csv

with open('../backward.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    block_counter = 0
    data_buffer = []
    for row in csv_reader:
        if line_count == 0:
            line_count += 1
        else:
            line_count += 1
            data_buffer.append(row[2])
            if (block_counter == 0 and row[2] != "0x23") :
                continue
            block_counter += 1
            if (block_counter == 4) :
                print(data_buffer[0] , data_buffer[1] , data_buffer[2] , data_buffer[3])
                block_counter = 0
                data_buffer = []