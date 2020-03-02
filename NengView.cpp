// NengView.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "NengView.h"
#include "MainFrm.h"
#include "Math.h"
#include "DrawView.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
bool drawfromfiledone = false;
bool b_lianfang = false;
WORD *buf=NULL;
int pointNumb;
// int m_qishi;
int lianfang;	//-1������״̬��0Ϊ32�����ţ�1Ϊʱ����������
int m_xianshu=0;
//int m_cha=0;
int cx,cy;
long step;

//float xiuzheng;
//float m_liangcheng;
float m_beishu;
//int m_qishi1=0;
//int m_jieshu=0;
CString str;
extern CString gbLocation;
extern CString gbLocation1;


extern int gbLineNo; 
extern CString strText;

IMPLEMENT_DYNCREATE(CNengView, CFormView)

CNengView::CNengView()
	: CFormView(CNengView::IDD)
{
	//{{AFX_DATA_INIT(CNengView)
	m_strPath = _T("");
	m_nLineNumb = 0;
	m_yanse = 0;
	m_shezhi = 20;
	m_showangle = _T("");
	m_banjing = _T("");
	m_xian = 0;
	m_dianya = _T("");
	m_n = 1.0;
	yuzhi = 20;
	m_liangcheng = 2;
	m_HeadNumb = 0;
	m_beishu = 1.0;
	lianfang = -1;
	m_azinum = 0;
	fengxiang =  0.0f;
	hangxiang =  0.0f;
	ptemp1=(0,0);
	ptemp2=(0,0);
	ptemp3=(0,0);
	ptemp4=(0,0);
	//}}AFX_DATA_INIT	
	
}

CNengView::~CNengView()
{
	if(buf)
	{
			delete []buf;
			buf = NULL;
	}
}

void CNengView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNengView)
	DDX_Control(pDX, IDC_SLIDER1, m_slider1);
	DDX_Control(pDX, IDC_COMBO1, m_strPointNumb);
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
	DDX_Text(pDX, IDC_EDIT2, m_nLineNumb);
	DDX_Radio(pDX, IDC_RADIO1, m_yanse);
	DDX_Text(pDX, IDC_EDIT3, m_shezhi);
	DDX_Text(pDX, IDC_EDIT4, m_showangle);
	DDX_Text(pDX, IDC_EDIT6, m_banjing);
	DDX_Text(pDX, IDC_EDIT8, m_xian);
	DDX_Text(pDX, IDC_EDIT9, m_dianya);
	DDX_Text(pDX, IDC_EDIT11, m_n);
	DDX_Slider(pDX, IDC_SLIDER1, yuzhi);
	DDX_Radio(pDX, IDC_RADIO3, m_liangcheng);
	DDX_Text(pDX, IDC_EDIT5, m_HeadNumb);
	DDX_Text(pDX, IDC_EDIT7, m_azinum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNengView, CFormView)
	//{{AFX_MSG_MAP(CNengView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MESSAGE_DISPLAYLINE,DisPlayLine)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNengView diagnostics

#ifdef _DEBUG
void CNengView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNengView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNengView message handlers

void CNengView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	static char BASED_CODE szFilter[] = "�״�ͼ������(*.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);


	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="��ͣ"))		//���������ʱ��ͣ����״̬
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"����");
	}
		
	
	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		
		lianfang=-1;
		if(GetDlgItemText(IDC_BUTTON5,str),str!="��ͣ")	
		SetDlgItemText(IDC_BUTTON5,"��ͣ");

		b_lianfang = false;
		UpdateData(false);

		this->OnButton2();
	}

}

void CNengView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	this->m_pFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	// TODO: Add your specialized code here and/or call the base class

	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1300");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1500");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2048");
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("600");
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(3);
	m_slider1.SetRange(1,50,TRUE);
    m_slider1.SetPos(yuzhi);

    UpdateData(false);
}

