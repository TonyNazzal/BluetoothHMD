/*
The MIT License (MIT)

Copyright (c) 2014 (https://hackaday.io/project/2068-%2460-bluetooth-head-mounted-display.-)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <SoftwareSerial.h>// import the serial library
#include <avr/io.h>
#include "display.h"
#include "sound.h"
SoftwareSerial MySerial(11, 10);
#define OLED_address  0x3C
char rx_byte;
unsigned char buff[8][17];
int offset = 0;
int speakerPin = 6;

void setup() {
	i2c_init();
	init_OLED();
	//RGB LED
	pinMode(3, OUTPUT); 
	pinMode(4, OUTPUT); 
	pinMode(5, OUTPUT);
	//SPEAKER 
	pinMode(speakerPin, OUTPUT);
	//TURN OFF LEDS
	digitalWrite(3, HIGH);
	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	//start bluetooth serial
	MySerial.begin(9600);
	noTone(6);
	clear_display();
	delay(50);

	sendcommand(0x20);            //Set Memory Addressing Mode
	sendcommand(0x02);            //Set Memory Addressing Mode ab Page addressing mode(RESET)  
	sendcommand(0xa6);            //Set Normal Display (default)
	delay(10);
    //init buffers
    int x = 0;
    for(;x<8;x++)
      buff[x][0] = '\n';

}

void loop() {

	if(MySerial.available()){
		int x = 0;
		char bufferc[255];
		while(1) {

			int c = MySerial.read();
			if(-1 == c)
				break;
			bufferc[x++] = c;
			tone(6, c);
			digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
			delay(50);
			digitalWrite(4, HIGH);
			delay(20);
			noTone(6);
		}
		bufferc[x] = NULL;

		//write_to_display(bufferc);
		if(!do_cmd(bufferc))
                  write_to_display2(bufferc);
                delay(200);

	}
	delay(20);

}

int do_cmd(char *cmd)
{
  int len = strlen(cmd);
  char *command;
  char *icmd;
  if(len > 0 && len > 4 && '*' == cmd[0] && '*' == cmd[1] && '*' == cmd[2] && '*' == cmd[3])
  {
    command = cmd+4;
    //RGB LED Commands
    if(strstr(command,"LED"))
   {
     icmd = command+3;
     switch(atoi(icmd))
     {
      //Turn on LEDS
      case 1:
      digitalWrite(3, LOW);
      break;
      case 2:
      digitalWrite(4, LOW);
      break;
      case 3:
      digitalWrite(5, LOW);
      break;
      //Turn off LEDS      
      case 4:
      digitalWrite(3, HIGH);
      break;
      
      case 5:
      digitalWrite(4, HIGH);
      break;
      
      case 6:
      digitalWrite(5, HIGH);
      break;
     
     }
     return 1;
     //Clear screen
   }else if(strstr(command, "CLR"))
    {
      clear_display();
      return 1;
    }
    //Sound commands
  else if(strstr(command, "SND"))
  {
     icmd = command+3;
     switch(atoi(icmd))
    {
    case 1:
    r2D2();
    break;
    case 2:
    closeEncounters();
    break;
    case 3:
    ariel();
    break;
    }
    return 1;
  }else 
  
  return 0;
  }
  return 0;
}

void write_to_display2(char * str)

{
  	int len = strlen(str);
	int x = 0;
        for(;x<len;x+=16)
        {
          memcpy(buff[offset],str+x,16);
          buff[offset][16] = '\0';

          if(7 == offset)
          {
            shift_buffers();
	    write_reverse_string((char *)buff[offset], offset);
          }else
            write_reverse_string((char *)buff[offset++], offset);
        }
              
}
void shift_buffers()
{

  int x =0;
  for(;x<8;x++)
  {
    memcpy(buff[x],buff[x+1], 16);
    write_reverse_string((char *)buff[x], x);
  
  }

}
void write_reverse_string(char *str, int col)
{
  int len = strlen(str);
  int x = 0, pos = 15;
  unsigned char temp[2] = {'\0','\0'};
  
  for(;x<len;x++, pos--)
  {
      temp[0] = str[x];
      setXY(col,pos);
      sendReverseStr(temp);
  }
}

//==========================================================//
void sendcommand(unsigned char com)
{
	i2c_OLED_send_cmd(com);  

	//Wire.beginTransmission(OLED_address);     //begin transmitting
	//Wire.write(0x80);                          //command mode
	//Wire.write(com);
	//Wire.endTransmission();                    // stop transmitting

}

//==========================================================//
void clear_display(void)
{
	unsigned char i,k;
	for(k=0;k<8;k++)
	{	
		setXY(k,0);    
		{
			for(i=0;i<128;i++)     //clear all COL
			{
				SendChar(0);         //clear all COL
				//delay(10);
			}
		}
	}
}

//==========================================================//
void SendChar(unsigned char data)
{
	i2c_OLED_send_byte(data);
	/*
	   Wire.beginTransmission(OLED_address); // begin transmitting
	   Wire.write(0x40);//data mode
	   Wire.write(data);
	   Wire.endTransmission();    // stop transmitting
	 */
}

