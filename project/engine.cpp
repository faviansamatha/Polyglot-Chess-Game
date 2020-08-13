#include <iostream>
#include <string>
#include <cstring>

#define SIZE 8

using namespace std;


class ChessState{

    public: 
    

    class Pawn{

    };
    class Knight{

    };
    class Bishop{

    };

    class Rook{

    };

    class Queen{

    };

    class King{

    }; 

    ChessState(int board[SIZE][SIZE]){


    }

};


extern "C"
const void free_pointer (char* ptr){

    delete ptr; 
}


char* alterHello(char* name){
    char hello[] = "Hello ";
    char excla[] = "!\n";
    // char *greeting = new char[ strlen(name) + strlen(hello) + strlen(excla) + 1 ];
    char *greeting = new char[( strlen(name) + strlen(hello) + strlen(excla) + 1)];
    if( greeting == NULL) exit(1);
    strcpy( greeting , hello);
    strcat(greeting, name);
    strcat(greeting, excla);

    return greeting;


}

void initializeBoard(int board[SIZE][SIZE]){

    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 8; j++){

            board[i][j] = 0;
        }
    }
}

// Board is represented with integers:
//      0 = empty
//      1 = White Pawn
//     -1 = Black Pawn
//      3 = White Knight
//     -3 = Black Knight
//      4 = White Bishop 
//     -4 = Black Bishop
//      5 = White Rook
//     -5 = Black Rook 
//      9 = White Queen
//     -9 = Black Queen
//  10000 = White King
// -10000 = Black King

// This function converts the string to an 8/8 board
void convertBoard(char* sBoard, int board[8][8]){

    int index = 0;

    for(int i = 0; i < SIZE; i++){

        for(int j = 0; j < SIZE; j++){

            char char1 = sBoard[index];
            char char2 = sBoard[index+1];

            if(char1 == '0' && char2 == '0'){

                board[i][j] = 0;
            }
            else if (char1 == 'w' && char2 == 'P'){
                
                board[i][j] = 1;
            }
            else if (char1 == 'b' && char2 == 'P'){
                
                board[i][j] = -1;
            }
            else if (char1 == 'w' && char2 == 'R'){
                
                board[i][j] = 5;
            }
            else if (char1 == 'b' && char2 == 'R'){
                
                board[i][j] = -5;
            }
            else if (char1 == 'w' && char2 == 'B'){
                
                board[i][j] = 4;
            }
            else if (char1 == 'b' && char2 == 'B'){
                
                board[i][j] = -4;
            }
            else if (char1 == 'w' && char2 == 'N'){
                
                board[i][j] = 3;
            }
            else if (char1 == 'b' && char2 == 'N'){
                
                board[i][j] = -3;
            }
            else if (char1 == 'w' && char2 == 'Q'){
                
                board[i][j] = 9;
            }
            else if (char1 == 'b' && char2 == 'Q'){
                
                board[i][j] = -9;
            }
            else if (char1 == 'w' && char2 == 'K'){
                
                board[i][j] = 10000;
            }
            else if (char1 == 'b' && char2 == 'K'){
                
                board[i][j] = -10000;
            }
            index = index +2;

        }
        
    }

}

void printBoard(int board[8][8]){

    for(int i = 0; i < SIZE; i++){
        
        for(int j = 0; j < SIZE; j++){

          cout << board[i][j] << " ";  
        }
        cout << endl;
    }
}


extern "C"
const char* sendMove(char* sBoard)
{ 

    int board[8][8];
    initializeBoard(board);
    convertBoard(sBoard, board);

    char *greeting = alterHello(sBoard);
    return greeting;
}



int main(){

    char buffer[129] = "bRbNbBbQbKbBbNbRbPbPbPbPbPbPbPbP0000000000000000000000000000000000000000000000000000000000000000wPwPwPwPwPwPwPwPwRwNwBwQwKwBwNwR";
    
    int testBoard[8][8];
    initializeBoard(testBoard);
    
    convertBoard(buffer, testBoard);

    printBoard(testBoard);
    // cout << endl << buffer[128];

}