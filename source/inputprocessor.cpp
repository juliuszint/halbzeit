#include "inputprocessor.h"

Inputprocessor::Inputprocessor(FussballStadionScene* station)
{
    this->stadion = station;
}

void Inputprocessor::doIt()
{
    if(InputObserver::getInstance()->isKeyPressed(Qt::Key_1))
    {
        this->stadion->DoStuff();
    }
}