//==========================================================//
void setXY(unsigned char row,unsigned char col)
{
	sendcommand(0xb0+row);                //set page address
	sendcommand(0x00+(8*col&0x0f));       //set low col address
	sendcommand(0x10+((8*col>>4)&0x0f));  //set high col address
}


//==========================================================//
void sendStr(unsigned char *string)
{
	sendReverseStr(string);
	return;
	unsigned char i=0;
	//setXY(0,0);    
	while(*string)
	{
		for(i=0;i<8;i++)
		{
			SendChar(myFont[*string-0x20][i]);

			// SendChar(*string);
			delay(2);
		}
		*string++;
	}
}

void sendReverseStr(unsigned char *string)
{
	unsigned char i=0;
	//setXY(0,0);    
	while(*string)
	{
		for(i=0;i<8;i++)
		{
			SendChar(myFont[*string-0x20][7-i]);

			// SendChar(*string);
			delay(2);
		}
		*string++;
	}
}
//==========================================================//
void init_OLED(void)
{
	i2c_OLED_init();

}
//WWW.WIDE.HK

void  i2c_OLED_init(void){
	i2c_OLED_send_cmd(0xae);    //display off
	i2c_OLED_send_cmd(0x2e);    //deactivate scrolling
	i2c_OLED_send_cmd(0xa4);          //SET All pixels OFF
	//  i2c_OLED_send_cmd(0xa5);            //SET ALL pixels ON
	delay(50);
	i2c_OLED_send_cmd(0x20);            //Set Memory Addressing Mode
	i2c_OLED_send_cmd(0x02);            //Set Memory Addressing Mode to Page addressing mode(RESET)
	//  i2c_OLED_send_cmd(0xa0);      //colum address 0 mapped to SEG0 (POR)*** wires at bottom
	i2c_OLED_send_cmd(0xa1);    //colum address 127 mapped to SEG0 (POR) ** wires at top of board
	//  i2c_OLED_send_cmd(0xC0);            // Scan from Right to Left (POR)         *** wires at bottom
	i2c_OLED_send_cmd(0xC8);          // Scan from Left to Right               ** wires at top
	i2c_OLED_send_cmd(0xa6);            // Set WHITE chars on BLACK backround

	//  i2c_OLED_send_cmd(0xa7);            // Set BLACK chars on WHITE backround
	i2c_OLED_send_cmd(0x81);            // Setup CONTRAST CONTROL, following byte is the contrast Value
	i2c_OLED_send_cmd(0xaf);            // contrast value between 1 ( == dull) to 256 ( == bright)
	delay(20);
	i2c_OLED_send_cmd(0xaf);          //display on
	delay(20);
}

// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************

static uint32_t neutralizeTime = 0;
static int16_t  i2c_errors_count = 0;

#define I2C_SPEED 100000L     //100kHz normal mode, this value must be used for a genuine WMP

