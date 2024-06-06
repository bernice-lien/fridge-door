
#include <Wire.h>
#include "SparkFun_VL53L1X.h" 

SFEVL53L1X distanceSensor;
int buzzerPin = 13;
int beep_init = 1;

void setup(void)
{
  Wire.begin();

  Serial.begin(115200);
  Serial.println("Booting Sensor");

  if (distanceSensor.begin() != 0) 
  {
    Serial.println("Error in Booting");
    while (1)
      ;
  }
  Serial.println("Sensor online!");
}

void loop(void)
{
  distanceSensor.startRanging(); //start measurment
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();
  Serial.print("Distance(mm): ");
  Serial.print(distance);
  Serial.println();
 
  if(beep_init == -1 & distance > 12)
  {
    tone(buzzerPin, 523, 1000); 
    delay(1000);
    tone(buzzerPin, 659, 1000); 
    delay(1000);
    tone(buzzerPin, 392, 1000); 
    delay(1000);
    tone(buzzerPin, 523, 1000);
    delay(1000);
    beep_init = 1;
  }

  if (distance > 12 & beep_init == 1)
  {
    
    Serial.print("Waiting....");
    delay(120000);
    Serial.print("Done!");
    Serial.println();

  }

  if (distance < 12)
    beep_init = 1;
    delay(2000);




}
