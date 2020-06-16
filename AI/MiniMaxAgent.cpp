#include "MiniMaxAgent.h"
#include "Board.h"
#include <QPair>
#include <limits.h>

MiniMaxAgent::MiniMaxAgent(int depth, BoardMarks AImark, BoardMarks playerMark)
    : depth(depth), AImark(AImark), playerMark(playerMark) {}

int MiniMaxAgent::maxMove(Board &board, int depth, int alpha, int beta) const {
    // if game over return score
    BoardState state = board.evaluateBoard();
    if ( (0 == depth) || (BoardState::NoWinner != state) )
        return score(state);

    int bestScore = INT_MIN;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, this->AImark);

                // Compare result of this move with respect to AI
                int score = minMove(board, depth - 1, alpha, beta);

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

int MiniMaxAgent::minMove(Board &board, int depth, int alpha, int beta) const {
    // if game over return score
    BoardState state = board.evaluateBoard();
    if ( (0 == depth) || (BoardState::NoWinner != state) )
        return score(state);

    int bestScore = INT_MAX;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, playerMark);

                // Compare result of this move with respect to player
                int score = maxMove(board, depth - 1, alpha, beta);

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

int MiniMaxAgent::score(const BoardState state) const {
    if ( (BoardMarks::O == this->AImark) && (BoardState::OWins == state) )
        return AI_WIN_SCORE;
    else if ( (BoardMarks::X == this->AImark) && (BoardState::XWins == state) )
        return AI_WIN_SCORE;
    else if ( (BoardMarks::O == this->AImark) && (BoardState::XWins == state) )
        return PLAYER_WIN_SCORE;
    else if ( (BoardMarks::X == this->AImark) && (BoardState::OWins == state) )
        return PLAYER_WIN_SCORE;
    else
        return TIE_SCORE;
}

int MiniMaxAgent::play(Board &board) {
    if (BoardState::NoWinner != board.evaluateBoard())
        return defaults::INVALID_CELL;

    int bestScore = INT_MIN;
    QPair<int, int> bestEntry;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, AImark);

                int moveScore = minMove(board, this->depth - 1, INT_MIN, INT_MAX);
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

    board.setPlayerInput(bestEntry.first, bestEntry.second, this->AImark);
    return bestEntry.first * board.size() + bestEntry.second;
}
