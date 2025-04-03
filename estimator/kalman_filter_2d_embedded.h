#ifndef KALMAN_FILTER_2D_EMBEDDED_H
#define KALMAN_FILTER_2D_EMBEDDED_H

#define KF2D_STATE_DIM 4
#define KF2D_MEAS_DIM 2

typedef struct {
    float A[KF2D_STATE_DIM][KF2D_STATE_DIM];
    float H[KF2D_MEAS_DIM][KF2D_STATE_DIM];
    float Q[KF2D_STATE_DIM][KF2D_STATE_DIM];
    float R[KF2D_MEAS_DIM][KF2D_MEAS_DIM];
    float P[KF2D_STATE_DIM][KF2D_STATE_DIM];
    float K[KF2D_STATE_DIM][KF2D_MEAS_DIM];
    float x[KF2D_STATE_DIM];
} KalmanFilter2D_Embedded;

void kalman2d_embedded_init(KalmanFilter2D_Embedded* kf, float dt);
void kalman2d_embedded_predict(KalmanFilter2D_Embedded* kf);
void kalman2d_embedded_update(KalmanFilter2D_Embedded* kf, float z[KF2D_MEAS_DIM]);

#endif
