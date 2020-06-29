#ifndef SERIAL_PIPE_H
#define SERIAL_PIPE_H
#include <Arduino.h>

#define OK F("200#")
#define NOK F("400#")

class Pipe
{
public:
	Pipe(Stream *serialPtr);
	void setBoundary(char initiator, char terminator);

	void send(const char *data);
	char *read(char *dataPtr);

	bool sendNAck(const char *data);
	char *readNAck(char *dataPtr);

	int waitForAck();
	void ack();
	void noAck();
	// void sendAck(const __FlashStringHelper *msg);
	

	// bool sendAck(const char *data);
	


	int available();
	bool discardUntil(char terminator);
	char *readUntil(char *buffer,char terminator);
	int getOpcode();
	
private:
	Stream *serial;
	int _ackTimeout = 2000;

	long _last_millis;
	int _last_len;
	uint8_t _serialAvailCounter;
	char _initiator = '$';
	char _terminator = '#';
	void _bufferClear();
	int _timedRead();
};
#endif