
var config = {
    position: 'start',
    draggable: true,
    droppOffBoard: 'snapback',
    onDrop: onDrop
}


var board = Chessboard('board', config)
$('#startBtn').on('click', board.start)
$('#clearBtn').on('click', board.clear)

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

async function isValidMoveCallback(returnData){
    console.log(returnData);
    return returnData
}

async function onDrop(source, target, piece, newPos, oldPos, orientation){

    console.log('Source: ' + source)
    console.log('Target: ' + target)
    // console.log('Piece: ' + piece)
    // console.log('New position: ' + Chessboard.objToFen(newPos))
    // console.log('Old position: ' + Chessboard.objToFen(oldPos))
    // console.log('Orientation: ' + orientation)
    // console.log('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
    console.log(piece[0])

    if(target != 'offboard')
    {
        board.draggable = false;
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
        else{
            board.draggable = true;

        }

        
    }
    // board.position(oldPos);

   
    // var test = Math.floor(Math.random()*2);
    // var booltest = false;
    // if(test ===1){
    //     booltest = true;
    // }
    // console.log(booltest);
    // if(booltest){
    //     return 'snapback'
    // }
    // else{
        
    // }
}

