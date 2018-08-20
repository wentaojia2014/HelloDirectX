#pragma once

#ifdef unix
#define TAO_EXPORT __attribute__((visibility("default")))
#define TAO_IMPORT __attribute__((visibility("default")))
#define TAO_HIDDEN __attribute__((visibility("hidden")))
#else
#define TAO_EXPORT __declspec(dllexport)
#define TAO_IMPORT __declspec(dllimport)
#endif

#ifdef TAOMATHLIBRARY
#define TAOEXPORT TAO_EXPORT
#else
#define TAOEXPORT TAO_IMPORT
#endif

