#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "Board.h"

using namespace testing;

TEST(BoardTest, resetBoard)
{
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    board.reset();

    EXPECT_EQ(board.at(0, 0), BoardMarks::Empty);
    EXPECT_EQ(board.at(0, 1), BoardMarks::Empty);
    EXPECT_EQ(board.at(0, 2), BoardMarks::Empty);

    EXPECT_EQ(board.at(1, 0), BoardMarks::Empty);
    EXPECT_EQ(board.at(1, 1), BoardMarks::Empty);
    EXPECT_EQ(board.at(1, 2), BoardMarks::Empty);

    EXPECT_EQ(board.at(2, 0), BoardMarks::Empty);
    EXPECT_EQ(board.at(2, 1), BoardMarks::Empty);
    EXPECT_EQ(board.at(2, 2), BoardMarks::Empty);
}

TEST(BoardTest, evaluateBoardXWins3x3)
{
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* X X X
     * O O X
     * - O - */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* O O X
     * X X X
     * - O - */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::Empty);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::Empty);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O O X
     * - O -
     * X X X */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X O O
     * X O X
     * X X O */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* O X O
     * O X X
     * X X O */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O O X
     * O X X
     * X O X */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* X O O
     * O X X
     * X O X */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O O X
     * O X X
     * X O X */
    EXPECT_EQ(BoardState::XWins, board.evaluateBoard());
}

TEST(BoardTest, evaluateBoardOWins3x3)
{
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* O O O
     * X X O
     * - X - */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* X X O
     * O O O
     * - X - */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::Empty);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::Empty);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X X O
     * - X -
     * O O O */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O X X
     * O X O
     * O O X */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* X O X
     * X O O
     * O O X */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X X O
     * X O O
     * O X O */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* O X X
     * X O O
     * O X O */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X X O
     * X O O
     * O X O */
    EXPECT_EQ(BoardState::OWins, board.evaluateBoard());
}

TEST(BoardTest, evaluateBoardTie3x3){
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::O);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X O X
     * O X X
     * O X O */
    EXPECT_EQ(BoardState::Tie, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O X O
     * X O X
     * X O X */
    EXPECT_EQ(BoardState::Tie, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X X O
     * O X X
     * X O O */
    EXPECT_EQ(BoardState::Tie, board.evaluateBoard());
}

TEST(BoardTest, evaluateBoardNoWinner3x3){
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::X);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X O X
     * O X X
     * - X O */
    EXPECT_EQ(BoardState::NoWinner, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::Empty);
    board.setPlayerInput(0, 1, BoardMarks::Empty);
    board.setPlayerInput(0, 2, BoardMarks::Empty);

    board.setPlayerInput(1, 0, BoardMarks::Empty);
    board.setPlayerInput(1, 1, BoardMarks::Empty);
    board.setPlayerInput(1, 2, BoardMarks::Empty);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::Empty);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* - - -
     * - - -
     * - - - */
    EXPECT_EQ(BoardState::NoWinner, board.evaluateBoard());

    board.reset();

    board.setPlayerInput(0, 0, BoardMarks::Empty);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::Empty);

    board.setPlayerInput(1, 0, BoardMarks::Empty);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::Empty);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* - X -
     * - X O
     * X - O */
    EXPECT_EQ(BoardState::NoWinner, board.evaluateBoard());
}

TEST(BoardTest, setPlayerInputValid){
    Board board(4);
    EXPECT_EQ(true, board.setPlayerInput(0, 0, BoardMarks::X));
    EXPECT_EQ(true, board.setPlayerInput(3, 3, BoardMarks::X));
    EXPECT_EQ(true, board.setPlayerInput(2, 1, BoardMarks::X));
    EXPECT_EQ(true, board.setPlayerInput(1, 0, BoardMarks::X));
}

TEST(BoardTest, setPlayerInputOutOfBounds){
    Board board(4);
    EXPECT_ANY_THROW(board.setPlayerInput(0, 4, BoardMarks::X));
    EXPECT_ANY_THROW(board.setPlayerInput(-1, 2, BoardMarks::X));
    EXPECT_ANY_THROW(board.setPlayerInput(5, 2, BoardMarks::X));
    EXPECT_ANY_THROW(board.setPlayerInput(-1, -1, BoardMarks::X));
}

TEST(BoardTest, setPlayerInputOverwrite){
    Board board(4);
    EXPECT_EQ(true, board.setPlayerInput(0, 0, BoardMarks::X));
    EXPECT_EQ(false, board.setPlayerInput(0, 0, BoardMarks::X));
    EXPECT_EQ(true, board.setPlayerInput(3, 3, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(3, 3, BoardMarks::X));
}

TEST(BoardTest, setPlayerInputAfterGameOver){
    Board board(3);

    // O Wins
    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::O);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    /* X X O
     * O O O
     * - X - */
    EXPECT_EQ(false, board.setPlayerInput(0, 0, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(3, 3, BoardMarks::X));
    EXPECT_EQ(false, board.setPlayerInput(2, 1, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(1, 0, BoardMarks::X));

    board.reset();

    // X wins
    board.setPlayerInput(0, 0, BoardMarks::X);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::O);

    /* X O O
     * X O X
     * X X O */
    EXPECT_EQ(false, board.setPlayerInput(0, 0, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(3, 3, BoardMarks::X));
    EXPECT_EQ(false, board.setPlayerInput(2, 1, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(1, 0, BoardMarks::X));

    board.reset();

    // Tie
    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::X);
    board.setPlayerInput(0, 2, BoardMarks::O);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::O);
    board.setPlayerInput(1, 2, BoardMarks::X);

    board.setPlayerInput(2, 0, BoardMarks::X);
    board.setPlayerInput(2, 1, BoardMarks::O);
    board.setPlayerInput(2, 2, BoardMarks::X);

    /* O X O
     * X O X
     * X O X */
    EXPECT_EQ(false, board.setPlayerInput(0, 0, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(3, 3, BoardMarks::O));
    EXPECT_EQ(false, board.setPlayerInput(2, 1, BoardMarks::X));
    EXPECT_EQ(false, board.setPlayerInput(1, 0, BoardMarks::X));
}

TEST(BoardTest, boardAccessValid){
    Board board(3);

    board.setPlayerInput(0, 0, BoardMarks::O);
    board.setPlayerInput(0, 1, BoardMarks::O);
    board.setPlayerInput(0, 2, BoardMarks::Empty);

    board.setPlayerInput(1, 0, BoardMarks::X);
    board.setPlayerInput(1, 1, BoardMarks::X);
    board.setPlayerInput(1, 2, BoardMarks::O);

    board.setPlayerInput(2, 0, BoardMarks::Empty);
    board.setPlayerInput(2, 1, BoardMarks::X);
    board.setPlayerInput(2, 2, BoardMarks::Empty);

    EXPECT_EQ(BoardMarks::X, board.at(1, 1));
    EXPECT_EQ(BoardMarks::O, board.at(1, 2));
    EXPECT_EQ(BoardMarks::Empty, board.at(2, 2));
}

TEST(BoardTest, boardAccessInValid){
    Board board(3);

    EXPECT_ANY_THROW(board.at(1, 4));
    EXPECT_ANY_THROW(board.at(-1, 2));
    EXPECT_ANY_THROW(board.at(-10, -10));
    EXPECT_ANY_THROW(board.at(5, 9));
}
