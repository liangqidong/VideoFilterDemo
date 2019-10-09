#ifndef FILTER_H
#define FILTER_H

#include "IFilterPin.h"
#include "IFilterInterface.h"
#include "IVideoFilterPropertyPage.h"
#include "FilterInputPin.h"
#include "FilterOutputPin.h"

#define FILTER_NAME TEXT("Filter")
#include <iostream>
#include <map>
#include <mutex>

class FilterDemo
	: public CBaseFilter
	, public CCritSec
	, public IFilterPin
	, public IFilterInterface
	, public ISpecifyPropertyPages
{
public:
	
	FilterDemo(TCHAR *pName, LPUNKNOWN pUnk, HRESULT *phr);
	~FilterDemo();
	DECLARE_IUNKNOWN
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);
	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);
	CBasePin *GetPin(int n);
	int GetPinCount();
	STDMETHODIMP GetPages(CAUUID *pPages);
	
	STDMETHODIMP Run(REFERENCE_TIME tStart);
	STDMETHODIMP Pause();
	STDMETHODIMP Stop();

	//PIN module
	STDMETHODIMP SetInputAndOutputNum(const Pin* pin);
	STDMETHODIMP SetInputPinInfo(const unsigned int pinidex, const DataInfo* dataInfo);
	STDMETHODIMP SetoutputPinInfo(const unsigned int pinidex, const DataInfo* dataInfo);

	//interface module

private:
	long Receive(std::string pinName, IMediaSample* sample);
	long SetMediaType(std::string pinName, DataInfo* dataInfo);
	
	std::map<int, FilterOutputPin*>		m_outputPinMap;
	std::map<int, FilterInputPin*>		m_inputPinMap;
	std::map<std::string, int>			m_inputPinNameAndIdMap;
	std::map<std::string, int>			m_outputPinNameAndIdMap;
	std::mutex							m_mutex;
};
#endif//FILTER_H

