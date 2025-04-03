#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../kalman_filter_3d.h"

float noise(float std) {
    return ((float)rand() / RAND_MAX) * 2 * std - std;
}

int main() {
    KalmanFilter3D kf;
    kalman3d_init(&kf, 1.0f);

    float x = 0, y = 0, vx = 1.0f, vy = 0.5f;
    float yaw = 0.0f, yaw_rate = 0.1f;

    FILE* f = fopen("output_kf_3d.csv", "w");
    fprintf(f, "Step,TrueX,TrueY,Yaw,EstX,EstY,EstYaw\n");

    for (int t = 0; t < 40; t++) {
        x += vx;
        y += vy;
        yaw += yaw_rate;

        float z[3] = {
            x + noise(1.5f),
            y + noise(1.5f),
            yaw + noise(0.05f)
        };

        kalman3d_predict(&kf);
        kalman3d_update(&kf, z);

        printf("[t=%02d] True: (%.2f, %.2f, %.2f) | Est: (%.2f, %.2f, %.2f)\n",
               t, x, y, yaw, kf.x[0], kf.x[1], kf.x[4]);

        fprintf(f, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                t, x, y, yaw, kf.x[0], kf.x[1], kf.x[4]);
    }

    fclose(f);
    printf("✅ 3D Kalman output saved to output_kf_3d.csv\n");
    return 0;
}
