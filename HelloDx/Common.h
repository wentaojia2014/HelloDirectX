#pragma once
#include <Windows.h>
#include <string>

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
        throw std::system_error
        {
            hr, std::system_category(), std::forward<T>(msg)
        };
	}
}
