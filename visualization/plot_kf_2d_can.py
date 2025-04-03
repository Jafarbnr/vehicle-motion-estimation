import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV
df = pd.read_csv("../output_kf_2d_can.csv")

# Plot position
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.plot(df["X"], df["Y"], label="Estimated Path", linewidth=2)
plt.title("Position from CAN")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.legend()

# Plot velocity
plt.subplot(1, 2, 2)
plt.plot(df["VX"], label="VX", linewidth=2)
plt.plot(df["VY"], label="VY", linewidth=2)
plt.title("Velocity from CAN")
plt.xlabel("Time Step")
plt.ylabel("Velocity")
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()
