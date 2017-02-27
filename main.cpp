#include"concol.h"
#include<iostream>
#include<stack>
#include<string>
#include<windows.h>
#include<limits>
#include<stdexcept>
#include<conio.h>
#include<algorithm>
using namespace std;
using namespace eku;

void menu();
void displayart();
void straightline();
string postfixinfix(string pass);
string postfixprefix(string pass);
string infixpostfix(string pass);
string infixprefix(string pass);
string prefixpostfix(string pass);
string prefixinfix(string pass);
int precedence(char a);
string displayoutput(stack<char> temp, stack<char> temp2);
string displayoutput2(stack<string> temp, stack<string> temp2);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13



struct console
  {
  console( unsigned width, unsigned height )
    {
    SMALL_RECT r;
    COORD      c;
    hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (!GetConsoleScreenBufferInfo( hConOut, &csbi ))
      throw runtime_error( "You must be attached to a human." );

    r.Left   =
    r.Top    = 0;
    r.Right  = width -1;
    r.Bottom = height -1;
    SetConsoleWindowInfo( hConOut, TRUE, &r );

    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize( hConOut, c );
    }

  ~console()
    {
    SetConsoleTextAttribute(    hConOut,        csbi.wAttributes );
    SetConsoleScreenBufferSize( hConOut,        csbi.dwSize      );
    SetConsoleWindowInfo(       hConOut, TRUE, &csbi.srWindow    );
    }

  void color( WORD color = 0x07 )
    {
    SetConsoleTextAttribute( hConOut, color );
    }

  HANDLE                     hConOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  };

console con( 35, 35 );

int main(void){
	menu();
	system("exit");
	return 0;
}

void menu(){
	SetConsoleTitle("Ayala Project");
	concolinit();
	string returncode;
	int position = 1;
	int key;
	int y=26;
	while(true){
		system("cls");
		key = 0;
		displayart();
		straightline();
		cout<<red<<"  Postfix-Infix-Prefix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Main Menu(Use arrow keys to select)"<<endl;
		cout<<" [ ]Postfix to Infix"<<endl;
		cout<<" [ ]Postfix to Prefix"<<endl;
		cout<<" [ ]Infix to Postfix"<<endl;
		cout<<" [ ]Infix to Prefix"<<endl;
		cout<<" [ ]Prefix to Infix"<<endl;
		cout<<" [ ]Prefix to Postfix"<<endl;
		cout<<" [ ]Exit";
		if(position == 0){
			position = 7;
		}
		else if(position == 8){
			position = 1;
		}
		COORD p;
		switch(position){
			case 1:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 26});
    			cout<<green;
    			break;
    		case 2:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 27});
    			cout<<green;
    			break;
    		case 3:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    			cout<<green;
    			break;
			case 4:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 29});
    			cout<<green;
    			break;
    		case 5:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    			cout<<green;
    			break;
    		case 6:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 31});
    			cout<<green;
    			break;
    		case 7:
    			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 32});
    			cout<<green;
    			break;
    	}
		cout<<"X";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    		switch((key=getche())) {
        		case KEY_UP:
					position--;
            		break;
        		case KEY_DOWN:
					position++;
            		break;
            	case ENTER:
            		if(position == 1){
            			postfixinfix("none");
					}
					else if(position == 2){
						postfixprefix("none");
					}
					else if(position == 3){
						infixpostfix("none");
					}
					else if(position == 4){
						infixprefix("none");
					}
					else if(position == 5){
						prefixinfix("none");
					}
					else if(position == 6){
						prefixpostfix("none");
					}
					else if(position == 7){
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 22});
						cout<<"                                           ";
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {8, 22});
						cout<<"Have a nice day!";
						return;
					}
				}
		Beep(200, 250);
    }
}

string postfixinfix(string pass){
	stack<string> operators;
	stack<string> output;
	string postfix = pass;
	string infix;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Postfix to Infix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, postfix);
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
	    cout<<"Stack: ";
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
	    cout<<"Output: ";
	}
    for(unsigned i = 0; i < postfix.length(); i++){
    	string token;
    	token.push_back(postfix[i]);
    	if(postfix[i]=='+'||postfix[i]=='-'||postfix[i]=='*'||postfix[i]=='/'||postfix[i]=='^'||postfix[i]=='%'){
			if(!operators.empty()){
				operators.pop();
			}
			operators.push(")");
			operators.push(output.top());
			output.pop();
			operators.push(token);
			operators.push(output.top());
			output.pop();
			operators.push("(");
			string combine;
			while(!operators.empty()){
				infix = displayoutput2(operators, output);
				combine.append(operators.top());
				operators.pop();
			}
			output.push(combine);
		}
		else{
			output.push(token);
		}
		infix = displayoutput2(operators, output);
	}
	while(!operators.empty()){
		output.push(operators.top());
		operators.pop();
    	infix = displayoutput2(operators, output);
	}
	if(pass=="none"){
		getche();	
	}
	return infix;
}

