#pragma once

#include "glm/glm.hpp"
#include <glm/ext/scalar_constants.hpp>

class Camera
{
public:
    glm::mat4 getViewMatrix() const;
    virtual void rotate(float yaw, float pitch) {} // in degrees
    virtual void setPosition(const glm::vec3 &pos) {}
    virtual void move(const glm::vec3 &offsetPos) {}

    const glm::vec3 &getLook() const { return mLook; }
    const glm::vec3 &getRight() const { return mRight; }
    const glm::vec3 &getUp() const { return mUp; }

    float getFOV() const { return mFOV; }
    void setFOV(float fov) { mFOV = fov; }

protected:
    Camera();

    glm::vec3 mPosition;
    glm::vec3 mTargetPos;
    glm::vec3 mUp;

    glm::vec3 mLook;
    glm::vec3 mRight;
    const glm::vec3 WORLD_UP;

    // Euler angles (in radians)
    float mYaw;
    float mPitch;

    float mFOV; // degrees
};

class OrbitCamera : public Camera
{
public:
    OrbitCamera();

    void rotate(float yaw, float pitch) override;

    void setLookAt(const glm::vec3 &target);
    void setRadius(float radius);

private:
    void updateCameraVectors();

    float mRadius;
};

class FPSCamera : public Camera
{
public:
    FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
              float yaw = glm::pi<float>(),
              float pitch = 0.0f); // (yaw) initial angle faces -Z

    void rotate(float yaw, float pitch) override;
    void setPosition(const glm::vec3 &pos) override;
    void move(const glm::vec3 &offsetPos) override;

private:
    void updateCameraVectors();
};