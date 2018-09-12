/* Enigma class implementation */

#include <iostream>

using namespace std;

#include "errors.h"
#include "functions.h"
#include "Enigma.h"

Enigma::Enigma(int num, vector<int> pb_cfg, vector<int> rf_cfg,
	       vector< vector<int> > rot_cfg, vector<int> rot_pos)
{
  plugboard_ptr = new Plugboard(pb_cfg);
  reflector_ptr = new Reflector(rf_cfg);
  num_of_rotors = (int)rot_cfg.size();
  rotors_ptr = new Rotor*[num_of_rotors];
  for (int rot = 0; rot < num_of_rotors; rot++)
    rotors_ptr[rot] = new Rotor(rot_cfg[rot], rot_pos, rot);
}

void Enigma::press_key(char input, char& output)
{
  int letter_idx = 0;
  int pb_out;
  int rf_out;
  int rot_in;
  int rot_out;
  int rightmost = num_of_rotors - 1;
  if (num_of_rotors > 0)
    this->turnRotors(rightmost);
  while (letter_idx < ALPHA_SIZE)
    {
      if (ALPHABET[letter_idx] == input)
	{
	  plugboard_ptr->transmitSignal(letter_idx, pb_out);
	  if (num_of_rotors > 0)
	    {
	      rot_in = pb_out;
	      for (int rot_id = (num_of_rotors - 1); rot_id >= 0; rot_id--)
		{
		  rotors_ptr[rot_id]->transmitSignal(rot_out, rot_in, !LEFT_TO_RIGHT);
		  rot_in = rot_out;
		}
	      reflector_ptr->transmitSignal(rot_out, rf_out);
	      rot_in = rf_out;
	      for (int rot_id = 0; rot_id < num_of_rotors; rot_id++)
		{
		  rotors_ptr[rot_id]->transmitSignal(rot_in, rot_out, LEFT_TO_RIGHT);
		  rot_in = rot_out;
		}
	      plugboard_ptr->transmitSignal(rot_out, pb_out);
	      break;
	    }
	  reflector_ptr->transmitSignal(pb_out, rf_out);
	  plugboard_ptr->transmitSignal(rf_out, pb_out);
	  break;
	}
      letter_idx++;
    }
  output = ALPHABET[pb_out];
}

void Enigma::turnRotors(int rightmost_rot)
{
  rotors_ptr[rightmost_rot]->turn();
  if (rightmost_rot == 0)
    return;
  vector<int> notches = rotors_ptr[rightmost_rot]->getNotches();
  int position = rotors_ptr[rightmost_rot]->getPosition();
  for (int i = 0; i < (int)notches.size(); i++)
    {
      if (position == notches[i])
	turnRotors(rightmost_rot - 1);
    }
  return;
}

Enigma::~Enigma()
{
  delete plugboard_ptr;
  delete reflector_ptr;
  for (int i = 0; i < num_of_rotors; i++)
    delete rotors_ptr[i];
  delete [] rotors_ptr;
}
