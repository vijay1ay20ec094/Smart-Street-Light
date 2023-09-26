#include <SPI.h>
#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#define CLIENT_ADDRESS 1 
#define SERVER_ADDRESS 2  

RH_RF95 rf95(4, 2); 

RHMesh manager(rf95, CLIENT_ADDRESS);

void setup() {
  Serial.begin(115200); 
  if (!manager.init()) { //initiate the LoRa module
    Serial.println("LoRa initialization failed.");
    while (1);
  }
  rf95.setFrequency(866.0); 
}

void loop() {
  String dataToSend = "Streetlight 1 is ON";
  String dataToSend1 = Serial.readString(); //Enter the data to be sent
  //in our project we have specified "On" to switch on light in node 3,"off" to turn off led remotely
  
  // Send data to Node 2
  manager.sendtoWait((uint8_t*)dataToSend.c_str(), dataToSend.length(), SERVER_ADDRESS); //Transmission line code
 delay(1000);
  manager.sendtoWait((uint8_t*)dataToSend1.c_str(), dataToSend1.length(), SERVER_ADDRESS);
  
  Serial.println("Data sent to Node 2: " + dataToSend);
  
  Serial.println("Data sent to Node 2: " + dataToSend1);

 // delay(1000); // Send data every 5 seconds
}
