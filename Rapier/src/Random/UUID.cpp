#include "ipch.h"
#include "Random/UUID.h"
#include "Random/Randomizer.h"

namespace Rapier {
	UUID::UUID()
		: m_UUID(Randomizer::RandomUINT64())
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}
}

namespace std {
	template<>
	class std::hash<Rapier::UUID>
	{
		size_t operator()(const Rapier::UUID& uuid) const {
			return std::hash<uint64_t>()((uint64_t)uuid);
		}
	};

	/*
	template<> 
	class std::equal_to<Rapier::UUID>
	{
		using argument_type = Rapier::UUID;
		using result_type = bool;

		bool constexpr operator()(const Rapier::UUID& lhs, const Rapier::UUID& rhs) const {
			return (uint64_t)lhs == (uint64_t)rhs;
		}
	};
	*/
}