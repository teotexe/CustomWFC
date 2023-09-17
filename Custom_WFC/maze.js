class TILE {
    constructor(rules) {
        this.LEFT = new Array(rules);
        this.RIGHT = new Array(rules);
        this.TOP = new Array(rules);
        this.BOTTOM = new Array(rules);
        this.texture_path = '';
    }
}

let brd = [];
const tiles = [];
let BOARD_SIZE = 10;

function eventHandler() {
    BOARD_SIZE = parseInt(document.getElementById("boardSize").value);
    brd = [];
    initArray();
    completeBoard(0, 0, brd);
}

const blank = new TILE(3);
blank.LEFT = [0, 0, 0];
blank.RIGHT = [0, 0, 0];
blank.TOP = [0, 0, 0];
blank.BOTTOM = [0, 0, 0];
blank.texture_path = 'pipes/blank.png';
tiles.push(blank);

const up = new TILE(3);
up.LEFT = [0, 1, 0];
up.RIGHT = [0, 1, 0];
up.TOP = [0, 1, 0];
up.BOTTOM = [0, 0, 0];
up.texture_path = 'pipes/up.png';
tiles.push(up);

const down = new TILE(3);
down.TOP = [0, 0, 0];
down.RIGHT = [0, 1, 0];
down.BOTTOM = [0, 1, 0];
down.LEFT = [0, 1, 0];
down.texture_path = 'pipes/down.png';
tiles.push(down);

const left = new TILE(3);
left.TOP = [0, 1, 0];
left.RIGHT = [0, 0, 0];
left.BOTTOM = [0, 1, 0];
left.LEFT = [0, 1, 0];
left.texture_path = 'pipes/left.png';
tiles.push(left);

const right = new TILE(3);
right.TOP = [0, 1, 0];
right.RIGHT = [0, 1, 0];
right.BOTTOM = [0, 1, 0];
right.LEFT = [0, 0, 0];
right.texture_path = 'pipes/right.png';
tiles.push(right);

function printBoard(brd) {
    const board = document.getElementById("board");
    board.innerHTML = ''; // Clear the board

    for (let i = 0; i < BOARD_SIZE; i++) {
        const row = document.createElement("tr");
        for (let j = 0; j < BOARD_SIZE; j++) {
            const cell = document.createElement("td");
            const tile = brd[i][j][0];
            cell.style.backgroundImage = `url(${tile.texture_path})`;
            cell.style.backgroundSize = "cover";
            row.appendChild(cell);
        }
        board.appendChild(row);
    }
}


function completeBoard(row, col, brd) {
    if (row === BOARD_SIZE) {
        console.log('Board complete');
        printBoard(brd);
        return true;
    }

    if (col === BOARD_SIZE) {
        return completeBoard(row + 1, 0, brd);
    }

    if (!brd[row][col] || brd[row][col].length === 0) {
        return false;
    }

    let i = Math.floor(Math.random() * brd[row][col].length);
    let value = brd[row][col][i];
    let brdCopy = JSON.parse(JSON.stringify(brd));

    if (collapseTile(row, col, value, brdCopy)) {
        if (completeBoard(row, col + 1, brdCopy)) return true;
    }

    brd[row][col].splice(i, 1);

    return completeBoard(row, col, brd);
}


function collapseTile(row, col, tile, brd) {
    brd[row][col] = [tile];

    if (col > 0) {
        let curr = tile;
        for (let j = 0; j < brd[row][col - 1].length; j++) {
            if (
                brd[row][col - 1][j].RIGHT.toString() !== tile.LEFT.toString()
            ) {
                brd[row][col - 1].splice(j, 1);
                j--;
            }
        }
        if (brd[row][col - 1].length > 0) curr = brd[row][col - 1][0];
        else return false;
    }

    if (col < BOARD_SIZE - 1) {
        let curr = tile;
        for (let j = 0; j < brd[row][col + 1].length; j++) {
            if (
                brd[row][col + 1][j].LEFT.toString() !== tile.RIGHT.toString()
            ) {
                brd[row][col + 1].splice(j, 1);
                j--;
            }
        }
        if (brd[row][col + 1].length > 0) curr = brd[row][col + 1][0];
        else return false;
    }

    if (row > 0) {
        let curr = tile;
        for (let j = 0; j < brd[row - 1][col].length; j++) {
            if (
                brd[row - 1][col][j].BOTTOM.toString() !== tile.TOP.toString()
            ) {
                brd[row - 1][col].splice(j, 1);
                j--;
            }
        }
        if (brd[row - 1][col].length > 0) curr = brd[row - 1][col][0];
        else return false;
    }

    if (row < BOARD_SIZE - 1) {
        let curr = tile;
        for (let j = 0; j < brd[row + 1][col].length; j++) {
            if (
                brd[row + 1][col][j].TOP.toString() !== tile.BOTTOM.toString()
            ) {
                brd[row + 1][col].splice(j, 1);
                j--;
            }
        }
        if (brd[row + 1][col].length > 0) curr = brd[row + 1][col][0];
        else return false;
    }

    return true;
}

function initArray()
{
    for (let i = 0; i < BOARD_SIZE; i++) {
    brd.push([]);
    for (let j = 0; j < BOARD_SIZE; j++) {
        brd[i].push([...tiles]); // Create a copy of the tiles array
    }
}}

window.onload = function () {
    initArray();
    completeBoard(0, 0, brd);
};
