/*
 *
 * Librarby for mini Asteroid - Arduino NANO
 *
 * Author: Marek Urbanski
 * e-mail: marek@www2.pl
 *
 * https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
 */

#ifndef Opponent_h
#define Opponent_h
#include "Arduino.h"

class Opponent
{
  public:
    Opponent();
    void Initialize();
    void Action(byte u_x, byte u_y);
    byte x;
    byte y;
	  byte prev_x;
	  byte prev_y;
	  boolean collision;
    boolean killed;
    byte speed;
    byte my_size;
    byte my_prev_size;
    byte min_size;
    byte max_size;
    boolean size_up;
  private:
	  byte px;
	  byte py;
	  byte dirrection_x;
	  byte dirrection_y;
};

#endif
