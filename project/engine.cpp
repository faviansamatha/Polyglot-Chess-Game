#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 8


using namespace std;

// A function to immitate a move and returns points if a piece was taken
int immitateMove( int from_row, int from_col, int to_row, int to_col,  int cur_board[SIZE][SIZE], int future_board[SIZE][SIZE]){

    for(int i = 0; i < SIZE; i++){

        for(int j = 0; j < SIZE; j++){

            future_board[i][j] = cur_board[i][j];
        }

    }
    
    int points = future_board[to_row][to_col];
    future_board[to_row][to_col] = future_board[from_row][from_col];
    future_board[from_row][from_col] = 0;

    return points;
}

bool inCheck(int future_board[SIZE][SIZE],int colour){

        int king_row = -1;
        int king_col = -1;

        if(colour == 1){

            for(int i = 0; i < SIZE; i++){

                for(int j = 0; j < SIZE; j++){

                    if(future_board[i][j] == 10000){
                        king_row = i;
                        king_col = j;
                        break;
                    }

                }
            }
        }

        else if (colour == -1){

            for (int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){

                    if (future_board[i][j] == -10000){
                        king_row = i;
                        king_col = j;
                    }
                }
            }
        }

        //Checks right of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row;
            int check_col = king_col + i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black rook
                if(future_board[check_row][check_col] == -5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy rook
                if(future_board[check_row][check_col] == 5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }
        
        //Checks left of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row;
            int check_col = king_col - i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black rook
                if(future_board[check_row][check_col] == -5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy rook
                if(future_board[check_row][check_col] == 5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }
        //Checks up the rank to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row -i;
            int check_col = king_col;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black rook
                if(future_board[check_row][check_col] == -5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy rook
                if(future_board[check_row][check_col] == 5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }
        //Checks down the rank to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row + i;
            int check_col = king_col;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black rook
                if(future_board[check_row][check_col] == -5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy rook
                if(future_board[check_row][check_col] == 5 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }

        //Checks top-right of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row-i;
            int check_col = king_col + i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black bishop
                if(future_board[check_row][check_col] == -4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                //If there is an enemy pawn
                else if (i == 1 && future_board[check_row][check_col] == -1){
                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy bishop
                if(future_board[check_row][check_col] == 4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }

        //Checks top-left of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row-i;
            int check_col = king_col - i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black bishop
                if(future_board[check_row][check_col] == -4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                //If there is an enemy pawn
                else if (i == 1 && future_board[check_row][check_col] == -1){
                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy bishop
                if(future_board[check_row][check_col] == 4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }
        //Checks bottom-left of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row+i;
            int check_col = king_col - i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black bishop
                if(future_board[check_row][check_col] == -4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy bishop
                if(future_board[check_row][check_col] == 4){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                //If there is an enemy pawn
                else if (i == 1 && future_board[check_row][check_col] == 1){
                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }

        //Checks bottom-right of the file to see if there are any hostile pieces
        for (int i = 1; i< 8; i++){

            int check_row = king_row+i;
            int check_col = king_col + i;

            if(check_col >=8 || check_col <0 || check_row >=8 || check_row <0){
                break;
            }

            if(colour ==1){

                // If its another white piece blocking any threats
                if(future_board[check_row][check_col] >0){

                    break;
                }
                // If there is a black bishop
                if(future_board[check_row][check_col] == -4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == -9){

                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == -10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] <0){

                    break;
                }

            }
            else if(colour ==-1){

                // If its another black piece blocking any threats
                if(future_board[check_row][check_col] <0){

                    break;
                }
                // If there is an enemy bishop
                if(future_board[check_row][check_col] == 4 ){

                    return true;
                }
                // If there is an enemy queen
                else if(future_board[check_row][check_col] == 9){

                    return true;
                }
                //If there is an enemy pawn
                else if (i == 1 && future_board[check_row][check_col] == 1){
                    return true;
                }
                else if (i == 1 && future_board[check_row][check_col] == 10000){
                    return true;
                }
                // If there is an opponent's piece blocking it
                else if(future_board[check_row][check_col] >0){

                    break;
                }
            }         

        }

        // Checks if there is a knight threatening a king
        int possible_places[4] = {-2,-1,1,2};
        for (int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){

                if(abs(possible_places[i]) + abs(possible_places[j]) ==3){
                

                    int knight_row = possible_places[i] + king_row;
                    int knight_col = possible_places[j] + king_col;
                    if(knight_row >=8 || knight_row < 0 || knight_col >=8 || knight_row < 0){
                        continue;
                    }

                    if(colour == 1){
                        if(future_board[knight_row][knight_col] == -3){
                            return true;
                        }
                    }
                    if(colour == -1){

                        if(future_board[knight_row][knight_col] == 3){
                            return true;
                        }
                    }

                }
            }
        }

        return false;

    }

class ChessState{

    public: 
    vector<int> piece_i;
    vector<int> piece_j;
    vector<int> movable_piece_i;
    vector<int> movable_piece_j;
    int totalMoves;
    char choseni;
    char chosenj;
    int turn;

    ChessState(int board[SIZE][SIZE],int colour){

        totalMoves = 0;
        turn = colour;
        if(colour == -1){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){

                        if (board[i][j] <= -1){
                            piece_i.push_back(i);
                            piece_j.push_back(j);
                        } 
                }
            }
        }
        else if(colour == 1){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){

                        if (board[i][j] >= 1){
                            piece_i.push_back(i);
                            piece_j.push_back(j);
                        } 
                }
            }
        }
        
        for (int i = 0; i < (int)piece_i.size() ; i ++ ){

            int row = piece_i[i];
            int col = piece_j[i];
            if(abs(board[row][col]) == 1  ){
                    
                Pawn p = Pawn(row,col,board);

                totalMoves = totalMoves + p.i_moves.size();
                if (p.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }
                
            }
            else if (abs(board[row][col]) == 3){

                Knight n = Knight(row,col,board);
                totalMoves = totalMoves + n.i_moves.size();
                if (n.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }

            }
            else if (abs(board[row][col]) == 4){

                Bishop b = Bishop(row,col,board);
                totalMoves = totalMoves + b.i_moves.size();
                if (b.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }
                 

            }
            else if (abs(board[row][col]) == 5){

                Rook r = Rook(row,col,board);
                totalMoves = totalMoves + r.i_moves.size();
                if (r.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }
            }
            else if (abs(board[row][col]) == 9){

                Queen q = Queen(row,col,board);
                totalMoves = totalMoves + q.i_moves.size();
                if (q.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }
            }
            else if (abs(board[row][col]) == 10000){

                King k = King(row,col,board);
                totalMoves = totalMoves + k.i_moves.size();
                if (k.i_moves.size() != 0){
                    movable_piece_i.push_back(row);
                    movable_piece_j.push_back(col);
                }
            }

        }    
    }
    

    
    void randomMove(int &i0, int &j0, int &i, int &j, int board[8][8]){

        if(movable_piece_i.size() == 0){
            i = -1;
            j = -1;
            return;
        }

        srand((unsigned) time(0));
        int random_int = (rand()%movable_piece_i.size());

        int row = movable_piece_i[random_int];
        int col = movable_piece_j[random_int];

            if(abs(board[row][col]) == 1  ){
                    
                Pawn p = Pawn(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%p.i_moves.size());
                
                i = p.i_moves[random];
                j = p.j_moves[random];
                i0 = p.row_pos;
                j0 = p.col_pos;
                return;
            }
            else if (abs(board[row][col]) == 3){

                Knight n = Knight(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%n.i_moves.size());
                
                i = n.i_moves[random];
                j = n.j_moves[random];
                i0 = n.row_pos;
                j0 = n.col_pos;
                return;

            }
            else if (abs(board[row][col]) == 4){

                Bishop b = Bishop(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%b.i_moves.size());
                
                i = b.i_moves[random];
                j = b.j_moves[random];
                i0 = b.row_pos;
                j0 = b.col_pos;
                return;

            }
            else if (abs(board[row][col]) == 5){

                Rook r = Rook(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%r.i_moves.size());
                
                i = r.i_moves[random];
                j = r.j_moves[random];
                i0 = r.row_pos;
                j0 = r.col_pos;
                return;

            }
            else if (abs(board[row][col]) == 9){

                Queen q = Queen(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%q.i_moves.size());
                
                i = q.i_moves[random];
                j = q.j_moves[random];
                i0 = q.row_pos;
                j0 = q.col_pos;
                return;

            }
            else if (abs(board[row][col]) == 10000){

                King k = King(row,col,board);
                srand((unsigned) time(0));
                int random = (rand()%k.i_moves.size());
                
                i = k.i_moves[random];
                j = k.j_moves[random];
                i0 = k.row_pos;
                j0 = k.col_pos;
                return;
            }

    }

    // char * minMax(int depth){


    // }

    
        class Pawn{

            public: 
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;

                Pawn(int row, int col, int board[8][8]){

                    row_pos = row;
                    col_pos = col;
                    int file_difference[2] = {-1,1};
                    if(board[row][col] > 0)
                    {
                        colour = 1;
                    }
                    else
                    {
                        colour = -1;
                    }

                    if (colour == 1)
                    {
                        if (row-1 >=0 && board[row-1][col] == 0 ){
                            i_moves.push_back(row-1);
                            j_moves.push_back(col);
                        }
                        if (row == 6 && board[row-2][col] == 0 && board[row-1][col] == 0){
                            
                            i_moves.push_back(row-2);
                            j_moves.push_back(col);
                        }
                        //Check possible attacks
                        for (int i = 0; i < 2; i ++)
                        {   
                            int check = col + file_difference[i];
                            if (check <0 || check >7 || row-1 >7 || row-1 <0){
                                continue;
                            } 
                            else if ( board[row-1][check] <0 ){

                                i_moves.push_back(row-1);
                                j_moves.push_back(check);
                            }
                        }

                    }
                    
                    else if (colour == -1)
                    {
                        if (row+1 <=7 && board[row+1][col] == 0 ){
                            i_moves.push_back(row+1);
                            j_moves.push_back(col);
                        }
                        if (row == 1 && board[row+2][col] == 0 && board[row+1][col] == 0){
                            
                            i_moves.push_back(row+2);
                            j_moves.push_back(col);
                        }
                        //Check possible attacks
                        for (int i = 0; i < 2; i ++)
                        {   
                            int check = col + file_difference[i];
                            if (check <0 || check >7 || row+1 >7 || row+1 <0){
                                continue;
                            } 
                            else if ( board[row+1][check] >0 ){

                                i_moves.push_back(row+1);
                                j_moves.push_back(check);
                            }
                        }

                    }

                    // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }
                    
                }

        };
        class Knight{

            public: 
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;

                Knight(int row, int col, int board[8][8]){
                        
                    row_pos = row;
                    col_pos = col;
                    int pos_difference[4] = {-2,-1,1,2};
                    if(board[row][col] > 0)
                    {
                        colour = 1;
                    }
                    else
                    {
                        colour = -1;
                    }
                    for(int i = 0; i < 4; i++){

                        for(int j = 0; j <4; j++){

                                if(abs(pos_difference[i]) + abs(pos_difference[j]) == 3){

                                    int row_check = row + pos_difference[i];
                                    int col_check = col + pos_difference[j];

                                    if( row_check > 7 || row_check < 0){
                                        continue;
                                    }
                                    if (col_check > 7 || col_check < 0){

                                        continue;
                                    }
                                    if (colour == 1){
                                        if (board[row_check][col_check] >= colour){
                                            continue;
                                        }
                                        else{
                                            i_moves.push_back(row_check);
                                            j_moves.push_back(col_check);
                                        }
                                    }
                                    else if (colour == -1){
                                        
                                        if(board[row_check][col_check] <= colour){
                                            continue;
                                        }
                                        else{
                                            i_moves.push_back(row_check);
                                            j_moves.push_back(col_check);
                                        }
                                    }
                                }
                        }
                    }

                    // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }

                }
        };
        class Bishop{

            public: 
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;
                
            Bishop(int row, int col, int board[8][8]){

                row_pos = row;
                col_pos = col;
                if(board[row][col] > 0)
                {
                    colour = 1;
                }
                else
                {
                    colour = -1;
                }

                bool obstacle = false;
                // Checks the top-right
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row-i;
                    int col_check = col+i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }
                
                //checks top-left
                obstacle = false;
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row-i;
                    int col_check = col-i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                } 
                obstacle = false;
                //checks bottom-left
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row+i;
                    int col_check = col-i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }

                obstacle = false;
                //checks bottom-right
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row+i;
                    int col_check = col+i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }     
                // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }          
            }

            
        };

        class Rook{
            public:
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;

                Rook(int row, int col, int board[8][8]){

                    row_pos = row;
                    col_pos = col;
                    if(board[row][col] > 0)
                    {
                        colour = 1;
                    }
                    else
                    {
                        colour = -1;
                    }

                    // This will check moves down
                    bool obstacle = false;
                    for(int i = 1; i < 8; i++){

                        int row_check = row + i;
                        int col_check = col;

                        if (obstacle){
                            break;
                        }

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                    // This will check moves up
                    obstacle = false;
                    for(int i = 1; i < 8; i++){
                        if (obstacle){
                            break;
                        }

                        int row_check = row - i;
                        int col_check = col;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                    // This will check moves left
                    obstacle = false;
                    for(int i = 1; i < 8; i++){
                        if (obstacle){
                            break;
                        }

                        int row_check = row;
                        int col_check = col - i;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                     // This will check moves right
                    obstacle = false;
                    for(int i = 1; i < 8; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row;
                        int col_check = col + i;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }
                    // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }

                }

        };

        class Queen{
            public: 
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;
            Queen(int row, int col, int board[8][8]){
                row_pos = row;
                col_pos = col;
                if(board[row][col] > 0)
                {
                    colour = 1;
                }
                else
                {
                    colour = -1;
                }

                bool obstacle = false;
                // Checks the top-right
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row-i;
                    int col_check = col+i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }
                
                //checks top-left
                obstacle = false;
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row-i;
                    int col_check = col-i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                } 
                obstacle = false;
                //checks bottom-left
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row+i;
                    int col_check = col-i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }

                obstacle = false;
                //checks bottom-right
                for (int i = 1; i < 8; i++){

                    if (obstacle){
                        break;
                    }
                    int row_check = row+i;
                    int col_check = col+i;
                    

                    if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                        break;
                    }

                    if(colour == 1){
                        if (board[row_check][col_check] >=1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] <0){

                            obstacle = true;
                            
                        }
                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);

                    }
                    else if(colour ==-1){
                        if(board[row_check][col_check] <= -1){
                            obstacle = true;
                            continue;
                        }
                        else if(board[row_check][col_check] >0){
                            obstacle = true;
                        }

                        i_moves.push_back(row_check);
                        j_moves.push_back(col_check);
                    }
                }  

                // This will check moves down
                    obstacle = false;
                    for(int i = 1; i < 8; i++){

                        int row_check = row + i;
                        int col_check = col;

                        if (obstacle){
                            break;
                        }

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                    // This will check moves up
                    obstacle = false;
                    for(int i = 1; i < 8; i++){
                        if (obstacle){
                            break;
                        }

                        int row_check = row - i;
                        int col_check = col;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                    // This will check moves left
                    obstacle = false;
                    for(int i = 1; i < 8; i++){
                        if (obstacle){
                            break;
                        }

                        int row_check = row;
                        int col_check = col - i;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }

                     // This will check moves right
                    obstacle = false;
                    for(int i = 1; i < 8; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row;
                        int col_check = col + i;

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }

                    }
                    // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }
            }   

        };

        class King{

            public: 
                vector<int> i_moves;
                vector<int> j_moves;
                int colour;
                int row_pos;
                int col_pos;
                King(int row, int col, int board[8][8]){
                    row_pos = row;
                    col_pos = col;
                    if(board[row][col] > 0)
                    {
                        colour = 1;
                    }
                    else
                    {
                        colour = -1;
                    }

                    bool obstacle = false;
                    // Checks the top-right
                    for (int i = 1; i < 2; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row-i;
                        int col_check = col+i;
                        

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }

                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }
                    }
                    
                    //checks top-left
                    obstacle = false;
                    for (int i = 1; i < 2; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row-i;
                        int col_check = col-i;
                        

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }

                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }
                    } 
                    obstacle = false;
                    //checks bottom-left
                    for (int i = 1; i < 2; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row+i;
                        int col_check = col-i;
                        

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }
                    }

                    obstacle = false;
                    //checks bottom-right
                    for (int i = 1; i < 2; i++){

                        if (obstacle){
                            break;
                        }
                        int row_check = row+i;
                        int col_check = col+i;
                        

                        if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                            break;
                        }

                        if(colour == 1){
                            if (board[row_check][col_check] >=1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] <0){

                                obstacle = true;
                                
                            }
                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);

                        }
                        else if(colour ==-1){
                            if(board[row_check][col_check] <= -1){
                                obstacle = true;
                                continue;
                            }
                            else if(board[row_check][col_check] >0){
                                obstacle = true;
                            }

                            i_moves.push_back(row_check);
                            j_moves.push_back(col_check);
                        }
                    }  

                        // This will check moves down
                        obstacle = false;
                        for(int i = 1; i < 2; i++){

                            int row_check = row + i;
                            int col_check = col;

                            if (obstacle){
                                break;
                            }

                            if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                                break;
                            }

                            if(colour == 1){
                                if (board[row_check][col_check] >=1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] <0){

                                    obstacle = true;
                                    
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);

                            }
                            else if(colour ==-1){
                                if(board[row_check][col_check] <= -1){
                                    obstacle = true;
                                    
                                    continue;
                                }
                                else if(board[row_check][col_check] >0){
                                    obstacle = true;
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);
                            }

                        }

                        // This will check moves up
                        obstacle = false;
                        for(int i = 1; i < 2; i++){
                            if (obstacle){
                                break;
                            }

                            int row_check = row - i;
                            int col_check = col;

                            if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                                break;
                            }

                            if(colour == 1){
                                if (board[row_check][col_check] >=1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] <0){

                                    obstacle = true;
                                    
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);

                            }
                            else if(colour ==-1){
                                if(board[row_check][col_check] <= -1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] >0){
                                    obstacle = true;
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);
                            }

                        }

                        // This will check moves left
                        obstacle = false;
                        for(int i = 1; i < 2; i++){
                            if (obstacle){
                                break;
                            }

                            int row_check = row;
                            int col_check = col - i;

                            if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                                break;
                            }

                            if(colour == 1){
                                if (board[row_check][col_check] >=1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] <0){

                                    obstacle = true;
                                    
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);

                            }
                            else if(colour ==-1){
                                if(board[row_check][col_check] <= -1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] >0){
                                    obstacle = true;
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);
                            }

                        }

                        // This will check moves right
                        obstacle = false;
                        for(int i = 1; i < 2; i++){

                            if (obstacle){
                                break;
                            }
                            int row_check = row;
                            int col_check = col + i;

                            if(row_check >=8 || row_check <0 || col_check >= 8 || col_check <0){
                                break;
                            }

                            if(colour == 1){
                                if (board[row_check][col_check] >=1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] <0){

                                    obstacle = true;
                                    
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);

                            }
                            else if(colour ==-1){
                                if(board[row_check][col_check] <= -1){
                                    obstacle = true;
                                    continue;
                                }
                                else if(board[row_check][col_check] >0){
                                    obstacle = true;
                                }
                                i_moves.push_back(row_check);
                                j_moves.push_back(col_check);
                            }

                    }
                    // If doing this move would result in a check, it is illegal so remove it from the possible set of moves
                    for(int i = 0; i < (int)i_moves.size(); i++){

                        int futureboard[8][8];
                        int to_row = i_moves[i];
                        int to_col = j_moves[i];
                        immitateMove(row_pos,col_pos, to_row, to_col,board,futureboard);
                        
                        // ChessState chessTest = ChessState(futureboard,colour);
                        if (inCheck(futureboard,colour) ){

                            i_moves.erase(i_moves.begin() + i);
                            j_moves.erase(j_moves.begin() + i);
                            i--;
                        }

                    }
            }

        }; 

        

};


