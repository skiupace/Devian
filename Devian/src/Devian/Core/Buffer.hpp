#pragma once
#pragma once

#include <vector>

/*
	CPU Buffer
	Holds Pointer To Data And Size In Bytes
*/

namespace DEVIAN {
	class BufferData {
	public:
		BufferData() : m_Data(nullptr), m_Size(0) {}
		BufferData(void* data, uint32_t size) : m_Data(data), m_Size(size) {}

		const void* GetData() const { return m_Data; }
		uint32_t GetSize() const { return m_Size; }

		template <typename T>
		static BufferData CreateFrom(const std::vector<T>& data) {
			return { (void*)data.data(), (uint32_t)(data.size() * sizeof(T)) };
		}

	private:
		const void* m_Data;
		uint32_t m_Size;
	};
}