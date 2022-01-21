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
bin_len = 0.001

def bin_em(data):
    data_final = []
    div = len(data) / (length / bin_len)
    for i in range(int(length / bin_len)):
        datap = np.mean(data[int(i * div):int(i * div + div)])
        data_final.append(datap)
    return data_final

def cleanup(data):
    data_final = []
    for i in range(len(data)):
        print((data[i]))
        data_final.append(round(data[i],1))

def main():

    # Read WAV file using scipy.io.wavfile into two arrays
    # Note that the data_wav file is the amplitude and is split into stereo (two columns)
    # fs_wav is the sample rate
    fs_wav, data_wav = wavfile.read("Ring_v2_highs.wav")

    # Trim down to 90 seconds long (for the instabanger)
    data_wav_crop = data_wav[0 : length * fs_wav]

    # Use the fast Fourier transform algorithm to get frequency data - NEEDS MORE RESEARCH
    # fft_spectrum = np.fft.rfft(time_wav_crop)
    # freq = np.fft.rfftfreq(data_wav_norm_crop.size, d=1./fs_wav)
    # fft_spectrum_abs = np.abs(fft_spectrum)

    data_binned = bin_em(abs(data_wav_norm_crop))
    #print(int(data_binned[0]))
    #data_clean = cleanup(data_binned)
    #print(data_clean)

    plt.plot(range(int(length/bin_len)), data_binned);
    plt.show()
    print(abs(data_wav_norm_crop))

if __name__ == '__main__':
    main()