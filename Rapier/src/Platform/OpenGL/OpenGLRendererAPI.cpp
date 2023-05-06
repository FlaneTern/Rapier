#include "ipch.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Rapier 
{

	static GLbitfield RapierBufferMaskToOpenGL(uint8_t bufferMask) 
	{
		GLbitfield OpenGLMask = 0;
		if (bufferMask & RapierColorBufferBit)
			OpenGLMask |= GL_COLOR_BUFFER_BIT;

		if (bufferMask & RapierDepthBufferBit)
			OpenGLMask |= GL_DEPTH_BUFFER_BIT;

		if (bufferMask & RapierStencilBufferBit)
			OpenGLMask |= GL_STENCIL_BUFFER_BIT;

		return OpenGLMask;
	}

	static GLenum RapierDepthFunctionToOpenGL(DepthFunction depthfunction) 
	{
		switch (depthfunction)
		{
		case DepthFunction::Never:           return GL_NEVER;
		case DepthFunction::Less:            return GL_LESS;
		case DepthFunction::Equal:           return GL_EQUAL;
		case DepthFunction::LessEqual:       return GL_LEQUAL;
		case DepthFunction::Greater:         return GL_GREATER;
		case DepthFunction::GreaterEqual:    return GL_GEQUAL;
		case DepthFunction::NotEqual:        return GL_NOTEQUAL;
		case DepthFunction::Always:          return GL_ALWAYS;
		}

		RAPIER_CORE_ASSERT(false, "Unkown Depth Function !");
		return 0;
	}

	static DepthFunction OpenGLDepthFunctionToRapier(GLenum depthfunction) 
	{
		switch (depthfunction)
		{
		case GL_NEVER:       return DepthFunction::Never;
		case GL_LESS:        return DepthFunction::Less;
		case GL_EQUAL:       return DepthFunction::Equal;
		case GL_LEQUAL:      return DepthFunction::LessEqual;
		case GL_GREATER:     return DepthFunction::Greater;
		case GL_GEQUAL:      return DepthFunction::GreaterEqual;
		case GL_NOTEQUAL:    return DepthFunction::NotEqual;
		case GL_ALWAYS:      return DepthFunction::Always;
		}

		RAPIER_CORE_ASSERT(false, "Unkown Depth Function !");
		return DepthFunction::Always;
	}

	void OpenGLRendererAPI::Init() 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::Clear(uint8_t bufferMask) 
	{
		glClear(RapierBufferMaskToOpenGL(bufferMask));
	}


	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) 
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}


	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) 
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) 
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) 
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void OpenGLRendererAPI::SetLineWidth(float width) 
	{
		glLineWidth(width);
	}

	void OpenGLRendererAPI::SetDepthFunction(DepthFunction depthfunction) 
	{
		glDepthFunc(RapierDepthFunctionToOpenGL(depthfunction));
	}

	DepthFunction OpenGLRendererAPI::GetDepthFunction() 
	{
		int depthfunction;
		glGetIntegerv(GL_DEPTH_FUNC, &depthfunction);
		return OpenGLDepthFunctionToRapier(depthfunction);
	}
}