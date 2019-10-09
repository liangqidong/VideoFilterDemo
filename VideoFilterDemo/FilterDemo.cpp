#include "FilterDemo.h"

#ifndef BEGIN_FILTER_INTERFACE
#define BEGIN_FILTER_INTERFACE\
	long returnValue = S_OK;\
	char* errorMsg = nullptr;\
	HRESULT codyy_methodresult = S_OK;\
	try\
	{
#endif//BEGIN_FILTER_INTERFACE
#ifndef ERROR_RETURN_FILTER_INTERFACE
#define ERROR_RETURN_FILTER_INTERFACE\
	goto RETURN
#endif//ERROR_RETURN_FILTER_INTERFACE

#ifndef END_FILTER_INTERFACE
#define END_FILTER_INTERFACE\
	}\
	catch (HRESULT & resultException)\
	{\
	codyy_methodresult = resultException;\
	}\
	catch (...)\
	{\
	codyy_methodresult = E_FAIL;\
	}\
RETURN:\
return returnValue
#endif//END_FILTER_INTERFACE

FilterDemo::FilterDemo(TCHAR *pName, LPUNKNOWN pUnk, HRESULT *phr)
	: CBaseFilter(FILTER_NAME, pUnk, this, CLSID_Filter)
{

}

FilterDemo::~FilterDemo()
{
	for (auto t = m_outputPinMap.begin(); t != m_outputPinMap.end(); t++)
	{
		if (t->second)
		{
			delete t->second;
			t->second = nullptr;
		}
	}
	m_outputPinMap.clear();
	m_outputPinNameAndIdMap.clear();

	for (auto t = m_inputPinMap.begin(); t != m_inputPinMap.end(); t++)
	{
		if (t->second)
		{
			delete t->second;
			t->second = nullptr;
		}
	}
	m_inputPinMap.clear();
	m_inputPinNameAndIdMap.clear();
}

CUnknown * WINAPI FilterDemo::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
	return new FilterDemo(NAME("Audio Filter"), pUnk, phr);
}

STDMETHODIMP FilterDemo::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
	CheckPointer(ppv, E_POINTER);
	if (riid == IID_ISpecifyPropertyPages)
	{
		return GetInterface((ISpecifyPropertyPages*)this, ppv);
	}

	if (riid == IID_FilterPin)
	{
		return GetInterface((IFilterPin*)this, ppv);
	}

	if (riid == IID_FilterInterface)
	{
		return GetInterface((IFilterInterface*)this, ppv);
	}
	
	return CBaseFilter::NonDelegatingQueryInterface(riid, ppv);
}

CBasePin * FilterDemo::GetPin(int pinIndex)
{
	if (pinIndex > m_outputPinMap.size() + m_inputPinMap.size()
		|| pinIndex < 0)
	{
		return ERROR;
	}

	if (pinIndex < m_inputPinMap.size())
	{
		auto inputPinItor = m_inputPinMap.find(pinIndex);
		if (m_inputPinMap.end() == inputPinItor)
		{
			return nullptr;
		}
		return inputPinItor->second;
	}
	int outpinIndex = pinIndex - m_inputPinMap.size();
	auto outputPinItor = m_outputPinMap.find(outpinIndex);
	if (m_outputPinMap.end() == outputPinItor)
	{
		return nullptr;
	}
	return outputPinItor->second;
}

int FilterDemo::GetPinCount()
{
	return m_outputPinMap.size() + m_inputPinMap.size();
}

STDMETHODIMP FilterDemo::Run(REFERENCE_TIME tStart)
{
	return CBaseFilter::Run(tStart);
}

STDMETHODIMP FilterDemo::Pause()
{
	return  CBaseFilter::Pause();
}

STDMETHODIMP FilterDemo::Stop()
{

	return CBaseFilter::Stop();
}

STDMETHODIMP FilterDemo::GetPages(CAUUID *pPages)
{
	CheckPointer(pPages, E_POINTER);

	pPages->cElems = 1;
	pPages->pElems = (GUID *)CoTaskMemAlloc(sizeof(GUID));
	if (pPages->pElems == NULL) {
		return E_OUTOFMEMORY;
	}

	*(pPages->pElems) = CLSID_FilterProp;
	return NOERROR;
}

