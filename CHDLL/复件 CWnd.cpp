#include "StdAfx.h"
#include "CWnd.h"
//#include "resource.h"
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
#define  DEF_WNDCLASS    L"CHNiHao"
CWnd *CWnd::m_pWindow=NULL;
CWnd::CWnd()
{
    m_hWnd = NULL;

    m_nExitCode = 0;
	m_lpddclipper = NULL;
	m_backSurface = NULL;
	m_primarySurface = NULL;
	m_ddraw = NULL;
	m_pClipRect = new V_RECT; 
}
CWnd::~CWnd()
{
	delete m_pClipRect;
    AfxDelHWnd(m_hWnd);
	if (m_lpddclipper)
	{
		m_lpddclipper->Release();
	}
	if (m_backSurface)
	{
		m_backSurface->Release();
	}
	if (m_primarySurface)
	{
		m_primarySurface->Release();
	}
	if (m_ddraw)
	{
		m_ddraw->Release();
	}
	
}
HWND CWnd::GetSafeHwnd()
{
    return m_hWnd;
}


BOOL CWnd::Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName,DWORD dwStyle,const RECT& rect,HWND hWndParent,UINT nID)
{
	//if( !RegisterWindow( lpszClassName ) )
	//{
	//	MessageBox( NULL, _T("Can not register class"), _T("!"), MB_OK );
	//	return FALSE;
	//}
    static BOOL bReg = 0;
    if(lpszClassName == NULL)
    {
        lpszClassName = DEF_WNDCLASS;
        if(!bReg)//保证只注册一次
        {
            RegisterWindow( lpszClassName );
            bReg = 1;
        }
    }
	if( ::IsWindow( m_hWnd ) )
		return FALSE;


    m_hWnd =::CreateWindowEx(NULL, lpszClassName, lpszWindowName, dwStyle,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		hWndParent, NULL, AfxGetInstanceHandle(),NULL);
  
	if (IsWindow(m_hWnd))
	{

		//if(InitDirectDraw(TRUE))
		{
			DDSURFACEDESC ddsd;
			
			if (FAILED(DirectDrawCreate(NULL, &m_ddraw, NULL)))
				return(0);
			// set cooperation to full screen
			if (FAILED(m_ddraw->SetCooperativeLevel(m_hWnd, 
				DDSCL_NORMAL)))
				return(0);


			// clear ddsd and set size
			DDRAW_INIT_STRUCT(ddsd); 

			// enable valid fields
			ddsd.dwFlags = DDSD_CAPS;

			// request a complex, flippable
			ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

			// create the primary surface
			if (FAILED(m_ddraw->CreateSurface(&ddsd, &m_primarySurface, NULL)))
				return(0);

			m_backSurface = DDraw_Create_Surface(rect.right - rect.left, rect.bottom - rect.top,0,-1);


			//m_lpddclipper = DDraw_Attach_Clipper(m_backSurface,1,&rect);
			if(FAILED(m_ddraw->CreateClipper(0,&m_lpddclipper,NULL)))
				return false;
			//else
			//{
			//	//m_lpddclipper->SetHWnd(0,m_hWnd);
			//	//m_lpddclipper->SetClipList()
			//	//m_backSurface->SetClipper(m_lpddclipper);
			//}

		}

		
		m_pWindow = this;

        m_rect =  rect;
        AfxAddHWnd(m_hWnd,this);
		return TRUE;
	}
	return FALSE;
}
BOOL CWnd::ShowWindow(int nCmdShow)
	{ _ASSERT(::IsWindow(m_hWnd)); return ::ShowWindow(m_hWnd, nCmdShow); }
void CWnd::Invalidate(BOOL bErase)
	{ _ASSERT(::IsWindow(m_hWnd)); ::InvalidateRect(m_hWnd, NULL, bErase); }
void CWnd::UpdateWindow()
	{ _ASSERT(::IsWindow(m_hWnd)); ::UpdateWindow(m_hWnd); }
void CWnd::PostNcDestroy()
{
	// default to nothing
}

