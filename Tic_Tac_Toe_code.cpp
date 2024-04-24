#include <iostream>


using namespace std;


char symbolconversion[7]{//the conversion table between number indecies and symbols 0 is used for empty cell and 
                        ' ',
                        'X',
                        'O',
                        '@',
                        '=',
                        '+',
                        '-'
};




class cell {
private:
    int value;
public:
    cell() {
        value = 0;
    }
    int get() {
        return value;
    }

    void set(int newVal) {
        value = newVal;
    }
    char getSym() {
        return symbolconversion[value];
    }
};

void printBoard(cell** board, int size_rows, int size_columns) {//a basic 2d array printing function
    for (int i = 0; i < size_rows; i++) {
        for (int j = 0; j < size_columns; j++) {
            cout << "|" << board[i][j].getSym();
        }
        cout << "|" << endl;
    }
}

//checks whether someone has won along the horizontal and vertical axis returns the id of the winner or 0 if noone won
int linearVictoryCheck(cell** board, int size_rows, int size_columns, int win) {//the function is fed the game board the game board size and the amount required to win
    int bufferVal = 0;
    int buffer;
    for (int i = 0; i < size_rows; i++) {
        buffer = 0;
        for (int j = 0; j < size_columns; j++) {
            if (board[i][j].get() == bufferVal) { buffer++; }
            else { bufferVal = board[i][j].get(); buffer = 1; }
            if (bufferVal != 0 && buffer >= win) {
                return bufferVal;
            }
        }
    }
    for (int i = 0; i < size_columns; i++) {
        buffer = 0;
        for (int j = 0; j < size_rows; j++) {
            if (board[j][i].get() == bufferVal) { buffer++; }
            else { bufferVal = board[i][j].get(); buffer = 1; }
            if (bufferVal != 0 && buffer >= win) {
                return bufferVal;
            }
        }
    }
    return 0;
}

void gameMoves(int pCount, cell** board, int size_row, int size_column, int win) {//plays the game... what can i say...
    int x, y;
    for (int i = 1; i <= pCount; i++) {
        cout << "player " << i << " please select your row and column :";
        cin >> x >> y;
        while (x - 1 > size_row || y - 1 > size_column) {
            cout << "ERROR try again:";
            cin >> x >> y;
        }
        while (1) {
            if (x - 1 <= size_row && y - 1 <= size_column) {
                if (board[x - 1][y - 1].get() == 0) {
                    break;
                }
                cout << "that cell is occupied!";
            }
            else cout << "ERROR try again:";
            cin >> x >> y;
        }
        board[x - 1][y - 1].set(i);
        printBoard(board, size_row, size_column);
        if (linearVictoryCheck(board, size_row, size_column, win) > 0) { cout << "Victory CCHEKC!!!" << linearVictoryCheck(board, size_row, size_column, win) << endl; }
    }
}


int main() {
    int gameSize_rows, gameSize_columns, playerCount, winCondition;
    cin >> gameSize_rows >> gameSize_columns >> playerCount >> winCondition;
    cell** board = new cell * [gameSize_rows];
    for (int i = 0; i < gameSize_rows; i++) {
        board[i] = new cell[gameSize_columns];
    }
    printBoard(board, gameSize_rows, gameSize_columns);
    while (1) {
        gameMoves(playerCount, board, gameSize_rows, gameSize_columns, winCondition);
    }
}