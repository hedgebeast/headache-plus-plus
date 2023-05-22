#include <iostream>
#include <string>
#include <vector>

using namespace std;

/********************************************************************************************************************
 ***************************************************  CONSTRUCTORS ************************************************** 
 * (1) Special member method
 * (2) Invoked during object creation
 * (3) Used for initialization
 * (4) Same name as Class
 * (5) No return type is specified
 * (6) Can be overloaded
 * 
 ****************************************************  DESTRUCTORS **************************************************
 * (1) Special member method
 * (2) Same name as Class preceded by a ~
 * (3) Invoked automatically when an object is destroyed
 * (4) No return type and no parameters
 * (5) Only 1 destructor is allowed per class (cannot overload)
 * (6) Useful to release memory and other resources
 ********************************************************************************************************************/

class Player{
private:
/*
 * Class data members can be declared as static
 * A single data member that belongs to the class, not the objects
 * Can be called using the class name
 * Useful to store class-wide information
 */ 
    string name;
    int health;
    int xp;
    static int num_players;
    friend void display_player(const Player &p); //although put under private but still need friend keyword to access other private members
    
public:
//    friend void display_player(const Player &p); //can access all private members without using getter and may also change private data members
    void set_name(string name_val){name=name_val;}
    
    //putting const after the function => not a const function but cannot alter variable inside too
    string get_name() const {return name;} //can still display or return name but will not allow modification to name
    int get_health() const {return health;}
    int get_xp() const {return xp;}
    
    static int get_num_players(); //function is static, so it only has access to static data members
    
    //Copy Constructor
    Player(const Player &);
    
//    //Destructor
//    ~Player(){cout << "Destructor called for: " + name << endl;}

    //Overloaded Constructors: provide many useful initialization options for classes
//    Player(){                   //Create own default constructor
//        cout << "Constructor with no argument called!" << endl;
//        name = "None";                                              //Assignment not initialization!
//        health = 0;
//        xp = 0;
//    }
//    
//    //Better way (Constructor Initialization Lists - No code in the Constructor body)
//    Player(): name{"None"}, health{0}, xp{0} {} //order is according to the member variables declared above
//    
//    Player(string arg1){
//        cout << "Constructor with 1 string argument called!" << endl;
//        name = arg1;
//
//    }
//    Player(string arg1, int arg2, int arg3){
//        cout << "Constructor with 3 arguments called!" << endl;
//        name = arg1;
//        health = arg2;
//        xp = arg3;
//    }
    
    Player();
    Player(string);
    Player(string, int, int);
    
    
    ~Player(){                  //Destructor
        cout << "Destructor called for "<< name << endl; 
        --num_players;
    }
};

//Delegating Constructors
Player::Player(string _name, int _health, int _xp)
    : name{_name}, health{_health}, xp{_xp} {
        cout << "3 arguments Constructors for " + name <<  endl;
        ++num_players;
    }

Player::Player()
    : Player{"None", 0, 0}{ //calls the delegating constructor
        cout << "This is the \"Default\" Constructor" << endl;
    }
    
Player::Player(string _name)
    : Player{_name, 0, 0}{
        cout << "Constructor with 1 argument" << endl;
    }
    
Player::Player(const Player &source) //source and the newly created object both point to the same data area
//    : name {source.name}, health {source.health}, xp {source.xp}{
    : Player{source.name, source.health, source.xp} {
        cout << "Copy Constructor - made copy of: " + name << endl;
    }
    
/********************************************************************************************************************
 **************************************************  BEST PRACTICES ************************************************* 
 * (1) Provide a copy constructor when class has raw pointer members
 * (2) Provide the copy constructor with a const reference parameter
 * (3) Use STL classes as they already provide copy constructors
 * (4) Avoid using raw pointer data members if possible or use smart pointers
 * 
 *************************************************  COPY CONSTRUCTOR ************************************************
 * DECLARATION: Type::Type(const Type &source); 
 * by reference cus //if we pass in by value then we have to make a copy of it => defeats the purpose
 * //const cus we are only copying the source, we are not modifying it
 * 
 ********************************************************************************************************************/ 
 
class Deep{
private:
    int *data {nullptr}; //deep copy whenever there's a raw pointer as a class data member

public: 
    void set_data_value(int d){*data = d;}
    int get_data_value(){return *data;}
    
    int* get_data(){return data;}
    
    //Constructor
    Deep(int d);
    
    //Copy Constructor
    Deep(const Deep &source);
    //Move Constructor
    Deep(Deep &&source) noexcept;
    
    //Destructor
    ~Deep();
 };
 
Deep::Deep(int d){
    data = new int;
    cout <<"Current address of data at default constructor: " << data << endl;
    *data = d;
}

Deep::Deep(const Deep &source)
    //it will go back to the delegating constructor to allocate another storage on the heap for the copy
    : Deep(*source.data){   //Not just copying the pointer, but also copying the data pointed to by the pointer
        cout << "Copy constructor - deep copy for: " << *data << endl;
    }
    
