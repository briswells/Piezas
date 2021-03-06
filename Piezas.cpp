#include "Piezas.h"
#include <vector>
#include <iostream>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas():
    board(std::vector< std::vector<Piece> >(4, std::vector<Piece>(3, Blank))),
    turn(X)
{}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  board = std::vector< std::vector<Piece> >(4, std::vector<Piece>(3, Blank));
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  Piece cur = turn;
  if(turn == X){
    turn = O;
  }
  else{
    turn = X;
  }
  if (column >= 0 && column < 4){
    if(board[column][2] == Blank){
      for(int i = 0; i < (int)board[column].size(); ++i){
        if(board[column][i] == Blank){
          board[column][i] = cur;
          return cur;
        }
      }
    }
    else{
      return Blank;
    }
  }
  return Invalid;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if (column >= 0 && column < 4 && row >= 0 && row < 3){
    return board[column][row];
  }
  return Invalid;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  int xMax(1), oMax(1), curStreak(1);
  for(int i = 0; i < (int)board.size(); ++i){
    curStreak = 1;
    Piece curChecking = Blank;
    for(int j = 0; j < (int)board[i].size(); ++j){
      Piece curPiece = pieceAt(j, i);
      if(curPiece == Blank){
        return Invalid;
      }
      else if(curChecking == curPiece){
        curStreak++;
      }
      else{
        if(curPiece == X){
          curChecking = X;
          if(curStreak > oMax){
            oMax = curStreak;
          }
          curStreak = 1;
        }
        else if(curPiece == O){
          curChecking = O;
          if(curStreak > xMax){
            xMax = curStreak;
          }
          curStreak = 1;
        }
      }
    }
    if(curChecking == X && curStreak > xMax){
      xMax = curStreak;
    }
    if(curChecking == O && curStreak > oMax){
      oMax = curStreak;
    }
  }
  for(int j = 0; j < (int)board[0].size(); ++j){
    curStreak = 1;
    Piece curChecking = Blank;
    for(int i = 0; i < (int)board.size(); ++i){
      Piece curPiece = pieceAt(j, i);
      if(curPiece == Blank){
        return Invalid;
      }
      else if(curChecking == curPiece){
        curStreak++;
      }
      else{
        if(curPiece == X){
          curChecking = X;
          if(curStreak > oMax){
            oMax = curStreak;
          }
          curStreak = 1;
        }
        else if(curPiece == O){
          curChecking = O;
          if(curStreak > xMax){
            xMax = curStreak;
          }
          curStreak = 1;
        }
      }
    }
    if(curChecking == X && curStreak > xMax){
      xMax = curStreak;
    }
    if(curChecking == O && curStreak > oMax){
      oMax = curStreak;
    }
  }
  if(xMax > oMax){
    return X;
  }
  else if(oMax > xMax){
    return O;
  }
  return Blank;
}
