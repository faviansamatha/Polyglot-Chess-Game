
var config = {
    position: 'start',
    draggable: true,
    droppOffBoard: 'snapback',
    onDrop: onDrop
}


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
    board.start

})
// $('#checkmate').on('click', board.start)
// $('#clearBtn').on('click', board.clear)

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

async function getAiMove(board){

    return $.ajax({
        contentType: 'application/json;charset=UTF-8',
        type: "POST",
        url: '/aiTurn',
        data: board,
        dataTye: "json",
        success: (result)=>{
           console.log("Success getting ai move")

        },
        error: function(error){
            console.log(error);
            console.log("There was an error with the server");
            // return 'snapback';
        }
    }) 
}

async function isValidMoveCallback(returnData){
    console.log(returnData);
    return returnData
}

async function onDrop(source, target, piece, newPos, oldPos, orientation){

    console.log('Source: ' + source)
    console.log('Target: ' + target)
    console.log('Piece: ' + piece)
    console.log(piece[0])

    if(target != 'offboard')
    {
        // board. = false;
        var data = JSON.stringify({
            old: oldPos, 
            new: newPos,
            source: source,
            target: target,
            piece: piece,
            });

        var output = await isValidMove(data);
        output = JSON.parse(output);
        console.log(output);
        console.log(output["results"]);

        if(output['results'] === "False"){


            board.position(oldPos);

        }
        else if (output['results'] == "True"){

            console.log("HELLO")
            var dataBoard = JSON.stringify({ board: board.position()});
            var aiMoveJ = await getAiMove(dataBoard);
            var aiMove = JSON.parse(aiMoveJ) ;

            let from = aiMove['moves'][0] + aiMove['moves'][1]
            let to = aiMove['moves'][2] + aiMove['moves'][3]  
            let aiFinalMove = from + '-' + to;
            board.move(aiFinalMove);
            console.log(from);
            console.log(to);
            console.log(aiMove);
            console.log(aiFinalMove);
            

        }

        
    }

}

