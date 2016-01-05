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

void FussballStadionScene::ShootLeft()
{
    //this->fussballPhysicObject->setAngularVelocity(QVector3D(-20, 0 ,0));
    this->fussballPhysicObject->setLinearVelocity(QVector3D(-3.2, 0, -10));
}
void FussballStadionScene::ShootRight()
{
    //this->fussballPhysicObject->setAngularVelocity(QVector3D(-20, 0 ,0));
    this->fussballPhysicObject->setLinearVelocity(QVector3D(3.2, 0, -10));
}

void PrintMatrix(QMatrix4x4 m)
{
    for(int row = 0; row < 4; row ++)
    {
        QVector4D v = m.row(row);
        qDebug("%f, %f, %f, %f", v.x(), v.y(), v.z(), v.w());
    }
}

void FussballStadionScene::ResetScene()
{
    this->fussballPhysicObject->setLinearVelocity(QVector3D(0, 0, 0));
    this->fussballPhysicObject->setAngularVelocity(QVector3D(0, 0, 0));

    QMatrix4x4 m = this->fussballPhysicObject->getEngineModelMatrix();

    qDebug("before manipulation");
    PrintMatrix(m);

    m.data()[12] = this->fussballRootPosition.x();
    m.data()[13] = this->fussballRootPosition.y();
    m.data()[14] = this->fussballRootPosition.z();

    qDebug("after manipulation");
    PrintMatrix(m);
    this->fussballPhysicObject->setEngineModelMatrix(m);

    qDebug( "Resettings Scene" );
}


