#ifndef PROSPERO_SCE_KERNEL_H
#define PROSPERO_SCE_KERNEL_H

#include <stdint.h>
#include <stddef.h>

typedef struct sceKernelNotifyRequest {
  char useless1[45];
  char message[3075];
} sceKernelNotifyRequest_t;

#ifdef __cplusplus
extern "C" {
#endif

#define PROSPERO_SCE_KERNEL_PROT_CPU_READ 0x01
#define PROSPERO_SCE_KERNEL_PROT_CPU_WRITE 0x02
#define PROSPERO_SCE_KERNEL_PROT_CPU_EXEC 0x04
#define PROSPERO_SCE_KERNEL_PROT_GPU_READ 0x10
#define PROSPERO_SCE_KERNEL_PROT_GPU_WRITE 0x20

#define PROSPERO_SCE_KERNEL_MAP_FIXED 0x10

#define PROSPERO_SCE_KERNEL_DIRECT_TYPE_CPU 12

int sceKernelAllocateDirectMemory(int64_t search_start, int64_t search_end, size_t len, size_t alignment, int memory_type, int64_t* phys_addr_out);
int sceKernelMapDirectMemory(void** addr, uint64_t len, int prot, int flags, int64_t direct_memory_start, uint64_t alignment);
int sceKernelReleaseDirectMemory(int64_t start, uint64_t len);
int32_t sceKernelMprotect(const void *address, size_t length, int protection);
int32_t sceKernelReserveVirtualRange(void **address, size_t length, int flags, size_t alignment);
int sceKernelMunmap(void * vaddr, uint64_t len);
int32_t sceKernelQueryMemoryProtection(void *address, void **start, void **end, uint32_t *protection);
int sceKernelSendNotificationRequest(int param0, sceKernelNotifyRequest_t*, uint64_t size, int param3);
size_t sceKernelGetDirectMemorySize();
void sceKernelUsleep(int timeUs);

#ifdef __cplusplus
}
#endif

#endif