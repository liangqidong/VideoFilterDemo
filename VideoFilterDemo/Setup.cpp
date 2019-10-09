#ifdef _WIN32

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif

#include <initguid.h>
#include <tchar.h>

#include "FilterDemo.h"
#include "FilterPinPage.h"

const AMOVIESETUP_MEDIATYPE OutputVideoPinTypes =
{
	&MEDIATYPE_Video,
	&MEDIASUBTYPE_NULL
};

const AMOVIESETUP_PIN outputVideoPin =
{
	L"Output",
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	&CLSID_NULL,
	NULL,
	1,
	&OutputVideoPinTypes
};

const AMOVIESETUP_MEDIATYPE OutputAudioPinTypes =
{
	&MEDIATYPE_Audio,
	&MEDIASUBTYPE_PCM
};

const AMOVIESETUP_PIN outputAudioPin =
{
	L"Output",
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	&CLSID_NULL,
	NULL,
	1,
	&OutputAudioPinTypes
};

const AMOVIESETUP_PIN outputPins[] =
{
	{
		L"Output",
		FALSE,
		TRUE,
		FALSE,
		FALSE,
		&CLSID_NULL,
		NULL,
		/*1*/0,
		NULL
		/*&OutputVideoPinTypes*/
	}
};

const AMOVIESETUP_FILTER Capture =
{
	&CLSID_Filter,
	FILTER_NAME,
	MERIT_NORMAL,
	0,
	NULL
};

CFactoryTemplate g_Templates[] =
{
	{
		FILTER_NAME,
		&CLSID_Filter,
		FilterDemo::CreateInstance,
		NULL,
		&Capture
	},

	{
		FILTER_PAGE_NAME,
		&CLSID_FilterProp,
		FilterPinPage::CreateInstance,
		NULL,
		NULL
	},
};

int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);


STDAPI DllRegisterServer()
{
	return AMovieDllRegisterServer2(TRUE);
}

STDAPI DllUnregisterServer()
{
	return AMovieDllRegisterServer2(FALSE);
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);


BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  dwReason,
	LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}


#endif