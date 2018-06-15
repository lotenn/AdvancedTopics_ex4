#include <string>
#include <utility>
#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;

static bool test1(){
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++){
        for(int col =0; col < 7; col++){
            board.setPiece(row, col, "Piece", i);
            i = (i+1)%4;
        }
    }
    int occurence[4]= {0,0,0,0};
    for(auto pieceInfo : board){
        occurence[get<3>(pieceInfo)]++;
    }
    for(int i = 0;i<4;i++){
        if (occurence[i] != 21){
            return false;
        }
    }
    return true;
}

static bool test2(){
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++){
        for(int col =0; col < 7; col++){
            board.setPiece(row, col, "Piece", i);
            i = (i+1)%4;
        }
    }
    int occurence[4]= {0,0,0,0};
    for(auto pieceInfo : board.allPiecesOfPlayer(1)){
        occurence[get<3>(pieceInfo)]++;
    }
    for(int i = 0;i<4;i++){
        if (i==1 && occurence[i] != 21){
            return false;
        }
        else if(i!=1 && occurence[i] != 0){
            return false;
        }
    }
    return true;
}

static bool test3(){
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++){
        for(int col =0; col < 7; col++){
            board.setPiece(row, col, "Piece", i);
            i = (i+1)%4;
        }
    }
    int occurence[4]= {0,0,0,0};
    for(auto pieceInfo : board.allOccureneceOfPiece("Piece")){
        occurence[get<3>(pieceInfo)]++;
    }
    for(int i = 0;i<4;i++){
        if (i==1 && occurence[i] != 21){
            return false;
        }
    }
    return true;
}

static bool test4(){
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++){
        for(int col =0; col < 7; col++){
            board.setPiece(row, col, "Piece", i);
            i = (i+1)%4;
        }
    }
    int occurence[4]= {0,0,0,0};
    for(auto pieceInfo : board.allOccureneceOfPieceForPlayer("Piece",1)){
        occurence[get<3>(pieceInfo)]++;
    }
    for(int i = 0;i<4;i++){
        if (i==1 && occurence[i] != 21){
            return false;
        }
        else if(i!=1 && occurence[i] != 0){
            return false;
        }
    }
    return true;
}


int main(){
	RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);

    return 0;
}
