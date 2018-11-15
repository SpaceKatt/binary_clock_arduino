const int numCols = 2;
const int colPins[] = {0, 1};

const int numRows = 4;
const int rowPins[] = {6, 7, 8, 9};

void setup() {
  // For dark, bring row high and col low
  for (int i = 0; i < numCols; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  // To light, bring row low and col high
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
