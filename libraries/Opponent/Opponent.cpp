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
 randomSeed(analogRead(2));
 x = random(10,150);
 y = random(10,130);

 collision = false;
 killed = false;
 speed = 2;
 min_size = 5;
 max_size = 20;
 dirrection_x = random(0,speed);
 dirrection_y = random(0,speed);
 my_size = random(min_size,max_size);
 my_prev_size = my_size;
 size_up = true;
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

  /*
   * Change size of the Opponent
   *
   */
  my_prev_size = my_size;
  //if(random(1,10) >5)
  if(size_up == true)
    my_size = my_size + 1;
  else
    my_size = my_size - 1;

  if(my_size > max_size)
      {
      size_up = false;
      my_size = max_size;
      }

  if(my_size < min_size)
      {
      size_up = true;
      my_size = min_size;
      }

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
