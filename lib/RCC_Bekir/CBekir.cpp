/*
 Name:		CBekir.cpp
 Created:	22/04/2016 18:04:56
 Author:	AcerE521
*/

#include "CBekir.h"

void CBekir::setup()
{
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
}

void CBekir::loop()
{
	//leds
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	digitalWrite(12, HIGH);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
	digitalWrite(13, LOW);
}
