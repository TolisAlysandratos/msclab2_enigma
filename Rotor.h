/* Rotor class declaration */

#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
 public:
  /* Constructor which takes in a vector containing 
     rotor's mapping and notches and stores the first in
     'connections' and the latter in the 'notches' attributes;
     it also takes a vector containing rotor positions and stores
     the position according to the rotor's place on the enigma machine */
  Rotor(const vector<int> rot_cfg, const vector<int> rot_pos, int pos_idx);

  /* Function that takes in an input signal's value
     and outputs the signal according to the mapping
     in the 'connections' vector */
  void transmitSignal(int& left_io, int& right_io, bool left_to_right);

  /* Function that returns the private attribute 'notches' */
  vector<int>& getNotches();

  /* Function that return the private attribute 'position' */
  int getPosition();

  /* Function that increments the rotor's position by one */
  void turn();
  
 private:
  vector<int> connections;
  vector<int> notches;
  int position;
};

#endif
