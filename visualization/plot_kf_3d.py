import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV output
df = pd.read_csv("../output_kf_3d.csv")

# Plot estimated vs true position
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(df["TrueX"], df["TrueY"], label="True Path", linewidth=2)
plt.plot(df["EstX"], df["EstY"], label="Estimated Path", linestyle='--', linewidth=2)
plt.title("Position: True vs Estimated")
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.grid(True)
plt.legend()

# Plot yaw angle
plt.subplot(1, 2, 2)
plt.plot(df["Yaw"], label="True Yaw", linewidth=2)
plt.plot(df["EstYaw"], label="Estimated Yaw", linestyle='--', linewidth=2)
plt.title("Yaw Angle Over Time")
plt.xlabel("Time Step")
plt.ylabel("Yaw (rad)")
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()
