#ifndef FUSSBALLSTADIONSCENE_H
#define FUSSBALLSTADIONSCENE_H

#include "node.h"
#include "physicengine.h"
#include "drawable.h"
#include "transformation.h"
#include "texture.h"
#include "trianglemesh.h"

class FussballStadionScene
{
private:
    bool initialized;
    Node* root;

    PhysicEngine* physicEngine;
    int physicEngineSlot;

    Drawable* fussballFeld;
    PhysicObject* fussballFeldPhysicObject;
    Transformation* fussballFeldTransformation;

    Drawable* fussball;
    PhysicObject* fussballPhysicObject;
    Transformation* fussballTransformation;

    Drawable* tor;
    PhysicObject* torPhysicObject;
    Transformation* torTransformation;

public:
    FussballStadionScene();

    void Initialize();

    Node * GetRootNode();
};

#endif // FUSSBALLSTADIONSCENE_H
