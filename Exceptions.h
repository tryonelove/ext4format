#include <iostream>
#include <exception>

using namespace std;

class CantOpenDevice: public exception {
    std::string m_error;
    public:
        CantOpenDevice(){
            m_error = "Can't open device.";
        }
        
        const char* what() {
            return m_error.c_str();
        }
};