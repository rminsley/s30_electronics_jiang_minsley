//63Hz sine wave
//by Amanda Ghassaei 2012
//https://www.instructables.com/id/Arduino-Vocal-Effects-Box/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//sends 63Hz sine wave to arduino PORTD DAC
float t = 0;

void setup() {
  //set port/pin  mode. see http://www.arduino.cc/en/Reference/PortManipulation for more info
  DDRD = 0xFF;//port d (digital pins 0-7) all outputs
  
  cli();//stop interrupts

  //set timer2 interrupt at 40kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 40khz increments
  OCR2A = 49;// = (16*10^6) / (8*40000)-1
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS11 bit for 8 prescaler
  TCCR2B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts
}

ISR(TIMER2_COMPA_vect) {
  //increment t
  t+=1;
  if (t==628){//40kHz/628 =~ 63Hz
    t=0;
  }
}


void loop(){
  //sine wave of frequency ~63Hz
  //send sine values to PORTD between 0 and 255
  PORTD=byte(127+127*sin(t/100));
}
