 #include <hellodrum.h>
 #include <MIDI.h>
 MIDI_CREATE_DEFAULT_INSTANCE();

 int playCount = 0, start_delay = 600;
 static uint8_t score = 0;
 bool win = true;
 
 HelloDrum kick(0);
 HelloDrum snare(1);
 HelloDrum hihat(2);
// HelloDrum tom1(3);
// HelloDrum tom2(4);
// HelloDrum crash(5);

void sense() {
   kick.singlePiezo();
   snare.singlePiezo();
   hihat.singlePiezo();
//   tom1.singlePiezo();
//   tom2.singlePiezo();
//   crash.singlePiezo();
}

void play_hiHat() {
    MIDI.sendNoteOn(46, 100, 10);
    MIDI.sendNoteOff(46, 0, 10);  
}

void play_hiHatClose() {
    MIDI.sendNoteOn(42, 100, 10);
    MIDI.sendNoteOff(42, 0, 10);
}

void play_kick() {
    MIDI.sendNoteOn(35, 100, 10);
    MIDI.sendNoteOff(35, 0, 10);
}

void play_snare() {
    MIDI.sendNoteOn(38, 60, 10);
    MIDI.sendNoteOff(38, 0, 10);
}

void play_crash() {
  MIDI.sendNoteOn(49, 120, 10);
  MIDI.sendNoteOff(49, 0, 10);  
}

void play_beat1(int t) {
  play_crash();
  play_kick();
  delay(t);
  play_hiHat();
  play_snare();
  delay(t);
  play_hiHat();
  play_kick();
  delay(t/2);
  play_kick();
  delay(t/2);
  play_hiHat();
  play_snare();
  delay(t);
}

void play_beat2(int t) {
  play_crash();
  play_kick();
  delay(t/2);
  play_hiHat();
  play_kick();
  delay(t/2);
  play_hiHat();
  play_snare();
  delay(t/2);
  play_hiHat();
  delay(t/4);
  play_snare();
  delay(t/4);
  play_hiHat();
  delay(t/4);
  play_snare();
  delay(t/4);
  play_hiHat();
  play_kick();
  delay(t/2);
  play_hiHat();
  play_snare();
  delay(t/2);
  play_hiHat();
  delay(t/4);
  play_snare();
  delay(t/4);
}

void play_beat3(int t) {
  play_crash();
  play_kick();
  delay(t/2);
  play_kick();
  delay(t/2);
  play_hiHat();
  play_snare();
  delay(t/2);
  play_snare();
  delay(t/2);
  play_hiHat();
  play_kick();
  delay(t/2);
  play_kick();
  delay(t/2);
  play_hiHat();
  play_snare();
  delay(t/2);
  play_snare();
  delay(t/2);

}

bool check_user(int t, int notes) {
  unsigned long start_t = millis(), elapse_time = 0, measure = (4 * t);
  int noteCount = 0;
  
  while(elapse_time <= measure) {

      sense();
     
      if (kick.hit == true)
      {
        MIDI.sendNoteOn(35, kick.velocity, 10); //(note, velocity, channel)
        MIDI.sendNoteOff(35, 0, 10);
        noteCount++;
      }
    
      
      if (snare.hit == true)
      {
        MIDI.sendNoteOn(38, snare.velocity, 10); //(note, velocity, channel)
        MIDI.sendNoteOff(38, 0, 10);
        noteCount++;
      }
     
      if (hihat.hit == true)
      {
        MIDI.sendNoteOn(46, hihat.velocity, 10); //(note of close, velocity, channel)
        MIDI.sendNoteOff(46, 0, 10);
        noteCount++;
      }
//      
//      if(crash.hit == true)
//      {
//        MIDI.sendNoteOn(49, crash.velocity, 10); //(note of close, velocity, channel)
//        MIDI.sendNoteOff(49, 0, 10);  
//        noteCount++;
//      }
      
      unsigned long now_t = millis();
      elapse_time = now_t - start_t;
  }
  
  if(noteCount > 0)
    return true;

  else
    return false;

}

