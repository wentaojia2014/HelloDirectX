#pragma once
#include <Windows.h>
#include <string>
namespace TaoD3D
{

static std::string GetLastErrorAsString()
{
    // Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return std::string("errorMessageID is 0"); // No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = ::FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)(&messageBuffer),
        0,
        nullptr);
    std::string message(messageBuffer, size);

    // Free the buffer.
    ::LocalFree(messageBuffer);

    return message;
}

template <typename T>
void ThrowIfFailed(HRESULT hr, T &&msg)
{
    if (FAILED(hr))
    {
        OutputDebugStringA(GetLastErrorAsString().data());
        throw std::system_error{ hr, std::system_category(), std::forward<T>(msg) };
    }
}

template <typename T>
void SafeShutdown(T *p)
{
    if (p)
    {
        p->Shutdown();
        delete p;
        p = nullptr;
    }
}
template <typename T>
void SafeRelease(T *p)
{
    if (p)
    {
        p->Release();
        p = nullptr;
    }
}
template <typename T>
void SafeDelete(T *p)
{
    if (p)
    {
        delete p;
        p = nullptr;
    }
}
template <typename T>
void SafeDeleteArray(T *p)
{
    if (p)
    {
        delete [] p;
        p = nullptr;
    }
}
} // namespace TaoD3D
