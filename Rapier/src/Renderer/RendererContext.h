#pragma once

namespace Rapier 
{
	class RendererContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}