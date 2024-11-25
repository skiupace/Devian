#pragma once
#include <string>
#include <glm/glm.hpp>

namespace DEVIAN {
    namespace GL {
        class GLShader {
        public:
            GLShader() : m_ProgramID(0) {}
            ~GLShader();

            bool LoadFromFile(const std::string&, const std::string&);

            bool LoadFromString(const std::string&, const std::string&);

            void Bind() const;

            void SetFloat(const std::string&, float) const;
            void SetMat4(const std::string&, const glm::mat4&) const;
            void SetMat3(const std::string&, const glm::mat3&) const;

            // Get program ID
            uint32_t GetProgramID() const { return m_ProgramID; }

        private:
            uint32_t m_ProgramID;
            bool CompileAndLink(const std::string&, const std::string&);
        };
    }
}
