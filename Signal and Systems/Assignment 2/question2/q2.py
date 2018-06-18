#Onat Şahin 150150129 Question 2
import numpy as np
from scipy.io import wavfile
from sklearn.decomposition import PCA
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline

ones = []
twos = []

for i in range(1,21):  #Reading the .wav files
    rate1, data1 = wavfile.read("one" + str(i) + ".wav")
    rate2, data2 = wavfile.read("two" + str(i) + ".wav")
    ones.append(np.fft.fft(data1.T[0]))
    twos.append(np.fft.fft(data2.T[0]))

trainFeatures = []
labels = []

for i in range(15): #Arranges the data set so that ones and twos are mixed
    trainFeatures.append(ones[i][:10]) #Taking the first ten coefficients for each data in the set
    trainFeatures.append(twos[i][:10])
    labels.append(1) #Creating the labels for the trainSet
    labels.append(2)

labels = np.array(labels)
trainFeatures = np.matrix(trainFeatures)

tests = ones[15:20] + twos[15:20] #Creating the test set and labels
testLabels = [1,1,1,1,1,2,2,2,2,2]

#for i in range(15,20):         #Code to create a mixed test set like the training set. Gives the same result
    #print("ones",ones[i])      #as the set above
    #tests.append(ones[i])
    #print("twos",ones[i])
    #tests.append(twos[i])
    #testLabels.append(1)
    #testLabels.append(2)

for i in range(len(tests)): #Taking the first ten coefficients of the test set
    tests[i] = tests[i][:10]

tests = np.array(tests)

pca = PCA(n_components=1)
logreg = LogisticRegression()
pipeline = Pipeline([('pca', pca), ('logreg', logreg)]) #The pipeline to do the operations
pipeline.fit(trainFeatures, labels) #Training

predictions = []
for test in tests: #Predicting the test set
    predictions.append(pipeline.predict(test))
print("Predictions: ", predictions) #Printing the predictions and true classes
print("True labels: ", testLabels)
correct = 0
for i in range(len(tests)):
    if(predictions[i].item(0) == testLabels[i]):
        correct += 1

print("Accuracy: ", correct/10*100, "%") #Printing the accuracy
