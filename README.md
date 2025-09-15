# 🤖 Self-Balancing Robot using PID Controller

A two-wheeled **self-balancing robot** implemented with **Arduino Mega, MPU6050 IMU, L298N motor driver, and PID control**.  
The robot maintains its balance by continuously reading tilt angle data from the MPU6050 and adjusting the motor speeds using a tuned **PID controller**.

---

## ✨ Features
- 🚀 Real-time balancing using **PID control**
- 📡 MPU6050 for accurate tilt measurement
- ⚡ Arduino Mega + L298N motor driver
- 🔋 Battery powered (Li-ion)
- 🖥️ Serial Monitor feedback for debugging
- 📷 Photos of actual build included

---

## 🛠️ Components Used
- Arduino Mega
- MPU6050 (Gyroscope + Accelerometer)
- L298N Motor Driver
- 2 × BO Motors (150 RPM)
- Li-ion Battery Pack
- Chassis, wheels, jumper wires

---

## ⚙️ How It Works
1. MPU6050 measures the **tilt angle** of the robot.  
2. Arduino calculates the **error** between current angle and setpoint.  
3. A **PID controller** adjusts motor speed and direction.  
4. Robot maintains balance dynamically.

---

## 📊 PID Control Equation
\[
Output = Kp \times error + Ki \times \int error \, dt + Kd \times \frac{d(error)}{dt}
\]

---

## 📸 Photos

| Full Robot | Circuit Wiring | Demo |
|------------|----------------|------|
| ![Robot](photos/robot_full.jpg) | ![Wiring](photos/circuit_wiring.jpg) | ![Demo](photos/balancing_demo.gif) |

---

## 🚀 Getting Started
1. Clone the repo:
   ```bash
   git clone https://github.com/samshoni/Self-Balancing-Robot-PID-Controller.git
Open Self-Balancing-Robot-PID-Controller.ino in Arduino IDE.

Install the required library:

MPU6050_tockn

Upload to Arduino Mega.

Power with Li-ion battery pack and test balancing.

📹 Demo Video
(Add YouTube link if you upload a video demo!)

👨‍💻 Author
Sam Shoni Zacharia

GitHub | LinkedIn

yaml
Copy code

---

## 🔄 3. Update Repo with Photos + README
Run these commands after editing README and adding images:

```bash
git add .
git commit -m "Added project photos and updated README with details"
git push