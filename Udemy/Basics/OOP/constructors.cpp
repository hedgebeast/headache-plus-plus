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
 * **************************************************  DESTRUCTORS **************************************************
 * (1) Special member method
 * (2) Same name as Class preceded by a ~
 * (3) Invoked automatically when an object is destroyed
 * (4) No return type and no parameters
 * (5) Only 1 destructor is allowed per class (cannot overload)
 * (6) Useful to release memory and other resources
 ********************************************************************************************************************/

class Player{
private:
    string name;
    int health;
    int xp;
    
public:
    void set_name(string name_val){name=name_val;}
    string get_name(){return name;}

    //Overloaded Constructors
    Player(){
        cout << "Constructor with no argument called!" << endl;
        name = "None";
        health = 0;
        xp = 0;
    }
    Player(string arg1){
        cout << "Constructor with 1 string argument called!" << endl;
        name = arg1;

    }
    Player(string arg1, int arg2, int arg3){
        cout << "Constructor with 3 arguments called!" << endl;
        name = arg1;
        health = arg2;
        xp = arg3;
    }
    
    ~Player(){                  //Destructor
        cout << "Destructor called for "<< name << endl; 
    }
};


int main(){
    {
        Player Dudu;    //C++ will generate a Default Constructor that does nothing
        cout << Dudu.get_name() << endl;
        Dudu.set_name("Dudu");
        cout << Dudu.get_name() << endl;
    }
    
    {
        Player Bubu;
        Bubu.set_name("Bubu");
        
        Player Hero("Hero");
        cout << Hero.get_name() << endl; 
        Hero.set_name("God");
        cout << Hero.get_name() << endl;
        
        Player Villain("Villain", 100, 15);
        Villain.set_name("Devil");
    }
    
    
    Player *enemy = new Player();
    enemy->set_name("Enemy");
    cout << (*enemy).get_name() << endl;
    
    Player *boss = new Player("Boss", 1000, 250);
    boss->set_name("BOSS");
    cout << boss->get_name() << endl;
    
    delete enemy;
    delete boss;
    
 return 0;   
}