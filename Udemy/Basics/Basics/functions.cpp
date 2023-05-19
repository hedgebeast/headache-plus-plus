#include <iostream>
#include <iomanip>
#include <cmath> //common mathematical calculations like sqrt, pow etc
#include <vector>

#include <cstdlib> //required for rand()
#include <ctime> //required for time()

using namespace std;

void temperature_conversion(double = 100); //trying function prototypes and include default argument value
double fahrenheit_to_celsius(double); 
double fahrenheit_to_kelvin(double);

void zero_array(int numbers [], size_t size); //a function to initialize all elements to 0
void print_array(const int numbers [], size_t);

void print(const vector<int> &); //PASS BY REFERENCE EXAMPLE

void print(const vector<int> &v){ //can add const to prevent changes to vector (more efficient than pass by value)
    for (auto num: v)
        cout << num << " ";
    cout << endl;
}

// Use case of static variable! (**retains its value between calls**) - behaves like a global variable but scope is local
void incrementCounter() {
    static int counter {0};  // Static variable initialization
    //value is preserved between function calls; useful when need to know a previous value in a function
    // without having to pass it in all the time
    
    counter++;  // Increment the counter

    cout << "Static Variable Counter: " << counter << std::endl;
}

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
    
    temperature_conversion(120.53);
    
    int numbers[] {1,2,3,4,5};
    print_array(numbers, size(numbers));
    zero_array(numbers, size(numbers));    
    
    vector<int> data {100, 120, 150, 310, 69};
    print(data);
    
    incrementCounter();
    incrementCounter();
    incrementCounter();
    
    return 0;
}

void temperature_conversion(double fahrenheit_temperature) {
    
    double celsius_temperature = fahrenheit_to_celsius(fahrenheit_temperature);
    double kelvin_temperature = fahrenheit_to_kelvin (fahrenheit_temperature);
    
    cout << celsius_temperature << " " << kelvin_temperature << endl;
    
    cout << fixed << setprecision(2);
    cout << "The fahrenheit temperature " << fahrenheit_temperature << " degrees is equivalent to " \
    << celsius_temperature << " degrees celsius and " << kelvin_temperature << " degrees kelvin." << endl;
}


double fahrenheit_to_celsius(double x){
//    return round((5.0/9.0)*(x-32));
    return (5.0/9.0)*(x-32.0);
}

double fahrenheit_to_kelvin(double x){
  return fahrenheit_to_celsius(x) + 273.0;
}

void zero_array(int numbers [], size_t size){
    for (size_t i {0}; i < size; ++i)
        numbers[i] = 0;
        
    print_array(numbers, size);
}

void print_array(const int numbers [], size_t size){
//    cout << size << endl;
    for (size_t i {0}; i< size; ++i)
        cout << numbers[i] << " ";
    cout << endl;
}