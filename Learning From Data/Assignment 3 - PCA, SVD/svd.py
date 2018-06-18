#Onat Şahin 150150129
import matplotlib.pyplot as plt
from scipy import misc
import numpy as np
from PIL import Image

def readImage(imageName): #Reading the image and seperating the channels
    rgb = misc.imread(imageName)
    redChannel = rgb[:,:,0]
    greenChannel = rgb[:,:,1]
    blueChannel = rgb[:,:,2]
    return redChannel, greenChannel, blueChannel

def SVD(A):
    transposeA = np.transpose(A) #Multiplying A with the transpose of A
    temp = np.dot(transposeA, A)
    eigenvals, eigenvecs = np.linalg.eig(temp) #Finding the eigenvalues and eigenvectors of the found matrix
    eigenvalsAbs = np.absolute(eigenvals) #Taking the absoulte value of eigenvalues
    indexes = eigenvalsAbs.argsort()[::-1]
    eigenvals = eigenvals[indexes] #Sorting the eigenvalues in terms of their absolute value
    eigenvalsAbs = eigenvalsAbs[indexes]
    eigenvecs = eigenvecs[:,indexes] #Sorting the eigenvectors in terms of the absolute value of their eigenvalues
    singularVals = np.sqrt(eigenvalsAbs) #Taking the square root of absolute eigenvalues to find the singular values
    S = np.diag(singularVals) #Creating the singular value matrix by placing singular values to diagonal elements
    Sinv = np.linalg.inv(S) #Finding the inverse of S
    V = eigenvecs #Finding matrices U and V
    transposeV = np.transpose(V)

    tempU = np.dot(A,V)
    U = np.dot(tempU,Sinv)

    return U,S,transposeV

def reduceByRank(S,rank): #I assumed the rank to be the percentage of the singular values used.
    size = S.shape[0]     #This function keeps the given percantage and makes the rest zero.
    singularNum = int(size / 100 * rank)

    for i in range(singularNum, size):
        S[i][i] = 0
    return S

def compress(imageFile, rank):
    red, green, blue = readImage(imageFile) #Read the image and split the channels

    U, S, transposeV = SVD(red) #Apply SVD
    reducedS = reduceByRank(S, rank) #Reduce the S matrix
    reducedRedTemp = np.dot(U,reducedS) #Recreate the channel with the reduced S
    reducedRed = np.dot(reducedRedTemp, transposeV)

    U, S, transposeV = SVD(green)
    reducedS = reduceByRank(S, rank)
    reducedGreenTemp = np.dot(U,reducedS)
    reducedGreen = np.dot(reducedGreenTemp, transposeV)

    U, S, transposeV = SVD(blue)
    reducedS = reduceByRank(S, rank)
    reducedBlueTemp = np.dot(U,reducedS)
    reducedBlue = np.dot(reducedBlueTemp, transposeV)

    compressed = rgbArray = np.zeros(red.shape + (3,), 'uint8') #Construct the compressed image with the channels
    compressed[:,:,0] = reducedRed
    compressed[:,:,1] = reducedGreen
    compressed[:,:,2] = reducedBlue
    compressed = Image.fromarray(compressed)

    return compressed

#The main program
rank = int(input("Enter rank: "))
print("\nCompressing with SVD...\n")
newImage = compress('data.jpg', rank)
newImage.save('compressed.jpg')
print("Compression complete. Compressed file is saved as 'compressed.jpg'\n")
