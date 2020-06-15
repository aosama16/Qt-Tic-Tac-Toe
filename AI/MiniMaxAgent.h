#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H
#include "TTTCommonTypes.h"
#include "AIAgent.h"

class MiniMaxAgent final : public AIAgent
{
public:
    MiniMaxAgent(int depth);

private:
    int depth;
    BoardMarks AImark;
    BoardMarks playerMark;
    int maxMove(Board &board, int depth, int alpha, int beta);
    int minMove(Board &board, int depth, int alpha, int beta);
    int score(BoardState state);
    int play(Board &board, BoardMarks mark) override;
    void reset() override;
};

#endif // MINIMAXAGENT_H
