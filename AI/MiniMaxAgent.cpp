#include "MiniMaxAgent.h"
#include "Board.h"
#include <QPair>
#include <limits.h>

MiniMaxAgent::MiniMaxAgent(int depth)
    : depth(depth), AImark(BoardMarks::Empty), playerMark(BoardMarks::Empty) {}

int MiniMaxAgent::maxMove(Board &board, int depth, int alpha, int beta) {
    // if game over return score
    BoardState state = board.evaluateBoard();
    if (depth == 0 || state != BoardState::NoWinner)
        return score(state);

    int bestScore = INT_MIN;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (board.at(row, col) == BoardMarks::Empty) {
                // Try the move
                board.setPlayerInput(row, col, this->AImark);

                // Compare result of this move with respect to AI
                int score = minMove(board, depth - 1, alpha, beta);

                // Reset the move done
                board.setPlayerInput(row, col, BoardMarks::Empty);

                bestScore = std::max(bestScore, score);
                alpha = std::max(alpha, score);
                if (beta <= alpha)
                    break;
            }
        }
    }
    return bestScore;
}

int MiniMaxAgent::minMove(Board &board, int depth, int alpha, int beta) {
    // if game over return score
    BoardState state = board.evaluateBoard();
    if (depth == 0 || state != BoardState::NoWinner)
        return score(state);

    int bestScore = INT_MAX;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (board.at(row, col) == BoardMarks::Empty) {
                // Try the move
                board.setPlayerInput(row, col, playerMark);

                // Compare result of this move with respect to player
                int score = maxMove(board, depth - 1, alpha, beta);

                // Reset the move done
                board.setPlayerInput(row, col, BoardMarks::Empty);

                bestScore = std::min(bestScore, score);
                beta = std::min(beta, score);
                if (beta <= alpha)
                    break;
            }
        }
    }
    return bestScore;
}

int MiniMaxAgent::score(BoardState state) {
    if (this->AImark == BoardMarks::O && state == BoardState::OWins)
        return 1;
    else if (this->AImark == BoardMarks::X && state == BoardState::XWins)
        return 1;
    else if (this->AImark == BoardMarks::O && state == BoardState::XWins)
        return -1;
    else if (this->AImark == BoardMarks::X && state == BoardState::OWins)
        return -1;
    else
        return 0;
}

int MiniMaxAgent::play(Board &board, BoardMarks mark) {
    if (board.evaluateBoard() != BoardState::NoWinner)
        return -1;

    if (this->AImark == BoardMarks::Empty) {
        this->AImark = mark;
        this->playerMark =
            (this->AImark == BoardMarks::O ? BoardMarks::X : BoardMarks::O);
    }

    int bestScore = INT_MIN;
    QPair<int, int> bestEntry;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
            if (board.at(row, col) == BoardMarks::Empty) {
                // Try the move
                board.setPlayerInput(row, col, AImark);

                int moveScore = minMove(board, this->depth - 1, INT_MIN, INT_MAX);
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestEntry.first = row;
                    bestEntry.second = col;
                }

                // Reset the move done
                board.setPlayerInput(row, col, BoardMarks::Empty);
            }
        }
    }

    board.setPlayerInput(bestEntry.first, bestEntry.second, this->AImark);
    return bestEntry.first * board.size() + bestEntry.second;
}

void MiniMaxAgent::reset() {
    AImark = BoardMarks::Empty;
    playerMark = BoardMarks::Empty;
}
