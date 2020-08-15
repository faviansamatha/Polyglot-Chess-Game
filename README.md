# Prototype Polygot Chess Program

### How to start

Here are the instructions to start:

1. Execute `vagrant up`
2. Execute `vagrant ssh` (or however you get into the vagrant environment)
3. Execute `cd project/project` (to access the project folder)
4. Execute `make` or `make build` (to build the c++ files to be callable from python and to start the server)
5. Open a web-browser and go to localhost:5000


### Project Description
This project was meant to imitate a human player vs an ai in chess. However, some rules of chess have not been implemented yet.
- The ability to castle
- The ability to do enpassant
- The ability to promote a pawn to a queen
- The ability to play as black
- Stalemate leads to one player winning (player who moved last)

These will be done in future implementations. However, the game is functioning. Players will have to press a button to check if they have no more moves.
The player will get an alert if they have succesfully won the game

### Language Methods of Communication:
1. Flask Framework and Routes. Javascript 
2. Foreign function interface with ctypes. Python files uses 


### Reasons for language choice:
- I used Javascript because it was a great language to use to display a chess interface. 
- I used Python because it could host a server and creating chess rules and game logic is much simple in Python.
- I used C++ because it is the 'fastest' out of the other 2 languages for chess engines. Many chess engines are created using this language as well due to its speed.


The make file contains other commands to help out execution
1. `make run` Runs the python server (use when the c++ files are already built for python use)
2. `make reubild` Used to rebuild the C build folder
3. `make clean` Used to remove the C build folder

### Future improvements (other than completeness of chess rules)
- Stronger AI
- Change turn variable from server-side to client-side
- Ability to play against other players
- Adding more to this list

