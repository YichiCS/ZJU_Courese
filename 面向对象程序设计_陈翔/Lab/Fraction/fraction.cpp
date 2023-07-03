#include <iostream>

using namespace std;
class  A {
public:
    A(){
        cout << 0 << endl;
    }
    A(const A&){
        cout << 1 << endl;
    }
    A &operator = (const A&){
        cout << 2 << endl;
        return *this;
    }
};


int main(){
    A a1,a2;
    a2= a1;
    A a3 = a2;
}