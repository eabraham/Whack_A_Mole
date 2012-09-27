//game variables
unsigned long lastButtonTime =0;
unsigned long cumReactionTime =0;
unsigned long currReactionTime =0;
unsigned long currButtonTime =0;
int rndButton=0;
int targetState=0;
int buttonState=0;
int startbuttonState=0;


//config
int turnsPerGame=10;
int numDigButtons=10;
int digButtons[] ={2,3,4,5,6,7,8,9,10,11,12];
int numAnButtons=5;
int anaButtons[] ={A0,A1,A2,A3,A4];
int anaLevels[] ={3,2,5,2,2];
int startButtonPin=1;
int analogTol=20;

int LEDPinStart=20;
int buttonCount=17;
//pin, button type (0 dig, 1 ana), levels, current level
int buttons[17][4] = {
    {2,0,2,1},
    {3,0,2,1},
    {4,0,2,1},
    {5,0,2,1},
    {6,0,2,1},    
    {7,0,2,1},    
    {8,0,2,1},    
    {9,0,2,1},
    {10,0,2,1},
    {11,0,2,1},
    {12,0,2,1},
    {A0,0,2,1},    
    {A1,0,5,1},
    {A2,0,4,1},
    {A3,0,3,1},   
    {A4,0,3,1},    
    {A5,0,3,1}        
};


void setup(){
  //setup pins
  uptButtonState();
}
void loop(){
   startbuttonState = digitalRead(startButtonPin);
   if (startbuttonState == HIGH){
     resetGameVar();
     //start new game
     lastButtonTime=millis();
     for (int i=0;i<turnsPerGame;i++){
       uptButtonState();
       executeTurn();         
     }
     //To Do: display reaction time
   }
   //To Do:  display cumReactionTime
}
void uptButtonState(){
  for (int x=0;x<buttonCount;x++){
    if (buttons[x][1] == 0){
      //is digital
      buttons[x][4]=digitalRead(buttons[x][0]);
    }else{
      //is analog
      buttons[x][4]=analogRead(buttons[x][0])/200;      
    }
  }
}
int getRandomButton(){
  return random(buttonCount);
}

void executeTurn(){
  rndButton = getRandomButton();
  if (buttons[rndButton][1] == 0){
    //is digital  
    targetState=abs(buttons[rndButton][3]-1);
    digitalWrite(LEDPinStart+buttons[rndButton][3]-1,HIGH); //Light up LED
    while(buttonState != targetState){
      buttonState = digitalRead(rndButton);
    }
    digitalWrite(LEDPinStart+buttons[rndButton][3]-1,LOW); //Turn off LED
  } else {
    //is analog  
    targetState=abs(buttons[rndButton][3]-random(buttons[rndButton][2]));
    digitalWrite(LEDPinStart+buttons[rndButton][3]-1,HIGH); //Light up LED
    while(buttonState != targetState){
      buttonState = analogRead(rndButton);
    }
    digitalWrite(LEDPinStart+buttons[rndButton][3]-1,LOW); //Turn off LED    
  }
  currButtonTime= millis();
  currReactionTime=(currButtonTime-lastButtonTime);
  
  cumReactionTime+=currReactionTime;
  lastButtonTime=currButtonTime;
}

void resetGameVar(){
  cumReactionTime=0;
  lastButtonTime=millis();
  rndButton=0;
}  