extern "C"
const void free_pointer (char* ptr){

    delete ptr; 
}

// Test function for myself
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

// Converting the board back to a string.
void convertString( char* sBoard, int board[8][8]){

    int index = 0;

    for(int i = 0; i < SIZE; i++){

        for(int j =0; j < SIZE; j++){

            if(board[i][j] == 0){

                sBoard[index]= '0';
                sBoard[index+1] = '0';
            }
            else if(board [i][j] == 1){

                sBoard[index] = 'w';
                sBoard[index+1] = 'P';
            }
            else if(board [i][j] == -1 ){

                sBoard[index] = 'b';
                sBoard[index+1] = 'P';
            }
            else if(board [i][j] == 3 ){

                sBoard[index] = 'w';
                sBoard[index+1] = 'N';
            }
            else if(board [i][j] == -3 ){

                sBoard[index] = 'b';
                sBoard[index+1] = 'N';
            }
            else if(board [i][j] == 4){

                sBoard[index] = 'w';
                sBoard[index+1] = 'B';
            }
            else if(board [i][j] == -4 ){

                sBoard[index] = 'b';
                sBoard[index+1] = 'B';
            }
            else if(board [i][j] == 5){

                sBoard[index] = 'w';
                sBoard[index+1] = 'R';
            }
            else if(board [i][j] == -5){

                sBoard[index] = 'b';
                sBoard[index+1] = 'R';
            }
            else if(board [i][j] == 9 ){

                sBoard[index] = 'w';
                sBoard[index+1] = 'Q';
            }
            else if(board [i][j] == -9){

                sBoard[index] = 'b';
                sBoard[index+1] = 'Q';
            }
            else if(board [i][j] == 10000){

                sBoard[index] = 'w';
                sBoard[index+1] = 'K';
            }
            else if(board [i][j] == -10000){

                sBoard[index] = 'b';
                sBoard[index+1] = 'K';
            }
            else{
                cout << "This should never happen!!!!";
            }
            index= index+2;
        }
    }
    sBoard[128] = 0;
}

