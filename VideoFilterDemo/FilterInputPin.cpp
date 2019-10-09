#include "FilterInputPin.h"

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

BOOL FilterInputPin::WCharToMByte(LPCWSTR lpcwszStr, std::string &str)
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

FilterInputPin::FilterInputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName)
	: CBaseInputPin(pObjName, pFilter, pLock, phr, pPinName)
	, m_dataCallBack(nullptr)
	, m_mediaTypeCallBack(nullptr)
	, m_isCompleteConnect(false)
	, m_dataInfo(nullptr)
{
	WCharToMByte(pPinName, m_pinName);
}

FilterInputPin::~FilterInputPin()
{
	if (nullptr != m_dataInfo)
	{
		delete m_dataInfo;
		m_dataInfo = nullptr;
	}
}

STDMETHODIMP_(ULONG) FilterInputPin::NonDelegatingAddRef()
{
	CAutoLock lock_it(m_pLock);
	ULONG r = CBaseInputPin::NonDelegatingAddRef();
	return r;
}

STDMETHODIMP_(ULONG) FilterInputPin::NonDelegatingRelease()
{
	CAutoLock lock_it(m_pLock);
	ULONG r = CBaseInputPin::NonDelegatingRelease();
	return r;
}

HRESULT FilterInputPin::CheckMediaType(const CMediaType *pmt)
{
	BEGIN_METHOD
		if (!pmt)
			return E_INVALIDARG;

	if (pmt->majortype != MEDIATYPE_Video)
		return E_FAIL;
	END_METHOD
	return NOERROR;
}

HRESULT FilterInputPin::SetMediaType(const CMediaType *pmt)
{
	BEGIN_METHOD
		CAutoLock lock_it(m_pLock);
	HRESULT hr = NOERROR;

	WAVEFORMATEX	*wfx = (WAVEFORMATEX*)pmt->pbFormat;
	if (!wfx) return E_FAIL;
	if (nullptr != m_dataInfo)
	{
		return CBaseInputPin::SetMediaType(pmt);
	}
	if (nullptr != m_mediaTypeCallBack)
	{
// 		DataInfo videoInfo;
// 		VIDEOINFOHEADER	*pvi = (VIDEOINFOHEADER*)pmt->pbFormat;
// 		if (!pvi) return E_FAIL;
// 		videoInfo.bitmap.bmiHeader = pvi->bmiHeader;
// 		//todo 初始化媒体类型
// 		m_mediaTypeCallBack(m_pinName, &videoInfo);
	}
	
	hr = CBaseInputPin::SetMediaType(pmt);
	if (FAILED(hr))
		return hr;
	END_METHOD
}

HRESULT FilterInputPin::BreakConnect()
{
	m_isCompleteConnect = false;
	return NOERROR;
}

HRESULT FilterInputPin::CompleteConnect(IPin *pReceivePin)
{
	m_isCompleteConnect = true;
	return NOERROR;
}

STDMETHODIMP FilterInputPin::Receive(IMediaSample *pSample)
{
	if (nullptr != m_dataCallBack)
	{
		m_dataCallBack(m_pinName, pSample);
	}
	return NOERROR;
}

long FilterInputPin::RegMediaTypeCallBack(std::function<long(std::string, DataInfo*)> callback)
{
	m_mediaTypeCallBack = callback;
	return NOERROR;
}

long FilterInputPin::RegDataCallBack(std::function<long(std::string, IMediaSample*)> callback)
{
	m_dataCallBack = callback;
	return NOERROR;
}

long FilterInputPin::SetPinMediaType(DataInfo* pInputVideoInfo)
{
	if (nullptr == pInputVideoInfo)
	{
		return NOERROR;
	}
	if (nullptr == m_dataInfo)
	{
		m_dataInfo = new DataInfo;
	}
	memcpy(m_dataInfo, pInputVideoInfo, sizeof(DataInfo));
	return NOERROR;
}

long FilterInputPin::GetCompleteConnectState(bool& state)
{
	state = m_isCompleteConnect;
	return NOERROR;
}

long FilterInputPin::SetLogFileName(const char* fileName)
{
	std::string strFileName(fileName);
	return NOERROR;
}
