import numpy as np
import matplotlib.pyplot as plt

# Time step
dt = 1.0
steps = 50

# Define matrices
A = np.array([[1, 0, dt, 0],
              [0, 1, 0, dt],
              [0, 0, 1,  0],
              [0, 0, 0,  1]])

H = np.array([[1, 0, 0, 0],
              [0, 1, 0, 0]])

Q = np.eye(4) * 0.01  # Process noise
R = np.eye(2) * 5.0   # Measurement noise
P = np.eye(4) * 1.0   # Initial estimate error

# Initial state
x = np.array([[0], [0], [1], [0.5]])  # Start at origin, moving diagonally
x_true = x.copy()

# Storage
true_states = []
measured_positions = []
estimated_states = []

for _ in range(steps):
    # Simulate true motion
    x_true = A @ x_true
    true_states.append(x_true[:2].flatten())

    # Simulate noisy GPS
    z = H @ x_true + np.random.multivariate_normal([0, 0], R).reshape(2, 1)
    measured_positions.append(z.flatten())

    # Kalman prediction
    x = A @ x
    P = A @ P @ A.T + Q

    # Kalman update
    y = z - H @ x
    S = H @ P @ H.T + R
    K = P @ H.T @ np.linalg.inv(S)
    x = x + K @ y
    P = (np.eye(4) - K @ H) @ P

    estimated_states.append(x[:2].flatten())

# Convert to arrays
true_states = np.array(true_states)
measured_positions = np.array(measured_positions)
estimated_states = np.array(estimated_states)

# Plot
plt.figure(figsize=(10, 6))
plt.plot(true_states[:, 0], true_states[:, 1], label="True Position", linewidth=2)
plt.plot(measured_positions[:, 0], measured_positions[:, 1], 'x', label="Noisy GPS", alpha=0.5)
plt.plot(estimated_states[:, 0], estimated_states[:, 1], label="Kalman Estimate", linestyle="--", linewidth=2)
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.title("2D Position and Velocity Estimation using Kalman Filter")
plt.legend()
plt.grid()
plt.tight_layout()
plt.show()
