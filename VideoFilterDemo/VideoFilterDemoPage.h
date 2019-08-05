#pragma once
#ifndef WINDOWS_H
#define WINDOWS_H
#include <windows.h>
#endif//WINDOWS_H

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifndef CPROP_H
#define CPROP_H
#include "cprop.h"
#endif//CPROP_H

#include "IVideoFilter.h"


#define FILTER_PAGE_NAME NAME("Page")
class VideoFilterDemoPage
	: public CBasePropertyPage
{
public:
	VideoFilterDemoPage(LPUNKNOWN punk, HRESULT *phr);
	~VideoFilterDemoPage(void);

	static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);
	INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT OnConnect(IUnknown *pUnknown);
	HRESULT OnDisconnect();
	HRESULT OnActivate();
	HRESULT OnApplyChanges();
	void SetDirty();

private:
	IVideoFilter*			m_videoFilter;
};

