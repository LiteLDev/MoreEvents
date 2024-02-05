#pragma once

#ifdef MORE_EVENTS_EXPORTS

#define MORE_EVENTS_API __declspec(dllexport)

#else

#define MORE_EVENTS_API __declspec(dllimport)

#endif
