#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
    glm::mat4 getViewMatrix() const;
    virtual void rotate(float yaw, float pitch) {} // in degrees

protected:
    Camera();

    glm::vec3 mPosition;
    glm::vec3 mTargetPos;
    glm::vec3 mUp;

    // Euler angles (in radians)
    float mYaw;
    float mPitch;
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