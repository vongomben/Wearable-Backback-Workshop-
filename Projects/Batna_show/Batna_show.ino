#include <Adafruit_NeoPixel.h>

int PIN = 9; // Adressable LED strip pin

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

// These constants won't change.  They're used to give names
// to the pins used:

const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A3;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue1 = 0;        // value read from the pot

int pressureTreshold = 0;
int pressureTreshold1 = 0;
int pressureTresholdOffset = 100;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //  while (!Serial);

  // calibrate during the first three seconds
  while (millis() < 5000) {
    sensorValue = analogRead(analogInPin);
    sensorValue1 = analogRead(analogInPin1);

    // record the maximum value for sensor
    if (sensorValue > pressureTreshold) {
      pressureTreshold = sensorValue;
    }

    // record the maximum value for sensor1
    if (sensorValue1 > pressureTreshold1) {
      pressureTreshold1 = sensorValue1;
    }

    delay(20);
  }

  pressureTreshold += pressureTresholdOffset;
  pressureTreshold1 += pressureTresholdOffset;

  Serial.print("Treshold : ");
  Serial.print(pressureTreshold);
  Serial.print(" ");
  Serial.println(pressureTreshold1);

  rainbowCycle(2);
  delay(50);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  sensorValue1 = analogRead(analogInPin1);

  if ((sensorValue > pressureTreshold) && (sensorValue1 < pressureTreshold1)) {
    Serial.print("Caso 1: DX -->");
    printAll();

    for (int i = 0; i < 4; i++) {
      //arrow right
      arrowRight();
      delay(500);
      //turn all leds off
      allOff();
      delay(500);
    }
  }
  else if ((sensorValue1 > pressureTreshold1) && ( sensorValue < pressureTreshold)) {
    Serial.print("Caso 2: SX -->");
    printAll();

    for (int i = 0; i < 4; i++) {
      arrowLeft();
      delay(500);
      //turn all leds off
      allOff();
      delay(500);
    }
  }
  else if ((sensorValue > pressureTreshold) && (sensorValue1 > pressureTreshold1)) {
    Serial.print("Caso 3: STOP -->");
    printAll();

    for (int i = 0; i < 10; i++) {
      // All Red
      stopp();
      delay(200);
      //turn all leds off
      allOff();
      delay(200);
    }

  } else if ((sensorValue < pressureTreshold) && (sensorValue1 < pressureTreshold1)) {
    Serial.print("Caso 4: GO -->");
    printAll();
    // All turned off
    allOff();
  }
}

void printAll() {

  //Serial.print("sensor1 = " );
  Serial.print(sensorValue);
  Serial.print("," );
  //  Serial.print(" sensor2 = " );
  Serial.print(sensorValue1);
  Serial.println();
}


void arrowRight() {
  colorAddress(0, strip.Color(0, 0, 0), 0); // first LED off
  
  colorAddress(1, strip.Color(255, 165, 0), 0); // second LED orange
  colorAddress(3, strip.Color(255, 165, 0), 75); // forth LED orange
  colorAddress(2, strip.Color(255, 165, 0), 75);   // third LED orange
}

void arrowLeft() {
    colorAddress(2, strip.Color(0, 0, 0), 0);   // third LED off
    
  colorAddress(1, strip.Color(255, 165, 0), 0); // second LED orange
  colorAddress(3, strip.Color(255, 165, 0), 75); // forth LED orange
  colorAddress(0, strip.Color(255, 165, 0), 75); // first LED orange
}

void stopp() {
  // All Red
  colorAddress(0, strip.Color(255, 0, 0), 0);
  colorAddress(2, strip.Color(255, 0, 0), 25);
  colorAddress(1, strip.Color(255, 0, 0), 0);
  colorAddress(3, strip.Color(255, 0, 0), 25);
}

void allOff() {
  colorAddress(0, strip.Color(0, 0, 0), 0);
  colorAddress(1, strip.Color(0, 0, 0), 0);
  colorAddress(2, strip.Color(0, 0, 0), 0);
  colorAddress(3, strip.Color(0, 0, 0), 0);
}

// Fill individual dots with a specific color
void colorAddress(int add, uint32_t c, uint8_t wait) {
  strip.setPixelColor(add, c);
  strip.show();
  delay(wait);

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}






