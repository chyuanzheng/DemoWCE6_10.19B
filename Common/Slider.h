#pragma once
typedef struct
{
    WORD    Dn_wMapUp;
    WORD    Dn_wMapDown;
    POINT   Dn_pnt;
    WORD    Up_wMapUp;
    WORD    Up_wMapDown;
    POINT   Up_pnt;
    WORD    Sd_wMapUp;
    WORD    Sd_wMapDown;
    POINT   Sd_pnt;
    WORD    Sd_slider;
    UINT    nStep;
    UINT    nEvent;
}SliderInfo;
#define SLIDER_ID   12
typedef enum
{
    NONE_SPACE, 
    UP_BTN, 
    DOWN_BTN, 
    UP_SPACE, 
    MID_SPACE, 
    DOWN_SPACE
}BTN_SLID;
#include "AbControl.h"
class CE_CONTROL_API Slider : public AbControl
{
protected:
	//�¼�
	UINT     m_nEvent;
	//��ťͼƬ
	HBITMAP  m_dn_down;
	HBITMAP  m_dn_up;
	HBITMAP  m_up_down;
	HBITMAP  m_up_up;
	HBITMAP  m_sd_down;
	HBITMAP  m_sd_up;

    HBITMAP  m_sd_slider;

	//��ť����
	RECT     m_up_rect;//1
    RECT     m_sd_rect;//2
    RECT     m_dn_rect;//3
    FLOAT     m_fstep;
    FLOAT     m_lScale;
	//�ж��Ƿ񱻰���
	BTN_SLID    m_isButtonDown;
    BTN_SLID    m_preButtonDown;
    FLOAT   m_fStart_pos;
    FLOAT   m_fSlid_pp;
    POINT   m_Sdpnt;
    int     m_fstepNum;
    int     m_nAmt;

    
	
public:
	Slider();
	virtual ~Slider();
	void Init(const SliderInfo& pSdInfo);
    //void SetStatus(FOART fStart_pos,FLOAT fSlid_pp);
    //void Init(WORD Dn_wMapUp, WORD Dn_wMapDown, WORD Up_wMapUp, WORD Up_wMapDown, WORD Sd_wMapUp, WORD Sd_wMapDown, UINT nEvent);
    void SetPos(FLOAT fStart_pos=-1, FLOAT fSlid_pp=-1,bool isShow = true);//����ǰ��λ�á�����ĩ��λ�á�



protected:
	//�滭
	virtual void Draw( HDC hdcDst );
	//��Ӧ�����¼�
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
    //�ͷ���Դ
    void  FreeRes();
    void DrawUp( HDC hdcDst );
    void DrawSd( HDC hdcDst );
    void DrawDn( HDC hdcDst );
    void SendMsg();
    


private:
	BTN_SLID InMyArea( int x, int y );
    BOOL InRect( int x, int y, RECT& rect );
    void HandleSlider(BTN_SLID btn_slid,int x, int y,HDC hdc, bool bMove = false);
    void OnTimer( UINT IDEvent );
    void MoveStepUp( bool bUp  );
    void MovePageUp( bool bUp );
    void MoveSlider( INT nspace );
};
