#pragma once

class IClientEntity;

class IClientEntityList
{
public:

	IClientEntity* get_client_entity(int idx)
	{
		using original_fn = IClientEntity * (__thiscall*)(IClientEntityList*, int);
		return (*reinterpret_cast<original_fn**>(this))[3](this, idx);
	}
};