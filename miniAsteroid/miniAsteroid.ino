/*
 * 
 * Arduino NANO
 * 
 * Author: Marek Urbanski
 * e-mail: marek@www2.pl
 * 
 * https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
 * 
 * Game - mini Asteroid
 * This game has a lot of limitations because Arduino NANO has only: 
 * - 16kb RAM
 * - 16 MHz speed
 * 
 * It uses:
 * 
 *  - Arduino NANO v3 - ATMEGA328P, AU 1708
 *  - LCD 160×128 TFT display with a ST7735S controller,  / LCD 1.8'' TFT SPI ST7735 micro SD ARDUINO STM32
 *  - ARDUINO joystick AVR BASCOM
 *  - 2 x Microstick
 *  - Universal board - PI22 240 WIERCONA 3x7
 */

#include <Opponent.h>
#include <Bullet.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

/*
 * Pins definition
 */
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!

/*
 * global variables
 * mostly byte, because Arduino nano has only 16kb RAM
 * Bots are limited to 50
 * Bullets are limited to 10
 * Thats all because of 16kb RAM
 */
byte px = 0;
byte py = 0;
byte x = 50;
byte y = 50;
byte prev_x = 50;
byte prev_y = 50;
byte max_bullet = 10;
byte nr = 1;
byte nr2 = 1;
int active_time = 0;
byte max_botow = 4;
byte last_joy_x = 2;
byte last_joy_y = 0;
boolean shot_can_be_fired = true;
byte speed = 1;
String prev_text;

Opponent bot[50];
Bullet bullet[10];

/* function for checking 
 * free ram
 */
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


/*
 * Main fusetup
 */
void setup(void) {
  Serial.begin(9600);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  tft.setTextWrap(false);
  tft.setCursor(0, 10);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.println("Game rules:");
  tft.println("");
  tft.println("- Upper button: reset the game");
  tft.println("- JoyStick: move ship");
  tft.println("- Lower button: fire");
  tft.println("");
  tft.println("You are the ship");
  tft.println("Destroy enemies");
  tft.println("(hold fire to skip this)");
  if(digitalRead(5) != HIGH) // skip waiting when pressed key
    delay(4000);
  tft.println("wait...");
  if(digitalRead(5) != HIGH) // skip waiting when pressed key
    delay(1000);
  tft.setTextSize(2);
  tft.print("3,");
  if(digitalRead(5) != HIGH) // skip waiting when pressed key
    delay(1000);
  tft.print("2,");
  if(digitalRead(5) != HIGH) // skip waiting when pressed key
    delay(1000);
  tft.print("1,");
  if(digitalRead(5) != HIGH) // skip waiting when pressed key
    delay(1000);
  tft.print("go !");
  tft.fillScreen(ST7735_BLACK);
  

// setup pins
  pinMode(7, INPUT); 
  pinMode(6, INPUT); 
  pinMode(5, INPUT); 
  pinMode(4, INPUT); 

}

/*
 * Draw description
 * on screen
 */
void setup_description(String text)
{
  tft.setTextWrap(false);
  tft.setCursor(0, 10);
  tft.setTextSize(1);
  //tft.setTextColor(ST7735_BLACK);
  //tft.print(prev_text);
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.print(text);
  prev_text = text;

}

/*
 * Function for drawing object
 * Draw first previous object with black lines - remove previous image
 * and after that draw new picture
 */
void draw_object(byte type, byte x, byte y, byte prev_x, byte prev_y, byte size_object, byte size_prev_object)
  {
    size_prev_object = size_prev_object + 5;
    
    if(type == 1)  // bullet
      {
      tft.drawCircle(prev_x, prev_y, 1, ST7735_BLACK);
      tft.drawCircle(x, y, 1, ST7735_GREEN);  
      }

    if(type == 2) // bot
      {
      tft.fillRect(prev_x-(size_prev_object/2), prev_y-(size_prev_object/2), size_prev_object, size_prev_object, ST7735_BLACK);
      tft.fillRect(x-(size_object/2), y-(size_object/2), size_object, size_object, ST7735_RED);  
      tft.drawRect(x-(size_object/2), y-(size_object/2), size_object, size_object, ST7735_WHITE);  
      
      }

    if(type == 3) // my
      {
        
      tft.fillCircle(prev_x, prev_y, 6, ST7735_BLACK);
      tft.drawLine(x-5,y,x+5,y, ST7735_WHITE);
      tft.drawLine(x,y-5,x,y+5, ST7735_WHITE);
      tft.fillCircle(x, y, 3, ST7735_BLUE);  
      tft.drawCircle(x, y, 3, ST7735_WHITE);
      }

  }

/*
 * Function for removing object only
 */
void undraw_object(byte type, byte x, byte y, byte size_object)
  {
    size_object = size_object + 5;
    if(type == 1)  // bullet
      {
      tft.fillCircle(x, y, 3, ST7735_BLACK);  
      }

    if(type == 2) // bot
      {
      for(byte i=0; i<size_object/2+15; i=i+3)
        tft.fillCircle(x, y, i, ST7735_WHITE);  

      for(byte i=0; i<size_object/2+18; i=i+3)
        tft.fillCircle(x, y, i, ST7735_BLACK);  
      }

    if(type == 3) // my
      {
      tft.fillCircle(x, y, 6, ST7735_BLACK);  
      }

  }


