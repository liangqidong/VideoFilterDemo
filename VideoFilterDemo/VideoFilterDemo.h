#pragma once

#include "IVideoFilter.h"
#include "IVideoFilterPropertyPage.h"
#include "VideoFilterInputPin.h"
#include "VideoFilterOutputPin.h"

#define FILTER_NAME TEXT("Video Filter")
#include <iostream>

class VideoFilterDemo
	: public CBaseFilter
	, public CCritSec
	, public IVideoFilter
	, public ISpecifyPropertyPages
{
public:
	
	VideoFilterDemo(TCHAR *pName, LPUNKNOWN pUnk, HRESULT *phr);
	~VideoFilterDemo();
	DECLARE_IUNKNOWN
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);
	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);
	CBasePin *GetPin(int n);
	int GetPinCount();

	STDMETHODIMP Run(REFERENCE_TIME tStart);
	STDMETHODIMP Pause();
	STDMETHODIMP Stop();

	STDMETHODIMP GetPages(CAUUID *pPages);
	void UpdatePage(int info_only);
	STDMETHODIMP SetPropertyPage(IUnknown *pUnk);

private:
	HRESULT*							m_phr;
	CCritSec							m_lockInfo;
	IVideoPropertyPage*					m_propertyPage;
	VideoFilterOutputPin*				m_outputPin;
};

