
#include "StdAfx.h"
#include "PhatSDK.h"

#define WEENIE_DEFAULTS_FILE_VERSION 2

CWeenieDefaults::CWeenieDefaults()
{
	m_FileVersion = WEENIE_DEFAULTS_FILE_VERSION;
	m_Timestamp = time(NULL);
}

CWeenieDefaults::~CWeenieDefaults()
{
}

DEFINE_PACK(CWeenieDefaults)
{
	pWriter->Write<DWORD>(WEENIE_DEFAULTS_FILE_VERSION);
	pWriter->Write<std::string>(m_Description);
	pWriter->Write<DWORD>(m_Timestamp);
	m_Qualities.Pack(pWriter);
	m_WorldObjDesc.Pack(pWriter);
	pWriter->Write<BYTE>(m_bIsAutoGenerated ? 1 : 0);
}

DEFINE_UNPACK(CWeenieDefaults)
{
	m_FileVersion = pReader->Read<DWORD>();
	m_Description = pReader->ReadString();
	m_Timestamp = pReader->Read<DWORD>();

	if (pReader->GetLastError())
		return false;

	m_Qualities.UnPack(pReader);

	if (pReader->GetLastError())
		return false;

	m_WCID = m_Qualities.GetID();

	if (m_FileVersion >= 2)
	{
		m_WorldObjDesc.UnPack(pReader);
		m_bIsAutoGenerated = pReader->Read<BYTE>() ? true : false;
	}

	return true;
}