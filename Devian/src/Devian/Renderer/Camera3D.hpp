#pragma once
#include <glm/glm.hpp>

namespace DEVIAN {
	struct CameraData {
		glm::vec3 Position = { 0.0f, 0.0f, 3.0f };

		float Fov = 45.0f;
		float NearPlane = 0.1f;
		float FarPlane = 1000.0f;
		float Speed = 10.0f;
		float MovementSmoothness = 5.0f;

		float ScrollSpeedScaler = 1.0f;
		float ScrollSmoothness = 10.0f;

		float TurnSpeed = 0.1f;
		float TurnSmoothness = 10.0f;

		float Pitch = 0.0f;
		float Yaw = -90.0f;
	};

	class Camera3D {
	public:
		Camera3D() = default;
		Camera3D(const glm::vec3&);

		void Update(float);

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		CameraData GetCameraData();

	private:
		CameraData m_CameraData;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraUp;

	private:
		glm::vec3 m_TargetPosition;
		glm::vec3 m_CameraForwardDirection;

		float m_TargetPitch;
		float m_TargetYaw;
		float m_TargetFov;
	};
}