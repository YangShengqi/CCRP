
// CCRPDlg.h : 头文件
//

#pragma once
#include "TeeChar\tchart.h"
#include "afxwin.h"


// CCCRPDlg 对话框
class CCCRPDlg : public CDialogEx
{
// 构造
public:
	CCCRPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCRP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	/*功能：生成服从正态分布的伪随机数
	  参数：randSave[]：存储生成的伪随机数*/
	void randGene(double randSave[]);
	double cepCompute(double xSigma, double ySigma);
	CTChart m_cTraj;
	CTChart m_cSingle;
	CTChart m_cHpoint;
	CTChart m_cVpoint;
	CTChart m_cKpoint;
	CTChart m_cUpoint;
	CTChart m_cEpoint;
	CTChart m_cSumpoint;
	int m_nErrp;
	int m_nCep;
	double m_xveh;
	double m_yveh;
	double m_height;
	double m_v;
	double m_k;
	double m_u;
	double m_e;
	double m_xtarg;
	double m_ytarg;
	afx_msg void OnBnClickedTraj();
	afx_msg void OnBnClickedDefault();
	afx_msg void OnBnClickedLoadparam();
	afx_msg void OnBnClickedErrpoint();
	afx_msg void OnBnClickedVradio();
	afx_msg void OnBnClickedHradio();
	afx_msg void OnBnClickedKradio();
	afx_msg void OnBnClickedUradio();
	afx_msg void OnBnClickedEradio();
	afx_msg void OnBnClickedSumradio();
	afx_msg void OnBnClickedDrawall();
	afx_msg void OnBnClickedHcep();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedComputecep();
	CStatic m_sTitle;
private:
	CFont m_font;
public:
	afx_msg void OnBnClickedSinglecep();
	afx_msg void OnBnClickedDrawallcep();
};
