#pragma once

class CTGuildNormalFrame : public ITInnerFrame
{
public:
	enum InfoEnum
	{
		INFO_GNAME,							///< ����
		INFO_GDATE,							///< ��� ���� ��
		INFO_GMASTER,						///< �����
		INFO_GMASTER_PEER,					///< ����� ����
		INFO_GSUBMASTER1,					///< �� �����
		INFO_GSUBMASTER2,					///< �� �����
		INFO_GMBCNT,						///< ������ ��
		INFO_GLEV,							///< ��� ����
		INFO_GEXP,							///< ��� ����ġ
		INFO_GKIND,							///< ��� ����
		INFO_MYDUTY,						///< ���� ����
		INFO_MYPEER,						///< ���� ����
		INFO_MYCONT,						///< ���� ��� ���嵵
		INFO_GMONEY_RUNE,					///< ��� �ڱ�
		INFO_GMONEY_LUNA,					///< ��� �ڱ�
		INFO_GMONEY_CRON,					///< ��� �ڱ�
		INFO_NOTIFY,						///< ��� ��������
		INFO_GUILD_RANK,
		INFO_GUILD_POINT,
		INFO_GUILD_USEABLE_POINT,
		INFO_COUNT,
	};

protected:
	TComponent*		m_vInfoCtrl[INFO_COUNT];
	TButton* m_pGuildMarkButton;
	TButton* m_pGuildExitButton;
	
	TImageList*		m_pMarkImgset;
	TImageList*		m_pBackImgset;
	TComponent*		m_pBackBase;

public:
	virtual void RequestInfo();
	virtual void ResetInfo();

	void HideComponentWhenTactics();

public:
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual void ShowComponent( BOOL bVisible );

public:
	CTGuildNormalFrame(TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTGuildNormalFrame();
};