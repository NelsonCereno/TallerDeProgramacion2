#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "State.h"
#include <queue>
#include <vector>

class BranchAndBound {
public:
    State *best;
    int lowerBound;
    BranchAndBound();
    int calculateLowerBound(State *s);
    int selectVertex(State *s);
    int branchAndBound(State *s);
};

#endif // BRANCHANDBOUND_H