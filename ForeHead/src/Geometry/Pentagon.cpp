#include "Pentagon.h"

namespace Forehead {

	std::unique_ptr<Pentagon> Pentagon::s_Pentagon = std::make_unique<Pentagon>();
}