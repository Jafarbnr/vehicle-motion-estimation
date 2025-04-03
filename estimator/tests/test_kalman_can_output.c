#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "../kalman_filter_2d.h"

// Simulated CAN message function (encodes and logs)
void send_can_message(unsigned int can_id, float x, float y, float vx, float vy, FILE* log) {
    unsigned char data[16];
    memcpy(&data[0],  &x,  4);
    memcpy(&data[4],  &y,  4);
    memcpy(&data[8],  &vx, 4);
    memcpy(&data[12], &vy, 4);

    printf("[CAN TX] ID: 0x%03X | Data: ", can_id);
    for (int i = 0; i < 16; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");

    // Log to CSV (decoded values)
    fprintf(log, "%.2f,%.2f,%.2f,%.2f\n", x, y, vx, vy);
}

// Adds noise to the simulated measurement
float rand_noise(float std_dev) {
    return ((float)rand() / RAND_MAX) * 2.0f * std_dev - std_dev;
}

int main() {
    KalmanFilter2D kf;
    kalman2d_init(&kf, 1.0f);  // dt = 1 second

    srand((unsigned int)time(NULL));
    float true_state[4] = {0, 0, 1, 0.5}; // [x, y, vx, vy]

    FILE* log = fopen("output_kf_2d_can.csv", "w");
    if (!log) {
        printf("❌ Failed to open output_kf_2d_can.csv\n");
        return 1;
    }
    fprintf(log, "X,Y,VX,VY\n");

    for (int t = 0; t < 20; ++t) {
        // Simulate motion
        true_state[0] += true_state[2];
        true_state[1] += true_state[3];

        float meas[2] = {
            true_state[0] + rand_noise(2.5f),
            true_state[1] + rand_noise(2.5f)
        };

        kalman2d_predict(&kf);
        kalman2d_update(&kf, meas);

        printf("[t=%02d] Pos: (%.2f, %.2f)  Vel: (%.2f, %.2f)\n",
               t, kf.x[0], kf.x[1], kf.x[2], kf.x[3]);

        send_can_message(0x200, kf.x[0], kf.x[1], kf.x[2], kf.x[3], log);
        Sleep(100);
    }

    fclose(log);
    printf("✅ CAN simulation + log saved to output_kf_2d_can.csv\n");
    return 0;
}
