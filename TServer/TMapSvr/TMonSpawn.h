#pragma once


class CTMonSpawn
{
public:
	LPTMONSPAWN m_pSPAWN;
	VTMONSTER m_vTMON;

	BYTE m_bStatus;
	DWORD m_dwLeader;
	BYTE m_bGroupOrder; //�׷쳻������ ����.
public:
	CTMonSpawn();
	virtual ~CTMonSpawn();
};
