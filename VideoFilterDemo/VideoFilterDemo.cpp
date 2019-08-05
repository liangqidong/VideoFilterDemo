#include "VideoFilterDemo.h"

VideoFilterDemo::VideoFilterDemo(TCHAR *pName, LPUNKNOWN pUnk, HRESULT *phr)
	: CBaseFilter(FILTER_NAME, pUnk, this, CLSID_VideoFilter)
	, m_propertyPage(nullptr)
{
		if (nullptr == m_outputPin)
		{
			m_outputPin = new VideoFilterOutputPin(FILTER_NAME, this, this, phr, TEXT("outPin"));
			
			VideoInfo*pOutputPinVideoInfo = new VideoInfo;
			m_outputPin->SetVideoMediaType(pOutputPinVideoInfo);
		}
}

VideoFilterDemo::~VideoFilterDemo()
{

}

CUnknown * WINAPI VideoFilterDemo::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
	return new VideoFilterDemo(NAME("Audio Filter"), pUnk, phr);
}

STDMETHODIMP VideoFilterDemo::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
	CheckPointer(ppv, E_POINTER);
	if (riid == IID_ISpecifyPropertyPages) {
		return GetInterface((ISpecifyPropertyPages*)this, ppv);
	}
	if (riid == IID_VideoFilter)
	{
		return GetInterface((IVideoFilter*)this, ppv);
	}
	else
		return CBaseFilter::NonDelegatingQueryInterface(riid, ppv);
}

CBasePin * VideoFilterDemo::GetPin(int pinIndex)
{
	return m_outputPin;
}

int VideoFilterDemo::GetPinCount()
{
	return 1;
}

STDMETHODIMP VideoFilterDemo::Run(REFERENCE_TIME tStart)
{
	return CBaseFilter::Run(tStart);
}

STDMETHODIMP VideoFilterDemo::Pause()
{
	return  CBaseFilter::Pause();
}

STDMETHODIMP VideoFilterDemo::Stop()
{

	return CBaseFilter::Stop();
}

STDMETHODIMP VideoFilterDemo::GetPages(CAUUID *pPages)
{
	CheckPointer(pPages, E_POINTER);

	pPages->cElems = 1;
	pPages->pElems = (GUID *)CoTaskMemAlloc(sizeof(GUID));
	if (pPages->pElems == NULL) {
		return E_OUTOFMEMORY;
	}

	*(pPages->pElems) = CLSID_VideoFilterProp;
	return NOERROR;
}

void VideoFilterDemo::UpdatePage(int info_only)
{
	CAutoLock	lock(&m_lockInfo);
	if (m_propertyPage)
		m_propertyPage->Update(info_only);
}

STDMETHODIMP VideoFilterDemo::SetPropertyPage(IUnknown *pUnk)
{
	CAutoLock	lock(&m_lockInfo);
	if (m_propertyPage) {
		m_propertyPage->Release();
		m_propertyPage = NULL;
	}

	if (pUnk) {
		return pUnk->QueryInterface(IID_VideoFilterProp, (void**)&m_propertyPage);
	}
	return S_OK;
}

