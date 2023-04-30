#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include<numeric>
using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {

       int i=0;
       bool forward=true;
       vector<string> rowstrings(numRows);
       while(i<s.length()){
           if(forward){
               int j=0;
               while(j<numRows && i <s.length()){
                   rowstrings[j++].append(1,s[i++]);
               }
               forward=false;
           }else{
               int j=numRows-2;
               while(j>0 && i <s.length()){
                   rowstrings[j--].append(1,s[i++]);
               }
               forward=true;
           }
       }
       
       return std::accumulate(begin(rowstrings),end(rowstrings),string(),[](auto s, auto& v){
          return s+v;
       });
    }
};
#if 0
int main()
{
    auto print = [](auto str,auto rows){
        cout<<str<<" for rows "<<rows<< "\n";
        auto converted= Solution().convert(str,rows);
        cout << converted<<"\n";
        return converted;
    };

    cout << ("asbahhli" == print("abhilash",4))<<"\n";
    cout << ("abhilash" == print("abhilash",8))<<"\n";
    cout << ("abhilash" == print("abhilash",1))<<"\n";
    cout << ("ahlsbiah" == print("abhilash",2))<<"\n";
}
#endif
