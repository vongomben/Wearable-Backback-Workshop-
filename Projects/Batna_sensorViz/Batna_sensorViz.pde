import processing.serial.*;
Serial myPort;
int lnfeed = 10;   // Linefeed in ASCII
int numBand = 2;  // number of band
int band[];       // array to read the 7 values



void setup() { 
  size(800, 600); 
  noStroke(); 
  //textFont(f);
  println(Serial.list());
  //  String portName = Serial.list()[0];
  String portName = "/dev/ttyACM1"; 
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil(lnfeed);
} 

void draw() { 
  background(0);

  for (int i=0; i < numBand; i++) {

    int value = band[i];
    value = int(map(value, 0, 1024, 0, height));
    fill(value);
    rect ((i*width/2)+3, height-value, (width/2)-6, value);
  }
}


// Thanks to Enkel Bici previous code for this. 

void serialEvent(Serial myPort) {

  String myString = myPort.readStringUntil(lnfeed);

  // if you got any bytes other than the linefeed:
  if (myString != null) {

    myString = trim(myString);
    band = int(split(myString, ','));
    //print(band.length);
    for (int bandNum = 0; bandNum < band.length-1; bandNum++) {
      print("Sensor " + bandNum + ": " + band[bandNum] + "\t");
    }

    // add a linefeed after all the sensor values are printed:
    println();
  }
}
