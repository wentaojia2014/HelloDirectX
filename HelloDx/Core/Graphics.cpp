#include "Graphics.h"

Graphics::Graphics () {}


Graphics::~Graphics () {}

Graphics::Graphics (const Graphics &) {}

Graphics::Graphics (Graphics &&) {}

bool Graphics::Initialize (int screenWidth, int screenHeight, HWND hwnd) {
    return true;
}

void Graphics::Shutdown () {}

bool Graphics::Frame () {
    return true;
}

bool Graphics::Render () {
    return true;
}
