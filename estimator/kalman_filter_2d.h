#ifndef KALMAN_FILTER_2D_H
#define KALMAN_FILTER_2D_H

#define STATE_DIM 4
#define MEAS_DIM 2

typedef struct {
    float A[STATE_DIM][STATE_DIM];
    float H[MEAS_DIM][STATE_DIM];
    float Q[STATE_DIM][STATE_DIM];
    float R[MEAS_DIM][MEAS_DIM];
    float P[STATE_DIM][STATE_DIM];
    float K[STATE_DIM][MEAS_DIM];
    float x[STATE_DIM]; // state estimate
} KalmanFilter2D;

void kalman2d_init(KalmanFilter2D* kf, float dt);
void kalman2d_predict(KalmanFilter2D* kf);
void kalman2d_update(KalmanFilter2D* kf, float z[MEAS_DIM]);

#endif