//Deep copying results in a lot of overhead => Consider using 
//***MOVE CONSTRUCTOR*** (when user pass in r-value temporary)
Deep::Deep(Deep &&source) noexcept
    //Simply copies the address of the resource from source to the current object
//    : data {source.data}{       
{   cout << "Current address of data at move constructor: " << get_data() << endl;
    cout << "Current address of source data: " << source.data << endl;
    
    data = source.data;
    
        //and nulls out the pointer in the source pointer
        source.data = nullptr;
        cout << "Next address of data at move constructor: " << get_data() << endl;
        cout << "Next address of source data: " << source.data << endl;
        cout << "Move constructor - moving resource: " << *data << endl;
    }

Deep::~Deep(){
    if(data != nullptr){
        cout << "Destructor freeing data for: " << *data << endl;
    }
    else {
        cout << "Destructor freeing data for nullptr" << endl;
    }
    delete data;
}

//Case when copy constructor will be called (pass object as value)
void display_player(const Player &p){
//    cout << "Name: " << p.get_name() << endl;
//    cout << "Health: " << p.get_health() << endl;
//    cout << "XP: " << p.get_xp() << endl;
    
    //after declaring that this function is a friend
    cout << "Name: " << p.name << endl;
    cout << "Health: " << p.health << endl;
    cout << "XP: " << p.xp << endl;
}

void display_deep(Deep s){
    cout << "Displaying deep value: " << s.get_data_value() << endl;
}


int Player::num_players {0};
int Player::get_num_players(){return num_players;}


void display_active_players(){
    cout << "Active players: " << Player::get_num_players() << endl;
}

int main(){
//    {
//        Player Dudu;    //C++ will generate a Default Constructor that does nothing
//        cout << "--------------------------------------------------------\n";
//        cout << Dudu.get_name() << endl;
//        Dudu.set_name("Dudu");
//        cout << Dudu.get_name() << endl;
//        
//        display_player(Dudu);
//    }
    display_active_players();

    {
        Deep obj1 {100};
        display_deep(obj1);
        
        Deep obj2 {obj1};
        
        obj2.set_data_value(1000);
        
        cout << "The value of data at obj1 is: " << obj1.get_data_value() << endl;
        cout << "The value of data at obj2 is: " << obj2.get_data_value() << endl;
    }
    {
        cout << "----------------------------------------------" << endl;
        cout << "Testing Move Constructor! " << endl;
        cout << "----------------------------------------------" << endl;
        vector<Deep> vec;
        
        cout << "Current address of vector: " << &vec << endl;
        vec.push_back(Deep{300}); //Copy constructor will be called to copy the temps
        vec.push_back(Deep{999});
        
        cout << "The address of the last element in the vector: " << &vec[1] << endl;
        cout << "The address of the data contained in the last element in the vector: " << vec[1].get_data() << endl;
        cout << "Last element in the vector: " << vec[1].get_data_value() << endl;
        cout<< "There are " << vec.size() << " items in the vector!" << endl;
        
    }
    
    {
        cout << "--------------------- Making Dudu Object below ---------------------\n";
        Player dudu {"DUDU", 10, 50};  
        cout << "--------------------- Making Baby Dudu below (Will trigger copy constructor - passing object) ---------------------\n";
        Player baby_dudu {dudu};
        cout << "--------------------- Displaying Dudu Profile below ---------------------\n";
        display_player(dudu);
    }
    cout << "--------------------------------------------------------\n";
    {
        Player Bubu;
        Bubu.set_name("Bubu");
        
        Player Hero("Hero");
        cout << Hero.get_name() << endl; 
        Hero.set_name("God");
        cout << Hero.get_name() << endl;
        
        const Player Villain("Villain", 100, 15); //declaring const object
//        Villain.set_name("Devil"); //cannot
        
        display_player(Villain);
        
        display_active_players();
    }
    
    
    Player *enemy = new Player();
    enemy->set_name("Enemy");
    cout << (*enemy).get_name() << endl;
    
    Player *boss = new Player("Boss", 1000, 250);
    boss->set_name("Boss");
    cout << boss->get_name() << endl;
    
    delete enemy;
    delete boss;
    
 return 0;   
}


/* Friend of a Class
 * (1) A function or class that has access to private class member and that function of or class is NOT a member of the class  
 *     it is accessing.
 * (2) Function: Can be regular non-membr functions or can be member methods of another class
 * (3) Class: Another class can have access to private class members
 * (4) Friendship must be granted not taken 
 *      - Declared explicitly in the class that is granting friendship
 *      - Declared in the function prototype with the keyword 'friend'
 * (5) Friendship is not symmetric
 *      - Must be explicitly granted i.e. if A is a friend of B, B is NOT a friend of A
 * (6) Friendship is not transitive
 *      - i.e. if A is a friend of B and B is a friend of C, then A is NOT a friend of C
*/

