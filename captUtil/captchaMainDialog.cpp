#include "StdAfx.h"
#include "Resource.h"
#include "captchaMainDialog.h"
#include "captchaCanvasWnd.h"

//--------------------------------------------------------------------------------------------
CMainDialog::CMainDialog()
{
}

//--------------------------------------------------------------------------------------------
CMainDialog::~CMainDialog()
{
}

//--------------------------------------------------------------------------------------------
LRESULT CMainDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//Center window
	CenterWindow(GetParent());

	//Set scroll range
	m_hParamPosX = ::GetDlgItem(m_hWnd, IDC_SLIDER_X);
	m_hParamPosY = ::GetDlgItem(m_hWnd, IDC_SLIDER_Y);
	m_hFreQuency = ::GetDlgItem(m_hWnd, IDC_SLIDER_FREQUENCY);
	m_hCylinderFre = ::GetDlgItem(m_hWnd, IDC_SLIDER_CYLINDER_F);
	m_hCylinderAngle = ::GetDlgItem(m_hWnd, IDC_SLIDER_CYLINDER_ANGLE);
	m_hCylinderScale = ::GetDlgItem(m_hWnd, IDC_SLIDER_CYLINDER_SCALE);

	::SendMessage(m_hParamPosX, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));
	::SendMessage(m_hParamPosY, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));
	::SendMessage(m_hFreQuency, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));
	::SendMessage(m_hCylinderFre, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));
	::SendMessage(m_hCylinderAngle, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));
	::SendMessage(m_hCylinderScale, TBM_SETRANGE, (WPARAM)(BOOL)TRUE, (LPARAM)MAKELONG(0, 999));

	//GEN IMAGE!
	Generate gen;
	gen.generateQuestion(m_question);

	//Create canvas
	HWND hCanvasParent = ::GetDlgItem(m_hWnd, IDC_CANVAS);

	RECT rect;
	::GetClientRect(hCanvasParent, &rect);

	m_canvasWindow = new CCanvasWindow;
	m_canvasWindow->Create(hCanvasParent, rect, _T("Canvas"), WS_CHILD);
	m_canvasWindow->ShowWindow(SW_SHOW);

	m_canvasWindow->setQuestion(&m_question);


	return (LRESULT)TRUE;
}


//--------------------------------------------------------------------------------------------
void CMainDialog::_generateRand(void)
{
	Generate gen;
	gen.randParam(m_param);

	::SendMessage(m_hParamPosX, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.pos_x*999));
	::SendMessage(m_hParamPosY, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.pos_y*999));
	::SendMessage(m_hFreQuency, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.frequency*999));
	::SendMessage(m_hCylinderFre, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.cylinder_fre*999));
	::SendMessage(m_hCylinderAngle, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.cylinder_angle*999));
	::SendMessage(m_hCylinderScale, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(m_param.cylinder_scale*999));

	gen.generateQuestion(m_question, &m_param);
	m_canvasWindow->redraw();
}

//--------------------------------------------------------------------------------------------
LRESULT CMainDialog::OnButtonRand(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	_generateRand();
	return TRUE;
}

//--------------------------------------------------------------------------------------------
LRESULT CMainDialog::OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hScroll = (HWND)lParam;

	if(	hScroll == m_hParamPosX || hScroll == m_hParamPosY || hScroll == m_hFreQuency || 
		hScroll==m_hCylinderAngle || hScroll==m_hCylinderFre || hScroll==m_hCylinderScale)
	{
		m_param.pos_x = (float)::SendMessage(m_hParamPosX, TBM_GETPOS, 0, 0)/999.0f;
		m_param.pos_y = (float)::SendMessage(m_hParamPosY, TBM_GETPOS, 0, 0)/999.0f;
		m_param.frequency = (float)::SendMessage(m_hFreQuency, TBM_GETPOS, 0, 0)/999.0f;
		m_param.cylinder_fre = (float)::SendMessage(m_hCylinderFre, TBM_GETPOS, 0, 0)/999.0f;
		m_param.cylinder_angle = (float)::SendMessage(m_hCylinderAngle, TBM_GETPOS, 0, 0)/999.0f;
		m_param.cylinder_scale = (float)::SendMessage(m_hCylinderScale, TBM_GETPOS, 0, 0)/999.0f;
		
		Generate gen;
		gen.generateQuestion(m_question, &m_param);
		m_canvasWindow->redraw();
	}
	return (LRESULT)TRUE;
}

//--------------------------------------------------------------------------------------------
LRESULT CMainDialog::OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

