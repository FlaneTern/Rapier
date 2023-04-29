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
	struct hash<Rapier::UUID>
	{
		std::size_t operator()(const Rapier::UUID& uuid) const {
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}