string postfixprefix(string pass){
	stack<char> operators;
	stack<char> output;
	string postfix = pass;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Postfix to Prefix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, postfix);
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    	cout<<"Stack: ";
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    	cout<<"Output: ";
	}
	string infix = postfixinfix(postfix);
    string prefix = infixprefix(infix);
	if(pass=="none"){
		getche();	
	}
	return prefix;
}

string infixpostfix(string pass){
	stack<char> operators;
	stack<char> output;
	string infix = pass;
	string postfix;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Infix to Postfix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, infix);
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
	    cout<<"Stack: ";
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
	    cout<<"Output: ";
	}
	
    for(unsigned i = 0; i < infix.length(); i++){
    	if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'||infix[i]=='^'||infix[i]=='%'){
			if(!operators.empty() && operators.top()!='(' && operators.top()!=')'){
				if(precedence(operators.top())<=precedence(infix[i])){
					output.push(operators.top());
					operators.pop();
				}
			}
			operators.push(infix[i]);
		}
		else if(infix[i]=='('){
			operators.push(infix[i]);
		}
		else if(infix[i]==')'){
			output.push(operators.top());
			operators.pop();
			while(operators.top()!='('){
				output.push(operators.top());
				operators.pop();
			}
			operators.pop();
		}
		else{
			output.push(infix[i]);
		}
		postfix = displayoutput(operators, output);
	}
	while(!operators.empty()){
		if(operators.top()=='('||operators.top()==')'){
			operators.pop();
		}
		else{
			output.push(operators.top());
			operators.pop();
		}
		postfix = displayoutput(operators, output);
	}
	if(pass=="none"){
		getche();	
	}
	return postfix;
}

string infixprefix(string pass){
	stack<string> operators;
	stack<string> output;
	string infix = pass;
	string prefix;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Infix to Prefix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, infix);
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    	cout<<"Stack: ";
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    	cout<<"Output: ";
	}
    for(unsigned i = 0; i < infix.length(); i++){
    	string token;
    	token.push_back(infix[i]);
    	if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'||infix[i]=='^'||infix[i]=='%'){
			operators.push(token);
		}
		else if(infix[i]=='('){
			output.push(token);
		}
		else if(infix[i]==')'){
			string reverse;
			stack<string> temp;
			while(output.top()!="(" && !operators.empty()){
				prefix = displayoutput2(operators, output);
				temp.push(output.top());
				output.pop();
			}
			while(!temp.empty()){
				prefix = displayoutput2(operators, output);
				reverse.append(temp.top());
				temp.pop();
			}
			output.pop();
			output.push(operators.top());
			operators.pop();
			output.push(reverse);
		}
		else{
			output.push(token);
		}
		prefix = displayoutput2(operators, output);
	}
	while(!operators.empty()){
		output.push(operators.top());
		operators.pop();
		prefix = displayoutput2(operators, output);
	}
	if(pass=="none"){
		getche();	
	}
	return prefix;
}

string prefixpostfix(string pass){
	stack<string> operators;
	stack<string> output;
	string prefix = pass;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Prefix to Postfix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, prefix);
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    	cout<<"Stack: ";
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    	cout<<"Output: ";
	}
	string infix = prefixinfix(prefix);
	string postfix = infixpostfix(infix);
	if(pass=="none"){
		getche();	
	}
	return postfix;
}

