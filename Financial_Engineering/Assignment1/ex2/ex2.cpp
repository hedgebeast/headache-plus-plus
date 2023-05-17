#include <iostream>
#include <string>

using namespace std;

/* Done by: Leon Cai
 * 
*/

bool isPrime (int p){
    if (p <= 1)
        return false;
        
    else {
        for(int i = 2; i < p; i++){
//            cout << "The modulus of " << p << " and " << i << " is " << p % i << endl;
            if (p % i == 0) 
                return false;
        }
        return true;
    }
}

void goldbach (int m){
    bool isGoldbach = false;
    
    for(int i = 2; i < m; i++){
        // example prime number 10: (3+7) or (5+5)
        if (isPrime(i) && isPrime(m-i)) {
            cout << "Found 1 pair of primes: " << i << " and " << m-i << endl;
            isGoldbach = true;
            break;
        }
//        cout << "still in for loop" << endl;
    }
    
//    cout << "outside of for loop" << endl;
    if (isGoldbach == false)
        cout << "Found a counterexample for the Goldbach's conjecture!" << endl;
}

void handle_negative_odd(int i){
    if (i <= 0) {
        throw invalid_argument("Number must be POSITIVE!");
    } 
    else if (i % 2 != 0) {
        throw invalid_argument("Number must be EVEN!");
    }
}

int main()
{
    int n, m;
    
//    cout << "Please enter an integer: ";
//    cin >> n;
//    cout << "You have entered the integer: " << n << endl;
//    
//    
//    if (isPrime(n)) {
//        cout << "The integer " << n << " is a prime number!" << endl;
//    }
//    
//    else 
//        cout << "The integer " << n <<  " is NOT a prime number!" << endl;
        
    cout << "Please enter an POSITIVE EVEN integer greater than 2 to verify the Goldbach's conjecture: " << endl;
    cin >> m;
    
    
    if (m % 2 == 1) {
        cout << "You have entered an odd integer!" << endl;
        cout << "Please enter a POSITIVE EVEN integer greater than 2: " << endl;
        cin >> m;
        
        handle_negative_odd(m);
    }
    
    else {
        if (m <= 2){
            cout << "You have entered an integer <= 2!" << endl;
            cout << "Please enter a POSITIVE EVEN integer greater than 2: " << endl;
            cin >> m;
            
            handle_negative_odd(m);
        }
        else if (m <= 0){
            cout << "You have entered either ZERO or a NEGATIVE integer!" << endl;
            cout << "Please enter a POSITIVE EVEN integer greater than 2: " << endl;
            cin >> m;
            
            handle_negative_odd(m);
        }
        else
            goldbach(m);
    }
    return 0;
}

