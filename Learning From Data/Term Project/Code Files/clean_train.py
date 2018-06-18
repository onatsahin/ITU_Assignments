#This code cleans train data and create new train file.

import pandas as pd
from datetime import date
from feature_operations import *

file = open("train.txt","r")
test = file.read().split('\n')
data = []
iter = 0
for t in test:
    iter +=1
    data.append(t.split(','))
colorDict = {''}
iter -=1
print("Features: ",data[0])
data = data[1:iter-1]
emptyInstancesList = []
iter -= 2
mark_count = 0
print("First Size: ",iter)
N = iter

#Find Instances with ? features
for i in range(0,len(data)):
    for j in range(0,13):
        if data[i][j] == '?' and j == 10:
            emptyInstancesList.append(i)
        elif data[i][2] == '?':
            data[i][2] = makeDeliverAfter1Day(data[i][1])



#Delete found instances
N = iter - len(emptyInstancesList)
print("Deleted Instances with ? marks: ",len(emptyInstancesList))
iteriter =0
for i in emptyInstancesList:
    data.pop(i-iteriter)
    iteriter +=1

print("New size: ",N)

#Find orders which are delivered before ordered.
wrongDateList = []
for i in range(0,N):
    if diff_two_date(data[i][1],data[i][2]) < 0:
        data[i][2] = data[i][1]

#Delete found instances
N -= len(wrongDateList)
print("Deleted Instances with deliverDate - orderDate < 0: ",len(wrongDateList))
iteriter =0
for i in wrongDateList:
    data.pop(i-iteriter)
    iteriter +=1
print("New size: ",N)

colorList = []
manufacturerList = []
salutationList = []
stateList = []

print("Find Lists")
#Find all colors and put them into a list
for i in range(0,N):
    if data[i][5] not in colorList:
        colorList.append(data[i][5])
#Find all manufacturers and put them into a list
for i in range(0,N):
    if data[i][6] not in manufacturerList:
        manufacturerList.append(data[i][6])
#Find all salutations and put them into a list
for i in range(0,N):
    if data[i][9] not in salutationList:
        salutationList.append(data[i][9])
#Find all states and put them into a list
for i in range(0,N):
    if data[i][11] not in stateList:
        stateList.append(data[i][11])

today = "2018-05-16"
clean_data = []

print("Item...")
itemIds = readReturnNum("itemId.txt")
print("Customer...")
customerIds = readReturnNum("customerID.txt")
print("Manufactuer..")
manifactuterIds = readReturnNum("manufacturerID.txt")
print("State..")
stateID = readReturnNum("stateID.txt")
print('Color..')
colorID = readReturnNum("colorID.txt")
print('Size..')
sizeID = readReturnNum("sizeID.txt")
print('salutation')
salutationID = readReturnNum("salutationID.txt")
print('creationDate')
creationDateID = readReturnNum("creationDateID.txt")
print('dateOfBirth')
dateOfBirthID = readReturnNum("dateOfBirthID.txt")
print("Create Clean Train Data")
#Create clean text file.
for i in range(N):
    row  = []
    row.append(diff_two_date(data[i][1],data[i][2]))#Difference between order and deliver
    row.append( itemIds[data[i][3] ] )#Keep itemID
    row.append(sizeID[data[i][4]])
    row.append(colorID[data[i][5]])
    row.append( manifactuterIds[data[i][6]] )
    row.append(data[i][7])#Keep price
    row.append( customerIds[data[i][8]] )#Keep customerID
    row.append(salutationID[data[i][9]])#find_index_of(salutationList,data[i][9]))# Map salutation
    age = int(diff_two_date(data[i][10],today) / 365)
    row.append(dateOfBirthID[str(map_ages(age))])#Calculate age of person
    row.append(stateID[data[i][11]]) #find_index_of(stateList,data[i][11]))# Map State
    row.append(creationDateID[data[i][12]] )#Map creationYear
    row.append(data[i][13])
    clean_data.append(row)
file = open("cleantrain.txt","w")
for i in range(N):
    str_row = ""
    for j in range(0,len(clean_data[0])):
        str_row += str(clean_data[i][j])
        if j != len(clean_data[0]) - 1:
            str_row += ','
    str_row += '\n'
    file.write(str_row)
file.close()
