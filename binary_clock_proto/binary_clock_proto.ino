// cathodes
const int numCols = 2;
const int colPins[] = {4, 5};

// anodes
const int numRows = 4;
const int rowPins[] = {6, 7, 8, 9};

int secPerMin = 60;

int globalCount = 0;

int seconds = 0;
int minutes = 0;
int hours = 0;

unsigned long sysTime;
unsigned long lastTick;

void setup() {
  sysTime = millis();
  lastTick = millis();
  
  for (int i = 0; i < numCols; i++) {
    pinMode(colPins[i], OUTPUT);
  }

  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
  }

  allOff();

  seconds = globalCount % 60;
  minutes = globalCount / 60 % 60;
  hours = globalCount / 3600 % 24;

  Serial.begin(9600);
}

void allOff() {
    // For dark, bring row high and col low
  for (int i = 0; i < numCols; i++) {
    digitalWrite(colPins[i], LOW);
  }

  // To light, bring row low and col high || row HIGH-colLOW || LOWLOW
  for (int i = 0; i < numRows; i++) {
    digitalWrite(rowPins[i], HIGH);
  }
}

void lightCoord(int x, int y) {
  int rowPin = rowPins[x];
  int colPin = colPins[y];
  
  digitalWrite(rowPin, LOW);
  digitalWrite(colPin, HIGH);
}

void displaySeconds() {
  int temp = seconds;
  int mask = 1;
  int decade = 1;
  
  for (int col = 0; col < 2; col++) {
    temp = seconds / decade % 10; 
    for (int row = 0; row < numRows; row++) {
      if (col + row > 3) {
        break;
      }

//      Serial.println(temp);
      if ((temp >> row) & mask) {
        lightCoord(row, col);
        allOff();
      }

    }
    decade *= 10;
  }
}

void loop() {
  sysTime = millis();

  if (sysTime - lastTick > 1000) {
    lastTick = millis();
    globalCount++;
    Serial.println(seconds);
    seconds = globalCount % 60;
    minutes = globalCount / 60 % 60;
    hours = globalCount / 3600 % 24; 
  }
  
  allOff();
  
  displaySeconds();
}
