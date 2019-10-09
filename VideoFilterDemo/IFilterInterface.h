#ifndef FILTER_INTERFACE_H_
#define FILTER_INTERFACE_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IID_FILTER_INTERFACE
#define IID_FILTER_INTERFACE
	// {7cf87cb4-2372-4464-bccc-920483785e14}
	static const GUID IID_FilterInterface =
	{ 0x7cf87cb4, 0x2372, 0x4464,{ 0xbc, 0xcc, 0x92, 0x04, 0x83, 0x78, 0x5e, 0x14 } };
#endif//IID_FILTER_INTERFACE

#ifndef CLSID_FILTER
#define CLSID_FILTER
	// {633FC39C-A74F-4DA9-B7A9-3EB68614E8A8}
	static const GUID CLSID_Filter =
	{ 0x633fc39c, 0xa74f, 0x4da9,{ 0xb7, 0xa9, 0x3e, 0xb6, 0x86, 0x14, 0xe8, 0xa8 } };
#endif//CLSID_Filter


	DECLARE_INTERFACE_(IFilterInterface, IUnknown)
	{
		
	};

#ifdef __cplusplus
}
#endif //DECLARE_INTERFACE_


#endif //FILTER_INTERFACE_H_