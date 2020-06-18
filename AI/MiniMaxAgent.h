#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H
#include "TTTCommonTypes.h"
#include "AIAgent.h"

/**
 * @brief The MiniMaxAgent class handles all the logic
 * of picking a cell based on the MiniMax Algorithm.
 *
 * It simulates all possible plays taking turns simulating
 * an AI turn then a Player turn until a final state is
 * reached, then it scores the final state by giving a
 * negative value if the Player wins and a positive value
 * if it wins, then backtracks picking the minimum score
 * if it is the player turn and the max score if its
 * the AI turn.
 */

class MiniMaxAgent final : public AIAgent
{
public:
    /**
     * @brief MiniMaxAgent: a constructor function that creates the MiniMax Agent.
     * @param depth: cutoff of the minimax algorithm's search tree.
     * @param AImark: The mark (X or O) of the AI.
     * @param playerMark: The mark (X or O) of the human player.
     */
    MiniMaxAgent(unsigned short depth, BoardMarks AImark, BoardMarks playerMark);
    /**
     * @brief Start the minimax algorithm to choose a cell to play based on a given board.
     * @param board: a reference to the board model.
     * @return the chosen cell index (in a 1D array) that the AI played.
     */
    int play(Board &board) override;

private:
    /**
     * @brief depth cutoff of the minimax algorithm's search tree.
     */
    const unsigned short depth_;
    /**
     * @brief The mark (X or O) of the AI.
     */
    const BoardMarks AImark_;
    /**
     * @brief The mark (X or O) of the human player.
     */
    const BoardMarks playerMark_;

    /**
     * @brief AI_WIN_SCORE defines the score of the final board when the AI wins.
     */
    static constexpr short AI_WIN_SCORE = 1;
    /**
     * @brief PLAYER_WIN_SCORE defines the score of the final board when the human player wins.
     */
    static constexpr short PLAYER_WIN_SCORE = -1;
    /**
     * @brief TIE_SCORE defines the score of the final board when the the game is a tie.
     */
    static constexpr short TIE_SCORE = 0;

    /**
     * @brief maxMove simulates the AI choice based on the final game states,
     * as it wants to win it will choose the maximum score of each simulated move.
     * @param board: a reference to the board model.
     * @param depth: The current depth of the search tree.
     * @param alpha: The minimum score that the maximizing player is assured of.
     * @param beta: The maximum score that the minimizing player is assured of.
     * @return
     */
    short maxMove(Board &board, unsigned short depth, short alpha, short beta) const;
    /**
     * @brief minMove simulates the player choice based on the final game states,
     * as it wants to win it will choose the minimum score of each simulated move.
     * @param board: a reference to the board model.
     * @param depth: The current depth of the search tree.
     * @param alpha: The minimum score that the maximizing player is assured of.
     * @param beta: The maximum score that the minimizing player is assured of.
     * @return
     */
    short minMove(Board &board, unsigned short depth, short alpha, short beta) const;
    /**
     * @brief score associates a score to the final states of a game.
     * @param state is an input paramater that specifies the state of the game.
     * @return a score based on the state of the game.
     */
    short score(const BoardState state) const;
};

#endif // MINIMAXAGENT_H
