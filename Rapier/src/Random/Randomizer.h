#pragma once

namespace Rapier {
	class RAPIER_API Randomizer {
	public:
		static uint32_t RandomUINT32(uint32_t minimum = 0, uint32_t maximum = 0xffffffff);
		static uint64_t RandomUINT64(uint64_t minimum = 0, uint64_t maximum = 0xffffffffffffffff);
	};
}