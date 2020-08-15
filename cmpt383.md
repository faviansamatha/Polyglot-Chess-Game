# Prototype Polygot Chess Program

### How to start

Here are the instructions to start:

1. Execute `vagrant up`
2. Execute `vagrant ssh` (or however you get into the vagrant environment)
3. Execute `cd project/project` (to access the project folder)
4. Execute `make` or `make build` (to build the c++ files to be callable from python and to start the server)
5. Open a web-browser and go to localhost:5000. If needed do ctrl + f5 for hard-reset. 

The make file contains other commands to help out execution
1. `make run` Runs the python server (use when the c++ files are already built for python use)
2. `make reubild` Used to rebuild the C build folder
3. `make clean` Used to remove the C build folder

### Project Description
This project was meant to imitate a human player vs an ai in chess. However, some rules of chess have not been implemented yet.
- The ability to castle
- The ability to do enpassant
- The ability to promote a pawn to a queen
- The ability to play as black
- Stalemate leads to one player winning (player who moved last)

These will be done in future implementations. However, the game is functioning. Players will have to press a button to check if they have no more moves.
The player will get an alert if they have succesfully won the game

### Project Features
- Chess game with drag and drop functionality
- Chess engine written in C++ that uses a Minimax search algorithm (not the most powerful, but it works and is fast!)
- Hosted on a Python server which communicates with Javascript
- Button to check whether or not there is a legal move or if user is in checkmate. If user is not in checkmate, it will suggest a random move (or maybe the only legal move)

### Language Methods of Communication:
1. Flask Framework with routes. Javascript communicates with the python server using POST requests. 
2. Foreign function interface with ctypes. Python files uses ctypes library to communicate with the C++ engine.

### Reasons for language choice and their functions in the system:
- I used Javascript because it was a great language to use to display a chess interface. It does the front-end part of the system and lets the user interact with the game.
- I used Python because it could host a server and creating chess rules and game logic is much simple in Python. The python game logic functions is used to tell the player whether or not their moves are valid.
- I used C++ because it is the 'fastest' out of the other 2 languages for chess engines. Many chess engines are created using this language as well due to its speed. The C++ is only used for the AI's move and not the player's move.

### Future improvements (other than completeness of chess rules)
- Stronger AI
- Change turn variable from server-side to client-side
- Ability to play against other players
- Adding more to this list

### Libraries used
I used the chessboard.js library for the javascript and front-end part because I do not have a lot of experience with front-end development. Credit goes to: https://chessboardjs.com/

