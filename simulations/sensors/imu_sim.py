
import numpy as np

def simulate_imu(states, accel_noise_std=0.1, gyro_noise_std=0.01):
    """
    Simulates IMU readings (acceleration, gyro) with Gaussian noise.
    """
    N = len(states)
    accel = np.full(N, 1.0) + np.random.normal(0, accel_noise_std, N)
    gyro = np.full(N, 0.01) + np.random.normal(0, gyro_noise_std, N)
    return accel, gyro
