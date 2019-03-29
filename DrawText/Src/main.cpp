#include "Application.h"
#include "MainWindow.h"
#include "TextRender.h"
using namespace Tao3D;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR /*cmdParamarg*/, int /* cmdShow */)
{
    Application app;
    TextRender render;
    MainWindow window;
    app.setWindow(&window);
    app.setRender(&render);
    app.init(1024, 768, "TextRender");

    window.show();
    app.exec();
    return 0;
}
