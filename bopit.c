//BOPIT IS FUN

//reference: https://gist.github.com/c-eastman/5380163


#include <LiquidCrystal.h>

//set all LEDs and buttons to needed inputs
//numbers are obviously not correct as of now
const int startButton = 4;
const int userButton = 5;
const int userSlider = 6;
const int userToggle = 7;
//does the LCD screen need something?

//store the state of the inputs
int stateButtonState = 0;
int userButtonState = 0;
int userSliderState = 0;
int userToggleState = 0;

boolean gameOn = false;

int userChoice = 0;
int score = 0;
int turn = 0; //turn number, used to index array of commands
double waitTime = 600; //max time between command given and user action

int commands[30];




void setup() {
	//set start button, user button, slider, toggle to inputs
	//setup the LCD display
	
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("Bop It!");
	
}

void loop() {
	
	//when the game button is pressed setup 
	if (startButtonState == 1) { //how to represent high? 1?
		//reset turn count and score
		score = 0;
		turn = 0;
		gameOn = true;
		
		for (int i = 0; i < 100; i++){ //used to generate random commands 
			commands[i] = random(0,3); //random commands are 0, 1, 2
		}
	}
	
	stateButtonState = digitalRead(startButton);
	userButtonState = digitalRead(userButton);
	userSliderState = digitalRead(userSlider);
	userToggleState = digitalRead(userToggle);
	
	//the main loop for playing the game
	if (gameOn) {
		
	}
	
}


/* //function for comparing user input with desired input
int check (choice, desired) {
	if (desired == choice) {
		//blink green LED
		score += 1;
		return 1;
		
	} else {
		//blink red led
		//display score
		//end game
		return -1;
	}
} */

//updates the LCD screen with a text indicator of the current score
void LCD update(String text, int color {
	LCD.print(text);
)