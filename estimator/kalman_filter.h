// Header file for Kalman Filter
#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

typedef struct {
    float A;  // State transition
    float B;  // Control input
    float H;  // Observation model
    float Q;  // Process noise covariance
    float R;  // Measurement noise covariance
    float P;  // Estimate error covariance
    float x;  // State estimate
} KalmanFilter1D;

void kalman_init(KalmanFilter1D* kf, float A, float B, float H, float Q, float R);
void kalman_predict(KalmanFilter1D* kf, float u);
float kalman_update(KalmanFilter1D* kf, float z);

#endif

