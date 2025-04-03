#include "kalman_filter_2d_embedded.h"

static void mat_identity(float* A, int n) {
    for (int i = 0; i < n * n; i++) A[i] = 0;
    for (int i = 0; i < n; i++) A[i * n + i] = 1.0f;
}

void kalman2d_embedded_init(KalmanFilter2D_Embedded* kf, float dt) {
    float A[16] = {
        1, 0, dt, 0,
        0, 1, 0, dt,
        0, 0, 1,  0,
        0, 0, 0,  1
    };
    float H[8] = {
        1, 0, 0, 0,
        0, 1, 0, 0
    };

    for (int i = 0; i < 16; i++) kf->A[0][0] = A[i];
    for (int i = 0; i < 8; i++)  kf->H[0][0] = H[i];

    mat_identity(&kf->P[0][0], KF2D_STATE_DIM);
    mat_identity(&kf->Q[0][0], KF2D_STATE_DIM);
    mat_identity(&kf->R[0][0], KF2D_MEAS_DIM);

    for (int i = 0; i < KF2D_STATE_DIM; i++) kf->x[i] = 0.0f;
    kf->x[2] = 1.0f;  // vx
    kf->x[3] = 0.5f;  // vy
}

void kalman2d_embedded_predict(KalmanFilter2D_Embedded* kf) {
    float x_next[4] = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            x_next[i] += kf->A[i][j] * kf->x[j];
    for (int i = 0; i < 4; i++) kf->x[i] = x_next[i];
}

void kalman2d_embedded_update(KalmanFilter2D_Embedded* kf, float z[2]) {
    float y[2] = { z[0] - kf->x[0], z[1] - kf->x[1] };
    kf->x[0] += 0.5f * y[0];  // Simplified fixed gain
    kf->x[1] += 0.5f * y[1];
}
