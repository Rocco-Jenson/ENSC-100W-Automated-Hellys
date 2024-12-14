/* ENSC 100W Helly's Arduino Nano 33 BLE Sketch */
/* Rocco Jenson 301625699 */

/*
Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float BLE_MOTOR_SPEED_CLOUD;
  bool BLE_EMERGENCY_CLOUD;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

/* Check if correct Arduino is used else do nothing */
#if defined(ARDUINO_ARDUINO_NANO33BLE)

#include "thingProperties.h"
#include <ArduinoBLE.h>
#include <Servo.h>

Servo ESC;

#define THROTTLE_LOW 1000
#define THROTTLE_MAX 1900
#define ESC_PIN 3

static unsigned int BLE_MOTOR_SPEED{0};
static bool BLE_EMERGENCY_BUTTON_PRESSED{false};
static int ESC_CURRENT_SPEED{1000};

void ESC_MOTOR_SPEED(unsigned int motorSpeed, unsigned int currentSpeed) noexcept {
  if (BLE_EMERGENCY_BUTTON_PRESSED) {
    /* Set Motor to 0 and set Input pins to high for faster stop */
    ESC.writeMicroseconds(THROTTLE_LOW);

    delay(5000); // 5 Seconds

    BLE_EMERGENCY_BUTTON_PRESSED = false;

    return;
  }

  if (motorSpeed > currentSpeed) {
    for (int i = currentSpeed; motorSpeed >= i; i += 10) {
      ESC.writeMicroseconds(i);
      delay(10);
      ESC_CURRENT_SPEED = i;
    }
  } else {
    for (int i = currentSpeed; motorSpeed <= i; i -= 10) {
      ESC.writeMicroseconds(i);
      delay(10);
      ESC_CURRENT_SPEED = i;
    }
  }
}


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  delay(5000);
/*------------------------------------------------------------------------------------------------*/
  
  ESC.attach(ESC_PIN);
  ESC_CURRENT_SPEED = THROTTLE_LOW;
  ESC.writeMicroseconds(ESC_CURRENT_SPEED);
}

void loop() {
  ArduinoCloud.update();
  
  if (!ArduinoCloud.connected()) {
    BLE_EMERGENCY_BUTTON_PRESSED = true; // On disconnect
    ESC_MOTOR_SPEED(THROTTLE_LOW, ESC_CURRENT_SPEED);
    Serial.println("Disconnected from central device!!!");
  }

  delay(150);
}

/*
  Since BLEMOTORSPEEDCLOUD is READ_WRITE variable, onBLEMOTORSPEEDCLOUDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBLEMOTORSPEEDCLOUDChange()  {
  Serial.println("BLE_BUTTON");
  BLE_MOTOR_SPEED = BLE_MOTOR_SPEED_CLOUD;

  int motorSpeed = map(BLE_MOTOR_SPEED, 0, 100, THROTTLE_LOW, THROTTLE_MAX);
  motorSpeed = constrain(motorSpeed, THROTTLE_LOW, THROTTLE_MAX);

  ESC_MOTOR_SPEED(motorSpeed, ESC_CURRENT_SPEED);
}
/*
  Since BLEEMERGENCYCLOUD is READ_WRITE variable, onBLEEMERGENCYCLOUDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBLEEMERGENCYCLOUDChange()  {
  Serial.println("BLE_BUTTON");
  BLE_EMERGENCY_BUTTON_PRESSED = BLE_EMERGENCY_CLOUD;
}

#endif