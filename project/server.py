from flask import Flask, render_template, request
import json

wCanCastleKing = True
wCanCastleQueen = True
bCanCastleKing = True
bCanCastleQueen = True
pawnEnpassant = None
turn = 'w'



# global wCanCastleKing = True
# global wCanCastleQueen = True
# global bCanCastleKing = True
# global bCanCastleQueen = True
# global pawnEnpassant = None
# global turn = 'w'

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

    # Checks legal queen moves
    # Checks legal knight moves
    # Checks legal bishop moves
    # Checks legal Rook moves
    # Checks Catling Moving
    # Checks EnPassant Move
    # Checks ifCastling is possible
    # Checks if king is in check in the future
    # Checks if king is currently in check


# import requests
app = Flask(__name__, template_folder='static')

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

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/isValidMove', methods=['POST','GET'])
def isValidMove():

    data = json.loads(request.data)
    old = data['old']
    new = data['new']
    old_pos = data['source']
    new_pos = data['target']
    piece = data['piece']

    old_board = createBoard(old)
    new_board = createBoard(new)
    printBoard(old_board)
    board = ChessState(old_board)
    output = None

    #Uncomment bellow to implemen tturns
    # if piece[0] != turn:
    #     output = False
    if piece[1]=='P':
        output = board.pawnMoves(piece,old_pos,new_pos)

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
    app.run()

    
