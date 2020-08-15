from flask import Flask, render_template, request
import json
import ctypes
import numpy
import glob

libfile = glob.glob('build/*/engine*.so')[0]


lib = ctypes.CDLL(libfile)

lib.sendMove.argtypes = (ctypes.c_char_p,)
lib.sendMove.restype = (ctypes.c_char_p)

lib.checkIfMate.argtypes = (ctypes.c_char_p,)
lib.checkIfMate.restype = (ctypes.c_char_p)

def aiMove(board):
    pResults = lib.sendMove(board)
    result = pResults.decode("utf-8")
    return result

def testMove(board):
    pMove = ctypes.c_char_p(board.encode('utf-8'))
    return aiMove(pMove)

def checkMate(board):
    newBoard = ctypes.c_char_p(board.encode('utf-8'))
    pResults = lib.checkIfMate(newBoard)
    result = pResults.decode("utf-8")
    return result

# def hello(name):
#     pResult = lib.sendMove(name)
#     result = pResult.decode("utf-8")
#     return result

# def test():
#     frank = "Frank"
#     pName = ctypes.c_char_p(frank.encode('utf-8'))
#     print(hello(pName))
   

wCanCastleKing = True
wCanCastleQueen = True
bCanCastleKing = True
bCanCastleQueen = True
pawnEnpassant = None
turn = 'w'

def switchTurns(): 
    global turn
    if turn== 'w':
        turn = 'b'
    else:
        turn = 'w'

