#ifndef PROSPERO_SCE_KERNEL_H
#define PROSPERO_SCE_KERNEL_H

#include <stdint.h>

typedef struct sceKernelNotifyRequest {
  char useless1[45];
  char message[3075];
} sceKernelNotifyRequest_t;

#ifdef __cplusplus
extern "C" {
#endif

int sceKernelAllocateDirectMemory(int64_t search_start, int64_t search_end, size_t len, size_t alignment, int memory_type, int64_t* phys_addr_out);
int sceKernelMapDirectMemory(void** addr, uint64_t len, int prot, int flags, int64_t direct_memory_start, uint64_t alignment);
int sceKernelReleaseDirectMemory(int64_t start, uint64_t len);
int sceKernelMunmap(void * vaddr, uint64_t len);
int sceKernelSendNotificationRequest(int param0, sceKernelNotifyRequest_t*, uint64_t size, int param3);

#ifdef __cplusplus
}
#endif

#endif