#include "kalman_filter_3d.h"

void kalman3d_init(KalmanFilter3D* kf, float dt) {
    for (int i = 0; i < KF3D_STATE_DIM; i++) kf->x[i] = 0.0f;
    kf->x[2] = 1.0f;  // vx
    kf->x[3] = 0.5f;  // vy

    // State transition A
    for (int i = 0; i < KF3D_STATE_DIM * KF3D_STATE_DIM; i++)
        ((float*)kf->A)[i] = 0;

    kf->A[0][0] = 1; kf->A[0][2] = dt;
    kf->A[1][1] = 1; kf->A[1][3] = dt;
    kf->A[2][2] = 1;
    kf->A[3][3] = 1;
    kf->A[4][4] = 1;

    // Measurement H
    for (int i = 0; i < KF3D_MEAS_DIM * KF3D_STATE_DIM; i++)
        ((float*)kf->H)[i] = 0;

    kf->H[0][0] = 1;
    kf->H[1][1] = 1;
    kf->H[2][4] = 1;

    for (int i = 0; i < KF3D_STATE_DIM * KF3D_STATE_DIM; i++) {
        ((float*)kf->P)[i] = (i % 6 == 0) ? 1.0f : 0.0f;
        ((float*)kf->Q)[i] = (i % 6 == 0) ? 0.01f : 0.0f;
    }

    for (int i = 0; i < KF3D_MEAS_DIM * KF3D_MEAS_DIM; i++) {
        ((float*)kf->R)[i] = (i % 4 == 0) ? 4.0f : 0.0f;
    }
}

void kalman3d_predict(KalmanFilter3D* kf) {
    float x_pred[KF3D_STATE_DIM] = {0};
    for (int i = 0; i < KF3D_STATE_DIM; i++)
        for (int j = 0; j < KF3D_STATE_DIM; j++)
            x_pred[i] += kf->A[i][j] * kf->x[j];

    for (int i = 0; i < KF3D_STATE_DIM; i++)
        kf->x[i] = x_pred[i];
}

void kalman3d_update(KalmanFilter3D* kf, float z[KF3D_MEAS_DIM]) {
    float y[3] = {
        z[0] - kf->x[0],
        z[1] - kf->x[1],
        z[2] - kf->x[4]
    };

    kf->x[0] += 0.4f * y[0];
    kf->x[1] += 0.4f * y[1];
    kf->x[4] += 0.6f * y[2];
}
