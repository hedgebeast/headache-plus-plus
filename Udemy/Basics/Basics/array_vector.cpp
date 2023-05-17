#include <iostream>
#include <climits>

#include <vector>

using namespace std; 

int age {30}; //global variable

int main() {
    
    cout << "Global age is: " << age << endl;
    
    int age (21); //trying constructor initialization; local variable
    cout << "Local age is: " << age << endl;
    
    const int min_age = 18;
    cout << "The min age to smoke is " << min_age << endl;
    
    cout << "int: " << sizeof(int) << " bytes." << endl;
    cout << "age: " << sizeof(age) << " bytes." << endl;
//    cout << "long: " << sizeof(long) << " bytes." << endl;
//    cout << "long long: " << sizeof(long long) << " bytes." << endl;


    // ARRAY
//    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    char vowels[] {'a', 'e', 'i', 'o', 'u'};
    cout << "The first vowel is: " << vowels[0] << endl;
    cout << "The last vowel is: " << vowels[4] << endl;
    
    // 2D array
    int movie_rating [3][4] = {
        
        {0, 4, 3, 5},
        {2, 3, 3, 5},
        {1, 4, 4, 5}
        
        };
    cout << "2nd row and 3rd column is: " << movie_rating[1][2] << endl;
    
    // Use a dynamic array such as VECTOR (an array that can grow and shrink in size at execution time
    //NOTE: compile with  g++ -std=c++2a -o test variables.cpp (as long as it's c++11 and above on macOS)
    vector <int> test_vector {12, 231, 123}; //vector is an object-oriented template class
    cout << "First element in the vector: " << test_vector[0] << endl;
    
    // can append using the push_back() method
    test_vector.push_back(100);
    cout << "Last element in the vector: " << test_vector[3] << endl;
    cout<< "There are " << test_vector.size() << " items in the vector!" << endl;
    
    // 2D-VECTOR
    
    vector <vector<int>> test_2d_vector {   //vector of vector
        {1,2,3,4},
        {4,3,2,1},
        {2,4,1,3}
        };
    
    cout << "\nExample of some ratings by reviewer #1 using array syntax: " << endl;
    cout << test_2d_vector[0][0] << endl;
    cout << test_2d_vector[0][1] << endl;
    cout << test_2d_vector[0][2] << endl;
    cout << test_2d_vector.at(0).at(3) << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < numbers.size(); ++i) { //size_t is an unsigned integer type defined in the <cstddef> header. The size_t type is guaranteed to be able to represent the size of any object in memory. 
        std::cout << numbers[i] << " ";
    }
    
    return 0;
}