#define I2C_PULLUPS_ENABLE         PORTC |= 1<<4; PORTC |= 1<<5;   // PIN A4&A5 (SDA&SCL)
#define I2C_PULLUPS_DISABLE        PORTC &= ~(1<<4); PORTC &= ~(1<<5);

void i2c_init(void) {
#if defined(INTERNAL_I2C_PULLUPS)
	I2C_PULLUPS_ENABLE
#else
		I2C_PULLUPS_DISABLE
#endif
		TWSR = 0;                                    // no prescaler => prescaler = 1
	TWBR = ((F_CPU / I2C_SPEED) - 16) / 2;   // change the I2C clock rate
	TWCR = 1<<TWEN;                              // enable twi module, no interrupt
}

void i2c_rep_start(uint8_t address) {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; // send REPEAT START condition
	waitTransmissionI2C();                       // wait until transmission completed
	TWDR = address;                              // send device address
	TWCR = (1<<TWINT) | (1<<TWEN);
	waitTransmissionI2C();                       // wail until transmission completed
}

void i2c_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	//  while(TWCR & (1<<TWSTO));                // <- can produce a blocking state with some WMP clones
}

void i2c_write(uint8_t data ) {	
	TWDR = data;                                 // send data to the previously addressed device
	TWCR = (1<<TWINT) | (1<<TWEN);
	waitTransmissionI2C();
}

uint8_t i2c_read(uint8_t ack) {
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);
	waitTransmissionI2C();
	uint8_t r = TWDR;
	if (!ack) i2c_stop();
	return r;
}

uint8_t i2c_readAck() {
	return i2c_read(1);
}

uint8_t i2c_readNak(void) {
	return i2c_read(0);
}

void waitTransmissionI2C() {
	uint16_t count = 255;
	while (!(TWCR & (1<<TWINT))) {
		count--;
		if (count==0) {              //we are in a blocking state => we don't insist
			TWCR = 0;                  //and we force a reset on TWINT register
			neutralizeTime = micros(); //we take a timestamp here to neutralize the value during a short delay
			i2c_errors_count++;
			break;
		}
	}
}

size_t i2c_read_to_buf(uint8_t add, void *buf, size_t size) {
	i2c_rep_start((add<<1) | 1);	// I2C read direction
	size_t bytes_read = 0;
	uint8_t *b = (uint8_t*)buf;
	while (size--) {
		/* acknowledge all but the final byte */
		*b++ = i2c_read(size > 0);
		/* TODO catch I2C errors here and abort */
		bytes_read++;
	}
	return bytes_read;
}

size_t i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size) {
	i2c_rep_start(add<<1); // I2C write direction
	i2c_write(reg);        // register selection
	return i2c_read_to_buf(add, buf, size);
}

/* transform a series of bytes from big endian to little
   endian and vice versa. */
void swap_endianness(void *buf, size_t size) {
	/* we swap in-place, so we only have to
	 * place _one_ element on a temporary tray
	 */
	uint8_t tray;
	uint8_t *from;
	uint8_t *to;
	/* keep swapping until the pointers have assed each other */
	for (from = (uint8_t*)buf, to = &from[size-1]; from < to; from++, to--) {
		tray = *from;
		*from = *to;
		*to = tray;
	}
}

void i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val) {
	i2c_rep_start(add<<1); // I2C write direction
	i2c_write(reg);        // register selection
	i2c_write(val);        // value to write in register
	i2c_stop();
}


void i2c_OLED_send_cmd(uint8_t command) {
	TWBR = ((F_CPU / 400000L) - 16) / 2; // change the I2C clock rate
	i2c_writeReg(OLED_address, 0x80, (uint8_t)command);
}

void i2c_OLED_send_byte(uint8_t val) {
	TWBR = ((F_CPU / 400000L) - 16) / 2; // change the I2C clock rate
	i2c_writeReg(OLED_address, 0x40, (uint8_t)val);
}

////////////////////////SOUND RELATED

