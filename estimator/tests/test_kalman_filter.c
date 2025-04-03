// Unit test for Kalman Filter in C
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "../kalman_filter.h"

// Generate noisy measurement with fault injection at step 10
float generate_measurement(float true_value, float noise_std, int step) {
    // Inject a spike at step 10
    if (step == 10) {
        return true_value + 5.0f; // simulate a large fault
    }
    float noise = ((float)rand() / RAND_MAX) * 2.0f * noise_std - noise_std;
    return true_value + noise;
}

int main() {
    srand((unsigned int)time(NULL));

    KalmanFilter1D kf;
    kalman_init(&kf, 1.0, 0.1, 1.0, 0.01, 0.1); // A, B, H, Q, R

    float control_input = 1.0f;
    float true_velocity = 0.0f;
    float noise_std = 0.05f;
    float max_safe_jump = 1.0f;

    // Open file to log data with fault detection
    FILE *file = fopen("output_with_fault.csv", "w");
    if (file == NULL) {
        printf("❌ Failed to open output_with_fault.csv for writing.\n");
        return 1;
    }

    // Write CSV header
    fprintf(file, "Time(s),True Velocity,Measurement,Estimate,FaultDetected\n");

    // Run simulation loop
    for (int t = 0; t < 20; ++t) {
        true_velocity += control_input * 0.1f;
        float measurement = generate_measurement(true_velocity, noise_std, t);

        // Detect fault (spike)
        int fault_detected = 0;
        if (fabs(measurement - true_velocity) > max_safe_jump) {
            fault_detected = 1;
            measurement = kf.x; // Use previous estimate instead
        }

        // Kalman filter steps
        kalman_predict(&kf, control_input);
        float estimate = kalman_update(&kf, measurement);

        // Console and file output
        printf("%d,%.2f,%.2f,%.2f,%s\n", t, true_velocity, measurement, estimate,
               fault_detected ? "YES" : "NO");
        fprintf(file, "%d,%.2f,%.2f,%.2f,%s\n", t, true_velocity, measurement, estimate,
                fault_detected ? "YES" : "NO");

        Sleep(100); // simulate 100 ms loop
    }

    fclose(file);
    printf("✅ Results saved to output_with_fault.csv\n");

    return 0;
}
