/*
 *
 * Librarby for mini Asteroid - Arduino NANO
 *
 * Author: Marek Urbanski
 * e-mail: marek@www2.pl
 *
 * https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
 */

#ifndef Bullet_h
#define Bullet_h
#include "Arduino.h"

class Bullet
{
  public:
    Bullet();
    void Action(byte u_x, byte u_y);
    void Fire(byte u_x, byte u_y, byte kier_x, byte kier_y);
    byte x;
    byte y;
	  byte prev_x;
	  byte prev_y;
    boolean active;
  private:
	  byte dirrection_x;
	  byte dirrection_y;
};

#endif
