
var images = {
    0 : "",
    1 : "qrc:///img/bulbasaur.png",
    2 : "qrc:///img/caterpie.png",
    3 : "qrc:///img/charmander.png",
    4 : "qrc:///img/dratini.png",
    5 : "qrc:///img/meowth.png",
    6 : "qrc:///img/pidgey.png",
    7 : "qrc:///img/pikachu.png",
    8 : "qrc:///img/psyduck.png",
    9 : "qrc:///img/venonat.png",
}


function findRow(index, size) {
    return Math.floor(index / size);
}

function findColumn(index, size) {
    return Math.floor(index % size);
}
