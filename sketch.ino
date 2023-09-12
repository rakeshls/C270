#include <MD_MAX72xx.h>
#include <ezButton.h>

// matrix controls
const byte data_pin = 11;
const byte chip_select_pin = 10;
const byte clock_pin = 13;
const byte max_devices = 4;

ezButton button(8);

int head_y = 0;  
int head_x = 0;
int flag=0;
 
String direction="" , prev_direction = "";
int max_x = 31, max_y = 7;

// creating matrix object
MD_MAX72XX matrix = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, chip_select_pin, max_devices);

// define the joystick controls
const byte hpin = A0;
const byte vpin = A1;

void setup(){
  Serial.begin(9600);

  matrix.begin();
  matrix.clear();

  button.setDebounceTime(25);
  matrix.setPoint(head_x,head_y,true);
  
}

void loop(){

  button.loop();
 // put your main code here, to run repeatedly:
 if(flag==0){
    check_direction();
    move_sprite();
 }

 matrix.setPoint(head_y,head_x,true);
 delay(200);
  
}

void window_check(){
  if(head_x > max_x) head_x=0;
  else if(head_x < 0) head_x=max_x;
  else if(head_y > max_y) head_y=0;
  else if(head_y < 0) head_y=max_y;
}


void check_direction(){

  if(analogRead(hpin)>512 &&  prev_direction  !=  "right")
    direction="left";
  else if(analogRead(hpin)<512 &&  prev_direction  !=  "left")
    direction="right";
  else if(analogRead(vpin)>512 &&  prev_direction  !=  "down")
    direction="up";
  else if(analogRead(vpin)<512 &&  prev_direction  !=  "up")
    direction="down";

  //  updating prev_direction
  prev_direction = direction;

}

void move_sprite(){
  if(direction=="left") head_x++;
  else if(direction=="right") head_x--;
  else if(direction=="up") head_y--;
  else if(direction=="down") head_y++;

  window_check();

  if(button.isPressed()){
    Serial.println("The button is pressed");
    flag=1;
  }
}