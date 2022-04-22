 #include <hellodrum.h>
 #include <MIDI.h>
 MIDI_CREATE_DEFAULT_INSTANCE();

 #define START_DELAY_DEFAULT    600
 
 int playCount = 0, start_delay = START_DELAY_DEFAULT;
 uint8_t score = 0;
 bool win_round = true, start_game = false, win_game = false;

 HelloDrum kick(0);
 HelloDrum snare(1);
 HelloDrum hihat(2);

void sense() {
  
   // args (sensitivity, threshold, scan time, mask time
   kick.singlePiezo();
   snare.singlePiezo();
   hihat.singlePiezo();

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

// checks if number of notes played by user matches number of notes in given beat
bool check_user(int t, int notes) {

  // variable to track elapsed time of user attempt
  unsigned long start_t = millis(), elapse_time = 0, measure = (4 * t);
  int noteCount = 0;

  // execute while the elapsed time does not exceed the time of the measure
  while(elapse_time <= measure) {

      // sense for user input, if user hits any pad, increment number of notes 
      sense();
     
      if (kick.hit == true)
      {
        MIDI.sendNoteOn(35, 100, 10); //(note, velocity, channel)
        MIDI.sendNoteOff(35, 0, 10);
        ++noteCount;
      }
    
      
      if (snare.hit == true)
      {
        MIDI.sendNoteOn(38, 80, 10);
        MIDI.sendNoteOff(38, 0, 10);
        ++noteCount;
      }
     
      if (hihat.hit == true)
      {
        MIDI.sendNoteOn(46, 80, 10);
        MIDI.sendNoteOff(46, 0, 10);
        ++noteCount;
      }
      
      unsigned long now_t = millis();
      elapse_time = now_t - start_t;
  }

  // if number of notes matches notes in beat, user wins round
  if(noteCount >= notes - 1 && noteCount <= notes + 1)
    return true;

  else
    return false;

}

// game logic function returning a bool. accepts an integer time value for delay/tempo 
// and 8 bit wide unsigned int for score count to be displayed to 7 segment displays
bool beat_off(int t) {
  
  long beatNumber = random(1,4); // generate random number [1, 3]
  int notes = 0; // variable to track number of notes user plays
  bool success;

 // random number generated will determine which beat to play 
  switch(beatNumber) {
    case 1: 
      play_beat1(t);
      notes = 9; // total number of notes in beat
      break;
      
    case 2:
      play_beat2(t);
      notes = 16;
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
    score = (score + 1) & 0xFF;
    displayWrite(score);
    digitalWrite(2, HIGH); // power success indicator LED
    delay(2000); // leave on for 2 seconds
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
  int pin, pin2, a, b;
  
  if(value <= 9) {
               
     for(pin = 5, a = 0; pin <= 8; pin++, a++)
        digitalWrite(pin, bitRead(value, a));


     for(pin2 = 12, b = 0; pin2 >= 9; pin2--, b++) {
        digitalWrite(pin2, bitRead(0, b));
         
     }
  }

  else if(value >= 10) {
    int ones, tens;
     ones = value % 10;
     tens = (value / 10) % 10;
        
     for(pin = 5, a = 0; pin <= 8; pin++, a++)
        digitalWrite(pin, bitRead(ones, a));
      
     for(pin2 = 12, b = 0; pin2 >= 9; pin2--, b++)
        digitalWrite(pin2, bitRead(tens, b));
  }
}

// function to read if user has started game by hitting snare 5 times within 4 seconds
// returns true if 5 snare hits were detected, else false
 bool check_start() {
  
     int count = 0; // tracks how many times pad was hit
     unsigned long start_t = millis(), elapse_time = 0; // track time
     

     // check user input for 4 seconds
     while(elapse_time <= 3000) {

         sense();
        
         if (kick.hit == true)
        {
          MIDI.sendNoteOn(35, 120, 10); //(note, velocity, channel)
          MIDI.sendNoteOff(35, 0, 10);
        }
      
        if (snare.hit == true)
        {
          MIDI.sendNoteOn(38, 80, 10); //(note, velocity, channel)
          MIDI.sendNoteOff(38, 0, 10);
          ++count;
        }
       
        if (hihat.hit == true)
        {
          MIDI.sendNoteOn(46, 80, 10); //(note of close, velocity, channel)
          MIDI.sendNoteOff(46, 0, 10);  
        }

        unsigned long now_t = millis();
        elapse_time = now_t - start_t;
        
     } // end while
        
    if(count == 5) return true; 

    else return false;
 }

 
 void setup()
 {
     randomSeed(0);
     MIDI.begin(10);

     // setup for BCD converter pins
     for(int i = 5; i <= 12; i++)
        pinMode(i, OUTPUT);
     
     // setup for LED indicators
     pinMode(2, OUTPUT);
     pinMode(3, OUTPUT);
 }   
  
 void loop()
 {
    
    sense(); // sense piezo inputs

    //Sending MIDI signals.
    
    if (kick.hit == true)
    {
      MIDI.sendNoteOn(35, 100, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(35, 0, 10);
    }
  
    //SNARE//
    if (snare.hit == true)
    {
      MIDI.sendNoteOn(38, 80, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(38, 0, 10);

    }
    //HIHAT
    if (hihat.hit == true)
    {
      MIDI.sendNoteOn(46, 80, 10); //(note of close, velocity, channel)
      MIDI.sendNoteOff(46, 0, 10);  
    }
  

    start_game = (start_game == false) ? check_start() : true;
    
    // if start has been activated
    if(start_game) {
        // game logic 
        if(playCount < 100 && win_round) {
           
           win_round = beat_off(start_delay);
           start_delay -= 4; // increase tempo by decreasing delay
           playCount++;

        }

        // if user wins game or loses reset all values
        if(playCount == 99 || win_round == false) {
          start_game = false;
          start_delay = START_DELAY_DEFAULT;
          playCount = 0;
          score = 0;
          
        }
    }
     
 }
