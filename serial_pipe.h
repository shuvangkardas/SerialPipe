#ifndef SERIAL_PIPE_H
#define SERIAL_PIPE_H
#include <Arduino.h>

#define OK F("200#")
#define NOK F("404#")

class Pipe
{
public:
	Pipe(Stream *serialPtr);
	void setBoundary(char initiator, char terminator);

	int getOpcode();
	void send(const char *data);
	void send(uint8_t opCode, const char *data);
	char *read(char *dataPtr);

	bool sendWithAck(const char *data);
	char *readWithAck(char *dataPtr);

	int waitForAck();
	void ack();
	void noAck();
	
private:
	Stream *serial;
	int _ackTimeout = 2000;

	long _last_millis;
	char _initiator = '$';
	char _terminator = '#';

	int _available();
	char *readUntil(char *buffer,char terminator);
	bool _discardUntil(char terminator);
	void _bufferClear();
	int _timedRead();
};
#endif