bool beat_off(int t, uint8_t s) {
  long beatNumber = random(1,4); // generate random number [1, 3]
  int notes = 0;
  bool success;
  
  switch(beatNumber) {
    case 1: 
      play_beat1(t);
      notes = 9;
      break;
      
    case 2:
      play_beat2(t);
      notes = 1;
      break;
      
    case 3:
      play_beat3(t);
      notes = 12;
      break; 
  }

  // count off to start
  play_hiHatClose();
  delay(t);
  play_hiHatClose();
  delay(t);
  play_hiHatClose();
  delay(t);
  play_hiHatClose();
  delay(t);

  bool flag = check_user(t, notes);

  // if user succeeds
  if(flag) {
    digitalWrite(2, HIGH); // power success indicator LED
    ++score; // increment score
    displayWrite(s); // display score to 7 segment displays
    delay(2000);
    digitalWrite(2, LOW); // turn off LED
    success = true; 
  }
  
  else { 
    
    digitalWrite(3, HIGH); // power fail indicator LED
    delay(3000); // leave on for 3 seconds
    digitalWrite(3, LOW); // turn off LED
    
    success = false;
  }

  return success;
}

// function to display score to 7 segment displays
void displayWrite(uint8_t value) {

  if(value < 10) {
     digitalWrite(5, bitRead(value, 0));  // BCD LSB
     digitalWrite(6, bitRead(value, 1));
     digitalWrite(7, bitRead(value, 2));
     digitalWrite(8, bitRead(value, 3));  // BCD MSB

     // display 0 for single digit score
     digitalWrite(9, bitRead(0, 0));  // BCD LSB
     digitalWrite(10, bitRead(0, 1));
     digitalWrite(11, bitRead(0, 2));
     digitalWrite(12, bitRead(0, 3));  // BCD MSB
  }

  else {
    
     digitalWrite(5, bitRead(value, 0));  // BCD LSB
     digitalWrite(6, bitRead(value, 1));
     digitalWrite(7, bitRead(value, 2));
     digitalWrite(8, bitRead(value, 3));  
     digitalWrite(9, bitRead(value, 4));
     digitalWrite(10, bitRead(value, 5));
     digitalWrite(11, bitRead(value, 6));
     digitalWrite(12, bitRead(value, 7));  // BCD MSB

  }
}
 

 void setup()
 {
     randomSeed(1112112112);
     MIDI.begin(10);

     // setup for BCD converter pins
     pinMode(5, OUTPUT);
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT);
     pinMode(8, OUTPUT);
     pinMode(9, OUTPUT);
     pinMode(10, OUTPUT);
     pinMode(11, OUTPUT);
     pinMode(12, OUTPUT);

     // setup for LED indicators
     pinMode(2, OUTPUT);
     pinMode(3, OUTPUT);

     // setup for start button
     pinMode(4, INPUT);

     
 void loop()
 {
    
    sense();

     //Sending MIDI signals.
    //KICK//
    if (kick.hit == true)
    {
      MIDI.sendNoteOn(35, kick.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(35, 0, 10);
    }
  
    //SNARE//
    if (snare.hit == true)
    {
      MIDI.sendNoteOn(38, snare.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(38, 0, 10);
    }
    //HIHAT//
    if (hihat.hit == true)
    {
      MIDI.sendNoteOn(46, hihat.velocity, 10); //(note of close, velocity, channel)
      MIDI.sendNoteOff(46, 0, 10);  
    }
    //TOM1//
//    if(tom1.hit == true)
//    {
//      MIDI.sendNoteOn(47, tom1.velocity, 10); //(note of close, velocity, channel)
//      MIDI.sendNoteOff(47, 0, 10);  
//    }
//    //TOM2//
//    if(tom2.hit == true)
//    {
//      MIDI.sendNoteOn(43, tom2.velocity, 10); //(note of close, velocity, channel)
//      MIDI.sendNoteOff(43, 0, 10);  
//    }
//    //CRASH//
//    if(crash.hit == true)
//    {
//      MIDI.sendNoteOn(49, crash.velocity, 10); //(note of close, velocity, channel)
//      MIDI.sendNoteOff(49, 0, 10);  
//    }
//    
    if(digitalRead(4) == LOW) {
        // game logic 
        if(playCount < 100 && win) {
           win = beat_off(start_delay, score);
           start_delay -= 4;
           playCount++;
        }
    }
     
 }
