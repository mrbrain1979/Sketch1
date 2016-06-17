/*
 Name:		Sketch1.ino
 Created:	17.06.2016 18:42:51
 Author:	mr_br
*/


#include <Wire.h>

#include "RTClib.h"

RTC_DS1307 RTC;
int led = 13;           // —ветодиодна€ лента управл€етс€ 13-й ножкой
int brightness = 0;    // яркость ленты
int fadeAmount = 2;    // Ўаг регулировки €ркости
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

		// строка ниже используетс€ дл€ настройки даты и времени часов

		// RTC.adjust(DateTime(__DATE__, __TIME__));

	}

}

void loop() {
	// ранний рассвет
	DateTime now = RTC.now();
	if (now.hour() == 10 && now.minute() <= 3) {
		brightness = 1;
		if (now.minute() > 3)
			brightness = brightness + 1;
	 }
	// основной рассвет	
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