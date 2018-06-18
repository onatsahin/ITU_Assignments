#
#   Onat Şahin - 150150129
#   Question 3 code
#   The code is mostly taken from https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/
#   Comments and explanations are written by me
#
import numpy as np

def FFT(x):
    """A recursive implementation of the 1D Cooley-Tukey FFT"""
    x = np.asarray(x, dtype=float)
    N = x.shape[0]

    if N % 2 > 0:
        raise ValueError("size of x must be a power of 2")
    elif N <= 32:           #if size is small enough, do regular DFT calculation. This step takes O(n^2)
        n = np.arange(N)
        k = n.reshape((N, 1))
        M = np.exp(-2j * np.pi * k * n / N) #Discrete fourier transform calculation formula
        return np.dot(M, x)
    else:                   #else, use divide and conquer approach to reduce the number of calculations
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])
        factor = np.exp(-2j * np.pi * np.arange(N) / N) #Form the signal and return
        return np.concatenate([X_even + factor[:N / 2] * X_odd, X_even + factor[N / 2:] * X_odd])
