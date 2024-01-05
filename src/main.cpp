#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{   
    int controller=0;
    cout << endl << "| help: 1.Search 2.tommorow's task 3.All at Once 4.Exit |"<< endl;
    for (size_t i = 0; i < 57; i++)
    {
        cout << "*";
    }
    cout << endl << "Today date:" << endl;
    for (size_t i = 0; i < 30; i++)
    {
        cout << "*";
    }
    cout << endl << "Todays Task:";
    cout << endl ;
    for (size_t i = 0; i < 57; i++)
    {
        cout << "*";
    }
    cout << endl ;
    cin >> controller;
    while (controller == 4)
    {
        break;
    }
    
    return 0;
}
