#include <stdio.h>
#include <stdlib.h>
#include "../kalman_filter_2d_embedded.h"

float simulate_noise(float std_dev) {
    return ((float)rand() / RAND_MAX) * 2 * std_dev - std_dev;
}

int main() {
    KalmanFilter2D_Embedded kf;
    kalman2d_embedded_init(&kf, 1.0f);

    float true_x = 0, true_y = 0;
    float vx = 1.0f, vy = 0.5f;

    FILE* log = fopen("output_kf_2d_embedded.csv", "w");
    if (!log) {
        printf("❌ Failed to open CSV log file.\n");
        return 1;
    }

    fprintf(log, "Step,TrueX,TrueY,EstX,EstY\n");
    printf("Time\tTrueX\tTrueY\tEstX\tEstY\n");

    for (int t = 0; t < 30; t++) {
        true_x += vx;
        true_y += vy;

        float z[2] = {
            true_x + simulate_noise(2.0f),
            true_y + simulate_noise(2.0f)
        };

        kalman2d_embedded_predict(&kf);
        kalman2d_embedded_update(&kf, z);

        printf("%2d\t%.2f\t%.2f\t%.2f\t%.2f\n", t, true_x, true_y, kf.x[0], kf.x[1]);
        fprintf(log, "%d,%.2f,%.2f,%.2f,%.2f\n", t, true_x, true_y, kf.x[0], kf.x[1]);
    }

    fclose(log);
    return 0;
}
