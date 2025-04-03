import pandas as pd
import matplotlib.pyplot as plt

# Load logged data
df = pd.read_csv("../output_kf_2d_embedded.csv")

# Plot estimated vs true position
plt.figure(figsize=(10, 6))
plt.plot(df["TrueX"], df["TrueY"], label="True Position", linewidth=2)
plt.plot(df["EstX"], df["EstY"], label="Estimated Position", linestyle="--", linewidth=2)
plt.title("2D Embedded Kalman Filter - Position Tracking")
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
