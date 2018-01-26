#ifndef __CAMERA_H
#define __CAMERA_H

#include <GLFW/glfw3.h>	// include GLFW (which includes the OpenGL header)
#include <glm/glm.hpp>	// include GLM (ideally should only use the GLM headers that are actually used)
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
using namespace glm;	// to avoid having to use glm::

#define MOVEMENT_SENSITIVITY 0.05f		// camera movement sensitivity
#define ROTATION_SENSITIVITY 0.005f		// camera rotation sensitivity

class Camera {
public:
	Camera();
	~Camera();

	void update(GLFWwindow* window);
	void updateYaw(float yaw);
	void updatePitch(float pitch);
	void setViewMatrix(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up);
	void setProjectionMatrix(glm::mat4& matrix);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPosition();

private:
	float mYaw;
	float mPitch;
	glm::vec3 mPosition;
	glm::vec3 mLookAt;
	glm::vec3 mUp;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;
};

#endif