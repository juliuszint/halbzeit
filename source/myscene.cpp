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
    QString path(SRCDIR);
    Node* sceneRoot = new Node();

    Drawable* centerScene = new Drawable(new SimpleCube(.5,.5,.5));
    Color* color = centerScene->GetProperty<Color>();
    color->SetValue(1, 0, 0, 1);


    Drawable* tor = new Drawable(new TriangleMesh(QString("./../models/fussballtor.obj")));
    Texture* c = tor->GetProperty<Texture>();
    c->LoadPicture(QString("./../textures/tortexture.png"));

    Transformation* torPosition = new Transformation();
    torPosition->Translate(0, -.01, -43.7);

    Drawable* fussball = new Drawable(new TriangleMesh(QString("./../models/fussball.obj")));
    c = fussball->GetProperty<Texture>();
    c->LoadPicture(QString("./../textures/fussballtexture.png"));

    Transformation* fussballPosition = new Transformation();
    fussballPosition->Translate(0, .2, -31.3);

    Drawable* fussballfeld = new Drawable(new TriangleMesh(QString("./../models/fussballfeld.obj")));
    c = fussballfeld->GetProperty<Texture>();
    c->LoadPicture(QString("./../textures/fussballfeldtexture.jpg"));

    Shader* s = new Shader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    tor->setShader(s);
    fussball->setShader(s);
    fussballfeld->setShader(s);

    torPosition->AddChild(tor);
    fussballPosition->AddChild(fussball);

    sceneRoot->AddChild(fussballfeld);
    sceneRoot->AddChild(torPosition);
    sceneRoot->AddChild(fussballPosition);

    //sceneRoot->AddChild(centerScene);
    return sceneRoot;
}
