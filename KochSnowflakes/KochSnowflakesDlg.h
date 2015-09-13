
// KochSnowflakesDlg.h : header file
//

#pragma once


#include "afxwin.h"
#include "afxcmn.h"
#include "ProcessMaster.h"
#include "PainterI.h"


// CKochSnowflakesDlg dialog
class CKochSnowflakesDlg : public CDialogEx
{
// Construction
public:
	CKochSnowflakesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KOCHSNOWFLAKES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:

	PainterI painter;

	ProcessMaster process;

public:

	afx_msg void OnBnClickedOk();
	//CStatic pic_view;
};
