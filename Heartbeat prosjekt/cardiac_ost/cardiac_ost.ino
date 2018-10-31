#include <SPI.h>
#include <SD.h>

File myFile;

const int chipSelect = 53;
unsigned int cardiac_array[5] = {939, 940, 941, 942, 944};
bool HaveSDCard = false;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:pinMode(chipSelect,OUTPUT);
  const int chipSelect = 53; // MEGA CS

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  if (SD.begin(chipSelect) )
  {
    HaveSDCard = true;
    Serial.print("SD Card - OK");
  }
  else
    Serial.print("SD Card - FAIL");

  delay( 2000 );
}
void loop()
{
  if ( HaveSDCard )
  {
    myFile = SD.open("test.txt", FILE_WRITE);

    if ( !myFile )
      for ( int i = 0; i < 5; i++ )
      {
        if ( !myFile )
        {
          delay( 500 );
          myFile = SD.open("test.txt", FILE_WRITE );
        }
      }

    if ( myFile )
    {
      //myFile.print(cardiac_array);
      for (int i = 0; i < (sizeof(cardiac_array))/2; i++) {
        myFile.print(cardiac_array[i]);
        myFile.print(" ,");
      }
      //close the file;
      delay(500);
      myFile.close();
      myFile.flush();
      Serial.print("Writing OK. DONE");
    }
    else
      Serial.print("Writing FAIL!");
  }

  HaveSDCard = false;
}
