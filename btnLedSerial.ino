/*
RJ 45 T-568B Pinout
GND - Orange, Brown
Btn - Green
LED - Blue
*/

const int BUFFER_SIZE = 10;
char buf[BUFFER_SIZE];

String valA, inString;  // string to hold input

// how many Buttons with LED
#define numBtns 6

// Variables will change:
int btnState[numBtns];
int lastBtnState[numBtns];
int btnPin[] = {2, 5, 8, 11, A0, A3};
int ledPin[] = {3, 6, 9, 12, A1, A4};
int gndPin[] = {4, 7, 10, 13, A2, A5};
int reading[numBtns];
int pinNum;
int ledState;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[numBtns];  // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);
  // default settings
  
  //Setup Buttons and LEDS
  for (int i = 0; i < numBtns; i++) {
    pinMode(btnPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);
    pinMode(gndPin[i], OUTPUT);
    digitalWrite(gndPin[i], LOW);
    digitalWrite(ledPin[i], HIGH);
    lastBtnState[i] = HIGH;
  }
  Serial.println("Ready");
}

void loop() {
  // read the state of the switch into a local variable:
  for (int i = 0; i < numBtns; i++) {
    reading[i] = digitalRead(btnPin[i]);
  // check to see if you just pressed the button
  // (i.e. the input went from HIGH to LOW), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  
    if (reading[i] != lastBtnState[i]) {
      // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading[i] != btnState[i]) {
        btnState[i] = reading[i];
        //Serial.println(i);
  
        // only toggle the LED if the new button state is LOW
        if (btnState[i] == LOW) {
          Serial.println(i);
          //if (digitalRead(ledPin[i]) == 1){
            //digitalWrite(ledPin[i], 0);
          //}
        }
      }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastBtnState[i] = reading[i];
  }

  if (Serial.available() > 0) {
    Serial.readBytesUntil('\n', buf, BUFFER_SIZE);
    digitalWrite(ledPin[int(buf[0] - '0')], int(buf[1] - '0'));
  }
}
