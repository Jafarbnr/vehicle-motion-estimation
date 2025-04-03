import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
df = pd.read_csv("../output_kf_2d.csv")

# Plot positions
plt.figure(figsize=(10, 6))
plt.plot(df["TrueX"], df["TrueY"], label="True Position", linewidth=2)
plt.scatter(df["MeasX"], df["MeasY"], label="Noisy Measurements", alpha=0.5, color='red')
plt.plot(df["EstX"], df["EstY"], label="Kalman Estimate", linestyle='--', linewidth=2)

plt.title("2D Kalman Filter: Position Estimation")
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
