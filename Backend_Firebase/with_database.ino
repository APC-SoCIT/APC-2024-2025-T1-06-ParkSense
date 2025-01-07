#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseESP8266.h>  // Include Firebase ESP8266 library
#include <ESP8266WiFi.h>

#define WIFI_SSID "WiFi Name"
#define WIFI_PASSWORD "WiFi Password"

// Replace with your Firebase credentials
#define FIREBASE_HOST "https://ir-sensor-project-bfab0-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "urWEKxTQG0tA3ITXdwSgA1wqyAOTI2XrXTCXDm08"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Firebase reference path
String path = "/sensor_status";

// IR Sensor Pin and LED Pin
#define IR_SENSOR_PIN D5
#define LED_PIN D4

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Configure the IR sensor and LED pin modes
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED starts in the OFF state

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected.");

  // Set up Firebase configuration
  firebaseConfig.database_url = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int irState = digitalRead(IR_SENSOR_PIN); // Read the IR sensor state
  Serial.print("IR Sensor State: ");
  Serial.println(irState);

  if (irState == LOW) {  // Object detected
    digitalWrite(LED_PIN, HIGH);   // Turn on the LED
    lcd.setCursor(0, 0);
    lcd.print("S1: Full ");
    Serial.println("Object detected! LED ON.");

    // Write "Full" status to Firebase and check success
    bool success = Firebase.setString(firebaseData, path, "Full");
    if (success) {
      Serial.println("Data written to Firebase successfully.");
    } else {
      Serial.print("Firebase write failed. Error: ");
      Serial.println(firebaseData.errorReason());
    }

  } else {  // No object detected
    digitalWrite(LED_PIN, LOW);    // Turn off the LED
    lcd.setCursor(0, 0);
    lcd.print("S2: Empty");
    Serial.println("No object detected. LED OFF.");

    // Write "Empty" status to Firebase and check success
    bool success = Firebase.setString(firebaseData, path, "Empty");
    if (success) {
      Serial.println("Data written to Firebase successfully.");
    } else {
      Serial.print("Firebase write failed. Error: ");
      Serial.println(firebaseData.errorReason());
    }
  }

  delay(500);
}
