/*	
By Vincent Gosselin, 2017.

The following is a program to monitor
temperature and humidity in Vincent's Room.

The state machine of the program :
1 : Wait for 10sec
2 : Acquire temperature and humidity
3 : Construct a string to send to InfluxDB (inside a AWS server)
4 : Send the string using the Lora Module
*/

//This is using a nice library to simplify the code.
#include "Lora_simplified.h"
//Custom tools for a better code.
#include "arduinotools.h"
//Library for the DHT11 sensor
#include "arduinonanodht11.h"

//Library for lowpower
#include "LowPower.h"

/* Global Objects */

//SmarWait timer, from arduinotools lib.
//SmartWait timer1;	
//DHT11 sensor
dht11 dht11(2);//PIN 2.

/* Global Variables */ 
int temperature;
int humidity;

void setup()
{
  //Lora_init();
  Serial.begin(38400);
  Serial.println("Hello");
}

void loop(void)
{
  // //SLEEP for 8sec.
  // LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  // delay(50);
  //Serial.begin(38400);


  // //SmarWait timer, from arduinotools lib.
  // SmartWait timer1; 
  // //DHT11 sensor
  // dht11 dht11(2);//PIN 2.

  // /* Global Variables */
  // int temperature;
  // int humidity;
  Serial.println("Wake up");
  Lora_init();
  // Serial.println("Hello");

  //Scan temperature and humidity
  dht11.scan();
  //Serial.print("Humidity is : ");Serial.println(dht11.get_humidity(),DEC);
  //Serial.print("Temperature is : ");Serial.println(dht11.get_temperature(),DEC);
  temperature = dht11.get_temperature();
  humidity = dht11.get_humidity();

  //string to send
  char string[100];
  sprintf(string, "\\!node1:temperature_air=%d:humidity_air=%d", temperature,humidity);
  Lora_send_string(string);

  Serial.println("Die now");

  //SLEEP for 8sec.
  delay(50);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  delay(50);
     
}


