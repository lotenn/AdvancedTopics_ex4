#include <iostream>
#include "GameBoard.h"

int main() {
    GameBoard<2, 2, char> board;
    PieceInfo<char> piece = board.getPiece(1, 1);
    if(!piece)
        cout << "Test 1 succeeded!" << endl;
    else
        cout << "Test 1 failed" << endl;

    piece = board.setPiece(1, 1, 'S', 0);
    if(!piece)
        cout << "Test 2 succeeded!" << endl;
    else
        cout << "Test 2 failed" << endl;

   piece = board.getPiece(1, 1);
    if(!piece)
        cout << "Test 3 failed" << endl;
    else
        cout << "Test 3 - player: " << piece->first << " piece: " << piece->second << endl;

    piece = board.setPiece(1, 2, 'S', 4);
    if(!piece)
        cout << "Test 4 succeeded!" << endl;
    else
        cout << "Test 4 failed" << endl;

    piece = board.getPiece(1, 2);
    if(!piece)
        cout << "Test 5 succeeded!" << endl;
    else
        cout << "Test 5 failed" << endl;

    piece = board.setPiece(2, 2, 'L', 1);
    if(!piece)
        cout << "Test 5 succeeded!" << endl;
    else
        cout << "Test 5 failed" << endl;

    for(auto pieceInfo : board) {
        cout << "row: " << std::get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }
    cout << "**************************" << endl;
    int playerNum = 1;
    for(auto pieceInfo : board.allPiecesOfPlayer(playerNum)) {
        cout << "row: " << std::get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }

    return 0;
}