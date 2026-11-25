#ifndef SCE_VIDEO_OUT_H
#define SCE_VIDEO_OUT_H

#include <stdint.h>

typedef struct SceVideoOutFlipStatus {
	uint64_t count;
	uint64_t processTime;
	uint64_t reserved0;
	int64_t flipArg;
	uint64_t reserved1;
	uint64_t processTimeCounter;
	int32_t gcQueueNum;
	int32_t flipPendingNum;	
	int32_t currentBuffer;	
	uint32_t reserved2;
	uint64_t submitProcessTimeCounter;
	uint64_t reserved3[7];
} SceVideoOutFlipStatus;

typedef struct SceVideoOutVblankStatus {
	uint64_t count;
	uint64_t processTime;
	uint64_t reserved;
	uint64_t processTimeCounter;
	uint8_t flags;
	uint8_t phase;
	uint8_t pad1[6];
} SceVideoOutVblankStatus;

typedef struct SceVideoOutColorSettings {
	float    gamma[3];
	uint32_t option;
} SceVideoOutColorSettings;

typedef struct SceVideoOutColorSpaceConversionSettings {
	uint32_t param[8];
} SceVideoOutColorSpaceConversionSettings;

typedef struct SceVideoOutBuffers {
	const void *data;
	const void *metadata;
	const void *reserved[2];
} SceVideoOutBuffers;

struct SceVideoOutBufferAttribute2 {
	int32_t _reserved0;
	int32_t tilingMode;
	int32_t aspectRatio;
	uint32_t width;
	uint32_t height;
	uint32_t pitchInPixel;
	uint64_t option;
	uint64_t pixelFormat;
	uint64_t dccCbRegisterClearColor;
	uint32_t dccControl;
	uint32_t pad0;
	uint64_t _reserved1[3];
};

typedef enum SceVideoOutGlobalBlendSpace {
	SCE_VIDEO_OUT_GLOBAL_BLEND_SPACE_GAMMA   = 0,
	SCE_VIDEO_OUT_GLOBAL_BLEND_SPACE_LINEAR  = 1,
} SceVideoOutGlobalBlendSpace;

typedef enum SceVideoOutOutputResolution {
	SCE_VIDEO_OUT_OUTPUT_RESOLUTION_UNKNOWN = 0,
	SCE_VIDEO_OUT_OUTPUT_RESOLUTION_HD =1,
	SCE_VIDEO_OUT_OUTPUT_RESOLUTION_4K =2,
} SceVideoOutOutputResolution;

typedef enum SceVideoOutOutputDynamicRange {
	SCE_VIDEO_OUT_OUTPUT_DYNAMIC_RANGE_UNKNOWN = 0,
	SCE_VIDEO_OUT_OUTPUT_DYNAMIC_RANGE_SDR=1,
	SCE_VIDEO_OUT_OUTPUT_DYNAMIC_RANGE_HDR=2,
} SceVideoOutOutputDynamicRange;

typedef enum SceVideoOutOutputStatusFlags {
	SCE_VIDEO_OUT_OUTPUT_STATUS_FLAGS_HDR   =(1U<<0),
} SceVideoOutOutputStatusFlags;

typedef struct SceVideoOutOutputStatus {
	uint32_t resolution;
	uint32_t dynamicRange;
	uint64_t refreshRate;
	uint64_t flags;
	uint64_t _reserved[3];
} SceVideoOutOutputStatus;

