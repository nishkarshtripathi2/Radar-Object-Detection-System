🎯 Radar Object Detection System (Arduino + Processing)

This project is a mini radar system built using Arduino UNO, an HC-SR04 Ultrasonic sensor, and a servo motor.
A real-time radar-style visualization is displayed using the Processing IDE.

🚀 Features

🔍 Object detection up to 2 meters

🟢🟡🔴 Color-based distance warning system

📡 Radar-style sweeping animation

🧠 Smooth signal filtering (noise reduction)

🕹 Real-time visualization interface

🛠 Hardware Used
Component	Quantity	Purpose
Arduino UNO	1	Microcontroller
HC-SR04 Ultrasonic Sensor	1	Distance measurement
Servo Motor SG90	1	Sweeping motion
Jumpers + USB Cable	-	Connections
🧩 Working Principle

The sensor emits ultrasonic waves and measures echo time. 
	​
The servo rotates from 0° to 180°, collecting distance values, which are plotted on a radar UI in Processing.

💻 Software Requirements

Arduino IDE

Processing IDE

Required Libraries:

Servo.h (Arduino)

processing.serial.* (Processing)

📂 Files Included
File	Description
Radar_Arduino.ino	Arduino scanning & distance measurement
Radar_Processing.pde	Radar GUI visualization
report.pdf (optional)	Full project documentation
Circuit_Diagram.png	Wiring reference
Demo.gif	Project preview
📷 Preview



📌 Future Upgrades

Replace ultrasonic sensor with LiDAR

Add Bluetooth/Wi-Fi logging

Voice or buzzer alert system

👨‍💻 Developed By

Nishkarsh Tripathi
📍 Engineering Student
🔗 LinkedIn: www.linkedin.com/in/nishkarsh-tripathi-5423b12b6
