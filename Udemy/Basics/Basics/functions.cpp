#include <iostream>
#include <cmath> //common mathematical calculations like sqrt, pow etc

#include <cstdlib> //required for rand()
#include <ctime> //required for time()

using namespace std;

int main(){
    
    int random_number {};
    size_t count {10};
    int min {1};
    int max {6};
    
    //seed the random number generator
    //else will get the same sequence random numbers every run
    
    cout << "RAND_MAX on my system is: " << RAND_MAX << endl;
    srand(time(nullptr)); //valid valid
    
    for (size_t i=1; i<=count; i++){
        
        random_number = rand() % max + min; //generate a random number [min, max]
        cout << random_number << endl;
        
    }
    
    return 0;
}