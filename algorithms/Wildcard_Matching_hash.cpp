#include<string>
#include<iostream>
#include<algorithm>
#include"profiler.h"
#include"verify.h"
#include<unordered_map>
using namespace std;
class Solution {
public:


    struct hash{
        using HASHTYPE=unordered_map<char,hash*>;
        HASHTYPE h;
        string value;
        void insert(const string& s){
            auto current=this;
            for(char c:s){
                if(current->h[c]==nullptr){
                    current->h[c]=new hash();
                }
                current=current->h[c];
            }
            current->value=s;

        }

        auto collapsed(string_view p,char c){
            auto iter = find_if(begin(p),end(p),[&](auto v){return v!=c;});
            return distance(begin(p),iter);
        }
        bool handlesinglereplacer(string_view p){

           for(auto& ha:h){
               {
                   bool found =ha.second->findPattern(p.substr(1));
                   if(found){
                       return found;
                   }
               }
           }
           return false;
        }
        bool handleWildcharReplacer(string_view p){
            auto nextvalidcharindex=collapsed(p,'*');
            if(p.length()<=nextvalidcharindex){
                return true;
            }

            if(findPattern(p.substr(nextvalidcharindex))){
                return true;
            }

            for(auto& ha:h){
                bool found =ha.second->findPattern(p.substr(nextvalidcharindex-1));
                if(found){
                    return found;
                }
            }
            return false;
        }
        bool isendofstring(){
            return h.empty();
        }
        bool findPattern(string_view p){
            if(p.length()==0){
                return isendofstring();
            }

            auto c =p[0];
            if(c=='*'){
               return handleWildcharReplacer(p);
            }
            if(c=='?'){
                return handlesinglereplacer(p);
            }

            if(h.find(c)==end(h)){
                return false;
            }
            auto& nextpath=h[c];
            if(p.length()==1){
                return !nextpath->value.empty();
            }
            return h[c]->findPattern(p.substr(1));

        }

    };
    bool isMatch(string s, string p) {
        if(p.empty()){
            return s.empty();
        }
        hash h;
        h.insert(s);
        return h.findPattern(p);
    }
};
