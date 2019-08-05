
#ifndef VIDEO_FILTER_H_
#define VIDEO_FILTER_H_

#ifndef _STREAMS_H_
#define _STREAMS_H_
#include <streams.h>
#endif//_STREAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

	// {B359F5E7-4119-4C01-89F5-5567DE085960}
	static const GUID IID_VideoFilter =
	{ 0xb359f5e7, 0x4119, 0x4c01,{ 0x89, 0xf5, 0x55, 0x67, 0xde, 0x8, 0x59, 0x60 } };

	// {633FC39C-A74F-4DA9-B7A9-3EB68614E8A8}
	static const GUID CLSID_VideoFilter =
	{ 0x633fc39c, 0xa74f, 0x4da9,{ 0xb7, 0xa9, 0x3e, 0xb6, 0x86, 0x14, 0xe8, 0xa8 } };


	DECLARE_INTERFACE_(IVideoFilter, IUnknown)
	{
	
	};

#ifdef __cplusplus
}
#endif //DECLARE_INTERFACE_


#endif //VIDEO_FILTER_H_