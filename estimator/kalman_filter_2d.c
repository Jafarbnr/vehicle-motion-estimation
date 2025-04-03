#include "kalman_filter_2d.h"
#include <string.h>

// Matrix utility functions
static void mat_mult(float* C, float* A, float* B, int m, int n, int p) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++) {
            C[i * p + j] = 0;
            for (int k = 0; k < n; k++)
                C[i * p + j] += A[i * n + k] * B[k * p + j];
        }
}

static void mat_transpose(float* B, float* A, int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B[j * m + i] = A[i * n + j];
}

static void mat_add(float* C, float* A, float* B, int m, int n) {
    for (int i = 0; i < m * n; i++)
        C[i] = A[i] + B[i];
}

static void mat_sub(float* C, float* A, float* B, int m, int n) {
    for (int i = 0; i < m * n; i++)
        C[i] = A[i] - B[i];
}

static void mat_copy(float* B, float* A, int m, int n) {
    memcpy(B, A, sizeof(float) * m * n);
}

static void mat_identity(float* A, int n) {
    memset(A, 0, sizeof(float) * n * n);
    for (int i = 0; i < n; i++)
        A[i * n + i] = 1.0f;
}

static void mat_inverse_2x2(float* inv, float* A) {
    float det = A[0] * A[3] - A[1] * A[2];
    inv[0] = A[3] / det;
    inv[1] = -A[1] / det;
    inv[2] = -A[2] / det;
    inv[3] = A[0] / det;
}

// Kalman functions
void kalman2d_init(KalmanFilter2D* kf, float dt) {
    memset(kf, 0, sizeof(KalmanFilter2D));

    float A[STATE_DIM][STATE_DIM] = {
        {1, 0, dt, 0},
        {0, 1, 0, dt},
        {0, 0, 1,  0},
        {0, 0, 0,  1}
    };

    float H[MEAS_DIM][STATE_DIM] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };

    memcpy(kf->A, A, sizeof(A));
    memcpy(kf->H, H, sizeof(H));
    mat_identity(&kf->P[0][0], STATE_DIM);
    mat_identity(&kf->Q[0][0], STATE_DIM);
    mat_identity(&kf->R[0][0], MEAS_DIM);

    for (int i = 0; i < STATE_DIM; i++)
        kf->x[i] = 0.0f;

    kf->x[2] = 1.0f; // vx
    kf->x[3] = 0.5f; // vy
}

void kalman2d_predict(KalmanFilter2D* kf) {
    float Ax[STATE_DIM];
    for (int i = 0; i < STATE_DIM; i++) {
        Ax[i] = 0;
        for (int j = 0; j < STATE_DIM; j++)
            Ax[i] += kf->A[i][j] * kf->x[j];
    }
    memcpy(kf->x, Ax, sizeof(Ax));

    float AT[STATE_DIM][STATE_DIM], AP[STATE_DIM][STATE_DIM], APA_T[STATE_DIM][STATE_DIM];
    mat_transpose(&AT[0][0], &kf->A[0][0], STATE_DIM, STATE_DIM);
    mat_mult(&AP[0][0], &kf->A[0][0], &kf->P[0][0], STATE_DIM, STATE_DIM, STATE_DIM);
    mat_mult(&APA_T[0][0], &AP[0][0], &AT[0][0], STATE_DIM, STATE_DIM, STATE_DIM);
    mat_add(&kf->P[0][0], &APA_T[0][0], &kf->Q[0][0], STATE_DIM, STATE_DIM);
}

void kalman2d_update(KalmanFilter2D* kf, float z[MEAS_DIM]) {
    float Hx[MEAS_DIM], y[MEAS_DIM];
    for (int i = 0; i < MEAS_DIM; i++) {
        Hx[i] = 0;
        for (int j = 0; j < STATE_DIM; j++)
            Hx[i] += kf->H[i][j] * kf->x[j];
        y[i] = z[i] - Hx[i];
    }

    float HT[STATE_DIM][MEAS_DIM];
    mat_transpose(&HT[0][0], &kf->H[0][0], MEAS_DIM, STATE_DIM);

    float HP[MEAS_DIM][STATE_DIM];
    mat_mult(&HP[0][0], &kf->H[0][0], &kf->P[0][0], MEAS_DIM, STATE_DIM, STATE_DIM);

    float HPH_T[MEAS_DIM][MEAS_DIM];
    mat_mult(&HPH_T[0][0], &HP[0][0], &HT[0][0], MEAS_DIM, STATE_DIM, MEAS_DIM);

    float S[MEAS_DIM][MEAS_DIM];
    mat_add(&S[0][0], &HPH_T[0][0], &kf->R[0][0], MEAS_DIM, MEAS_DIM);

    float S_inv[MEAS_DIM][MEAS_DIM];
    mat_inverse_2x2(&S_inv[0][0], &S[0][0]);

    float PH_T[STATE_DIM][MEAS_DIM];
    mat_mult(&PH_T[0][0], &kf->P[0][0], &HT[0][0], STATE_DIM, STATE_DIM, MEAS_DIM);

    mat_mult(&kf->K[0][0], &PH_T[0][0], &S_inv[0][0], STATE_DIM, MEAS_DIM, MEAS_DIM);

    for (int i = 0; i < STATE_DIM; i++)
        for (int j = 0; j < MEAS_DIM; j++)
            kf->x[i] += kf->K[i][j] * y[j];

    float KH[STATE_DIM][STATE_DIM] = {0};
    float temp[STATE_DIM][STATE_DIM];
    mat_mult(&KH[0][0], &kf->K[0][0], &kf->H[0][0], STATE_DIM, MEAS_DIM, STATE_DIM);

    float I_KH[STATE_DIM][STATE_DIM];
    mat_identity(&I_KH[0][0], STATE_DIM);
    mat_sub(&I_KH[0][0], &I_KH[0][0], &KH[0][0], STATE_DIM, STATE_DIM);
    mat_mult(&temp[0][0], &I_KH[0][0], &kf->P[0][0], STATE_DIM, STATE_DIM, STATE_DIM);
    mat_copy(&kf->P[0][0], &temp[0][0], STATE_DIM, STATE_DIM);
}
