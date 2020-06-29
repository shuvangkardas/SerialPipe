#include "serial_pipe.h"


Pipe::Pipe(Stream *serialPtr)
{
	serial = serialPtr;
}

int Pipe::_timedRead()
{
	int c;
	_last_millis = millis();
	do
	{
		c = serial -> read();
		if (c > 0 )
		{
			return c;
		}
	} while ((millis() - _last_millis) < 1000);
	return -1;
}

char * Pipe::readUntil(char *buffer,char terminator)
{
	char *ptr  = buffer;

	int c = _timedRead();
	while(c >=0 && c != terminator)
	{
		*ptr = (char)c;
		ptr++;
		c = _timedRead();
	}

	// Serial.print("Term : ");Serial.println((char)c);
	//Check terminator found properly or not. 
	if(c == terminator)
	{
		// Serial.println(F("Term: "));
		*ptr = '\0'; //string terminator as extra safety
		return buffer;
	}
	else
	{
		// Serial.println(F("Not Term"));
		return ptr;//sending the position of null pointer;
	}
	// Serial.print("Term : ");Serial.println((char)c);
	
	// _bufferClear();
	// return buffer;
}

void Pipe::_bufferClear()
{
	while (serial -> available())
	{
		serial -> read();
	}
}

int Pipe::available()
{
	int len = serial -> available();
	if(len > 0)
	{
		return len;
	}
	else
	{
		return -1;
	}
	// int current_len = 0;
	// current_len = serial -> available();
	// int len_diff = current_len  - _last_len;
	// if(len_diff>0)
	// {
	// 	Serial.println(F("Increasing"));
	// 	_last_len = current_len;
	// 	_last_millis = millis();
	// }
	// else
	// {
	// 	long current_millis = millis();
	// 	if( current_millis -  _last_millis > 1000)
	// 	{
	// 		_last_millis = current_millis;
	// 		if(current_len> 0 ) return current_len;
	// 	}
	// }
	// return -1;
}

bool Pipe::discardUntil(char terminator)
{
	int c = 0;
	do
	{
		c = _timedRead();
		if((char)c == terminator)
		{
			// Serial.print(F("Found: "));Serial.println((char)c);
			return true;
		} 
	}while(c>0);

	return false;
}

int Pipe::getOpcode()
{
	int length = available();
	if(length > 0)
	{
		bool firstChar = discardUntil(_initiator);
		if(firstChar)
		{
			char opStr[6];
			char *ptr = readUntil(opStr,'=');
			// Serial.print("op: ");Serial.println(ptr);
			int opcode = atoi(ptr);
			return opcode;
		}
	}
	return -1;

}

void Pipe::send(const char *data)
{
	serial -> print(data);
}

char *Pipe::read(char *dataPtr)
{
	char *ptr = dataPtr;
	return readUntil(ptr,_terminator);//This ensures teminated properly
	// return dataPtr;
}

// void Pipe::sendAck(const __FlashStringHelper *msg)
// {
// 	serial -> print(msg);
// }

void Pipe::ack()
{
	serial -> print(OK);
}
void Pipe::noAck()
{
	serial ->print(NOK);
}

int Pipe::waitForAck()
{
	int timeOut = _ackTimeout;
	char ackData[5];
	while(--timeOut)
	{
		if(serial -> available())
		{
			char *ptr = read(ackData);
			int code = atoi(ptr);
			// Serial.println(code);
			return code;
		}
		delay(1);
	}
	// Serial.println(F("Timeout"));
	return -1;
}


bool Pipe::sendNAck(const char *data)
{
	serial -> print(data);
	int code = waitForAck();
}


char *Pipe::readNAck(char *dataPtr)
{
	char *ptr = dataPtr;
	readUntil(ptr,_terminator);
	int len = strlen(dataPtr);
	if(len >0 )
	{
		// sendAck(OK);
		ack();
		// serial -> print(F("200#"));
		// serial -> print(F("404#"));
	}
	else
	{
		noAck();
		// serial -> print(F("404#"));
	}
	Serial.println(dataPtr);
	return dataPtr;
}

