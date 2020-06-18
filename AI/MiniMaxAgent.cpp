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
    // if game over return score.
    BoardState state = board.evaluateBoard();
    if ( (0 == depth) || (BoardState::NoWinner != state) )
        return score(state);

    // Choose the best score given all empty cell choices.
    short bestScore = SHRT_MIN;
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, AImark_);

                // Compare result of this move with respect to AI.
                short score = minMove(board, depth - 1, alpha, beta);

                // Reset the move done.
                board.resetCell(row, col);

                // Update the best score.
                bestScore = std::max(bestScore, score);
                // Update alpha
                alpha = std::max(alpha, score);
                // Prune the rest of cells after this one.
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

                // Update the best score.
                bestScore = std::min(bestScore, score);
                // Update beta
                beta = std::min(beta, score);
                // Prune the rest of cells after this one.
                if (beta <= alpha)
                    break;
            }
        }
    }
    return bestScore;
}

short MiniMaxAgent::score(const BoardState state) const
{
    // AI win score.
    if ( (BoardMarks::O == AImark_) && (BoardState::OWins == state) )
        return AI_WIN_SCORE;
    if ( (BoardMarks::X == AImark_) && (BoardState::XWins == state) )
        return AI_WIN_SCORE;
    // Player win score.
    if ( (BoardMarks::O == AImark_) && (BoardState::XWins == state) )
        return PLAYER_WIN_SCORE;
    if ( (BoardMarks::X == AImark_) && (BoardState::OWins == state) )
        return PLAYER_WIN_SCORE;

    // Tie or a non final state score.
    return TIE_SCORE;
}

int MiniMaxAgent::play(Board &board)
{
    // No play if the board is at a final state.
    if (BoardState::NoWinner != board.evaluateBoard())
        return defaults::INVALID_CELL;

    // Start of the minimax algorith and choose the best score of all available cells.
    int bestScore = INT_MIN;
    QPair<size_t, size_t> bestEntry;
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board.size(); ++col) {
            if (BoardMarks::Empty == board.at(row, col)) {
                // Try the move
                board.setPlayerInput(row, col, AImark_);

                // Update the best score and the best cell location.
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

    // Set the AI choice on the board.
    board.setPlayerInput(bestEntry.first, bestEntry.second, AImark_);
    // Return the 1D index of the cell to delegate any other updates needed.
    return static_cast<int>(bestEntry.first * board.size() + bestEntry.second);
}