BOOL CWnd::RegisterWindow(LPCTSTR lpClassName)
{
	//为防止此类已经被注册过，先销毁注册
	//::UnregisterClass( lpClassName, GetModuleHandle(NULL) );

	//设置窗体类属性
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = lpClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hbrBackground = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;

	return RegisterClass(&wndclass);
}
LRESULT CALLBACK CWnd::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//调用窗口类的回调函数
   CWnd *pCWnd = AfxGetCWnd(hWnd);
   if(pCWnd == NULL)
   {
        return ::DefWindowProc(hWnd, nMsg, wParam, lParam);;
   }
   switch( nMsg )
   {
   case WM_EXIT_PROSS:
	   return ::DestroyWindow(pCWnd->m_hWnd);
   case WM_DESTROY://
	   PostQuitMessage(pCWnd->m_nExitCode);
	   //#ifndef CH_CE_DEBUG
	   //	   return 0; 
	   //   case WM_NCDESTROY:
	   //#endif
	   pCWnd->PostNcDestroy();
	   return 0; 
   default:
	   break;
   }

   return pCWnd->WindowProc( nMsg, wParam, lParam );
}
LRESULT CWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    BaseBoard* db = AfxGetBoard(m_hWnd);
    if (db ==NULL)
    {
		return 0;
    }
	if (AfxTestNewBoard(m_hWnd) == TRUE)
	{
		db->AdjustRect(0,0);
	}
	switch( message )
	{
         case WM_PAINT:
             OnPaint();
            return 0;
		default:
			break;
	}
	
    if(db->DealCtrlMsg(m_hWnd, message, wParam, lParam))
    {
        return 0;
    }   
    return ::DefWindowProc(m_hWnd, message, wParam, lParam);
};
void  CWnd::SetShowEffect(BOARD_EFFECT effect)
{
}
void  CWnd::OnPaint()
{
    BaseBoard* db = AfxGetBoard(m_hWnd);
	list<BaseBoard*> boards; 
	boards.push_front(db);
	while (db->IsDomodal())
	{
		db = db->GetParentBoard();
		_ASSERT(db != NULL);
		boards.push_front(db);//从父窗口开始绘图
	}
    PAINTSTRUCT ps;
	
    HDC hdc = ::BeginPaint( m_hWnd, &ps );
	HDC hdcDest;
	if (m_pClipRect->size()>0)
	{
		DDraw_Attach_Clipper(m_pClipRect->size(),&((*m_pClipRect)[0]));
	}
	else
	{
		m_primarySurface->SetClipper(NULL);
	}
DDRAWPAINT:
	m_backSurface->GetDC(&hdcDest);
	list<BaseBoard*>::iterator pos;
	for (pos = boards.begin();pos != boards.end(); pos++)
	{
		(*pos)->Paint(hdcDest);
	}
	m_backSurface->ReleaseDC(hdcDest);
	RECT rect;
	::SetRect(&rect,0,0,m_rect.right-m_rect.left,m_rect.bottom-m_rect.top);
	HRESULT   hRet=m_primarySurface->Blt(&m_rect,m_backSurface,&rect,DDBLT_WAITNOTBUSY,NULL);//

	if (DDERR_SURFACELOST == hRet)
	{
		hRet = m_primarySurface->Restore();
		if (hRet == DD_OK)
		{
			goto DDRAWPAINT;
		}
	}
	m_pClipRect->clear();
    ::EndPaint( m_hWnd, &ps );
}



LPDIRECTDRAWSURFACE  CWnd::DDraw_Create_Surface(int width, int height, int mem_flags, int color_key )
{
	// this function creates an offscreen plain surface

	DDSURFACEDESC ddsd;         // working description
	LPDIRECTDRAWSURFACE lpdds;  // temporary surface

	// set to access caps, width, and height
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize  = sizeof(ddsd);
	ddsd.dwFlags =  DDSD_WIDTH | DDSD_HEIGHT;

	// set dimensions of the new bitmap surface
	ddsd.dwWidth  =  width;
	ddsd.dwHeight =  height;

	// set surface to offscreen plain
	/*ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;*/

	// create the surface
	if (FAILED(m_ddraw->CreateSurface(&ddsd,&lpdds,NULL)))
		return(NULL);

	// test if user wants a color key
	if (color_key >= 0)
	{
		// set color key to color 0
		DDCOLORKEY color_key; // used to set color key
		color_key.dwColorSpaceLowValue  = 0;
		color_key.dwColorSpaceHighValue = 0;

		// now set the color key for source blitting
		lpdds->SetColorKey(DDCKEY_SRCBLT, &color_key);
	} // end if

	// return surface
	return(lpdds);
} // end DDraw_Create_Surface

BOOL CWnd::DDraw_Attach_Clipper(int num_rects,LPRECT clip_list)

{
	LPRGNDATA region_data;             // pointer to the region data that contains
	// first allocate memory for region data
	region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+num_rects*sizeof(RECT));

	// now copy the rects into region data
	memcpy(region_data->Buffer, clip_list, sizeof(RECT)*num_rects);

	// set up fields of header
	region_data->rdh.dwSize          = sizeof(RGNDATAHEADER);
	region_data->rdh.iType           = RDH_RECTANGLES;
	region_data->rdh.nCount          = num_rects;
	region_data->rdh.nRgnSize        = num_rects*sizeof(RECT);

	region_data->rdh.rcBound.left    =  64000;
	region_data->rdh.rcBound.top     =  64000;
	region_data->rdh.rcBound.right   = -64000;
	region_data->rdh.rcBound.bottom  = -64000;

	for (int index=0; index<num_rects; index++)
	{
		// test if the next rectangle unioned with the current bound is larger
		if (clip_list[index].left < region_data->rdh.rcBound.left)
			region_data->rdh.rcBound.left = clip_list[index].left;

		if (clip_list[index].right > region_data->rdh.rcBound.right)
			region_data->rdh.rcBound.right = clip_list[index].right;

		if (clip_list[index].top < region_data->rdh.rcBound.top)
			region_data->rdh.rcBound.top = clip_list[index].top;

		if (clip_list[index].bottom > region_data->rdh.rcBound.bottom)
			region_data->rdh.rcBound.bottom = clip_list[index].bottom;

	} // end for index


	if (FAILED(m_lpddclipper->SetClipList(region_data, 0)))
	{
		// release memory and return error
		free(region_data);
		return  FALSE;
	} // end if
	else
	{
		HRESULT ret = m_primarySurface->SetClipper(m_lpddclipper);
		_ASSERT(ret == DD_OK);
	}

	// all is well, so release memory and send back the pointer to the new clipper
	free(region_data);
	return TRUE;

} // end DDraw_Attach_Clipper

void CWnd::AddClipRect( const RECT &rc )
{
	m_pClipRect->push_back(rc);
}