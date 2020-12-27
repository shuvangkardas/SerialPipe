# SerialPipe

<!-- Badges -->
[![Build Status][build-shield]][build-url]
[![GitHub release][release-shield]][release-url]
[![GitHub commits][commits-shield]][commits-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

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

## Internal Library Opcode
The user cannot use opcode 0 to 9 for normal transaction. These opcodes are used by internal library 
- 1 ->  for connection check 

## Library Tested with
- Arduino Uno to Arduino Uno
- Arduino Uno to ESP8266



<!-- MARKDOWN LINKS & IMAGES -->
[build-shield]: https://travis-ci.com/shuvangkar/SerialPipe.svg?branch=master
[build-url]: https://travis-ci.com/github/shuvangkar/SerialPipe

[release-shield]: https://img.shields.io/github/release/shuvangkar/SerialPipe.svg
[release-url]: https://github.com/shuvangkar/SerialPipe

[commits-shield]: https://img.shields.io/github/commits-since/shuvangkar/SerialPipe/v0.1.0
[commits-url]: https://img.shields.io/github/commits-since/shuvangkar/SerialPipe/v0.1.0


[license-shield]: https://img.shields.io/github/license/shuvangkar/SerialPipe
[license-url]: https://github.com/shuvangkar/SIM800L/blob/master/LICENSE.txt


[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/shuvangkar