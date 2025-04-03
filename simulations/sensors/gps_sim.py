
import numpy as np

def simulate_gps(states, pos_noise_std=0.5):
    """
    Simulates GPS position measurements with Gaussian noise.
    """
    noisy_pos = states[:, :2] + np.random.normal(0, pos_noise_std, states[:, :2].shape)
    return noisy_pos
