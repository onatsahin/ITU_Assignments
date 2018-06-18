#
#   Onat Şahin - 150150129
#   Question 4 code
#
import numpy as np
import matplotlib.pyplot as plt

signal = [1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0] #From 0 to 4 in 0.25 steps
output = signal
x_axis = []

for i in range(10): #Convolutions
    output = np.convolve(output, signal)

for i in range(len(output)): #Creating the x-axis
    x_axis.append(i * 0.25)

plt.plot(x_axis, output)
plt.xlabel("t")
plt.ylabel("x(t)")
plt.show()
