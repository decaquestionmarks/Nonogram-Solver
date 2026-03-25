#include "hintgroup.hpp"

HintGroup::HintGroup(Direction d): dir{d} {
}

HintGroup::HintGroup(size_t n, Direction d): dir{d}{
    data.resize(n);
}

HintGroup::HintGroup(const std::vector<Hint> &d, Direction di): dir{di}{
    data = d;

}

HintGroup::~HintGroup(){}

size_t HintGroup::size() const{
    return data.size();
}

const Direction HintGroup::getDirection() const{
    return dir;
}

Hint& HintGroup::operator[](size_t i){
    return data[i];
}

const Hint &HintGroup::operator[](size_t i) const{
    return data[i];
}

const std::vector<Hint> &HintGroup::getAllHints() const{
    return data;
}

void HintGroup::findLongest(){
    std::vector<std::string> hhints;
        for(size_t i = 0; i< size();i++){
            std::string line = getHorizPrint(i);
            longest = std::max(longest, line.length());
        }
}

void HintGroup::vertPrint(std::ostream &os, size_t offset) const{
    // std::string strboard{};
    size_t vlongest = 0;
        for(size_t i = 0; i< size();i++){
            vlongest = std::max(vlongest, data[i].size());
        }
        for(size_t i = 0; i< vlongest; i++){
            os<<std::string(offset, ' ');
            for(size_t j = 0; j<size();j++){
                if(i<data[j].size()){
                    Hint h = data[j];
                    if(h[i]<10){
                        os<<std::to_string(h[i])+" ";
                    }
                    else{
                        os<<std::to_string(h[i]);
                    }
                }
                else{
                    os<<"  ";
                }
            }
            os<<std::endl;
        }
}

std::string HintGroup::getHorizPrint(size_t i) const{
    std::string ret{};
    for(auto s: data[i].getAll()){
                ret += (std::to_string(s)+" ");
            }
    return ret+(std::string(longest-ret.length(), ' '));
}
