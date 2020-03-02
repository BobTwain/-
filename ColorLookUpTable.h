// ColorLookUpTable.h: interface for the CColorLookUpTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_)
#define AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct CColorNode
{//��ɫ���е���ɫ�ڵ�
	float pos;        // 0~1 ,��һ������λ��
	COLORREF color;
	CColorNode(float p=0.f,COLORREF clr=0):pos(p),color(clr){}
};

  class CColorLookUpTable  
{ 
public:
//	void SetColorTable();
	CColorLookUpTable();
	virtual ~CColorLookUpTable();

	void SetValueRange(float min, float max);

	COLORREF GetColor(float pos)const;

	void DrawColorSpectrumRect(CDC* pDC, const CRect& drawRect);
	
	COLORREF LookUpColor(float v) const; //����ɫ���в�ѯvֵ����ɫ

private:
	CArray <CColorNode,CColorNode&> m_ColorTable; //��ɫ��(0~1�ڵ�λ��--->RGB��ɫ)
	float m_ValueMin, m_ValueMax;       //��ֵ�ķ�Χ,�÷�Χ�ڵ���ֵ����ɫ���ڵ���ɫ�໥��Ӧ


};

inline void CColorLookUpTable::SetValueRange(float min, float max)
{
	ASSERT( min < max );
	m_ValueMin = min;
	m_ValueMax = max;
}


#endif // !defined(AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_)
