#Our main code the train and testing the data.
#This code also cleans the test data.

import numpy as np
from feature_operations import *
from sklearn import linear_model, decomposition, datasets
from datetime import date
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn import tree

with open("test.txt") as file:
    data = [line.strip('\n') for line in file.readlines()]

data = [line.split(',') for line in data]

print("Features: ",data[0])

test_data = data[1:]
data = data[1:]

emptyInstancesList = []
mark_count = 0
#Find Instances with ? features
for i in range(0,len(data)):
    for j in range(0,13):
        if data[i][j] == '?' and j == 10:
            emptyInstancesList.append(i)
        elif data[i][2] == '?':
            data[i][2] = makeDeliverAfter1Day(data[i][1])


for i in range(0,len(data)):
    if diff_two_date(data[i][1],data[i][2]) < 0:
        data[i][2] = data[i][1]



#Delete found instances
N = len(data) - len(emptyInstancesList)
print("Deleted Instances with ? marks: ",len(emptyInstancesList))
iteriter =0
for i in emptyInstancesList:
    data.pop(i-iteriter)
    iteriter +=1

print("New size: ",N)
y_test = []
for i in range(N):
    y_test.append(0)
y_test = np.matrix(y_test)
print(y_test.shape)

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


print("Items..")
itemIds = readReturnNum("itemId.txt")
print("Customers..")
customerIds = readReturnNum("customerID.txt")
print("Manifactuters..")
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

today = "2018-05-16"
clean_data = []
#Create clean text file.
for i in range(N):
    row  = []
    row.append(diff_two_date(data[i][1],data[i][2]))#Difference between order and deliver
    if data[i][3] in itemIds.keys():
        row.append( itemIds[data[i][3] ] )#Keep itemID
    else:
        row.append('0.5')
    row.append(sizeID[data[i][4]])
    row.append(colorID[data[i][5]])
    row.append( manifactuterIds[data[i][6]] )
    row.append(data[i][7])#Keep price
    if data[i][8] in customerIds.keys():
        row.append( customerIds[data[i][8]] )#Keep customerID
    else:
        row.append('0.5')
    row.append(salutationID[data[i][9]])
    age = int(diff_two_date(data[i][10],today) / 365)
    row.append(dateOfBirthID[str(map_ages(age))])#Calculate age of person
    row.append(stateID[data[i][11]]) #find_index_of(stateList,data[i][11]))# Map State
    if data[i][12] in creationDateID.keys():
        row.append(creationDateID[data[i][12]] )#Map creationYear
    else:
        row.append('0.5')
    clean_data.append(row)

clean_data = [[ float(y) for y in x ] for x in clean_data]

#clean_data = normalize(clean_data)
clean_data = np.matrix(clean_data)
print(clean_data)
N,featureNum = clean_data.shape
print("Clean Data Shape: ",N,featureNum)
print("Read training set")
with open("cleantrain.txt") as file:
    train_data = [line.strip('\n') for line in file.readlines()]

train_data = [line.split(',') for line in train_data]

train_data = [[ float(y) for y in x ] for x in train_data]


labels = []
for i in range(len(train_data)):
    labels.append(train_data[i][len(train_data[0]) -1]  )
labels = np.array(labels)

#train_data  = normalize(train_data)
train_data = np.matrix(train_data)
N,M = train_data.shape


train_data  = train_data[:,:M-1]
N,M = train_data.shape
print("Train data shape : ",N,M)
print("Traing Logistic Regression")

#logistic = linear_model.LogisticRegression()
#logistic.fit(train_data,labels)
#pred = logistic.predict_proba(clean_data)

#myModel = RandomForestClassifier()
#myModel.fit(train_data,labels)
#pred = myModel.predict_proba(clean_data)


clf = tree.DecisionTreeClassifier()
clf.fit(train_data,labels)
pred = clf.predict_proba(clean_data)

final = []
print(pred)
for empty in emptyInstancesList:
    row  = [test_data[empty][0],0.0]
    final.append(row)
for p in range(len(data)):
    row = [data[p][0] , pred[p][1]]
    #row = [data[p][0] , pred[p]]
    final.append(row)

final = sorted(final,key = lambda x: (int(x[0])) )
print("Creating submission")

submitFile = open("submission_multi_proba.txt","w")
submitFile.write("orderItemID,returnShipment\n")
for i in final:
    rowStr = str(i[0]) + "," +str(i[1]) + str('\n')
    submitFile.write(rowStr)