void CNengView::OnButton2() 
{
    UpdateData(TRUE);

	static const double pi = 3.141592654;
    int Index = m_strPointNumb.GetCurSel();//ȥ�ĵ�ǰ�����˵����±�
	bool biao1=false;
    bool biao2=false;

    long filelength;

    switch(Index)
	{
	   case 0: 
		   {
			pointNumb=1300;
		    break;
		   }
	   case 1:
		   {
			pointNumb=1500;
		    break;
		   }
       case 2:
		   {
			pointNumb=2048;
		    break;
		   }
        case 3:
		   {
			pointNumb=600;
		    break;
		   }
	   default:
		   break;
	}

	FILE *stream;
	
	if( (stream = fopen( m_strPath, "rb" )) != NULL )
	{	
		fseek(stream, 0L, SEEK_END );
		filelength = ftell(stream);//�õ��ļ��Ĵ�С
	
        fseek(stream, 0L, SEEK_SET );//��λ���ļ��Ŀ�ͷ
		if(buf)
		{
			delete []buf;
			buf=NULL;
		}//��̬�ڴ��ͷ�

		buf = new WORD[filelength/2];
      
		if(buf==NULL)//û�м����ļ�
		{
			MessageBox("�����ڴ����");
		}
        
	    fread(buf, sizeof(WORD), filelength/2, stream);//����������
		fclose(stream); 

	}
	 		 
	else if(b_lianfang)
	{	 
		KillTimer(1);
		MessageBox("��ǰʱ�����в���32��ͼ��");
		
		m_nMap--;
		CString pathname = m_strPath.Left(m_strPath.ReverseFind('_'));//���ļ�������pathname
		m_strPath.Format("%s_%02d.dat",pathname,m_nMap);
		return;
	}
	
	else
	{	 
		MessageBox("���ļ�������ѡ���ļ�"); 
		return;
	}
//////////////////////////////////////////////////////////////////////////

	m_xianshu=buf[1557];
	m_nLineNumb=m_xianshu;
    UpdateData(false);

    HDC hMYDC;//������һ������ΪHDC�ı���hMYDC
	hMYDC = ::GetDC(m_pFrm->m_pLeftView->m_hWnd);//��ô��ڵ��豸������
	CRect rect;
	::GetClientRect(m_pFrm->m_pLeftView->m_hWnd,&rect);//��û�ͼ�����򣬲���rectָ����

	CClientDC dc(m_pFrm->m_pLeftView);//��ʼ��ͼ

	cx = rect.right / 2;
	cy = rect.bottom / 2;

	HPEN hYellowPen = CreatePen(PS_SOLID,1,RGB(255,255,0));//����һ����ɫ�Ļ���
    SelectObject(hMYDC, hYellowPen);//����ɫ����ѡ��hMYDC
	MoveToEx(hMYDC, cx, cy, NULL);//�ƶ������������
	LineTo(hMYDC, cx, rect.top );//����ɫ�����ź���

    if(cx>cy)//ͼ����߽����С����Ϊ10�����ݶԴ��ڴ�С�ĵ������Ʋ�ͬ��С��ͼ��
	{
		step = 600/((cy-10))+1;//step�ǵ��ڴ�Сʹ�õ�
	}
	else
	{
		step = 600/((cx-90))+1;
	}
	
/////////////////////////////�������־////////////////////////////////
	CPen black(PS_SOLID, 3, RGB(0,0,0));	//�����Ϸ����µķ����߼���������ɫ���ʣ�
	dc.SelectObject(black);
	dc.MoveTo(ptemp1);
	dc.LineTo(ptemp2);

	dc.MoveTo(ptemp3);
	dc.LineTo(ptemp1);

	dc.MoveTo(ptemp4);
	dc.LineTo(ptemp1);

	hangxiang = (float)GetValue(1,6,4)*180*pow(2,-30);
	fengxiang = (float)GetValue(2,26,2)*180*pow(2,-14);

	float w_angle;	//������������ƫ�ƽǶ�
	w_angle = 360-hangxiang+fengxiang;
	if(w_angle-360 > 0.0005)
		w_angle-=360;
	CPoint point1,point2,point3,point4,ptemp;

	point1.x = cx + (600+10)/step*sin(pi*w_angle/180);
	point1.y = cy - (600+10)/step*cos(pi*w_angle/180);

	point2.x = cx + (600+70)/step*sin(pi*w_angle/180);
	point2.y = cy - (600+70)/step*cos(pi*w_angle/180);
	
//////////////////////////////////////////////////////////////////////////
	double Angle = 30*pi/180;	//20��
//	double	proportion = 0.6;
	double	Sin   = sin(Angle),   Cos  = cos(Angle);
	double	Sin2  = sin(-Angle),  Cos2 = cos(-Angle);
	
	ptemp.x = cx + (600+40)/step*sin(pi*w_angle/180);
	ptemp.y = cy - (600+40)/step*cos(pi*w_angle/180);

	int	nTempX	 = ptemp.x-point1.x;
	int nTempY	 = ptemp.y-point1.y;

	point3.x = (int)(nTempX*Cos - nTempY*Sin) + point1.x;//������ֹ��
	point3.y = (int)(nTempX*Sin + nTempY*Cos) + point1.y;
	point4.x = (int)(nTempX*Cos2 - nTempY*Sin2) + point1.x;//������ֹ��
	point4.y = (int)(nTempX*Sin2 + nTempY*Cos2) + point1.y;

//////////////////////////////////////////////////////////////////////////

	CPen pencolor(PS_SOLID, 3, RGB(0,255,255));
	dc.SelectObject(pencolor);

	dc.MoveTo(point1);
	dc.LineTo(point2);

	dc.MoveTo(point3);
	dc.LineTo(point1);

	dc.MoveTo(point4);
	dc.LineTo(point1);
	
	ptemp1 = point1;
	ptemp2 = point2;
	ptemp3 = point3;
	ptemp4 = point4;

//////////////////////////////////////////////////////////////////////////

	this->ZitiInfo();		//��ʾͼ�����ĵ�����Ϣ
	this->SiglCount();		// ���㷽λ���ʹ����ź��еĴ�������

////////////////////////////��ʾɫ��/////////////////////////////////////////////

	m_rect_color.left = (cx-600/step)/3+5;
	m_rect_color.right =m_rect_color.left+20;
	m_rect_color.top = cy-400/step;
	m_rect_color.bottom =cy+ 400/step;

	if(m_yanse==2)				//α��ʱ��ʾɫ��
	{	
		float ff= 2.5/50*yuzhi;
		float fffvalue = (float)0.18;

		CDC *pDC=CDC::FromHandle(hMYDC);		
		m_colortable.SetValueRange(fffvalue,ff);
		this->m_colortable.DrawColorSpectrumRect(pDC,m_rect_color);
		ReleaseDC(pDC);
	}
	else
	{
		CRect m_rect(m_rect_color);
		m_rect.left=m_rect_color.left-25;//25Ϊɫ��ֵ�Ŀ��
		m_rect.right=m_rect_color.right;
		m_rect.top=m_rect_color.top-10;
		m_rect.bottom=m_rect_color.bottom+10;
		
		CBrush brush(RGB(0,0,0));
		dc.FillRect(m_rect,&brush);
	}
//////////////////////////////////////////////////////////////////////////

	this->CRadarDraw();		//draw the radar image

//////////////////////////////////////////////////////////////////////////
	
   UpdateData(false);
   drawfromfiledone = true;
   
}

