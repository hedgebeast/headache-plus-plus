#include <iostream>
#include <vector>

using namespace std;
/*
 * (1) A pointer is a variable whose value is an address 
 * (2) The value of an array name is the address of the first element in the array
 * (3) Another variable or a function can be at that address
 * (4) To use the data that the pointer is pointing to, you must know its type
 * (5) int *ptr == int* ptr (compiler doesn't give a p*op)
 * (6) string *ptr; => pointer to a string type
 * (7) & the address operator
 */
 
const int *larger_integer (const int *, const int *);
int *create_array(size_t size, int init_value = 0);
 
int main(){
    
    int *p {nullptr}; //initializing pointer variable to 'point nowhere' (very different from pointing anywhere)
    
    cout << "Value of p: " << p << endl;
    cout << "Address of p: " << &p << endl;
    
    int x {10};
    
    p = &x; //pointer p now contains the address of x
    
    //*** In order to access the data at the address contained in pointer p,
    //*** use the dereferencing operator *
    
    cout << "The value/data that p is pointing to is: " << *p << endl; 
    
    cout << "---------------------- Another Example ------------------------" << endl;
    string name {"Dudu"};
    string *s_ptr {&name};
    cout << *s_ptr << endl;
    
    name = "Bubu";
    cout << *s_ptr << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //DYNAMIC MEMORY ALLOCATION - use pointers to access newly allocated heap storage
    
    int *int_ptr {nullptr};
    
    int_ptr = new int; //using new to allocate storage; allocate an integer on the heap
    
    cout << "An new address/storage is allocated @ " << int_ptr << endl;
    cout << *int_ptr << endl; //contains garbage as data at new address/storage has not been initialized
    
    *int_ptr = 100;
    
    cout << *int_ptr << endl; //Notice that the allocated storage does not have a name
                             //Therefore the only way to access the storage is to use pointer 
    
    delete int_ptr; //free the allocated storage
    cout << "After deleting allocated storage: " << int_ptr << endl;
    
    cout << "----------------- Using new[] to allocate storage for an array -----------------" << endl;
    
    double *array_ptr {nullptr};
    int size {};
    
    cout << "Size of array? ";
    cin >> size;
    
    array_ptr = new double[size]; //allocate array on the heap
    
    cout << array_ptr << endl;
    
    delete [] array_ptr; //free up storage at the heap
    
    //Pointer arithmetic only makes sense with raw array i.e. int_ptr++; or int_ptr--;
    
    int score[] {100, 95, 98, 68, -1};
    int *score_ptr {score};
    
    while (*score_ptr != -1){
//        cout << *score_ptr << endl;
//        score_ptr++;
        //OR
        cout << *score_ptr++ << endl; //dereference the pointer THEN increment the pointer
                                      //very different from (*score_ptr)++ == incrementing the dereferenced value
    }
    
    int high_score {100};
    int low_score {68};
    const int *score_ptr2 {&high_score}; //pointer is pointing to a constant int (hence cannot change the value of high_score!)
    
    score_ptr2 = &low_score; //but can still change the pointer to point elsewhere
    
    //HOWEVER, if we don't want the pointer to change and point somewhere else
    int *const score_ptr3 {&high_score};
    
    *score_ptr3 = 85; //ok to change the data that it is pointing to, but cannot change to point elsewhere already 
    
    //HENCE, if we wanna enforce that both the pointer and the data cannot be changed (combination of both)
    
    const int *const score_ptr4 (&high_score);
    
    cout << "----------------- Returning a Pointer from a Function -----------------" << endl;
    // Need to provide the type of the pointer in the function definition, as well as, in the function prototype
    // e.g. type *function(); => function will return an address
    
    
    int a {5}, b{10};
    const int *larger_int = larger_integer(&a, &b);
    cout << "the value of the larger integer is: " << *larger_int << endl;
    
    int *my_array;
    
    my_array = create_array(100, 20);
    
    cout << my_array[0] << " and last element " << my_array[99] << endl;
    
    delete [] my_array;
    
    
    cout << "----------------- What is a Reference -----------------" << endl;
    // An alias for a variable and it must be initialized when declared
    // Helpful t0 think of a reference as a constant pointer that is automatically dereferenced 
    vector<string> stooges {"Larry", "Moe", "Curly"};
    
    for (auto str:stooges){
        str = "Funny";  
        cout << str << " " << endl;
    }
        
    for (auto str:stooges)
        cout << str << " " << endl;
    
    for (auto &str:stooges){
        str = "Not Funny";  
        cout << str << " " << endl;
    }
        
    for (auto str:stooges)
        cout << str << " " << endl;
    
    for (auto const &str:stooges)
//        str = "Funny";  //compiler error
        cout << str << endl;
        
    int num {100};
    int &ref {num}; //the copy is referencing to num (L-value)
//    int &ref2 = 100; //ERROR as 100 is a literal/R-value
    
    num = 3050;
    cout << num << endl;
    cout << ref << endl;
    
    ref = 125;
    cout << num << endl;
    cout << ref << endl;

    return 0;
}


const int *larger_integer (const int *int_ptr1, const int *int_ptr2){
    if (*int_ptr1 > *int_ptr2){
        cout << "a is larger than b." << endl;
        return int_ptr1;
    }
    else {
        cout << "b is larger than a." << endl;
        return int_ptr2;
    }
}
    
int *create_array(size_t size, int init_value){
    int *new_storage {nullptr};
    
    new_storage = new int[size];
    for (size_t i {0}; i < size; i++)
        *(new_storage + i) = init_value;
    
    return new_storage;
}