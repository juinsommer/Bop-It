 #include <hellodrum.h>
 #include <MIDI.h>
 MIDI_CREATE_DEFAULT_INSTANCE();

 int playCount = 0;
 
 HelloDrum kick(0);
 HelloDrum snare(1);
 HelloDrum hihat(2);
 HelloDrum tom1(3);
 HelloDrum tom2(4);
 HelloDrum crash(5);
 
void play_hiHat() {
    MIDI.sendNoteOn(46, 100, 10);
    MIDI.sendNoteOff(46, 0, 10);  
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
  delay(t);
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
}

void play_beat2(int t) {
  delay(t/4);
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
  
}

void play_beat3(int t) {
  delay(t/2);
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
}

 void setup()
 {
     MIDI.begin(10);
 }

 void loop()
 {
  if(playCount < 1) {
    
   for(int i = 0; i < 2; i++)
      play_beat1(500);

   delay(1000);

   for(int i = 0; i < 2; i++)
      play_beat2(500);

   delay(1000);

   for(int i = 0; i < 2; i++)
      play_beat3(500);

   playCount++;
  }

   //Sensing
   kick.singlePiezo();
   snare.singlePiezo();
   hihat.singlePiezo();
   tom1.singlePiezo();
   tom2.singlePiezo();
   crash.singlePiezo();
  
//   delay(500);
//   play_snare();
     
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
    if(tom1.hit == true)
    {
      MIDI.sendNoteOn(47, tom1.velocity, 10); //(note of close, velocity, channel)
      MIDI.sendNoteOff(47, 0, 10);  
    }
    //TOM2//
    if(tom2.hit == true)
    {
      MIDI.sendNoteOn(43, tom2.velocity, 10); //(note of close, velocity, channel)
      MIDI.sendNoteOff(43, 0, 10);  
    }
    //CRASH//
    if(crash.hit == true)
    {
      MIDI.sendNoteOn(49, crash.velocity, 10); //(note of close, velocity, channel)
      MIDI.sendNoteOff(49, 0, 10);  
    }
      
 }