extern "C"
const char* sendMove(char* sBoard)
{ 

    int board[8][8];
    initializeBoard(board);
    convertBoard(sBoard, board);
    
    ChessState board_state = ChessState(board,-1);
    int i = 0;
    int j = 0;
    int i0 = 0;
    int j0 = 0;
    board_state.randomMove(i0,j0,i,j,board);

    char o1 = j0 +  97;
    char o2 = 56 - i0;
    char o3 = j + 97;
    char o4 = 56 - i;
    char* output= new char[5];
    output[0] = o1;
    output[1] = o2;
    output[2] = o3;
    output[3] = o4;
    output[4] = 0;

    cout<< output;

    // char *greeting = alterHello(sBoard);
    return output;
}

extern "C"
const char* checkIfMate(char* sBoard)
{ 

    int board[8][8];
    initializeBoard(board);
    convertBoard(sBoard, board);
    
    ChessState board_state = ChessState(board,1);
    int i = 0;
    int j = 0;
    int i0 = 0;
    int j0 = 0;
    board_state.randomMove(i0,j0,i,j,board);

    char o1 = j0 +  97;
    char o2 = 56 - i0;
    char o3 = j + 97;
    char o4 = 56 - i;
    char* output= new char[5];
    output[0] = o1;
    output[1] = o2;
    output[2] = o3;
    output[3] = o4;
    output[4] = 0;

    cout<< output;

    // char *greeting = alterHello(sBoard);
    return output;
}


