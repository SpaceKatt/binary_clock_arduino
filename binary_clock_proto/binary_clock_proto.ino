// cathodes
const int numCols = 6;
const int colPins[] = {2, 3, 4, 5, 6, 7};

// anodes
const int numRows = 4;
const int rowPins[] = {8, 9, 10, 11};

int secPerMin = 60;

unsigned long globalCount = 0;

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

void displayTime(int value, int low_bound, int high_bound) {
  int temp = value;
  int mask = 1;
  int decade = 1;
  
  for (int col = high_bound - 1; col >= low_bound; col--) {
    temp = value / decade % 10; 

    for (int row = 0; row < numRows; row++) {
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

    seconds = globalCount % 60;
    minutes = (globalCount / 60) % 60;
    hours = (globalCount / 3600) % 24;

    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(seconds);
  }
  
  allOff();
  
  displayTime(seconds, 4, 6);
  displayTime(minutes, 2, 4);
  displayTime(hours, 0, 2);
}
