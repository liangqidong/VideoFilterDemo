#ifndef VIDEO_FILTER_PROPERTY_PAGE_H_
#define VIDEO_FILTER_PROPERTY_PAGE_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

	//db8cf8e6-b8ff-48a2-b0a8-21d72729c09c
	static const GUID IID_VideoFilterProp =
	{ 0xdb8cf8e6, 0xb8ff, 0x48a2,{ 0xb0, 0xa8, 0x21, 0xd7, 0x27, 0x29, 0xc0, 0x9c } };

	//db8cf8e6-b8ff-48a2-b0a8-21d72729c09c
	static const GUID CLSID_VideoFilterProp =
	{ 0xdb8cf8e6, 0xb8ff, 0x48a2,{ 0xb0, 0xa8, 0x21, 0xd7, 0x27, 0x29, 0xc0, 0x9c } };

	DECLARE_INTERFACE_(IVideoPropertyPage, IUnknown)
	{
		STDMETHOD(Update)(int info_only) PURE;
	};

#ifdef __cplusplus
}
#endif
#endif//VIDEO_FILTER_PROPERTY_PAGE_H_



