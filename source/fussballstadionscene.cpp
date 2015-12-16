#include "fussballstadionscene.h"

FussballStadionScene::FussballStadionScene()
{
    this->initialized = false;

    this->fussballFeld = NULL;
    this->fussballFeldCollisionMesh = NULL;
    this->fussballFeldCollisionMeshTransformation = NULL;
    this->fussballFeldPhysicObject = NULL;

    this->fussball = NULL;
    this->fussballTransformation = NULL;
    this->fussballPhysicObject = NULL;

    this->tor = NULL;
    this->torTransformation = NULL;
    this->torPhysicObjectBack = NULL;

    this->physicEngineSlot = -1;
    this->physicEngine = NULL;
    this->root = NULL;
}

Node* FussballStadionScene::GetRootNode()
{
    return this->root;
}

void FussballStadionScene::DoStuff()
{
    //this->fussballPhysicObject->setAngularVelocity(QVector3D(-20, 0 ,0));
    this->fussballPhysicObject->setLinearVelocity(QVector3D(0, 0, -10));
}

void FussballStadionScene::Initialize()
{
    QString path(SRCDIR);
    this->root = new Node();

    Texture* texture = NULL;
    //Physic Engine Erzeugen und einen Pointer auf Instanz holen
    this->physicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    this->physicEngine = PhysicEngineManager::getPhysicEngineBySlot(this->physicEngineSlot);

    // ------------------------------------- tor --------------------------------------

    this->tor = new Drawable(new TriangleMesh(QString("./../models/fussballtor.obj")));
    this->tor->setTransparent(true);
    texture = tor->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/tortexture.png"));

    this->torTransformation = new Transformation();
    this->torTransformation->Translate(0, -.01, -43.7);

    this->torCollisionPlaneBack = new Drawable(new SimplePlane(6, 4));
    this->torCollisionPlaneBack->I_setStaticGeometry(true);

    this->torCollisionPlaneLeft = new Drawable(new SimplePlane(2.3, 4));
    this->torCollisionPlaneLeft->I_setStaticGeometry(true);

    this->torCollisionPlaneRight = new Drawable(new SimplePlane(2.3, 4));
    this->torCollisionPlaneRight->I_setStaticGeometry(true);

    this->torCollisionMeshTransformationBack = new Transformation();
    this->torCollisionMeshTransformationBack->Translate(0, 0, -.9);
    this->torCollisionMeshTransformationBack->AddChild(this->torCollisionPlaneBack);

    this->torCollisionMeshTransformationLeft = new Transformation();
    this->torCollisionMeshTransformationLeft->Translate(-3.1, 0, 0);
    this->torCollisionMeshTransformationLeft->Rotate(90.0f, 0.0f, 1.0f, 0.0f);
    this->torCollisionMeshTransformationLeft->AddChild(this->torCollisionPlaneLeft);

    this->torCollisionMeshTransformationRight = new Transformation();
    this->torCollisionMeshTransformationRight->Translate(3.1, 0, 0);
    this->torCollisionMeshTransformationRight->Rotate(90.0f, 0.0f, 1.0f, 0.0f);
    this->torCollisionMeshTransformationRight->AddChild(this->torCollisionPlaneRight);

    this->torTransformation->AddChild(this->torCollisionMeshTransformationBack);
    this->torTransformation->AddChild(this->torCollisionMeshTransformationLeft);
    this->torTransformation->AddChild(this->torCollisionMeshTransformationRight);

    this->torPhysicObjectBack = physicEngine->createNewPhysicObject(this->torCollisionPlaneBack);
    this->torPhysicObjectLeft = physicEngine->createNewPhysicObject(this->torCollisionPlaneLeft);
    this->torPhysicObjectRight = physicEngine->createNewPhysicObject(this->torCollisionPlaneRight);

    PhysicObjectConstructionInfo* torConstructionInfoBack = new PhysicObjectConstructionInfo();
    torConstructionInfoBack->setCollisionHull(CollisionHull::BoxAABB); //Automatische generierung einer Box aus den Vertexpunkten
    torConstructionInfoBack->setRestitution(.8);

    PhysicObjectConstructionInfo* torConstructionInfoLeft = new PhysicObjectConstructionInfo();
    torConstructionInfoLeft->setCollisionHull(CollisionHull::BoxAABB); //Automatische generierung einer Box aus den Vertexpunkten
    torConstructionInfoLeft->setRestitution(.8);

    PhysicObjectConstructionInfo* torConstructionInfoRight = new PhysicObjectConstructionInfo();
    torConstructionInfoRight->setCollisionHull(CollisionHull::BoxAABB); //Automatische generierung einer Box aus den Vertexpunkten
    torConstructionInfoRight->setRestitution(.8);

    this->torPhysicObjectBack->setConstructionInfo(torConstructionInfoBack);
    this->torPhysicObjectBack->registerPhysicObject();

    this->torPhysicObjectLeft->setConstructionInfo(torConstructionInfoLeft);
    this->torPhysicObjectLeft->registerPhysicObject();

    this->torPhysicObjectRight->setConstructionInfo(torConstructionInfoRight);
    this->torPhysicObjectRight->registerPhysicObject();


    // ------------------------------------- fussball --------------------------------------

    this->fussball = new Drawable(new TriangleMesh(QString("./../models/fussball.obj")));
    //this->fussball = new Drawable(new SimpleSphere(.5f));
    texture = this->fussball->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/fussballtexture.png"));

    this->fussballTransformation = new Transformation();
    this->fussballTransformation->Translate(0, 8, -31.3);

    this->fussballPhysicObject = physicEngine->createNewPhysicObject(fussball);

    //Ein PhysicObjectConstructionInfo Objekt erzeugen, welches die Eigenschaften eines PhysicObjects festlegt,
    //für jede Eigenschaft gibt es einen Standardwert, das Objekt wird später automatisch gelöscht
    PhysicObjectConstructionInfo* physicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    //Optionale veränderung der Informationen
    physicObjectConstructionInfo->setCollisionHull(CollisionHull::SphereRadius);   //Form des Hüllkörpers festlegen
    physicObjectConstructionInfo->setSphereRadius(.2f);                            //Radius der Sphere auf 0.5 setzen
    physicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f,0.f,0.f));    //Schwerpunkt des Objektes angeben, Standardwert (0,0,0)
    physicObjectConstructionInfo->setMass(2.f);                                    //Gewicht des Körpers bestimmen, sollte nicht zu groß gewählt werden
    physicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1)); //Mittelpunkttransformation angeben falls Geometrie in seinem Koordinatensystem verschoben liegt
    physicObjectConstructionInfo->setRestitution(.1f);                            //Elastizität des Körpers bestimmen, von 0 bis 1 definiert
    physicObjectConstructionInfo->setRollingFriction(0.2f);                        //Rollwiderstand vorallem bei Kugeln angeben


    this->fussballPhysicObject->setConstructionInfo(physicObjectConstructionInfo); //Dem PhysicObject die Konstruktionsinforaionen geben
    this->fussballPhysicObject->registerPhysicObject();                            //Das PhysicObject in seiner Engine Registrieren, damit die Simulation starten kann

    // ------------------------------------- fussball feld --------------------------------------

    this->fussballFeld = new Drawable(new TriangleMesh(QString("./../models/fussballfeld.obj")));
    this->fussballFeldCollisionMesh = new Drawable(new SimplePlane(200.0f));

    texture = this->fussballFeld->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/fussballfeldtexture.jpg"));

    this->fussballFeldCollisionMesh->I_setStaticGeometry(true);
    this->fussballFeldCollisionMeshTransformation = new Transformation();
    this->fussballFeldCollisionMeshTransformation->Translate(0.0, -0.01, 0.0);
    this->fussballFeldCollisionMeshTransformation->Rotate(-90.f,1.f,0.f,0.f);

    this->fussballFeldPhysicObject = physicEngine->createNewPhysicObject(this->fussballFeldCollisionMesh);

    PhysicObjectConstructionInfo* fussballFeldConstructionInfo = new PhysicObjectConstructionInfo();
    fussballFeldConstructionInfo->setCollisionHull(CollisionHull::BoxAABB); //Automatische generierung einer Box aus den Vertexpunkten


    this->fussballFeldPhysicObject->setConstructionInfo(fussballFeldConstructionInfo);
    this->fussballFeldPhysicObject->registerPhysicObject();

    Shader* s = new Shader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    this->tor->setShader(s);
    this->fussball->setShader(s);
    this->fussballFeld->setShader(s);

    this->torTransformation->AddChild(this->tor);
    this->fussballTransformation->AddChild(this->fussball);
    this->fussballFeldCollisionMeshTransformation->AddChild(this->fussballFeldCollisionMesh);

    this->root->AddChild(this->torTransformation);
    this->root->AddChild(this->fussballFeld);
    this->root->AddChild(this->fussballFeldCollisionMeshTransformation);
    this->root->AddChild(this->fussballTransformation);
}

