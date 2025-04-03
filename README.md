
# 🚗 Vehicle Motion Estimation

A portable C-based Kalman Filter system for estimating 2D and 3D vehicle motion, with support for CAN output, functional safety, embedded simulation, and Python visualization.

---

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-embedded-lightgrey)
![Status](https://img.shields.io/badge/status-active-brightgreen)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/Jafarbnr/vehicle-motion-estimation/blob/main/visualization/kalman_filter_demo.ipynb)




## 🧠 Features

- ✅ 2D Kalman Filter: `[x, y, vx, vy]`
- ✅ 3D Kalman Filter: `[x, y, vx, vy, yaw]`
- ✅ Simulated CAN output (16-byte message)
- ✅ Functional safety fallback (stuck/spiking sensors)
- ✅ Portable embedded version (no dynamic memory)
- ✅ Python plotting scripts
- ✅ Ready for STM32, FreeRTOS, or Raspberry Pi Pico
- ✅ Real-time test simulation and CSV logging

---

## 📂 Project Structure

```
vehicle-motion-estimation/
├── estimator/             # All Kalman C source and header files
│   ├── kalman_filter_2d*.c/h
│   ├── kalman_filter_3d.c/h
│   └── tests/             # Test programs and simulation
├── visualization/         # Python plotting scripts
├── demo/                  # 📸 Screenshots of plots and results
├── output_*.csv           # Simulation output logs
├── README.md
└── LICENSE
```

---

## 📸 Demo

### 3D Kalman Filter: Yaw + Position Estimation

![3D Estimation Plot](demo/kalman_3d_sample.png)

---

## ▶️ How to Run

### 🔧 Build (on PC)

```bash
# 2D
gcc estimator/kalman_filter_2d.c estimator/tests/test_kalman_filter_2d.c -o kalman2d.exe

# 3D
gcc estimator/kalman_filter_3d.c estimator/tests/test_kalman_3d.c -o kalman3d.exe

./kalman3d.exe
```

### 📊 Plot in Python

```bash
cd visualization
python plot_kf_3d.py
```

---

## 🛠️ For Embedded Targets

- Use `kalman_filter_2d_embedded.c/h`
- Integrate with FreeRTOS task or HAL driver
- No malloc, no I/O — suitable for STM32, RP2040, etc.

---

## 📄 License

This project is licensed under the MIT License.  
See [LICENSE](LICENSE) for details.

---

## 🧩 Contributing

Pull requests and forks welcome!  
Feel free to improve performance, add sensor fusion layers, or port to your MCU platform.

