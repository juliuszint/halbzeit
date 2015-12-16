#include "halbzeitgame.h"


HalbzeitGame::HalbzeitGame()
{

}

void HalbzeitGame::Initialize()
{
    this->camera = new ControllableCamera();
    this->sceneManager = SceneManager::instance();
    this->renderingContenxt = new RenderingContext(this->camera);
    this->renderingContextHandle = this->sceneManager->addContext(this->renderingContenxt);

    this->scene = new FussballStadionScene();
    this->scene->Initialize();

    this->inputProcessor = new Inputprocessor(this->scene);

    Node* composite = new Node();
    composite->AddChild(this->scene->GetRootNode());
    composite->AddChild(this->inputProcessor);
    this->sceneHandle = this->sceneManager->addScene(composite);
    this->screenRenderer = new ScreenRenderer(this->renderingContextHandle, this->sceneHandle);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(this->sceneHandle);
    SceneManager::instance()->setActiveContext(this->renderingContextHandle);
    //SceneManager::instance()->setFullScreen();
}

void SceneManager::initScenes()
{
    HalbzeitGame* game = new HalbzeitGame();
    game->Initialize();
}

