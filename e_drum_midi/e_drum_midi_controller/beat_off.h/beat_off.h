#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

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