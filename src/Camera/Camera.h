#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 class Camera {


     public:
     void SetPerspective(float fovDeg, float aspect, float zNear, float zFar) {
         fov_ = fovDeg;
         aspect_ =aspect;
    near_ = zNear;
         far_ = zFar;
         proj_ = glm::perspective(glm::radians(fov_), aspect_, near_, far_);


        }
     void SetViewportSize(int width, int height) {
         aspect_ = (height> 0 )? (float)width / (float)height : 1.0f;
         proj_ glm::perspective(glm::radians(fov_), aspect_, near_, far_);

     }

     void SetPosition(glm::vec3 position) {
         pos_ = position;
     }
     void SetYawPitch(float yaw, float pitch) {
         yaw_ = yaw;
         pitch_ = glm::clamp(pitch, -89.0f, 89.0f);
         updateVectors();
     }
     float GetYaw() const {return yaw_;}
     float GetPitch() const {return pitch_;}
    void MoveRelative(const glm::vec3& dirLocal,float speed,float dt) {
         pos_ +=(right_-pos_)*speed*dt;
     }
 }
