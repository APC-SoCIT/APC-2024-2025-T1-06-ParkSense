#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define IR_SENSOR_PIN D5 // IR sensor pin connected to GPIO D5
#define LED_PIN D4       // LED pin connected to GPIO D4

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your LCD's I2C address if needed

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);                     // Wait for 2 seconds
  lcd.clear();

  Serial.begin(115200);            // Start serial communication
  Serial.println("IR Sensor with LCD and LED Test...");
}

void loop() {
  int irState = digitalRead(IR_SENSOR_PIN); // Read the IR sensor state
  Serial.print("IR Sensor State: ");
  Serial.println(irState);         // Debugging: check IR sensor state

  if (irState == LOW) {            // Assuming LOW means object detected
    digitalWrite(LED_PIN, HIGH);   // Turn on the LED
    lcd.setCursor(0, 0);
    lcd.print("S1: Full   ");      // Update LCD to show "Full"
    Serial.println("Object detected! LED ON.");
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn off the LED
    lcd.setCursor(0, 0);
    lcd.print("S2: Empty  ");      // Update LCD to show "Empty"
    Serial.println("No object detected. LED OFF.");
  }

  delay(500);                      // Delay for readability
}
