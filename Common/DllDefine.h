#pragma once

#ifdef CHDLL_EXPORTS
#define CE_CONTROL_API __declspec(dllexport)
#else
#define CE_CONTROL_API __declspec(dllimport)
#endif