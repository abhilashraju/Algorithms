#include <iostream>
#include <vector>
using namespace std;
class Solution {
template<typename Iter>
void ring(vector<vector<int>>& arr,int sr,int er,int sc,int ec,Iter iter){
    int rowCounter=sr;
    int colCounter=sc;

    while(colCounter<ec){
        *iter=arr[sr][colCounter++];
    }

    rowCounter++;
    if(rowCounter>=er) return;
    colCounter=ec-1;
    while(rowCounter<er){
        *iter=arr[rowCounter++][colCounter];
    }
    colCounter--;
    if(colCounter < sc ) return;
    rowCounter=er-1;

    while(sc<=colCounter){
        *iter=arr[rowCounter][colCounter--];
    }
    rowCounter--;
    colCounter=sc;
    while(sr<rowCounter){
        *iter=arr[rowCounter--][colCounter];
    }
}
template<typename Iter>
void spiral(vector<vector<int>>& arr,Iter iter){
  int sr=0;
  int er=arr.size();
  int sc=0;
  int ec=arr[0].size();

  while(sr < er && sc < ec){
      ring(arr,sr,er,sc,ec,iter);
      sr++;er--;sc++,ec--;
  }

}
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        std::vector<int> output;
        spiral(matrix,std::back_inserter(output));
        return output;
    }
};

void print(vector<vector<int>>& arr){

    for(auto e:Solution().spiralOrder(arr)){
        cout<<e<<",";
    }
    cout<<"\n";
}
#if 0
int main(){

    vector<vector<int>> arr={{1,2,3,4},
                  {5,6,7,8},
                  {9,10,11,12}};
    print(arr);

    vector<vector<int>> arr2={{1,2,3,4},
                  {5,6,7,8},
                  };
    print(arr2);

    vector<vector<int>> arr3={{1}};
    print(arr3);

    vector<vector<int>> arr4={{1},
                   {2},
                   {3}};
    print(arr4);

    vector<vector<int>> arr5={{1,2,3}};
    print(arr5);

    vector<vector<int>> arr6={{1,1,1,1,1,1,1,1,1,1},
                    {1,2,2,2,2,2,2,2,2,1},
                    {1,2,3,3,3,3,3,3,2,1},
                    {1,2,3,4,4,4,4,3,2,1},
                    {1,2,3,4,4,4,4,3,2,1},
                    {1,2,3,3,3,3,3,3,2,1},
                    {1,2,2,2,2,2,2,2,2,1},
                    {1,1,1,1,1,1,1,1,1,1},
                   };
    print(arr6);
}
#endif
