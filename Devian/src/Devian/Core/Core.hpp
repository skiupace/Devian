#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define DEVIAN_ASSERT(cond) if (cond){} else { std::cerr << "Assertion Failed!" << std::flush; __debugbreak; }

#elif DEVIAN_RELEASE
	#define DEVIAN_ASSERT

#else
	#error This Engine is Currently Supports Windows Platform Only!
#endif