// THis is mostly for testing purposes since I don't directly call engine.cpp
int main(){

    // char buffer[129] = "bRbNbBbQbKbBbNbR000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000wRwNwBwQwKwBwNwR";
    // char buffer[129] = "bRbNbBbQbKbBbNbRbPbPbPbPbPbPbPbP0000000000000000000000000000000000000000000000000000000000000000wPwPwPwPwPwPwPwPwRwNwBwQwKwBwNwR";
    // char buffer[129] = "bRbNbB0000bKbNbRbP00bPbP00bQ000000000000wN00000000000000wQ00000000bP00000000000000000000wP000000wPwPwPwP00wPwPwPwRwNwB00wKwB00wR";
    // char buffer[129] = "bRbNbB0000bKbNbRbP00bPbP00wR000000000000wN00000000000000wQ00000000bP00000000000000000000wP000000wPwPwPwP00wPwPwPwRwNwB00wKwB0000";
    char buffer[129] = "00bNbBbQ00000000bR00bK0000wP000000000000wQ000000bPwNbP0000000000000000000000000000000000wP000000wPwPwPwP0000wPwPwR00wB00wK00wNwR";
    


    int testBoard[8][8];
    initializeBoard(testBoard);
    
    convertBoard(buffer, testBoard);

    printBoard(testBoard);
    ChessState board_state = ChessState(testBoard,-1);
    cout <<"Total Moves:" << board_state.movable_piece_i.size();
    int i = 0;
    int j = 0;
    int i0 = 0;
    int j0 = 0;
    board_state.randomMove(i0,j0,i,j,testBoard);
    char o1 = j0 +  97;
    char o2 = 56 - i0;
    char o3 = j + 97;
    char o4 = 56 - i;
    char* output= new char[5];
    output[0] = o1;
    output[1] = o2;
    output[2] = o3;
    output[3] = o4;
    output[4] = 0;

    cout<< output;

    

    // cout << endl << inCheck(testBoard,-1) << endl;
    // char* tester = new char[129];

    // convertString(tester, testBoard);

    // ChessState board1 = ChessState(testBoard,1);
    // cout <<endl<< board1.totalMoves << endl;

    // const char* nothing = sendMove(buffer);

    return 0;

    // cout << endl << buffer[128];

}