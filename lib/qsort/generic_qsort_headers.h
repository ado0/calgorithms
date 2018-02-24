#pragma once
#include "generic_types.h"

#define INIT_QSORT_HEADERS(T) void qsort_##T(void*, size_t, int(*comp)\
		(const void*, const void*)
