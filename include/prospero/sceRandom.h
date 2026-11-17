#ifndef PROSPERO_SCE_RANDOM_H
#define PROSPERO_SCE_RANDOM_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

int sceRandomGetRandomNumber(void* buf, size_t sz);

#ifdef __cplusplus
}
#endif

#endif