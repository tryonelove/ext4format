#include <iostream>

using namespace std;

class Formatter {
    string formatPath;
    static Formatter* formatter;
    Formatter();
    public:
        static Formatter* getFormatter();

        void setPath(string path);
        string getPath();

        void format();
};