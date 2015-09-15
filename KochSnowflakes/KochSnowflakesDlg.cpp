
// KochSnowflakesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KochSnowflakes.h"
#include "KochSnowflakesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CKochSnowflakesDlg::CKochSnowflakesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKochSnowflakesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKochSnowflakesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_VIEW, painter);
}

BEGIN_MESSAGE_MAP(CKochSnowflakesDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CKochSnowflakesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKochSnowflakesDlg message handlers

BOOL CKochSnowflakesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	process.SetPainter(&painter);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

HCURSOR CKochSnowflakesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKochSnowflakesDlg::OnBnClickedOk()
{
	process.Process();
}
