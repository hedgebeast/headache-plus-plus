#include <iostream>
#include <vector>

using namespace std;

class Shape {                   //Abstract Base Class now i.e. CANNOT do this: Shape s; and Share *p = new Shape();
public:
    virtual void draw() = 0;    //pure virtual function (force derived classes to override)
    virtual void rotate() = 0;  //pure virtual function
    
    virtual ~Shape(){}
};

class Open_Shape: public Shape{
public:
    virtual ~Open_Shape(){}
};

class Closed_Shape: public Shape{
public:
    virtual ~Closed_Shape(){}
};

class Line: public Open_Shape{
public:
    virtual void draw() override{
        cout << "Drawing a line" << endl; 
    }
    
    virtual void rotate() override {
        cout << "Rotating a line" << endl;
    }
    
    virtual ~Line(){}
};

class Circle: public Closed_Shape{
public:
    virtual void draw() override{
        cout << "Drawing a circle" << endl; 
    }
    
    virtual void rotate() override {
        cout << "Rotating a circle" << endl;
    }
    
    virtual ~Circle(){}
};

class Square: public Closed_Shape{
public:
    virtual void draw() override{
        cout << "Drawing a square" << endl; 
    }
    
    virtual void rotate() override {
        cout << "Rotating a square" << endl;
    }
    
    virtual ~Square(){}
};


int main(){
    
    Circle c;
    c.draw();
    
    Shape *ptr = new Circle();
    ptr->draw();
    ptr->rotate();
    
    delete ptr;
    
    Shape *s1 = new Circle();
    Shape *s2 = new Line();
    Shape *s3 = new Square();
    
    vector<Shape *> shapes {s1, s2, s3};
    for(const auto shape:shapes){
        shape->draw();
        shape->rotate();
    }
        
    delete s1;
    delete s2;
    delete s3;
    
    /********************** Using Class as an Interface **********************
     * i.e. An abstract class that has only pure virtual functions!
     * These functions provide a general set of services to the user of the class (provided as public)
     * Each subclass is free to implement these services as needed
     * Every service (method) must be implemented
     * The service type information is strictly enforced
    *************************************************************************/ 
    
    return 0;
}