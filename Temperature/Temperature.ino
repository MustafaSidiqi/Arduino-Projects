// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain


#include <virtuabotixRTC.h>
// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);


#include <DHT.h>
#define DHTPINa 2     // what pin we're connected to
#define DHTPINb 4     // what pin we're connected to
#include <SPI.h>
#include <SD.h>
File myFile;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT  DHTa(DHTPINa, DHTTYPE), DHTb(DHTPINb, DHTTYPE) ;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("tempdata.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("Writing to tempdata.txt...");
  } else {
    Serial.println("Error SD-card");
  }
  DHTa.begin();
}

void loop() {

  myFile = SD.open("tempdata.txt", FILE_WRITE);
  if (!myFile) {
    Serial.println("Error SD-card");
    for (;;) {
    }
  }
  // Wait a few seconds between measurements.

  // if the file opened okay, write to it:
  myRTC.updateTime();
  // Start printing elements as individuals
  myFile.print("Current Date / Time: ");
  myFile.print(myRTC.dayofmonth);
  myFile.print("/");
  myFile.print(myRTC.month);
  myFile.print("/");
  myFile.print(myRTC.year);
  myFile.print("  ");
  myFile.print(myRTC.hours);
  myFile.print(":");
  myFile.print(myRTC.minutes);
  myFile.print(":");
  myFile.println(myRTC.seconds);
  // Start printing elements as individuals
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  myFile.println("");
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float ha = DHTa.readHumidity();
  // Read temperature as Celsius
  float ta = DHTa.readTemperature();
  // Read temperature as Fahrenheit
  float fa = DHTa.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  // if (isnan(h) || isnan(t) || isnan(f)) {
  // Serial.println("Failed to read from DHT sensor!");
  // return;
  // }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hia = DHTa.computeHeatIndex(fa, ha);

  Serial.print("Transducer A:  Humidity: ");
  myFile.print("Transducer A:  Humidity: ");
  Serial.print(ha);
  myFile.print(ha);
  Serial.print(" % ");
  myFile.print(" % ");
  Serial.print("Temperature: ");
  myFile.print("Temperature: ");
  Serial.print(ta);
  myFile.print(ta);
  Serial.print(" *C      ");
  myFile.print(" *C      ");
  Serial.print(fa);
  myFile.print(fa);
  Serial.print(" *F  ");
  myFile.print(" *F  ");
  Serial.print("Heat index: ");
  myFile.print("Heat index: ");
  Serial.print(hia);
  myFile.print(hia);
  Serial.println(" *F");
  myFile.println(" *F");

  myFile.println("");
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float hb = DHTb.readHumidity();
  // Read temperature as Celsius
  float tb = DHTb.readTemperature();
  // Read temperature as Fahrenheit
  float fb = DHTb.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  // if (isnan(h) || isnan(t) || isnan(f)) {
  // Serial.println("Failed to read from DHT sensor!");
  // return;
  // }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hib = DHTb.computeHeatIndex(fb, hb);

  Serial.print("Transducer B:  Humidity: ");
  Serial.print(hb);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(tb);
  Serial.print(" *C      ");
  Serial.print(fb);
  Serial.print(" *F  ");
  Serial.print("Heat index: ");
  Serial.print(hib);
  Serial.println(" *F");

  myFile.print("Transducer B:  Humidity: ");
  myFile.print(hb);
  myFile.print(" % ");
  myFile.print("Temperature: ");
  myFile.print(tb);
  myFile.print(" *C      ");
  myFile.print(fb);
  myFile.print(" *F  ");
  myFile.print("Heat index: ");
  myFile.print(hib);
  myFile.println(" *F");
  myFile.println("");
  myFile.close();

  delay(300000);
}