void beep (int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     
     
void scale() 
{    
          beep(speakerPin, note_C7,500); //C: play the note C for 500ms 
          beep(speakerPin, note_D7,500); //D 
          beep(speakerPin, note_E7,500); //E 
          beep(speakerPin, note_F7,500); //F 
          beep(speakerPin, note_G7,500); //G 
          beep(speakerPin, note_A7,500); //A 
          beep(speakerPin, note_B7,500); //B 
          beep(speakerPin, note_C8,500); //C 
}  

void r2D2(){
          beep(speakerPin, note_A7,100); //A 
          beep(speakerPin, note_G7,100); //G 
          beep(speakerPin, note_E7,100); //E 
          beep(speakerPin, note_C7,100); //C
          beep(speakerPin, note_D7,100); //D 
          beep(speakerPin, note_B7,100); //B 
          beep(speakerPin, note_F7,100); //F 
          beep(speakerPin, note_C8,100); //C 
          beep(speakerPin, note_A7,100); //A 
          beep(speakerPin, note_G7,100); //G 
          beep(speakerPin, note_E7,100); //E 
          beep(speakerPin, note_C7,100); //C
          beep(speakerPin, note_D7,100); //D 
          beep(speakerPin, note_B7,100); //B 
          beep(speakerPin, note_F7,100); //F 
          beep(speakerPin, note_C8,100); //C 
}

void closeEncounters() {
          beep(speakerPin, note_Bb5,300); //B b
          delay(50);
          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_Ab5,300); //A b
          delay(50);
          beep(speakerPin, note_Ab4,300); //A b
          delay(50);
          beep(speakerPin, note_Eb5,500); //E b   
          delay(500);     
          
          beep(speakerPin, note_Bb4,300); //B b
          delay(100);
          beep(speakerPin, note_C5,300); //C
          delay(100);
          beep(speakerPin, note_Ab4,300); //A b
          delay(100);
          beep(speakerPin, note_Ab3,300); //A b
          delay(100);
          beep(speakerPin, note_Eb4,500); //E b   
          delay(500);  
          
          beep(speakerPin, note_Bb3,300); //B b
          delay(200);
          beep(speakerPin, note_C4,300); //C
          delay(200);
          beep(speakerPin, note_Ab3,300); //A b
          delay(500);
          beep(speakerPin, note_Ab2,300); //A b
          delay(550);
          beep(speakerPin, note_Eb3,500); //E b      
}

void ariel() {

          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,600); //D#
          delay(250);
          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(250);
          
          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,500); //D#
          delay(50);          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);             
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(50); 

}
 

void laugh2() {
          beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          beep(speakerPin, note_C6,200); //C
          delay(50);
          beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          beep(speakerPin, note_C6,200); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          

          
}
  
void squeak() {
  for (int i=100; i<5000; i=i*1.45) {
    beep(speakerPin,i,60);
  }
  delay(10);
  for (int i=100; i<6000; i=i*1.5) {
    beep(speakerPin,i,20);
  }
}

void waka() {
  for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
}

void catcall() {
  for (int i=1000; i<5000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
 delay(300);
 
  for (int i=1000; i<3000; i=i*1.03) {
    beep(speakerPin,i,10);
  }
  for (int i=3000; i>1000; i=i*.97) {
    beep(speakerPin,i,10);
  }
}

void ohhh() {
  for (int i=1000; i<2000; i=i*1.02) {
    beep(speakerPin,i,10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    beep(speakerPin,i,10);
  }
}

void uhoh() {
  for (int i=1000; i<1244; i=i*1.01) {
    beep(speakerPin,i,30);
  }
  delay(200);
  for (int i=1244; i>1108; i=i*.99) {
    beep(speakerPin,i,30);
  }
}

void laugh() {
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
}

int song = 0;

void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song==2){
     Serial.println(" 'Underworld Theme'");
     int size = sizeof(underworld_melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/underworld_tempo[thisNote];

       squeak(melodyPin, underworld_melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       squeak(melodyPin, 0,noteDuration);

    }

   }else{

     Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       squeak(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       squeak(melodyPin, 0,noteDuration);

    }
  }
}

void squeak(int targetPin, long frequency, long length) {
  digitalWrite(13,HIGH);
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13,LOW);

}
