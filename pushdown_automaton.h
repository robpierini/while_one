#ifndef Pushdown_Automaton_H
#define Pushdown_Automaton_H

#include "input_alphabet.h"
#include "stack_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "instantaneous_description.h"
#include "configuration_settings.h"

#include <string>

using namespace std;

class Pushdown_Automaton{
private:
    Input_Alphabet input_alphabet;
    Stack_Alphabet stack_alphabet;
    Transition_Function transition_function;
    States states;
    Final_States final_states;

    string initial_state;
    string name;
    string original_input_string
    bool valid;
    bool used;
    bool running;
    bool accepted;
    bool rejected;
    string initial_state;
    char start_character;
    int number_of_transitions;
    int number_of_crashes;
    
    //static Configuration_Setting_Pointer configuration_setting_pointer;
    
public:
    Pushdown_Automaton();
    
    Bool is_accepted(Instantaneous_Description instantaneous_description, int number_in_current_path);
    static void Link(const Configuration_Settings configration_settings);
    load(in definition_file_name:string);
    bool PDA_main(Configuration_Settings configuration_settings);
    string perform_transition(Instantaneous_description instantaneous_description, int number_of_transition_performed);
    bool is_accepted(Instantaneous_Description instantaneous_description, int number_in_current_path);
    void commands();
    bool is_valid_input_string(string value);
    void print_id(Instantaneous_description instantaneous_description);
    void initialize_string_list();
    void help_command();
    void show_command();
    void view_command();
    void list_command();
    void insert_command();
    void delete_command(int value);
    void sort_command();
    void set_command();
    void close_command();
};

//typedef pushdown_automaton *pushdown_automaton;
#endif