#ifndef _VIDEO_FILTER_OUTPUT_PIN_H_
#define _VIDEO_FILTER_OUTPUT_PIN_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

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


class FilterOutputPin
	: public CBaseOutputPin
{
public:
	FilterOutputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName);
	~FilterOutputPin();
	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT DecideBufferSize(IMemAllocator *pMemAllocator, ALLOCATOR_PROPERTIES * ppropInputRequest);

	HRESULT CompleteConnect(IPin *pReceivePin);
	HRESULT BreakConnect();
	HRESULT Deliver(IMediaSample *pMediaSample);

	long SetPinMediaType(DataInfo* pOutputPinVideoInfo);
	long GetPinCompleteConnectState(bool& state);
	long SetLogFileName(const char* fileName);
private:

	DataInfo* m_dataInfo;
	bool       m_isCompleteConnect;
};

#endif//_AUDIO_PLAY_CAPTURE_FILTER_OUTPUT_PIN_H_
