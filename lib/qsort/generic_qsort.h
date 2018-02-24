#pragma once
#include <stdlib.h>
#include <string.h>

#ifndef _STACK_MACRO_
#define _STACK_MACRO_

#define STACKSIZE 64

#define PREPARE_STACK                                                          \
        char *stack[STACKSIZE];                                                \
        char **stackptr = stack

#define PUSH(array, limit)                                                     \
        stackptr[0] = array;                                                   \
        stackptr[1] = limit;                                                   \
        stackptr += 2

#define POP(array, limit)                                                      \
        stackptr -= 2;                                                         \
        array = stackptr[0];                                                   \
        limit = stackptr[1]
#endif

#define THRESH 7

#define INIT_QSORT(T)                                                          \
        static inline void memswp_##T(char *i, char *j)                        \
        {                                                                      \
                T tmp;                                                         \
                                                                               \
                memcpy(&tmp, i, sizeof(T));                                    \
                memcpy(i, j, sizeof(T));                                       \
                memcpy(j, &tmp, sizeof(T));                                    \
        }                                                                      \
                                                                               \
        void qsort_##T(void *array, size_t array_size,                         \
                       int (*comp)(const void *, const void *))                \
        {                                                                      \
                char *i, *j;                                                   \
                size_t thresh = THRESH * sizeof(T);                            \
                char *array_ = (char *)array;                                  \
                char *limit = array_ + array_size * sizeof(T);                 \
                PREPARE_STACK;                                                 \
                                                                               \
                while(1)                                                       \
                {                                                              \
                        if((size_t)(limit - array_) > thresh)                  \
                        {                                                      \
                                i = array_ + sizeof(T);                        \
                                j = limit - sizeof(T);                         \
                                memswp_##T(((((size_t)(limit - array_)) /      \
                                             sizeof(T)) /                      \
                                            2) * sizeof(T) +                   \
                                               array_,                         \
                                           array_);                            \
                                if(comp(i, j) > 0)                             \
                                {                                              \
                                        memswp_##T(i, j);                      \
                                }                                              \
                                if(comp(array_, j) > 0)                        \
                                {                                              \
                                        memswp_##T(array_, j);                 \
                                }                                              \
                                if(comp(i, array_) > 0)                        \
                                {                                              \
                                        memswp_##T(i, array_);                 \
                                }                                              \
                                while(1)                                       \
                                {                                              \
                                        do                                     \
                                        {                                      \
                                                i += sizeof(T);                \
                                        } while(comp(array_, i) > 0);          \
                                        do                                     \
                                        {                                      \
                                                j -= sizeof(T);                \
                                        } while(comp(j, array_) > 0);          \
                                        if(i > j)                              \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        memswp_##T(i, j);                      \
                                }                                              \
                                memswp_##T(array_, j);                         \
                                if(j - array_ > limit - i)                     \
                                {                                              \
                                        PUSH(array_, j);                       \
                                        array_ = i;                            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        PUSH(i, limit);                        \
                                        limit = j;                             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(j = array_, i = j + sizeof(T); i < limit;  \
                                    j = i, i += sizeof(T))                     \
                                {                                              \
                                        for(; comp(j, j + sizeof(T)) > 0;      \
                                            j -= sizeof(T))                    \
                                        {                                      \
                                                memswp_##T(j, j + sizeof(T));  \
                                                if(j == array_)                \
                                                {                              \
                                                        break;                 \
                                                }                              \
                                        }                                      \
                                }                                              \
                                if(stackptr != stack)                          \
                                {                                              \
                                        POP(array_, limit);                    \
                                }                                              \
                                else                                           \
                                {                                              \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
        }\
\

