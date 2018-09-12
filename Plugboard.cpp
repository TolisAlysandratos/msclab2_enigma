/* Plugboard class implementation */

#include <iostream>
#include <vector>

using namespace std;

#include "Plugboard.h"

Plugboard::Plugboard(const vector<int> pb_cfg)
{
  for (int i = 0; i < (int)pb_cfg.size(); i++)
    connections.push_back(pb_cfg[i]);
}

void Plugboard::transmitSignal(int input, int& output)
{
  output = input;
  for (int i = 0; i < (int)connections.size(); i++)
    {
      if (connections[i] == input)
	{
	  if (i % 2 == 0)
	    output = connections[i + 1];
	  else
	    output = connections[i - 1];
	}
    }
}
