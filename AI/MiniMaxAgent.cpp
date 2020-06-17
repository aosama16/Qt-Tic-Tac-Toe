#include "MiniMaxAgent.h"
#include "Board.h"
#include <QPair>
#include <limits.h>

MiniMaxAgent::MiniMaxAgent(unsigned short depth, BoardMarks AImark, BoardMarks playerMark)
    : depth_(depth),
      AImark_(AImark),
      playerMark_(playerMark) {}

short MiniMaxAgent::maxMove(Board &board, unsigned short depth, short alpha, short beta) const
{
    // if game over return score
    BoardState state = board.evaluateBoard();
    if ( (0 == depth) || (BoardState::NoWinner != state) )
        return score(state);

    short bestScore = SHRT_MIN;
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, AImark_);

                // Compare result of this move with respect to AI
                short score = minMove(board, depth - 1, alpha, beta);

                // Reset the move done
                board.resetCell(row, col);

                bestScore = std::max(bestScore, score);
                alpha = std::max(alpha, score);
                if (beta <= alpha)
                    break;
            }
        }
    }
    return bestScore;
}

short MiniMaxAgent::minMove(Board &board, unsigned short depth, short alpha, short beta) const
{
    // if game over return score
    BoardState state = board.evaluateBoard();
    if ( (0 == depth) || (BoardState::NoWinner != state) )
        return score(state);

    short bestScore = SHRT_MAX;
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, playerMark_);

                // Compare result of this move with respect to player
                short score = maxMove(board, depth - 1, alpha, beta);

                // Reset the move done
                board.resetCell(row, col);

                bestScore = std::min(bestScore, score);
                beta = std::min(beta, score);
                if (beta <= alpha)
                    break;
            }
        }
    }
    return bestScore;
}

int MiniMaxAgent::score(const BoardState state) const
{
    if ( (BoardMarks::O == AImark_) && (BoardState::OWins == state) )
        return AI_WIN_SCORE;
    if ( (BoardMarks::X == AImark_) && (BoardState::XWins == state) )
        return AI_WIN_SCORE;
    if ( (BoardMarks::O == AImark_) && (BoardState::XWins == state) )
        return PLAYER_WIN_SCORE;
    if ( (BoardMarks::X == AImark_) && (BoardState::OWins == state) )
        return PLAYER_WIN_SCORE;

    return TIE_SCORE;
}

int MiniMaxAgent::play(Board &board)
{
    if (BoardState::NoWinner != board.evaluateBoard())
        return defaults::INVALID_CELL;

    int bestScore = INT_MIN;
    QPair<size_t, size_t> bestEntry;
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, AImark_);

                int moveScore = minMove(board, depth_ - 1, SHRT_MIN, SHRT_MAX);
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestEntry.first = row;
                    bestEntry.second = col;
                }

                // Reset the move done
                board.resetCell(row, col);
            }
        }
    }

    board.setPlayerInput(bestEntry.first, bestEntry.second, AImark_);
    return bestEntry.first * board.size() + bestEntry.second;
}
