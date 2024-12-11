#include <math.h> // For sqrt()

// Pin definitions
const int buttonPin = 10; // Arcade button connected to digital pin 10
const int ledPin = 13;    // LED connected to digital pin 13
const int xPin = A0;      // Accelerometer X-axis output
const int yPin = A1;      // Accelerometer Y-axis output
const int zPin = A2;      // Accelerometer Z-axis output

// ADXL335 constants
const float sensitivity = 0.1; // Sensitivity in V/G
const float vRef = 3.3;        // Reference voltage
const float impactThreshold = 2.5; // Minimum G value for a punch

// Variables for button and accelerometer
bool buttonPressed = false; // Tracks if the button is pressed
bool scoreSent = false;     // Tracks if the score has already been sent
float baselineX, baselineY, baselineZ;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button with pull-up resistor
  pinMode(ledPin, OUTPUT);          // LED output
  Serial.begin(9600);               // Serial communication

  // Calculate accelerometer baseline
  calculateBaseline();
}

void loop() {
  handleButton();
  if (!scoreSent) { // Only handle accelerometer if the score has not been sent
    handleAccelerometer();
  }
}

void handleButton() {
  int buttonState = digitalRead(buttonPin);

  // Detect button press and send "START" only once
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;       // Mark the button as pressed
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("<START>");  // Send "START" marker
    scoreSent = false;          // Reset score flag on restart
    delay(200);                 // Debounce delay
  } else if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;      // Reset the button state
    digitalWrite(ledPin, LOW);  // Turn off LED
  }
}

void handleAccelerometer() {
  // Read raw values from accelerometer
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);
  int zRaw = analogRead(zPin);

  // Convert raw values to voltage
  float xVoltage = (xRaw / 1023.0) * vRef;
  float yVoltage = (yRaw / 1023.0) * vRef;
  float zVoltage = (zRaw / 1023.0) * vRef;

  // Calculate acceleration in G
  float xG = ((xVoltage - vRef / 2) / sensitivity) - baselineX;
  float yG = ((yVoltage - vRef / 2) / sensitivity) - baselineY;
  float zG = ((zVoltage - vRef / 2) / sensitivity) - baselineZ;

  // Calculate acceleration magnitude
  float magnitudeG = sqrt(xG * xG + yG * yG + zG * zG);

  // Detect punch and send score only once
  if (magnitudeG > impactThreshold && !scoreSent) {
    int punchValue = map(magnitudeG, impactThreshold, impactThreshold + 10, 0, 2500);
    punchValue = constrain(punchValue, 0, 2500); // Constrain value to a maximum

    if (punchValue > 0) { // Ignore 0 scores
      Serial.print("<,:");
      Serial.print(punchValue); // Send score value
      Serial.println(">");      // End the packet
      scoreSent = true;         // Mark the score as sent
    }
    delay(200); // Prevent multiple detections for one punch
  }
}

void calculateBaseline() {
  int samples = 100;
  float sumX = 0, sumY = 0, sumZ = 0;

  for (int i = 0; i < samples; i++) {
    int xRaw = analogRead(xPin);
    int yRaw = analogRead(yPin);
    int zRaw = analogRead(zPin);

    float xVoltage = (xRaw / 1023.0) * vRef;
    float yVoltage = (yRaw / 1023.0) * vRef;
    float zVoltage = (zRaw / 1023.0) * vRef;

    sumX += (xVoltage - vRef / 2) / sensitivity;
    sumY += (yVoltage - vRef / 2) / sensitivity;
    sumZ += (zVoltage - vRef / 2) / sensitivity;

    delay(10);
  }

  baselineX = sumX / samples;
  baselineY = sumY / samples;
  baselineZ = sumZ / samples;

  Serial.println("Baseline Calculated:");
  Serial.print("X: ");
  Serial.println(baselineX);
  Serial.print("Y: ");
  Serial.println(baselineY);
  Serial.print("Z: ");
  Serial.println(baselineZ);
}
