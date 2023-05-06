#pragma once
#include "Rapier.h"

namespace Rapier
{

	class RapierLantern : public Application 
	{
	public:
		RapierLantern();

		~RapierLantern();

		void OnUpdate(DeltaTime dt) override;
		void PostUpdate() override;

		
	private:
	};
}