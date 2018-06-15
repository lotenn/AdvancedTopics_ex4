#ifndef ADVANCEDTOPICS_EX4_EX4_HEADER_H
#define ADVANCEDTOPICS_EX4_EX4_HEADER_H


#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template<int ROWS, int COLS, typename GAME_PIECE, int num_of_players = 2>
class GameBoard {
    vector<PieceInfo<GAME_PIECE>> board;


    bool isValidRow(int row){
        return (0 <= row && row < ROWS);
    }

    bool isValidCol(int col){
        return (0 <= col && col < COLS);
    }

    bool isValidPlayerNumber(int player_num){
        return player_num < num_of_players;
    }

    int calculate_board_index(int row, int col){
        return (row * COLS) + col;
    };

public:
    GameBoard(){
        int board_size = ROWS * COLS;
        for(int i = 0; i < board_size; i++)
            board.push_back(nullptr);
    }

    PieceInfo<GAME_PIECE> getPiece(int row, int col){
        if(!isValidRow(row) || !isValidCol(col))
            return nullptr;
        int piece_index = calculate_board_index(row, col);
        if(!board[piece_index])
            return nullptr;
        int piece_first = board[piece_index]->first;
        GAME_PIECE piece_second = board[piece_index]->second;
        return make_unique<const std::pair<int, GAME_PIECE>>(piece_first, piece_second);
    }

    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player){
        if(!isValidRow(row) || !isValidCol(col) || !isValidPlayerNumber(player))
            return nullptr;
        PieceInfo<GAME_PIECE> _piece = make_unique<const std::pair<int, GAME_PIECE>>(player, piece);
        int piece_index = calculate_board_index(row, col);
        _piece.swap(board[piece_index]);
        return _piece;
    };

    struct Iterator {
        const GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *iterGameBoard;
        typename vector<PieceInfo<GAME_PIECE>>::iterator itr;
        int current_pos;

        Iterator(const GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard,
                 typename vector<PieceInfo<GAME_PIECE>>::iterator _itr, int _current_pos) :
                iterGameBoard(_myGameBoard),
                itr(_itr),
                current_pos(_current_pos){}

        virtual tuple<int, int, GAME_PIECE, int> operator*(){
            int row = (current_pos / COLS) + 1, col = (current_pos % COLS) + 1, player_num = (*itr)->first;
            GAME_PIECE piece = (*itr)->second;
            return make_tuple(row, col, piece, player_num);
        }

        virtual Iterator& operator++() {
            itr++;
            current_pos++;
            find_item();
            return *this;
        }

        virtual void find_item(){
            auto end = iterGameBoard->board.end();
            while(itr != end && *itr == nullptr){
                itr++;
                current_pos++;
            }
        }

        virtual bool operator!=(Iterator other) { return (itr != other.itr); }
    };

    Iterator begin(){
        Iterator iter(this, board.begin(), 0);
        iter.find_item();
        return iter;
    }

    Iterator end(){
        Iterator iter(this, board.end(), (int)board.size());
        return iter;
    }

    class AllPieceOfPlayer{
        GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *playerGameBoard;
        int player_filter;
    public:
        AllPieceOfPlayer(GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard, int _player_filter) :
                playerGameBoard(_myGameBoard),
                player_filter(_player_filter){}

        struct PlayerIterator : Iterator{
            int player;
            PlayerIterator(const GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard,
                           typename vector<PieceInfo<GAME_PIECE>>::iterator _itr, int _current_pos, int _player) :
                    Iterator(_myGameBoard, _itr, _current_pos),
                    player(_player){}

            virtual void find_item(){
                auto end = Iterator::iterGameBoard->board.end();
                while(Iterator::itr != end){
                    bool isNull = *(Iterator::itr) == nullptr;
                    if(!isNull){
                        if((*Iterator::itr)->first == player)
                            break;
                    }
                    Iterator::itr++;
                    Iterator::current_pos++;
                }
            }

            PlayerIterator& operator++() {
                Iterator::itr++;
                Iterator::current_pos++;
                find_item();
                return *this;
            }

        };

        PlayerIterator begin(){
            int current_pos = 0;
            PlayerIterator iter(playerGameBoard, playerGameBoard->board.begin(), current_pos, player_filter);
            iter.find_item();
            return iter;
        }

        PlayerIterator end(){
            int current_pos = playerGameBoard->board.size();
            PlayerIterator iter(playerGameBoard, playerGameBoard->board.end(), current_pos, player_filter);
            return iter;
        }


    };

    AllPieceOfPlayer allPiecesOfPlayer(int player_num){
        return AllPieceOfPlayer(this, player_num);
    }

    class AllOccurrenceOfPiece{
        GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *pieceGameBoard;
        GAME_PIECE piece_filter;
    public:
        AllOccurrenceOfPiece(GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard, GAME_PIECE _piece_filter) :
                pieceGameBoard(_myGameBoard),
                piece_filter(_piece_filter){}

        struct PieceIterator : Iterator{
            GAME_PIECE piece;
            PieceIterator(const GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard,
                          typename vector<PieceInfo<GAME_PIECE>>::iterator _itr, int _current_pos, GAME_PIECE _piece) :
                    Iterator(_myGameBoard, _itr, _current_pos),
                    piece(_piece){}

            virtual void find_item(){
                auto end = Iterator::iterGameBoard->board.end();
                while(Iterator::itr != end){
                    bool isNull = *(Iterator::itr) == nullptr;
                    if(!isNull){
                        if((*Iterator::itr)->second == piece)
                            break;
                    }
                    Iterator::itr++;
                    Iterator::current_pos++;
                }
            }

            PieceIterator& operator++() {
                Iterator::itr++;
                Iterator::current_pos++;
                find_item();
                return *this;
            }
        };

        PieceIterator begin(){
            int current_pos = 0;
            PieceIterator iter(pieceGameBoard, pieceGameBoard->board.begin(), current_pos, piece_filter);
            iter.find_item();
            return iter;
        }

        PieceIterator end(){
            int current_pos = pieceGameBoard->board.size();
            PieceIterator iter(pieceGameBoard, pieceGameBoard->board.end(), current_pos, piece_filter);
            return iter;
        }

    };

    AllOccurrenceOfPiece allOccureneceOfPiece(GAME_PIECE piece){
        return AllOccurrenceOfPiece(this, piece);
    }

    class AllOccurrenceOfPieceForPlayer{
        GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *pieceForPlayerGameBoard;
        int player_filter;
        GAME_PIECE piece_filter;
    public:
        AllOccurrenceOfPieceForPlayer(GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard,
                                      int _player_filter, GAME_PIECE _piece_filter) :
                pieceForPlayerGameBoard(_myGameBoard),
                player_filter(_player_filter),
                piece_filter(_piece_filter){}

        struct PieceForPlayerIterator : Iterator{
            int player;
            GAME_PIECE piece;
            PieceForPlayerIterator(const GameBoard<ROWS, COLS, GAME_PIECE, num_of_players> *_myGameBoard,
                                   typename vector<PieceInfo<GAME_PIECE>>::iterator _itr, int _current_pos,
                                   int _player, GAME_PIECE _piece) :
                    Iterator(_myGameBoard, _itr, _current_pos),
                    player(_player),
                    piece(_piece){}

            virtual void find_item(){
                auto end = Iterator::iterGameBoard->board.end();
                while(Iterator::itr != end){
                    bool isNull = *(Iterator::itr) == nullptr;
                    if(!isNull){
                        if((*Iterator::itr)->first == player && (*Iterator::itr)->second == piece)
                            break;
                    }
                    Iterator::itr++;
                    Iterator::current_pos++;
                }
            }

            PieceForPlayerIterator& operator++() {
                Iterator::itr++;
                Iterator::current_pos++;
                find_item();
                return *this;
            }
        };

        PieceForPlayerIterator begin(){
            int current_pos = 0;
            PieceForPlayerIterator iter(pieceForPlayerGameBoard, pieceForPlayerGameBoard->board.begin(),
                                        current_pos, player_filter, piece_filter);
            iter.find_item();
            return iter;
        }

        PieceForPlayerIterator end(){
            int current_pos = pieceForPlayerGameBoard->board.size();
            PieceForPlayerIterator iter(pieceForPlayerGameBoard, pieceForPlayerGameBoard->board.end(),
                                        current_pos, player_filter, piece_filter);
            return iter;
        }

    };

    AllOccurrenceOfPieceForPlayer allOccureneceOfPieceForPlayer(GAME_PIECE piece, int player_num){
        return AllOccurrenceOfPieceForPlayer(this, player_num, piece);
    }
};


#endif //ADVANCEDTOPICS_EX4_EX4_HEADER_H
