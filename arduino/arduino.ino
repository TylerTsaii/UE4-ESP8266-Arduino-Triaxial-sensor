#include <DFRobot_LIS2DW12.h>
DFRobot_LIS2DW12_I2C acce;
#if defined(ESP32) || defined(ESP8266)
#define LIS2DW12_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS2DW12_CS 3
#elif (defined NRF5)
#define LIS2DW12_CS 2  //The pin on the development board with the corresponding silkscreen printed as P2
#endif

 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //RX=2,TX=3
 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);  
  while(!acce.begin()){
     Serial.println("Communication failed, check the connection and I2C address setting when using I2C communication.");
     delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  acce.softReset();
  acce.continRefresh(true);
  acce.setDataRate(DFRobot_LIS2DW12::eRate_50hz);
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF); 
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise2_14bit);
  Serial.print("Acceleration:\n");
  delay(100);  
}
 
void loop() {
  char s1[] = "x|" ;
  char s2[] = "|Y|";
  char s3[] = "|Z|";
  char strx[] ="";
  char stry[] ="";
  char strz[] ="";
  int i = 0;
  itoa(acce.readAccX(),strx,10);
  strcat(s1,strx);  
  Serial.println(s1);
  mySerial.print(s1);

  
  itoa(acce.readAccY(),stry,10);
  strcat(s2,stry);
  Serial.println(s2);
  mySerial.print(s2);

  itoa(acce.readAccZ(),strz,10);
  strcat(s3,strz);
  Serial.println(s3);
  mySerial.print(s3);

  
  delay(40);
}
