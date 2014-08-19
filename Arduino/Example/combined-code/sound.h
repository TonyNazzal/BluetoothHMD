// Reference:  This list was adapted from the table located here:
// 		http://www.phy.mtu.edu/~suits/notefreqs.html
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

const float  note_C0 = 16.35;  //C0
const float  note_Db0 = 17.32;  //C#0/Db0
const float  note_D0 = 18.35;  //D0
const float  note_Eb0 = 19.45;  //D#0/Eb0
const float  note_E0 = 20.6;  //E0
const float  note_F0 = 21.83;  //F0
const float  note_Gb0 = 23.12;  //F#0/Gb0
const float  note_G0 = 24.5;  //G0
const float  note_Ab0 = 25.96;  //G#0/Ab0
const float  note_A0 = 27.5;  //A0
const float  note_Bb0 = 29.14;  //A#0/Bb0
const float  note_B0 = 30.87;  //B0
const float  note_C1 = 32.7;  //C1
const float  note_Db1 = 34.65;  //C#1/Db1
const float  note_D1 = 36.71;  //D1
const float  note_Eb1 = 38.89;  //D#1/Eb1
const float  note_E1 = 41.2;  //E1
const float  note_F1 = 43.65;  //F1
const float  note_Gb1 = 46.25;  //F#1/Gb1
const float  note_G1 = 49;  //G1
const float  note_Ab1 = 51.91;  //G#1/Ab1
const float  note_A1 = 55;  //A1
const float  note_Bb1 = 58.27;  //A#1/Bb1
const float  note_B1 = 61.74;  //B1
const float  note_C2 = 65.41;  //C2 (Middle C)
const float  note_Db2 = 69.3;  //C#2/Db2
const float  note_D2 = 73.42;  //D2
const float  note_Eb2 = 77.78;  //D#2/Eb2
const float  note_E2 = 82.41;  //E2
const float  note_F2 = 87.31;  //F2
const float  note_Gb2 = 92.5;  //F#2/Gb2
const float  note_G2 = 98;  //G2
const float  note_Ab2 = 103.83;  //G#2/Ab2
const float  note_A2 = 110;  //A2
const float  note_Bb2 = 116.54;  //A#2/Bb2
const float  note_B2 = 123.47;  //B2
const float  note_C3 = 130.81;  //C3
const float  note_Db3 = 138.59;  //C#3/Db3
const float  note_D3 = 146.83;  //D3
const float  note_Eb3 = 155.56;  //D#3/Eb3
const float  note_E3 = 164.81;  //E3
const float  note_F3 = 174.61;  //F3
const float  note_Gb3 = 185;  //F#3/Gb3
const float  note_G3 = 196;  //G3
const float  note_Ab3 = 207.65;  //G#3/Ab3
const float  note_A3 = 220;  //A3
const float  note_Bb3 = 233.08;  //A#3/Bb3
const float  note_B3 = 246.94;  //B3
const float  note_C4 = 261.63;  //C4
const float  note_Db4 = 277.18;  //C#4/Db4
const float  note_D4 = 293.66;  //D4
const float  note_Eb4 = 311.13;  //D#4/Eb4
const float  note_E4 = 329.63;  //E4
const float  note_F4 = 349.23;  //F4
const float  note_Gb4 = 369.99;  //F#4/Gb4
const float  note_G4 = 392;  //G4
const float  note_Ab4 = 415.3;  //G#4/Ab4
const float  note_A4 = 440;  //A4
const float  note_Bb4 = 466.16;  //A#4/Bb4
const float  note_B4 = 493.88;  //B4
const float  note_C5 = 523.25;  //C5
const float  note_Db5 = 554.37;  //C#5/Db5
const float  note_D5 = 587.33;  //D5
const float  note_Eb5 = 622.25;  //D#5/Eb5
const float  note_E5 = 659.26;  //E5
const float  note_F5 = 698.46;  //F5
const float  note_Gb5 = 739.99;  //F#5/Gb5
const float  note_G5 = 783.99;  //G5
const float  note_Ab5 = 830.61;  //G#5/Ab5
const float  note_A5 = 880;  //A5
const float  note_Bb5 = 932.33;  //A#5/Bb5
const float  note_B5 = 987.77;  //B5
const float  note_C6 = 1046.5;  //C6
const float  note_Db6 = 1108.73;  //C#6/Db6
const float  note_D6 = 1174.66;  //D6
const float  note_Eb6 = 1244.51;  //D#6/Eb6
const float  note_E6 = 1318.51;  //E6
const float  note_F6 = 1396.91;  //F6
const float  note_Gb6 = 1479.98;  //F#6/Gb6
const float  note_G6 = 1567.98;  //G6
const float  note_Ab6 = 1661.22;  //G#6/Ab6
const float  note_A6 = 1760;  //A6
const float  note_Bb6 = 1864.66;  //A#6/Bb6
const float  note_B6 = 1975.53;  //B6
const float  note_C7 = 2093;  //C7
const float  note_Db7 = 2217.46;  //C#7/Db7
const float  note_D7 = 2349.32;  //D7
const float  note_Eb7 = 2489.02;  //D#7/Eb7
const float  note_E7 = 2637.02;  //E7
const float  note_F7 = 2793.83;  //F7
const float  note_Gb7 = 2959.96;  //F#7/Gb7
const float  note_G7 = 3135.96;  //G7
const float  note_Ab7 = 3322.44;  //G#7/Ab7
const float  note_A7 = 3520;  //A7
const float  note_Bb7 = 3729.31;  //A#7/Bb7
const float  note_B7 = 3951.07;  //B7
const float  note_C8 = 4186.01;  //C8
const float  note_Db8 = 4434.92;  //C#8/Db8
const float  note_D8 = 4698.64;  //D8
const float  note_Eb8 = 4978.03;  //D#8/Eb8
#define melodyPin 6 


