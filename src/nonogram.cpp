#include "nonogram.hpp"
#include <random>


    Nonogram::Nonogram(size_t h, size_t w): height{h}, width{w} {
        board = std::vector<std::vector<bool>>();
        for(size_t i =0; i< height; i++){
            board.push_back(std::vector<bool>());
            for(size_t j =0; j<width; j++){
                board[i].push_back(false);
            }
        }
        hclues = std::vector<std::vector<int>>();
        vclues = std::vector<std::vector<int>>();
        for(size_t i =0; i<height;i++){
            hclues.push_back(std::vector<int>());
        }
        for(size_t i =0; i<width;i++){
            vclues.push_back(std::vector<int>());
        }
        this->updateHints();

    }
    
    Nonogram::~Nonogram(){
    }

    void Nonogram::display(){
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
                strboard+=(board[i][j]?"██":"░░");
            }
            strboard+="\n";
        }
        std::cout<<std::endl<<strboard<<std::endl;
    }

    void Nonogram::set(size_t x, size_t y){
        if(x>=1&&x<=height&&y>=1&&y<=width){
            board[x-1][y-1] = true;
        }
        this->updateHints();
    }

    void Nonogram::scramble(){
        for(size_t i =0; i< height; i++){
            for(size_t j =0; j<width; j++){
                board[i][j] = rand()%2==0;
                // board[i][j] = rand()%2==0||rand()%3==0;
            }
        }
        this->updateHints();
    }

    void Nonogram::updateHints(){
        //remake the hints based on current board.
        for(size_t i =0; i< height; i++){
            hclues[i].clear();
            size_t len = 0;
            for(size_t j =0; j<width; j++){
                if(board[i][j]){
                    len++;
                }
                else if(len>0){
                    hclues[i].push_back(len);
                    len = 0;
                }
            }
            if(len>0){
                hclues[i].push_back(len);
                len = 0;
            }
        }
        for(size_t i =0; i< width; i++){
            vclues[i].clear();
            size_t len = 0;
            for(size_t j =0; j<height; j++){
                if(board[j][i]){
                    len++;
                }
                else if(len>0){
                    vclues[i].push_back(len);
                    len = 0;
                }
            }
            if(len>0){
                vclues[i].push_back(len);
                len = 0;
            }
        }
    }

    size_t Nonogram::getHeight(){
        return height;
    }

    size_t Nonogram::getWidth(){
        return width;
    }

    std::vector<std::vector<int>> Nonogram::getHorizontalClues(){
        return hclues;
    }

    std::vector<std::vector<int>> Nonogram::getVerticalClues(){
        return vclues;
    }

    bool Nonogram::get(size_t x, size_t y){
        if(x>=1&&x<=height&&y>=1&&y<=width){
            return board[x-1][y-1];
        }
        return false;
    }

    Line::Line(size_t n, bool h){
        data = std::vector<bool>();
        horizontal = h;
        for(size_t i = 0; i<n;i++){
            data.push_back(false);
        }
        length = n;
    }

    Line::Line(std::vector<bool> d, bool h){
        data = d;
        horizontal = h;
        length = d.size();
    }

    Line::~Line(){

    }

    Line Line::operator&(Line o){
        if(!compatible(o)){
            throw 2;
        }
        std::vector<bool> newline;
        for(size_t i = 0; i< length; i++){
            newline.push_back(data[i]&o.data[i]);
        }
        return Line(newline,horizontal);
    }

    bool Line::implies(Line o){
        if(!compatible(o)){
            throw 2;
        }
        bool ret = true;
        for(size_t i = 0; i<length; i++){
            ret&=(!data[i])|o.data[i];
        }
        return ret;
    }

    size_t Line::size(){
        return length;
    }

    bool Line::at(size_t n){
        if(n>=1&&n<=length){
            return data[n-1];
        }
        return false;
    }

    Line Nonogram::getLine(size_t n, bool horizontal){
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

    Line Line::operator|(Line o){
        if(!compatible(o)){
            throw 2;
        }
        std::vector<bool> newline;
        for(size_t i = 0; i< length; i++){
            newline.push_back(data[i]|o.data[i]);
        }
        return Line(newline,horizontal);
    }

    Line Line::operator!(){
        std::vector<bool> newline;
        for(size_t i = 0; i< length; i++){
            newline.push_back(!data[i]);
        }
        return Line(newline,horizontal);
    }

    bool Line::compatible(Line o){
        return (horizontal==o.horizontal) && (length==o.length);
    }

    bool Line::valid(size_t hused, size_t bitsused, std::vector<int> hint, bool debug){
        // if(debug){
        //     std::cout<<hused<<" "<<bitsused<<std::endl;
        // }
        if(hused==hint.size()&&(bitsused==length+1)){
            if(debug){
                std::cout<<"Valid use found "<<hused<<" "<<bitsused<<std::endl;
            }
            return true;
        }
        if(bitsused>length||hused>hint.size()){
            // if(debug){
            //     std::cout<<"Invalid use found"<<std::endl;
            // }
            return false;
        }
        if(hused>=hint.size()){
            if(data[bitsused]){
                // if(debug){
                //     std::cout<<"Invalid use found"<<std::endl;
                // }
                return false;
            }
            else{
                return valid(hused, bitsused+1, hint, debug);
            }
        }
        if((bitsused+hint[hused]<length&&data[bitsused+hint[hused]])){
            if(data[bitsused]){
                // if(debug){
                //     std::cout<<"Invalid use found"<<std::endl;
                // }
                return false;
            }
            else{
                return valid(hused, bitsused+1, hint, debug);
            }
        }
        if(data[bitsused]){
            // std::cout<<"Must use hint"<<std::endl;
            return valid(hused+1,bitsused+hint[hused]+1, hint, debug);
        }
        else{
            // std::cout<<"Can use hint"<<std::endl;
            return valid(hused, bitsused+1, hint, debug)||valid(hused+1,bitsused+hint[hused]+1, hint, debug);
        }
    }