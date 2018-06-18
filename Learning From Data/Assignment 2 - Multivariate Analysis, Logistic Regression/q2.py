#Onat Şahin 150150129 Question 2
import numpy as np
from scipy.misc import logsumexp
import math
import random

def process_data(): #Function to read and process data
    with open('iris.data') as file:
        list = [line.strip('\n') for line in file.readlines()]
    list = [line.split(',') for line in list]
    random.shuffle(list) #Data is processed and shuffled

    features = [] #Empty lists for features and labels
    labels = []

    for data in list: #Adding feature elements in the data to features list
        features.append([float(data[0]), float(data[1]), float(data[2]), float(data[3])])
        newlabel = [0,0,0] #Creating label list. The element "1" determines the label
        if data[4] == 'Iris-setosa':
            newlabel[0] = 1
        elif data[4] == 'Iris-versicolor':
            newlabel[1] = 1
        else:
            newlabel[2] = 1
        labels.append(newlabel)

    return features, labels

features, labels = process_data()
lrate = 0.1 #Learning rate
w = [[random.uniform(-0.01, 0.01) for i in range(4)] for j in range(3)] #Randomly initialize weights
N = len(features) #Number of training data
K = 3   # Number of classes
d = 4   # Input dimensionality
y = [0,0,0]
crossw = [] #List for final weights for each training in cross validation
crossResultsTest = [] #List for the number of correct predictions for each training in cross validation
confusion = [[0]*K for i in range(K)] #Empty confusion matrix
for c in range(10):
    print("Training ", c+1, "...") #This part generally follows the pseudocode given in the question
    w = [[random.uniform(-0.01, 0.01) for i in range(4)] for j in range(3)]
    for a in range(300):
        deltaw = [[0 for i in range(4)] for j in range(3)]
        correctCountTrain = 0

        for t in range(N):
            if t >= c*(N/10) and t < (c+1)*(N/10): #Skips the part which is going to be used for testing
                continue
            o = [0 for i in range(K)]
            for i in range(K):
                for j in range(d):
                    o[i] = o[i] + w[i][j] * features[t][j]

            #y = np.exp(o) / np.sum(np.exp(o), axis=0)
            y = np.exp(o - logsumexp(o)) #I used this version of softmax because the one given in the question causes an overflow

            for i in range(K):
                for j in range(d):
                    deltaw[i][j] = deltaw[i][j] + (labels[t][i] - y[i]) * features[t][j]

            for i in range(K):
                for j in range(d):
                    w[i][j] = w[i][j] + lrate * deltaw[i][j]

    crossw.append(w)
    correctCountTest = 0

    for t in range(int(c*(N/10)),int((c+1)*(N/10))): #Testing on the skipped part
        o = [0 for i in range(K)]
        for i in range(K):
            for j in range(d):
                o[i] = o[i] + w[i][j] * features[t][j]
        #y = np.exp(o) / np.sum(np.exp(o), axis=0)
        y = np.exp(o - logsumexp(o)) #Predicts class

        if np.argmax(y) == np.argmax(labels[t]): #Checks prediction and increments number of correct predictions
            correctCountTest += 1                # if it is correct

        confusion[np.argmax(labels[t])][np.argmax(y)] += 1 #Increments the corresponding element of the confusion matrix

    crossResultsTest.append(correctCountTest)
    print("Training ", c+1, "completed")

print("\nLearning rate: ", lrate)
print("Accuracy: ", sum(crossResultsTest)/N*100,"%") #Prints the results
print("\nConfusion Matrix:")
print(np.matrix(confusion),"\n")