/*
 * Main loop
 */
void loop() {
  // counter, how log user is playing
  active_time++;

  // this funcitn is not used
  // if you want to increase speed uncomment "speed++;"
  if(active_time % 3000 == 0) 
    {
    // speed++;
    }

  /* 
   * increase speed  
   * Check if user won the game
   */
  if(active_time % 100 == 0) 
  {
   //setup_description("Punktow: "+String(max_botow)+"."+String(active_time));
   max_botow++;
   speed++;
   active_time = 0;
   if(max_botow == 49)
       {
      // koniec gry - wygrana
      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      setup_description("YOU WIN !!!: "+String(max_botow)+"."+String(active_time));
      tft.println("YOU WIN !!! :) "+String(max_botow)+"."+String(active_time)+" !!!!");
      delay(3000000);
       }
  }


/*
 * This is fix because at the begining 
 * I didnt have an resistor and in some cases 
 * my finger was shoting the bullet without pressing the buttn
 */
  if(active_time % 10 == 0) 
  {
   shot_can_be_fired = true;
  }



  if(digitalRead(5) == HIGH) 
    {  
    if(shot_can_be_fired == true)
      {
        shot_can_be_fired = false;
        for(nr = 1; nr<max_bullet; nr++)
          {
          if(bullet[nr].active == false)
            { 
            bullet[nr].Fire(x,y,last_joy_x,last_joy_y);
            break;
            }
          }    
      }
    }


/*
 * Moving bullets
 * CHecking if bullet touch opponent (bot)
 * if yes - kill bot
 */
  for(nr = 1; nr<max_bullet; nr++)
    {
    bullet[nr].Action(0,0);
    if(bullet[nr].active == true)
      {
      draw_object(1, bullet[nr].x, bullet[nr].y, bullet[nr].prev_x, bullet[nr].prev_y, 6, 6);
      for(nr2=0; nr2<max_botow; nr2++)
        {
          // checking if bot is killed
          if(bot[nr2].killed == false)
            {
            // checking if bullet hit the bot
            if(
              ((bot[nr2].x + 3) > (bullet[nr].x - bot[nr2].my_size/2))
              && ((bot[nr2].x - 3) < (bullet[nr].x + bot[nr2].my_size/2))
              && ((bot[nr2].y + 3) > (bullet[nr].y - bot[nr2].my_size/2))
              && ((bot[nr2].y - 3) < (bullet[nr].y + bot[nr2].my_size/2))
              )
                {
                bullet[nr].active = false;
                bot[nr2].killed = true;               
                bullet[nr].visible = false;
                undraw_object(1, bullet[nr].x, bullet[nr].y, 6);
                undraw_object(1, bullet[nr].prev_x, bullet[nr].prev_y, 6);
                undraw_object(2, bot[nr2].x, bot[nr2].y, bot[nr].my_prev_size);
                }
            }
        }
      }
      else
      {
        if(bullet[nr].visible == true)
          {
          bullet[nr].visible = false;  
          undraw_object(1, bullet[nr].x, bullet[nr].y, 6);
          undraw_object(1, bullet[nr].prev_x, bullet[nr].prev_y, 6);        
          }
      }
    }
    
  
  //if(digitalRead(4) == HIGH) Serial.println(" 4- strzal");

  
  /*
   * Getting joystinc status
   */
  px = analogRead(2) / 100 - 5;
  py = -(analogRead(1) / 100 - 5);
  /*
   * Getting mouse position and saves to last joystinc position
   * This variables will be used to setup bullet direction
   */
  if((px != 0) || (py != 0))
    {
      last_joy_x = px;
      last_joy_y = py;
    }
  
  /*
   * Movig user 
   * checking if its in screen bounds. If its outside move to another part of screen
   */
  if(x>160) x = 1;
  if(y>130) y = 1;
  if(x<1) x = 160;
  if(y<1) y = 130;
  x = x + px;
  y = y - py;
  draw_object(3, x, y, prev_x, prev_y, 6, 6);

  /*
   * Save previous position
   */
  prev_x = x;
  prev_y = y;


/*
 * Moving bots
 * checking they collision
 * If anyone is in the collision - show game over
 */
for(nr=0; nr<max_botow; nr++)
{
  if(bot[nr].killed == false)
  {
    bot[nr].speed = speed;
    bot[nr].Action(x,y);
    
    draw_object(2, bot[nr].x, bot[nr].y, bot[nr].prev_x, bot[nr].prev_y, bot[nr].my_size, bot[nr].my_prev_size);
    
    if(bot[nr].collision == true)
    {
      // koniec gry - przegrana
      tft.fillScreen(ST7735_BLACK);
      setup_description("GAME OVER. YOU LOST: "+String(max_botow)+"."+String(active_time));
      x = 50;
      y = 50;
      speed = 1;
      active_time = 0;
      bot[nr].collision = false;
      delay(3000);
      tft.fillScreen(ST7735_BLACK);
      max_botow = 4;
      for(nr2=0; nr2<max_botow; nr2++)
      {
        bot[nr2].x = 10;
        bot[nr2].y = 10;
      }
    }
  }
}
  delay(50);
}
