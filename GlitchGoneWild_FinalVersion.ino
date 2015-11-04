// include the library code:
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

char directions[] = {'U', 'D', 'L', 'R'}, stringButton;
String userWord = "0123456789", userInput, computerRandom, currentUserWord = "0123456789";
boolean  buttonPressed = false;
int a = 0, counting, STATE = 0, correctCounter = 0, gameCounter = 0;
unsigned long previousMillis = 0;
const long interval = 15000;

//LCD Scroll Text
String test, top, bottom, sol1, sol2, sol3, sol4;
int characters = 0, lines = 0, lines1, lines2, lines3, lines4, remainder = 0;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
  randomSeed(analogRead(0));
  STATE = 0;

  test.reserve(200);
  top.reserve(30);
  bottom.reserve(30);
  //test = {"The Gunfight at the O.K. Corral was a 30-second gunfight between outlaw Cowboys and lawmen that is generally regarded as the most famous shootout in the history of the American Wild West.     "};
  test = {"   Welcome to   Glitch Gone WildYou work for thebank and things have gone awry. There's a glitchin the system and it seems like you are the onlyone who has     noticed.   What will you choose?"};
  sol1 = {"What a sly fox you are! You played their game and won! You’re rich as can be! Go walk out of this joint like the money you are."};
  
  characters = test.length();
  lines = (test.length() / 16) / 2;
  lines1 = (sol1.length() / 16) / 2;
  remainder = test.length() % 16;

}

uint8_t i = 0;
void loop() {
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (buttons & BUTTON_UP) {
      stringButton = 'U';
    }
    if (buttons & BUTTON_DOWN) {
      stringButton = 'D';
    }
    if (buttons & BUTTON_LEFT) {
      stringButton = 'L';
    }
    if (buttons & BUTTON_RIGHT) {
      stringButton = 'R';
    }
    if (buttons & BUTTON_SELECT) {
    }
  }
  boolean toggle = buttonCheck(buttons);

  if (STATE == 0) {
    backStory(test, lines);
  }

  if (STATE == 1) {
    lcd.setBacklight(WHITE);
    computerRandom = secretWordChoice();
    lcd.setCursor(0, 0);
    lcd.print("Quick! Match it!");
    lcd.setCursor(0, 1);
    lcd.print("   " + computerRandom);
    previousMillis = millis();
  }

  if (STATE == 2) {
    currentUserWord = getUserInput(toggle);
  }

  if (STATE == 3) {
    counting = compareString(computerRandom, currentUserWord);
  }

  if (STATE == 4) {
    if (counting == 1) {
      correctCounter++;
      lcd.clear();
      lcd.print("    Correct");
      lcd.setBacklight(GREEN);
      delay(3000);
      STATE = 5;
    }
    if (counting == -1) {
      lcd.clear();
      lcd.print("   INCORRECT");
      lcd.setBacklight(RED);
      delay(3000);
      STATE = 5;
    }
  }

  if (STATE == 5) {
    ++gameCounter;
    if (gameCounter < 5) {
      STATE = 1;
    }
    else {
      checkWin(correctCounter);
    }
    lcd.clear();

    stringButton = '0';
  }

  if (STATE == 6) {
    //play again
    lcd.setCursor(0, 0);
    lcd.print("  Play Again?:");
    lcd.setCursor(0, 1);

    lcd.print("   U/D = Y/N");
    a = 0,
    correctCounter = 0;
    gameCounter = 0;
    if (stringButton == 'U') {
      STATE = 0;

    } else if (stringButton == 'D') {
      STATE = 7;
      lcd.clear();
    }
  }
  if (STATE == 7) {
    lcd.setCursor(0, 0);
    lcd.print("   Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("     Reset!");
  }
  Serial.println(computerRandom);
}

String getUserInput(boolean buttonOutcome) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    STATE = 3;
  }
  if (buttonOutcome == true) {
    userWord.setCharAt(a, stringButton);
    a++;
  }
  if (a > 10) {
    userInput = userWord;
    a = 0;
    STATE = 3;
  }
  return userInput;
}

void checkWin (int _correctCounter) {
  lcd.setBacklight(WHITE);
  lcd.clear();
  switch (_correctCounter) {
    case 0:
      lcd.setBacklight(RED);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(RED);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(RED);
      lcd.setCursor(0, 0);
      lcd.print(" Couldn't Even");
      lcd.setCursor(0, 1);
      lcd.print("Win One Darn!");
      delay(3000);
      STATE = 6;
      break;
    case 5:  //win
      lcd.setBacklight(YELLOW);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(YELLOW);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(YELLOW);
      backStory(sol1, lines1);
      STATE = 6;
      break;
    case 1:
    case 2://good employee
      lcd.setBacklight(BLUE);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(BLUE);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(BLUE);
      lcd.setCursor(0, 0);
      lcd.print("Great Employee");
      lcd.setCursor(0, 1);
      lcd.print("And A Bummy Job!");
      delay(3000);
      STATE = 6;
      break;
    case 3:
    case 4:
      lcd.setBacklight(VIOLET);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(VIOLET);
      delay(500);
      lcd.setBacklight(WHITE);
      delay(500);
      lcd.setBacklight(VIOLET);
      lcd.setCursor(0, 0);
      lcd.print("You gave people");
      lcd.setCursor(0, 1);
      lcd.print("back their money");
      delay(3000);
      STATE = 6;
      break;
    default:
      break;
  }


}

int compareString(String _inputRandom, String _inputUser) {
  if (_inputRandom == _inputUser) {
    STATE = 4;
    return 1;
  }
  else {
    STATE = 4;
    return -1;
  }
}

String secretWordChoice() {
  String realSecret, secretWord = "0123456789";
  for (int i = 0; i < 10; i++) {
    secretWord.setCharAt(i, directions[random(4)]);
  }
  realSecret = secretWord;
  STATE = 2;
  return realSecret;
}

boolean buttonCheck(int _button) {
  boolean toggleState;
  if (_button != 0) {
    toggleState = true;
  }
  else {
    toggleState = false;
  }
  if (toggleState == true) {
    buttonPressed = true;
  }
  if ((toggleState == false) && (buttonPressed == true)) {
    buttonPressed = false;
    return true;
  }
  else {
    return false;
  }
}

void backStory(String _test, int _lines) {
  for (int i = 0; i <= _lines; i++) {
    Serial.println(i);
    top = _test.substring((16 * i) * 2, 16 + ((16 * i) * 2));
    lcd.setBacklight(YELLOW);
    lcd.setCursor(0, 0);
    lcd.print(top);
    lcd.setCursor(0, 1);
    bottom = _test.substring((16 + ((16 * i) * 2)), 32 + (16 + ((16 * i) * 2)));
    lcd.print(bottom);
    lcd.setBacklight(TEAL);
    delay(2200);
  }
  //if (buttons != 0) {
  lcd.clear();
  STATE = 1;
  //}
}


