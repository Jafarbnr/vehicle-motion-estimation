
import numpy as np

def simulate_vehicle_dynamics(t, dt, a_long=1.0, yaw_rate=0.01):
    """
    Simulates a simple 2D vehicle motion using constant acceleration and yaw rate.
    Returns position, velocity, yaw over time.
    """
    N = int(t / dt)
    x, y, v, yaw = 0, 0, 0, 0
    states = []

    for _ in range(N):
        v += a_long * dt
        yaw += yaw_rate * dt
        x += v * np.cos(yaw) * dt
        y += v * np.sin(yaw) * dt
        states.append([x, y, v, yaw])

    return np.array(states)
