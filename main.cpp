#include <iostream>
#include "GameBoard.h"

int main() {
    GameBoard<2, 2, char, 3> gb;
    gb.setPiece(0,0, 'F',0);
    gb.setPiece(1,1, 'B',2);

    PieceInfo<char> ret = gb.setPiece(0,0,'B', 3);


    if(!ret){
        cout << "nullptr" << endl;
    }

    else{
        cout << ret ->first << " " << ret ->second << endl;
    }

    cout <<  "player: "<<gb.getPiece(0,0)->first << "\tPiece: " << gb.getPiece(0,0)->second << endl;
//    cout <<  "player: "<<gb.getPiece(1,1)->first << "\tPiece: " << gb.getPiece(1,1)->second << endl;

    if(gb.getPiece(1,1) == nullptr){
        cout << "gb.getPiece(0,1) == nullptr" << endl;
    }



    return 0;
}