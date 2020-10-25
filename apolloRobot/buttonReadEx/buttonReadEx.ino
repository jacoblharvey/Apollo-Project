
int stateC;
int timerC;

void setup() {
  Serial.begin(9600);

  pinMode(6, OUTPUT); //WHITE
  pinMode(7, OUTPUT); //RED
  pinMode(8, INPUT_PULLUP); //BUTTON

  stateC = 0;
  timerC = 0;

  Serial.println("Program Start");
}

void stateMachineC(){ //gets called 10 times per second

  if(timerC > 0){
    timerC = timerC - 1;
  } else{
    switch(stateC){
      case 0:
        digitalWrite(6, HIGH); // turn White LED on
        if(digitalRead(8) == 0){
        // button is pressed
        digitalWrite(6, LOW); // turn LED off
        stateC = 1;
        timerC = 10;
        }
        break;
      case 1:
        digitalWrite(6, LOW); // turn LED off
         if(digitalRead(8) == 0){
        // button is pressed
        digitalWrite(6, HIGH); // turn White LED on
        stateC = 0;
        timerC = 10;
        }
        break;

  }
  }

}

void oncePer100mS(){ //gets called 10 times per second

  stateMachineC();
}
void loop(){
  int i;
  delay(100); //this is the only thing that slows us down
  oncePer100mS();


 i=digitalRead(8);
}



 
