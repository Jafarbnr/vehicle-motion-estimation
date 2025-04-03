
import numpy as np

class KalmanFilter1D:
    def __init__(self, A, B, H, Q, R, P, x0):
        self.A = A  # State transition
        self.B = B  # Control input
        self.H = H  # Observation
        self.Q = Q  # Process noise
        self.R = R  # Measurement noise
        self.P = P  # Initial estimation error
        self.x = x0  # Initial state

    def predict(self, u):
        self.x = self.A @ self.x + self.B * u
        self.P = self.A @ self.P @ self.A.T + self.Q
        return self.x

    def update(self, z):
        y = z - self.H @ self.x
        S = self.H @ self.P @ self.H.T + self.R
        K = self.P @ self.H.T @ np.linalg.inv(S)
        self.x += K @ y
        self.P = (np.eye(self.P.shape[0]) - K @ self.H) @ self.P
        return self.x
