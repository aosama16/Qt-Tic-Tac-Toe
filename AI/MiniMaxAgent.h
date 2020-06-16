#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H
#include "TTTCommonTypes.h"
#include "AIAgent.h"

class MiniMaxAgent final : public AIAgent
{
public:
    MiniMaxAgent(int depth, BoardMarks AImark, BoardMarks playerMark);

private:
    const int depth;
    const BoardMarks AImark;
    const BoardMarks playerMark;
    int maxMove(Board &board, int depth, int alpha, int beta) const;
    int minMove(Board &board, int depth, int alpha, int beta) const;
    int score(const BoardState state) const;
    int play(Board &board) override;
};

#endif // MINIMAXAGENT_H
