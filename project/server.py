from flask import Flask, render_template, request
import json
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
            

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/isValidMove', methods=['POST','GET'])
def isValidMove():
    data = json.loads(request.data)
    print(data['old'])
    old = data['old']
    print(old['a8'])
    createBoard(data['old'])
    # new = request.args['new']
    # print(old)
    # print(new)

    return json.dumps({'results':'True'})




if __name__ == '__main__':
    app.run()

    
