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
  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 3; ++j){
      if(game.pieceAt(i, j) != Blank){
        flag = false;
        break;
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
