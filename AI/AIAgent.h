#ifndef AIAGENT_H
#define AIAGENT_H

/**
 * @brief The AIAgent Interface describes
 * the behaviour of any implemented AI agents.
 */

class Board;
class AIAgent
{
public:
    AIAgent() {}
    virtual ~AIAgent() {}
    /**
     * @brief Start the algorithm to choose a cell to play based on a given board.
     * @param board: a reference to the board model.
     * @return the chosen cell index (in a 1D array) that the AI played.
     */
    virtual int play(Board &board) = 0;
    /**
     * @brief reset function that will reset the state of any search algorithm.
     */
    virtual void reset() {}
};

#endif // AIAGENT_H
