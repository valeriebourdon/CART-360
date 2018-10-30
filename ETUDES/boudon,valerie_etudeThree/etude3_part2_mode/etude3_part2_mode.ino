/**********************ETUDE 2 CART 360 2017*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  looper   ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/
#include "pitches.h" // include the pitches doc

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
// I changed this
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM


/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();

  // serial print to get values of A0
  //button 1 = 211
  //button 2 = 308
  //button 3 = 322
  //button 4 = 618
  //button 5 = 679
  Serial.println(analogRead(A0));
  delay(200); 
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode()
{
 /* IMPLEMENTED HERE */
 //If the button is pressed 
 if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
    if(mode <= 4){ // if the button presses are less than or equal to 4, prefixed increment by 1
      ++mode;
      delay(1000); // delay by a second to slow down incrementation
    }
    else {
    mode = 0; //If the button presses is more than 4 (# of modes), reset to 0
 }
 }
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
//creating functions for each colour setting using 0-255 values
void setOff() {
  analogWrite(LED_PIN_R, 0);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 0);
  }

void setR() {
  analogWrite(LED_PIN_R, 255);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 0);
  }

void setG() {
  analogWrite(LED_PIN_R, 0);
  analogWrite(LED_PIN_G, 255);
  analogWrite(LED_PIN_B, 0);
  }

void setB() {
  analogWrite(LED_PIN_R, 0);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 255);
  }

void setP() {
  analogWrite(LED_PIN_R, 80);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 255);
  }

void setRGB()
{
 /* IMPLEMENTED HERE */
 // using a case statement to match a colour to the current mode
 switch (mode) {
  case 0: setOff();
  break;
  case 1: setB();
  break;
  case 2: setR();
  break;
  case 3: setG();
  break;
  case 4: setP();
  break;
  default: setOff();
  break;  
  }
}

/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  
  else if(mode == 3) {
    play();
  }
   
   else if(mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
 /* IMPLEMENTED HERE */
 // reset note count
 int countNotes = 0;
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
 /* IMPLEMENTED HERE */
 if (analogRead(NOTE_IN_PIN) > 205 && analogRead(NOTE_IN_PIN) < 215) { // allow range of values for button press
   tone(BUZZER_PIN, NOTE_C5, 400);
   delay(100); // delay to slow down incrementation
 } else if (analogRead(NOTE_IN_PIN) > 305 && analogRead(NOTE_IN_PIN) < 315) {
   tone(BUZZER_PIN, NOTE_D5, 400);
   delay(100);  
 } else if (analogRead(NOTE_IN_PIN) > 320 && analogRead(NOTE_IN_PIN) < 325) {
   tone(BUZZER_PIN, NOTE_E5, 400);
   delay(100);
 } else if (analogRead(NOTE_IN_PIN) > 615 && analogRead(NOTE_IN_PIN) < 622) {
   tone(BUZZER_PIN, NOTE_F5, 400);
   delay(100);
 } else if (analogRead(NOTE_IN_PIN) > 670 && analogRead(NOTE_IN_PIN) < 685) {
   tone(BUZZER_PIN, NOTE_G5, 400);
   delay(100);
 }
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  if (countNotes <= MAX_NOTES) { // if less than 16 notes have been played
   if (analogRead(NOTE_IN_PIN) > 205 && analogRead(NOTE_IN_PIN) < 215) {
       tone(BUZZER_PIN, NOTE_C5, 400);
       notes[countNotes] = NOTE_C5; // set the value of 0 to 740
       countNotes++; // increase the index
       delay(100);
   } else if (analogRead(NOTE_IN_PIN) > 305 && analogRead(NOTE_IN_PIN) < 315) {
       tone(BUZZER_PIN, NOTE_D5, 400);
       notes[countNotes] = NOTE_D5;
       countNotes++;
       delay(100);
   } else if (analogRead(NOTE_IN_PIN) > 320 && analogRead(NOTE_IN_PIN) < 325) {
       tone(BUZZER_PIN, NOTE_E5, 400);
       notes[countNotes] = NOTE_E5;
       countNotes++;
       delay(100);
   } else if (analogRead(NOTE_IN_PIN) > 615 && analogRead(NOTE_IN_PIN) < 622) {
       tone(BUZZER_PIN, NOTE_F5, 400);
       notes[countNotes] = NOTE_F5;
       countNotes++;
       delay(100);
   } else if (analogRead(NOTE_IN_PIN) > 670 && analogRead(NOTE_IN_PIN) < 685) {
       tone(BUZZER_PIN, NOTE_G5, 400);
       notes[countNotes] = NOTE_G5;
       countNotes++;
       delay(100);
   }
  } else {
    countNotes = 0; 
    }
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play(){
  for (int i = 0; i <= countNotes; i++) { //play for the size of the array
    tone(BUZZER_PIN, notes[i], 400);
    delay(400);
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
 //play backwards by reversing the initial value and the restriction
  for (int i = countNotes; i >= 0; i--) { //play for the size of the array
    tone(BUZZER_PIN, notes[i], 400);
    delay(400);
  }}

/**************************************************************************/
/*
PART THREE: SHORT ANSWER
short answer is provided in part one
*/
