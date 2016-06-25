#include <stack>
#include <iostream>
#include<sstream>
#include <vector>
#include <fstream>
#include <ostream>
#include <map>
using namespace std ;


const int max_array_size=20;
 class scanner{


 public:
    void Scanner() {
		string scanner_output; 
	    int startoftoken=0 ;

	    string token;

	  string ReservedWord[]={"def","else","for","yield","if","else","in","not","None","is",
		  "True","False","del","pass","break","continue","raise","import","global","nonlocal",
		  "assert","try","finally","except","as", "from","or","and","lambda","read", 
		  "write","while","NEWLINE","DEDENT","INDENT","return","class"};
	
    int *darray;
	darray=new int[max_array_size];
	int no_of_whilte_space;
	string input_s;
	int arr_pointer=0;
	darray[0]=0;


	ifstream input_file ;
	ofstream output_file ;
	ofstream scanner_value;
	ofstream parcer_inpute ;

	input_file.open("tiny_sample_code.txt");
	int no_white_space_1=0;
	int no_white_space_2=0;

	while (!input_file.eof()) {

		string ss;
		
		//input_file.ignore();
		getline(input_file,ss);
		
		
		if(ss!="")
		{   no_of_whilte_space=0;
			char ws=ss[0];
			for(int x=1;x<ss.size();x++)
			{
				if (ws==' ')
				{
					no_of_whilte_space+=1;
					ws=ss[x];
				}
				else if(ws!=' ')
				{break;}
			}
		
			
			if(no_of_whilte_space > darray[arr_pointer] )
			{
				input_s.append(" INDENT ");
				cout<<"INDENT"<<endl;
				arr_pointer++;
				darray[arr_pointer]=no_of_whilte_space;

			}
			else if (no_of_whilte_space < darray[arr_pointer])
			{
				while(no_of_whilte_space < darray[arr_pointer])
				{
					input_s.append(" DEDENT ");
					cout<<"DEDENT"<<endl;
					arr_pointer--;
				}
			}
			
		}
	
		
		
		if(ss!="")
		{
			input_s.append(ss);
			input_s += '\n';
		}
		
	}
	while(darray[arr_pointer] > 0)
	{   
		cout<<"DEDENT"<<endl;
		input_s.append(" DEDENT ");
		arr_pointer--;
	}
	input_s.append("ENDMARKER");

	input_file.close();
	output_file.open("scanner_output.txt");
	scanner_value.open("scanner_value.txt");
	parcer_inpute.open("parcer_in.txt");
	
	//output_file<<input_s<<endl ;

	enum  states {START,INASSIGN,single_line_COMMENT,multiline_COMMENT,INNUM,INID,DONE ,NAME} ;

	states state= START;
	string currentToken;
	


	char c_next;
	for(int i=0 ; i<input_s.size();i++)
	{
		char c=input_s[i];

		switch(state)
		{
			
		case START:
		
				token="";
				
				startoftoken = i;  //indecate the index of the start of the token
				if (isdigit(c))
				{ 
					state = INNUM;
					token+=c;
				}

				else if (isalpha(c))
				{
					state = INID;
					token+=c;
				}
				
				
			
				else if ((c == ' ') || (c == '\t') )
					state=START;
				else if (c=='\n')
				{
					state=DONE;
					currentToken="NEWLINE";

				}
				else if (c == '#')
				{ 
					state = single_line_COMMENT;
					
					
				}
				else if (c=='"')
				{
					int a=i;
					if(input_s[a+1]=='"' && input_s[a+2]=='"')
					{   
						
						
						state=multiline_COMMENT;
						i=i+2;
						
					}
					else 
					{
						i--;
				      currentToken = "ERROR ";

					}

				}
				else
				{ 
				token+=c;
				switch (c)
				{ 



				case ':':
					currentToken=":";
					state = DONE;
					break;
				case',':
					currentToken=",";
					state = DONE;
					break;
				case'.':
					currentToken=".";
					state = DONE;
					break;
				case '<': 
			        c_next=input_s[++i];
					if(c_next=='='){currentToken="<=";state=DONE;}
					else if(c_next=='>'){currentToken="<>";state=DONE;}
					else {i--;currentToken="<";state=DONE;}
					
					break;

				case'>':
					c_next=input_s[++i];
					if(c_next=='='){currentToken=">=";state=DONE;}
					else {i--;currentToken=">";state=DONE;}

				case'!':
					c_next=input_s[++i];
					if(c_next=='='){currentToken="!=";state=DONE;}
					else {i--;currentToken="!";state=DONE;}

				case '=':
					 c_next=input_s[++i];
					if(c_next=='='){currentToken="==";state=DONE;}
					else {i--;currentToken="=";state=DONE;}
					break;

				


				case '*': 
					currentToken="*";
					state=DONE;
					break;
				case '+': 
					currentToken="+";
					state=DONE;
					break;
				case '-':
					currentToken="-";
					state=DONE;
					break;
				
				case '/':
					currentToken="/";
					state=DONE;
					break;
				case '(': 
					currentToken="(";
					state=DONE;
					break;
				case ')':
					currentToken=")";
					state=DONE;
					break;
				case ';':
					currentToken=";";
					state=DONE;
					break;
				
				case '[':
					currentToken="[";
					state=DONE;
					break;
				case ']':
					currentToken="]";
					state=DONE;
					break;

					
				default:

					currentToken = "ERROR";
					state=DONE;
					break;

				
				}
				}

				break;
			
////////////////////////////////////////////
		case single_line_COMMENT:


			if (c == '\n')
			{
				i--;
				state = START;
				currentToken="single_line_COMMENT";
			}
			else 
			{
				state=single_line_COMMENT ;
				token+=c;
				
			}
			break;
////////////////////////////////////////////
		case multiline_COMMENT:

			if(c=='"')
			{ 
				int a=i;
				if (input_s[a+1]=='"' && input_s[a+2]=='"' )
					
			    { 
					state=START;
					currentToken="MULTI_LINE_COMMENT";
					i=i+2; 
					
					
			    }
				else 
				{
					

					state=multiline_COMMENT;
					token+=c;

				}
			}
			else 
			{

				state=multiline_COMMENT;
				token+=c;

			}

		    break;
////////////////////////////////////////////
		case INASSIGN:
			state = DONE;
			if (c == '='){
			token+=c;
				currentToken = ":=   ";
			}
			else
			{
				i--;
				currentToken = "ERROR   ";
			}
			break;
////////////////////////////////////////////
		case INNUM:
			if (!isdigit(c))
			{
				i--;
				state = DONE;
				currentToken = "NUMBER";
			}
			else {
				token+=c;
				state=INNUM;
			}
			break;
//////////////////////////////////////////	
		case INID:
			if(isalpha(c)||isdigit(c)||c=='_')
			{
				state=INID;
			    token+=c;
			}
			else if (c=='('||c==')'||c==' '||c=='.'||c=='-'||c=='@'||c=='+'||c=='='||c==','||c==';'||c=='/'||c=='%'||c=='!'
				||c=='<'||c=='>'||c=='|'||c=='['||c==']'||c=='*'||c=='^'||c=='~'||c=='{'||c=='}'||c==':'||c=='&'||c=='\n')
		
			{ 
				i--;
				state = DONE;
				currentToken = "NAME";
			}
			
			break;
////////////////////////////////////////////			
		
		}//switch braket

		if(state == DONE /*|| i==(input_s.size()-1)*/)
		{
			state=START;
			
			bool printed=false;
			
			if(currentToken=="NAME")
			{
				for(int k=0;k <37 ;k++)
				{ 
					if(token==ReservedWord[k])
					{
						currentToken=ReservedWord[k];
						break;

					}

				}
				
				
			}
			else if(currentToken=="NEWLINE")
			{
				printed=true;
				scanner_value<<"NEWLINE"<<endl;
			}

			
			
			output_file<<currentToken<<"     " ;
			parcer_inpute<<currentToken<<endl;
			output_file<<token<<endl;
			if(printed==false)
			{scanner_value<<token<<endl;}
		}
	}	
	parcer_inpute<<"ENDMARKER";
	output_file.close();
	parcer_inpute.close();
	scanner_value.close();
}	
	
};










