#Onat Şahin 150150129 Question 8
import matplotlib.pyplot as plt
import numpy as np

t = np.arange(0,1,0.01)

signal = 2 + (4 * np.cos(500*np.pi*t + (5/4)*np.pi)) - (3 * np.sin(60 * np.pi * t)) + (3 * np.cos(250 * np.pi * t - np.pi/4))
freq = np.arange(0,len(signal)/100,0.01)
fourier = np.fft.fft(signal)

plt.subplot(2,1,1)
plt.plot(freq,np.abs(fourier))
plt.ylabel('magnitude')

plt.subplot(2,1,2)
plt.plot(freq,np.angle(fourier))
plt.xlabel('frequency')
plt.ylabel('phase')
plt.show()