#ifdef __cplusplus
extern "C" {
#endif

int32_t sceVideoOutOpen(int user_id, int bus_type, int index, const void *param);
int32_t sceVideoOutClose(int);
int32_t sceVideoOutSetFlipRate(int handle, int rate);
int32_t sceVideoOutSubmitFlip(int handle, int buffer_index, int flip_mode, int flip_argument);
int32_t sceVideoOutWaitVblank(int handle);

int32_t sceVideoOutRegisterBuffers(int, int, void * const *, int, const void *);
int32_t sceVideoOutUnregisterBuffers(int, int);
int32_t sceVideoOutGetFlipStatus(int32_t handle, SceVideoOutFlipStatus *status);
int32_t sceVideoOutGetVblankStatus(int32_t handle, SceVideoOutVblankStatus *status);
int32_t sceVideoOutIsFlipPending(int32_t handle);
int32_t sceVideoOutSetFlipMaster(int32_t slaveHandle, int32_t masterHandle);
int32_t sceVideoOutClearFlipMaster(int32_t slaveHandle);
int32_t sceVideoOutSetWindowModeMargins(int32_t handle, int top, int bottom);
int32_t sceVideoOutAddFlipEvent(SceKernelEqueue eq, int32_t handle, void *udata);
int32_t sceVideoOutAddVblankEvent(SceKernelEqueue eq, int32_t handle, void *udata);
int32_t sceVideoOutDeleteFlipEvent(SceKernelEqueue eq, int32_t handle);
int32_t sceVideoOutDeleteVblankEvent(SceKernelEqueue eq, int32_t handle);
int32_t sceVideoOutAddPreVblankStartEvent(SceKernelEqueue eq, int32_t handle, void *udata);
int32_t sceVideoOutDeletePreVblankStartEvent(SceKernelEqueue eq, int32_t handle);
int32_t sceVideoOutGetEventId(const SceKernelEvent *ev);
int32_t sceVideoOutGetEventData(const SceKernelEvent *ev, int64_t *data);
int32_t sceVideoOutGetEventCount(const SceKernelEvent *ev);
int32_t sceVideoOutColorSpaceConversionSettingsSetSdrToHdrConversion_(
	SceVideoOutColorSpaceConversionSettings* pSettings,
	float                                    lumaScale,
	uint32_t                                 option,
    uint32_t                                 sizeOfSettings);
int32_t sceVideoOutColorSpaceConversionSettingsSetDefaultSdrToHdrConversion_(
	SceVideoOutColorSpaceConversionSettings* p,
    uint32_t                                 sizeOfSettings);
int32_t sceVideoOutAdjustColorSpaceConversion_(
	int32_t                                  handle,
	SceVideoOutColorSpaceConversionSettings *pSettings,
	uint32_t                                 sizeOfSettings);
int32_t sceVideoOutColorSettingsSetGamma_(SceVideoOutColorSettings* p, float gamma, uint32_t sizeOfSettings);
int32_t sceVideoOutAdjustColor_(int32_t                   handle,
								SceVideoOutColorSettings *pSettings,
								uint32_t                  sizeOfSettings);
void sceVideoOutSetBufferAttribute2(SceVideoOutBufferAttribute2 *attribute, uint64_t pixelFormat, uint32_t tilingMode, uint32_t width, uint32_t height, uint64_t option, uint32_t dccControl, uint64_t dccCbRegisterClearColor);
int32_t sceVideoOutRegisterBuffers2(int32_t handle, int32_t setIndex, int32_t bufferIndexStart, const SceVideoOutBuffers *buffers, int32_t bufferNum, const SceVideoOutBufferAttribute2 *attribute, int32_t category, void *option);
int32_t sceVideoOutSubmitChangeBufferAttribute2(int32_t handle, int32_t setIndex, const SceVideoOutBufferAttribute2 *attribute, void *option);
void sceVideoOutAddBufferAttributeOption(SceVideoOutBufferAttribute2 *attribute, uint64_t option);
void sceVideoOutRemoveBufferAttributeOption(SceVideoOutBufferAttribute2 *attribute, uint64_t option);
int32_t sceVideoOutSetAlphaControl(int32_t handle, int globalAlphaMode, int globalAlphaValue, const uint8_t *a2lut, void *option);
int32_t sceVideoOutSetGlobalBlendSpace(int32_t handle, uint32_t space, uint32_t option);
int32_t sceVideoOutGetOutputStatus(int32_t handle, SceVideoOutOutputStatus *status);

// TODO: Convert to c function declarations
#if 0
asm(".global sceDbgVideoOutAddOutputModeVr60Privilege\n"
    ".type sceDbgVideoOutAddOutputModeVr60Privilege @function\n"
    "sceDbgVideoOutAddOutputModeVr60Privilege:\n");

asm(".global sceVideoOutAddBuffer\n"
    ".type sceVideoOutAddBuffer @function\n"
    "sceVideoOutAddBuffer:\n");

asm(".global sceVideoOutAddBuffer4k2kPrivilege\n"
    ".type sceVideoOutAddBuffer4k2kPrivilege @function\n"
    "sceVideoOutAddBuffer4k2kPrivilege:\n");

asm(".global sceVideoOutAddBufferAnisoPrivilege\n"
    ".type sceVideoOutAddBufferAnisoPrivilege @function\n"
    "sceVideoOutAddBufferAnisoPrivilege:\n");

asm(".global sceVideoOutAddBufferHdrPrivilege\n"
    ".type sceVideoOutAddBufferHdrPrivilege @function\n"
    "sceVideoOutAddBufferHdrPrivilege:\n");

asm(".global sceVideoOutAddBufferYccPrivilege\n"
    ".type sceVideoOutAddBufferYccPrivilege @function\n"
    "sceVideoOutAddBufferYccPrivilege:\n");

asm(".global sceVideoOutAddDisplayPositionEvent\n"
    ".type sceVideoOutAddDisplayPositionEvent @function\n"
    "sceVideoOutAddDisplayPositionEvent:\n");

asm(".global sceVideoOutAddDriver\n"
    ".type sceVideoOutAddDriver @function\n"
    "sceVideoOutAddDriver:\n");

asm(".global sceVideoOutAddOutputModeEvent\n"
    ".type sceVideoOutAddOutputModeEvent @function\n"
    "sceVideoOutAddOutputModeEvent:\n");

asm(".global sceVideoOutAddS3dHmdPrivilege\n"
    ".type sceVideoOutAddS3dHmdPrivilege @function\n"
    "sceVideoOutAddS3dHmdPrivilege:\n");

asm(".global sceVideoOutAddSetModeEvent\n"
    ".type sceVideoOutAddSetModeEvent @function\n"
    "sceVideoOutAddSetModeEvent:\n");

asm(".global sceVideoOutAddStereoBuffer\n"
    ".type sceVideoOutAddStereoBuffer @function\n"
    "sceVideoOutAddStereoBuffer:\n");

asm(".global sceVideoOutAdjustColor2_\n"
    ".type sceVideoOutAdjustColor2_ @function\n"
    "sceVideoOutAdjustColor2_:\n");

asm(".global sceVideoOutConfigureLayout\n"
    ".type sceVideoOutConfigureLayout @function\n"
    "sceVideoOutConfigureLayout:\n");

asm(".global sceVideoOutConfigureOptionsInitialize_\n"
    ".type sceVideoOutConfigureOptionsInitialize_ @function\n"
    "sceVideoOutConfigureOptionsInitialize_:\n");

asm(".global sceVideoOutConfigureOutput\n"
    ".type sceVideoOutConfigureOutput @function\n"
    "sceVideoOutConfigureOutput:\n");

asm(".global sceVideoOutConfigureOutputEx\n"
    ".type sceVideoOutConfigureOutputEx @function\n"
    "sceVideoOutConfigureOutputEx:\n");

asm(".global sceVideoOutConfigureOutputModeExSubmitDoneUnsafe_\n"
    ".type sceVideoOutConfigureOutputModeExSubmitDoneUnsafe_ @function\n"
    "sceVideoOutConfigureOutputModeExSubmitDoneUnsafe_:\n");

asm(".global sceVideoOutConfigureOutputModeEx_\n"
    ".type sceVideoOutConfigureOutputModeEx_ @function\n"
    "sceVideoOutConfigureOutputModeEx_:\n");

asm(".global sceVideoOutConfigureOutputMode_\n"
    ".type sceVideoOutConfigureOutputMode_ @function\n"
    "sceVideoOutConfigureOutputMode_:\n");

asm(".global sceVideoOutControlHdcpEncryption\n"
    ".type sceVideoOutControlHdcpEncryption @function\n"
    "sceVideoOutControlHdcpEncryption:\n");

asm(".global sceVideoOutCursorDisable\n"
    ".type sceVideoOutCursorDisable @function\n"
    "sceVideoOutCursorDisable:\n");

asm(".global sceVideoOutCursorEnable\n"
    ".type sceVideoOutCursorEnable @function\n"
    "sceVideoOutCursorEnable:\n");

asm(".global sceVideoOutCursorIsUpdatePending\n"
    ".type sceVideoOutCursorIsUpdatePending @function\n"
    "sceVideoOutCursorIsUpdatePending:\n");

asm(".global sceVideoOutCursorSet2xMagnify\n"
    ".type sceVideoOutCursorSet2xMagnify @function\n"
    "sceVideoOutCursorSet2xMagnify:\n");

asm(".global sceVideoOutCursorSetHotSpot\n"
    ".type sceVideoOutCursorSetHotSpot @function\n"
    "sceVideoOutCursorSetHotSpot:\n");

asm(".global sceVideoOutCursorSetImageAddress\n"
    ".type sceVideoOutCursorSetImageAddress @function\n"
    "sceVideoOutCursorSetImageAddress:\n");

asm(".global sceVideoOutCursorSetPosition\n"
    ".type sceVideoOutCursorSetPosition @function\n"
    "sceVideoOutCursorSetPosition:\n");

asm(".global sceVideoOutCursorSetPositionStereo\n"
    ".type sceVideoOutCursorSetPositionStereo @function\n"
    "sceVideoOutCursorSetPositionStereo:\n");

asm(".global sceVideoOutCurveSamplePointsCalc_\n"
    ".type sceVideoOutCurveSamplePointsCalc_ @function\n"
    "sceVideoOutCurveSamplePointsCalc_:\n");

asm(".global sceVideoOutDeleteDisplayPositionEvent\n"
    ".type sceVideoOutDeleteDisplayPositionEvent @function\n"
    "sceVideoOutDeleteDisplayPositionEvent:\n");

asm(".global sceVideoOutDeleteDriver\n"
    ".type sceVideoOutDeleteDriver @function\n"
    "sceVideoOutDeleteDriver:\n");

asm(".global sceVideoOutDeleteOutputModeEvent\n"
    ".type sceVideoOutDeleteOutputModeEvent @function\n"
    "sceVideoOutDeleteOutputModeEvent:\n");

asm(".global sceVideoOutDeleteSetModeEvent\n"
    ".type sceVideoOutDeleteSetModeEvent @function\n"
    "sceVideoOutDeleteSetModeEvent:\n");
	
asm(".global sceVideoOutDriverAddEvent\n"
    ".type sceVideoOutDriverAddEvent @function\n"
    "sceVideoOutDriverAddEvent:\n");

asm(".global sceVideoOutDriverDecrementBufferLabel\n"
    ".type sceVideoOutDriverDecrementBufferLabel @function\n"
    "sceVideoOutDriverDecrementBufferLabel:\n");

asm(".global sceVideoOutDriverDeleteEvent\n"
    ".type sceVideoOutDriverDeleteEvent @function\n"
    "sceVideoOutDriverDeleteEvent:\n");

asm(".global sceVideoOutDriverGetBufferLabelAddress\n"
    ".type sceVideoOutDriverGetBufferLabelAddress @function\n"
    "sceVideoOutDriverGetBufferLabelAddress:\n");

asm(".global sceVideoOutDriverGetEopHandle\n"
    ".type sceVideoOutDriverGetEopHandle @function\n"
    "sceVideoOutDriverGetEopHandle:\n");

asm(".global sceVideoOutDriverGetFinishedEopHandle\n"
    ".type sceVideoOutDriverGetFinishedEopHandle @function\n"
    "sceVideoOutDriverGetFinishedEopHandle:\n");

asm(".global sceVideoOutDriverGetLatestEopHandle\n"
    ".type sceVideoOutDriverGetLatestEopHandle @function\n"
    "sceVideoOutDriverGetLatestEopHandle:\n");

asm(".global sceVideoOutDriverIncrementBufferLabel\n"
    ".type sceVideoOutDriverIncrementBufferLabel @function\n"
    "sceVideoOutDriverIncrementBufferLabel:\n");

asm(".global sceVideoOutDriverResetBufferLabel\n"
    ".type sceVideoOutDriverResetBufferLabel @function\n"
    "sceVideoOutDriverResetBufferLabel:\n");

asm(".global sceVideoOutDriverTriggerEvent\n"
    ".type sceVideoOutDriverTriggerEvent @function\n"
    "sceVideoOutDriverTriggerEvent:\n");

asm(".global sceVideoOutGetBufferInformation\n"
    ".type sceVideoOutGetBufferInformation @function\n"
    "sceVideoOutGetBufferInformation:\n");

asm(".global sceVideoOutGetBufferLabelAddress\n"
    ".type sceVideoOutGetBufferLabelAddress @function\n"
    "sceVideoOutGetBufferLabelAddress:\n");

asm(".global sceVideoOutGetCoredumpOutputMode\n"
    ".type sceVideoOutGetCoredumpOutputMode @function\n"
    "sceVideoOutGetCoredumpOutputMode:\n");

asm(".global sceVideoOutGetCurrentOutputMode_\n"
    ".type sceVideoOutGetCurrentOutputMode_ @function\n"
    "sceVideoOutGetCurrentOutputMode_:\n");

asm(".global sceVideoOutGetDeviceCapabilityInfo_\n"
    ".type sceVideoOutGetDeviceCapabilityInfo_ @function\n"
    "sceVideoOutGetDeviceCapabilityInfo_:\n");

asm(".global sceVideoOutGetDeviceInfoExOts_\n"
    ".type sceVideoOutGetDeviceInfoExOts_ @function\n"
    "sceVideoOutGetDeviceInfoExOts_:\n");

asm(".global sceVideoOutGetDeviceInfoEx_\n"
    ".type sceVideoOutGetDeviceInfoEx_ @function\n"
    "sceVideoOutGetDeviceInfoEx_:\n");

asm(".global sceVideoOutGetHdmiKsvList_\n"
    ".type sceVideoOutGetHdmiKsvList_ @function\n"
    "sceVideoOutGetHdmiKsvList_:\n");

asm(".global sceVideoOutGetHdmiMonitorInfoNoMask_\n"
    ".type sceVideoOutGetHdmiMonitorInfoNoMask_ @function\n"
    "sceVideoOutGetHdmiMonitorInfoNoMask_:\n");

asm(".global sceVideoOutGetHdmiMonitorInfo_\n"
    ".type sceVideoOutGetHdmiMonitorInfo_ @function\n"
    "sceVideoOutGetHdmiMonitorInfo_:\n");

asm(".global sceVideoOutGetHdmiRawEdid_\n"
    ".type sceVideoOutGetHdmiRawEdid_ @function\n"
    "sceVideoOutGetHdmiRawEdid_:\n");

asm(".global sceVideoOutGetMonitorInfo\n"
    ".type sceVideoOutGetMonitorInfo @function\n"
    "sceVideoOutGetMonitorInfo:\n");

asm(".global sceVideoOutGetPipelineStatus\n"
    ".type sceVideoOutGetPipelineStatus @function\n"
    "sceVideoOutGetPipelineStatus:\n");

asm(".global sceVideoOutGetPortStatusInfo\n"
    ".type sceVideoOutGetPortStatusInfo @function\n"
    "sceVideoOutGetPortStatusInfo:\n");

asm(".global sceVideoOutGetPortStatusInfoByBusSpecifier_\n"
    ".type sceVideoOutGetPortStatusInfoByBusSpecifier_ @function\n"
    "sceVideoOutGetPortStatusInfoByBusSpecifier_:\n");

asm(".global sceVideoOutGetPortStatusInfo_\n"
    ".type sceVideoOutGetPortStatusInfo_ @function\n"
    "sceVideoOutGetPortStatusInfo_:\n");

asm(".global sceVideoOutGetResolutionStatus\n"
    ".type sceVideoOutGetResolutionStatus @function\n"
    "sceVideoOutGetResolutionStatus:\n");

asm(".global sceVideoOutGetStatusForWebcore\n"
    ".type sceVideoOutGetStatusForWebcore @function\n"
    "sceVideoOutGetStatusForWebcore:\n");

asm(".global sceVideoOutGetVideoOutModeByBusSpecifier_\n"
    ".type sceVideoOutGetVideoOutModeByBusSpecifier_ @function\n"
    "sceVideoOutGetVideoOutModeByBusSpecifier_:\n");

asm(".global sceVideoOutHdmiMonitorInfoIsSupportedHdcpVersion\n"
    ".type sceVideoOutHdmiMonitorInfoIsSupportedHdcpVersion @function\n"
    "sceVideoOutHdmiMonitorInfoIsSupportedHdcpVersion:\n");

asm(".global sceVideoOutHdmiMonitorInfoIsSupportedVideoOutMode_\n"
    ".type sceVideoOutHdmiMonitorInfoIsSupportedVideoOutMode_ @function\n"
    "sceVideoOutHdmiMonitorInfoIsSupportedVideoOutMode_:\n");

asm(".global sceVideoOutInitializeOutputOptions\n"
    ".type sceVideoOutInitializeOutputOptions @function\n"
    "sceVideoOutInitializeOutputOptions:\n");

asm(".global sceVideoOutIsOutputSupported\n"
    ".type sceVideoOutIsOutputSupported @function\n"
    "sceVideoOutIsOutputSupported:\n");

asm(".global sceVideoOutLockBuffer\n"
    ".type sceVideoOutLockBuffer @function\n"
    "sceVideoOutLockBuffer:\n");

asm(".global sceVideoOutModeSetAny_\n"
    ".type sceVideoOutModeSetAny_ @function\n"
    "sceVideoOutModeSetAny_:\n");

asm(".global sceVideoOutRazorAddCallback\n"
    ".type sceVideoOutRazorAddCallback @function\n"
    "sceVideoOutRazorAddCallback:\n");

asm(".global sceVideoOutRazorRecallCallbacks\n"
    ".type sceVideoOutRazorRecallCallbacks @function\n"
    "sceVideoOutRazorRecallCallbacks:\n");

asm(".global sceVideoOutRazorRemoveCallback\n"
    ".type sceVideoOutRazorRemoveCallback @function\n"
    "sceVideoOutRazorRemoveCallback:\n");

asm(".global sceVideoOutRegisterBufferAttribute\n"
    ".type sceVideoOutRegisterBufferAttribute @function\n"
    "sceVideoOutRegisterBufferAttribute:\n");

asm(".global sceVideoOutRegisterStereoBuffers\n"
    ".type sceVideoOutRegisterStereoBuffers @function\n"
    "sceVideoOutRegisterStereoBuffers:\n");

asm(".global sceVideoOutRemoveBuffer\n"
    ".type sceVideoOutRemoveBuffer @function\n"
    "sceVideoOutRemoveBuffer:\n");

asm(".global sceVideoOutSetBlankAfterResume\n"
    ".type sceVideoOutSetBlankAfterResume @function\n"
    "sceVideoOutSetBlankAfterResume:\n");

asm(".global sceVideoOutSetBufferAttribute\n"
    ".type sceVideoOutSetBufferAttribute @function\n"
    "sceVideoOutSetBufferAttribute:\n");

asm(".global sceVideoOutSetContentType\n"
    ".type sceVideoOutSetContentType @function\n"
    "sceVideoOutSetContentType:\n");

asm(".global sceVideoOutSetDisplayEventPosition\n"
    ".type sceVideoOutSetDisplayEventPosition @function\n"
    "sceVideoOutSetDisplayEventPosition:\n");

asm(".global sceVideoOutSetGamutMetadata_\n"
    ".type sceVideoOutSetGamutMetadata_ @function\n"
    "sceVideoOutSetGamutMetadata_:\n");

asm(".global sceVideoOutSetToneMap_\n"
    ".type sceVideoOutSetToneMap_ @function\n"
    "sceVideoOutSetToneMap_:\n");

asm(".global sceVideoOutSubmitChangeBufferAttribute\n"
    ".type sceVideoOutSubmitChangeBufferAttribute @function\n"
    "sceVideoOutSubmitChangeBufferAttribute:\n");

asm(".global sceVideoOutSubmitEopFlip\n"
    ".type sceVideoOutSubmitEopFlip @function\n"
    "sceVideoOutSubmitEopFlip:\n");

asm(".global sceVideoOutSysAddSetModeEvent\n"
    ".type sceVideoOutSysAddSetModeEvent @function\n"
    "sceVideoOutSysAddSetModeEvent:\n");

asm(".global sceVideoOutSysAddSetModeEvent2\n"
    ".type sceVideoOutSysAddSetModeEvent2 @function\n"
    "sceVideoOutSysAddSetModeEvent2:\n");

asm(".global sceVideoOutSysAddVblankEvent\n"
    ".type sceVideoOutSysAddVblankEvent @function\n"
    "sceVideoOutSysAddVblankEvent:\n");

asm(".global sceVideoOutSysAddVblankEvent2\n"
    ".type sceVideoOutSysAddVblankEvent2 @function\n"
    "sceVideoOutSysAddVblankEvent2:\n");

asm(".global sceVideoOutSysClose\n"
    ".type sceVideoOutSysClose @function\n"
    "sceVideoOutSysClose:\n");

asm(".global sceVideoOutSysConfigureLayout\n"
    ".type sceVideoOutSysConfigureLayout @function\n"
    "sceVideoOutSysConfigureLayout:\n");

asm(".global sceVideoOutSysConfigureOutput\n"
    ".type sceVideoOutSysConfigureOutput @function\n"
    "sceVideoOutSysConfigureOutput:\n");

asm(".global sceVideoOutSysConfigureOutputMode\n"
    ".type sceVideoOutSysConfigureOutputMode @function\n"
    "sceVideoOutSysConfigureOutputMode:\n");

asm(".global sceVideoOutSysCursorDisable\n"
    ".type sceVideoOutSysCursorDisable @function\n"
    "sceVideoOutSysCursorDisable:\n");

asm(".global sceVideoOutSysCursorEnable\n"
    ".type sceVideoOutSysCursorEnable @function\n"
    "sceVideoOutSysCursorEnable:\n");

asm(".global sceVideoOutSysCursorIsUpdatePending\n"
    ".type sceVideoOutSysCursorIsUpdatePending @function\n"
    "sceVideoOutSysCursorIsUpdatePending:\n");

asm(".global sceVideoOutSysCursorObtain\n"
    ".type sceVideoOutSysCursorObtain @function\n"
    "sceVideoOutSysCursorObtain:\n");

asm(".global sceVideoOutSysCursorRelease\n"
    ".type sceVideoOutSysCursorRelease @function\n"
    "sceVideoOutSysCursorRelease:\n");

asm(".global sceVideoOutSysCursorSetPosition\n"
    ".type sceVideoOutSysCursorSetPosition @function\n"
    "sceVideoOutSysCursorSetPosition:\n");

asm(".global sceVideoOutSysDeleteVblankEvent\n"
    ".type sceVideoOutSysDeleteVblankEvent @function\n"
    "sceVideoOutSysDeleteVblankEvent:\n");

asm(".global sceVideoOutSysDeleteVblankEvent2\n"
    ".type sceVideoOutSysDeleteVblankEvent2 @function\n"
    "sceVideoOutSysDeleteVblankEvent2:\n");

asm(".global sceVideoOutSysGetBus\n"
    ".type sceVideoOutSysGetBus @function\n"
    "sceVideoOutSysGetBus:\n");

asm(".global sceVideoOutSysGetColorConversionStatus\n"
    ".type sceVideoOutSysGetColorConversionStatus @function\n"
    "sceVideoOutSysGetColorConversionStatus:\n");

asm(".global sceVideoOutSysGetCurrentOutputMode\n"
    ".type sceVideoOutSysGetCurrentOutputMode @function\n"
    "sceVideoOutSysGetCurrentOutputMode:\n");

asm(".global sceVideoOutSysGetDeviceInfo\n"
    ".type sceVideoOutSysGetDeviceInfo @function\n"
    "sceVideoOutSysGetDeviceInfo:\n");

asm(".global sceVideoOutSysGetFlipStatus\n"
    ".type sceVideoOutSysGetFlipStatus @function\n"
    "sceVideoOutSysGetFlipStatus:\n");

asm(".global sceVideoOutSysGetMonitorInfo_\n"
    ".type sceVideoOutSysGetMonitorInfo_ @function\n"
    "sceVideoOutSysGetMonitorInfo_:\n");

asm(".global sceVideoOutSysGetPipelineStatus\n"
    ".type sceVideoOutSysGetPipelineStatus @function\n"
    "sceVideoOutSysGetPipelineStatus:\n");

asm(".global sceVideoOutSysGetResolutionStatus\n"
    ".type sceVideoOutSysGetResolutionStatus @function\n"
    "sceVideoOutSysGetResolutionStatus:\n");

asm(".global sceVideoOutSysGetResolutionStatus2\n"
    ".type sceVideoOutSysGetResolutionStatus2 @function\n"
    "sceVideoOutSysGetResolutionStatus2:\n");

asm(".global sceVideoOutSysGetVblankStatus\n"
    ".type sceVideoOutSysGetVblankStatus @function\n"
    "sceVideoOutSysGetVblankStatus:\n");

asm(".global sceVideoOutSysGetVblankStatus2\n"
    ".type sceVideoOutSysGetVblankStatus2 @function\n"
    "sceVideoOutSysGetVblankStatus2:\n");

asm(".global sceVideoOutSysGetVideoOutModeByBusSpecifier\n"
    ".type sceVideoOutSysGetVideoOutModeByBusSpecifier @function\n"
    "sceVideoOutSysGetVideoOutModeByBusSpecifier:\n");

asm(".global sceVideoOutSysHdmiMonitorInfoIsMorpheus\n"
    ".type sceVideoOutSysHdmiMonitorInfoIsMorpheus @function\n"
    "sceVideoOutSysHdmiMonitorInfoIsMorpheus:\n");

asm(".global sceVideoOutSysIsModeS3d\n"
    ".type sceVideoOutSysIsModeS3d @function\n"
    "sceVideoOutSysIsModeS3d:\n");

asm(".global sceVideoOutSysIsSupportedByMonitorInfo_\n"
    ".type sceVideoOutSysIsSupportedByMonitorInfo_ @function\n"
    "sceVideoOutSysIsSupportedByMonitorInfo_:\n");

asm(".global sceVideoOutSysIsUserStatusSystemDefault\n"
    ".type sceVideoOutSysIsUserStatusSystemDefault @function\n"
    "sceVideoOutSysIsUserStatusSystemDefault:\n");

asm(".global sceVideoOutSysIsUserStatusVr\n"
    ".type sceVideoOutSysIsUserStatusVr @function\n"
    "sceVideoOutSysIsUserStatusVr:\n");

asm(".global sceVideoOutSysModeIsSystemDefault\n"
    ".type sceVideoOutSysModeIsSystemDefault @function\n"
    "sceVideoOutSysModeIsSystemDefault:\n");

asm(".global sceVideoOutSysModeIsVr\n"
    ".type sceVideoOutSysModeIsVr @function\n"
    "sceVideoOutSysModeIsVr:\n");

asm(".global sceVideoOutSysOpenInternal\n"
    ".type sceVideoOutSysOpenInternal @function\n"
    "sceVideoOutSysOpenInternal:\n");

asm(".global sceVideoOutSysReadCrc\n"
    ".type sceVideoOutSysReadCrc @function\n"
    "sceVideoOutSysReadCrc:\n");

asm(".global sceVideoOutSysReadCrc64\n"
    ".type sceVideoOutSysReadCrc64 @function\n"
    "sceVideoOutSysReadCrc64:\n");

asm(".global sceVideoOutSysResetAtGpuReset\n"
    ".type sceVideoOutSysResetAtGpuReset @function\n"
    "sceVideoOutSysResetAtGpuReset:\n");

asm(".global sceVideoOutSysSetColorMode\n"
    ".type sceVideoOutSysSetColorMode @function\n"
    "sceVideoOutSysSetColorMode:\n");

asm(".global sceVideoOutSysSetDcePipeMode\n"
    ".type sceVideoOutSysSetDcePipeMode @function\n"
    "sceVideoOutSysSetDcePipeMode:\n");

asm(".global sceVideoOutSysSetDimmer\n"
    ".type sceVideoOutSysSetDimmer @function\n"
    "sceVideoOutSysSetDimmer:\n");

asm(".global sceVideoOutSysSetDimmer2\n"
    ".type sceVideoOutSysSetDimmer2 @function\n"
    "sceVideoOutSysSetDimmer2:\n");

asm(".global sceVideoOutSysSetHdcpEncryption\n"
    ".type sceVideoOutSysSetHdcpEncryption @function\n"
    "sceVideoOutSysSetHdcpEncryption:\n");

asm(".global sceVideoOutSysSetHdrMetadata\n"
    ".type sceVideoOutSysSetHdrMetadata @function\n"
    "sceVideoOutSysSetHdrMetadata:\n");

asm(".global sceVideoOutSysSetOverscanRatio\n"
    ".type sceVideoOutSysSetOverscanRatio @function\n"
    "sceVideoOutSysSetOverscanRatio:\n");

asm(".global sceVideoOutSysUpdateDisplayParameter\n"
    ".type sceVideoOutSysUpdateDisplayParameter @function\n"
    "sceVideoOutSysUpdateDisplayParameter:\n");

asm(".global sceVideoOutSysUpdatePrivilege\n"
    ".type sceVideoOutSysUpdatePrivilege @function\n"
    "sceVideoOutSysUpdatePrivilege:\n");

asm(".global sceVideoOutSysUpdateRenderingMode\n"
    ".type sceVideoOutSysUpdateRenderingMode @function\n"
    "sceVideoOutSysUpdateRenderingMode:\n");

asm(".global sceVideoOutUnlockBuffer\n"
    ".type sceVideoOutUnlockBuffer @function\n"
    "sceVideoOutUnlockBuffer:\n");

asm(".global sceVideoOutUnregisterBufferAttribute\n"
    ".type sceVideoOutUnregisterBufferAttribute @function\n"
    "sceVideoOutUnregisterBufferAttribute:\n");
#endif

#ifdef __cplusplus
}
#endif

#endif