void CNengView::OnRadio1() 
{

	m_yanse=0;
}

void CNengView::OnRadio2() 
{

	m_yanse=1;
}

void CNengView::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	m_yanse=2;
}

void CNengView::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_shezhi=m_slider1.GetPos();
    yuzhi=m_shezhi;
	m_n=2.5/50*m_shezhi;
    UpdateData(false);
	*pResult = 0;
}

void CNengView::DisPlayLine(LPARAM lp, WPARAM wp)
{
	m_showangle = gbLocation;
    m_banjing= gbLocation1;
	m_xian=gbLineNo;
	m_dianya=strText;
	UpdateData(FALSE);

}


void CNengView::OnButton3() 
{
	// TODO: Add your control notification handler code here


 	UpdateData(TRUE);


	static char BASED_CODE szFilter[] = "�״�ͼ������(*.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*_01.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="��ͣ"))
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"����");
	}

	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
	    m_nMap=1;
		lianfang=0;

		SetDlgItemText(IDC_BUTTON5,"��ͣ");
		b_lianfang = true;
		UpdateData(false);
	    SetTimer(1, 100, 0);

	}

}

void CNengView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(lianfang==0)
	{

		if(m_nMap>32)
		{
		  KillTimer(1);
		  lianfang =-1;
//		  m_nMap=1;
		  b_lianfang = false;
		  return;
		}
		CString filename1 = m_strPath.Left(m_strPath.ReverseFind('_'));
		CString filename2;
		filename2.Format("%s_%02d.dat",filename1,m_nMap);
		m_strPath =filename2;
		
		UpdateData(false);
		this->OnButton2();

		m_nMap++;
	}

	else if(lianfang==1)
	{
		WIN32_FIND_DATA filedata;
		
		CString filepath1 = m_strPath.Left(m_strPath.ReverseFind('\\'));
		CString filepath2;
		filepath2.Format("%s\\*_01.dat",filepath1);
	
		HANDLE hfind=FindFirstFile(filepath2,&filedata);
		
		CString filepath; 
			
		filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		
		while (m_strPath!=filepath)
		{
			FindNextFile(hfind,&filedata);
			filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		}
		
		UpdateData(false);
		this->OnButton2();
		
		if(FindNextFile(hfind,&filedata)!=0)
		{
		filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		m_strPath=filepath;
		}
		else 
		{
			KillTimer(1);
			lianfang=-1;
			FindClose(hfind);
			b_lianfang = false;
		}		
	}
	
	CFormView::OnTimer(nIDEvent);
}

