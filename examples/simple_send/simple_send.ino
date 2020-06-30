#include "serial_pipe.h"
#include <SoftwareSerial.h>

SoftwareSerial pipeSerial(2, 3);

Pipe pipe(&pipeSerial);

char buf[100] = "Hello World!!";
void setup()
{
  Serial.begin(9600);
  pipeSerial.begin(9600);
  Serial.println(F("Setup done"));
}

void loop()
{
  Serial.println(F("<---------------Sending--------------->"));
  uint8_t opcode = random(1,30); //opcode is random generated
  pipe.send(opcode,buf);
  int ack = pipe.waitForAck();
  Serial.println(buf);
  Serial.print(F("ACK Code :"));Serial.println(ack);
  delay(1000);

}
