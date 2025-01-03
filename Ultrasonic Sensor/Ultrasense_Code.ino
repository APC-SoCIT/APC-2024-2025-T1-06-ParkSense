#define TRIG_PIN D1   // TRIG pin connected to GPIO D1
#define ECHO_PIN D2   // ECHO pin connected to GPIO D2
#define LED_PIN D4    // LED pin connected to GPIO D4

long duration;
int distance;

void setup() {
  Serial.begin(115200); // Use a higher baud rate for ESP8266
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Ultrasonic Sensor with NodeMCU Test...");
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout for long pulses

  // Check if a valid pulse was received
  if (duration == 0) {
    Serial.println("No echo detected.");
    digitalWrite(LED_PIN, LOW); // Turn LED OFF
  } else {
    // Calculate distance in cm
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Check if object is within a specific range
    if (distance > 0 && distance <= 100) {
      digitalWrite(LED_PIN, HIGH); // Turn LED ON
      Serial.println("Object detected!");
    } else {
      digitalWrite(LED_PIN, LOW); // Turn LED OFF
      Serial.println("No object within range.");
    }
  }

  delay(500); // Delay for readability
}
