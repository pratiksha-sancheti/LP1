#include <iostream>
using namespace std;

bool isSafe(int board[][10], int i, int j, int n)
{
    // you can check for col
    for (int row = 0; row < i; row++)
    {
        if (board[row][j] == 1)
        {
            return false;
        }
    }
    int x = i;
    int y = j;
    // you can check for left diagonal
    while (x >= 0 && y >= 0)
    {
        if (board[x][y] == 1)
            return false;
        x--;
        y--;
    }
    // you can check for right diagonal
    x = i;
    y = j;
    while (x >= 0 && y < n)
    {
        if (board[x][y] == 1)
            return false;
        x--;
        y++;
    }
    // the position is now safe, col and diagonals
    return true;
}

bool solveNQueen(int board[][10], int i, int n)
{
    // base case
    if (i == n)
    {
        // you have sucessfully place queens in n rows (0...n-1)
        // print the board
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 1)
                {
                    cout << "Q ";
                }
                else
                {
                    cout << "_ ";
                }
            }
            cout << endl;
        }

        return true;
    }
    // recursive case
    // assume that next row will fill
    // try to place the queen in current row and call on the remaining part which will be solved by recursion
    for (int j = 0; j < n; j++)
    {
        // I have to check if i,j th position is safe to placed queen or not
        if (isSafe(board, i, j, n))
        {
            // place the queen - assuming i,j is right position
            board[i][j] = 1;
            bool nextQueenRakhPare = solveNQueen(board, i + 1, n);
            if (nextQueenRakhPare)
            {
                return true;
            }
            // means i,j is not the right postion - assumption is wrong
            board[i][j] = 0; // backtrack
        }
    }
    return false;
}

int main()
{
    int n; // no of queens
    cin >> n;
    int board[10][10] = {0};
    solveNQueen(board, 0, n);
    return 0;
}