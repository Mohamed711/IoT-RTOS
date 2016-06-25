

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
void subscriptlist(){cout<<"not support"<<endl;}
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
//////////////////////////////////////////////////////








////////////////////////




static enum StringValue { number, identifier, until, End, read ,IF,repeat,write ,bracket };
static map< string, StringValue> terminal;
//////////////////////////////////////////////////////
string pythonWord[]={"else","for","yield","if","then","else","end","repeat","until" ,
		                  "read", "write","while","return","in","not"};
	
// read all file and put it in one list
void init()
{
	string line;
	int n=0;
	string x ;
	input_file.open("parcer_in.txt");

	while(!input_file.eof()){

		getline(input_file,line);

		stringstream mycin (line) ;

		while (mycin >>x)
		{
			value[n++]= x;

		}

	}
	input_file.close();
////////////////////scanner_value file ///////////////////////
	string vline;
	int vn=0;
	string vx ;
	value_file.open("scanner_value.txt");

	while(!value_file.eof()){

		getline(value_file,vline);

		stringstream mycin (vline) ;

		while (mycin >>vx)
		{
			token_value_list[vn++]= vx; /////////////

		}

	}
	value_file.close();



}

/////////////////////////////
void error(void)
{
	cout<<"match ERROR"<<endl;
	parcer_output<<"match ERROR"<<endl;
	system ("pause");
	exit(1);

}
/////////////////////////////
bool match (string t)
{  
	if (!(token.compare(t)))
	{  
		bool printed=false;
		if (token=="def"){c_out<<" void ";}
		else if(token!="NAME" && token!="NUMBER"&&token != ":" && token!="NEWLINE" && token!="INDENT" && token!="DEDENT"&&token!="def")
		{ 
			for(int k=0;k <17 ;k++)
				{  
					if(token==pythonWord[k])
					{
						c_out<<" "<<token<<" ";
						printed=true;
						break;
					}

				}

			
		}
		else if(token=="NAME"||token=="NUMBER")
		{
			printed=true;
			token_value=token_value_list[i];
			c_out<<""<<token_value<<"";
		}
		if(printed==false && token != ":" && token!="NEWLINE" &&
			token!="INDENT" && token!="DEDENT"&&token!="def")
		{c_out<<token;}

		token=value[++i];	
		return true;
	}
	else 
	{
		error();
		return false;
	}

}
/////////////////////////////////////////////////
void unmatch()
{
	i--;
	token=value[i];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void NEWLINE() { match("NEWLINE");}
void NAME() {match("NAME");}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void single_input()
{
	if (token=="NEWLINE"){match("NEWLINE");}
	else if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" ||token=="("
		    ||token=="["||token=="{"||token=="NAME"||token=="NUMBER"||token=="STRING"
			||token=="..."||token=="None"||token=="True"||token=="False"||token=="*"||token=="del"
			||token=="pass"||token=="break"||token=="continue"||token=="return"||token=="yield"
			||token=="raise"||token=="from"||token=="import"||token=="global"||token=="nonlocal"
			||token=="assert")
	{
		simple_stmt();
	}
	else if(token=="if"||token=="while"||token=="for"||token=="try"||token=="with"||token=="def"||
		token=="class"||token=="@"||token=="ASYNC")
	{
		compound_stmt();
		match("NEWLINE");
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void file_input()
{
	// don't know what is the mean of ENDMARKER

	while(token=="NEWLINE"||token!="ENDMARKER")
	{
		if(token=="NEWLINE"){match("NEWLINE");}
		else if(token !="ENDMARKER"){stmt(); }

	}
	match("ENDMARKER");

}
////////////////////////////////////////////////////////////////////////////
void eval_input()
{
	testlist();
	while(token=="NEWLINE")
	{
	match("NEWLINE");
	}
	match("ENDMARKER");
}

////////////////////////////////////////////////////////////////////////////////////////////
void funcdef()
{
	cout<<"start funcdef"<<endl;
	match("def");
	match("NAME");
	parameters();
	if (token=="->")
	{
		test();
	}
	match(":");
	suite();
	cout<<"eennnnnnnnnnnnnnnnnnnnnnnnnnnd of funcdef"<<endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void parameters()
{
	match("(");
	if (token=="NAME")
	{
	typedargslist();
	}
	match(")");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void typedargslist()
{
	cout<<"typedargslist start"<<endl;
	tfpdef();
	if(token=="=")
	{
		match("=");
		test();
	}
	while(token==",")
	{
		match(",");
		tfpdef();
		if(token=="=")
		{
			match("=");
			test();
		}
	}
	if(token==",")
	{ 
		
		match(",");
		///////////repeted////
		if(token=="*")
		{
			
			match("*");
			if(token=="NAME")
			{
				tfpdef();
			}
			while(token==",")
			{
				match(",");
				tfpdef();
				if(token=="=")
				{
					match("=");
					test();
				}

			}
			if(token==",")
			{
				match(",");
				match("**");
				tfpdef();
			}

		}
		else if (token=="**")
		{
			match("**");
			tfpdef();
		}
		//////////////////
	}
	else if(token=="*")
	{
////////
		match("*");
			if(token=="NAME")
			{
				tfpdef();
			}
			while(token==",")
			{
				match(",");
				tfpdef();
				if(token=="=")
				{
					match("=");
					test();
				}

			}
			if(token==",")
			{
				match(",");
				match("**");
				tfpdef();
			}

		}
		else if (token=="**")
		{
			match("**");
			tfpdef();
		}
///////////
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void varargslist()
{
	vfpdef ();
	if(token=="=")
	{
		match("=");
		test();
	}
	while(token==",")
	{
		match(",");
		vfpdef ();
		if(token=="=")
		{
			match("=");
			test();
		}
	}
	if(token==",")
	{ 
		
		match(",");
		///////////repeted////
		if(token=="*")
		{
			
			match("*");
			if(token=="NAME")
			{
				vfpdef();
			}
			while(token==",")
			{
				match(",");
				vfpdef();
				if(token=="=")
				{
					match("=");
					test();
				}

			}
			if(token==",")
			{
				match(",");
				match("**");
				vfpdef();
			}

		}
		else if (token=="**")
		{
			match("**");
			vfpdef();
		}
		//////////////////
	}
	else if(token=="*")
	{
////////
		match("*");
			if(token=="NAME")
			{
				vfpdef();
			}
			while(token==",")
			{
				match(",");
				vfpdef();
				if(token=="=")
				{
					match("=");
					test();
				}

			}
			if(token==",")
			{
				match(",");
				match("**");
				vfpdef();
			}

		}
		else if (token=="**")
		{
			match("**");
			vfpdef();
		}
///////////
	
}
//////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void tfpdef()
{
	match("NAME");
	if(token==":")
	{
		match(":");
		test();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void vfpdef()
{
	match("NAME");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void stmt()
{
	if(token=="del"||token=="pass"||token=="break"||token=="continue"||token=="return"||token=="yield"||
		token=="raise"||token=="from"||token=="import"||token=="global"||token=="nonlocal"||token=="assert"
       ||token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False"||token=="*")
	{
		simple_stmt();
	}
	else if(token=="if"||token=="while"||token=="for"||token=="try"||token=="with"||token=="def"||
		token=="class"||token=="@"||token=="ASYNC")
	{
		compound_stmt();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void simple_stmt()
{
	small_stmt();
	while(token==";")
	{
		match(";");
		if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False"||token=="*"||token=="del"
	   ||token=="pass"||token=="break"||token=="continue"||token=="return"||token=="yield"
	   ||token=="raise"||token=="from"||token=="import"||token=="global"||token=="nonlocal"
	   ||token=="assert")
		{
			small_stmt();
		}
		else
		{
			token=value[--i];
		}
	}
	if(token==";")
	{
		match(";");
	}
	NEWLINE();
}
///////////////////////////////////////////////////////////////////////////////////////////////
void small_stmt()
{
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False"||token=="*")
	{
		expr_stmt();
	}
	else if(token=="del"){del_stmt();}
	else if(token=="pass"){pass_stmt();}
	else if(token=="break"||token=="continue"||token=="return"||token=="raise"||token=="yield"){flow_stmt();}
	else if(token=="import"){/*import_stmt();*/}
	//else if(token=="global"){global_stmt();}
	//else if(token=="nonlocal"){nonlocal_stmt();}
	//else if(token=="assert"){assert_stmt();}
	
	c_out<<" ; "<<endl;

}
///////////////////////////////////////////////////////////////////////////////////////
void expr_stmt()
{
	testlist_star_expr();
	if (token=="+="||token=="-="||token=="*="||token=="@="||token=="/="||
		token=="%="||token=="&="||token=="|="||token=="^="||token=="<<="||
		token==">>="||token=="**="||token=="//=")
	{
		augassign();
		if(token=="yield")
		{
			yield_expr();
		}
		else if (token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
		{
			testlist();
		}

	}
	else if(token=="=")
	{
		while(token=="=")
		{
			match("=");
			if(token=="yield")
			{
				yield_expr();
			}
			else if (token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False"||token=="*")
			{
				testlist_star_expr();
			}
		}

	}

}
////////////////////////////////////////////////////////////////////////////////////////
void testlist_star_expr()
{ 
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
	{
		test();
	}
	else if (token=="*")
	{
		star_expr();
	}
	while(token==",")
	{
		match(",");
		if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
		{
			test();
		}

	
		else if (token=="*")
		{
			star_expr();
		}


	}
	if(token==",")
	{
		match(",");
	}
}
///////////////////////////////
void star_expr()
{
	match("*"); expr();
}
/////////////////////////////////////////////////////////////
void testlist()
{
	test();
	while(token==",")
	{
		match(",");
		if (token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
		{
			test();
		}
	}


}
/////////////////////////////////////////////////////////////////////////////////////
void augassign()
{
	match(token);///mo2ktan
}
////////////////////////////////////////////////////////
void del_stmt()
{
	match("del");
	exprlist();

}
///////////////////////////////////////////////////////
void pass_stmt()
{
	match("pass");
}

///////////////////////////////////////////////////////////////
void flow_stmt()
{
	if (token=="break") {break_stmt();}
	else if(token=="continue"){continue_stmt();}
	else if (token=="return"){return_stmt();}
	else if (token=="raise"){raise_stmt();}
	else if (token=="yield"){yield_stmt();}

}
/////////////////////////////////////////////////////////////////
void break_stmt(){match("break");}
/////////////////////////////////////////////////////////////////
void continue_stmt(){match("continue");}
/////////////////////////////////////////////////////////////
void return_stmt()
{
	match("return");
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
	{
		testlist();
	}

}
///////////////////////////////////////////////////////////
void yield_stmt(){yield_expr();}

///////////////////////////////////////////////////////////
void raise_stmt()
{
	match("raise");
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
	{
		test();
		if(token=="from")
		{
			match("from");
			test();
		}
	}
}
////////////////////////////////////////////////////////////////////////
void import_stmt()//mosh kmlaaa
{
	if (token=="import"){/*import_name();*/}
	//else if()
}
////////////////////////////////////////////////////
void compound_stmt()
{
	if (token=="if"){if_stmt();}
	else if(token=="while"){while_stmt();}
	else if (token=="for"){for_stmt();}
	else if (token=="try"){/*try_stmt();*/}
	else if (token=="with"){/*with_stmt();*/}
	else if (token=="def"){funcdef();}
}
/////////////////////////////////////////////
void if_stmt()
{
	match("if");
	c_out<<"(";
	test();
	c_out<<")";
	match(":");
	suite();
	while(token=="elif")
	{
		match("elif");
		c_out<<"(";
		test();
		c_out<<")";
		match(":");
		suite();
	}
	if (token=="else")
	{
		match("else");
		match(":");
		suite();
	}
}
//////////////////////////////////////////////////////////////////////
void while_stmt()
{
	match("while");
	c_out<<"(";
	test(); 
	c_out<<")";
	match(":");
	suite();
	
	if(token=="else")
	{
		
		match("else");
		match(":");
		suite();
		
	}
}

///////////////////////////////////////////////
void for_stmt()
{
	match("for");
	c_out<<"(";
	exprlist();
	match("in");
	testlist();
	c_out<<")";
	match(":");
	suite();
	if(token=="else")
	{
		match("else");
		match(":");
		suite();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
void suite()
{
	c_out<< "  {  "<<endl;
	 if (token=="NEWLINE")
	{
		match("NEWLINE");
		match("INDENT");
		stmt();
		while(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" ||token=="("
		    ||token=="["||token=="{"||token=="NAME"||token=="NUMBER"||token=="STRING"
			||token=="..."||token=="None"||token=="True"||token=="False"||token=="*"||token=="del"
			||token=="pass"||token=="break"||token=="continue"||token=="return"||token=="yield"
			||token=="raise"||token=="from"||token=="import"||token=="global"||token=="nonlocal"
			||token=="assert"||token=="if"||token=="while"||token=="for"||token=="try"||token=="with"||token=="def"||
		token=="class"||token=="@"||token=="ASYNC" ) 
		{
			stmt();
		}
		//if(token=="DEDENT")
			match("DEDENT"); ///////////////////t2leeeeeeeeeeeeeeef
		//else if (token=="NEWLINE") match("NEWLINE");/////////////

	}
	 else if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" ||token=="("
		    ||token=="["||token=="{"||token=="NAME"||token=="NUMBER"||token=="STRING"
			||token=="..."||token=="None"||token=="True"||token=="False"||token=="*"||token=="del"
			||token=="pass"||token=="break"||token=="continue"||token=="return"||token=="yield"
			||token=="raise"||token=="from"||token=="import"||token=="global"||token=="nonlocal"
			||token=="assert"  )
	 {
		 simple_stmt();
	 }
	 
		 

	 c_out<<" } "<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////
void test()
{
	
	cout<<"test start"<<endl;
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
  { 
	or_test();
	if(token=="if")
	{
		match("if");
		or_test();
		match("else");
		test();
	}
  }
else if(token=="lambda")
{
	lambdef();
}


}

///////////////////////////////////////////////////////////////////////
void test_nocond()
{
	if (token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		or_test();
	}
	else if (token=="lambda"){lambdef_nocond();}
}
//////////////////////////////////////////////////////////////////
void lambdef()
{
	match("lambda");
	if(token=="NAME"||token=="*"||token=="**")
	{
		varargslist();
	}
	match(":");
	test();
}
///////////////////////////////////////////////////////////////////
void lambdef_nocond()
{
	match("lambda");
	if(token=="NAME"||token=="*"||token=="**")
	{
		varargslist();
	}
	match(":");
	test_nocond();
}
////////////////////////////////////////////////////////////////////
void or_test()
{
	and_test();
	while(token=="or")
	{
		match("or");
		and_test();
	}
}
/////////////////////////////////////////////////////
void and_test()
{
	not_test();
	while(token=="and")
	{
		match("and");
		not_test();
	}

}
//////////////////////////////////////////////////////////
void not_test()
{
	if(token=="not")
	{
		match("not");
		not_test();
	}
	else if(token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		comparison();
	}
}
//////////////////////////////////////////////////////////////////
void comparison()
{
	cout<<"comparision is ok"<<endl;
	expr();
	while(token=="<"||token==">"||token=="=="||token==">="||token=="<="||token=="<>"||token=="!="
		||token=="in"||token=="not"||token=="is"||token=="is")
	{
		comp_op();
		expr();
	}
}
/////////////////////////////////////////////////////////////////////////
void comp_op()
{
	if(token=="<") {match("<");}
	if(token==">") {match(">");}
	if(token=="==") {match("==");}
	if(token==">=") {match(">=");}
	if(token=="<=") {match("<=");}	
	if(token=="<>") {match("<>");}
	if(token=="!=") {match("!=");}
	if(token=="in") {match("in");}
	if(token=="not") {match("not");match("in"); }
	
	if(token=="is") 
	{
		match("is");
		if(token=="not") {match("not");}
	}

}
/////////////////////////////////////////////////////////
void expr()
{
	xor_expr();
	while(token=="|")
	{
		match("|");
		xor_expr();
	}
}
////////////////////////////////////////////////////////////////////////////
void xor_expr()
{
	and_expr();
	while(token=="^")
	{
		match("^");
		and_expr();
	}
}
////////////////////////////////////////////////////////////////
void and_expr()
{
	shift_expr();
	while (token=="&")
	{
		match("&");
		shift_expr();
	}
}
/////////////////////////////////////////////////////////////////
void shift_expr()
{
	arith_expr();
	while(token==">>"||token=="<<")
	{
		if(token==">>"){match(">>");arith_expr();}
		if(token=="<<"){match("<<");arith_expr();}

	}
}
//////////////////////////////////////////////////////////////////
void arith_expr()
{
	term();
	while(token=="+"||token=="-")
	{
		if(token=="+"){match("+");term();}
		if(token=="-"){match("-");term();}
	}
}
/////////////////////////////////////////////////////////////////////
void term()
{
	cout<<"term is start"<<endl;
	factor();
	while(token=="*"||token=="@"||token=="/"||token=="%"||token=="//")
	{
		match(token);
		factor();

	}
}
////////////////////////////////////////////
void factor()
{
	cout<<"factor"<<endl;
	if(token=="+"||token=="-"||token=="~")
	{
		match(token);
		factor();
	}
	else if (token=="AWAIT" 
       ||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
	   ||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		power();
	}
}
////////////////////////////////////////////////////////////////////////////
void power()
{
	atom_expr();
	if(token=="**")
	{
		match("**");
		factor();
	}
}
////////////////////////////////////////////////////////////////
void atom_expr()
{
	cout<<"atom_expr start"<<endl;
	if(token=="AWAIT")
	{
		match("AWAIT");
	}
	atom();
	while(token=="("||token=="["||token==".")
	{
		trailer();
	}
}
///////////////////////////////////////////////////////////////////////
void atom()
{
	cout<<"atom"<<endl;
	if(token=="(")
	{
		match("(");
		if(token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
		{
			testlist_comp();
		}
		else if (token=="yield")
		{
			yield_expr();
		}
		match(")");
	}
	else if(token=="[")
	{
		match("[");
		if(token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
		{
			testlist_comp();
		}
		match("]");

	}
	else if(token=="{")
	{
		match("{");
		if (token!="}")  ///mo2ktaaaaaaan
		{
			dictorsetmaker();
		}
		match("}");
	}
	else if(token=="NAME"){match("NAME");}
	else if(token=="NUMBER"){match("NUMBER");}
	else if(token=="STRING"){match("STRING"); while(token=="STRING"){match("STRING");}}
	else if(token=="..."){match("...");}
	else if(token=="None"){match("None");}
	else if(token=="True"){match("True");}
	else if(token=="False"){match("False");}
	

}
///////////////////////////////////////////////////////////////////////
void trailer()
{
	if(token=="(")
	{
		match("(");
		if (token=="*"||token=="**"||token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
		{
			arglist();
		}
		match(")");
	}
	else if (token=="[")
	{
		match("[");
		subscriptlist();
		match("]");
	}
	else if (token==".")
	{
		match(".");
		NAME();
	}
}
///////////////////////////////////////////////////////////////////////
void testlist_comp()
{
	if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		test();
		while(token==","||token=="for" )
		{
			if(token=="for"    /*com_for*/)
			{
				comp_for();
			}
			else if(token==",")
			{
				match(",");
				if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	
				{
					test();
				}
				else if (token=="*")
				{
					star_expr();
				}
				//else{cout<<"testlist_com_error"<<endl;}
			}

		}


	}
	else if(token=="*")
	{
		star_expr();
		while(token==","||  token=="for"    )
		{
			if(token=="for"    /*com_for*/)
			{
				comp_for();
			}
			else if(token==",")
			{
				match(",");
				if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
				{
					test();
				}
				else if (token=="*")
				{
					star_expr();
				}
				//else{cout<<"testlist_com_error"<<endl;}
			}

		}

	}
	else
	{
		error();
	}

}
///////////////////////////////////////////////////////////////////////
void dictorsetmaker() ////mosh kmla
{
	bool h=false;
	if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		test();
		match(":");
		test();
		h=true;
	}
	else if (token=="**"){match("**");expr();h=true;}
	////////////
	if(h)
	{
		if(token=="for")
		{
			comp_for();
		}
		else if(token==",")
		{

		}

	}



}
////////////////////////////////////////////////////////////////
void arglist()
{
	argument();
	while(token==",")
	{
		match(",");
		if (token=="*"||token=="**"||token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
		{
			argument();
		}
	}
}
////////////////////////////////////////////////////////////////////
void argument()
{
	if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		test();
		if(token=="for")
		{
			comp_for();
		}
		else if(token=="=")
		{
			test();
		}
	}
	else if(token=="**"||token=="*")
	{
		match(token);
		test();
	}
}
//////////////////////////////////////////////////////////////

void exprlist()
{
	if(token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	{
		expr();

	}
	else if(token=="*")
	{
		star_expr();
	}
	while(token==",")
	{
		match(",");
		if(token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
		{
			expr();
		}
		else if(token=="*")
		{
			star_expr();
		}


	}


}
////////////////////////////////////////////////////
void comp_iter()
{
	if(token=="for"){comp_for();}
	else if(token=="if"){comp_if();}
}
////////////////////////////////////////////////////
void comp_for()
{
	match("for");
	exprlist();
	match("in");
	or_test();
	if(token=="if"||token=="for")
	{
		comp_iter();
	}
}
///////////////////////////////////////////////
void comp_if()
{
	match("if");
	test_nocond();
	if(token=="if"||token=="for")
	{
		comp_iter();
	}
}
/////////////////////////////////////////////////////////
void encoding_decl()
{
	NAME();
}
////////////////////////////////////////////////////
void yield_expr()
{
	match("yield");
	if(token=="yield")
	{
		yield_arg();
	}
}
//////////////////////////////////////////////////////////////
void yield_arg()
{
	if(token=="from")
	{
		match("from");
		test();
	}
	else testlist();
}
//////////////////////////////////////////////////////////////////

int main()
{
	int x=2;
		if(x==1||4||5){cout<<"5ebaaaa"<<endl;}

	scanner p;
	p.Scanner();

	
	
	init();
	
	c_out.open("C_output.c");
	
	token=value[i];
	token_value=token_value_list[i];
	
	//funcdef();
	//single_input();
	file_input();


	
	c_out.close();
	
	system ("pause");
	return 0;

}