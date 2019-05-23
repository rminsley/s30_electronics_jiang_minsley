# Arduino Vocal Effects Box

## Description 
The Arduino Vocal Effects Box is a real-time digital signal processor that distorts audio signals using an Arduino. It samples audio from a microphone, the audio signal is then manipulated digitally by the Arduino, the signal is then converted to analog, and finally output through a speaker. The Arduino code used used to distort sound relies on a technique called granular synthesis. The code programs the Arduino to divide up incoming sound into small sized samples (grains) that it can then store and manipulate.  Our voice box has the ability to change audio frequency, the grain size, and the wet/dry signal. We used the instructions provided by amandaghassaei at https://www.instructables.com/id/Arduino-Vocal-Effects-Box/

## Parts
Amount | Part
------------ | -------------
1 | Arduino Uno REV 3
2 | 100 Ω 1/4W Resistor
7 | 10 kΩ 1/4-Watt Resistor 
9 | 20 kΩ 1/4-Watt Resistor
1 | 1 kΩ 1/4-Watt Resistor 
3 | 100 kΩ 1/4-Watt Resistor
1 | 2 kΩ 1/4-Watt Resistor
1 | 10 kΩ Audio Control Potentiometer
2 | 10 kΩ Linear-Taper Potentiometer
2 | 1 MΩ Linear-Taper Potentiometer
1 | 1 MΩ Logarithmic Potentiometer
1 | 10 μF electrolytic capacitor
1 | 47 nF capacitor
3 | 0.1 μF capacitor
1 | TL082 Wide Dual JFET Input Op Amp
2 | TS922IDT Dual Op Amp
2 | Socket Adapter SOIC to 8DIP (to put the amp on breadboard)
2 | 9V Alkaline Battery
2 | Heavy-Duty 9V Snap Connectors
1 | SPST Switch
1 | DPDT Switch
2 | 5mm LED
1 | Microphone that can be read on Oscilloscope 
1 | 3W 16Ω Speaker
1 | Breadboard with power strips

### Budget
Total Cost: ~$100  
Cost exluding parts found in lab (i.e. resistors, capacitors, Arduino, breadboard, microphone and speaker): ~$40

## Assembly Description 
  The project can be broken down into three parts: the audio output, the audio input, the distortion control. We first built the audio output (See circuit diagram 1). For part 1, we were mostly able to construct the circuit with the provided circuit diagram from the instructable page. The audio output comes from the Arduino digital output pins 0 to 7. From these pins, the signal goes through a 8-bit R2R digital to analog converter (DAC). The R2R DAC is composed of a resistor ladder of seven 10 kΩ resistors and nine 20 kΩ resistors. After constructing the DAC we tested the DAC output using the code from step 6 of the instructables page (see testing_dac.ino)



The signal then goes through to two TS922IDT op-amps in parallel that act as voltage followers. Voltage followers protect the DAC from signal voltages from the speaker load. From the op-amps the signal then goes through a low-pass filter and a 10 kΩ logarithmic  potentiometer that acts as the output volume controller. We used a 0.01 μF capacitor and a 1 kΩ resistor to make our low-pass filter that roughly filters out frequencies above 20 kHz. 
	A major issue that we encountered was figuring out the orientation of the op-amp pins and mounting the op-amps onto socket adapters so that they could be plugged into the bread-board. The op-amps that we bought on Digi-Key did not have an dot indicator for the location of pin 1. We contacted the manufacturer of the op-amps STMicroelectronics, and they proved to be not very helpful. We found through online searches one of the edges of the amp has a slight inclination compared to the other sides that at right angles. When the inclined angle is pointing towards you, pin 1 is located in the lower left corner. The op-amps are incredibly small and soldering them to their mounts proved to be difficult. We were able to solder two out of the three amps but unfortunately in figuring out how to solder first amp we broke the socket adapter. We decided to replace this amp entirely with a comparable amp that is premade with an adapter that fits the bread-board. 
	
After completing the output circuit, we then moved on to the input circuit (see circuit diagram 2). The input circuit consists of microphone connections that feed in audio signals to a TL082 amplifier and the signal is then offsetted by 2.5V using the battery. The circuit also includes a potentiometer that adjust the amplitude of the incoming signal. After this, the signal is sent to the Arduino analog pin A0.
	We first built the DC offset. The DC offset consist of two capacitors and two 100 kΩ resistor. But since we were waiting for the op-amp to arrive, we used the amplifier that came with our microphone to boost the signal to the -2.5V - 2.5V range, and built ourselves a separate DC offset using a 9V battery and a voltage divider. In that way, we could directly input our signal from this seperate circuit so that we could test the output module. We simply tested that the input signal can be corrected reproduced by the Arduino and the voltage followers were in the correct position. The code we used comes from the instructables page step 26 (see testing_input.ino).
	After we did the test, we built the input module without the op-amp as it did not arrive until the third to last day of project work. The diagram were confusing to us. The main problem comes from the location of the ground. Notice in the circuit diagram, the battery is seperated, but in fact they are controlled using a DPDT switch. And since the amp requires a +9V -9V input, we must connect the positive side of one of the battery to the Arduino GND, creating the -9V supply. Later when we got the op-amp, we managed to input our microphone signal directly into the op-amp we have without using the amplifier that came with the microphone. In the instrutables page, for the parts list, she listed a 50 kΩ linear potentiometer, where in fact she used a 10 kΩ linear potentiometer.
	
We then moved on to build the distortion control. In this part, the circuit diagram is fairly straightforward (see Circuit_diagram_3). There are three 1 MΩ potentiometers, two linear and one logarithmic. By changing the resistance, we change the discharge time for the RC circuit, which is measured by the Arduino and from this we adjust the pitch, dry/wet, and grain size of the output signal. In the instructables page, she used a potentiometer with SPST switch, however, we did not have that, and we simply substituted it using a SPST switch connected in series with 10 kΩ linear potentiometer.

After the build is complete, we used the final code provided by the instrutables page, which is a code that contains high sample rate input, and uses granular synthesis to output a distorted audio that is controled by the distortion control. The code can be found step 36 of the instructable page, and is uploaded as finalcode.ino .