# A class to represent the previous chess state
class ChessState: 
    def __init__(self, board,future_state):
        self.board = createBoard(board)
        self.future = createBoard(future_state)


    # Checks legal pawn moves needs to check if it is pinned
    def inCheck(self,colour):
        kingIndex1 = ' '
        kingIndex2 = ' '
        king = colour + 'K'
        if colour =='w':
            opponent = 'b'
        else:
            opponent = 'w'

        for i in range(97,105):
            for j in range(49,57):
                index = chr(i)+ chr(j)
                if self.future[index] == king:
                    kingIndex1 = index[0]
                    kingIndex2 = index[1]
                    break
        if kingIndex1 == ' ' and kingIndex2 == ' ':
            print("Something went wrong here, a king should always be on the board!!!")

        #Check down file for any hostile pieces
        for i in range(1,8):
            check = kingIndex1 + chr(ord(kingIndex2) +i)
            if check[1] > '8' or check[1] < '1':
                continue
            if(self.future[check][0] == colour):
                break
            if(self.future[check] == (opponent + 'R')):
                return True
            if(self.future[check] == (opponent + 'Q')):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check up the file for any hostile pieces
        for i in range(1,8):
            check = kingIndex1 + chr(ord(kingIndex2 )-i)
            if check[1] > '8' or check[1] < '1':
                continue
            if(self.future[check][0] == colour):
                break
            if(self.future[check] == (opponent + 'R')):
                return True
            if(self.future[check] == (opponent + 'Q')):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break
                
        #Check right of the rank for any hostile pieces
        for i in range(1,8):
            check = chr(ord(kingIndex1) +i) + kingIndex2
            if check[0] > 'h' or check[0] < 'a':
                continue
            if(self.future[check][0] == colour):
                break
            if(self.future[check] == (opponent + 'R')):
                return True
            if(self.future[check] == (opponent + 'Q')):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check left of the rank for any hostile pieces
        for i in range(1,8):
            check = chr(ord(kingIndex1 )-i) + kingIndex2
            if check[0] > 'h' or check[0] < 'a':
                continue
            if(self.future[check][0] == colour):
                break
            if(self.future[check] == (opponent + 'R')):
                return True
            if(self.future[check] == (opponent + 'Q')):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break
        
        #Check top-right for any hostile pieces

        for i in range(1,8):
            index1 = chr(ord(kingIndex1) +i )
            index2 = chr(ord(kingIndex2) +i)
            check = index1 + index2
            if check[0] >'h' or check[0] < 'a' or check[1] > '8' or check[1] < '1':
                continue
            if (self.future[check][0] == colour):
                break
            if (self.future[check] == (opponent + 'B')):
                return True
            if (self.future[check] == (opponent + 'Q')):
                return True
            if i ==1 and colour =='w'and self.future[check] == (opponent + 'P'):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check top-left for any hostile pieces
        for i in range(1,8):
            index1 = chr(ord(kingIndex1) -i)
            index2 = chr(ord(kingIndex2) +i)
            check = index1 + index2
            if check[0] >'h' or check[0] < 'a' or check[1] > '8' or check[1] < '1':
                continue
            if (self.future[check][0] == colour):
                break
            if (self.future[check] == (opponent + 'B')):
                return True
            if (self.future[check] == (opponent + 'Q')):
                return True
            if i ==1 and colour =='w'and self.future[check] == (opponent + 'P'):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check bottom-left for any hostile pieces
        for i in range(1,8):
            index1 = chr(ord(kingIndex1) -i )
            index2 = chr(ord(kingIndex2) -i)
            check = index1 + index2
            if check[0] >'h' or check[0] < 'a' or check[1] > '8' or check[1] < '1':
                continue
            if (self.future[check][0] == colour):
                break
            if (self.future[check] == (opponent + 'B')):
                return True
            if (self.future[check] == (opponent + 'Q')):
                return True
            if i ==1 and colour =='b'and self.future[check] == (opponent + 'P'):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check bottom-right for any hostile pieces
        for i in range(1,8):
            index1 = chr(ord(kingIndex1) +i )
            index2 = chr(ord(kingIndex2) -i)
            check = index1 + index2
            if check[0] >'h' or check[0] < 'a' or check[1] > '8' or check[1] < '1':
                continue
            if (self.future[check][0] == colour):
                break
            if (self.future[check] == (opponent + 'B')):
                return True
            if (self.future[check] == (opponent + 'Q')):
                return True
            if i ==1 and colour =='b'and self.future[check] == (opponent + 'P'):
                return True
            if(i == 1 and self.future[check] == (opponent + 'K')):
                return True
            if(self.future[check][0] == (opponent)):
                break

        #Check if a knight is checking the king
        pos_moves = [-2,-1,1,2]
        for i in pos_moves:
            for j in pos_moves:
                if abs(i) + abs(j) == 3:
                    index1 = chr(ord(kingIndex1) + i)
                    index2 = chr(ord(kingIndex2) + j)
                    if(index1 <'a' or index1 > 'h'):
                        continue
                    if(index2 >'8' or index2 < '1'):
                        continue
                    check = index1 + index2
                    if(self.future[check] == (opponent + 'N')):
                        return True
        return False





#It might error out when it reaches the edge so change this please
class Pawn: 
    def __init__(self, old_pos, colour, board):
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_moves = []
        file_difference = [-1,1]
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        if(colour == 'w'):
            index2 = chr(cur_rank_int+1)
            index = chr(cur_file_int) + index2
            if index2 <= '8' and index2 >= '1':
                if board[index] == "00":     
                    pos_moves.append(index)
                if chr(cur_rank_int) =='2':
                    index2 = chr(cur_rank_int+2)
                    index = chr(cur_file_int) + index2
                    index3 = chr(cur_file_int) + chr(cur_rank_int +1)
                    if board[index] == "00" and board[index3] == "00":     
                        pos_moves.append(index)
                for i in file_difference:
                    index1 = chr(cur_file_int + i)
                    index2 = chr(cur_rank_int +1)

                    if(index1 < 'a' or index1 > 'h'):
                        continue
                    index = index1 + index2
                    if(board[index][0] == opponent):
                        pos_moves.append(index)
        elif(colour =='b'):
            index2 = chr(cur_rank_int-1)
            index = chr(cur_file_int) + index2
            if index2 <= '8' and index2 >= '1':
                if board[index] == "00":
                    pos_moves.append(index)
                if chr(cur_rank_int) =='7':
                    index2 = chr(cur_rank_int-2)
                    index = chr(cur_file_int) + index2
                    index3 = chr(cur_file_int) + chr(cur_rank_int +1)
                    if board[index] == "00" and board[index3] == "00":     
                        pos_moves.append(index)
                for i in file_difference:
                    index1 = chr(cur_file_int + i)
                    index2 = chr(cur_rank_int -1)
                    if(index1 < 'a' or index1 > 'h'):
                        continue
                    index = index1 + index2
                    if(board[index][0] == opponent):
                        pos_moves.append(index)
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        print(pos_moves)

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves

        
        



