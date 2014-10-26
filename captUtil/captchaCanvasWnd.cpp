#include "StdAfx.h"
#include "captchaCanvasWnd.h"

//--------------------------------------------------------------------------------------------
CCanvasWindow::CCanvasWindow()
	: m_nCanvasPitch(0)
	, m_question(0)
{
}

//--------------------------------------------------------------------------------------------
CCanvasWindow::~CCanvasWindow()
{

}

//--------------------------------------------------------------------------------------------
LRESULT CCanvasWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if(!m_bmpCanvas.IsNull())
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(dc);
		HBITMAP hBmpOld = dcMem.SelectBitmap(m_bmpCanvas);
		dc.BitBlt(0, 0, m_size.cx, m_size.cy, dcMem, 0, 0, SRCCOPY);
		dcMem.SelectBitmap(hBmpOld);
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
LRESULT CCanvasWindow::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

//--------------------------------------------------------------------------------------------
void CCanvasWindow::setQuestion(Generate::Question* question)
{
	m_question = question;
	redraw();
}

//--------------------------------------------------------------------------------------------
void CCanvasWindow::_createCanvas(int width, int height)
{
	//free old canvas
	if(!m_bmpCanvas.IsNull())
	{
		m_bmpCanvas.DeleteObject();
	}

	m_size.cx = width;
	m_size.cy = height;

	//cal pitch
	m_nCanvasPitch=width*2;
	while(m_nCanvasPitch%4!=0) m_nCanvasPitch++;
	m_nCanvasPitch=m_nCanvasPitch>>1;

	// create canvas dc
	CDC dcCanvas;
	dcCanvas.CreateCompatibleDC(CClientDC(m_hWnd));

	//create DIB Section
	BITMAPINFO bmpInfo; 
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize		= sizeof (BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth		= width; 
	bmpInfo.bmiHeader.biHeight		= -height;
	bmpInfo.bmiHeader.biPlanes		= 1;
	bmpInfo.bmiHeader.biBitCount	= 16;
	bmpInfo.bmiHeader.biSizeImage	= m_nCanvasPitch * height * 2;
	m_bmpCanvas.Attach(CreateDIBSection(CClientDC(m_hWnd), &bmpInfo, DIB_RGB_COLORS, (VOID**)&(m_pCanvasBitbuf), 0, 0));
}

//--------------------------------------------------------------------------------------------
LRESULT CCanvasWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int cx = GET_X_LPARAM(lParam);
	int cy = GET_Y_LPARAM(lParam);
	bHandled = FALSE;

	if(cx==0 || cy==0) return 0;

	//reset canvas
	_createCanvas(cx, cy);

	// redraw
	redraw();

	return 1;
}

//--------------------------------------------------------------------------------------------
void CCanvasWindow::redraw(void)
{
	if(m_bmpCanvas.IsNull() || m_question==0) return;

	//fill back
	for(int i=0; i<m_size.cy; i++)
	{
		unsigned short* pCanvasBit = m_pCanvasBitbuf+i*m_nCanvasPitch;
		ZeroMemory(pCanvasBit, m_nCanvasPitch*sizeof(unsigned short)); 
	}

	unsigned short* pCanvasBit = m_pCanvasBitbuf;

	for(int i=0; i<Generate::Question::IMAGE_SIZE; i++)
	{
		pCanvasBit = m_pCanvasBitbuf + m_nCanvasPitch*i;
		for(int j=0; j<Generate::Question::IMAGE_SIZE; j++)
		{
			unsigned char data = m_question->imageBuf[(i*Generate::Question::IMAGE_SIZE+j)>>1];
			if(j&1) 
			{
				data = data&0x0F;
			}
			else
			{
				data = (data>>4)&0x0F;
			}

			*pCanvasBit++ = (data<<11) | (data<<6) | (data<<1);
		}
	}

	//send redraw request
	::InvalidateRect(m_hWnd, 0, TRUE);
}