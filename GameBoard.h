#ifndef ADVANCEDTOPICS_EX4_GAMEBOARD_H
#define ADVANCEDTOPICS_EX4_GAMEBOARD_H

#include <iostream>
#include <memory>

using namespace std;

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template<int ROW, int COL, typename GAME_PIECE, int num_of_players = 2>
class GameBoard {
    PieceInfo<GAME_PIECE> board[ROW][COL];

public:
    GameBoard(){
        for(int i=0; i<ROW; i++) {
            for (int j = 0; j < COL; j++) {
                board[i][j] = nullptr;
            }
        }
    }

    PieceInfo<GAME_PIECE> getPiece(int row, int col){
        if(board[row][col] == nullptr)
            return nullptr;
        pair<int, GAME_PIECE> pieceInfo (board[row][col]->first, board[row][col]->second);
        return make_unique<pair<int, GAME_PIECE>>(pieceInfo);
    }

    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player){
        if(!(player < num_of_players))
            return nullptr;
        else if(board[row][col] == nullptr){
            board[row][col] = make_unique<pair<int, GAME_PIECE>>(player, piece);
            return nullptr;
        }
        else{
            pair<int, GAME_PIECE> oldPieceInfo (board[row][col]->first, board[row][col]->second);
            board[row][col] = make_unique<pair<int, GAME_PIECE>>(player, piece);
            return make_unique<pair<int, GAME_PIECE>>(oldPieceInfo);
        }
    }


};




#endif //ADVANCEDTOPICS_EX4_GAMEBOARD_H
