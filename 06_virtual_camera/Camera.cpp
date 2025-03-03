#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

const float DEF_FOV = 45.f;

Camera::Camera() : mPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
                   mTargetPos(glm::vec3(0.0f, 0.0f, 0.0f)),
                   mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
                   mYaw(glm::pi<float>()),
                   mPitch(0.0f),
                   mRight(glm::vec3(0.0f, 0.0f, 0.0f)),
                   WORLD_UP(glm::vec3(0.0f, 1.0f, 0.0f)),
                   mFOV(DEF_FOV)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(mPosition, mTargetPos, mUp);
}

OrbitCamera::OrbitCamera() : mRadius(10.0f)
{
}

void OrbitCamera::rotate(float yaw, float pitch)
{
    mYaw = glm::radians(yaw);
    mPitch = glm::radians(pitch);

    mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.f + 0.1f,
                        glm::pi<float>() / 2.f - 0.1f);

    updateCameraVectors();
}

void OrbitCamera::setLookAt(const glm::vec3 &target)
{
    mTargetPos = target;
}

void OrbitCamera::setRadius(float radius)
{
    mRadius = glm::clamp(radius, 2.0f, 100.0f);
}

void OrbitCamera::updateCameraVectors()
{
    mPosition.x = mTargetPos.x + mRadius * cos(mPitch) * sin(mYaw);
    mPosition.y = mTargetPos.y + mRadius * sin(mPitch);
    mPosition.z = mTargetPos.z + mRadius * cos(mYaw) * cos(mPitch);
}

// class FPSCamera : public Camera
// {
// public:
//     FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
//               float yaw = glm::pi<float>(),
//               float pitch = 0.0f); // (yaw) initial angle faces -Z

//     void rotate(float yaw, float pitch) override;
//     void setPosition(const glm::vec3 &pos) override;
//     void move(const glm::vec3 &offsetPos) override;

// private:
//     void updateCameraVectors();
// };

FPSCamera::FPSCamera(glm::vec3 position, float yaw, float pitch)
{
    mPosition = position;
    mYaw = yaw;
    mPitch = pitch;
}

void FPSCamera::rotate(float yaw, float pitch)
{
    mYaw += glm::radians(yaw);
    mPitch += glm::radians(pitch);

    mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.f + 0.1f,
                        glm::pi<float>() / 2.f - 0.1f);

    updateCameraVectors();
}

void FPSCamera::setPosition(const glm::vec3 &pos)
{
    mPosition = pos;
}

void FPSCamera::move(const glm::vec3 &offsetPos)
{
    mPosition += offsetPos;
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors()
{
    glm::vec3 look;
    look.x = sin(mYaw) * cos(mPitch);
    look.y = sin(mPitch);
    look.z = cos(mYaw) * cos(mPitch);
    mLook = glm::normalize(look);
    mRight = glm::normalize(glm::cross(mLook, WORLD_UP));
    mUp = glm::normalize(glm::cross(mRight, mLook));

    mTargetPos = mPosition + mLook;
}
