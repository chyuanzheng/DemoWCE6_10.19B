#ifndef DDAY_IMAGESMANAGER_H
#define DDAY_IMAGESMANAGER_H

#pragma once

#include <imaging.h>

typedef struct _tagPARGBImageInfo
{
	UINT Width;             // the Width of the image
	UINT Height;            // the Height of the image
	DWORD pixelformat;      // the pixelformat of the image
	HBITMAP hBitMap;        // the Handle of the PARGB image 
}PARGBImageInfo;

typedef map<int,PARGBImageInfo*>  MAP_IMAGE_INFO;

class CImagesManager
{
public:
	static CImagesManager* GetInstance();
	virtual ~CImagesManager();  
	
    BOOL GetImageFromFile( const TCHAR* file,PARGBImageInfo* imageinfo );
	UINT AddImage(const TCHAR* file);
	BOOL RemoveImage(UINT ResID);
	BOOL DrawAlphaImage(UINT ResID,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha=255);
	BOOL DrawAlphaImage(HBITMAP bmp,DWORD imgPixelformat,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha=255);
private:
	CImagesManager();
	UINT GetAFreeID();
	MAP_IMAGE_INFO m_mapinfo;
	static CImagesManager *m_pInstance;
	IImagingFactory *m_pImgFactory;
};

#endif