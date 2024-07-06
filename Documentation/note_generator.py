import numpy as np


front = "{"
back = "}"
# Define the frequencies of the notes in octave 4
note_frequencies = {
    "C_1": 32.70,   "Cs_1": 34.65,   "D_1": 36.71,   "Ds_1": 38.89,   "E_1": 41.20,   "F_1": 43.65,   "Fs_1": 46.25,   "G_1": 49.00,   "Gs_1": 51.91,   "A_1": 55.00,   "As_1": 58.27,   "B_1": 61.74,
    "C_2": 65.41,   "Cs_2": 69.30,   "D_2": 73.42,   "Ds_2": 77.78,   "E_2": 82.41,   "F_2": 87.31,   "Fs_2": 92.50,   "G_2": 98.00,   "Gs_2": 103.83,  "A_2": 110.00,  "As_2": 116.54,  "B_2": 123.47,
    "C_3": 130.81,  "Cs_3": 138.59,  "D_3": 146.83,  "Ds_3": 155.56,  "E_3": 164.81,  "F_3": 174.61,  "Fs_3": 185.00,  "G_3": 196.00,  "Gs_3": 207.65,  "A_3": 220.00,  "As_3": 233.08,  "B_3": 246.94,
    "C_4": 261.63,  "Cs_4": 277.18,  "D_4": 293.66,  "Ds_4": 311.13,  "E_4": 329.63,  "F_4": 349.23,  "Fs_4": 369.99,  "G_4": 392.00,  "Gs_4": 415.30,  "A_4": 440.00,  "As_4": 466.16,  "B_4": 493.88,
    "C_5": 523.25,  "Cs_5": 554.37,  "D_5": 587.33,  "Ds_5": 622.25,  "E_5": 659.25,  "F_5": 698.46,  "Fs_5": 739.99,  "G_5": 783.99,  "Gs_5": 830.61,  "A_5": 880.00,  "As_5": 932.33,  "B_5": 987.77,
    "C_6": 1046.50, "Cs_6": 1108.73, "D_6": 1174.66, "Ds_6": 1244.51, "E_6": 1318.51, "F_6": 1396.91, "Fs_6": 1479.98, "G_6": 1567.98, "Gs_6": 1661.22, "A_6": 1760.00, "As_6": 1864.66, "B_6": 1975.53,
    "C_7": 2093.00, "Cs_7": 2217.46, "D_7": 2349.32, "Ds_7": 2489.02, "E_7": 2637.02, "F_7": 2793.83, "Fs_7": 2959.96, "G_7": 3135.96, "Gs_7": 3322.44, "A_7": 3520.00, "As_7": 3729.31, "B_7": 3951.07
}

# Sampling rate (in Hz)
sampling_rate = 1 / 10e-6

# Initialize the lists for each note
note_lists = {}

# Generate the lists for each note
for note, frequency in note_frequencies.items():
    # Calculate the time values for one period
    t = np.arange(0, 1 / frequency, 1 / sampling_rate)
    
    # Generate the sine wave for the note
    sine_wave = np.sin(2 * np.pi * frequency * t)
    
    # Scale the values to the desired range (0 to 4096/12)
    scaled_values = (sine_wave + 1) * (4096 / 12) / 2
    
    # Round the values to the nearest integer
    rounded_values = np.round(scaled_values).astype(int)
    
    # Add the list to the dictionary
    note_lists[note] = rounded_values.tolist()
#f = open("output1.txt","x")
f = open("output1.txt","w")

# Print the lists for each note
for note, values in note_lists.items():
   #print(f"#define {note}_SAMPLES {len(values)}")
   #print(f"{note}_Table = {front}{values}{back}")
   f.write(f"#define {note}_SAMPLES {len(values)}\n")
   f.write(f"const int {note}_Table = {front}{values}{back};\n")

f.close()


    