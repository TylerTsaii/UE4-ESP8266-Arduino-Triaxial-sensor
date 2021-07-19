 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "CU_e9fE"
#define STAPSK  "88888888"
#endif

unsigned int localPort = 9989;      // local port to listen on

// buffers for receiving and sending data
//char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged\r\n";       // a string to send back

WiFiUDP Udp;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Udp.begin(localPort);  
  Udp.beginPacket({192,168,1,4}, 7788);  
}


void loop() {
  char a[20] = ""; //定义字符数组，接受来自上位机的数据
  int i = 0;
  while (!Serial.available()); //等待数据传送过来，若没有数据，一直等待，即执行到本行不向下执行
  while (Serial.available()) //当发现缓存中有数据时，将数据送至字符数组a中
  {
    a[i] = Serial.read();
    i++;
    delay(3);
  }
  
  //int packetSize = Udp.parsePacket();
  Udp.write(a);
  Udp.endPacket();
  Serial.println(a);
  delay(10);
}
