#pragma once
#include "../Indices/Indices.h"

class C_BaseEntity;
class DVariant;
class CRecvProxyData;
class RecvProp;
class RecvTable;

typedef C_BaseEntity* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();

typedef void(*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void(*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData, int objectID);
typedef void(*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);

class RecvProp
{
public:
	char*				    m_pVarName;
	int						m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;

	bool					m_bInsideArray;

	const void*				m_pExtraData;

	RecvProp*				m_pArrayProp;
	ArrayLengthRecvProxyFn	m_ArrayLengthProxy;

	RecvVarProxyFn			m_ProxyFn;
	DataTableRecvVarProxyFn	m_DataTableProxyFn;

	RecvTable*				m_pDataTable;
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	const char*				m_pParentArrayPropName;
};

class RecvTable {
public:
	RecvProp*	m_pProps;
	int			m_nProps;
	void*		m_pDecoder;
	char*		m_pNetTableName;
	bool		m_bInitialized;
	bool		m_bInMainList;
};

struct ClientClass
{
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;
	char*					m_pNetworkName;
	RecvTable*				m_pRecvTable;
	ClientClass*			m_pNext;
	int						m_ClassID;
};

class IBaseClientDLL {
public:
	ClientClass* get_client_classes() {
		using original_fn = ClientClass * (__thiscall*)(IBaseClientDLL*);
		return (*reinterpret_cast<original_fn**>(this))[Indices::get_client_classes](this);
	}
};

class IClientMode
{
public:
};