
// CCRPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CCRP.h"
#include "CCRPDlg.h"
#include "afxdialogex.h"
#include "CcrpAim.h"
#include "TeeChar\series.h"
#include "TeeChar\point3dseries.h"
#include "TeeChar\titles.h"
#include "TeeChar\strings.h"
#include "TeeChar\axislabelsitem.h"
#include "TeeChar\axes.h"
#include "TeeChar\axis.h"
#include "TeeChar\axistitle.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

#define MKCOUNT 100		//���ؿ���������
#define MKCEP 100

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double omega = 0.1;		//�ɻ�ת����ٶ�
double deltat = 0.01;		//��׼���̲���
double h = 0.01;			//�����������ʱ�䲽��
double hSigma = 50;
double vSigma = 0.1, uSigma = 5;
double kSigma = 0.1, eSigma = 0.1;


// CCCRPDlg �Ի���

CCCRPDlg::CCCRPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CCRP_DIALOG, pParent)
	, m_nErrp(0)
	, m_nCep(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCRPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRAJCHART, m_cTraj);
	DDX_Control(pDX, IDC_HEICHART, m_cHpoint);
	DDX_Control(pDX, IDC_VCHART, m_cVpoint);
	DDX_Control(pDX, IDC_KCHART, m_cKpoint);
	DDX_Control(pDX, IDC_UCHART, m_cUpoint);
	DDX_Control(pDX, IDC_ECHART, m_cEpoint);
	DDX_Control(pDX, IDC_SUMCHART, m_cSumpoint);
	DDX_Radio(pDX, IDC_HRADIO, m_nErrp);
	DDX_Control(pDX, IDC_SINGLE, m_cSingle);
	DDX_Radio(pDX, IDC_HCEP, m_nCep);
	DDX_Control(pDX, IDC_TITLE, m_sTitle);
}

BEGIN_MESSAGE_MAP(CCCRPDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TRAJ, &CCCRPDlg::OnBnClickedTraj)
	ON_BN_CLICKED(IDC_DEFAULT, &CCCRPDlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDC_LOADPARAM, &CCCRPDlg::OnBnClickedLoadparam)
	ON_BN_CLICKED(IDC_ERRPOINT, &CCCRPDlg::OnBnClickedErrpoint)
	ON_BN_CLICKED(IDC_VRADIO, &CCCRPDlg::OnBnClickedVradio)
	ON_BN_CLICKED(IDC_HRADIO, &CCCRPDlg::OnBnClickedHradio)
	ON_BN_CLICKED(IDC_KRADIO, &CCCRPDlg::OnBnClickedKradio)
	ON_BN_CLICKED(IDC_URADIO, &CCCRPDlg::OnBnClickedUradio)
	ON_BN_CLICKED(IDC_ERADIO, &CCCRPDlg::OnBnClickedEradio)
	ON_BN_CLICKED(IDC_SUMRADIO, &CCCRPDlg::OnBnClickedSumradio)
	ON_BN_CLICKED(IDC_DRAWALL, &CCCRPDlg::OnBnClickedDrawall)
	ON_BN_CLICKED(IDC_HCEP, &CCCRPDlg::OnBnClickedHcep)
	ON_BN_CLICKED(IDC_RADIO2, &CCCRPDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CCCRPDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CCCRPDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CCCRPDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CCCRPDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_COMPUTECEP, &CCCRPDlg::OnBnClickedComputecep)
	ON_BN_CLICKED(IDC_SINGLECEP, &CCCRPDlg::OnBnClickedSinglecep)
	ON_BN_CLICKED(IDC_DRAWALLCEP, &CCCRPDlg::OnBnClickedDrawallcep)
END_MESSAGE_MAP()


// CCCRPDlg ��Ϣ�������

BOOL CCCRPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_font.CreatePointFont(150, _T("΢���ź�"), NULL);
	m_sTitle.SetFont(&m_font);

	SetDlgItemText(IDC_XVEH, _T("0"));		//m_xveh = 500.0
	SetDlgItemText(IDC_YVEH, _T("0"));		//m_yveh = 500.0
	SetDlgItemText(IDC_HEIGHT, _T("1000"));		//m_height = 1000
	SetDlgItemText(IDC_VVEH, _T("200"));		//m_v = 200.0
	SetDlgItemText(IDC_KVEH, _T("0"));			//m_k = 10.0
	SetDlgItemText(IDC_UWIND, _T("10"));		//m_u = 10.0
	SetDlgItemText(IDC_EWIND, _T("20"));		//m_e = 20.0
	SetDlgItemText(IDC_XTARG, _T("5000"));		//m_xtarg = 5000.0
	SetDlgItemText(IDC_YTARG, _T("2000"));		//m_ytarg = 2000.0

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCCRPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCCRPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCCRPDlg::randGene(double randND[])
{
	srand(time(NULL));
	double r1, r2;
	int phase = 1;
	for (int i = 0; i < MKCOUNT; i++)
	{
		if (phase)
		{
			r1 = rand() / static_cast<double>(RAND_MAX);
			r2 = rand() / static_cast<double>(RAND_MAX);
			randND[i] = sqrt(-2 * log(r1))*cos(2 * PI*r2);
		}
		else
			randND[i] = sqrt(-2 * log(r1))*sin(2 * PI*r2);
		phase = 1 - phase;
	}
}

