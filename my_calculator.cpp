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
            cout << (equation[x].value)<< endl;
        }else if(equation[x].kind != 'n'){
            cout << (equation[x].kind)<< endl;;
        }
    }

}

vector<Token> combine_numbers(vector<Token> equation){
    vector<char> combine;
    int start;
    int end;
    int vector_start_size = equation.size();
    bool run = false;
    int number = 0; 
    int counter = 0;
    int walkThrough = 0;
    for(int x = 0; x < equation.size();x++){
        cout << "1--------In the for loop but not in the while loop -- equation.size() = " << equation.size() << endl;
        run = false;
        counter++;
        while(equation[x].kind == 'n' && x != equation.size()){
            cout << "2--------In the while loop -- equation[x].kind = " << equation[x].kind << endl;
            if(number == 0){
                start = x;
                run = true;
                number = equation[x].value - 48;
                x++;
                cout << "In the num == 0 if -- num = " << number << endl;
            // }else if(equation[x+1].kind == 'n' && number == 0){// This is good for the first run through but not for the second 
            //     number = number * 10;
            //     number = number + equation[x+1].value - 48;
            //     x = x + 2;
            //     cout << "In the else if(equation[x+1].kind == 'n' && number == 0) -- num = " << number << endl;
            }else if(number != 0 && equation[x+1].kind == 'n'){// used if there is another number following but it is not the first or last number in the int
                number = number * 10;
                cout << "number * 10 = " << number << "  equation[x].value - 48 = " << (equation[x].value - 48) << " x = " << (x+1) << endl;
                number = number + (equation[x].value - 48);
                x++;
                cout << "In the else if(number != 0 && equation[x+1].kind == 'n') -- num = " << number << endl;
            }else if(number != 0 && equation[x+1].kind != 'n'){//used for the last number in the int (!!!!!!!!!!might not need this one)
                number = number * 10;
                cout << "number * 10 = " << number << "  equation[x].value - 48 = " << (equation[x].value - 48) << " x = " << (x+1) << endl;
                number = number + (equation[x].value - 48);
                x++;
                end = x;
                cout << "In the else if(number != 0 && equation[x+1].kind != 'n') -- num = " << number << endl;
            }else{
                number = 0;
                cout << "In the else -- num = " << number << endl;
            }
        }
        if(run == true){
            cout << "------------------------------ added to vector" << endl;
            equation[start].value = number;
            equation.erase(equation.begin() + (start+1), equation.begin() + end);
            number = 0;
            print_equation(equation);
            cout << "x = " << x << " equation.size() = " << equation.size() <<  " vector_start_size = " << vector_start_size << endl;
            if(x >= equation.size() && counter >= 2){
                cout << "counter = " << counter << "  equation.size() = " << equation.size() << endl;
                int pop_back_amount = equation.size() - counter;
                for(int y = 0; y < pop_back_amount;y++){
                    equation.pop_back();
                }
                cout << "done" << endl;
            }
            x = start;
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
    print_equation(rough_equation); // used to double check what equation is being stored in the 
    vector<Token> final_equation = combine_numbers(rough_equation);
    print_equation(final_equation);
}