// Kalman Filter implementation in C
#include "kalman_filter.h"

void kalman_init(KalmanFilter1D* kf, float A, float B, float H, float Q, float R) {
    kf->A = A;
    kf->B = B;
    kf->H = H;
    kf->Q = Q;
    kf->R = R;
    kf->P = 1.0f;  // Initial error covariance
    kf->x = 0.0f;  // Initial state
}

void kalman_predict(KalmanFilter1D* kf, float u) {
    kf->x = kf->A * kf->x + kf->B * u;
    kf->P = kf->A * kf->P * kf->A + kf->Q;
}

float kalman_update(KalmanFilter1D* kf, float z) {
    float y = z - kf->H * kf->x;
    float S = kf->H * kf->P * kf->H + kf->R;
    float K = kf->P * kf->H / S;

    kf->x = kf->x + K * y;
    kf->P = (1 - K * kf->H) * kf->P;

    return kf->x;
}
