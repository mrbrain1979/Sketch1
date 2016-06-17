/*
 Name:		Sketch1.ino
 Created:	17.06.2016 18:42:51
 Author:	mr_br
*/


#include <Wire.h>

#include "RTClib.h"

RTC_DS1307 RTC;
int led = 13;           // ������������ ����� ����������� 13-� ������
int brightness = 0;    // ������� �����
int fadeAmount = 2;    // ��� ����������� �������
void setup() {

	Serial.begin(57600);

	Wire.begin();

	RTC.begin();

	while (!RTC.isrunning()) {

		Serial.println("RTC is NOT running!");
		brightness = 100;
		analogWrite(led, brightness);
		delay(1000);
		brightness = 0;
		analogWrite(led, brightness);

		// ������ ���� ������������ ��� ��������� ���� � ������� �����

		// RTC.adjust(DateTime(__DATE__, __TIME__));

	}

}

void loop() {
	// ������ �������
	DateTime now = RTC.now();
	if (now.hour() == 10 && now.minute() <= 3) {
		brightness = 1;
		if (now.minute() > 3)
			brightness = brightness + 1;
	 }
	// �������� �������	
	if (now.hour() >= 11 && now.hour() <= 13)
	{
		if (brightness <= 253)
			brightness = brightness + fadeAmount;
		else brightness = 255;
	}
	if (now.hour() >= 13 && now.hour() < 20)
	{
		brightness = 255;
	}
	if (now.hour() >= 20 && now.hour() <= 22) {

		if (brightness > 1)
			brightness = brightness - fadeAmount;
		else
			brightness = 1;

	}
	if (now.hour() >= 23 && now.minute() > 20)
		brightness = 0;
	Serial.print(now.hour(), DEC);
	Serial.print('-');
	Serial.println(now.minute(), DEC);
	Serial.println(brightness, DEC);
	analogWrite(led, brightness);
	delay(60000);

}