void CNengView::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	if(lianfang!= -1  && (GetDlgItemText(IDC_BUTTON5,str),str=="��ͣ"))		//����->ֹͣ
		
	{ 
			KillTimer(1);

			SetDlgItemText(IDC_BUTTON5,"����");
			b_lianfang = false;
	}

	else if (lianfang!= -1  && (GetDlgItemText(IDC_BUTTON5,str),str=="����"))	//ֹͣ->����
	{	
		SetTimer(1,100,0);
		SetDlgItemText(IDC_BUTTON5,"��ͣ");
		b_lianfang = true;
	}
	UpdateData(FALSE);
}

void CNengView::OnButton6() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);


	static char BASED_CODE szFilter[] = "�״�ͼ������(*_01.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*_01.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="��ͣ"))
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"����");
	}

	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		lianfang=1;

		SetDlgItemText(IDC_BUTTON5,"��ͣ");
		b_lianfang = true;
		UpdateData(false);

	    SetTimer(1, 100, 0);
	}

}


void CNengView::OnRadio3() 
{
	// TODO: Add your control notification handler code here

	m_liangcheng = 0;
	m_beishu = 3.0;

}

void CNengView::OnRadio4() 
{
	// TODO: Add your control notification handler code here

	m_liangcheng = 1;
	m_beishu = 1.5;

}

void CNengView::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	m_liangcheng = 2;
	m_beishu = 1.0;
}



void CNengView::SiglCount()
{
	unsigned short H_voltage=0;
	unsigned short aziVolNow,aziVolNext;
	m_HeadNumb=0;
	m_azinum=0;
	
	for(int i=0;i<m_xianshu;i++)
	{
		H_voltage=buf[i*pointNumb+5158]&0x4000;
		
		if (H_voltage==0x4000)
			m_HeadNumb++;
		
		else 
			break;
	} 

	for (int k=0;k<m_xianshu-1;k++)
	{
		aziVolNow =	buf[k*pointNumb+5158]&0x8000;
		aziVolNext = buf[(k+1)*pointNumb+5158]&0x8000;	
		
		if (aziVolNow==0 && aziVolNext==0x8000)
			m_azinum++;
		else 
			continue;
	}
		
}

