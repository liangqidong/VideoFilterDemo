#ifndef _VIDEO_FILTER_OUTPUT_PIN_H_
#define _VIDEO_FILTER_OUTPUT_PIN_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifndef _VIDEO_INFO_H_
#define _VIDEO_INFO_H_
typedef struct _VideoInfo
{

}VideoInfo;
#endif//_VIDEO_INFO_H_


class VideoFilterOutputPin
	: public CBaseOutputPin
{
public:
	VideoFilterOutputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName);
	~VideoFilterOutputPin();
	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT DecideBufferSize(IMemAllocator *pMemAllocator, ALLOCATOR_PROPERTIES * ppropInputRequest);

	HRESULT CompleteConnect(IPin *pReceivePin);
	HRESULT BreakConnect();
	HRESULT Deliver(IMediaSample *pMediaSample);

	long SetVideoMediaType(VideoInfo* pOutputPinVideoInfo);
	long GetPinCompleteConnectState(bool& state);
	long SetLogFileName(const char* fileName);
private:

	VideoInfo* m_videoInfo;
	bool       m_isCompleteConnect;
};

#endif//_AUDIO_PLAY_CAPTURE_FILTER_OUTPUT_PIN_H_
