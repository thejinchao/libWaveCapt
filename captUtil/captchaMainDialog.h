#pragma once

#include <waveGenerate.h>

//pre-define class
class CCanvasWindow;

/** Main Function Dialog
*/
class CMainDialog : public CDialogImpl< CMainDialog >
{
	/*************************************************************************
			Public Methods
	*************************************************************************/
public:

	/*************************************************************************
			Inherit Methods
	*************************************************************************/
public:
	enum { IDD = IDD_DIALOG_MAIN };

	BEGIN_MSG_MAP(CMainDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_RAND, OnButtonRand)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnButtonRand(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	/*************************************************************************
			Implementation Methods
	*************************************************************************/
private:
	void _generateRand(void);

	/*************************************************************************
		Implementation Data
	*************************************************************************/
private:
	CCanvasWindow* m_canvasWindow;			//!< Canvas window 
	Generate::Question m_question;
	Generate::Param m_param;

	HWND m_hParamPosX;
	HWND m_hParamPosY;
	HWND m_hFreQuency;
	HWND m_hCylinderFre;
	HWND m_hCylinderAngle;
	HWND m_hCylinderScale;

	/*************************************************************************
		Construction and Destruction
	*************************************************************************/
public:
	CMainDialog();
	~CMainDialog();
};