void CNengView::CRadarDraw()
{
	
	static const double pi = 3.141592654;

	int n=0;
	unsigned short f=0;

	long i,j;
	int color;
	float angle=0.0;

    float zhi1=0.0;////��ѹֵ
	float ff= 2.5/50*yuzhi;
	float fffvalue = (float)0.18;

    HDC hMYDC;
	hMYDC = ::GetDC(m_pFrm->m_pLeftView->m_hWnd);
    

if (m_beishu==1.0||m_beishu==1.5)	//draw the radar image in 1.5 or 2.4 sea miles
{

	for(i=0;i<m_xianshu;i++)
	{
		
		angle+=(360.0/m_xianshu); //��360����������ƽ��
		for(j=0;j<600/m_beishu;j++)
		{ 
			
			int cx1=int(cx+(j)*(m_beishu/step)*sin(pi*angle/180.0));
			int cy1=int(cy-(j)*(m_beishu/step)*cos(pi*angle/180.0));
			f=buf[i*pointNumb+j+5158]&0x3fff;//���������ߵĵ���					
			zhi1=(float)f*2.5/8191.0;//�����õ�ĵ�ѹֵ
			if(m_yanse==0)//ѡ���ɫʱ
			{	
				if(zhi1>ff)//��ѹֵ��������ʱ
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));//���������õ�ѹ������Ϊ��ɫ
				}
				else 
				{									
					color=zhi1*255/ff;//��ѹ��������ʱ
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));//
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,255));//�����ڵ�����Ϊ��ɫ
					
				}
				
			}
			else if(m_yanse==1)//ѡ��ڰ�ʱ
			{ 
				if(zhi1>ff)//�������õ�
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));//���������õ��ѹ�õ㻭�ɰ�ɫ
				}
				else 
				{
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}
			}
			
			else//��ѡ��Ϊα��ʱ
			{										
			
				if(zhi1>ff)
				{
					zhi1=ff;
				}  // ����һ�жϱ�����ͼʱ����
				
				if(zhi1>=fffvalue)
				{	
					m_clrMapColor=m_colortable.LookUpColor((float)zhi1);
					SetPixel(hMYDC,cx1, cy1,m_clrMapColor);
				}
				else
				{
					SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));//���ɺ�ɫ
				}	
			}
		}
		
	}	

}  

if (m_beishu==3.0)				//��ʾ0.75�����״�ͼ��
{
	for(i=0;i<m_xianshu;i++)
	{
		
		angle+=(360.0/m_xianshu);
		for(int k=0;k<600/step;k++)		//j==200��
		{ 
			
			int j=k*step/m_beishu;
			int	cx1=int(cx+k*sin(pi*angle/180.0));
			int	cy1=int(cy-k*cos(pi*angle/180.0));
			
			
			f=buf[i*pointNumb+j+5158]&0x3fff;					
			zhi1=(float)f*2.5/8191.0;		//200��Ķ�Ӧ��ѹֵ,8191�Ǹ�ɶ��
			if(m_yanse==0)
			{	
				if(zhi1>ff)
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));
				}
				else 
				{									
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,255));
					
				}
				
			}
			else if(m_yanse==1)
			{ 
				if(zhi1>ff)
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
				}
				else 
				{
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}
			}
			else
			{										
				
				if(zhi1>ff)
				{
					zhi1=ff;
				}  
				
				if(zhi1>=fffvalue)
				{	
					m_clrMapColor=m_colortable.LookUpColor((float)zhi1);
					SetPixel(hMYDC,cx1, cy1,m_clrMapColor);
				}
				else
				{
					SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}	
			}
			
		}
		
	}	

}
 
   m_pFrm->m_pLeftView->Diaplay1();

}

