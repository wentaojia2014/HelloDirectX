#include "Application.h"
#include "MainWindow.h"
#include "GridRender.h"
using namespace Tao3D;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR /*cmdParamarg*/, int /* cmdShow */)
{
    Application app;
    GridRender render;
    MainWindow window;
    app.setWindow(&window);
    app.setRender(&render);
    app.init(1024, 768, "Grid");

    window.show();
    app.exec();
    return 0;
}
