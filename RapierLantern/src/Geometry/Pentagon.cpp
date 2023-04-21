#include "Pentagon.h"

namespace Rapier {

	std::unique_ptr<Pentagon> Pentagon::s_Pentagon = std::make_unique<Pentagon>();
}