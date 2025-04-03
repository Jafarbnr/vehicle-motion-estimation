import pandas as pd
import matplotlib.pyplot as plt

# Load CSV with fault data
df = pd.read_csv("../output_with_fault.csv")

# Plot data
plt.figure(figsize=(10, 6))
plt.plot(df["Time(s)"], df["True Velocity"], label="True Velocity", linewidth=2)
plt.plot(df["Time(s)"], df["Measurement"], label="Sensor Measurement", linestyle='--', alpha=0.7)
plt.plot(df["Time(s)"], df["Estimate"], label="Kalman Estimate", linestyle='-.', linewidth=2)

# Highlight fault points
faults = df[df["FaultDetected"] == "YES"]
if not faults.empty:
    plt.scatter(faults["Time(s)"], faults["Measurement"], color='red', label="Fault Detected", zorder=5)

plt.title("Kalman Filter with Fault Detection")
plt.xlabel("Time (s)")
plt.ylabel("Velocity [m/s]")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
