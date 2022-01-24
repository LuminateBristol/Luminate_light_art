# A Pythong file to do some fancy audio processing on the ROL audio
# Jan 2022
# Tutorial info: https://hackernoon.com/audio-handling-basics-how-to-process-audio-files-using-python-cli-jo283u3y

from pydub import AudioSegment
import numpy as np
from scipy.io import wavfile  # WAV pack
from scipy.fftpack import fft # Fourier transform pack
import matplotlib.pyplot as plt

data_final = []
length = 90
bin_len = 0.1

def bin_em(data):
    data_final = []
    div = len(data) / (length / bin_len)
    for i in range(int(length / bin_len)):
        datap = np.mean(data[int(i * div):int(i * div + div)])
        data_final.append(datap)
    return data_final

def cleanup(data):
    data_final = []
    data_norm = data / max(data)
    for i in range(len(data_norm)):
        datap = round(data_norm[i]*255, 0)
        data_final.append(int(datap))
    return data_final

def py2arduinoarray(data):
    print("{", end = "")
    for i in range(len(data)):
        print("{},".format(data[i]), end = " ")
    print("}")
    print(len(data))

def main():

    # Read WAV file using scipy.io.wavfile into two arrays
    # Note that the data_wav file is the amplitude and is split into stereo (two columns)
    # fs_wav is the sample rate
    fs_wav, data_wav = wavfile.read("Ring_v2_lows.wav")

    # Trim down to 90 seconds long (for the instabanger)
    data_wav_crop = data_wav[0 : length * fs_wav]

    # Bin data into larger time bins so there is not too much data to handle in Arduino
    data_binned = bin_em(abs(data_wav_crop[:,0]))
    data_clean = cleanup(data_binned)

    plt.plot(range(len(data_clean)), data_clean)
    plt.show()

    py2arduinoarray(data_clean)
    print(data_clean[60])

if __name__ == '__main__':
    main()