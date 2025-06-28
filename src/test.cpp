#include "nonogram.hpp"
#include "solver.hpp"
#include <windows.h>
#include <time.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(0);

    //Test 1
    Nonogram n = Nonogram(10,10);
    n.scramble();
    n.display();
    Solver s= Solver(n);
    s.display(false);

    for(int i= 0 ;i< 100; i++){
        int a;
        std::cin>>a;
        s.solveLine(a-1,false);
        s.display(false);
        // std::cout<<a<<" "<<b<<std::endl;
        // int c;
        // std::cin>>c;
    }

    
    
}