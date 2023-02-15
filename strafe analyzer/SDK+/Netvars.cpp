#include "../Interfaces/Interfaces.h"
#include "netvars.h"
#include "fnv1.h"

//antario if i remember correctly
namespace netvar_manager {
	using netvar_key_value_map = std::unordered_map< uint32_t, uintptr_t >;
	using netvar_table_map = std::unordered_map< uint32_t, netvar_key_value_map >;
	void initialize_props(netvar_table_map& table_map);

	uintptr_t get_net_var(const uint32_t table,
		const uint32_t prop) {
		static netvar_table_map map = {};
		if (map.empty())
			initialize_props(map);

		if (map.find(table) == map.end())
			return 0;

		netvar_key_value_map& table_map = map.at(table);
		if (table_map.find(prop) == table_map.end())
			return 0;

		return table_map.at(prop);
	}

	void add_props_for_table(netvar_table_map& table_map, const uint32_t table_name_hash, const std::string& table_name, RecvTable* table, const bool dump_vars, std::map< std::string, std::map< uintptr_t, std::string > >& var_dump, const size_t child_offset = 0) {
		for (auto i = 0; i < table->m_nProps; ++i) {
			auto& prop = table->m_pProps[i];

			if (prop.m_pDataTable && prop.m_nElements > 0) {
				if (std::string(prop.m_pVarName).substr(0, 1) == std::string("0"))
					continue;

				add_props_for_table(table_map, table_name_hash, table_name, prop.m_pDataTable, dump_vars, var_dump, prop.m_Offset + child_offset);
			}

			auto name = std::string(prop.m_pVarName);

			if (name.substr(0, 1) != "m" /*&& name.substr( 0, 1 ) != "b"*/)
				continue;

			const auto name_hash = fnv::hash(prop.m_pVarName);
			const auto offset = uintptr_t(prop.m_Offset) + child_offset;

			table_map[table_name_hash][name_hash] = offset;

			if (dump_vars)
				var_dump[table_name][offset] = prop.m_pVarName;
		}
	}

	void initialize_props(netvar_table_map& table_map) {
		const auto dump_vars = true;  //true if netvar dump

		std::map< std::string, std::map< uintptr_t, std::string > > var_dump;
		for (auto client_class = Interfaces::client->get_client_classes();
			client_class;
			client_class = client_class->m_pNext) {
			const auto table = reinterpret_cast<RecvTable*>(client_class->m_pRecvTable);
			const auto table_name = table->m_pNetTableName;
			const auto table_name_hash = fnv::hash(table_name);

			if (table == nullptr)
				continue;

			add_props_for_table(table_map, table_name_hash, table_name, table, dump_vars, var_dump);
		}
	}
}