double CCCRPDlg::cepCompute(double xSigma, double ySigma)
{
	if ((xSigma < ySigma) && (xSigma / ySigma < 0.28))
		return 0.615*xSigma + 0.562*ySigma;
	else if ((xSigma > ySigma) && (ySigma / xSigma < 0.28))
		return 0.615*ySigma + 0.562*xSigma;
	else
		return 0.5887*(xSigma + ySigma);
}

//////////////////////////Ĭ�ϲ�������////////////////////////
void CCCRPDlg::OnBnClickedDefault()
{
	SetDlgItemText(IDC_XVEH, _T("0"));		//m_xveh = 500.0
	SetDlgItemText(IDC_YVEH, _T("0"));		//m_yveh = 500.0
	SetDlgItemText(IDC_HEIGHT, _T("1000"));		//m_height = 1000
	SetDlgItemText(IDC_VVEH, _T("200"));		//m_v = 200.0
	SetDlgItemText(IDC_KVEH, _T("0"));			//m_k = 10.0
	SetDlgItemText(IDC_UWIND, _T("10"));		//m_u = 10.0
	SetDlgItemText(IDC_EWIND, _T("20"));		//m_e = 20.0
	SetDlgItemText(IDC_XTARG, _T("5000"));		//m_xtarg = 5000.0
	SetDlgItemText(IDC_YTARG, _T("2000"));		//m_ytarg = 2000.0
}

/////////////////////////���ز���/////////////////////////////
void CCCRPDlg::OnBnClickedLoadparam()
{
	CString str;
	GetDlgItemText(IDC_XVEH, str);
	m_xveh = (double)_ttof(str);
	GetDlgItemText(IDC_YVEH, str);
	m_yveh = (double)_ttof(str);
	GetDlgItemText(IDC_HEIGHT,str);
	m_height = (double)_ttof(str);
	GetDlgItemText(IDC_VVEH, str);
	m_v = (double)_ttof(str);
	GetDlgItemText(IDC_KVEH, str);
	m_k = (double)_ttof(str);
	GetDlgItemText(IDC_UWIND, str);
	m_u = (double)_ttof(str);
	GetDlgItemText(IDC_EWIND, str);
	m_e = (double)_ttof(str);
	GetDlgItemText(IDC_XTARG, str);
	m_xtarg = (double)_ttof(str);
	GetDlgItemText(IDC_YTARG, str);
	m_ytarg = (double)_ttof(str);
	if (m_xtarg <= 0 || m_ytarg <= 0)
		AfxMessageBox(_T("����Ŀ�����괦�������0��ֵ"));
	if (m_k < 0 || m_k >= 90)
		AfxMessageBox(_T("���ڿ��ٺ���Ǵ�����0-90��ֵ������90��"));
}

