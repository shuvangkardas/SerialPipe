# SerialPipe

## Bidrectional peer to peer library 
This is a simple bidirectional communication library in between two microcontrollers. So, the main advantage of the library is that any microcontroller can send  data to other microcontroller like `send(opcode,data)` and the other microcontroller send acknowledge if data packet is valid.  Depending on the opcode the microcontroller can interprete the data and performs different actions. 


## Sender Example
```
int opcode  = 10;
char data[] = "Sample data block"
pipe.send(opcode, data);
```
## Receiver Example
```
char readBuf[100];
int opCode = pipe.getOpcode();
if (opCode > 0)
{
    switch(opCode)
    {
        case 10:
            Serial.println(pipe.read(readBuf));
            pipe.ack();
        break;
        case 12:
            //perform different action
        break;
    }
}
```
## Testing 
- Arduino UNO to Arduino Uno Tested
- Arduino Uno to ESP8266 Tested