#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "../kalman_filter_2d.h"

float rand_noise(float std_dev) {
    return ((float)rand() / RAND_MAX) * 2.0f * std_dev - std_dev;
}

int main() {
    KalmanFilter2D kf;
    kalman2d_init(&kf, 1.0f);

    srand((unsigned int)time(NULL));

    FILE* f = fopen("output_kf_2d_safe.csv", "w");
    fprintf(f, "Step,TrueX,TrueY,MeasX,MeasY,EstX,EstY,Fault\n");

    float true_state[4] = {0, 0, 1, 0.5}; // x, y, vx, vy
    float prev_meas[2] = {0};
    const float jump_threshold = 10.0f;
    const float stuck_threshold = 0.01f;
    int fault = 0;

    for (int t = 0; t < 50; ++t) {
        true_state[0] += true_state[2];
        true_state[1] += true_state[3];

        float meas[2] = {
            true_state[0] + rand_noise(2.5f),
            true_state[1] + rand_noise(2.5f)
        };

        // Inject a stuck sensor at step 25
        if (t == 25) {
            meas[0] = prev_meas[0];
            meas[1] = prev_meas[1];
        }

        // Fault detection
        fault = 0;
        if (fabs(meas[0] - prev_meas[0]) < stuck_threshold &&
            fabs(meas[1] - prev_meas[1]) < stuck_threshold) {
            fault = 1;
        }

        if (fabs(meas[0] - prev_meas[0]) > jump_threshold ||
            fabs(meas[1] - prev_meas[1]) > jump_threshold) {
            fault = 1;
        }

        if (fault) {
            printf("[t=%02d] ⚠️ Fault detected! Using last estimate instead.\n", t);
            meas[0] = kf.x[0];
            meas[1] = kf.x[1];
        }

        kalman2d_predict(&kf);
        kalman2d_update(&kf, meas);

        printf("[t=%02d] Est: (%.2f, %.2f)  | Meas: (%.2f, %.2f)  | Fault: %s\n",
               t, kf.x[0], kf.x[1], meas[0], meas[1], fault ? "YES" : "NO");

        fprintf(f, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n",
                t, true_state[0], true_state[1],
                meas[0], meas[1],
                kf.x[0], kf.x[1],
                fault ? "YES" : "NO");

        prev_meas[0] = meas[0];
        prev_meas[1] = meas[1];

        Sleep(100);
    }

    fclose(f);
    printf("✅ Safety-enhanced simulation saved to output_kf_2d_safe.csv\n");
    return 0;
}
