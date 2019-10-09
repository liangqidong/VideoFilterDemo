#include "FilterPinPage.h"
#include "resource.h"

#ifndef COMMCTRL_H
#define COMMCTRL_H
#include <commctrl.h>
#pragma comment( lib, "comctl32.lib" )
#endif // !COMMCTRL_H


FilterPinPage::FilterPinPage(LPUNKNOWN punk, HRESULT *phr)
	: CBasePropertyPage(FILTER_PAGE_NAME, punk, IDD_DIALOG1, IDS_TITLE)
{

}

FilterPinPage::~FilterPinPage(void)
{

}

CUnknown* WINAPI FilterPinPage::CreateInstance(LPUNKNOWN pUnk, HRESULT* pHr)
{
	CUnknown *punk = new FilterPinPage(pUnk, pHr);

	if (NULL == punk)
	{
		*pHr = E_OUTOFMEMORY;
	}

	return punk;
}

//当对话框接收到窗口消息时被调用
INT_PTR FilterPinPage::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_hwnd = hwnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		char buff[128] = "1";
		SetWindowTextA(GetDlgItem(m_hwnd, IDC_OUTPUT_PIN_NUM), buff);
		SetWindowTextA(GetDlgItem(m_hwnd, IDC_INPUT_PIN_NUM), buff);
		SetDirty();
		break;
	}
	case WM_COMMAND:
	{
		if (wParam == IDC_PIN_NUM_SAVE)
		{
			ClickSavePinNum();
			Edit_Enable(GetDlgItem(m_hwnd, IDC_PIN_NUM_SAVE), false);
		}
			
// 		if (wParam == IDC_SAVE_OUTPUT_INFO)
// 			SetoutputInfo();
// 		if (wParam == IDC_SAVE_INPUT_INFO)
// 			SetoutputInfo();
		SetDirty();
		break;
	}
	}
	return CBasePropertyPage::OnReceiveMessage(hwnd, uMsg, wParam, lParam);
}

//当属性页创建的时候，会调用这个方法，通过这个方法将IUnknown指针付给Filter。
HRESULT FilterPinPage::OnConnect(IUnknown *pUnknown)
{
	CheckPointer(pUnknown, E_POINTER);
	return pUnknown->QueryInterface(IID_FilterPin,
		reinterpret_cast<void **>(&m_filterPin));
}

//当用户取消Property sheet时调用
HRESULT FilterPinPage::OnDisconnect()
{

	return S_OK;
}

//当对话框创建的时候被调用
HRESULT FilterPinPage::OnActivate()
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

//当用户单击OK或者Apply 按钮来确认对属性进行更新时，调用
HRESULT FilterPinPage::OnApplyChanges()
{
	return S_OK;
}

void FilterPinPage::SetDirty()
{
	m_bDirty = TRUE;
	if (m_pPageSite)
	{
		m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
	}
}

void FilterPinPage::ClickSavePinNum()
{
	Edit_Enable(GetDlgItem(m_hwnd, IDC_INPUT_PIN_NUM), false);
	Edit_Enable(GetDlgItem(m_hwnd, IDC_OUTPUT_PIN_NUM), false);
	char buff[128] = {0};
	GetWindowTextA(
		GetDlgItem(m_hwnd, IDC_OUTPUT_PIN_NUM),
		buff,
		128);
	int outputNum = atol(buff);
	memset(buff, 0, 128);
	GetWindowTextA(
		GetDlgItem(m_hwnd, IDC_INPUT_PIN_NUM),
		buff,
		128);
	int inputNum = atol(buff);
	char buff1[10] = "input1";
	char buff2[10] = "input2";
	char buff3[10] = "input3";
	char buff4[10] = "input4";
	char buff5[10] = "input5";
	char buff6[10] = "input6";
	char buff7[10] = "input7";
	char buff8[10] = "input8";
	const char* const inputname[8] = { buff1 ,buff2  ,buff3 ,buff4 ,buff5 ,buff6 ,buff7 ,buff8 };
	char outbuff1[10] = "output1";
	char outbuff2[10] = "output2";
	char outbuff3[10] = "output3";
	char outbuff4[10] = "output4";
	char outbuff5[10] = "output5";
	char outbuff6[10] = "output6";
	char outbuff7[10] = "output7";
	char outbuff8[10] = "output8";

	const char* const outputname[8] = { outbuff1 ,outbuff2  ,outbuff3 ,outbuff4 ,outbuff5 ,outbuff6  ,outbuff7 ,outbuff8 };
	Pin pin;
	pin.inputPinNum = inputNum;
	pin.outputPinNum = outputNum;
	pin.inputPinNameArr = inputname;
	pin.outputPinNameArr = outputname;
	m_filterPin->SetInputAndOutputNum(&pin);
}
