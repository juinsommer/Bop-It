 #include <hellodrum.h>
 #include <MIDI.h>
 MIDI_CREATE_DEFAULT_INSTANCE();

 //Please name your piezo.
 //The piezo named snare is connected to the A0 pin
 HelloDrum snare(0);

 //Setting
 byte SNARE[6] = {
   80, //sensitivity 
   10, //threshold
   20, //scantime
   20, //masktime
   38, //note
   1   //curve type
 }; 

 void setup()
 {
     MIDI.begin(10);
     snare.setCurve(SNARE[5]); //Set velocity curve 
 }

 void loop()
 {
     //Sensing
     snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]); //(sensitivity, threshold, scantime, masktime)

     //Sending MIDI signals
     if (snare.hit == true) {
         MIDI.sendNoteOn(SNARE[4], snare.velocity, 10);  //(note, velocity, channel)
         MIDI.sendNoteOff(SNARE[4], 0, 10);
     }
 }
