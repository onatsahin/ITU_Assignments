#Onat Şahin 150150129
from math import sqrt, exp, pi
import numpy as np
import matplotlib.pyplot as plt

def calculate_density(x, mean, varsquare):  #Function to calculate the probability density
     return 1/sqrt(2 * pi * varsquare) * exp( (-1/2) * ((x - mean) ** 2) / varsquare)

with open('data.txt') as file:  #Reading the data from file
    data = [number.strip('\n') for number in file.readlines()]

data = [float(number) for number in data] #Converting the input values to float

mean = sum(data) / len(data)  #calculating the mean

temp = 0
for number in data:           #calculating the square of variance
    temp += (number - mean) ** 2

varsquare = temp / len(data)

densities = []
bins = np.arange(0,18,0.01)    #creating a list that goes from 0 to 18 by steps of 0.01

for i in bins:
    densities.append(calculate_density(i,mean,varsquare))  #calculating probabilty densities for the created list to create
                                                           #the MLE fixed distribution line
                                                           
title = "mu = {}, std = {}".format(mean, sqrt(varsquare))  #Creating the plot
datas = plt.hist(data, normed=True, bins=25, label = 'data')
mle = plt.plot(bins,densities, label = 'MLE fixed distribution')
plt.legend(loc = 'upper right')
plt.title(title)
plt.show()
