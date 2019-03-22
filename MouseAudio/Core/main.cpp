#include "../Base/Application.h"
#include "../Base/MainWindow.h"
#include"TriangleRender.h"
using namespace Tao3D;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR /*cmdParamarg*/, int /* cmdShow */)
{
    Application app;
    TriangleRender render;
    MainWindow window(&render);
    app.setWindow(&window);
    app.init(1024, 768, "MouseAudio");
    
    window.show();
    app.exec();
    return 0;
}