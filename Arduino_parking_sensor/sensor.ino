// Pin definitions for ultrasonic sensors
const int CAR_SENSORS[3][2] = {
  {2, 3},   // Car Slot 1 (TRIG_PIN, ECHO_PIN)
  {4, 5},   // Car Slot 2
  {6, 7}    // Car Slot 3
};

const int MOTORCYCLE_SENSORS[3][2] = {
  {8, 9},   // Motorcycle Slot 1
  {10, 11}, // Motorcycle Slot 2
  {12, 13}  // Motorcycle Slot 3
};

// Constants for vehicle detection
const float CAR_THRESHOLD = 100.0;        // Distance in cm for car detection
const float MOTORCYCLE_THRESHOLD = 50.0;  // Distance in cm for motorcycle detection
const int READINGS_COUNT = 3;             // Number of readings to average

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  for (int i = 0; i < 3; i++) {
    pinMode(CAR_SENSORS[i][0], OUTPUT);
    pinMode(CAR_SENSORS[i][1], INPUT);
    pinMode(MOTORCYCLE_SENSORS[i][0], OUTPUT);
    pinMode(MOTORCYCLE_SENSORS[i][1], INPUT);
  }
}