class Knight:
    def __init__(self, old_pos, colour,board):
        
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = [-2,-1,1,2]
        pos_moves = []
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        for i in pos_differences:
            for j in pos_differences:
                if abs(i) + abs(j) == 3:
                    index1 = chr(cur_file_int + i)
                    index2 = chr(cur_rank_int + j)
                    if(index1 < 'a' or index1 >'h'):
                        continue
                    elif (index2 > '8' or index2 <'1'):
                        continue
                    index = index1+index2
                    if (board[index][0] == colour):
                        continue
                    if index not in pos_moves: 
                        pos_moves.append(index)
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        print(pos_moves)

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves

#Account for first enemy found
class Rook: 
    def __init__(self, old_pos, colour,board):
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = range(1,8)
        neg_differences = range(-1,-8,-1)
        pos_moves = []
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        self.old_pos = old_pos

    def isPossibleMove(self, new_pos):
        if (new_pos in self.pos_moves):
            if self.old_pos == "a1":
                global wCanCastleQueen
                wCanCastleQueen = False
            elif self.old_pos == "h1":
                global wCanCastleKing
                wCanCastleKing = False
            elif self.old_pos == "h8":
                global bCanCastleKing
                bCanCastleKing = False
            elif self.old_pos == "A8":
                global bCanCastleQueen
                bCanCastleQueen = False
            return True
        else:
            return False


class Bishop: 
    def __init__(self, old_pos, colour,board):
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = range(1,8)
        pos_moves = []
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        obstacle = False
        # top-right
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # top-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-right
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)

        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        print(pos_moves)

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves

# Queen Chess Piece
class Queen: 
    def __init__(self, old_pos, colour,board):
        
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = range(1,8)
        neg_differences = range(-1,-8,-1)
        pos_moves = []
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        pos_differences = range(1,8)
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # top-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-right
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)

        print(pos_moves)
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        print(pos_moves)

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves

# Could still refactor since I just copied queen's code and changed the ranges
class King:
    def __init__(self, old_pos, colour,board):
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = range(1,2)
        neg_differences = range(-1,-2,-1)
        pos_moves = []
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index1 = chr(cur_file_int +i)
            if(index1 <'a' or index1 > 'h'):
                continue
            else:
                index = index1+ chr(cur_rank_int)
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in pos_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        for i in neg_differences:
            if (obstacle):
                break
            index2 = chr(cur_rank_int +i)
            if(index2 <'1' or index2 > '8'):
                continue
            else:
                index = chr(cur_file_int) + index2
                if (board[index][0] == colour):
                    obstacle = True
                    continue
                elif (board[index][0] == opponent):
                    obstacle = True
                pos_moves.append(index)
        obstacle = False
        pos_differences = range(1,2)
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # top-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int + i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-left
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int - i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        obstacle = False
        # bottom-right
        for i in pos_differences:
            if(obstacle):
                break
            index1 = chr(cur_file_int + i)
            index2 = chr(cur_rank_int - i)
            if(index1 <'a' or index1 >'h' or index2 <'1' or index2 >'8'):
                break
            index = index1 + index2
            if(board[index][0] == colour):
                obstacle = True
                continue
            elif (board[index][0] == opponent):
                obstacle = True
            pos_moves.append(index)
        # if colour == 'W'
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour

    def isPossibleMove(self, new_pos):
        if new_pos in self.pos_moves:
            if self.colour =='w':
                global wCanCastleKing
                global wCanCastleQueen
                wCanCastleKing = False
                wCanCastleQueen = False
            else:
                global bCanCastleKing
                global bCanCastleQueen
                bCanCastleKing = False
                bCanCastleQueen = False
            return True

    
