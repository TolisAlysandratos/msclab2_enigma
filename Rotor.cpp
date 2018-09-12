/* Plugboard class implementation */

#include <iostream>
#include <vector>

using namespace std;

#include "Rotor.h"
#include "functions.h"

Rotor::Rotor(const vector<int> rot_cfg, const vector<int> rot_pos, int pos_idx)
{
  for (int i = 0; i < (int)rot_cfg.size(); i++)
    {
      if (i < MAX_CONNECTIONS)
	connections.push_back(rot_cfg[i]);
      else
	notches.push_back(rot_cfg[i]);
    }
  for (int i = 0; i < (int)rot_pos.size(); i++)
    {
      if (i == pos_idx)
	position = rot_pos[i];
    }
}

void Rotor::transmitSignal(int& left_io, int& right_io, bool left_to_right)
{
  if (left_to_right)
    {
      int input = (left_io + position) % ALPHA_SIZE;
      for (int rot_idx = 0; rot_idx < (int)connections.size(); rot_idx++)
	{ 
	  if (connections[rot_idx] == input)
	    right_io = rot_idx;
	}
      // formula for positive modulo
      right_io = ((right_io - position) % ALPHA_SIZE + ALPHA_SIZE) % ALPHA_SIZE;
    }
  else
    {
      int input = (right_io + position) % ALPHA_SIZE;
      left_io = ((connections[input] - position) % ALPHA_SIZE + ALPHA_SIZE) % ALPHA_SIZE;
    }
}

vector<int>& Rotor::getNotches()
{
  return notches;
}

int Rotor::getPosition()
{
  return position;
}

void Rotor::turn()
{
  position = (position + 1) % ALPHA_SIZE;
}
