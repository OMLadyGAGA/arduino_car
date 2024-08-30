// Ultrasonic sensor pins; (找出那個pin 把他安裝對根據我給的網站)
#define trigPin 11
#define echoPin 12

// Motor driver pins (adjusted to match your setup)
#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define in5 6
#define in6 7
#define in7 8
#define in8 9

// Distance thresholds in centimeters
#define distanceThresholdFront 15
#define distanceThresholdBack 25

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

    // Set left & right IR sensor pin as input
    pinMode(leftIrSensorPin, INPUT); 
    pinMode(rightIrSensorPin, INPUT);  

    // Set ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
    long duration, distance_inches, distance_CM;

    // Send a 10µs pulse to the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(echoPin, HIGH);

    distance_inches = microsecondsToInches(duration);
    distance_CM = microsecondsToCentimeters(duration);

    int leftSensorValue = digitalRead(leftIrSensorPin);   // Read left sensor value
    int rightSensorValue = digitalRead(rightIrSensorPin); // Read right sensor value

    // Print the distance for debugging
    Serial.print("distance in CM: ");
    Serial.print(distance_CM);
    Serial.println(" cm");

    // Control the car based on the distance
    if (distance_CM > distanceThresholdFront && distance_CM < distanceThresholdBack) {
        stopCar();
        Serial.println("Obstacle detected, stopping the car");

    }else if(distance_CM < distanceThresholdFront){
        moveBackward();
        Serial.println("Move Backward");

    else if(distance_CM > distanceThresholdBack){
        moveForward();
        Serial.println("Move Forward");

    } else if(leftSensorValue == LOW){
        turnLeft();
        Serial.println("Turn Left");

    }else if(rightSensorValue == LOW){
        turnRight();
        Serial.println("Turn Right");

    }


    delay(200); // Delay to prevent rapid switching
    stopCar();
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


long microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are 73.746
    // microseconds per inch (i.e. sound travels at 1130 feet per second).
    // This gives the distance travelled by the ping, outbound and return,
    // so we divide by 2 to get the distance of the obstacle.
    // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
    return (microseconds/2) / 74;
}

long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the object we
    // take half of the distance travelled.
    return (microseconds/2) / 29.1;
}


// void loop() {
//     int leftSensorValue = digitalRead(leftIrSensorPin);   // Read left sensor value
//     int rightSensorValue = digitalRead(rightIrSensorPin); // Read right sensor value

//     // Check if either sensor detects an object
//     if (leftSensorValue == LOW || rightSensorValue == LOW) {
//     // Object detected by either sensor
//     digitalWrite(ledPin, HIGH);  // Turn on the LED
//     Serial.println("Object detected!");
//     } else {
//     // No object detected by either sensor
//     digitalWrite(ledPin, LOW);   // Turn off the LED
//     }

//     delay(100);  // Small delay to stabilize the reading
// }
