#Question 6 Onat Şahin 150150129
def myConv(x,h):
    toSum = []
    requiredSize = len(x) + len(h) - 1
    for i in range(len(h)): #multiplies every element of h with every element of x. Adds 0's to fill the
        toSum.append([])    #required size and stores them in toSum
        for j in range(i):
            toSum[i].append(0)
        for j in range(len(x)):
            toSum[i].append(h[i] * x[j])
        while len(toSum[i]) != requiredSize:
            toSum[i].append(0)

    convolution = []
    for i in range(requiredSize): #finds column based sum of toSum to find the convolution
        tempSum = 0
        for j in range(len(h)):
            tempSum += toSum[j][i]
        convolution.append(tempSum)

    return convolution

x = [2,4,6,4,2]
h = [3,-1,2,1]

result = myConv(x,h)
print(result)