CNengView::GetValue(short flag, short position, short length)
{					//flag-������Ϣ������־��position-��Ϣ����Ӧ�������ƫ��
					//lengthΪ��Ϣ�ĳ���
	int value1=0;
	short value2=0;
	DWORD a[2]={0,0};

	if(flag==1)				//flag==1,������Ϣ1;
	{	
		int i=6+position/2;//bufΪword���飬�ʽ�position��2;
		
		switch(length)
		{
		case 2:
			
			value2=WORD((buf[i]<<8) | (buf[i]>>8));
				return value2;
			break;			//����2�ֽڵ�˳��
			
		case 4:
			
			a[0]=WORD(buf[i]<<8) | (buf[i]>>8);
			a[1]=WORD(buf[i+1]<<8) | (buf[i+1]>>8);
			value1=(a[0]<<16) | a[1];		//���Ϊ4�ֽ���ʽ
				return value1;
			break;		
			
		default:
			return 0;
			break;
		}
	}
	else				//flag==2,������Ϣ2;
	{
		int i=1507+position/2;
		
		switch(length)
		{
		case 2:
			
			value2=WORD((buf[i]<<8) | (buf[i]>>8));
				return value2;
			break;			//����2�ֽڵ�˳��
			
		case 4:
			
			a[0]=WORD(buf[i]<<8) | (buf[i]>>8);
			a[1]=WORD(buf[i+1]<<8) | (buf[i+1]>>8);
			value1=(a[0]<<16) | a[1];		//���Ϊ4�ֽ���ʽ
				return value1;
			break;		
			
		default:
			return 0;
			break;
		}
	}
}




void CNengView::ZitiInfo()
{
////////////////show the current filename/navInfomation on the LeftView //////////////
	
	CString filename1 = m_strPath.Right(strlen(m_strPath) - m_strPath.ReverseFind('\\')-1);
	CString filename2 = filename1.Left(filename1.ReverseFind('.'));

	CRect rect;
	::GetClientRect(m_pFrm->m_pLeftView->m_hWnd,&rect);
	
	CClientDC dc(m_pFrm->m_pLeftView);
	CFont font;
	font.CreatePointFont(320/step,"����_GB2312",NULL);
	CFont * pOldFont = dc.SelectObject(&font);
	
//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(RGB(0,0,0));
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(20,20,filename2);

//  ע�����µ�����Ϣ�����ո��Ǹ���ˢ���ϸ�ͼ��������Ϣ

	m_hangsu.Format("����:%+.2f��   ",(float)GetValue(2,18,2)*0.01);
	dc.TextOut(rect.right-185,10,m_hangsu);	
	m_hangxiang.Format("����:%.2f��   ",(float)GetValue(1,6,4)*180*pow(2,-30));
	dc.TextOut(rect.right-200,35,m_hangxiang);
	m_fengsu.Format("����:%.2fm/s   ",(float)GetValue(2,28,2)*0.01);
	dc.TextOut(rect.right-185,60,m_fengsu);
	m_fengxiang.Format("����:%.2f��   ",(float)GetValue(2,26,2)*180*pow(2,-14));
	dc.TextOut(rect.right-160,85,m_fengxiang);
//�ݺ�ҡһ���ո�����3�ո�
	m_zongyao.Format("��ҡ:%+.2f�� ",(float)GetValue(1,10,4)*90*pow(2,-30));
	dc.TextOut(10,rect.bottom-110,m_zongyao);
	m_hengyao.Format("��ҡ:%+.2f�� ",(float)GetValue(1,14,4)*90*pow(2,-30));
	dc.TextOut(40,rect.bottom-80,m_hengyao);
	m_haishen.Format("����:%.2fm   ",(float)GetValue(2,14,4)*0.01);
	dc.TextOut(25,rect.bottom-50,m_haishen);
//�����ո�
	m_dongsu.Format("����:%+.2f��  ",(float)GetValue(2,22,2)*0.01);
		dc.TextOut(rect.right-150,rect.bottom-110,m_dongsu);
	m_beisu.Format("����:%+.2f��  ",(float)GetValue(2,24,2)*0.01);
		dc.TextOut(rect.right-170,rect.bottom-80,m_beisu);
	m_disu.Format("����:%.2f��  ",(float)GetValue(2,20,2)*0.01);
		dc.TextOut(rect.right-160,rect.bottom-50,m_disu);
	
	dc.SelectObject(pOldFont);

/////////////////////////////////////////////////////////////////////////////////
}
