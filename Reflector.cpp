/* Reflector class implementation */

#include <iostream>
#include <vector>

using namespace std;

#include "Reflector.h"

Reflector::Reflector(const vector<int> rf_cfg)
{
  for (int i = 0; i < (int)rf_cfg.size(); i++)
    connections.push_back(rf_cfg[i]);
}

void Reflector::transmitSignal(int input, int& output)
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
