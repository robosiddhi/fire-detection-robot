/*
Code Name: Arduino Uno Fire Detecting Robocar
Author: RoboSiddhi

⚠ Warning

This project and its code are shared for learning and personal use only.  
Commercial use, redistribution, or selling (in any form) of this code or
project is not allowed without proper permission.  

                                                                                 .                 
              !^           .   ..   ..            
              ??^~^.      ....:....             
             :P5J?7?JY5.   ...^:::^..             
            .BG5JY75&JYG   ...^:::^..             
            .BBBP57?YYYG.   ....::::              
             :YBBGYJ??Y?   .  .^ YGGY.            
              :!BBBBY!:       .G??5BP^            
            ~GP5P5??77!7:    .^J55Y!              
           ^#57!7#5777!?57~:77JG                
           ?#G5PB#57777!B5GG5YPJ.                 
          .BGYY&&BPY???J!!Y5Y7:                   
          :7!~!7777!!!!^     
                               
Description:  Flame Detecting Robo Car A simple Arduino Uno based flame detecting robot using 3 
flame sensors, L298N motor driver, 4 BO motors with wheels, and a 2-cell 18650 battery pack.
The sensors detect the flame and Arduino controls the motors to follow the flame and create a hazard sound. Great for
learning robotics, DIY projects, and basic STEM applications.
*/


// --------- Flame sensor pins (analog) ---------- //
          int centerSensor = A1;  // only using center for analog control
          int leftSensor = A0; 
          int rightSensor = A2;
          
// --------- Motor Driver (L298N) Pins -----------//
          int L_IN1 = 2;
          int L_IN2 = 3;
          int L_EN  = 5;   // PWM pin
          int R_IN1 = 4;
          int R_IN2 = 7;
          int R_EN  = 6;   // PWM pin

// --------- Settings ----------- //
          int MOTOR_SPEED = 120;            // 0-255
          unsigned long MAX_PUMP_TIME = 20000UL; 

void setup() {
  Serial.begin(9600);

          pinMode(L_IN1, OUTPUT);
          pinMode(L_IN2, OUTPUT);
          pinMode(L_EN, OUTPUT);
          pinMode(R_IN1, OUTPUT);
          pinMode(R_IN2, OUTPUT);
          pinMode(R_EN, OUTPUT);
}

void loop() {
  // Read and invert sensor value //
          int rawValue = analogRead(centerSensor);
          int flameIntensity = 1023 - rawValue;  
          int rawValue1 = analogRead(leftSensor);
          int flameIntensity1 = 1023 - rawValue1;
          int rawValue2 = analogRead(rightSensor);
          int flameIntensity2 = 1023 - rawValue2;
  
Serial.print("Flame Intensity: ");
Serial.println(flameIntensity);

// Decision based only on center sensor //
   if (flameIntensity >= 100 && flameIntensity < 800) {
 forward();
 buzzer();// go towards flame
  } 

 

 else if(flameIntensity1 > 100 && flameIntensity1 < 900) {
    left();  // go left flame
}


 else if (flameIntensity2 > 100 && flameIntensity2 < 900) {
    right();  // go left flame
}
  else { stopCar();
  buzzerstop();
   }
}


/* ---------- Movement Functions ---------- */
void forward() {
          
          digitalWrite(L_IN1, HIGH);
          digitalWrite(L_IN2, LOW);  
          analogWrite(L_EN, MOTOR_SPEED);
          digitalWrite(R_IN1, HIGH); 
          digitalWrite(R_IN2, LOW);  
          analogWrite(R_EN, MOTOR_SPEED);
}
void left() {
  
          digitalWrite(L_IN1, HIGH);
          digitalWrite(L_IN2, LOW);  
          analogWrite(L_EN, MOTOR_SPEED);
          digitalWrite(R_IN1, LOW); 
          digitalWrite(R_IN2, HIGH);  
          analogWrite(R_EN, MOTOR_SPEED);
}
void right() {
  
          digitalWrite(L_IN1, LOW);
          digitalWrite(L_IN2, HIGH);  
          analogWrite(L_EN, MOTOR_SPEED);
          digitalWrite(R_IN1, HIGH); 
          digitalWrite(R_IN2, LOW);  
          analogWrite(R_EN, MOTOR_SPEED);
}
void stopCar() {
  
          analogWrite(L_EN, 0);
          analogWrite(R_EN, 0);
          digitalWrite(L_IN1, LOW);
          digitalWrite(L_IN2, LOW);
          digitalWrite(R_IN1, LOW);
          digitalWrite(R_IN2, LOW);
}
void buzzer(){

          tone(11, 400);
          delay(500);
          tone(11, 2000);
          delay(500);
}

void buzzerstop(){
          noTone(11);
}
