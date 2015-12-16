#include "inputprocessor.h"

Inputprocessor::Inputprocessor(FussballStadionScene* station)
{
    this->stadion = station;
}

void Inputprocessor::doIt()
{
    if(InputObserver::getInstance()->isKeyPressed(Qt::Key_1))
    {
        this->stadion->ShootLeft();
    }
    if(InputObserver::getInstance()->isKeyPressed(Qt::Key_2))
    {
        this->stadion->ShootRight();
    }
    if(InputObserver::getInstance()->isKeyPressed(Qt::Key_3))
    {
        this->stadion->ResetScene();
        InputObserver::getInstance()->setKeyUp(Qt::Key_3, 0);
    }

}

