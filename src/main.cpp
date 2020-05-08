const int SERIAL_BUFFER_SIZE = 50;
char serialBuffer[SERIAL_BUFFER_SIZE];

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)


DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

bool readSerial(Stream&);

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
   }
  dht.begin();
}
  
void loop() {

 
   float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return; 
   }  
 
  
//    Serial.print("Humidity: "); 
//    // Serial.print(" ");
//    Serial.print(h);
//    Serial.println(" %\t ");
//    
//    Serial.print("Temperature DHT: "); 
//    Serial.print(t);
//    Serial.println(" *C ");
//    
//    
//    Serial.print("Temperature BMP180 = ");
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");
//    
//    Serial.print("Pressure = ");
//    Serial.print(bmp.readPressure());
//    Serial.println(" Pa");
//    
//    // Calculate altitude assuming 'standard' barometric
//    // pressure of 1013.25 millibar = 101325 Pascal
//    Serial.print("Altitude = ");
//    Serial.print(bmp.readAltitude());
//    Serial.println(" meters");
//
//    Serial.print("Pressure at sealevel (calculated) = ");
//    Serial.print(bmp.readSealevelPressure());
//    Serial.println(" Pa");
//
//  // you can get a more precise measurement of altitude
//  // if you know the current sea level pressure which will
//  // vary with weather and such. If it is 1015 millibars
//  // that is equal to 101500 Pascals.
//    Serial.print("Real altitude = ");
//    Serial.print(bmp.readAltitude(101200));
//    Serial.println(" meters");
    
    Serial.print(h);
    Serial.print("  ");
    Serial.print(t);
    Serial.print("  ");
    Serial.print(bmp.readPressure());
    Serial.println();

 if (readSerial(Serial) )      //liefert true wenn das LF eingelesen wurde
  {   
    Serial.print("String: ");
    Serial.println(serialBuffer);

//    int var1 = atoi(strtok(serialBuffer, ","));
//    int var2 = atoi(strtok(NULL, ","));
//    int var3 = atoi(strtok(NULL, ","));
//
//    Serial.println(var1);
//    Serial.println(var2);
//    Serial.println(var3);
//    Serial.println();
  }
   delay(2000);
}
bool readSerial(Stream& stream)
{
  static byte index;

    while (stream.available())
    {
      char c = stream.read();

      if (c == '\n' && index > 0)       //wenn LF eingelesen und String länger als 0 ist
      {
        serialBuffer[index] = '\0';     //String terminieren
        index = 0;
        return true;                    //melden dass String fertig eingelesen wurde
      }
      else if (c >= 32 && index < SERIAL_BUFFER_SIZE - 1)   //solange noch Platz im Puffer ist
      {
        serialBuffer[index++] = c;    //Zeichen abspeichern und Index inkrementieren
      }
    }
    return false;        //noch nicht fertig
}

   

   
