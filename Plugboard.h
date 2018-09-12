/* Plugboard class declaration */

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard
{
 public:
  /* Constructor which takes in a vector containing 
     plugboard's configuration and stores it in the
     'connections' attribute */
  Plugboard(const vector<int> pb_cfg);

  /* Function that takes in an input signal's value
     and outputs the signal according to the mapping
     in the 'connections' vector */  
  void transmitSignal(int input, int& output);
  
 private:
  vector<int> connections;

};

#endif
