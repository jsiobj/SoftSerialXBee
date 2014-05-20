//---------------------------------------------------------------------
// Test program for XBee Series 2
// Using SoftwareSerial instead of Arduino's Hardware serial
//---------------------------------------------------------------------

#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(7,8); // Starting Soft Serial on pin 7 & 8
                                // XBee Tx connected to 7 (Rx), XBee Rx to 8 (Tx)

//---------------------------------------------------------------------
void xbeePrintConfig() {
  
  boolean bCmdMode=false;
  char xbeeReponse[32];
  
  Serial.println(F("XBee config Test Program"));

sre  Serial.print(F("Getting in CMD mode"));
  while(!bCmdMode) {
    Serial.print(F("."));
    delay(1200);
    xbeeSerial.print("+++");
    delay(1200);

    while (xbeeSerial.available() > 0) {
      xbeePrintResponse(0);
      bCmdMode=true;
    }
  }
  xbeeSendCommand("ATCH");
  xbeeSendCommand("ATID");
  xbeeSendCommand("ATDH");
  xbeeSendCommand("ATSL");
  xbeeSendCommand("ATDH");
  xbeeSendCommand("ATDL");
  xbeeSendCommand("ATMY");
  xbeeSendCommand("ATCN");
}

//---------------------------------------------------------------------
void xbeeSendCommand(char cmd[5]) {
  Serial.print(cmd);Serial.print(": ");
  xbeeSerial.write(cmd); xbeeSerial.write("\r");
  xbeePrintResponse(500);
}

//---------------------------------------------------------------------
void xbeePrintResponse(int timeout) {
  long int last=millis();
  
  // Looking for an output for timeout ms max
  while(xbeeSerial.available()>0 || millis()-last<timeout) {
    
    if(xbeeSerial.available()>0) {                            // We got something (at least 1 byte)
      char charRead=xbeeSerial.read(); 
      while(charRead!='\r' && xbeeSerial.available()>0) {     // Printing out until we get something different from CR
        Serial.write(charRead);
        charRead=xbeeSerial.read(); 
      }
      Serial.println();
    }
  }
}

//---------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  xbeePrintConfig();
}

void loop() {
  // Nothing else to do...
}
