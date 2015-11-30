char directions[] = {'U', 'D', 'L', 'R'};
String computerRandom, currentUserWord = "0123456789";
int a = 0, counting, STATE = 0, correctCounter = 0, gameCounter = 0;
unsigned long previousMillis = 0;
const long interval = 10000;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  randomSeed(analogRead(0));
  STATE = 0;
}

void loop() {

  if (STATE == 0) {
    inputString.remove(2);
    story();
    delay(3000);
  }

  if (STATE == 1) {
    computerRandom = secretWordChoice();
    Serial.println("Quick Match It!");
    Serial.println("   " + computerRandom);
    previousMillis = millis();
  }

  if (STATE == 2) {
    currentUserWord = convertTo(inputString, stringComplete);
  }

  if (STATE == 3) {
    counting = compareString(computerRandom, currentUserWord);
    Serial.println("   " + currentUserWord);
  }

  if (STATE == 4) {
    if (counting == 1) {
      correctCounter++;
      Serial.println("CORRECT");
      delay(3000);
      STATE = 5;
    }
    if (counting == -1) {
      Serial.println("INCORRECT");
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
    inputString = "";
  }

  if (STATE == 6) {
    Serial.println("Play Again?");
    Serial.println("Y = Yes | N = No");
    a = 0,
    correctCounter = 0;
    gameCounter = 0;
    inputString = "";
    STATE = 7;
  }


  if (STATE == 7) {
    if ((inputString == "Y") || (inputString == "y")) {
      STATE = 0;
    }
    else if ((inputString == "N") || (inputString == "n")) {
      STATE = 8;
    }
  }

  if (STATE == 8) {
    Serial.println("Game Over!!");
  }

}


/*------------Functions------------*/

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar != '\n') {
      inputString += inChar;
    }
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

String convertTo(String stringToConvert, boolean cond) {
  String converted = "0123456789";
  char c;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    STATE = 3;
  };
  if (cond == true) {
    for (int a = 0; a < 10; a++) {
      if (stringToConvert.charAt(a) == 'w' ) {
        c = 'U';
      } else if (stringToConvert.charAt(a) == 'a') {
        c = 'L';
      } else if (stringToConvert.charAt(a) == 's') {
        c = 'D';
      } else if (stringToConvert.charAt(a) == 'd') {
        c = 'R';
      };
      converted.setCharAt(a, c);
    };
  };
  return converted;
  STATE = 3;
}


void checkWin (int _correctCounter) {
  switch (_correctCounter) {
    case 0:  //jail
      Serial.println(" Couldn't Even Win One Darn!");
      delay(3000);
      STATE = 6;
      break;
    case 5:  //win
      Serial.println("What a sly fox you are! You played their game and won! You’re rich as can be! Go walk out of this joint like the money you are.");
      STATE = 6;
      break;
    case 1:
    case 2://good employee
      Serial.println("Great Employee And A Bummy Job");
      delay(3000);
      STATE = 6;
      break;
    case 3:
    case 4:  //hero
      Serial.println("You gave people their money back");
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

void story() {
  Serial.println("Welcome to Glitch Gone Wild!!");
  delay(3000);
  Serial.println("You work for the bank and things have gone awry.");
  Serial.println("There's a glitch in the system and it seems like you are the only one who has noticed.");
  delay(3000);
  Serial.println("You only have 10s for each round!!");
  Serial.println("What would you do?");
  STATE = 1;
}
