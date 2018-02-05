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
#include "Bullet.h"

Bullet::Bullet()
{
 x = 10;
 y = 10;
 dirrection_x = 0;
 dirrection_y = 0;
 active = false;
 visible = true;
}

void Bullet::Fire(byte u_x, byte u_y, byte kier_x, byte kier_y)
{
  if(active == false)
    {
    x = u_x;
    y = u_y;
    dirrection_x = - kier_x;
    dirrection_y = - kier_y;
    active = true;
    visible = true;
    }

}

void Bullet::Action(byte u_x, byte u_y)
{
if(active == true)
  {
  	if(x>165) active = false;
  	if(y>139) active = false;
  	if(x<1) active = false;
  	if(y<1) active = false;
    if (active == true)
      {
      prev_x = x;
    	prev_y = y;
    	x = x - dirrection_x;
    	y = y + dirrection_y;
      }
  }
}
