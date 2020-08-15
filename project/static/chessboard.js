
//used chessboard.js for the visual display: https://chessboardjs.com/index.html

//Board configuration
var config = {
    position: 'start',
    draggable: true,
    droppOffBoard: 'snapback',
    onDrop: onDrop
}

//Initializing chessboard
var board = Chessboard('board', config)
$('#startBtn').on('click', function(){


    $.ajax({
        type: "POST",
        url: '/newGame',
        success: (results)=>{
           console.log("Starting a new game")
        },
        error: function(error){
            console.log(error);
            console.log("There was an error with the server");
            // return 'snapback';
        }

    })
    board.start()
    

})

//Button for checkmate
$('#checkmate').on('click', function(){

    $.ajax({
        contentType: 'application/json;charset=UTF-8',
        type: "POST",
        url: '/checkIfMate',
        data: JSON.stringify({ board: board.position()}),
        dataTye: "json",
        success: (results)=>{

        },
        error: function(error){
            console.log(error);
            console.log("There was an error with the server");
            // return 'snapback';
        }

    }).done(function(data){

        var output = JSON.parse(data);
        if(output['legal'] == "False"){
            alert("Yea, you lost and got checkmated");
        }
        else{

            var from = output['moves'][0] + output['moves'][1]
            var to = output['moves'][2] + output['moves'][3]              
            alert("You are not checkmated. You still have some legal moves. For example " + from + " to " + to)
        }
    })

})

//Does a post request to check if the move is valid
async function isValidMove(outputData){

    return $.ajax({
        contentType: 'application/json;charset=UTF-8',
        type: "POST",
        url: '/isValidMove',
        data: outputData,
        dataTye: "json",
        success: (results)=>{
           console.log("Success validating move")

        },
        error: function(error){
            console.log(error);
            console.log("There was an error with the server");
            // return 'snapback';
        }
    })
}

//Does a POST request to get a move from the engine
async function getAiMove(board){

    return $.ajax({
        contentType: 'application/json;charset=UTF-8',
        type: "POST",
        url: '/aiTurn',
        data: board,
        dataTye: "json",
        success: (result)=>{
        },
        error: function(error){
            console.log(error);
            console.log("There was an error with the server");
            // return 'snapback';
        }
    }) 
}

// async function isValidMoveCallback(returnData){
//     console.log(returnData);
//     return returnData
// }
//Gets executed when a chess piece is dropped on the board
async function onDrop(source, target, piece, newPos, oldPos, orientation){

    //If t
    if(target != 'offboard')
    {
        var data = JSON.stringify({
            old: oldPos, 
            new: newPos,
            source: source,
            target: target,
            piece: piece,
            });

        var output = await isValidMove(data);
        output = JSON.parse(output);
        if(output['results'] === "False"){

            board.position(oldPos);
        }

        else if (output['results'] == "True"){
            var dataBoard = JSON.stringify({ board: newPos});
            var aiMoveJ = await getAiMove(dataBoard);


            var aiMove = JSON.parse(aiMoveJ) ;

            if (aiMove['legal'] == "False"){
                alert("Congratulations! You won!")

            }else{              
            let from = aiMove['moves'][0] + aiMove['moves'][1]
            let to = aiMove['moves'][2] + aiMove['moves'][3]  
            let aiFinalMove = from + '-' + to;
            board.move(aiFinalMove);
            }
        }
    }

}

