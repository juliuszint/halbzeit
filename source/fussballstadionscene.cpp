#include "fussballstadionscene.h"

FussballStadionScene::FussballStadionScene()
{
    this->initialized = false;

    this->fussballFeld = NULL;
    this->fussballFeldTransformation = NULL;
    this->fussballFeldPhysicObject = NULL;

    this->fussball = NULL;
    this->fussballTransformation = NULL;
    this->fussballPhysicObject = NULL;

    this->tor = NULL;
    this->torTransformation = NULL;
    this->torPhysicObject = NULL;

    this->physicEngineSlot = -1;
    this->physicEngine = NULL;
    this->root = NULL;
}

Node* FussballStadionScene::GetRootNode()
{
    return this->root;
}

void FussballStadionScene::Initialize()
{
    QString path(SRCDIR);
    this->root = new Node();

    Texture* texture = NULL;
    //Physic Engine Erzeugen und einen Pointer auf Instanz holen
    this->physicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    this->physicEngine = PhysicEngineManager::getPhysicEngineBySlot(this->physicEngineSlot);

    this->tor = new Drawable(new TriangleMesh(QString("./../models/fussballtor.obj")));
    this->tor->setTransparent(true);
    texture = tor->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/tortexture.png"));

    this->torTransformation = new Transformation();
    this->torTransformation->Translate(0, -.01, -43.7);

    // ------------------------------------- fussball --------------------------------------

    this->fussball = new Drawable(new TriangleMesh(QString("./../models/fussball.obj")));
    texture = this->fussball->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/fussballtexture.png"));

    this->fussballTransformation = new Transformation();
    this->fussballTransformation->Translate(0, 2, -31.3);

    this->fussballPhysicObject = physicEngine->createNewPhysicObject(fussball);

    //Ein PhysicObjectConstructionInfo Objekt erzeugen, welches die Eigenschaften eines PhysicObjects festlegt,
    //für jede Eigenschaft gibt es einen Standardwert, das Objekt wird später automatisch gelöscht
    PhysicObjectConstructionInfo* physicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    //Optionale veränderung der Informationen
    physicObjectConstructionInfo->setBoxHalfExtends(QVector3D(0.5f,0.5f,0.5f));    //Ausdehnung des Würfels in halber länge angeben
    physicObjectConstructionInfo->setCcdActivation(true);                          //durchdringen durch andere Objekte Abfangen, benötigt mehr Rechenzeit
    physicObjectConstructionInfo->setCollisionHull(CollisionHull::SphereRadius);   //Form des Hüllkörpers festlegen
    physicObjectConstructionInfo->setFriction(0.5f);                               //Reibung zwischen 0 und 1 angeben, 0 keine reibung 1 maximal
    physicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f,0.f,0.f));    //Schwerpunkt des Objektes angeben, Standardwert (0,0,0)
    physicObjectConstructionInfo->setMass(2.f);                                    //Gewicht des Körpers bestimmen, sollte nicht zu groß gewählt werden
    physicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1)); //Mittelpunkttransformation angeben falls Geometrie in seinem Koordinatensystem verschoben liegt
    physicObjectConstructionInfo->setRestitution(0.1f);                            //Elastizität des Körpers bestimmen, von 0 bis 1 definiert
    physicObjectConstructionInfo->setRollingFriction(0.2f);                        //Rollwiderstand vorallem bei Kugeln angeben


    this->fussballPhysicObject->setConstructionInfo(physicObjectConstructionInfo); //Dem PhysicObject die Konstruktionsinforaionen geben
    this->fussballPhysicObject->registerPhysicObject();                            //Das PhysicObject in seiner Engine Registrieren, damit die Simulation starten kann

    // ------------------------------------- fussball feld --------------------------------------

    this->fussballFeld = new Drawable(new TriangleMesh(QString("./../models/fussballfeld.obj")));
    texture = this->fussballFeld->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/fussballfeldtexture.jpg"));
    this->fussballFeld->I_setStaticGeometry(true);
    this->fussballFeldTransformation = new Transformation();

    this->fussballFeldPhysicObject = physicEngine->createNewPhysicObject(this->fussballFeld);

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
    this->fussballFeldTransformation->AddChild(this->fussballFeld);

    this->root->AddChild(this->torTransformation);
    this->root->AddChild(this->fussballFeldTransformation);
    this->root->AddChild(this->fussballTransformation);
}

