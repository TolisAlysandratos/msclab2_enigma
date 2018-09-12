/* Enigma class declaration */

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

#ifndef ENIGMA_H
#define ENIGMA_H

class Enigma
{
 public:
  /* Constructor that creates a simulation of an enigma machine;
     it takes as input vector containing configuration of plugboard,
     reflector and possible rotors and their initial position file;
     it then calls the constructors for the corresponding classes accordingly */
  Enigma(int num, vector<int> pb_cfg, vector<int> rf_cfg,
	 vector< vector<int> > rot_cfg, vector<int> rot_pos);

  /* Deconstructor for Enigma class */
  ~Enigma();

  /* Function that takes as input a single upper case alphabetical character
     and encrypts it according to the set-up of the enigma machine
     and outputs th corresponding encrypted character */
  void press_key(char input, char& output);
  
 private:
  int num_of_rotors;
  Plugboard* plugboard_ptr;
  Reflector* reflector_ptr;
  Rotor** rotors_ptr;

  /* Function used called by the 'press_key()' public function to help it
     update the rotors position (if any rotors are used in the enigma machine) */
  void turnRotors(int rightmost_rot);
  
};

#endif
