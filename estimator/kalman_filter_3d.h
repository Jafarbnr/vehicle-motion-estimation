#ifndef KALMAN_FILTER_3D_H
#define KALMAN_FILTER_3D_H

#define KF3D_STATE_DIM 5  // [x, y, vx, vy, yaw]
#define KF3D_MEAS_DIM 3   // [x, y, yaw]

typedef struct {
    float A[KF3D_STATE_DIM][KF3D_STATE_DIM];  // State transition
    float H[KF3D_MEAS_DIM][KF3D_STATE_DIM];   // Measurement model
    float Q[KF3D_STATE_DIM][KF3D_STATE_DIM];  // Process noise
    float R[KF3D_MEAS_DIM][KF3D_MEAS_DIM];    // Measurement noise
    float P[KF3D_STATE_DIM][KF3D_STATE_DIM];  // Covariance
    float K[KF3D_STATE_DIM][KF3D_MEAS_DIM];   // Kalman gain (optional)
    float x[KF3D_STATE_DIM];                  // State vector
} KalmanFilter3D;

void kalman3d_init(KalmanFilter3D* kf, float dt);
void kalman3d_predict(KalmanFilter3D* kf);
void kalman3d_update(KalmanFilter3D* kf, float z[KF3D_MEAS_DIM]);

#endif
