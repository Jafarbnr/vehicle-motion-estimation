
import numpy as np

def simulate_wheel_speed(states, noise_std=0.1):
    """
    Simulates wheel speed sensor readings with noise.
    """
    true_speed = states[:, 2]
    noisy_speed = true_speed + np.random.normal(0, noise_std, len(true_speed))
    return noisy_speed
