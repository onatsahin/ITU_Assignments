#Onat Şahin 150150129 Question 7,C

import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0,2.20,0.01)
f = 1
y = 4.179 * np.cos(2 * np.pi * f * (x) + (3 * np.pi / 10))
plt.plot(x, y)
plt.xlabel('t')
plt.ylabel('x(t)')
plt.show()
