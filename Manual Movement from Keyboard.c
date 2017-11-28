#include "simpletools.h"                      
#include "abdrive.h"

terminal *term;                               // For full duplex serial terminal
char c = 0;                                   // Stores character input

int main()                       
{
  //closes default terminal
  simpleterm_close();
  //open new terminal so code will not be stuck waiting for commands                         
  term = fdserial_open(31, 30, 0, 115200);
  
  // activitybot is stopped when the program starts
  drive_speed(0, 0);                          
  // Display user instructions and prompt.  
  dprint(term, "Check the box Echo\n\n");
  dprint(term, "w = Forward\ns = Backward\na = Left\nd = Right\nf = stop\n>");

  while(1)                                    
  {
    //shows character in terminal
    c = fdserial_rxTime(term, 50);
    
    //if w is pressed activitybot moves forward 
    if(c == 'w'){
      goForward();
    }
    //if s is pressed activitybot moves backwards            
    if(c == 's'){
      goBackward();
    } 
    //if a is pressed activitybot turns left          
    if(c == 'a'){
      turnLeft();
    } 
    //if d is pressed activitybot turns right            
    if(c == 'd'){
      turnRight();
    }
    // if f is pressed activitybot stops moving           
    if(c == 'f'){
      stopMoving();
    }               
  }
  
}

void goForward() {
  drive_ramp(64, 64);
}

void goBackward(){
  drive_ramp(-64, -64);
}

void turnLeft() {
  drive_speed(-64, 64);
}

void turnRight() {
  drive_speed(64, -64);
}

void stopMoving() {
  drive_ramp(0, 0);
}