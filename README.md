# ENSC-100W Design Lab Automated-Helly's

SFU ENSC 100W Group project
Code and Circuit Design for Automated Heely’s

For our ENSC 100W Design Lab project, my task was to design and implement the code and circuit for the Automated Heely’s. The electronics system uses an Arduino Nano 33 BLE microcontroller, an Electronic Speed Controller (ESC), and an ESC-compatible battery to control the motor speed and direction.

Key Features of the System:

Wireless Speed Control: The device allows users to control motor speed remotely using Arduino Cloud IoT. A mobile dashboard with a slider adjusts the speed, and an emergency stop button is included for safety.

Smooth Motor Operation: The ESC controls motor speed through PWM signals from the Arduino. To ensure smooth acceleration and deceleration, the motor speed changes gradually using a proportional ramping algorithm.

Emergency Stop Functionality: The motor stops immediately if the BLE connection is lost or the emergency button is pressed. This safety feature ensures the device stops in unexpected situations.

System Workflow:

Setup Phase: During startup, the ESC is set to a minimum throttle value to prevent accidental motor movement. The Arduino connects to the IoT Cloud for remote control functionality.

Operation Phase: The Arduino monitors the BLE connection and motor speed in real time. If the connection is lost, the motor automatically stops. Inputs from the mobile dashboard are used to adjust the motor speed dynamically.

Motor Control Algorithm: The ESC_MOTOR_SPEED function changes motor speed gradually in small steps to ensure smooth operation. If the emergency button is activated, the motor speed is set to zero immediately.

Challenges Addressed:

Smooth Speed Transitions: The ramping algorithm prevents sudden speed changes that could destabilize the user.

Connection Safety: If the BLE connection is lost, the motor stops automatically to prevent accidents.

Compact and Efficient Design: The Arduino Nano 33 BLE enables wireless communication and motor control in a compact and lightweight package, suitable for wearable devices like the Automated Heely’s.

Future Enhancements:

Adding sensors for real-time speed feedback.

Monitoring battery levels to notify the user when charging is needed.

Incorporating an automatic braking mechanism for smoother stops.
