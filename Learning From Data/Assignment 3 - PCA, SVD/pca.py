#Onat Şahin 150150129
import numpy as np
import matplotlib.pyplot as plt
import random

def readData(dataFile): #Funtion to read the data to a list
    with open(dataFile) as file:
        list = [line.strip('\n') for line in file.readlines()]
    list = [line.split(',') for line in list]
    for instance in list:
        for i in range(len(instance)):
            instance[i] = int(instance[i])

    features = []
    labels = []

    for instance in list: #Remove the labels from features to a seperate list
        features.append(instance[0:len(instance)-1])
        labels.append(instance[-1])

    return features, labels

features, labels = readData('data.txt')
covariance = np.cov(features, rowvar=False) #Finding covariance matrix of features
eigenvals, eigenvecs = np.linalg.eig(covariance) #Finding eigenvalues and eigenvectors of the covariance matrix
index = eigenvals.argsort()[::-1] #Sorting eigenvalues in descending order
eigenvals = eigenvals[index]
eigenvecs = eigenvecs[:,index] #Sorting eigenvectors according to corresponding eigenvalues

reduced = []
for vec in eigenvecs:
    reduced.append(vec[0:2]) #Take the first two eigenvectors to reduce the data to two dimensions.

reduced = np.array(reduced)
reduced = reduced.transpose()
npfeatures = np.array(features)

x = []
y = []

for i in range(len(features)):
    temp = np.dot(reduced, npfeatures[i].transpose()) #creating the new features
    x.append(temp[0])
    y.append(temp[1])

plt.scatter(x,y,s=1)

samples = random.sample(range(0,len(x)), 200)

for i in samples:
    plt.annotate(labels[i], (x[i],y[i]))

plt.show()