# Creates a board form 
def createBoard(data):
    board = {}
    for i in range(97,105):
        for j in range(49,57):
            index = chr(i)+ chr(j)
            if(index in data.keys()):
                board[index] = data[index]
            else:
                board[index] = "00"
    
    return board
            

# Turns the board to a string for C++ to access
def stringifyBoard(board):
    output = ""
    for i in range(56,48,-1):
        for j in range(97,105):
            index = chr(j) + chr(i)
            output = output + board[index]
            # output = output + board[index] + " "
        # output = output + "\n"

    # print(output)
    return output

def printBoard(board):
    for i in range(56,48,-1):
        for j in range(97, 105):
            index = chr(j) + chr(i)
            print(board[index] + " ", end = '')
        print("")    


# import requests
app = Flask(__name__, template_folder='static')


@app.route('/')
def index():
    global turn
    turn = 'w'
    return render_template('index.html')

@app.route('/checkIfMate', methods=['POST','GET'])
def checkIfMate():
    data = json.loads(request.data)
    databoard = data['board']

    board = ChessState(databoard,databoard)
    boardToSend = stringifyBoard(board.board)
    print("I am sending this to c++")
    print(boardToSend)
    output = checkMate(boardToSend)
    
    print("Here is the output: " + output)
    if(output[3] == '9'):
    
        legal = "False"
    
    else:
        legal = "True"
        
    return json.dumps({'moves':output, 'legal': legal})
    


@app.route('/aiTurn', methods=['POST','GET'])
def aiTurn():
    data = json.loads(request.data)
    databoard = data['board']

    board = ChessState(databoard,databoard)
    boardToSend = stringifyBoard(board.board)
    print("I am sending this to c++")
    print(boardToSend)
    output = testMove(boardToSend)
    
    print("Here is the output: " + output)
    if(output[3] == '9'):
    
        legal = "False"
    
    else:
        legal = "True"
    

    switchTurns()
    return json.dumps({'moves':output, 'legal': legal})

    
@app.route('/newGame')
def newGame():
    global turn
    turn = 'w'
    return

@app.route('/isValidMove', methods=['POST','GET'])
def isValidMove():

    data = json.loads(request.data)
    old = data['old']
    new = data['new']
    old_pos = data['source']
    new_pos = data['target']
    piece = data['piece']

    old_board = old
    new_board = new
    
    # printBoard(old_board)
    board = ChessState(old_board,new_board)
    print("validating this move")
    boardToSend = stringifyBoard(board.board)
    print(boardToSend)
    output = None
    # testMove(boardToSend)
    #Uncomment below to implement turns
    if piece[0] != turn or board.inCheck(piece[0]):
        output = False
    else:
        if piece[1]=='P':
            # output = board.pawnMoves(piece,old_pos,new_pos)
            pawn = Pawn(old_pos,piece[0],board.board)
            output = pawn.isPossibleMove(new_pos)
        elif piece[1] == 'N':
            knight = Knight(old_pos,piece[0],board.board)
            output = knight.isPossibleMove(new_pos)
        elif piece[1] == 'R':
            rook = Rook(old_pos,piece[0], board.board)
            output = rook.isPossibleMove(new_pos)
        elif piece[1] == 'B':
            bishop = Bishop(old_pos,piece[0], board.board)
            output = bishop.isPossibleMove(new_pos)
        elif piece[1] == 'Q':
            queen = Queen(old_pos,piece[0], board.board)
            output = queen.isPossibleMove(new_pos)
        elif piece[1] == 'K':
            king = King(old_pos,piece[0], board.board)
            output = king.isPossibleMove(new_pos)

    if output == True:
        results = "True"
        switchTurns()
    else:
        results = "False"
    # new = request.args['new']
    # print(old)
    # print(new)

    return json.dumps({'results':results})




if __name__ == '__main__':
    app.run(host= '0.0.0.0')

    
