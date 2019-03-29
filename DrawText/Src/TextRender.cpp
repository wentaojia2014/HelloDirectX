#include "TextRender.h"

#include "Application.h"
using namespace DirectX;
namespace Tao3D
{
TextRender::TextRender() {}
TextRender::~TextRender() {}
void TextRender::init(int width, int height)
{
    m_font = std::make_unique<SpriteFont>(gDevice, L"TaoFont.spritefont");
    m_spriteBatch = std::make_unique<SpriteBatch>(gContext);
    m_fontPos.x = width / 2.f;
    m_fontPos.y = height / 2.f;
}
void TextRender::update() 
{
    auto mouse = gMouse.GetState();
    m_mousePos = { (float)mouse.x, (float)mouse.y };
}
bool TextRender::render()
{
    m_spriteBatch->Begin();
    auto out = L"Hello World";
    std::wstring mouseX = L"Mouse X:" + std::to_wstring(static_cast<int>(m_mousePos.x));
    std::wstring mouseY = L"Mouse Y:" + std::to_wstring(static_cast<int>(m_mousePos.y));
    Vector2 origin = m_font->MeasureString(out) / 2.f;
    m_font->DrawString(m_spriteBatch.get(), out, m_fontPos, Colors::AntiqueWhite, 0.f, origin);
    origin = m_font->MeasureString(mouseX.data()) / 2.f;
    m_font->DrawString(m_spriteBatch.get(), mouseX.data(), { 150, 50 }, Colors::Azure, 0.f, origin);
    origin = m_font->MeasureString(mouseY.data()) / 2.f;
    m_font->DrawString(m_spriteBatch.get(), mouseY.data(), { 150, 100 }, Colors::Azure, 0.f, origin);
    m_spriteBatch->End();
    return true;
}
} // namespace Tao3D
