#include <iostream>

using namespace std;

template<typename T>
void fun(const T& data) {

}

int main(void ) {
    fun<int>(123);
}