void FussballStadionScene::Initialize()
{
    QString path(SRCDIR);
    this->root = new Node();

    Texture* texture = NULL;
    Color* color = NULL;
    Material* material = NULL;
    //Physic Engine Erzeugen und einen Pointer auf Instanz holen
    this->physicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    this->physicEngine = PhysicEngineManager::getPhysicEngineBySlot(this->physicEngineSlot);

    // ------------------------------------- tor --------------------------------------

    this->tor = new Drawable(new TriangleMesh(QString("./../models/fussballtor.obj")));
    this->tor->setTransparent(true);
    texture = tor->GetProperty<Texture>();
    texture->LoadPicture(QString("./../textures/tortexture.png"));

    this->torstangen = new Drawable(new TriangleMesh(QString("./../models/torstangen.obj")));
    this->torStangenTransformation = new Transformation();
    this->torStangenTransformation->AddChild(this->torstangen);
    this->torStangenTransformation->Translate(0, -.01, -43.0);

    color = this->torstangen->GetProperty<Color>();
    color->SetValue(0.9, 0.9, 0.9, 1.0);

    this->torTransformation = new Transformation();
    this->torTransformation->Translate(0, -.01, -43.7);

    this->torCollisionPlaneBack = new Drawable(new SimplePlane(6, 4));
    this->torCollisionPlaneBack->I_setStaticGeometry(true);
    this->torCollisionPlaneBack->setTransparent(true);
    color = this->torCollisionPlaneBack->GetProperty<Color>();
    color->SetValue(1.0, 1.0, 1.0, 0.0);

    this->torCollisionPlaneLeft = new Drawable(new SimplePlane(2.3, 4));
    this->torCollisionPlaneLeft->I_setStaticGeometry(true);
    this->torCollisionPlaneLeft->setTransparent(true);
    color = this->torCollisionPlaneLeft->GetProperty<Color>();
    color->SetValue(1.0, 1.0, 1.0, 0.0);

    this->torCollisionPlaneRight = new Drawable(new SimplePlane(2.3, 4));
    this->torCollisionPlaneRight->I_setStaticGeometry(true);
    this->torCollisionPlaneRight->setTransparent(true);
    color = this->torCollisionPlaneRight->GetProperty<Color>();
    color->SetValue(1.0, 1.0, 1.0, 0.0);

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
    this->fussballRootPosition.setX(0);
    this->fussballRootPosition.setY(4);
    this->fussballRootPosition.setZ(-31.3);
    this->fussballTransformation->Translate(this->fussballRootPosition.x(), this->fussballRootPosition.y(), this->fussballRootPosition.z());

    this->fussballPhysicObject = physicEngine->createNewPhysicObject(fussball);
    this->fussballPhysicObject->setAlwaysActive(false);

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
    this->fussballFeldCollisionMesh->setTransparent(true);

    color = fussballFeldCollisionMesh->GetProperty<Color>();
    color->SetValue(1.0, 1.0, 1.0, 0.0);

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

    Shader* textureShader = new Shader(QString("://shader/texture.vert"), QString("://shader/texture.frag"));
    this->tor->setShader(textureShader);
    this->fussball->setShader(textureShader);
    this->fussballFeld->setShader(textureShader);

    this->torTransformation->AddChild(this->tor);
    this->fussballTransformation->AddChild(this->fussball);
    this->fussballFeldCollisionMeshTransformation->AddChild(this->fussballFeldCollisionMesh);

    // ------------------------------------- bühne --------------------------------------

    this->flutlicht = new Light();
    this->flutlicht->setPosition(0.0, 30.0, -18.0, 1.0);
    this->flutlicht->setSpotDirection(0.0, 0.0, -1.0);
    this->flutlicht->setCutOffAngle(180.0);
    this->flutlicht->setDiffuse(0.7, 0.7, 0.7, 1.0);
    this->flutlicht->setSpecular(0.6, 0.6, 0.6, 1.0);
    this->flutlicht->setAmbient(0.6, 0.6, 0.6, 1.0);
    this->flutlicht->turnOn();

    Shader * phong = new Shader(QString("://shader/PhongVL.vert"), QString("://shader/PassThrough.frag"));
    this->buehneBeton = new Drawable(new TriangleMesh(QString("./../models/RestBuhne.obj")));
    this->buehneBetonTransformation = new Transformation();
    this->buehneBetonTransformation->AddChild(this->buehneBeton);
    this->buehneBetonTransformation->Translate(5.0, .5, -24.0);
    this->buehneBeton->setShader(phong);

    material = this->buehneBeton->GetProperty<Material>();
    material->setDiffuse(0.25, .25, .25, 1.);
    material->setAmbient(0.8, .8, .8, 1.);
    material->setSpecular(0.5, .5, .5, 1.);
    material->setShininess(.7);

    this->buehneHolzsitze = new Drawable(new TriangleMesh(QString("./../models/HolzSitze.obj")));
    this->buehneHolzsitze->setShader(phong);

    material = this->buehneHolzsitze->GetProperty<Material>();
    material->setDiffuse(.0, .4, .1, 1.);
    material->setAmbient(.0, .4, .1, 1.);
    material->setSpecular(.5, .5, .5, 1.);
    material->setShininess(.7);

    this->buehneHolzTransformation = new Transformation();
    this->buehneHolzTransformation->AddChild(this->buehneHolzsitze);
    this->buehneHolzTransformation->Translate(5.0, 0.5, -24.0);

    color = this->buehneHolzsitze->GetProperty<Color>();
    color->SetValue(.8, .4, .1, 1.0);

    // ------------------------------------- advertising --------------------------------------

    QString addTextures[10];
    addTextures[0] = QString("./../textures/adderhmann.jpg");
    addTextures[1] = QString("./../textures/adderhmann.jpg");
    addTextures[2] = QString("./../textures/addmcdonalds.jpg");
    addTextures[3] = QString("./../textures/addmcdonalds.jpg");
    addTextures[4] = QString("./../textures/addpost.jpg");
    addTextures[5] = QString("./../textures/addpost.jpg");
    addTextures[6] = QString("./../textures/addadidas.jpg");
    addTextures[7] = QString("./../textures/addadidas.jpg");
    addTextures[8] = QString("./../textures/addrothaus.jpg");
    addTextures[9] = QString("./../textures/addrothaus.jpg");

    for(int i = 0; i < 10; i++)
    {
	    this->advertising[i] = new Drawable(new SimplePlane(5, 1.0));
	    this->advertising[i]->setShader(textureShader);
	    this->advertisingTransformations[i] = new Transformation();
            this->advertisingTransformations[i]->Translate(-20.0 + (i * 5.2), .5, -47);
	    this->advertisingTransformations[i]->AddChild(this->advertising[i]); 

	    texture = this->advertising[i]->GetProperty<Texture>();
	    texture->LoadPicture(addTextures[i]);

	    this->root->AddChild(this->advertisingTransformations[i]);
    }

    // ------------------------------------- skybox --------------------------------------

    Shader *sCube = new Shader("://shader/skybox.vert", "://shader/texturecube.frag");
    Texture *te = new Texture(path + QString("/../textures/cubemap_miramar"));
    this->skybox = new Drawable(new SimpleCube(100));
    this->skybox->SetProperty<Texture>(te);
    this->skybox->setShader(sCube);

    this->root->AddChild(this->skybox);

    this->root->AddChild(this->buehneBetonTransformation);
    this->root->AddChild(this->buehneHolzTransformation);

    this->root->AddChild(this->torStangenTransformation);
    this->root->AddChild(this->torTransformation);
    this->root->AddChild(this->fussballFeld);
    this->root->AddChild(this->fussballFeldCollisionMeshTransformation);
    this->root->AddChild(this->fussballTransformation);
    this->flutlicht->AddChild(this->root);
    this->root = this->flutlicht;
}

