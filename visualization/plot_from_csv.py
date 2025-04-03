import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("../output.csv")

# Plot
plt.figure(figsize=(10, 6))
plt.plot(df["Time(s)"], df["True Velocity"], label="True Velocity", linewidth=2)
plt.plot(df["Time(s)"], df["Measurement"], label="Sensor Measurement", linestyle='--', alpha=0.7)
plt.plot(df["Time(s)"], df["Estimate"], label="Kalman Estimate", linestyle='-.', linewidth=2)

plt.title("Kalman Filter Velocity Estimation")
plt.xlabel("Time (s)")
plt.ylabel("Velocity [m/s]")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
