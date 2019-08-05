#ifndef _VIDEO_FILTER_INPUT_PIN_H_
#define _VIDEO_FILTER_INPUT_PIN_H_
#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#include <string>
#include <functional>

#ifndef _VIDEO_INFO_H_
#define _VIDEO_INFO_H_
typedef struct _VideoInfo
{
}VideoInfo;
#endif//_VIDEO_INFO_H_

class VideoFilterInputPin
	: public CBaseInputPin
{
public:
	VideoFilterInputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName);
	~VideoFilterInputPin();
	DECLARE_IUNKNOWN

	STDMETHODIMP_(ULONG) NonDelegatingAddRef();
	STDMETHODIMP_(ULONG) NonDelegatingRelease();
	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT SetMediaType(const CMediaType *pmt);
	HRESULT BreakConnect();
	virtual HRESULT CompleteConnect(IPin *pReceivePin);

	STDMETHODIMP Receive(IMediaSample *pSample);
	
	CMediaType& CurrentMediaType() { return m_mt; }

	long RegMediaTypeCallBack(std::function<long(std::string, VideoInfo*)> callback);
	long RegDataCallBack(std::function<long(std::string, IMediaSample*)> callback);
	long SetVideoMediaType(VideoInfo* pInputAudioInfo);
	long GetCompleteConnectState(bool& state);
	long SetLogFileName(const char* fileName);
private:
	BOOL WCharToMByte(LPCWSTR lpcwszStr, std::string &str);

	std::string  m_pinName;
	VideoInfo*		m_videoInfo;
	std::function<long(std::string, IMediaSample*)>     m_dataCallBack;
	std::function<long(std::string, VideoInfo* )>     m_mediaTypeCallBack;
	bool  m_isCompleteConnect;
};
#endif//_AUDIO_PROCESS_FILTER_INPUT_PIN_H_
