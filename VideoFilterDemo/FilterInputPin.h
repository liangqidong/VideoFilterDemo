#ifndef _VIDEO_FILTER_INPUT_PIN_H_
#define _VIDEO_FILTER_INPUT_PIN_H_
#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#include <string>
#include <functional>

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

class FilterInputPin
	: public CBaseInputPin
{
public:
	FilterInputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName);
	~FilterInputPin();
	DECLARE_IUNKNOWN

	STDMETHODIMP_(ULONG) NonDelegatingAddRef();
	STDMETHODIMP_(ULONG) NonDelegatingRelease();
	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT SetMediaType(const CMediaType *pmt);
	HRESULT BreakConnect();
	virtual HRESULT CompleteConnect(IPin *pReceivePin);

	STDMETHODIMP Receive(IMediaSample *pSample);
	
	CMediaType& CurrentMediaType() { return m_mt; }

	long RegMediaTypeCallBack(std::function<long(std::string, DataInfo*)> callback);
	long RegDataCallBack(std::function<long(std::string, IMediaSample*)> callback);
	long SetPinMediaType(DataInfo* videoInfo);
	long GetCompleteConnectState(bool& state);
	long SetLogFileName(const char* fileName);
private:
	BOOL WCharToMByte(LPCWSTR lpcwszStr, std::string &str);

	std::string  m_pinName;
	DataInfo*		m_dataInfo;
	std::function<long(std::string, IMediaSample*)>  m_dataCallBack;
	std::function<long(std::string, DataInfo* )>     m_mediaTypeCallBack;
	bool  m_isCompleteConnect;
};
#endif//_AUDIO_PROCESS_FILTER_INPUT_PIN_H_
