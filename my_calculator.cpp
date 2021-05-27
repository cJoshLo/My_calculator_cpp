#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
using namespace std;

class Token{
    public:
        char kind;
        double value;
};

void print_equation(vector<Token> equation){
    for(int x = 0; x < equation.size();x++){
        if(equation[x].kind == 'n'){
            cout << (equation[x].value-48);
        }else if(equation[x].kind != 'n'){
            cout << (equation[x].kind);
        }
    }

}

vector<Token> combine_numbers(vector<Token> equation){
    vector<char> combine;
    int start;
    int end;
    bool run = false;
    int number = 0; 
    for(int x = 0; x < equation.size();x++){
        run = false;
        while(equation[x].kind == 'n'){
            if(number == 0){
                start = x;
                run = true;
                number = equation[x].value;
            }
            if(equation[x+1].kind == 'n' && number == 0){// This is good for the first run through but not for the second 
                number = number * 10;
                number = number + equation[x+1].value;
                x = x + 2;
            }else if(number != 0 && equation[x+1].kind == 'n'){// used if there is another number following but it is not the first or last number in the int
                number = number * 10;
                number = number + equation[x].value;
                x++;
            }else if(number != 0 && equation[x+1].kind != 'n'){//used for the last number in the int (!!!!!!!!!!might not need this one)
                number = number * 10;
                number = number + equation[x].value;
                x++;
                end = x;
            }else{
                number = 0;
            }
        }
        if(run == true){
            x = start;
            // int amount_remove = end - start;
            equation[start].value = number;
            equation.erase(equation.begin() + (start+1), equation.begin() + end);
            // for(int y = 1; y <= amount_remove; y++){
            //     equation.erase(equation.begin() + (start+y));// equation[start+y]
            // }
        }
    }
    return equation;
}

Token checker(char x){
    switch(x){
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'://checking to see if the input is a number
            return Token{'n',x}; //creates a Token 
        case '+': case '-': case '/': case '*': // checking to see if the input is a equation mark
            return Token{x,0};
        default:
            cout << "The input is not valid" << endl;
            exit(3);//This is an exit code if an incorrect input is tried
    }
}


int main(){
    char x;
    vector<Token> rough_equation;
    while(cin >> x && x != ';'){// Takes the input for the equation and stores them into a vector
        Token input = checker(x);
        rough_equation.push_back(input);
    }
    // print_equation(equation); // used to double check what equation is being stored in the 
    vector<Token> final_equation = combine_numbers(rough_equation);
    print_equation(final_equation);
}