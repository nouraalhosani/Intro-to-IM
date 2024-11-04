// Pin Definitions
const int trigPin = 3;          // Trig pin for ultrasonic sensor
const int echoPin = 4;          // Echo pin for ultrasonic sensor
const int switchPin = 2;        // Switch to activate green LED
const int redLedPin = 9;        // Red LED for object detection
const int blueLedPin = 10;     // Blue LED controlled by switch

// Distance threshold to detect an object (in cm)
const int detectionThreshold = 20; 

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP);  // Use internal pull-up for switch
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  // Measuring distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Convert time to distance  in (cm)

  // Checks if an object is within the detection threshold
  if (distance > 0 && distance <= detectionThreshold) {
    digitalWrite(redLedPin, HIGH);   // Turns on red LED if an object is detected
  } else {
    digitalWrite(redLedPin, LOW);    // Turns off red LED if no object is detected
  }

  // Check switch state for blue LED
  int switchState = digitalRead(switchPin);
  if (switchState == LOW) {
    digitalWrite(blueLedPin, HIGH);  // Turns on the blue LED when switch is pressed
  } else {
    digitalWrite(blueLedPin, LOW);   // Turns off the blue LED when switch is not pressed
  }

  // Debugging information 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); //  delay 
}

