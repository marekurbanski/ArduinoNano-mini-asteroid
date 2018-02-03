/*
 *
 * Librarby for mini Asteroid - Arduino NANO
 *
 * Author: Marek Urbanski
 * e-mail: marek@www2.pl
 *
 * https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
 */


#include "Arduino.h"
#include "Opponent.h"

Opponent::Opponent()
{
// default start position
// variables defined
 x = 10;
 y = 10 ;
 collision = false;
 killed = false;
 speed = 2;
 dirrection_x = random(0,speed);
 dirrection_y = random(0,speed);
 my_size = random(6,15);
}

void Opponent::Action(byte u_x, byte u_y)
{
  // checking collision
  	if(
          ((u_x + 3) > (x - my_size/2))
          && ((u_x - 3) < (x + my_size/2))
          && ((u_y + 3) > (y - my_size/2))
          && ((u_y - 3) < (y + my_size/2))
      )
  	{
  		collision = true;
  	}
	prev_x = x;
	prev_y = y;

  // move opponent
  if(random(0,20)<3)
    {
  	px = random(-speed,speed-dirrection_x);
  	py = random(-speed,speed-dirrection_y);
    }
	if(x>160) x = 1;
	if(y>130) y = 1;
	if(x<1) x = 160;
	if(y<1) y = 130;
	x = x - px;
	y = y + py;
}
