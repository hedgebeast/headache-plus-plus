#include <iostream>

// namespace is used to help reduce naming conflicts
//std is the name for the C++ 'standard' namespace
using namespace std; // Use the entire std namespace

/*
 * Alternatively, we can use only what we need
 * 
 * using std::cout;
 * using std::cin;
 * using std::endl;
 */


// int main(int argc, char *argv[]) {return 0} -- when you pass input from the console to the main function
// argc = argument count
// argv = argument vector
// i.e. program.exe argument1 argument2

int main(){
    
    //initialize variable
    int fav_num;
    
    //show on console
    cout << "Enter your favourite number between 1 and 100: ";
    
    //grab from console
    cin >> fav_num;
    
    if (fav_num == 24) {
        cout << "Amazing! " << fav_num << " is my favourite number too!" << endl;
    }
    
    else{
        cout << "Not really!! 24 is my favourite number!" << endl;
    }
    
    int num1, num2;
    cout << "Enter 2 integers separated with a space: ";
    cin >> num1 >> num2;
    cout << "You entered: " << num1 << " and " << num2 << endl; 
    
	return 0;
}
