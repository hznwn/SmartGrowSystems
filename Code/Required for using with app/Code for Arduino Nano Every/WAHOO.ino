// Define analog sensor pins
const int sensorPin1 = A1;  // Pin A1 connected to Sensor 1
const int sensorPin2 = A2;  // Pin A2 connected to Sensor 2
const int sensorPin3 = A3;  // Pin A3 connected to Sensor 3
const int sensorPin4 = A4;  // Pin A4 connected to Sensor 4

// Builtin LED
const int indicatorLedPin = LED_BUILTIN;  // Onboard LED pin


void setup() {
  Serial1.begin(115200); // Initialize serial1 at 115200 baud rate with a 1s delay to get is started
  delay(1000);

  pinMode(6, OUTPUT);   // Pin 6 supports PWM, LED 1
  pinMode(7, OUTPUT);   // Pin 7 supports PWM, LED 2
  pinMode(10, OUTPUT);  // Pin 10 supports PWM, LED 3
  pinMode(11, OUTPUT);  // Pin 11 supports PWM, LED 4

  pinMode(indicatorLedPin, OUTPUT); // Set indicator LED pin as OUTPUT
}

int led_status = 0;

void loop() {
  if (Serial1.available() > 0) { // Check if data is available to read from serial
    char command = Serial1.read();
  
    if (command == '1'){
      led_status = 1;
      digitalWrite(indicatorLedPin, HIGH); // Turn on the LED indicator
    }

    else if (command == '0'){
      led_status = 0;
      digitalWrite(indicatorLedPin, LOW); // Turn off the LED indicator
    }
  }

  if (led_status == 1){

  // Read analog sensor values
  int sensorValue1 = analogRead(sensorPin1);  // Read value from Sensor 1
  int sensorValue2 = analogRead(sensorPin2);  // Read value from Sensor 2
  int sensorValue3 = analogRead(sensorPin3);  // Read value from Sensor 3
  int sensorValue4 = analogRead(sensorPin4);  // Read value from Sensor 4

  // Map sensor values to PWM range and control LED brightness
  analogWrite(6, map(sensorValue1, 0, 1023, 0, 255));  // Sensor 1 -> pin 6 (LED 1)
  analogWrite(7, map(sensorValue2, 0, 1023, 0, 255));  // Sensor 2 -> pin 7 (LED 2)
  analogWrite(10, map(sensorValue3, 0, 1023, 0, 255)); // Sensor 3 -> pin 10 (LED 3)
  analogWrite(11, map(sensorValue4, 0, 1023, 0, 255)); // Sensor 4 -> pin 11 (LED 4)
  }

  else {
  
  digitalWrite(6, LOW); // Turn off light connected to pin 5
  digitalWrite(7, LOW); // Turn off light connected to pin 6
  digitalWrite(10, LOW); // Turn off light connected to pin 9
  digitalWrite(11, LOW); // Turn off light connected to pin 10
  }

  delay(10); // Small delay between sensor readings and LED updates
}
