/* Main file */

#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

#include "errors.h"
#include "functions.h"
#include "Enigma.h"

int main(int argc, char** argv)
{
  if (argc < MIN_NUM_FILES)
    {
      cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
      return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

  int num_of_rotors;
  if (argc > MIN_NUM_FILES + 1)
    num_of_rotors = (argc - MIN_NUM_FILES - 1);
  else
    num_of_rotors = 0;
  
  vector<int> pb_config;
  vector<int> rf_config;
  vector< vector<int> > rot_config(num_of_rotors);
  vector<int> rot_positions;

  int result = loadConfigFiles(argc, argv, pb_config, rf_config, rot_config, rot_positions);
  if (result != NO_ERROR)
    {
      return result;
    }

  Enigma enigma_1(num_of_rotors, pb_config, rf_config, rot_config, rot_positions);

  char ch_in;
  char ch_out = '\0';
  while (cin >> ch_in)
    {
      if ((isalpha(ch_in) && isupper(ch_in)) || isspace(ch_in))
	{
	  enigma_1.press_key(ch_in, ch_out);
	  cout << ch_out;
	}
      else
	{
	  cerr << ch_in << " is not a valid input character "
	       << "(input characters must be upper case letters A-Z)!" << endl;
	  return INVALID_INPUT_CHARACTER;
	}
    }
  return 0;
}
