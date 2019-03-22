#include "../Base/Application.h"
#include "../Base/MainWindow.h"

using namespace Tao3D;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR /*cmdParamarg*/, int /* cmdShow */)
{
    Application app;
    MainWindow window;
    window.init(1024, 768, "MouseAudio");
    app.setWindow(&window);
    window.show();
    app.exec();
    return 0;
}