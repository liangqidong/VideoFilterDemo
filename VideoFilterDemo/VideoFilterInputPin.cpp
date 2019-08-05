#include "VideoFilterInputPin.h"

#ifndef BEGIN_METHOD
#define BEGIN_METHOD\
	HRESULT codyy_methodresult = S_OK;\
	try\
	{
#endif//BEGIN_METHOD

#ifndef END_METHOD
#define END_METHOD\
	}\
	catch (HRESULT & resultException)\
	{\
	codyy_methodresult = resultException;\
	}\
	catch (...)\
	{\
	codyy_methodresult = E_FAIL;\
	}\
	return codyy_methodresult;
#endif//END_METHOD

BOOL VideoFilterInputPin::WCharToMByte(LPCWSTR lpcwszStr, std::string &str)
{
	DWORD dwMinSize = 0;
	LPSTR lpszStr = NULL;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (0 == dwMinSize)
	{
		return FALSE;
	}
	lpszStr = new char[dwMinSize];
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwMinSize, NULL, FALSE);
	str = lpszStr;
	delete[] lpszStr;
	lpszStr = NULL;
	return TRUE;
}

VideoFilterInputPin::VideoFilterInputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName)
	: CBaseInputPin(pObjName, pFilter, pLock, phr, pPinName)
	, m_dataCallBack(nullptr)
	, m_mediaTypeCallBack(nullptr)
	, m_isCompleteConnect(false)
	, m_videoInfo(nullptr)
{
	WCharToMByte(pPinName, m_pinName);
}

VideoFilterInputPin::~VideoFilterInputPin()
{
	if (nullptr != m_videoInfo)
	{
		delete m_videoInfo;
		m_videoInfo = nullptr;
	}
}

STDMETHODIMP_(ULONG) VideoFilterInputPin::NonDelegatingAddRef()
{
	CAutoLock lock_it(m_pLock);
	ULONG r = CBaseInputPin::NonDelegatingAddRef();
	return r;
}

STDMETHODIMP_(ULONG) VideoFilterInputPin::NonDelegatingRelease()
{
	CAutoLock lock_it(m_pLock);
	ULONG r = CBaseInputPin::NonDelegatingRelease();
	return r;
}

HRESULT VideoFilterInputPin::CheckMediaType(const CMediaType *pmt)
{
	BEGIN_METHOD
		if (!pmt)
			return E_INVALIDARG;

	if (pmt->majortype != MEDIATYPE_Audio)
		return E_FAIL;

	if (pmt->subtype != MEDIASUBTYPE_PCM)
		return E_FAIL;
	if (pmt->formattype != FORMAT_WaveFormatEx)
		return E_FAIL;

	if (pmt->FormatLength() != sizeof(WAVEFORMATEX))
		return E_FAIL;

	if (pmt->pbFormat != NULL &&  nullptr != m_videoInfo)
	{
		WAVEFORMATEX* pWfx = reinterpret_cast<WAVEFORMATEX*>(pmt->Format());
		if (0)//todo 检查媒体类型
		{

			return VFW_E_INVALID_MEDIA_TYPE;
		}
	}
	END_METHOD
	return NOERROR;
}

HRESULT VideoFilterInputPin::SetMediaType(const CMediaType *pmt)
{
	BEGIN_METHOD
		CAutoLock lock_it(m_pLock);
	HRESULT hr = NOERROR;

	WAVEFORMATEX	*wfx = (WAVEFORMATEX*)pmt->pbFormat;
	if (!wfx) return E_FAIL;
	if (nullptr != m_videoInfo)
	{
		return CBaseInputPin::SetMediaType(pmt);
	}
	if (nullptr != m_mediaTypeCallBack)
	{
		VideoInfo videoInfo;
		//todo 初始化媒体类型
		m_mediaTypeCallBack(m_pinName, &videoInfo);
	}
	
	hr = CBaseInputPin::SetMediaType(pmt);
	if (FAILED(hr))
		return hr;
	END_METHOD
}

HRESULT VideoFilterInputPin::BreakConnect()
{
	m_isCompleteConnect = false;
	return NOERROR;
}

HRESULT VideoFilterInputPin::CompleteConnect(IPin *pReceivePin)
{
	m_isCompleteConnect = true;
	return NOERROR;
}

STDMETHODIMP VideoFilterInputPin::Receive(IMediaSample *pSample)
{
	if (nullptr != m_dataCallBack)
	{
		m_dataCallBack(m_pinName, pSample);
	}
	return NOERROR;
}

long VideoFilterInputPin::RegMediaTypeCallBack(std::function<long(std::string, VideoInfo*)> callback)
{
	m_mediaTypeCallBack = callback;
	return NOERROR;
}

long VideoFilterInputPin::RegDataCallBack(std::function<long(std::string, IMediaSample*)> callback)
{
	m_dataCallBack = callback;
	return NOERROR;
}

long VideoFilterInputPin::SetVideoMediaType(VideoInfo* pInputVideoInfo)
{
	if (nullptr == pInputVideoInfo)
	{
		return NOERROR;
	}
	if (nullptr == m_videoInfo)
	{
		m_videoInfo = new VideoInfo;
	}
	memcpy(m_videoInfo, pInputVideoInfo, sizeof(VideoInfo));
	return NOERROR;
}

long VideoFilterInputPin::GetCompleteConnectState(bool& state)
{
	state = m_isCompleteConnect;
	return NOERROR;
}

long VideoFilterInputPin::SetLogFileName(const char* fileName)
{
	std::string strFileName(fileName);
	return NOERROR;
}
