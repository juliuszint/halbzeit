#ifndef HALBZEITGAME_H
#define HALBZEITGAME_H

#include "node.h"
#include "fussballstadionscene.h"
#include "controllablecamera.h"
#include "renderingcontext.h"
#include "scenemanager.h"
#include "screenrenderer.h"
#include "inputprocessor.h"

class HalbzeitGame
{
private:
    Inputprocessor* inputProcessor;
    FussballStadionScene * scene;
    unsigned int sceneHandle;

    ControllableCamera * camera;
    SceneManager* sceneManager;

    ScreenRenderer* screenRenderer;
    RenderingContext* renderingContenxt;
    unsigned int renderingContextHandle;
public:
    HalbzeitGame();

    void Initialize();
};

#endif // HALBZEITGAME_H
