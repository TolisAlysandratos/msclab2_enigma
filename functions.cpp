/* Implementation file containing function definitions */

#include <iostream>
#include <fstream>

using namespace std;

#include "errors.h"
#include "functions.h"


int loadConfigFiles(int num_input, char** file, vector<int>& pb_cfg, vector<int>& rf_cfg,
		    vector< vector<int> >& rot_cfg, vector<int>& rot_pos)
{
  int result = NO_ERROR;
  result = loadPlugboard(file[1], pb_cfg);
  if (result != NO_ERROR)
    {
      return result;
    }
  result = loadReflector(file[2], rf_cfg);
  if (result != NO_ERROR)
    {
      return result;
    }
  if ((int)rot_cfg.size() > 0)
    {
      int rot = 0;
      for (int i = MIN_NUM_FILES; i <= (num_input - 2); i++)
	{
	  result = loadRotor(file[i], rot_cfg[rot]);
	  if (result != NO_ERROR)
	    {
	      return result;
	    }
	  rot++;
	}
      result = loadRotorPos(file[num_input - 1], rot_pos, (int)rot_cfg.size());
      if (result != NO_ERROR)
	{
	  return result;
	}
    }
  return NO_ERROR;
}


int loadPlugboard(const char* filename, vector<int>& pb_cfg)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cerr << "Failed to open plugboard file: " << filename << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  int num;
  int count = 0;
  while (in_stream >> num)
    {
      if ((num < 0) || (num > 25))
	{
	  in_stream.close();
	  cerr << "Number " << num << " in plugboard file " << filename
	       << " is not a valid index number "
	       << "(numbers must be integers between 0-25)!" << endl;
	  return INVALID_INDEX;
	}
      pb_cfg.push_back(num);
      count++;
    }
  if (!in_stream.eof())
    {
      in_stream.close();
      cerr << "Non-numeric character in plugboard file "
	   << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
  if (count % 2 != 0 || count > 26)
    {
      in_stream.close();
      cerr << "Incorrect number of parameters in plugboard file "
	   << filename << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
  for (int i = 0; (i < (int)pb_cfg.size() - 1); i++)
    {
      for (int j = (i + 1); j < (int)pb_cfg.size(); j++)
	{
	  if (pb_cfg[i] == pb_cfg[j])
	    {
	      cerr << "Impossible plugboard configuration of input " << pb_cfg[i]
		   << " (attempt to map to self or pair with more than one" << endl;
	      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	    }
	}
    }
  in_stream.close();
  return NO_ERROR;
}


int loadReflector(const char* filename, vector<int>& rf_cfg)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cerr << "Failed to open reflector file: " << filename << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  int num;
  int count = 0;
  while (in_stream >> num)
    {
      if ((num < 0) || (num > 25))
	{
	  in_stream.close();
	  cerr << "Number " << num << " in reflector file " << filename
	       << " is not a valid index number "
	       << "(numbers must be integers between 0-25)!" << endl;
	  return INVALID_INDEX;
	}
      rf_cfg.push_back(num);
      count++;
    }
  if (!in_stream.eof())
    {
      in_stream.close();
      cerr << "Non-numeric character in reflector file " << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
  if (count % 2 != 0)
    {
      in_stream.close();
      cerr << "Incorrect (odd) number of parameters in reflector file "
	   << filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
  if (count < 26)
    {
      in_stream.close();
      cerr << "Insufficient number of mappings in reflector file: "
	   << filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
  for (int i = 0; (i < (int)rf_cfg.size() - 1); i++)
    {
      for (int j = (i + 1); j < (int)rf_cfg.size(); j++)
	{
	  if (rf_cfg[i] == rf_cfg[j])
	    {
	      cerr << "Invalid reflector mapping of input " << rf_cfg[i]
		   << " (attempt to map to self or pair with more than one)" << endl;
	      return INVALID_REFLECTOR_MAPPING;
	    }
	}
    }
  in_stream.close();
  return NO_ERROR;
}

int loadRotor(const char* filename, vector<int>& rot_cfg)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cerr << "Failed to open rotor file: " << filename << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  int num;
  int count = 0;
  vector<int> notches;
  while (in_stream >> num)
    {
      if ((num < 0) || (num > 25))
	{
	  in_stream.close();
	  cerr << "Number " << num << " in rotor file " << filename
	       << " is not a valid index number "
	       << "(numbers must be integers between 0-25)!" << endl;
	  return INVALID_INDEX;
	}
      rot_cfg.push_back(num);
      if (count < MAX_CONNECTIONS)
	{
	  for (int i = 0; (i < count); i++)
	    {
	      if (num == rot_cfg[i])
		{
		  in_stream.close();
		  cerr << "Invalid mapping of input " << count
		       << " to output " << num
		       <<" (output " << num << " is already mapped to from input "
		       << i << ")";
		  return INVALID_ROTOR_MAPPING;
		}
	    }
	}
      else
	{
	  notches.push_back(num);
	  for (int i = 0; i < (count - ROTOR_CONNECTIONS); i++)
	    {
	      if (num == notches[i])
		{
		  in_stream.close();
		  cerr << "Invalid rotor configuration: notch " << notches[i]
		       << " at index " << count << " is already given at index "
		       << (i + ROTOR_CONNECTIONS) << endl;
		  return INVALID_ROTOR_MAPPING;
		}
	    }
	} 
      count++;
    }
  if (!in_stream.eof())
    {
      in_stream.close();
      cerr << "Non-numeric character for mapping in rotor file "
	   << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
  if (count < MAX_CONNECTIONS)
    {
      cerr << "Not all inputs mapped in rotor file: " << filename << endl;
      return INVALID_ROTOR_MAPPING;
    }
  if (count == MAX_CONNECTIONS)
    {
      cerr << "No notches contained in rotor file: " << filename << endl;
      return INVALID_ROTOR_MAPPING;
    }
  if (count > (MAX_CONNECTIONS + MAX_NOTCHES))
    {
      in_stream.close();
      cerr << "Number of notches exceeds number of connections in rotor file: "
	   << filename << endl;
      return INVALID_ROTOR_MAPPING;
    }
  return NO_ERROR;
}

int loadRotorPos(const char* filename, vector<int>& rot_pos, int num_of_rotors)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
    {
      cerr << "Failed to open rotor position file: " << filename << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  int num;
  int count = 0;
  while (in_stream >> num)
    {
      rot_pos.push_back(num);
      if ((num < 0) || (num > 25))
	{
	  in_stream.close();
	  cerr << "Number " << num << " in reflector file " << filename
	       << " is not a valid index number "
	       << "(numbers must be integers between 0-25)!" << endl;
	  return INVALID_INDEX;
	}
      count++;
    }
  if (!in_stream.eof())
    {
      in_stream.close();
      cerr << "Non-numeric character in rotor positions file "
	   << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
  if (count < num_of_rotors)
    {
      in_stream.close();
      cerr << "No starting position for rotor " << count
	   << " in rotor position file: " << filename << endl;
      return NO_ROTOR_STARTING_POSITION;
    }
  return NO_ERROR;
}
