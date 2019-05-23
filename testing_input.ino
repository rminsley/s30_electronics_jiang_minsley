//Simple Audio Out
//by Amanda Ghassaei
//https://www.instructables.com/id/Arduino-Vocal-Effects-Box/
//July 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

int incomingAudio;

void setup(){
  for (byte i=0;i<8;i++){
    pinMode(i,OUTPUT);//set digital pins 0-7 as outputs
  }
  pinMode(A0,INPUT);
}

void loop(){
  incomingAudio = analogRead(A0);//read input from A0
  incomingAudio = incomingAudio/4;//scale from 10 bit to 8 bit
  PORTD = incomingAudio;//send out DAC
}
