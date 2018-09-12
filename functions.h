/* Header file containing function declarations and constants */

#include <vector>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

const int MIN_NUM_FILES = 3;
const int MAX_CONNECTIONS = 26;
const int ROTOR_CONNECTIONS = 26;
const int MIN_NOTCHES = 1;
const int MAX_NOTCHES = 26;
const int ALPHA_SIZE = 26;
const char ALPHABET[ALPHA_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const bool LEFT_TO_RIGHT = true;

/* Function that checks the configuration files for errors and stores their content
   using the corresping output parameters; return an error code as soon as an error is found */
int loadConfigFiles(int num_input, char** file, vector<int>& pb_cfg, vector<int>& rf_cfg,
		    vector< vector<int> >& rot_cfg, vector<int>& rot_pos);

/* Function that checks the plugboard configuration file and stores its contents in a vector;
   if an error is found, it returns the appropriate error code */
int loadPlugboard(const char* filename, vector<int>& pb_cfg);

/* Function that checks the reflector configuration file and stores its contents in a vector;
   if an error is found, it returns the appropriate error code */
int loadReflector(const char* filename, vector<int>& rf_cfg);

/* Function that checks the rotor configuration file and stores its contents in a vector;
   if an error is found, it returns the appropriate error code */
int loadRotor(const char* filename, vector<int>& rot_cfg);

/* Function that checks the rotor position configuration file and stores its contents in a vector;
   if an error is found, it returns the appropriate error code */
int loadRotorPos(const char* filename, vector<int>& rot_pos, int num_of_rotors);

#endif
