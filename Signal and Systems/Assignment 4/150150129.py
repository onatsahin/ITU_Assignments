#
# Onat Sahin
# 150150129
#
import numpy as np
import scipy
import scipy.signal
import scipy.io
import scipy.io.wavfile
import wave
import matplotlib.pyplot as plt


def modulator(inputsignal, sampleRate, fc): #Multiply the signal with generated cosine responses
    duration = np.linspace(0, len(inputsignal)/sampleRate, num=len(inputsignal))
    timeVals = np.arange(0,duration[-1],1.0/sampleRate)
    cosSignal = np.cos(2 * np.pi * fc * timeVals)
    modulated = inputsignal * cosSignal
    return modulated

def demodulator(signal, fc, phase, sampleRate): #Same as the modulator except the phase
    duration = np.linspace(0, len(signal)/sampleRate, num=len(signal))
    timeVals = np.arange(0,duration[-1],1.0/sampleRate)
    cosSignal = np.cos(2 * np.pi * fc * timeVals + phase)
    demodulated = signal * cosSignal
    return demodulated

def convolution(signal, filter): #Convolution
    return scipy.signal.convolve(signal, filter)

signalFile = wave.open('voice.wav') #Read the signal
inputsignal = signalFile.readframes(-1)
inputsignal = np.fromstring(inputsignal, 'Int16')

firFilter = scipy.io.loadmat('firFilter_b_Coeffs.mat') #Read the FIR low pass filter
coeff = firFilter['b']

plt.figure(1)
plt.plot(inputsignal) #Plot the input signal

sampleRate = signalFile.getframerate()

filtered = convolution(inputsignal, coeff[0]) #Filter the input with the low pass filter

plt.figure(2)
Pxx, freqs, bins, im = plt.specgram(filtered, Fs=sampleRate) #Plot the spectogram

fcarrier = 8500#
modulated = modulator(filtered, sampleRate, fcarrier)
demodulated = demodulator(modulated, fcarrier+10, 0, sampleRate)

response_int = [i for i in demodulated]
response_int = np.array(response_int,'Int16') #Reconstruct the signal to write to file
scipy.io.wavfile.write('output.wav',sampleRate,response_int)

plt.show()
