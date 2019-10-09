#ifndef FILTER_PIN_H_
#define FILTER_PIN_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IID_FILTER_PIN
#define IID_FILTER_PIN
	// {B359F5E7-4119-4C01-89F5-5567DE085960}
	static const GUID IID_FilterPin =
	{ 0xb359f5e7, 0x4119, 0x4c01,{ 0x89, 0xf5, 0x55, 0x67, 0xde, 0x8, 0x59, 0x60 } };
#endif//IID_FILTER_PIN

#ifndef CLSID_FILTER
#define CLSID_FILTER
	// {633FC39C-A74F-4DA9-B7A9-3EB68614E8A8}
	static const GUID CLSID_Filter =
	{ 0x633fc39c, 0xa74f, 0x4da9,{ 0xb7, 0xa9, 0x3e, 0xb6, 0x86, 0x14, 0xe8, 0xa8 } };
#endif//CLSID_Filter
	
#ifndef PIN
#define PIN
	typedef struct _Pin
	{
		unsigned int inputPinNum;
		unsigned int outputPinNum;
		const char*const*  inputPinNameArr;
		const char*const*  outputPinNameArr;
		_Pin()
		{
			inputPinNum = 0;
			outputPinNum = 0;
			inputPinNameArr = nullptr;
			outputPinNameArr = nullptr;
		}
	}Pin;
#endif//PIN

#ifndef DATA_INFO
#define DATA_INFO
	typedef enum _DataType
	{
		No_Data_Type,
		AUDIO_PCM,
		AUDIO_AAC,
		VIDEO_H264,
		VIDEO_YUY2,
		VIDEO_NV_12,
	}DataType;
	typedef struct _DataInfo
	{
		DataType dataType;
		WAVEFORMATEX wfx;
		BITMAPINFO bitmap;
		_DataInfo()
		{
			dataType = No_Data_Type;
		}
	} DataInfo;
#endif//DATA_INFO

	DECLARE_INTERFACE_(IFilterPin, IUnknown)
	{
		STDMETHOD(SetInputAndOutputNum)(const Pin* pin)PURE;
		STDMETHOD(SetInputPinInfo)(const unsigned int pinidex, const DataInfo* dataInfo)PURE;
		STDMETHOD(SetoutputPinInfo)(const unsigned int pinidex, const DataInfo* dataInfo)PURE;
	};

#ifdef __cplusplus
}
#endif //DECLARE_INTERFACE_


#endif //FILTER_PIN_H_