#ifndef DDAY_IMAGESMANAGER_H
#define DDAY_IMAGESMANAGER_H

#pragma once

#include <imaging.h>
#include "DllDefine.h"

typedef struct _tagPARGBImageInfo
{
	UINT Width;             // the Width of the image
	UINT Height;            // the Height of the image
	DWORD pixelformat;      // the pixelformat of the image
	HBITMAP hBitMap;        // the Handle of the PARGB image 
}PARGBImageInfo;



class CE_CONTROL_API CImagesManager
{
public:
	static CImagesManager* GetInstance();
	virtual ~CImagesManager();  

	BOOL GetImageFromFile( const TCHAR* file,PARGBImageInfo* imageinfo );
	HANDLE AddImage(const TCHAR* file);
	BOOL RemoveImage(HANDLE ResID);
	BOOL DrawAlphaImage(HANDLE ResID,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha=255);
	BOOL DrawAlphaImage(HBITMAP bmp,DWORD imgPixelformat,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha=255);
private:
	CImagesManager();
	static CImagesManager *m_pInstance;
	IImagingFactory *m_pImgFactory;
};

#endif