#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    void printBoard(vector<vector<char>>& board){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout<<board[i][j]<<",";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    vector<char> availOptions(vector<vector<char>>& board,int row, int column){
        auto gr=row/3;
        auto gc =column/3;
        bool a[10]={false};
        for(int i=gr*3;i<(gr+1)*3;i++){
            for(int j=gc*3;j<(gc+1)*3;j++){
                if(board[i][j] !='.'){
                    a[board[i][j]-'1']=true;
                }
            }
        }
        for(int j=0;j<9;j++){
             if(board[row][j] !='.'){
                a[board[row][j]-'1']=true;
             }
        }
        for(int i=0;i<9;i++){
             if(board[i][column] !='.'){
                a[board[i][column]-'1']=true;
             }
        }
        vector<char> candidates;
        for(int i=0;i<9;i++){
            if(!a[i]){
                candidates.push_back('1'+i);
            }
        }
        return candidates;
    }
    pair<int,int> findNextToFill(vector<vector<char>>& board){
        for(int newi=0;newi<9;newi++){
            for(int newj=0;newj<9;newj++){
                if(board[newi][newj]=='.'){
                    return {newi,newj};
                }
            }
        }
        return {-1,-1};
    }
    bool tryFill(vector<vector<char>>& board,int i,int j,char c){
        board[i][j]=c;
        auto[newi,newj]=findNextToFill(board);
        if(newi==-1){
            return true;
        }

        auto options=availOptions(board,newi,newj);
        for(auto o:options){
            if(tryFill(board,newi,newj,o)){
                return true;
            }
        }
        board[i][j]='.';
        return false;

    }
    void solveSudoku(vector<vector<char>>& board) {
       auto iter=find(begin(board[0]),end(board[0]),'.');
       int col=distance(begin(board[0]),iter);
       for(auto o:availOptions(board,0,col)){
            if(tryFill(board,0,col,o)){
                break;
            }
       }

    }
};
#if 0
int main(){

    auto print =[](auto& board){
        cout<<"Input\n";
        Solution().printBoard(board);
        cout <<"\n Output\n";
        Solution().solveSudoku(board);
        Solution().printBoard(board);
    };
    vector<vector<char>> input={
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    print(input);


}
#endif
