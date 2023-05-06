#pragma once

namespace Rapier 
{

	class RAPIER_API UUID 
	{
	public:
		UUID();
		UUID(uint64_t uuid);

		operator uint64_t() const { return m_UUID; }

		bool operator==(const UUID& other) const
		{
			return (uint64_t)*this == (uint64_t)other;
		}

	private:
		uint64_t m_UUID;
	};
}
