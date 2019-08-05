#include "VideoFilterDemoPage.h"
#include "resource.h"

#ifndef COMMCTRL_H
#define COMMCTRL_H
#include <commctrl.h>
#pragma comment( lib, "comctl32.lib" )
#endif // !COMMCTRL_H


VideoFilterDemoPage::VideoFilterDemoPage(LPUNKNOWN punk, HRESULT *phr)
	: CBasePropertyPage(FILTER_PAGE_NAME, punk, IDD_DIALOG1, IDS_TITLE)
{

}

VideoFilterDemoPage::~VideoFilterDemoPage(void)
{

}

CUnknown* WINAPI VideoFilterDemoPage::CreateInstance(LPUNKNOWN pUnk, HRESULT* pHr)
{
	CUnknown *punk = new VideoFilterDemoPage(pUnk, pHr);

	if (NULL == punk)
	{
		*pHr = E_OUTOFMEMORY;
	}

	return punk;
}

//���Ի�����յ�������Ϣʱ������
INT_PTR VideoFilterDemoPage::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_hwnd = hwnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		SetDirty();
		break;
	}
	case WM_COMMAND:
	{

		SetDirty();
		break;
	}
	}
	return CBasePropertyPage::OnReceiveMessage(hwnd, uMsg, wParam, lParam);
}

//������ҳ������ʱ�򣬻�������������ͨ�����������IUnknownָ�븶��Filter��
HRESULT VideoFilterDemoPage::OnConnect(IUnknown *pUnknown)
{
	CheckPointer(pUnknown, E_POINTER);
	return pUnknown->QueryInterface(IID_VideoFilter,
		reinterpret_cast<void **>(&m_videoFilter));
}

//���û�ȡ��Property sheetʱ����
HRESULT VideoFilterDemoPage::OnDisconnect()
{

	return S_OK;
}

//���Ի��򴴽���ʱ�򱻵���
HRESULT VideoFilterDemoPage::OnActivate()
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_BAR_CLASSES;
	if (InitCommonControlsEx(&icc) == FALSE)
	{
		return E_FAIL;
	}
	return S_OK;
}

//���û�����OK����Apply ��ť��ȷ�϶����Խ��и���ʱ������
HRESULT VideoFilterDemoPage::OnApplyChanges()
{
	return S_OK;
}

void VideoFilterDemoPage::SetDirty()
{
	m_bDirty = TRUE;
	if (m_pPageSite)
	{
		m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
	}
}