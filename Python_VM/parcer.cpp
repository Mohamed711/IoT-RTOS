

#include "parcer.h"

	
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

/////////////////////////////////////////////////////////////////////
void error(void)
{
	cout<<"match ERROR"<<endl;
	parcer_output<<"match ERROR"<<endl;
	system ("pause");
	exit(1);

}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
bool match (string t)
{  
	if (!(token.compare(t)))
	{  
		bool printed=false;
		if (token=="def"){printed=true;}
		else if(token!="NAME" && token!="NUMBER"&&token != ":" && token!="NEWLINE" && token!="INDENT" && token!="DEDENT"&&token!="def")
		{ 
			for(int k=0;k <30 ;k++)
				{  
					if(token==pythonWord[k])
					{
						string t=" ";
						t.append(token);
						t.append(" ");
						add_in_stmt_array(t);
						printed=true;
						break;
					}

				}

			
		}
		else if(token=="NAME"||token=="NUMBER")
		{
			printed=true;
			token_value=token_value_list[i];
			//c_out<<""<<token_value<<"";
			add_in_stmt_array(token_value);
			if(token=="NAME")
			{
				check_if_defined=check_if_in_defined_array(token_value);
			}
			else if(token=="NUMBER")
			{

			}
		}
		if(printed==false && token != ":" && token!="NEWLINE" &&
			token!="INDENT" && token!="DEDENT"&&token!="def")
		{
			//c_out<<token;
			add_in_stmt_array(token);
		
		}

		token=value[++i];	
		return true;
	}
	else 
	{
		error();
		return false;
	}

}
//////////////////////////////////////////////////////
bool check_if_in_defined_array(string NAME_value)
{
	bool defined=false;
	int x;
	for(x=0;x<=p_defined_int_array;x++)
	{
		if(defined_int_array[x]==NAME_value)
		{
			defined=true;
			break;
		}
	}
	for(x=0;x<=p_defined_string_array;x++)
	{
		if(defined_string_array[x]==NAME_value)
		{
			defined=true;
			break;
		}
	}
	if(defined==false)
	{
		add_in_undefined_array(NAME_value);
	}
	return defined;
}
////////////////////////////////////////////////////////
void add_in_undefined_array(string Name)
{
	undefined_NAME_arry[p_undefined_NAME_array++]=Name;
	
}
////////////////////////////////////////////////////////
void insert_type_in_stmt_arry(int position,string type)
{

	int len=p_stmt_array; //3lshan l pointer now byshawer 3la 2welmkan fady y7ot fe
	int index=position;
	int indexOfLast=len-1;

	if ((index>=0)&&(index<=len)){

		for(indexOfLast;indexOfLast>=index;indexOfLast--){
			//cout<<"fg\n";
			stmt_array[indexOfLast+1]=stmt_array[indexOfLast];
		}
		stmt_array[index]=type;
	}
	else
		cout<<"\nPosition does not exist\n";
	p_stmt_array++;
}
/////////////////////////////////////////////////////////////////////////////////
string check_type(string value)  //mo2ktaan
{  
	string return_value;
	/* int i=0;
	char s=value[i];
	
	while(s ==' ')
	{
		s=value[i++];
	}
		if (s=='0'||s=='1'||s=='2'||s=='3'||s=='4'||s=='5'||s=='6'||s=='7'||s=='8'||s=='9')
		{
			return_value= " int ";
		}
		else if (isalpha(s))
		{
			return_value= " string ";
		}
		
	*/
	if (token=="NAME")
	{

		return_value=" char ";
	}
	else if (token=="NUMBER")
	{
		return_value=" int ";
	}

		return return_value;
}
/////////////////////////////////////////////////////////////////////////////////
void print_stmt_array()
{ 
	int i;
	for(i=0;i<p_stmt_array;i++)
	{
		c_out<<stmt_array[i];
	}
	p_stmt_array=0;


}
/////////////////////////////////////////////////
void add_in_stmt_array(string token)
{
	stmt_array[p_stmt_array++]=token;
}
/////////////////////////////////////////////////////////////////////////////////
void change_from_undefined_to_defined(int position_of_undefined_array,string type)
{ 

	if(type==" int ")
	{  
		while(p_undefined_NAME_array>position_of_undefined_array){
		defined_int_array[p_defined_int_array++]=undefined_NAME_arry[--p_undefined_NAME_array];
		}
	}
	else if(type==" char ")
	{  
		while(p_undefined_NAME_array>position_of_undefined_array){
		defined_string_array[p_defined_string_array++]=undefined_NAME_arry[--p_undefined_NAME_array];
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
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
		else if(token !="ENDMARKER"){
		stmt();
		print_stmt_array();
		}

	}
	//match("ENDMARKER");

}
///////////////////////////////////////////////////////////////////////////////////////////
void eval_input()
{
	testlist();
	while(token=="NEWLINE")
	{
	match("NEWLINE");
	}
	match("ENDMARKER");
}
/////////////////////////////////////////////////////////////////////
void decorator()
{
	match("@");
	dotted_name();
	if(token=="(")
	{
		match("(");
		arglist();
		match(")");
	}
	match("NEWLINE");

}
//////////////////////////////////////////////////////////////////////////
void decorators()
{
	decorator();
    if(token=="@")
	{
		decorator();
	}
	
}
/////////////////////////////////////////////////////////////////
void async_funcdef()
{
	match("ASYNC");
	funcdef();
}
////////////////////////////////////////////////////////////////////////////////////////////
void funcdef()
{
	int p_funcdef_begin=p_stmt_array;
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
	insert_type_in_stmt_arry(p_funcdef_begin,function_return_type);
	function_return_type=" void ";
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
	
	string type;
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
	
	//c_out<<" ; "<<endl;
	add_in_stmt_array(" ; \n");

}
///////////////////////////////////////////////////////////////////////////////////////
void expr_stmt()
{  
	int p_expr_stmt_begain = p_stmt_array;
	int xx=0;
	int p_undefined_array_expr_stmt_begin=p_undefined_NAME_array;
	string type;

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
			if(xx==0){
			
			 type=check_type(token);
			xx++;
			}
			

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
	if(!check_if_defined){
		insert_type_in_stmt_arry(p_expr_stmt_begain,type);}
	change_from_undefined_to_defined(p_undefined_array_expr_stmt_begin,type);
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
		function_return_type=check_type(token);
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
	if (token=="import"){import_name();}
	else if (token=="from"){import_from();}
	
}
///////////////////////////////////////////////////////
void import_name()
{
	match("import");
	dotted_as_name();
}
//////////////////////////////////////////////////////
void import_from()
{
	match("from");
	while(token=="."||token=="...")
	{
		match(token);
		if(token=="NAME")
		{
			dotted_name();
		}
	}
	match("import");
	if(token=="*"){match("*");}
	else if(token=="("){match("(");import_as_names();match(")");}
	else if (token=="NAME"){import_as_names();}
}
////////////////////////////////////////////////////////
void import_as_name()
{
	match("NAME");
	if (token=="as"){match("as");NAME();}
}
//////////////////////////////////////////////////////////
void dotted_as_name()
{
	dotted_name();
	if(token=="as")
	{
		match("as");NAME();
	}
}
////////////////////////////////////////////////////////
void import_as_names()
{
	import_as_name();
	while (token==",")
	{
		match(",");
		if(token=="NAME")
		{
			import_as_name();
		}
	}
}
////////////////////////////////////////////////////////
void dotted_as_names()
{
	dotted_as_name();
	while(token==",")
	{
		match(",");
		dotted_as_name();
	}
}
///////////////////////////////////////////////////////////
void dotted_name()
{
	NAME();
	while(token==".")
	{
		match(".");
		NAME();
	}
}
///////////////////////////////////////////////////////
void global_stmt()
{
	match("global");
	NAME();
	while(",")
	{
		match(",");
		NAME();
	}
}
////////////////////////////////////////////////////////
void nonlocal_stmt()
{
	match("nonlocal");
	NAME();
	while(token==",")
	{
		match(",");
		NAME();
	}
}
//////////////////////////////////////////////////////
void assert_stmt()
{
	match("assert");
	test();
	if(token==",")
	{
		match(",");
		test();
	}
}
///////////////////////////////////////////////////////
void compound_stmt()
{
	if (token=="if"){if_stmt();}
	else if(token=="while"){while_stmt();}
	else if (token=="for"){for_stmt();}
	else if (token=="try"){/*try_stmt();*/}
	else if (token=="with"){/*with_stmt();*/}
	else if (token=="def"){funcdef();}
}
////////////////////////////////////////////////////////////
void async_stmt()
{
	match("ASYNC");
	if(token=="def"){funcdef();}
	else if(token=="with"){with_stmt();}
	else if(token=="for"){for_stmt();}
}
///////////////////////////////////////////////////////////
void if_stmt()
{
	match("if");
	//c_out<<"(";
	add_in_stmt_array("(");
	test();
	//c_out<<")";
	add_in_stmt_array(")");
	match(":");
	suite();
	while(token=="elif")
	{
		match("elif");
		//c_out<<"(";
		add_in_stmt_array("(");
		test();
		//c_out<<")";
		add_in_stmt_array(")");
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
	//c_out<<"(";
	add_in_stmt_array("(");
	test(); 
	//c_out<<")";
	add_in_stmt_array(")");
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
	//c_out<<"(";
	add_in_stmt_array("(");
	exprlist();
	match("in");
	testlist();
	//c_out<<")";
	add_in_stmt_array(")");
	match(":");
	suite();
	if(token=="else")
	{
		match("else");
		match(":");
		suite();
	}
}
////////////////////////////////////////////////////
void try_stmt()
{
	match("try");
	match(":");
	suite();
	if(token=="except")
	{
		except_clause();
			match(":");
			suite();

		while(token=="except")
		{
			except_clause();
			match(":");
			suite();
		}
		if(token=="else")
		{
			match("else");
			match(":");
			suite();
		}
		if(token=="finally")
		{
			match("finally");
			match(":");
			suite();
		}


	}
	else if (token=="finally"){match("finally");match(":");suite();}
}
////////////////////////////////////////////////////////////////////////////
void with_stmt()
{
	match("with");
	with_item();
	while(token==",")
	{
		match(",");
		with_item();
	}
	match(":");
	suite();
}
/////////////////////////////////////////////////////////////////
void with_item()
{
	test();
	if(token=="as"){match("as");NAME();}
}
///////////////////////////////////////////////
void except_clause()
{
	match("except");
	if(token=="not"||token=="+"||token=="-" ||token=="~"||token=="AWAIT" 
					||token=="("||token=="["||token=="{"||token=="NAME"||token=="NUMBER"
					||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False")
	
	{
		test();
		if(token=="as")
		{
			match("as");
			NAME();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
void suite()
{
	int p_scope_of_int_variable=p_defined_int_array;
	int p_scope_of_string_variable=p_defined_string_array;
	add_in_stmt_array(" { \n");

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
	 
		 

	// c_out<<" } "<<endl;
	 add_in_stmt_array(" } \n");

	  p_defined_int_array=p_scope_of_int_variable;
	 p_defined_string_array=p_scope_of_string_variable;
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
///////////////////////////////////////////////////
void star_expr()
{
	match("*"); expr();
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
/////////////////////////////////////////////////////////////
void subscriptlist()
{
	subscript();
	while(token==",")
	{
		match(",");
		if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	
		{
			subscript();
		}
	}
}
///////////////////////////////////////////////////////////////////////
void subscript()
{
	if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	
	{
		test();
	}
	if(token==":")
	{
		match(":");
		if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	
		{
			test();
		}
		if(token==":")
		{
			sliceop();
		}
	}
	
}
////////////////////////////////////////////
void sliceop()
{
	match(":");
	if(token=="not"||token=="+"||token=="-"||token=="~"||token=="AWAIT" ||token=="("||token=="["||token=="{"||token=="NAME"
			||token=="NUMBER"||token=="STRING"||token=="..."||token=="None"||token=="True"||token=="False" )
	
		{
			test();
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
	
	c_out.open("C_output.txt");
	
	token=value[i];
	token_value=token_value_list[i];
	
	//funcdef();
	//single_input();
	file_input();


	
	c_out.close();
	
	system ("pause");
	return 0;

}