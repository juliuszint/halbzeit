#include "OpenGL.h"
#include "window.h"
#include "screenrenderer.h"
#include "scenemanager.h"
#include "transformation.h"
#include "KeyboardTransformation.h"
#include "animatedtransformation.h"
#include "interpolatedrotation.h"
#include "controllablecamera.h"
#include "color.h"
#include "trianglemesh.h"
#include "texture.h"
#include "simplecube.h"
#include "ui_dockwidget.h"
#include "fussballstadionscene.h"

Node* initHalbzeitScene();

void SceneManager::initScenes()
{
    ControllableCamera *cam = new ControllableCamera();
    RenderingContext *myContext=new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);

    FussballStadionScene* fussballStadion = new FussballStadionScene();
    fussballStadion->Initialize();

    unsigned int myScene = SceneManager::instance()->addScene(fussballStadion->GetRootNode());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);

    Q_UNUSED(myRenderer)

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();
}

