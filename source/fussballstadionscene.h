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
    QVector3D fussballRootPosition;

    // Todo (julius): sollte man eigentlich mal noch in einen TorNode auslagern
    Drawable* tor;
    Drawable* torCollisionPlaneBack;
    Drawable* torCollisionPlaneLeft;
    Drawable* torCollisionPlaneRight;
    PhysicObject* torPhysicObjectBack;
    PhysicObject* torPhysicObjectLeft;
    PhysicObject* torPhysicObjectRight;
    Transformation* torTransformation;
    Transformation* torCollisionMeshTransformationBack;
    Transformation* torCollisionMeshTransformationLeft;
    Transformation* torCollisionMeshTransformationRight;

public:
    FussballStadionScene();

    void Initialize();

    Node * GetRootNode();

    void ShootLeft();
    void ShootRight();

    void ResetScene();
};

#endif // FUSSBALLSTADIONSCENE_H
