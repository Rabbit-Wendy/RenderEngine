#pragma once

#include "VertexArray.h"

namespace RE {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;
        const Ref<IndexBuffer>& GetIndexBuffer() const override;

	private:
        uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
	};
}