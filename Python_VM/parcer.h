#include <iostream>
#include <string>
#include <list>
#include "scanner.h"

using namespace std ;

 // function proto tybe for recursion
void single_input();
void file_inpute();
void eval_inpute();
void decorator();
void decorators();
void async_funcdef();
void funcdef();
void parameters();
void typedargslist();
void tfpdef();
void varargslist();
void vfpdef();
void stmt();
void simple_stmt();
void small_stmt();
void expr_stmt();
void testlist_star_expr();
void augassign();
void del_stmt();
void pass_stmt();
void flow_stmt();
void break_stmt();
void continue_stmt();
void return_stmt();
void yield_stmt();
void raise_stmt();
void import_stmt();
void import_name();
void import_from();
void import_as_name();
void dotted_as_name();	
void import_as_names();
void dotted_as_names();
void dotted_name();
void global_stmt();
void nonlocal_stmt();
void assert_stmt();
void compound_stmt();
void async_stmt();
void if_stmt();
void while_stmt();
void for_stmt();
void try_stmt();
void with_stmt();
void with_item();
void except_clause();

void suite();

void test();
void test_nocond();


void lambdef();
void lambdef_nocond();
void or_test();
void and_test();
void not_test();
void comparison();
void comp_op();
void star_expr();
void expr(); 
void xor_expr();
void and_expr();
void shift_expr();
void arith_expr();
void term();
void factor();
void power();
void atom_expr();
void atom();
void testlist_comp();
void trailer();
void subscriptlist();
void subscript();
void sliceop();
void exprlist();
void testlist();
void dictorsetmaker();
void classdef();
void arglist();
void argument();
void comp_iter();
void comp_for();
void comp_if();
void encoding_decl();
void yield_expr(); 
void yield_arg();

void NAME();


void NEWLINE();
void init();
void error(void);
bool match (string t);
void unmatch();

// global variable
list<string> kk;

string token;
string token_value;
ifstream input_file ;
ifstream value_file ;
string value[300];
string token_value_list[300];

int i=0;

int n=0;


ofstream parcer_output;
ofstream c_out;
/*
static enum StringValue { number, identifier, until, End, read ,IF,repeat,write ,bracket };
static map< string, StringValue> terminal;
*/
//////////////////////////////////////////////////////
string pythonWord[]={"else","for","yield","if","else","in","not","None","is",
		  "True","False","del","pass","break","continue","raise","import","global","nonlocal",
		  "assert","try","finally","except","as", "from","or","and","lambda", 
		  "while","return","class"};



// variable for type adding 


string stmt_array[300];
int p_stmt_array=0;

string defined_int_array[50];
int p_defined_int_array=0;

string defined_string_array[50];
int p_defined_string_array=0;

string undefined_NAME_arry[5];
int p_undefined_NAME_array=0;

string function_return_type=" void ";


void add_in_stmt_array(string token);
bool check_if_defined; // moken yb2aarray
bool check_if_in_defined_array(string NAME_value);
void add_in_undefined_array(string Name);
void insert_type_in_stmt_arry(int position, string type);
string check_type(string value);
void print_stmt_array(); 
void change_from_undefined_to_defined(int position_of_undefined_array,string type);




