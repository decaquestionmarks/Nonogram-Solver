#include "nonogram.hpp"
#include "solver.hpp"
#include <windows.h>
#include <time.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    size_t w = 10;
    size_t h = 10;
    std::cin>>w>>h;
    while(true){
        Nonogram n = Nonogram(h,w);
        n.scramble();
        n.display();
        
        Solver s= Solver(n);
        s.display(false);
        getchar();
        std::cout<<"Your Turn."<<std::endl;
        while(!s.correct()){
            // s.stepBoard();
            // s.display(false);
            for(size_t i = 0; i<h; i++){
                s.solveLine(i,true);
            }
            s.display(false);
            getchar();
            for(size_t i = 0; i<w; i++){
                s.solveLine(i,false);
            }
            s.display(false);
            getchar();
        }
    }
}