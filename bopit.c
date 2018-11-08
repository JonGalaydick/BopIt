//BOPIT IS FUN

//reference for general gameplay: https://gist.github.com/c-eastman/5380163
//reference for sounds: https://www.arduino.cc/en/Tutorial/toneMelody
//reference for timer: hopefully this https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing


#include <LiquidCrystal.h>

//example tone definitions, have to finalize this eventually
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49

//set all pins that the arduino needs
//numbers are obviously not correct as of now
const int startButton = 4;
const int userButton = 5;
const int userSlider = 6;
const int userToggle = 7;
const int speakerPin = 8;
//does the LCD screen need something?

int previousSliderState;

//store the state of the inputs (might not need this)
// int stateButtonState = 0;
// int userButtonState = 0;
// int userSliderState = 0;
// int userToggleState = 0;

boolean gameOn = false;
boolean nextCommand = true;

int userChoice = 0; //what the user action is during gameplay
int score = 0; //also indexes command array
long delayTime = 5000; //wait time for user to make an action

int commands[100]; //game commands

unsigned long previousMills = 0;


void setup() {
	//set start button, user button, slider, toggle digital inputs on the microprocessor
	//setup the LCD display
	
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("Bop It!");
	
}

void loop() {
	
	// stateButtonState = digitalRead(startButton);
	// userButtonState = digitalRead(userButton);
	// userSliderState = digitalRead(userSlider);
	// userToggleState = digitalRead(userToggle);
	
	//when the game button is pressed setup 
	if (startButtonState == HIGH) { //how to represent high? 1? HIGH?
		resetGame();
	}
	
	unsigned long currentMills = millis();

	
	//the main loop for playing the game
	if (gameOn) {
		
		//give the player their command
		if (nextCommand) {
			if (command[score] == 1) {
			//give button command sound
			LCD_update("BUTTON");
			playSound(NOTE_A3);
			} else if (command[score] == 2) {
				//give slider command sound
				LCD_update("SLIDE");
				playSound(NOTE_C4);
			} else if (command[score] == 3) {
				//give toggle command sound
				LCD_update("TOGGLE");
				playSound(NOTE_G1);
			} else {
				LCD_update("COMMAND ISSUE");
			}
		}

		
		if (currentMills - previousMills > delayTime) {
			
			if (digitalRead(userButton) == HIGH) {
				userChoice = 1;
			} else if (digitalRead(userSlider) != previousSliderState) { 
				//done on a change of state since it doesnt automatically go back to LOW
				userChoice = 2;
			} else if (digitalRead(userToggle) == HIGH) {
				userChoice = 3;
			}
			
			if (userChoice == command[score]) {
				//correct action made in correct amount of time
				score += 1;
				LCD_update("Correct!");
				delayTime -= 40;
				previousMills = currentMills; //reset countdown for next turn
				nextCommand = true; //so we can give the user their next command
				if (score == 99) {
					LCD_update("You Win!!!");
					gameOn = false;
				}
			} else if (userChoice != 0 && userChoice != command[turn]) {
				//incorrect action made in the time frame
				LCD_update("Game Over!");
				gameOn = false;
			}
			
		} else {
			LCD_update("Game Over!");
			gameOn = false;
		}
			
	}
	
}

//called when game start button is pressed
void resetGame() {
	score = 0;
	turn = 0;
	gameOn = true;
	previousMills = millis(); //set starting time of the game
	previousSliderState = digitalRead(userSlider);
	
	//for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){ //used to generate random commands 
	for (int i = 0; i < 100; i++) {
		commands[i] = random(1, 4); //random commands are 1, 2, 3
		//0 maps to the button
		//1 maps to the sldier
		//2 maps to the toggle
	}
}

//updates the LCD screen with game state and current score
void LCD_update(String text) {
	lcd.clear();
	lcd.setCursor(3,0);
	lcd.print(text);
	
	//convert score to a string variant, then print it on the LCD on a new line
	lcd.setCursor(3,0);
	char scoreString[12];
	sprintf(scoreString, "Score: %d", score);
	lcd.print(scoreString);
)

//takes the int representation of a sound and plays it to the speaker
void playSound(int sound) {
	tone(speakerPin, sound, 500); //500 millisecond duration
}







