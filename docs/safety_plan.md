# 🚧 Functional Safety Plan (ISO 26262 Inspired)

## 📌 Project: Vehicle Motion State Estimation (VMSES)

This document outlines a simplified safety strategy for the velocity estimation system, inspired by ISO 26262 standards used in automotive embedded systems.

---

## 1. 🧠 Safety Goals

| ID   | Goal Description                                    | ASIL | Justification                              |
|------|-----------------------------------------------------|------|---------------------------------------------|
| SG01 | Prevent incorrect velocity estimation               | B    | Affects braking, stability, and control     |
| SG02 | Detect and handle sensor signal failure             | A    | Sensor faults can degrade estimation        |
| SG03 | Ensure estimator produces output at expected rate   | A    | Output delay could impact real-time systems |

---

## 2. ⚠️ Hazard Analysis

| Hazard ID | Description                              | Cause                     | Effect                              | Severity |
|-----------|------------------------------------------|---------------------------|--------------------------------------|----------|
| H01       | Estimation drift due to sensor bias      | Gyro/IMU drift            | Gradual loss of accuracy             | Medium   |
| H02       | Sudden spike in velocity                 | Faulty wheel speed sensor | Unsafe control actions (e.g., braking) | High     |
| H03       | Delay in output update                   | CPU overload or freeze    | Missed control loop                  | High     |

---

## 3. 🛡️ Safety Requirements

| ID   | Requirement Description                                  | Linked Goal |
|------|----------------------------------------------------------|-------------|
| SR01 | Filter must validate incoming sensor values              | SG01, SG02  |
| SR02 | If estimation error exceeds threshold, enter safe state  | SG01, SG02  |
| SR03 | Filter must produce output within 100ms (10 Hz)          | SG03        |

---

## 4. 🧪 Safety Mechanisms

- Kalman Filter reduces measurement noise and handles missing data
- Sanity checks on sensor inputs (e.g., velocity must be non-negative)
- Timer to detect if estimator stops updating
- Logging for offline analysis

---

## 5. 📦 Safe State Definition

If the system detects:

- Sudden spikes in input
- Flat-lining velocity (sensor stuck)
- Update loop fails

Then the system will:

- Output last known safe velocity
- Flag error to system monitor
- Optionally request fallback to redundant estimator

---

## 6. ✅ Verification Checklist

| Item                            | Status  |
|---------------------------------|---------|
| Sensor input range checks       | ✔️      |
| Output timing monitored         | ✔️ Simulated 100ms loop |
| Fault injection planned         | ⏳      |
| Logging to file implemented     | ✔️      |
| CAN interface emulated          | ✔️ Python simulation     |

---

## 📚 Notes

This document is a simplified reference and **not a full ISO 26262 safety case**. For production-grade systems, additional hazard classification (HARA), FMEA, and validation plans are needed.
