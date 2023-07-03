#include <iostream>

using namespace std;

template <class T>
class Vector{
public:
    Vector();                      // creates an empty vector
    Vector(int size);              // creates a vector for holding 'size' elements
    Vector(const Vector& r);       // the copy ctor
    ~Vector();                     // destructs the vector 
    T& operator[](int index);      // accesses the specified element without bounds checking
    T& at(int index);              // accesses the specified element, throws an exception of
                                    // type 'std::out_of_range' when index <0 or >=m_nSize
    int size() const;              // return the size of the container
    void push_back(const T& x);    // adds an element to the end 
    void clear();                  // clears the contents
    bool empty() const;            // checks whether the container is empty 
    private:
    void inflate();                // expand the storage of the container to a new capacity,
                                    // e.g. 2*m_nCapacity
    T *m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the total number of elements that can be held in the
                                    // allocated storage
};

template <class T>
Vector<T>::Vector(): m_pElements(NULL), m_nSize(0), m_nCapacity(0) {}

template <class T>
Vector<T>::Vector(int size): m_pElements(NULL), m_nSize(0), m_nCapacity(0){
    if(m_nCapacity < size)  inflate();
    m_nSize = size;
}

template <class T>
Vector<T>::Vector(const Vector& r): m_pElements(NULL), m_nSize(0), m_nCapacity(0){
    *this = r;
}

template <class T>
Vector<T>::~Vector(){
    clear();
}

template <class T>
T& Vector<T>::operator[](int index){
    return m_pElements[index];
}

template <class T>
T& Vector<T>::at(int index){
    if(index < 0 || index >= m_nSize){
        throw out_of_range("Index out of range");
    }
    return m_pElements[index];
}

template <class T>
int Vector<T>::size() const{
    return m_nSize;
}

template <class T>
void Vector<T>::push_back(const T& x){
    if(m_nSize == m_nCapacity){
        inflate();
    }
    m_pElements[m_nSize++] = x;
}

template <class T>
void Vector<T>::clear(){
    delete[] m_pElements;
    m_pElements = NULL;
    m_nSize = 0;
    m_nCapacity = 0;
}

template <class T>
bool Vector<T>::empty() const{
    return m_nSize == 0;
}

template <class T>
void Vector<T>::inflate(){
    int newCapacity = (m_nCapacity == 0 ? 1 : m_nCapacity * 2);
    T* newElements = new T[newCapacity];
    for(int i = 0; i < m_nSize; i++){
        newElements[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = newElements;
    m_nCapacity = newCapacity;
}


int main() {
    // Test default constructor
    Vector<int> v1;
    cout << "v1 size: " << v1.size() << endl;
    cout << "v1 empty: " << v1.empty() << endl;

    // Test constructor with size argument
    Vector<int> v2(10);
    cout << "v2 size: " << v2.size() << endl;
    cout << "v2 empty: " << v2.empty() << endl;

    // Test copy constructor
    Vector<int> v3(v2);
    cout << "v3 size: " << v3.size() << endl;
    cout << "v3 empty: " << v3.empty() << endl;

    // Test push_back
    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
    }
    cout << "v1 size: " << v1.size() << endl;
    cout << "v1 empty: " << v1.empty() << endl;

    // Test operator[]
    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << " ";
    }
    cout << endl;

    // Test at
    try{
        v1.at(10);
    }
    catch (std::out_of_range& e){
        cout << "Exception caught: " << e.what() << endl;
    }

    // Test clear
    v1.clear();
    cout << "v1 size: " << v1.size() << endl;
    cout << "v1 empty: " << v1.empty() << endl;

    return 0;
}