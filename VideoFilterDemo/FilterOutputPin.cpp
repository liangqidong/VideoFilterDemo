#include "FilterOutputPin.h"

#include <string>

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

FilterOutputPin::FilterOutputPin(TCHAR *pObjName, CBaseFilter *pFilter, CCritSec *pLock, HRESULT *phr, LPCWSTR pPinName)
	: CBaseOutputPin(pObjName, pFilter, pLock, phr, pPinName)
	, m_dataInfo(nullptr)
	, m_isCompleteConnect(FALSE)
{

}


FilterOutputPin::~FilterOutputPin()
{

	if (nullptr != m_dataInfo)
	{
		delete m_dataInfo;
		m_dataInfo = nullptr;
	}

}

HRESULT FilterOutputPin::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	BEGIN_METHOD
		if (iPosition < 0)
			return E_INVALIDARG;
	if (iPosition > 0)
		return VFW_S_NO_MORE_ITEMS;
// 	if (nullptr != m_dataInfo)
// 	{
// 		VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER*)pMediaType->AllocFormatBuffer(sizeof(*pvi));
// 
// 		pvi->bmiHeader.biCompression = 0x3231564E;
// 		pvi->bmiHeader.biBitCount = 16;
// 		pvi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
// 		pvi->bmiHeader.biWidth = 1920;
// 		pvi->bmiHeader.biHeight = 1080;
// 		pvi->bmiHeader.biPlanes = 1;
// 		pvi->bmiHeader.biSizeImage = pvi->bmiHeader.biWidth*pvi->bmiHeader.biHeight * pvi->bmiHeader.biBitCount / 8;;
// 		pvi->bmiHeader.biXPelsPerMeter = 0;
// 		pvi->bmiHeader.biYPelsPerMeter = 0;
// 		pvi->bmiHeader.biClrUsed = 0;
// 		pvi->bmiHeader.biClrImportant = 0;
// 		pvi->AvgTimePerFrame = 333333;
// 		RECT rect;
// 		rect.left = 0;
// 		rect.bottom = 0;
// 		rect.right = 0;
// 		rect.top = 0;
// 		 
// 		pvi->rcSource = rect;
// 		pvi->rcTarget = rect;
// 		pvi->dwBitRate = 147456000;
// 		pvi->dwBitErrorRate = 0;
// 		const GUID SubTypeGUID = GetBitmapSubtype(&pvi->bmiHeader);
// 		pMediaType->SetSubtype(&SubTypeGUID);
// 		pMediaType->SetSampleSize(pvi->bmiHeader.biSizeImage);
// 		pMediaType->SetType(&MEDIATYPE_Video);
// 		pMediaType->SetTemporalCompression(FALSE);
// 		pMediaType->SetFormatType(&FORMAT_VideoInfo);
// 		pMediaType->cbFormat = 88;
// 	}
	END_METHOD
}

HRESULT FilterOutputPin::CheckMediaType(const CMediaType *pmt)
{

	BEGIN_METHOD
		if (!pmt)
			return E_INVALIDARG;

	if (pmt->majortype != MEDIATYPE_Video)
		return E_FAIL;

	END_METHOD
}

HRESULT FilterOutputPin::DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES * pProp)
{
	HRESULT hr = NOERROR;

	VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)m_mt.Format();
	pProp->cBuffers = 1;
	pProp->cbBuffer = pvi->bmiHeader.biSizeImage;

	ALLOCATOR_PROPERTIES Actual;
	hr = pAlloc->SetProperties(pProp, &Actual);

	if (FAILED(hr)) return hr;
	if (Actual.cbBuffer < pProp->cbBuffer) return E_FAIL;

	return hr;
}

HRESULT FilterOutputPin::CompleteConnect(IPin *pReceivePin)
{
	m_isCompleteConnect = true;
	return CBaseOutputPin::CompleteConnect(pReceivePin);
}

HRESULT FilterOutputPin::BreakConnect()
{
	m_isCompleteConnect = false;
	return CBaseOutputPin::BreakConnect();
}

HRESULT FilterOutputPin::Deliver(IMediaSample *pMediaSample)
{
	return CBaseOutputPin::Deliver(pMediaSample);
}

long FilterOutputPin::SetPinMediaType(DataInfo* pOutputPinVideoInfo)
{
	if (nullptr == m_dataInfo)
	{
		m_dataInfo = new DataInfo;
	}
	memcpy(m_dataInfo, pOutputPinVideoInfo, sizeof(DataInfo));
	return NOERROR;
}

long FilterOutputPin::GetPinCompleteConnectState(bool& state)
{
	state = m_isCompleteConnect;
	return NOERROR;
}

long FilterOutputPin::SetLogFileName(const char* fileName)
{
	std::string strFileName(fileName);
	return NOERROR;
}
