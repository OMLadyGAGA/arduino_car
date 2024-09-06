// Ultrasonic sensor pins
#define trigPin 11
#define echoPin 12

// Motor driver pins
#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define in5 6
#define in6 7
#define in7 8
#define in8 9

// Distance thresholds in centimeters
#define distanceThresholdToStop 15
#define distanceThresholdToFollowStart 25
#define distanceThresholdToFollowEnd 45
#define DELAYTICKS 200

// Define pins
const int leftIrSensorPin = A1;  // Left IR sensor connected to A1
const int rightIrSensorPin = A2; // Right IR sensor connected to A2

void setup() {
    // Set motor pins as output
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);

    // Set left & right IR sensor pins as input
    pinMode(leftIrSensorPin, INPUT); 
    pinMode(rightIrSensorPin, INPUT);  

    // Set ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
    long duration, distance_CM;

    // Send a 10µs pulse to the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(echoPin, HIGH);

    distance_CM = microsecondsToCentimeters(duration);

    int leftSensorValue = digitalRead(leftIrSensorPin);   // Read left sensor value
    int rightSensorValue = digitalRead(rightIrSensorPin); // Read right sensor value

    // Print the distance for debugging
    Serial.print("Distance in CM: ");
    Serial.print(distance_CM);
    Serial.println(" cm");

    Serial.print("Left Sensor Value: ");
    Serial.println(leftSensorValue);
    Serial.print("Right Sensor Value: ");
    Serial.println(rightSensorValue);

    // Control the car based on the distance and sensor values
    if (distance_CM > distanceThresholdToFollowStart && distance_CM < distanceThresholdToFollowEnd) {
        if (leftSensorValue == LOW && rightSensorValue == LOW) {
            moveForward();
            Serial.println("Move Forward");
        } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
            turnLeft();
            Serial.println("Turn Left");
        } else if (rightSensorValue == LOW && leftSensorValue == HIGH) {
            turnRight();
            Serial.println("Turn Right");
        } else {
            moveForward();
            Serial.println("Move Forward");
        }
    } else if (distance_CM <= distanceThresholdToStop) {
        moveBackward();
        Serial.println("Move Backward");
    } else if (distance_CM > distanceThresholdToStop && distance_CM < distanceThresholdToFollowStart) {
        stopCar();
        Serial.println("Stop Car");
    }

    delay(DELAYTICKS); // Delay to prevent rapid switching
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void stopCar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void turnLeft() {
  // Adjust the motor outputs to turn left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void turnRight() {
  // Adjust the motor outputs to turn right
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

long microsecondsToCentimeters(long microseconds) {
    return (microseconds / 2) / 29.1;
}
