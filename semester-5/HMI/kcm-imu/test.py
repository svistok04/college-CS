import pandas as pd
import matplotlib.pyplot as plt

# Load the data
file_name = "Scenariusz_2_Obracanie_telefonu.csv"  # Replace with your actual file name
data = pd.read_csv(file_name)

# Convert timestamps to seconds
data['time_s'] = (data['timestamp_ms'] - data['timestamp_ms'][0]) / 1000.0

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(data['time_s'], data['magX'], color="green", label="magX (µT)")
plt.title("Magnetometer Data - magX")
plt.xlabel("Time [s]")
plt.ylabel("Magnetic Field [µT]")
plt.grid()

# Save the plot as an image
plt.tight_layout()
plt.savefig("Scenariusz_2_magX.png", bbox_inches="tight")

# Show the plot
plt.show()
