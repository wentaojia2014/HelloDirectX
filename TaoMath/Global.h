#pragma once

#ifdef unix
#define TAO_EXPORT     __attribute__((visibility("default")))
#define TAO_IMPORT     __attribute__((visibility("default")))
#define TAO_HIDDEN     __attribute__((visibility("hidden")))
#else
#define TAO_EXPORT __declspec(dllexport)
#define TAO_IMPORT __declspec(dllimport)
#endif

#ifdef TAOMATHLIBRARY
#define TAOMATH_EXPORT TAO_EXPORT
#else
#define TAOMATH_EXPORT TAO_IMPORT
#endif