STDMETHODIMP FilterDemo::SetInputAndOutputNum(const Pin* pin)
{
	BEGIN_FILTER_INTERFACE;
	if (nullptr == pin)
	{
		returnValue = E_FAIL;
		errorMsg = "pin parameter error";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	unsigned int inputpinNum = pin->inputPinNum;
	const char*const* const inputPinNameArr = pin->inputPinNameArr;
	for (size_t i = 0; i < inputpinNum; i++)
	{
		char* pszMultiByte = (char*)inputPinNameArr[i];
		wchar_t pinName[MAX_PIN_NAME] = { 0 };
		swprintf(pinName, MAX_PIN_NAME, L"%hs", pszMultiByte);
		HRESULT hr = S_OK;
		m_inputPinMap.insert(std::pair<int, FilterInputPin*>(i, new FilterInputPin(FILTER_NAME, this, this, &hr, pinName)));
		if (!SUCCEEDED(hr))
		{
			returnValue = hr;
			errorMsg = "CBasePin create error";
			ERROR_RETURN_FILTER_INTERFACE;
		}
		m_inputPinMap[i]->RegMediaTypeCallBack(std::bind(&FilterDemo::SetMediaType, this, std::placeholders::_1, std::placeholders::_2));
		m_inputPinMap[i]->RegDataCallBack(std::bind(&FilterDemo::Receive, this, std::placeholders::_1, std::placeholders::_2));
		m_inputPinNameAndIdMap.insert(std::pair<std::string, int>(pszMultiByte, i));
	}

	unsigned int outputpinNum = pin->outputPinNum;
	const char*const* const outputNameArr = pin->outputPinNameArr;
	for (size_t i = 0; i < inputpinNum; i++)
	{
		char* pszMultiByte = (char*)outputNameArr[i];
		wchar_t pinName[MAX_PIN_NAME] = { 0 };
		swprintf(pinName, MAX_PIN_NAME, L"%hs", pszMultiByte);
		HRESULT hr = S_OK;
		m_outputPinMap.insert(std::pair<int, FilterOutputPin*>(i, new FilterOutputPin(FILTER_NAME, this, this, &hr, pinName)));
		if (!SUCCEEDED(hr))
		{
			returnValue = hr;
			errorMsg = "CBasePin create error";
			ERROR_RETURN_FILTER_INTERFACE;
		}
		m_outputPinNameAndIdMap.insert(std::pair<std::string, int>(pszMultiByte, i));
	}
	END_FILTER_INTERFACE;
}

STDMETHODIMP FilterDemo::SetInputPinInfo(const unsigned int pinidex, const DataInfo* dataInfo)
{
	BEGIN_FILTER_INTERFACE;
	if (nullptr == dataInfo)
	{
		returnValue = E_FAIL;
		errorMsg = "dataInfo parameter error";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	auto iterator = m_inputPinMap.find(pinidex);
	if (m_inputPinMap.end() == iterator)
	{
		returnValue = E_FAIL;
		errorMsg = "pinidex does not exist in m_inputPinMap";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	if (nullptr == iterator->second)
	{
		returnValue = E_FAIL;
		errorMsg = "pinidex exists in m_inputPinMap, but inputPin pointer does not exist";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	returnValue = iterator->second->SetPinMediaType(const_cast<DataInfo*>(dataInfo));

	END_FILTER_INTERFACE;
}

STDMETHODIMP FilterDemo::SetoutputPinInfo(const unsigned int pinidex, const DataInfo* dataInfo)
{
	BEGIN_FILTER_INTERFACE;
	if (nullptr  == dataInfo)
	{
		returnValue = E_FAIL;
		errorMsg = "dataInfo parameter error";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	auto iterator = m_outputPinMap.find(pinidex);
	if (m_outputPinMap.end() == iterator)
	{
		returnValue = E_FAIL;
		errorMsg = "pinidex does not exist in m_outputPinMap";
		ERROR_RETURN_FILTER_INTERFACE;
	}
	if (nullptr == iterator->second)
	{
		returnValue = E_FAIL;
		errorMsg = "pinidex exists in m_outputPinMap, but outputPin pointer does not exist";
		ERROR_RETURN_FILTER_INTERFACE;
	}

	returnValue = iterator->second->SetPinMediaType(const_cast<DataInfo*>(dataInfo));

	END_FILTER_INTERFACE;
}

long FilterDemo::Receive(std::string pinName, IMediaSample* sample)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	return S_OK;
}

long FilterDemo::SetMediaType(std::string pinName, DataInfo* dataInfo)
{

	return S_OK;
}
