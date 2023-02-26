#include <iostream>
#include <map>
using namespace std;
long long travelCount(int row, int column,map<pair<int,int>,long long>& cache){
    if(cache.find(pair{row,column})!= end(cache)){
        return cache[{row,column}];
    }
    if(row<1 || column<1){
        return 0;
    }
    if(row==1 ||column ==1){
        return 1;
    }
    return cache[{row,column}]= travelCount(row-1,column,cache)+travelCount(row,column-1,cache);

}

//int main(){

//    auto print=[](auto a, auto b){
//        cout<<"travelCount("<<a<<","<<b<<") =";
//        map<pair<int,int>,long long> cache;
//        cout<<travelCount(a,b,cache)<<"\n";

//    };

//    print(0,0);
//    print(0,1);
//    print(1,0);
//    print(1,1);
//    print(2,2);
//    print(2,3);
//    print(5,6);
//    print(18,18);
//}
