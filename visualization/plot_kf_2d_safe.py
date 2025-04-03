import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV
df = pd.read_csv("../output_kf_2d_safe.csv")

# Plot paths
plt.figure(figsize=(10, 6))
plt.plot(df["TrueX"], df["TrueY"], label="True Path", linewidth=2)
plt.scatter(df["MeasX"], df["MeasY"], label="Noisy Measurements", color="red", alpha=0.4)
plt.plot(df["EstX"], df["EstY"], label="Kalman Estimate", linestyle="--", linewidth=2)

# Highlight fault detections
faults = df[df["Fault"] == "YES"]
if not faults.empty:
    plt.scatter(faults["EstX"], faults["EstY"], color="black", marker="x", s=80, label="Fault Detected")

plt.title("2D Kalman Filter with Functional Safety Monitoring")
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
