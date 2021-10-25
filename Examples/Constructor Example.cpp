#include <iostream> 

using namespace std; // so that dont have to do std::cout every single time

class coordinate {
public:
    int x,y;
    
    coordinate() { // constructor initializer
        x = 0;
        y = 0;
    }

    coordinate(int X, int Y) { // constructor w/ parameters
        x = X;
        y = Y;
    }

    void print() {
        cout << x << ", " << y << endl;

    }

} ;

int main() {
    coordinate billy(1,2);
    billy.print();
}
