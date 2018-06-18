#We used this code to evaluate a submission and create a better one by converting some probabilty values into anothers. 
import csv

ranges = [0,0,0,0,0,0]
with open("submission_multi_proba.txt") as file:
    data = [line.strip('\n') for line in file.readlines()]

data = [line.split(',') for line in data]
data = data[1:]
N = 0
new_data = []
for i in data:
    row = []
    N += 1
    row.append(i[0])
    if float(i[1]) < 0.0:
        row.append(0.0)
    if float(i[1]) == 0.0:
        ranges[0] += 1
        row.append(i[1])
    elif float(i[1]) < 0.31:
        ranges[1] += 1
        row.append(i[1])
    elif float(i[1]) < 0.41:
        ranges[2] += 1
        row.append('0.25')
    elif float(i[1]) < 0.51:
        row.append('0.0')
    elif float(i[1]) < 0.6:
        row.append('1.0')
    elif float(i[1]) < 0.7:
        row.append('1.0')
    elif float(i[1]) < 0.81:
        ranges[3] += 1
        row.append(i[1])
    elif float(i[1]) < 1.0:
        ranges[4] += 1
        row.append(i[1])
    else:
        ranges[5] += 1
        row.append('1.0')
    new_data.append(row)

file = open("awesome_sub_proba.txt","w")
file.write("orderItemID,returnShipment\n")
for i in new_data:
    str_row = str(i[0]) + ", "+ str(i[1]) + "\n"
    file.write(str_row)
file.close()


print("Total Instances: " ,N)
print(str(ranges[0]) + " instances is equal to 0")
print(str(ranges[1]) + " instances is in the range 0.0 -> 0.3")
print(str(ranges[2]) + " instances is in the range 0.3 -> 0.6")
print(str(ranges[3]) + " instances is in the range 0.6 -> 0.8")
print(str(ranges[4]) + " instances is in the range 0.8 -> 1")
print(str(ranges[5]) + " instances is equal to 1")
