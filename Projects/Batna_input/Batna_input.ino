

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A3;  // Analog input pin that the potentiometer is attached to

const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue1 = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  sensorValue1 = analogRead(analogInPin1);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);

//if ((sensorValue < 100) && (sensorValue1 > 100)) {
//Serial.println("Caso 1");
//} else if ((sensorValue1 < 100) && ( sensorValue > 100)) {
//Serial.println("Caso 2");
//} else if ((sensorValue < 100) && (sensorValue1 < 100)) {
//Serial.println("Caso 3");
//
//}


  // print the results to the serial monitor:
  //Serial.print("sensor1 = " );
  Serial.print(sensorValue);
Serial.print("," );
//  Serial.print(" sensor2 = " );
  Serial.print(sensorValue1);
  Serial.println();
 // Serial.print("\t output = ");
 // Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(20);
}
