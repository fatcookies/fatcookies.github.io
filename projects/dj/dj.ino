// Based on http://www.instructables.com/id/Easy-3-Pot-Potentiometer-Arduino-Uno-Effects-Midi-/step4/The-Code/

// Current and previous value of all three potentionmeters
int pots[3][2] = { {0,0}, {0,0}, {0,0} };

// All button states (1 = has been pressed down, 0 = released/not pressed)
int state[6] = {0,0,0,0,0,0};

void setup() {
   Serial.begin(57600); // Set the speed of the midi port to the same as we will be using in the Hairless Midi software 
   digitalWrite(3,HIGH);
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(6,HIGH);
}

void loop() {
  // Left bass
  handlePot(3,1);

  // Right bass
  handlePot(6,2);

  // Crossfader
  handlePot(5,3);

  //left white
  handleButt(9,0);
  //left red
  handleButt(8,1);
  //left blue
  handleButt(7,2);

  // right blue
  handleButt(12,3);
  //right red
  handleButt(10,4);
  //right white
  handleButt(11,5);
    
  delay(10); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.
}

// Sends a MIDI message to control channel "number" on any pot change on physical "pin"
inline void handlePot(int pin, int number) {
     pots[number-1][0] = (1023-analogRead(pin))/8;   // inverse value and decrese
      if (pots[number-1][0] != pots[number-1][1]) { // Only send if change
          MIDImessage(176,number,pots[number-1][0]); // 176 = CC command (channel 1 control change), 1 = Which Control, val = value read from Potentionmeter 1
      }         
      pots[number-1][1] = pots[number-1][0];
}

// Sends a MIDI message to "number" for any full press on physical "pin"
inline void handleButt(int pin, int number) {
  if (digitalRead(pin) == HIGH) {
    state[number] = 1;

   } else {
    if(state[number] == 1) {
      MIDImessage(144,number,127);
      state[number] = 0;
    }
   }
}

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}
