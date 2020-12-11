/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, constructorTest)
{
  Piezas game;
  bool flag = true;
  for(int x = 0; x < 4; ++x){
    for(int y = 0; y < 3; ++y){
      if(game.pieceAt(y, x) != Blank){
        flag = false;
      }
    }
  }
	ASSERT_TRUE(flag);
}

TEST(PiezasTest, pieceAt)
{
  Piezas game;
	ASSERT_TRUE((game.pieceAt(0,0) == Blank));
}

TEST(PiezasTest, pieceAtOutOfBoundsNeg)
{
  Piezas game;
	ASSERT_FALSE((game.pieceAt(-1,-1) == Blank));
}

TEST(PiezasTest, pieceAtOutOfBoundsPos)
{
  Piezas game;
	ASSERT_FALSE((game.pieceAt(10,10) == Blank));
}

TEST(PiezasTest, dropPieceBasic)
{
  Piezas game;
  game.dropPiece(0);
	ASSERT_TRUE((game.pieceAt(0,0) == X));
}

TEST(PiezasTest, dropPieceFillRow)
{
  Piezas game;
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(0);
  Piece test = game.dropPiece(0);
	ASSERT_TRUE((test == Blank));
}

TEST(PiezasTest, dropPieceOutOfBounds)
{
  Piezas game;
  Piece test = game.dropPiece(-1);
	ASSERT_TRUE((test == Invalid));
}

TEST(PiezasTest, resetTest)
{
  Piezas game;
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(0);
  game.reset();
  bool flag = true;
  for(int x = 0; x < 4; ++x){
    for(int y = 0; y < 3; ++y){
      if(game.pieceAt(y, x) != Blank){
        flag = false;
      }
    }
  }
	ASSERT_TRUE(flag);
}

TEST(PiezasTest, gameStateUnfinished)
{
  Piezas game;
  game.dropPiece(0);
  Piece test = game.gameState();
	ASSERT_TRUE((test == Invalid));
}

TEST(PiezasTest, gameStateTie)
{
  Piezas game;
  for(int i = 0; i < 4; ++i){
    game.dropPiece(i);
    game.dropPiece(i);
    game.dropPiece(i);
  }
  Piece test = game.gameState();
	ASSERT_FALSE((test == X || test == O));
}

TEST(PiezasTest, gameStateHorizontalWin)
{
  Piezas game;
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(0);
  game.dropPiece(3);
  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(1);
  Piece test = game.gameState();
	ASSERT_TRUE((test == X));
}

TEST(PiezasTest, gameStateVerticalWin)
{
  Piezas game;
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(0);
  game.dropPiece(2);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(3);
  game.dropPiece(1);
  game.dropPiece(2);
  Piece test = game.gameState();
  std::cout<<test<<std::endl;
	ASSERT_TRUE((test == X));
}
