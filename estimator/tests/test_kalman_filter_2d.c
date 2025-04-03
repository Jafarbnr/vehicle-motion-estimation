#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "../kalman_filter_2d.h"

// Generate random Gaussian-like noise within ±std_dev
float rand_noise(float std_dev) {
    return ((float)rand() / RAND_MAX) * 2.0f * std_dev - std_dev;
}

int main() {
    KalmanFilter2D kf;
    kalman2d_init(&kf, 1.0f);  // dt = 1.0 seconds

    srand((unsigned int)time(NULL));  // seed randomness

    // CSV output
    FILE* f = fopen("output_kf_2d_realtime.csv", "w");
    if (!f) {
        printf("❌ Failed to open CSV file.\n");
        return 1;
    }
    fprintf(f, "Step,TrueX,TrueY,MeasX,MeasY,EstX,EstY\n");

    float true_state[4] = {0, 0, 1, 0.5}; // [x, y, vx, vy]

    for (int t = 0; t < 50; ++t) {
        // Simulate true 2D motion
        true_state[0] += true_state[2];  // x += vx
        true_state[1] += true_state[3];  // y += vy

        // Add noise to GPS-like position measurement
        float meas[2] = {
            true_state[0] + rand_noise(2.5f),
            true_state[1] + rand_noise(2.5f)
        };

        // Kalman filter
        kalman2d_predict(&kf);
        kalman2d_update(&kf, meas);

        // Print real-time output
        printf("[t=%02d] True: (%.2f, %.2f)  | Meas: (%.2f, %.2f)  | Est: (%.2f, %.2f)\n",
               t, true_state[0], true_state[1], meas[0], meas[1], kf.x[0], kf.x[1]);

        // Save to CSV
        fprintf(f, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                t, true_state[0], true_state[1],
                meas[0], meas[1],
                kf.x[0], kf.x[1]);

        Sleep(100); // simulate 100 ms control loop (10 Hz)
    }

    fclose(f);
    printf("✅ Real-time 2D Kalman simulation logged to output_kf_2d_realtime.csv\n");

    return 0;
}
