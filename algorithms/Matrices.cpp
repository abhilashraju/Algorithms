#include <iostream>
#include <vector>
using namespace std;
template<int M,int N,typename Iter>
void ring(int (&arr)[M][N],int sr,int er,int sc,int ec,Iter iter){
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
template<int M,int N,typename Iter>
void spiral(int (&m)[M][N],Iter iter){
  int sr=0;
  int er=M;
  int sc=0;
  int ec=N;

  while(sr < er && sc < ec){
      ring(m,sr,er,sc,ec,iter);
      sr++;er--;sc++,ec--;
  }

}
template<int M,int N>
void print(int (&arr)[M][N]){
    std::vector<int> output;
    spiral(arr,std::back_inserter(output));
    for(auto e:output){
        cout<<e<<",";
    }
    cout<<"\n";
}
#if(0)
int main(){

    int arr[][4]={{1,2,3,4},
                  {5,6,7,8},
                  {9,10,11,12}};
    print(arr);

    int arr2[][4]={{1,2,3,4},
                  {5,6,7,8},
                  };
    print(arr2);

    int arr3[][1]={{1}};
    print(arr3);

    int arr4[][1]={{1},
                   {2},
                   {3}};
    print(arr4);

    int arr5[][3]={{1,2,3}};
    print(arr5);

    int arr6[][10]={{1,1,1,1,1,1,1,1,1,1},
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
