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

#include "ui_dockwidget.h"

Node* initHalbzeitScene();

void SceneManager::initScenes()
{
    //Ui_FPSWidget *lDock;
    //QDockWidget *lDockWidget = new QDockWidget(QString("FPS"), SceneManager::getMainWindow());

    ControllableCamera *cam = new ControllableCamera();
    RenderingContext *myContext=new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initHalbzeitScene());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer)

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
//    SceneManager::instance()->setFullScreen();

    // Hab mir angeschaut wie man evtl die doofen ränder wegbekommt. Das ui Element was hier
    // ist das Widget was angezeit wird im MainWindow. Definiert wird das ganze in der Datei
    // glwithwidgets.ui im FrameworkSource und evtl kann es über die variable noch ein bisschen
    // konfiguriert werden ohne das man den kompletten Szenegraphen rekompiliert
    Ui::GLwithWidgets* ui = MainWindow::getUi();
    Q_UNUSED(ui)

//    lDock = new Ui_FPSWidget();
//    lDock->setupUi(lDockWidget);
//    lDockWidget->resize(200,100);
//    SceneManager::getMainWindow()->addDockWidget(Qt::RightDockWidgetArea, lDockWidget);
//    lDockWidget->show();
//    QObject::connect(Window::getInstance(), SIGNAL(sigFPS(int)), lDock->lcdNumber, SLOT(display(int)));
}

Node *initHalbzeitScene()
{
    Node* sonnensystem = new Node();

    return sonnensystem;
}
