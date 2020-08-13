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
    def __init__(self, board):
        self.board = createBoard(board)
    
    # STILL NEED TO CHECK FOR ENPASSANT
    # Checks legal pawn moves needs to check if it is pinned
    def pawnMoves(self,piece,old_pos,new_pos):
        old_file = old_pos[0]
        new_file = new_pos[0]
        old_rank = old_pos[1]
        new_rank = new_pos[1]
        colour = piece[0]
        opponent = None
        if colour =='w':
            opponent = 'b'
        else:
            opponent ='w'
        pieceType = piece[1]
        file_difference = ord(new_file) - ord(old_file)
        rank_difference = int(new_rank) - int(old_rank)
        print("file_difference: " + str(file_difference))
        print("rank_difference: " + str(rank_difference))
        
        # Checks if it's trying to take something not diagonal
        if self.board[new_pos] != "00" and file_difference == 0:
            print("Here1")
            return False
        if self.board[new_pos][0] == colour:
            print("Here1")
            return False
        if pieceType != 'P':
            print("Here1")
            return False

        # Checks standard moves 
        if colour == 'w' :
            if rank_difference < 0:
                print("Herea")
                return False
            if rank_difference == 2 and old_rank != '2':
                print("Hereb")
                return False
            if rank_difference > 2 or rank_difference == 0:
                print("Herec")
                return False
            if rank_difference == 1 and abs(file_difference) == 1:
                if self.board[new_pos][0] != 'b' and self.board[new_pos] != "00":
                    print("Hered")
                    print(self.board[new_pos][0])
                    return False 
        elif colour == 'b':
            if rank_difference > 0:
                print("Herea")
                return False
            if rank_difference == -2 and old_rank != '7':
                print("Hereb")
                return False
            if rank_difference < -2 or rank_difference == 0:
                print("Herec")
                return False
            if rank_difference == -1 and abs(file_difference) == 1:
                if self.board[new_pos][0] != 'w' and self.board[new_pos] != "00":
                    print("Hered")
                    return False 
        if file_difference == 0:
            return True
        elif abs(file_difference) ==1 and self.board[new_pos][0] == opponent:
            return True

        return False
        # Checks if it wants to take a pie

    # Checks legal knight moves
    # def knightMoves(self,piece,old_pos,new_pos):
    #     old_file = old_pos[0]
    #     new_file = new_pos[0]
    #     old_rank = old_pos[1]
    #     new_rank = new_pos[1]
    #     colour = piece[0]
    #     opponent = None
    #     if colour =='w':
    #         opponent = 'b'
    #     else:
    #         opponent ='w'
    #     pieceType = piece[1]
    #     file_difference = ord(new_file) - ord(old_file)
    #     rank_difference = int(new_rank) - int(old_rank)

# class Pawn:
#     def __init__(self, old_pos, colour):



class Knight:
    def __init__(self, old_pos, colour,board):
        cur_file_int = ord(old_pos[0])
        cur_rank_int = ord(old_pos[1])
        pos_differences = [-1,1,2,-2]
        pos_moves = []

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

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves

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

        print(pos_moves)
        self.pos_moves = pos_moves
        self.pos_attacks = pos_moves
        self.colour = colour
        print(pos_moves)

    def isPossibleMove(self, new_pos):
        return new_pos in self.pos_moves
    
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
            

def printBoard(board):
    for i in range(56,48,-1):
        for j in range(97, 105):
            index = chr(j) + chr(i)
            print(board[index] + " ", end = '')
        print("")    