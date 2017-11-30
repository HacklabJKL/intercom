/*
 Intercom buttons
 
 The circuit has two LED pushbuttons:
 * PTT constant-voltage LED connected to pin 6 and switch connected to pin 8
 * "Deafing" constant-voltage LED connected to pin 7 and switch connected to pin 9
 
 Outputs:
 * "m" when PTT is down and M when it is released. LED is lit when button is down.
 * "d" when deafing button is pressed and D when it is pressed again (toggle switch). LED is lit when it is in "D" state.
 */

bool pttStateOld = false;
bool deafStateOld = false;
bool pttDebounce = false;
bool deafDebounce = false;
bool deafed = false;

void setup(){
  //start serial connection
  Serial.begin(9600);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop(){
  //read the pushbutton value into a variable
  bool pttState = digitalRead(8);
  bool deafState = digitalRead(9);

  if (deafState != deafStateOld) {
    if (!deafDebounce) {
      deafState = deafStateOld;
      deafDebounce = true;
    } else {
      deafDebounce = false;
    }
  }

  if (pttState != pttStateOld) {
    if (!pttDebounce) {
      pttState = pttStateOld;
      pttDebounce = true;
    } else {
      pttDebounce = false;
    }
  }

  if (!deafState && deafStateOld) {
    deafed = !deafed;
    digitalWrite(7, deafed ? HIGH : LOW);
    Serial.print(deafed ? 'D' : 'd');
  }  

  if (pttState != pttStateOld) {
    digitalWrite(6, pttState ? LOW : HIGH);
    Serial.print(pttState ? 'M' : 'm');
  }

  pttStateOld = pttState;
  deafStateOld = deafState;
  delayMicroseconds(1000);
}



