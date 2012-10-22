#include "../common/StdAfx.h"
#include "../common/ImagesManager.h"

#include <initguid.h>
#include <imgguids.h>


CImagesManager *CImagesManager::m_pInstance = NULL;
CImagesManager* CImagesManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CImagesManager;
	}
	return m_pInstance;
}

CImagesManager::CImagesManager()
{

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance (CLSID_ImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IImagingFactory,
		(void **)&m_pImgFactory);
	m_pMapinfo = new MAP_IMAGE_INFO;

}

CImagesManager::~CImagesManager()
{
	_ASSERT(m_pMapinfo->size() == 0);
	m_pImgFactory->Release();
	CoUninitialize();
	delete m_pMapinfo;

}

BOOL CImagesManager::GetImageFromFile( const TCHAR* file,PARGBImageInfo* imageinfo )
{

	IImage *pImage                 = NULL;

	BOOL Result = TRUE;

	if (SUCCEEDED(m_pImgFactory->CreateImageFromFile(file, &pImage)))
	{
		ImageInfo imgInfo = {0};
		if (SUCCEEDED(pImage->GetImageInfo(&imgInfo)))
		{
			BitmapData bmpData           = {0};
			IBitmapImage *pBitmapImage = NULL;
			RECT rc                       = {0, 0, imgInfo.Width, imgInfo.Height};

			imageinfo->Width = imgInfo.Width;
			imageinfo->Height = imgInfo.Height;
			imageinfo->pixelformat = imgInfo.PixelFormat;

			// 如果图片的像素格式是PIXFMT_32BPP_PARGB 的则说明具备Alpha通道
			if(IsAlphaPixelFormat(imgInfo.PixelFormat))
			{
				DWORD formatid = PIXFMT_32BPP_PARGB;
				//if(imgInfo.PixelFormat == Format32bppArgb)
				//	formatid = PIXFMT_32BPP_PARGB;
				//else if(imgInfo.PixelFormat == Format24bppRgb)
				//	formatid = PixelFormat24bppRGB;

				if (SUCCEEDED(m_pImgFactory->CreateBitmapFromImage(pImage, 0, 0, formatid, 
					InterpolationHintDefault, &pBitmapImage)))
				{
					pBitmapImage->LockBits(&rc, ImageLockModeRead, formatid, &bmpData);
					imageinfo->hBitMap = CreateBitmap(imgInfo.Width, imgInfo.Height, 1, 
						GetPixelFormatSize(imgInfo.PixelFormat), bmpData.Scan0);
					if(imageinfo->hBitMap == NULL)
					{
						Result = FALSE;
					}

					pBitmapImage->UnlockBits(&bmpData);
					pBitmapImage->Release(); 

				}
				else
				{
					Result = FALSE;
				}
			}
			else
			{
				HDC hdc = ::GetDC(NULL);
				HDC memHdc = ::CreateCompatibleDC(hdc);
				imageinfo->hBitMap = CreateCompatibleBitmap(hdc,imgInfo.Width,imgInfo.Height);
				HGDIOBJ hOldBitmap=SelectObject(memHdc,imageinfo->hBitMap);
				RECT rect = { 0, 0, imgInfo.Width,imgInfo.Height};
				pImage->Draw(memHdc,&rect,NULL);

				SelectObject(memHdc, hOldBitmap);
				DeleteDC(memHdc);
				ReleaseDC(NULL,hdc);
			}
		}

		pImage->Release();
	}
	else
	{
		Result = FALSE;
	}

	return Result;
}

UINT CImagesManager::AddImage( const TCHAR* file )
{
	UINT ResID = GetAFreeID();

	PARGBImageInfo* imageinfo = (PARGBImageInfo*)::LocalAlloc(LPTR,sizeof(PARGBImageInfo));
	if(GetImageFromFile(file,imageinfo))
	{
		m_pMapinfo->insert(pair<UINT,PARGBImageInfo*>(ResID,imageinfo));
		return ResID;
	}

	LocalFree(imageinfo);//cyz 10/10/8 # 14 :08
	return 0;



}

BOOL CImagesManager::RemoveImage( UINT ResID )
{
	MAP_IMAGE_INFO::iterator iter=m_pMapinfo->find(ResID);
	if(iter!=m_pMapinfo->end())
	{
		PARGBImageInfo* info = (PARGBImageInfo*)iter->second;

		if(info && info->hBitMap)
		{
			DeleteObject(info->hBitMap);
		}
		LocalFree(info);

		m_pMapinfo->erase(iter);
		return TRUE;
	}
	else return FALSE;
}

BOOL CImagesManager::DrawAlphaImage( UINT ResID,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha/*=255*/ )
{
	MAP_IMAGE_INFO::iterator iter=m_pMapinfo->find(ResID);
	if(iter!=m_pMapinfo->end())
	{
		PARGBImageInfo* info = (PARGBImageInfo*)iter->second;
		if(info)
		{
			RECT SourceRECT;
			if(srcRC == NULL)
			{
				SourceRECT.left = 0; SourceRECT.top = 0;
				SourceRECT.right = info->Width; SourceRECT.bottom = info->Height;
			}
			else SourceRECT = *srcRC;

			DrawAlphaImage(info->hBitMap,info->pixelformat,destDC,&SourceRECT,destRC,Alpha);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CImagesManager::DrawAlphaImage( HBITMAP bmp,DWORD imgPixelformat,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha/*=255*/ )
{
	HDC hdcMem         = ::CreateCompatibleDC(NULL);
	HGDIOBJ hGdiObjOld = ::SelectObject(hdcMem, bmp);

	if(IsAlphaPixelFormat(imgPixelformat))
	{
		BLENDFUNCTION blendFunction = {0};
		blendFunction.AlphaFormat = AC_SRC_ALPHA;
		blendFunction.BlendFlags = 0;
		blendFunction.BlendOp = AC_SRC_OVER;
		blendFunction.SourceConstantAlpha = Alpha; 

		::AlphaBlend(destDC, destRC->left, destRC->top, 
			destRC->right-destRC->left, destRC->bottom-destRC->top, 
			hdcMem, srcRC->left, srcRC->top, 
			srcRC->right - srcRC->left, 
			srcRC->bottom - srcRC->top, blendFunction);
	}
	else
	{
		::StretchBlt(destDC,destRC->left,destRC->top,
			destRC->right-destRC->left, destRC->bottom-destRC->top, 
			hdcMem,srcRC->left, srcRC->top,srcRC->right-srcRC->left, srcRC->bottom-srcRC->top, SRCCOPY);
	}
	::SelectObject(hdcMem, hGdiObjOld);
	if (hdcMem)
	{
		DeleteDC(hdcMem);
		hdcMem = NULL;
	}
	return TRUE;
}

UINT CImagesManager::GetAFreeID()
{
	int retid = 1;

	MAP_IMAGE_INFO::iterator iter;

	for (iter = m_pMapinfo->begin();iter != m_pMapinfo->end();iter++)
	{
		if (retid == iter->first)
		{
			retid++;
		}
		else if (retid < iter->first)
		{
			break;
		}

	}
	_ASSERT(m_pMapinfo->find(retid) == m_pMapinfo->end());
	return retid;
}