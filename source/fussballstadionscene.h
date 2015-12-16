#ifndef FUSSBALLSTADIONSCENE_H
#define FUSSBALLSTADIONSCENE_H

#include "node.h"
#include "physicengine.h"
#include "drawable.h"
#include "transformation.h"
#include "texture.h"
#include "trianglemesh.h"
#include "simpleplane.h"
#include "simplesphere.h"
#include "simplecube.h"

class FussballStadionScene
{
private:
    bool initialized;
    Node* root;

    PhysicEngine* physicEngine;
    int physicEngineSlot;

    // Note (julius): fussballfeld collisionmesh gibts weil iwie die uv maps abgefucked
    // waren sobald man das eigentliche feld als physic object macht
    Drawable* fussballFeld;
    Drawable* fussballFeldCollisionMesh;
    PhysicObject* fussballFeldPhysicObject;
    Transformation* fussballFeldCollisionMeshTransformation;

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

    void DoStuff();
};

#endif // FUSSBALLSTADIONSCENE_H
