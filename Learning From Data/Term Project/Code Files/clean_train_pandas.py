#This code calculates the probabilty of return of each instances and writes the values to a text file.
import pandas as pd

data = pd.read_csv('cleantrain_labels.txt',sep = ',')
labels = ["orderItemID","orderDate","deliveryDate","itemID","size","color","manufacturerID","price","customerID","salutation","dateOfBirth","state","creationDate","returnShipment"]

a = data.groupby(["customerID","customerID"])["returnShipment"].sum()
ax = data.groupby(["customerID","customerID"])["returnShipment"].count()

x = data.groupby(["dateDifference","dateDifference"])["returnShipment"].sum() /  data.groupby(["dateDifference","dateDifference"])["returnShipment"].count()

file = open("dateDifferenceID.txt","w")
for index,item in x.iteritems():
    strRow = str(index[0]) + "," +str(item) + "\n"
    file.write(strRow)
file.close()
