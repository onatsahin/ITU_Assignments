#Onar Şahin 150150129 Question 1
import numpy as np
import matplotlib.pyplot as plt

def readData(dataFile): #Funtion to read the data to a list
    with open(dataFile) as file:
        list = [line.strip('\n') for line in file.readlines()]
    list.pop(0)
    list = [line.split(',') for line in list]
    for data in list:
        data[0] = float(data[0])
        data[1] = float(data[1])
        data[2] = int(data[2])

    return list

def splitData(dataList): #Function to split the training data in terms of their classes
    class0 = []
    class1 = []
    class2 = []

    for data in dataList:
        if data[2] == 0:
            class0.append(data)
        elif data[2] == 1:
            class1.append(data)
        else:
            class2.append(data)

    return class0, class1, class2

def calculateMeanVector(dataList): #Function that calculates the mean vector for features
    sum1 = 0
    sum2 = 0

    for data in dataList:
        sum1 += data[0]
        sum2 += data[1]

    mean1 = sum1 / len(dataList)
    mean2 = sum2 / len(dataList)

    meanVector = np.zeros((2,1))
    meanVector[0][0] = mean1
    meanVector[1][0] = mean2
    return meanVector

def calculateCovarianceMatrix(dataList, meanVector): #Creates the covariance matrix according to the formula
    cov11 = 0
    cov12 = 0
    cov22 = 0

    for data in dataList:
        cov11 += (data[0] - meanVector[0][0])**2
        cov12 += (data[0] - meanVector[0][0]) * (data[1] - meanVector[1][0])
        cov22 += (data[1] - meanVector[1][0])**2

    n = len(dataList)-1
    cov11 /= n
    cov12 /= n
    cov22 /= n

    matrix = np.zeros((2,2))
    #matrix = [[0,0],[0,0]]
    matrix[0][0] = cov11
    matrix[1][1] = cov22
    matrix[0][1] = cov12
    matrix[1][0] = cov12
    return matrix

def calculateP(data0, data1, data2): #Calculates general class probabilities
    pList = [0,0,0]
    totalNum = len(data0) + len(data1) + len(data2)
    pList[0] = len(data0) / totalNum
    pList[1] = len(data1) / totalNum
    pList[2] = len(data2) / totalNum

    return pList

def predictClass(covMatrices,means,classProbs,data):
    results = [0,0,0]
    for i in range(3): #For every class, the operation below computes the discriminant function with given data
        results[i] = (-1/2) * np.dot( np.dot(np.transpose(data - means[i]), np.linalg.inv(covMatrices[i])), (data - means[i]) ) - (1/2) * np.log(np.linalg.det(covMatrices[i])) + np.log(classProbs[i])
    max = -10E9
    for i in range(3): #Finds which class has the max probability and predicts that class
        if results[i].item(0,0) > max:
            max = results[i].item(0,0)
            maxIndex = i
    return maxIndex

def training(dataFile): #Function that calculates means and covariance matrices with the functions above
    data = readData(dataFile)
    class0, class1, class2 = splitData(data)

    means = []
    means.append(calculateMeanVector(class0))
    means.append(calculateMeanVector(class1))
    means.append(calculateMeanVector(class2))

    covMatrices = []
    covMatrices.append(calculateCovarianceMatrix(class0, means[0]))
    covMatrices.append(calculateCovarianceMatrix(class1, means[1]))
    covMatrices.append(calculateCovarianceMatrix(class2, means[2]))

    classProbs = calculateP(class0, class1, class2)

    return means, covMatrices, classProbs, data

def test(testData, means, covMatrices, classProbs): #Compares predictions with true labels and calculates accuracy
    dataList = readData(testData)
    correctPrediction = 0
    results = [0,0,0]

    for data in dataList:
        realData = np.matrix([[data[0]],[data[1]]])
        prediction = predictClass(covMatrices,means,classProbs,realData)
        if prediction == data[2]:
            correctPrediction += 1

    accuracy = correctPrediction / len(dataList) * 100
    return accuracy

def plotBoundaries(dataList,covMatrices,means,classProbs): #Plots the boundaries
    x1max = -10E9
    x1min = 10E9
    x2max = -10E9
    x2min = 10E9

    for data in dataList:
        if data[0] > x1max:
            x1max = data[0]
        if data[0] < x1min:
            x1min = data[0]
        if data[1] > x2max:
            x2max = data[1]
        if data[1] < x2min:
            x2min = data[1]

    xx, yy = np.meshgrid(np.arange(x1min-0.5, x1max+0.5, 0.1), np.arange(x2min-0.5, x2max+0.5, 0.02))
    Z = []

    for i in range(0,len(xx.ravel())):
        realData = np.matrix([[xx.ravel()[i]],[yy.ravel()[i]]])
        Z.append(predictClass(covMatrices,means,classProbs,realData))
    Z = np.array(Z)

    plt.figure()
    Z = Z.reshape(yy.shape)
    plt.pcolormesh(xx,yy,Z,cmap=plt.cm.Paired)
    plt.show()

means, covMatrices, classProbs, trainingData = training('datatrain.csv')
accuracy = test('datatest.csv', means, covMatrices, classProbs)
print("Accuracy: {}%".format(accuracy))
plotBoundaries(trainingData,covMatrices,means,classProbs)
