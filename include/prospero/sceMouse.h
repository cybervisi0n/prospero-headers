#ifndef PROSPERO_SCE_MOUSE_H
#define PROSPERO_SCE_MOUSE_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

int sceMouseInit(void);

#define SCE_MOUSE_OPEN_PARAM_NORMAL	0x00
#define SCE_MOUSE_OPEN_PARAM_MERGED	0x01

typedef struct SceMouseOpenParam {
	uint8_t behaviorFlag;
	uint8_t unknown[7];
} SceMouseOpenParam;

#define SCE_MOUSE_PORT_TYPE_STANDARD		0 
#define SCE_MOUSE_MAX_STANDARD_PORT_INDEX	2

int sceMouseOpen(int userId, int32_t type, int32_t index, const SceMouseOpenParam* pParam);
int sceMouseClose(int32_t handle);

#define SCE_MOUSE_BUTTON_PRIMARY		0x00000001
#define SCE_MOUSE_BUTTON_SECONDARY		0x00000002
#define SCE_MOUSE_BUTTON_OPTIONAL		0x00000004
#define SCE_MOUSE_BUTTON_OPTIONAL2		0x00000008
#define SCE_MOUSE_BUTTON_OPTIONAL3		0x00000010
#define SCE_MOUSE_BUTTON_INTERCEPTED	0x80000000

typedef struct SceMouseData {
	uint64_t		timestamp;	
	bool			connected;	
	uint32_t		buttons;	
	int32_t			xAxis;		
	int32_t			yAxis;		
	int32_t			wheel;		
	int32_t			tilt;		
	uint8_t			reserve[8];	
} SceMouseData;

int sceMouseRead(int32_t handle, SceMouseData *pData, int32_t num);

#ifdef __cplusplus
}
#endif

#endif