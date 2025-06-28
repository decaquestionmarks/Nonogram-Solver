#include "nonogram.hpp"
#include "solver.hpp"
#include <algorithm>
#include <numeric>
#include <functional>

    Solver::Solver(Nonogram n): puzzle{n}{
        board = std::vector<std::vector<bool>>();
        height = n.getHeight();
        width = n.getWidth();
        for(size_t i =0; i< height; i++){
            board.push_back(std::vector<bool>());
            xboard.push_back(std::vector<bool>());
            for(size_t j =0; j<width; j++){
                board[i].push_back(false);
                xboard[i].push_back(false);
            }
        }
        hclues = n.getHorizontalClues();
        vclues = n.getVerticalClues();
    }
    
    Solver::~Solver(){
    }

    void Solver::display(bool debug){
        std::string strboard;
        //settle horizontal hints display
        std::vector<std::string> hhints;
        size_t hlongest = 0;
        for(size_t i = 0; i< height;i++){
            std::string line = "";
            for(auto s: this->hclues[i]){
                line += (std::to_string(s)+" ");
            }
            hlongest = std::max(hlongest, line.length());
            hhints.push_back(line);
        }
        
        //vertical hint display
        size_t vlongest = 0;
        for(size_t i = 0; i< width;i++){
            vlongest = std::max(vlongest, vclues[i].size());
        }
        for(size_t i = 0; i< vlongest; i++){
            strboard+=std::string(hlongest, ' ');
            for(size_t j = 0; j<width;j++){
                if(i<vclues[j].size()){
                    if(vclues[j][i]<10){
                        strboard+=std::to_string(vclues[j][i])+" ";
                    }
                    else{
                        strboard+=std::to_string(vclues[j][i]);
                    }
                }
                else{
                    strboard+="  ";
                }
            }
            strboard+="\n";
        }

        //create board display
        for(size_t i =0; i< height; i++){
            strboard+=hhints[i]+(std::string(hlongest-hhints[i].length(), ' '));
            for(size_t j =0; j<width; j++){
                if(board[i][j]){
                    strboard+="██";
                }
                else if(xboard[i][j]){
                    strboard+="XX";
                }
                else{
                    strboard+="░░";
                }
            }
            strboard+="\n";
        }
        std::cout<<std::endl<<strboard<<std::endl;
        std::cout<<"Is Valid: "<<(valid(debug)?"Yes":"No")<<std::endl;
        std::cout<<"Is Correct: " <<(Partialcorrect()?"Yes":"No")<<std::endl;
    }

    void Solver::flip(size_t x, size_t y){
        if(x>=1&&x<=height&&y>=1&&y<=width){
            board[x-1][y-1] = !board[x-1][y-1];
        }
    }

    bool Solver::valid(bool debug){
        bool pc = true;
        for(size_t i = 0; i<height&&pc; i++){
            if(debug){
                std::cout<<i<<" "<<pc<<std::endl;
            }
            pc&= getLine(i+1,true).valid(0,0,hclues[i],debug);
        }
        for(size_t i = 0; i<width&&pc; i++){
            if(debug){
                std::cout<<i<<" "<<pc<<std::endl;
            }
            pc&= getLine(i+1,false).valid(0,0,vclues[i],debug);
        }
        return pc;
    }

    bool Solver::Partialcorrect(){
        bool pc = true;
        for(size_t i = 0; i<height; i++){
            for(size_t j = 0; j<width; j++){
                pc&= (!board[i][j])|puzzle.get(i+1,j+1);
                // std::cout<<board[i][j]<<" "<<puzzle.get(i+1,j+1)<<" "<<((!board[i][j])|puzzle.get(i+1,j+1))<<std::endl;
            }
        }
        return pc;
    }

    bool Solver::correct(){
        bool pc = true;
        for(size_t i = 0; i<height; i++){
            for(size_t j = 0; j<width; j++){
                pc&= board[i][j]==puzzle.get(i+1,j+1);
                // std::cout<<board[i][j]<<" "<<puzzle.get(i+1,j+1)<<" "<<((board[i][j])==puzzle.get(i+1,j+1))<<std::endl;
            }
        }
        return pc;
    }

    Line Solver::getLine(size_t n, bool horizontal){
        std::vector<bool> newline;
        if(horizontal){
            if(n>=1&&n<=height){
                for(size_t i= 0; i<width; i++){
                    newline.push_back(board[n-1][i]);
                }
            }
        }
        else{
            if(n>=1&&n<=width){
                for(size_t i= 0; i<height; i++){
                    newline.push_back(board[i][n-1]);
                }
            }
        }
        return Line(newline,horizontal);
    }

    void Solver::markx(size_t x, size_t y){
        if(x>=1&&x<=height&&y>=1&&y<=width){
            xboard[x-1][y-1] = !xboard[x-1][y-1];
        }
    }

    Line Solver::getxLine(size_t n, bool horizontal){
        std::vector<bool> newline;
        if(horizontal){
            if(n>=1&&n<=height){
                for(size_t i= 0; i<width; i++){
                    newline.push_back(xboard[n-1][i]);
                }
            }
        }
        else{
            if(n>=1&&n<=width){
                for(size_t i= 0; i<height; i++){
                    newline.push_back(xboard[i][n-1]);
                }
            }
        }
        return Line(newline,horizontal);
    }

    std::vector<std::vector<bool>> Solver::generateAll(const std::vector<int> &hint, size_t n){
        // std::cout<<"???"<<std::endl;
        std::vector<std::vector<bool>> ret;
        // std::cout<<"Here 0"<<std::endl;
        // std::cout<<n<<std::endl<<std::accumulate(hint.begin(),hint.end(),0)<<std::endl<<hint.size()<<std::endl;
        size_t leeway = n - (std::accumulate(hint.begin(),hint.end(),0)+hint.size()-1);
        // std::cout<<"Here 1 "<<leeway<<std::endl;
        //recursion
        for(size_t i = 0; i<=leeway; i++){
            std::vector<bool> instance;
            for(size_t j = 0; j<i;j++){
                instance.push_back(false);
            }
            for(int j = 0; j<hint[0];j++){
                instance.push_back(true);
            }
            while(instance.size()<n){
                instance.push_back(false);
            }
            size_t nextstart = i+hint[0]+1;
            // std::cout<<"Here 2"<<std::endl;
            std::vector<std::vector<bool>> remainders;
            if(hint.size()>1){
                remainders = generateAll(std::vector<int>(hint.begin()+1,hint.end()),n-nextstart);
            }
            else{
                ret.push_back(instance);
            }
            // std::cout<<"Here 3"<<std::endl;
            for(auto r : remainders){
                for(size_t j = 0; j<r.size(); j++){
                    instance[nextstart+j] = r[j];
                }
                // for(auto a : instance){
                //     std::cout<<a<<" ";
                // }
                // std::cout<<std::endl;
                ret.push_back(instance);
            }
        }
        // for(auto i: ret){
        //     for(auto j: i){
        //         std::cout<<j<<" ";
        //     }
        //     std::cout<<std::endl;
        // }
        return ret;
    }

    void Solver::solveLine(size_t n, bool horizontal){
        // std::cout<<"entered"<<std::endl;
        if(horizontal){
            std::vector<std::vector<bool>> boolpossibilities = generateAll(hclues[n],width);
            // for(auto i: boolpossibilities){
            //     for(auto j: i){
            //         std::cout<<j<<" ";
            //     }
            //     std::cout<<std::endl;
            // }
            std::vector<Line> possibilities;
            // std::cout<<"Here 1"<<std::endl;
            std::transform(boolpossibilities.begin(),boolpossibilities.end(),std::back_inserter(possibilities),
                [&](const std::vector<bool>& l){return Line(l,horizontal);});
            // std::cout<<"Here 2"<<std::endl;
            std::vector<Line> realposs;
            std::copy_if(possibilities.begin(),possibilities.end(),std::back_inserter(realposs),
                [&](Line l){return getLine(n+1,horizontal).implies(l)&&getxLine(n+1,horizontal).implies(!l);});
            // std::cout<<"Here 3"<<std::endl;
            if(!realposs.empty()){
                Line fill = std::accumulate(realposs.begin()+1,realposs.end(), realposs[0],
                    [](Line a, Line b){return a&b;});
                // std::cout<<"Here 4"<<std::endl;
                Line xs = !std::accumulate(realposs.begin()+1,realposs.end(), realposs[0],
                    [](Line a, Line b){return a|b;});
                // std::cout<<"Here 5"<<std::endl;
                for(size_t i = 0; i< width; i++){
                    if(fill.at(i+1)&&!board[n][i]){
                        flip(n+1,i+1);
                    }
                    if(xs.at(i+1)&&!xboard[n][i]){
                        markx(n+1,i+1);
                    }
                }
                // std::cout<<"Here 6"<<std::endl;
            }
        }
        else{
            std::vector<std::vector<bool>> boolpossibilities = generateAll(vclues[n],height);
            std::vector<Line> possibilities;
            std::transform(boolpossibilities.begin(),boolpossibilities.end(),std::back_inserter(possibilities),
                [&](std::vector<bool> l){return Line(l,horizontal);});
            std::vector<Line> realposs;
            std::copy_if(possibilities.begin(),possibilities.end(),std::back_inserter(realposs),
                [&](Line l){return getLine(n+1,horizontal).implies(l)&&getxLine(n+1,horizontal).implies(!l);});
            if(!realposs.empty()){
                Line fill = std::accumulate(realposs.begin()+1,realposs.end(), realposs[0],
                    [](Line a, Line b){return a&b;});
                Line xs = !std::accumulate(realposs.begin()+1,realposs.end(), realposs[0],
                    [](Line a, Line b){return a|b;});
                for(size_t i = 0; i< height; i++){
                    if(fill.at(i+1)&&!board[i][n]){
                        flip(i+1,n+1);
                    }
                    if(xs.at(i+1)&&!xboard[i][n]){
                        markx(i+1,n+1);
                    }
                }
            }    
        }
    }

    void Solver::stepBoard(){
        for(size_t i = 0; i<height; i++){
            solveLine(i,true);
        }
        for(size_t i = 0; i<width; i++){
            solveLine(i, false);
        }
    }
