import numpy as np

# Define the frequencies of the notes in octave 4
note_frequencies = {
    "C": 261.63,
    "C#": 277.18,
    "D": 293.66,
    "D#": 311.13,
    "E": 329.63,
    "F": 349.23,
    "F#": 369.99,
    "G": 392.00,
    "G#": 415.30,
    "A": 440.00,
    "A#": 466.16,
    "B": 493.88
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

# Print the lists for each note
for note, values in note_lists.items():
    print(f"{note}: {values}")

    