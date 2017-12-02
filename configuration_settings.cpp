/*
 * file: configuration_settings.cpp
 * author: lvancleef
 * version: 0.4
 * date: 11/30/2017
 *
 * notes: load and exit attempted. 
 */

#include "configuration_settings.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

Configuration_Settings::Configuration_Settings(string name)
{	
	application_name = name;

	maximum_number_transitions = 1;
	maximum_number_characters = 32;
	complete_paths = false;
	changed = false;

	changed = load(name);
}

bool Configuration_Settings::load(string name)
{
	application_name = name;
	string pda_file = name + ".cfg";
	
	ifstream config_file;

	config_file.open(pda_file.c_str());

	if(!config_file.is_open())
	{
		return false;
	}

	// if settings successfully set from file, toggle
	bool transitions_set = false;
	bool chars_set = false;
	bool paths_set = false;

	string line;
	string value;
	int int_value = 0;

	size_t found;
	bool found_one = false;
	string found_keyword = "";

	bool error_converting = false;
	
	// attempt to read in lines
	while (getline(config_file, line))
	{	
		// does any keyword exist in line

		found = To_Upper(line).find("MAXIMUM_TRANSITIONS")
		if (found!=string::npos))
		{
			found_keyword = "MAXIMUM_TRANSITIONS";
			found_one = true;
		}

		found = To_Upper(line).find("MAXIMUM_CHARACTERS") 
		if (found!=string::npos)
		{
			// if keyword has already been set, line is invalid
			if (found_keyword.compare("") != 0)
			{
				found_one = false;
			}
			else
			{
				found_keyword = "MAXIMUM_CHARACTERS";
				found_one = true;
			}
		}
		
		found = To_Upper(line).find("COMPLETE_PATHS") 
		if (found!=string::npos)
		{
			// if keyword has already been set, line is invalid
			if (found_keyword.compare("") != 0)
			{
				found_one = false;
			}
			else
			{
				found_keyword = "COMPLETE_PATHS";
				found_one = true;
			}
		}

		if (found_one)
		{
			// does = exist in line
			found = line.find("=")
			if (found != string::npos)
			{
				// get what should be the value after the "="
				value = line.substr(found+1);

				if (found_keyword.compare("MAXIMUM_TRANSITIONS") == 0 ||
					found_keyword.compare("MAXIMUM_CHARACTERS") == 0)
				{
					try
					{
						int_value = stoi(value);
					}
					catch(...)
					{
						// error converting
						error_converting = true;
					}

					if (!error_converting)
					{
						// value has to be greater than 0
						if (int_value > 0)
						{
							if (found_keyword.compare("MAXIMUM_TRANSITIONS") == 0 &&
								transitions_set == false)
							{
								maximum_number_transitions = int_value;
								transitions_set = true;
							}	
							else if (chars_set == false)
							{
								maximum_number_characters = int_value;
								chars_set = true;
							}
						}
					}

				}
				else if (paths_set == false)
				{ // MIGHT need to edit this for situations such as YES'M or NOPE. 
					// since those situations would not be valid

					found = value.find("YES")
					if (found != str::npos)
					{
						complete_paths = true;
						paths_set = true;
					}

					if (paths_set == false)
					{
						found = value.find("NO")
						if (found != str::npos)
							paths_set = true;
					}
				}
			}
		}

		// reset variables
		line = "";	
		value = "";
		int_value = 0;
		found = 0;
		found_one = false;
		found_keyword == "";
		error_converting = false;
	}


	if (transitions_set &&
		chars_set &&
		paths_set)
		return false;

	return true;
}

int Configuration_Settings::get_maximum_transitions() const
{
	return maximum_number_transitions;
}

int Configuration_Settings::get_maximum_characters() const
{
	return maximum_number_characters;
}

bool Configuration_Settings::get_complete_paths() const
{
	return complete_paths;
}

string Configuration_Settings::complete_paths_string() const
{
	if (complete_paths)
		return "YES";
	else
		return "NO";
}

void Configuration_Settings::set_command()
{
	string value;
	int result;

	cout << "Maximum Transitions[" << maximum_number_transitions << "]: ";
	cin.ignore();

	if (getline(cin, value) and value.empty())
		return;

	stringstream convert(value);

	if ( !(convert >> result) )
   		result = 0;

   	if ((result > 0))
   	{
   		cout << "Maximum transitions changed from " << maximum_number_transitions << " to " << result << "." << endl;
   		maximum_number_transitions = result;

   		changed = true;
   	}
   	else
   	{
   		cout << "Input '" << value << "' entered is not a positive integer." << endl;
   	}

   	return;
}

void Configuration_Settings::truncate_command()
{
	string value;
	int result;

	cout << "Maximum Characters Before Truncation[" << maximum_number_characters << "]: ";

	cin.ignore();

	if (getline(cin, value) and value.empty())
		return;

	stringstream convert(value);

	if ( !(convert >> result) )
   		result = 0;

   	if ((result > 0))
   	{
   		cout << "Maximum characters changed from " << maximum_number_characters << " to " << result << "." << endl;
   		maximum_number_characters = result;

   		changed = true;
   	}
   	else
   	{
   		cout << "Input '" << value << "' entered is not a positive integer." << endl;
   	}

   	return;
}

void Configuration_Settings::display_command()
{
	if(complete_paths)
	{
   		cout << "Complete Paths is now FALSE." << endl;
   		complete_paths = false;
   	}
   	else
   	{
   		cout << "Complete Paths is now TRUE." << endl;
   		complete_paths = true;
   	}

   	changed = true;

	return;
}

void Configuration_Settings::exit_command()
{

	if(changed)
	{
		ofstream config_file;
		string pda_file = application_name + ".cfg";

		config_file.open(pda_file.c_str(), ios::out | ios::trunc);

		if(!config_file.is_open())
		{
			cout << "Error writing to Configurations Settings file." << endl;
		}
		else
		{
			config_file << "MAXIMUM_TRANSITIONS=" << maximum_number_transitions << endl;
			config_file << "MAXIMUM_CHARACTERS=" << maximum_number_characters << endl;
			config_file << "COMPLETE_PATHS=" << complete_paths_string() << endl;

			config_file.close();

			cout << "Configurations Settings file successfuly updated." << endl;
		}
	}

	exit(0);
}

