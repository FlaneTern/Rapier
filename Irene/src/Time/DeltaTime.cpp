#include "ipch.h"
#include "DeltaTime.h"

namespace IRENE {
	DeltaTime::DeltaTime(std::chrono::high_resolution_clock::time_point prevTime) {
		dt = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - prevTime).count();
	}
}