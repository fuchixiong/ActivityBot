#include "simpletools.h"                    
#include "abdrive.h"                         
#include "ping.h"                     
#include "time.h"
#include "stdbool.h"
 
int turn; 

int main() // main function
{
    drive_setRampStep(10);
    //creating a two minute timer
    time_t endwait;
    int seconds = 120;
    endwait = time(NULL) + seconds;
    bool right = false;
    
    // while the time is less then 2 minutes
    while ((time(NULL) < endwait)) {
        goForward();
        // While distance greater than or equal to 20 cm, wait 5ms & recheck.
        while (ping_cm(8) >= 20) {
            pause(5); // Wait until object in range
        }
        stopMoving(); // Object is range stop moving
        freqout(4, 500, 1000); //beep if obstacle is found
        
        turn = rand() % 2;
       
        //turnRight();
        
        // Checks to see if object is on the right
        if(ping_cm(8) < 20){
           stopMoving();
           turnRight();
           freqout(4,500,1000);        
        }else{
           goForward();  
        } 
         // turns robot left if object is in the left direction commands to go backwards.    
         if(ping_cm(8) < 20){
           stopMoving();
           turnLeft();
           freqout(4,500,1000);
        } else {
           goForward();  
        }        
        
        // Keep turning while object is in view
        while (ping_cm(8) < 20);
    }
    stopMoving(); // Stop moving
    
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
