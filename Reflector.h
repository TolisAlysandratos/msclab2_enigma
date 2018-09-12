/* Reflector class declaration */

#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector
{
 public:
  /* Constructor which takes in a vector containing 
     reflector's configuration and stores it in the
     'connections' attribute */
  Reflector(const vector<int> rf_cfg);

  /* Function that takes in an input signal's value
     and outputs the signal according to the mapping
     in the 'connections' vector */
  void transmitSignal(int input, int& output);

 private:
  vector<int> connections;

};

#endif
