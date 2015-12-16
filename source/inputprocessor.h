#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include "idleobserver.h"
#include "fussballstadionscene.h"
#include "inputobserver.h"

class Inputprocessor : public Node, public IdleObserver
{
private:
    FussballStadionScene* stadion;
public:
    Inputprocessor(FussballStadionScene* stadion);

    void doIt();
};

#endif // INPUTPROCESSOR_H