///////////////////////////���۵�������//////////////////////////
void CCCRPDlg::OnBnClickedTraj()
{
	double K = m_k;
	CcrpAim ccrp;
	ccrp.CCRP(m_height, m_v, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
	int nAimidx = ccrp.output_aim();
	int nCount= ccrp.output_index();
	
	CString str;
	str.Format(_T("%.4lf"), ccrp.output_stdrange());
	SetDlgItemText(IDC_STDRANGE, str);
	str.Format(_T("%.4lf"), ccrp.output_stdtime());
	SetDlgItemText(IDC_STDTIME, str);
	str.Format(_T("%.4lf"), K);
	SetDlgItemText(IDC_KRELEASE, str);
	str.Format(_T("%.4lf"), ccrp.output_xbomb(nAimidx));
	SetDlgItemText(IDC_XRELEASE, str);
	str.Format(_T("%.4lf"), ccrp.output_zbomb(nAimidx));
	SetDlgItemText(IDC_YRELEASE, str);
	str.Format(_T("%.4lf"), ccrp.output_ybomb(nAimidx));
	SetDlgItemText(IDC_ZRELEASE, str);
	str.Format(_T("%.4lf"), ccrp.output_xbomb(nCount));
	SetDlgItemText(IDC_XCOMPACT, str);
	str.Format(_T("%.4lf"), ccrp.output_zbomb(nCount));
	SetDlgItemText(IDC_YCOMPACT, str);

	m_cTraj.Series(0).Clear();
	m_cTraj.GetHeader().GetText().SetItem(0, COleVariant(_T("���۵���")));
	m_cTraj.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cTraj.GetAxis().GetLeft().GetTitle().SetCaption(_T("Z"));
	m_cTraj.GetAxis().GetDepth().GetTitle().SetCaption(_T("Y"));
	for (int j = 0; j < (nCount + 1); j++)
		m_cTraj.Series(0).GetAsPoint3D().AddXYZ(ccrp.output_xbomb(j), ccrp.output_ybomb(j), ccrp.output_zbomb(j), NULL, NULL);
}

//////////////////////////����Ŷ������ɢ����ѡ�����ӳ��//////////////////////
void CCCRPDlg::OnBnClickedHradio()
{
	m_nErrp = 0;
}

void CCCRPDlg::OnBnClickedVradio()
{
	m_nErrp = 1;
}

void CCCRPDlg::OnBnClickedKradio()
{
	m_nErrp = 2;
}

void CCCRPDlg::OnBnClickedUradio()
{
	m_nErrp = 3;
}

void CCCRPDlg::OnBnClickedEradio()
{
	m_nErrp = 4;
}

void CCCRPDlg::OnBnClickedSumradio()
{
	m_nErrp = 5;
}

/////////////////////////////���Ƶ�һ����������µ����ɢ��////////////////////////////////
void CCCRPDlg::OnBnClickedErrpoint()
{
	double K=m_k;
	double randND[MKCOUNT];
	double hError, vError, kError, uError, eError;
	double xeIP[MKCOUNT], zeIP[MKCOUNT];
	CcrpAim ccrp;
	randGene(randND);
	m_cSingle.Series(0).Clear();
	m_cSingle.Series(1).Clear();
	m_cSingle.GetHeader().SetVisible(TRUE);
	m_cSingle.GetAxis().GetBottom().GetTitle().SetVisible(TRUE);
	m_cSingle.GetAxis().GetLeft().GetTitle().SetVisible(TRUE);

	switch (m_nErrp)
	{
	////////////////�߶�������ɢ��/////////////////
	case 0:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			hError = m_height + randND[i]* hSigma;
			ccrp.CCRP(hError, m_v, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			K = m_k;
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("�߶�������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	/////////////////����������ɢ��/////////////////
	case 1:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			vError = m_v + randND[i]* vSigma;
			ccrp.CCRP(m_height, vError, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			K = m_k;
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("����������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	/////////////////�����������ɢ��/////////////////
	case 2:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			kError = K + randND[i]* kSigma;
			ccrp.CCRP(m_height, m_v, omega, kError, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("�����������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	/////////////////����������ɢ��/////////////////
	case 3:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			uError = m_u + randND[i]* uSigma;
			ccrp.CCRP(m_height, m_v, omega, K, uError, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			K = m_k;
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("����������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	/////////////////�����������ɢ��/////////////////
	case 4:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			eError = m_e + randND[i]* eSigma;
			ccrp.CCRP(m_height, m_v, omega, K, m_u, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			K = m_k;
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("�����������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	/////////////////�����в��������������ɢ��/////////////////
	case 5:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			hError = m_height + randND[i]* hSigma;
			vError = m_v + randND[i] * vSigma;
			kError = m_k + randND[i] * kSigma;
			uError = m_u + randND[i] * uSigma;
			eError = m_e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
			zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
			ccrp.reset();
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("ȫ������ɢ��")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
		for (int i = 0; i < MKCOUNT; i++)
			m_cSingle.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
		break;
	}
	}
}

///////////////////////////��������ȫ��6�ֲ�ͬ����������µ����ɢ��/////////////////////////////
void CCCRPDlg::OnBnClickedDrawall()
{
	double K = m_k;
	double randND[MKCOUNT];
	double hError, vError, kError, uError, eError;
	double xeIP[MKCOUNT], zeIP[MKCOUNT];
	CcrpAim ccrp;
	randGene(randND);
	m_cSingle.Series(0).Clear();
	m_cSingle.Series(1).Clear();
	m_cSingle.GetHeader().SetVisible(FALSE);
	m_cSingle.GetAxis().GetBottom().GetTitle().SetVisible(FALSE);
	m_cSingle.GetAxis().GetLeft().GetTitle().SetVisible(FALSE);
	////////////////�߶�������ɢ��/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		hError = m_height + randND[i] * hSigma;
		ccrp.CCRP(hError, m_v, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		K = m_k;
		ccrp.reset();
	}
	m_cHpoint.Series(0).Clear();
	m_cHpoint.Series(1).Clear();
	m_cHpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("�߶�������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cHpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
	/////////////////����������ֲ�/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		vError = m_v + randND[i] * vSigma;
		ccrp.CCRP(m_height, vError, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		K = m_k;
		ccrp.reset();
	}
	m_cVpoint.Series(0).Clear();
	m_cVpoint.Series(1).Clear();
	m_cVpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("����������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cVpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
	/////////////////�����������ֲ�/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		kError = K + randND[i] * kSigma;
		ccrp.CCRP(m_height, m_v, omega, kError, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		ccrp.reset();
	}
	m_cKpoint.Series(0).Clear();
	m_cKpoint.Series(1).Clear();
	m_cKpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("�����������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cKpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
	/////////////////����������ֲ�/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		uError = m_u + randND[i] * uSigma;
		ccrp.CCRP(m_height, m_v, omega, K, uError, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		K = m_k;
		ccrp.reset();
	}
	m_cUpoint.Series(0).Clear();
	m_cUpoint.Series(1).Clear();
	m_cUpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("����������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cUpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
	/////////////////�����������ֲ�/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		eError = m_e + randND[i] * eSigma;
		ccrp.CCRP(m_height, m_v, omega, K, m_u, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		K = m_k;
		ccrp.reset();
	}
	m_cEpoint.Series(0).Clear();
	m_cEpoint.Series(1).Clear();
	m_cEpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("�����������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cEpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
	/////////////////��������ֲ�/////////////////
	for (int i = 0; i < MKCOUNT; i++)
	{
		hError = m_height + randND[i] * hSigma;
		vError = m_v + randND[i] * vSigma;
		kError = m_k + randND[i] * kSigma;
		uError = m_u + randND[i] * uSigma;
		eError = m_e + randND[i] * eSigma;
		ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
		xeIP[i] = ccrp.output_xbomb(ccrp.output_index());
		zeIP[i] = ccrp.output_zbomb(ccrp.output_index());
		ccrp.reset();
	}
	m_cSumpoint.Series(0).Clear();
	m_cSumpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("ȫ������ɢ��")));
	m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("X"));
	m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("Y"));
	for (int i = 0; i < MKCOUNT; i++)
		m_cSumpoint.Series(0).AddXY(xeIP[i], zeIP[i], NULL, NULL);
}

//////////////////////////////CEP���㵥ѡ�����ӳ��////////////////////////////////
void CCCRPDlg::OnBnClickedHcep()
{
	m_nCep = 0;
}

void CCCRPDlg::OnBnClickedRadio2()
{
	m_nCep = 1;
}

void CCCRPDlg::OnBnClickedRadio3()
{
	m_nCep = 2;
}

void CCCRPDlg::OnBnClickedRadio4()
{
	m_nCep = 3;
}

void CCCRPDlg::OnBnClickedRadio5()
{
	m_nCep = 4;
}

void CCCRPDlg::OnBnClickedRadio6()
{
	m_nCep = 5;
}

///////////////////////////////////ָ��������CEP����/////////////////////////////
void CCCRPDlg::OnBnClickedComputecep()
{
	double K = m_k;
	double randND[MKCOUNT];
	double hError, vError, kError, uError, eError;
	double xeIP, zeIP;
	double xExp = 0, yExp = 0;
	double xMse = 0, yMse = 0;
	double cep;
	CcrpAim ccrp;
	CString str;
	randGene(randND);

	switch (m_nCep)
	{
	////////////////�߶����CEP/////////////////
	case 0:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			hError = m_height + randND[i] * hSigma;
			ccrp.CCRP(hError, m_v, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			K = m_k;
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	////////////////�������CEP/////////////////
	case 1:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			vError = m_v + randND[i] * vSigma;
			ccrp.CCRP(m_height, vError, omega, K, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			K = m_k;
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	/////////////////��������CEP/////////////////
	case 2:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			kError = K + randND[i] * kSigma;
			ccrp.CCRP(m_height, m_v, omega, kError, m_u, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	////////////////�������CEP/////////////////
	case 3:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			uError = m_u + randND[i] * uSigma;
			ccrp.CCRP(m_height, m_v, omega, K, uError, m_e, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			K = m_k;
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	////////////////��������CEP/////////////////
	case 4:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			eError = m_e + randND[i] * eSigma;
			ccrp.CCRP(m_height, m_v, omega, K, m_u, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			K = m_k;
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	/////////////////�����в�����������CEP/////////////////
	case 5:
	{
		for (int i = 0; i < MKCOUNT; i++)
		{
			hError = m_height + randND[i] * hSigma;
			vError = m_v + randND[i] * vSigma;
			kError = m_k + randND[i] * kSigma;
			uError = m_u + randND[i] * uSigma;
			eError = m_e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, m_xtarg, m_ytarg, m_xveh, m_yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - m_xtarg);
			yExp = yExp + (zeIP - m_ytarg);
			xMse = xMse + pow((xeIP - m_xtarg), 2);
			yMse = yMse + pow((zeIP - m_ytarg), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCOUNT;
		yExp = yExp / MKCOUNT;
		xMse = sqrt(xMse / (MKCOUNT - 1));
		yMse = sqrt(yMse / (MKCOUNT - 1));
		cep = cepCompute(xMse, yMse);
		str.Format(_T("%.4lf"), xExp);
		SetDlgItemText(IDC_XEXP, str);
		str.Format(_T("%.4lf"), yExp);
		SetDlgItemText(IDC_YEXP, str);
		str.Format(_T("%.4lf"), xMse);
		SetDlgItemText(IDC_XMSE, str);
		str.Format(_T("%.4lf"), yMse);
		SetDlgItemText(IDC_YMSE, str);
		str.Format(_T("%.4lf"), cep);
		SetDlgItemText(IDC_CEP, str);
		break;
	}
	}
}

/////////////////////////////����CEP��ĳһ�����ı仯����////////////////////////////////
void CCCRPDlg::OnBnClickedSinglecep()
{
	double xveh = 0, yveh = 0;
	double xtarg = 5000.0, ytarg = 2000.0;
	double height = 1000.0;
	double v = 200.0;
	double K = 10.0;
	double u = 10.0;
	double e = 20.0;
	double randND[MKCOUNT];
	double hError, vError, kError, uError, eError;
	double xImp, zImp, xeIP, zeIP;
	double xExp = 0, yExp = 0;
	double xMse = 0, yMse = 0;
	CcrpAim ccrp;
	randGene(randND);
	m_cSingle.Series(0).Clear();
	m_cSingle.Series(1).Clear();
	m_cSingle.GetHeader().SetVisible(TRUE);
	m_cSingle.GetAxis().GetBottom().GetTitle().SetVisible(TRUE);
	m_cSingle.GetAxis().GetLeft().GetTitle().SetVisible(TRUE);

	switch (m_nCep)
	{
	//////////////////////////�߶�-CEP����/////////////////////////
	case 0:
	{
		xtarg = 15000.0;
		ytarg = 15000.0;
		height = 1000.0;
		double hcep[46];
		for (int j=0;j<46;j++)
		{
			for (int i = 0; i < MKCEP; i++)
			{
				hError = height + randND[i] * hSigma;
				vError = v + randND[i] * vSigma;
				kError = K + randND[i] * kSigma;
				uError = u + randND[i] * uSigma;
				eError = e + randND[i] * eSigma;
				ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
				xeIP = ccrp.output_xbomb(ccrp.output_index());
				zeIP = ccrp.output_zbomb(ccrp.output_index());
				xExp = xExp + (xeIP - xtarg);
				yExp = yExp + (zeIP - ytarg);
				xMse = xMse + pow((xeIP - xtarg), 2);
				yMse = yMse + pow((zeIP - ytarg), 2);
				ccrp.reset();
			}
			xExp = xExp / MKCEP;
			yExp = yExp / MKCEP;
			xMse = sqrt(xMse / (MKCEP - 1));
			yMse = sqrt(yMse / (MKCEP - 1));
			hcep[j] = cepCompute(xMse, yMse);
			height = height + 200;
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("�߶�-CEP����")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("�߶�(m)"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
		for (int k = 0; k < 46; k++)
			m_cSingle.Series(1).AddXY(1000 + k * 200, hcep[k], NULL, NULL);
		break;
	}
	//////////////////////////����-CEP����/////////////////////////
	case 1:
	{
		v = 100.0;
		double vcep[21];
		for (int j = 0; j<16; j++)
		{
			for (int i = 0; i < MKCEP; i++)
			{
				hError = height + randND[i] * hSigma;
				vError = v + randND[i] * vSigma;
				kError = K + randND[i] * kSigma;
				uError = u + randND[i] * uSigma;
				eError = e + randND[i] * eSigma;
				ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
				xeIP = ccrp.output_xbomb(ccrp.output_index());
				zeIP = ccrp.output_zbomb(ccrp.output_index());
				xExp = xExp + (xeIP - xtarg);
				yExp = yExp + (zeIP - ytarg);
				xMse = xMse + pow((xeIP - xtarg), 2);
				yMse = yMse + pow((zeIP - ytarg), 2);
				ccrp.reset();
			}
			xExp = xExp / MKCEP;
			yExp = yExp / MKCEP;
			xMse = sqrt(xMse / (MKCEP - 1));
			yMse = sqrt(yMse / (MKCEP - 1));
			vcep[j] = cepCompute(xMse, yMse);
			v = v + 10;
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("����-CEP����")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("����(m/s)"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
		for (int k = 0; k < 16; k++)
			m_cSingle.Series(1).AddXY(100 + k * 10, vcep[k], NULL, NULL);
		break;
	}
	//////////////////////////�����-CEP����/////////////////////////
	case 2:
	{
		xtarg = 5000.0;
		ytarg = 5000.0;
		K = 0;
		double kcep[41];
		for (int j = 0; j<41; j++)
		{
			for (int i = 0; i < MKCEP; i++)
			{
				hError = height + randND[i] * hSigma;
				vError = v + randND[i] * vSigma;
				kError = K + randND[i] * kSigma;
				uError = u + randND[i] * uSigma;
				eError = e + randND[i] * eSigma;
				ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
				xeIP = ccrp.output_xbomb(ccrp.output_index());
				zeIP = ccrp.output_zbomb(ccrp.output_index());
				xExp = xExp + (xeIP - xtarg);
				yExp = yExp + (zeIP - ytarg);
				xMse = xMse + pow((xeIP - xtarg), 2);
				yMse = yMse + pow((zeIP - ytarg), 2);
				ccrp.reset();
			}
			xExp = xExp / MKCEP;
			yExp = yExp / MKCEP;
			xMse = sqrt(xMse / (MKCEP - 1));
			yMse = sqrt(yMse / (MKCEP - 1));
			kcep[j] = cepCompute(xMse, yMse);
			K = K+1;
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("�����-CEP����")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("�����(��)"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
		for (int k = 0; k < 41; k++)
			m_cSingle.Series(1).AddXY(0 + k * 1, kcep[k], NULL, NULL);
		break;
	}
	//////////////////////////����-CEP����/////////////////////////
	case 3:
	{
		double ucep[21];
		for (int j = 0; j<21; j++)
		{
			for (int i = 0; i < MKCEP; i++)
			{
				hError = height + randND[i] * hSigma;
				vError = v + randND[i] * vSigma;
				kError = K + randND[i] * kSigma;
				uError = u + randND[i] * uSigma;
				eError = e + randND[i] * eSigma;
				ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
				xeIP = ccrp.output_xbomb(ccrp.output_index());
				zeIP = ccrp.output_zbomb(ccrp.output_index());
				xExp = xExp + (xeIP - xtarg);
				yExp = yExp + (zeIP - ytarg);
				xMse = xMse + pow((xeIP - xtarg), 2);
				yMse = yMse + pow((zeIP - ytarg), 2);
				ccrp.reset();
			}
			xExp = xExp / MKCEP;
			yExp = yExp / MKCEP;
			xMse = sqrt(xMse / (MKCEP - 1));
			yMse = sqrt(yMse / (MKCEP - 1));
			ucep[j] = cepCompute(xMse, yMse);
			u = u + 1;
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("����-CEP����")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("����(m/s)"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
		for (int k = 0; k < 21; k++)
			m_cSingle.Series(1).AddXY(10 + k * 1, ucep[k], NULL, NULL);
		break;
	}
	//////////////////////////���ٺ����-CEP����/////////////////////////
	case 4:
	{
		double ecep[31];
		for (int j = 0; j<31; j++)
		{
			for (int i = 0; i < MKCEP; i++)
			{
				hError = height + randND[i] * hSigma;
				vError = v + randND[i] * vSigma;
				kError = K + randND[i] * kSigma;
				uError = u + randND[i] * uSigma;
				eError = e + randND[i] * eSigma;
				ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
				xeIP = ccrp.output_xbomb(ccrp.output_index());
				zeIP = ccrp.output_zbomb(ccrp.output_index());
				xExp = xExp + (xeIP - xtarg);
				yExp = yExp + (zeIP - ytarg);
				xMse = xMse + pow((xeIP - xtarg), 2);
				yMse = yMse + pow((zeIP - ytarg), 2);
				ccrp.reset();
			}
			xExp = xExp / MKCEP;
			yExp = yExp / MKCEP;
			xMse = sqrt(xMse / (MKCEP - 1));
			yMse = sqrt(yMse / (MKCEP - 1));
			ecep[j] = cepCompute(xMse, yMse);
			e = e + 1;
		}
		m_cSingle.GetHeader().GetText().SetItem(0, COleVariant(_T("���ٺ����-CEP����")));
		m_cSingle.GetAxis().GetBottom().GetTitle().SetCaption(_T("���ٺ����(��)"));
		m_cSingle.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
		for (int k = 0; k < 31; k++)
			m_cSingle.Series(1).AddXY(10 + k * 1, ecep[k], NULL, NULL);
		break;
	}
	}
}

/////////////////////////////����ȫ�����CEP�仯����////////////////////////////////
void CCCRPDlg::OnBnClickedDrawallcep()
{
	double xveh = 0, yveh = 0;
	double xtarg = 5000.0, ytarg = 2000.0;
	double height = 1000.0;
	double v = 200.0;
	double K = 10.0;
	double u = 10.0;
	double e = 20.0;
	double randND[MKCOUNT];
	double hError, vError, kError, uError, eError;
	double xImp, zImp, xeIP, zeIP;
	double xExp = 0, yExp = 0;
	double xMse = 0, yMse = 0;
	CcrpAim ccrp;
	randGene(randND);
	m_cSingle.Series(0).Clear();
	m_cSingle.Series(1).Clear();
	m_cSingle.GetHeader().SetVisible(FALSE);
	m_cSingle.GetAxis().GetBottom().GetTitle().SetVisible(FALSE);
	m_cSingle.GetAxis().GetLeft().GetTitle().SetVisible(FALSE);
	m_cSumpoint.Series(0).Clear();
	m_cSumpoint.GetHeader().SetVisible(FALSE);
	m_cSumpoint.GetAxis().GetBottom().GetTitle().SetVisible(FALSE);
	m_cSumpoint.GetAxis().GetLeft().GetTitle().SetVisible(FALSE);
	//////////////////////////�߶�-CEP����/////////////////////////
	double xtargh = 15000.0, ytargh = 15000.0;
	double heighth = 1000.0;
	double hcep[46];
	for (int j = 0; j<46; j++)
	{
		for (int i = 0; i < MKCEP; i++)
		{
			hError = heighth + randND[i] * hSigma;
			vError = v + randND[i] * vSigma;
			kError = K + randND[i] * kSigma;
			uError = u + randND[i] * uSigma;
			eError = e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtargh, ytargh, xveh, yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - xtarg);
			yExp = yExp + (zeIP - ytarg);
			xMse = xMse + pow((xeIP - xtargh), 2);
			yMse = yMse + pow((zeIP - ytargh), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCEP;
		yExp = yExp / MKCEP;
		xMse = sqrt(xMse / (MKCEP - 1));
		yMse = sqrt(yMse / (MKCEP - 1));
		hcep[j] = cepCompute(xMse, yMse);
		heighth = heighth + 200;
	}
	m_cSingle.Series(1).Clear();
	m_cHpoint.Series(0).Clear();
	m_cHpoint.Series(1).Clear();
	m_cHpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("�߶�-CEP����")));
	m_cHpoint.GetAxis().GetBottom().GetTitle().SetCaption(_T("�߶�(m)"));
	m_cHpoint.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
	for (int k = 0; k < 46; k++)
		m_cHpoint.Series(1).AddXY(1000 + k * 200, hcep[k], NULL, NULL);
	//////////////////////////����-CEP����/////////////////////////
	double vv = 100.0;
	double vcep[16];
	for (int j = 0; j<16; j++)
	{
		for (int i = 0; i < MKCEP; i++)
		{
			hError = height + randND[i] * hSigma;
			vError = vv + randND[i] * vSigma;
			kError = K + randND[i] * kSigma;
			uError = u + randND[i] * uSigma;
			eError = e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - xtarg);
			yExp = yExp + (zeIP - ytarg);
			xMse = xMse + pow((xeIP - xtarg), 2);
			yMse = yMse + pow((zeIP - ytarg), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCEP;
		yExp = yExp / MKCEP;
		xMse = sqrt(xMse / (MKCEP - 1));
		yMse = sqrt(yMse / (MKCEP - 1));
		vcep[j] = cepCompute(xMse, yMse);
		vv = vv + 10;
	}
	m_cSingle.Series(1).Clear();
	m_cVpoint.Series(0).Clear();
	m_cVpoint.Series(1).Clear();
	m_cVpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("����-CEP����")));
	m_cVpoint.GetAxis().GetBottom().GetTitle().SetCaption(_T("����(m/s)"));
	m_cVpoint.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
	for (int k = 0; k < 16; k++)
		m_cVpoint.Series(1).AddXY(100 + k * 10, vcep[k], NULL, NULL);
	//////////////////////////�����-CEP����/////////////////////////
	double ytargk = 5000.0;
	double Kk = 0;
	double kcep[41];
	for (int j = 0; j<41; j++)
	{
		for (int i = 0; i < MKCEP; i++)
		{
			hError = height + randND[i] * hSigma;
			vError = v + randND[i] * vSigma;
			kError = Kk + randND[i] * kSigma;
			uError = u + randND[i] * uSigma;
			eError = e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytargk, xveh, yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - xtarg);
			yExp = yExp + (zeIP - ytarg);
			xMse = xMse + pow((xeIP - xtarg), 2);
			yMse = yMse + pow((zeIP - ytargk), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCEP;
		yExp = yExp / MKCEP;
		xMse = sqrt(xMse / (MKCEP - 1));
		yMse = sqrt(yMse / (MKCEP - 1));
		kcep[j] = cepCompute(xMse, yMse);
		Kk = Kk + 1;
	}
	m_cSingle.Series(1).Clear();
	m_cKpoint.Series(0).Clear();
	m_cKpoint.Series(1).Clear();
	m_cKpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("�����-CEP����")));
	m_cKpoint.GetAxis().GetBottom().GetTitle().SetCaption(_T("�����(��)"));
	m_cKpoint.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
	for (int k = 0; k < 41; k++)
		m_cKpoint.Series(1).AddXY(0 + k * 1, kcep[k], NULL, NULL);
	//////////////////////////����-CEP����/////////////////////////
	double uu = 10.0;
	double ucep[21];
	for (int j = 0; j<21; j++)
	{
		for (int i = 0; i < MKCEP; i++)
		{
			hError = height + randND[i] * hSigma;
			vError = v + randND[i] * vSigma;
			kError = K + randND[i] * kSigma;
			uError = uu + randND[i] * uSigma;
			eError = e + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - xtarg);
			yExp = yExp + (zeIP - ytarg);
			xMse = xMse + pow((xeIP - xtarg), 2);
			yMse = yMse + pow((zeIP - ytarg), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCEP;
		yExp = yExp / MKCEP;
		xMse = sqrt(xMse / (MKCEP - 1));
		yMse = sqrt(yMse / (MKCEP - 1));
		ucep[j] = cepCompute(xMse, yMse);
		uu = uu + 1;
	}
	m_cSingle.Series(1).Clear();
	m_cUpoint.Series(0).Clear();
	m_cUpoint.Series(1).Clear();
	m_cUpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("����-CEP����")));
	m_cUpoint.GetAxis().GetBottom().GetTitle().SetCaption(_T("����(m/s)"));
	m_cUpoint.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
	for (int k = 0; k < 21; k++)
		m_cUpoint.Series(1).AddXY(10 + k * 1, ucep[k], NULL, NULL);
	//////////////////////////���ٺ����-CEP����/////////////////////////
	double ee = 10.0;
	double ecep[31];
	for (int j = 0; j<31; j++)
	{
		for (int i = 0; i < MKCEP; i++)
		{
			hError = height + randND[i] * hSigma;
			vError = v + randND[i] * vSigma;
			kError = K + randND[i] * kSigma;
			uError = u + randND[i] * uSigma;
			eError = ee + randND[i] * eSigma;
			ccrp.CCRP(hError, vError, omega, kError, uError, eError, deltat, h, xtarg, ytarg, xveh, yveh);
			xeIP = ccrp.output_xbomb(ccrp.output_index());
			zeIP = ccrp.output_zbomb(ccrp.output_index());
			xExp = xExp + (xeIP - xtarg);
			yExp = yExp + (zeIP - ytarg);
			xMse = xMse + pow((xeIP - xtarg), 2);
			yMse = yMse + pow((zeIP - ytarg), 2);
			ccrp.reset();
		}
		xExp = xExp / MKCEP;
		yExp = yExp / MKCEP;
		xMse = sqrt(xMse / (MKCEP - 1));
		yMse = sqrt(yMse / (MKCEP - 1));
		ecep[j] = cepCompute(xMse, yMse);
		ee = ee + 1;
	}
	m_cSingle.Series(1).Clear();
	m_cEpoint.Series(0).Clear();
	m_cEpoint.Series(1).Clear();
	m_cEpoint.GetHeader().GetText().SetItem(0, COleVariant(_T("���ٺ����-CEP����")));
	m_cEpoint.GetAxis().GetBottom().GetTitle().SetCaption(_T("���ٺ����(��)"));
	m_cEpoint.GetAxis().GetLeft().GetTitle().SetCaption(_T("CEP"));
	for (int k = 0; k < 31; k++)
		m_cEpoint.Series(1).AddXY(10 + k * 1, ecep[k], NULL, NULL);
}
