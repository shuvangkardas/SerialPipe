#include "serial_pipe.h"
#include <SoftwareSerial.h>

SoftwareSerial pipeSerial(2, 3);

Pipe pipe(&pipeSerial);

char buf[100];

void setup()
{
  Serial.begin(9600);
  pipeSerial.begin(9600);
}

void loop()
{
  int opCode = pipe.getOpcode();
  if (opCode > 0)
  {
    Serial.println(F("<---------------Receiving--------------->"));
    Serial.print(F("opcode: ")); Serial.println(opCode);
    Serial.println(pipe.read(buf));
    pipe.ack();
  }

}