string prefixinfix(string pass){
	stack<string> operators;
	stack<string> output;
	string prefix = pass;
	string infix;
	if(pass=="none"){
		system("cls");
		displayart();
		straightline();
		cout<<red<<"    Prefix to Infix Converter"<<endl<<dark_white;
		straightline();
		cout<<"Enter Arithmetic Expression: "<<endl;
		getline(cin, prefix);
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    	cout<<"Stack: ";
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    	cout<<"Output: ";
	}
	stack<string> reverse;
	for(unsigned i = 0; i < prefix.length(); i++){
		string token;
		token.push_back(prefix[i]);
		reverse.push(token);
	}
	while(!reverse.empty()){
		if(reverse.top()=="+"||reverse.top()=="-"||reverse.top()=="*"||reverse.top()=="/"||reverse.top()=="^"||reverse.top()=="%"){
			if(!operators.empty()){
				operators.pop();
			}
			stack<string> reverse2;
			operators.push("(");
			operators.push(output.top());
			output.pop();
			operators.push(reverse.top());
			operators.push(output.top());
			output.pop();
			operators.push(")");
			string combine;
			while(!operators.empty()){
				infix = displayoutput2(operators, output);
				reverse2.push(operators.top());
				operators.pop();
			}
			while(!reverse2.empty()){
				combine.append(reverse2.top());
				reverse2.pop();
			}
			output.push(combine);
			reverse.pop();
		}
		else{
			output.push(reverse.top());
			reverse.pop();
		}
		infix = displayoutput2(operators, output);
	}
	while(!operators.empty()){
		output.push(operators.top());
		operators.pop();
		infix = displayoutput2(operators, output);
	}
	if(pass=="none"){
		getche();	
	}
	return infix;
}

int precedence(char a){
    int temp;
    if(a == '^'){temp = 1;}
    else if(a == '*' || a =='/' || a =='%'){temp = 2;}
    else if(a == '+'|| a =='-'){temp = 3;}
    return temp;
}

string displayoutput(stack<char> temp, stack<char> temp2){
	Sleep(250);
	Beep(100, 250);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    cout<<"Stack:                                                ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    cout<<"Stack: ";
    stack<char> dump2;
    for(stack<char> dump = temp; !dump.empty();dump.pop()){
		dump2.push(dump.top());
	}
	for(; !dump2.empty();dump2.pop()){
    	cout<<dump2.top();
	}
	string expression;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    cout<<"Output:                                               ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    cout<<"Output: ";
    stack<char> dump3;
    for(stack<char> dump = temp2; !dump.empty();dump.pop()){
		dump3.push(dump.top());
	}
	for(; !dump3.empty();dump3.pop()){
		expression.push_back(dump3.top());
    	cout<<dump3.top();
	}
	return expression;
}

string displayoutput2(stack<string> temp, stack<string> temp2){
	Sleep(250);
	Beep(100, 250);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    cout<<"Stack:                                                ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 28});
    cout<<"Stack: ";
    for(stack<string> dump = temp; !dump.empty();dump.pop()){
		cout<<dump.top();
	}
	string expression;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    cout<<"Output:                                               ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 30});
    cout<<"Output: ";
    stack<string> dump3;
    for(stack<string> dump = temp2; !dump.empty();dump.pop()){
		dump3.push(dump.top());
	}
	for(; !dump3.empty();dump3.pop()){
		expression.append(dump3.top());
    	cout<<dump3.top();
	}
	return expression;
}

void displayart(){
	cout<<red<<"                 {}"<<endl;
	cout<<" ,  A            {}"<<endl;
	cout<<" / \\,| ,        .--."<<endl;
	cout<<"|=|= >         /.--.\\"<<endl;
	cout<<" \\ /`| `       |====|"<<endl;
	cout<<" `  |          |`::`| "<<endl;
	cout<<"    |	   .-;`\\..../`;_.-^-._"<<endl;
	cout<<"    /\\\\/  /  |...::..|`   :   `|"<<endl;
	cout<<"    |:'\\ |   /'''::''|   .:.   |"<<endl;
	cout<<"    \\ /\\;-,/ \\   ::  |.."<<yellow<<"AYALA"<<red<<"..|"<<endl;
	cout<<"    |\\ <` >  >._::_. |'"<<yellow<<"PROJECT"<<red<<"'|"<<endl;
	cout<<"    | `""`     /   ^^/>|   ':'   |"<<endl;
	cout<<"    |        |       \\    :   /"<<endl;
	cout<<"    |        |        \\   :  /"<<endl;
	cout<<"    |        |___/\\___|`-.:.-`"<<endl;
	cout<<"    |         \\_ || _/	`"<<endl;
	cout<<"    |         <_ >< _>"<<endl;
	cout<<"    |         |  ||  |"<<endl;
	cout<<"    |         |  ||  |"<<endl;
	cout<<"    |        _\\.:||:./_"<<endl;
	cout<<"    |       /____/\\____\\"<<endl<<dark_white;
}

void straightline(){
	cout<<yellow<<"=================================="<<endl<<dark_white;
}


