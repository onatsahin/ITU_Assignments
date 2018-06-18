from scipy import signal
from scipy import misc
import numpy as np
from skimage import color
import matplotlib.pyplot as plt

image = misc.imread('noisyCameraman.png')
grayscale = color.rgb2gray(image)
kernel = [[1/9, 1/9, 1/9], [1/9, 1/9, 1/9], [1/9, 1/9, 1/9]]
output = signal.convolve2d(grayscale, kernel, mode = 'same')

plt.subplot(2,1,1)
plt.title('Input image')
plt.imshow(grayscale, cmap = plt.cm.gray)
plt.subplot(2,1,2)
plt.title('Output image')
plt.imshow(output, cmap = plt.cm.gray)
plt.show()
