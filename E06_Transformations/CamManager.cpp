#include "CamManager.h"
matrix4 CamManager::GetView() {
	return viewMatrix;
}
//Using a 4.0 by 2.5 aspect ratio
matrix4 CamManager::GetProjection(bool bOrtographic) {
	//Orthographic
	if (bOrtographic) {
		return glm::ortho(-40.0f, 40.0f, -25.0f, 25.0f, .001f, 1000.0f);
	}
	//Perspective
	else {
		return glm::perspective(90.0f, 4.0f / 2.5f, .01f, 1000.0f);
	}
}

//Take a position and start the camera there
void CamManager::SetPosition(vector3 v3PositionIn) {
	v3Position = v3PositionIn;
	viewMatrix = glm::translate(IDENTITY_M4, v3Position);
}

void CamManager::SetTarget(vector3 v3TargetIn) {
	v3Target = v3TargetIn;
}

void CamManager::SetUp(vector3 v3UpIn) {
	v3Up = v3UpIn;
}

void CamManager::MoveForward(float fIncrement) {
	//Take the components of the matrix to find the vector of each direction
	viewMatrix = glm::translate(viewMatrix, vector3(viewMatrix[0][2],viewMatrix[1][2],viewMatrix[2][2])*fIncrement);
}
void CamManager::MoveSideways(float fIncrement) {
	//Take the components of the matrix to find the vector of each direction
	viewMatrix = glm::translate(viewMatrix, vector3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0])*fIncrement);
}
void CamManager::MoveUp(float fIncrement) {
	//Take the components of the matrix to find the vector of each direction
	viewMatrix = glm::translate(viewMatrix, vector3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1])*fIncrement);
}


//X Rotation
void CamManager::ChangePitch(float fIncrement) {
	//Convert degrees to radians
	fIncrement = fIncrement / 180.0f * PI;
	//Set camera at Identity, rotate, then put back to original position
	matrix4 storeLocation = viewMatrix;
	viewMatrix = IDENTITY_M4;

	//Mix two quats together to get a full rotation and use Increment for Lerp
	quaternion qFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	quaternion qSecond = glm::quat(vector3(PI, 0.0f, 0.0f));
	quaternion quatRotat = glm::mix(qFirst, qSecond, fIncrement);
	matrix4 m4Rotat = glm::mat4_cast(quatRotat);
	viewMatrix = m4Rotat;
	viewMatrix *= storeLocation;
}

void CamManager::ChangeRoll(float fIncrement) {
	fIncrement = fIncrement / 180.0f * PI;
	matrix4 storeLocation = viewMatrix;
	viewMatrix = IDENTITY_M4;

	quaternion qFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	quaternion qSecond = glm::quat(vector3(0.0f, PI, 0.0f));
	quaternion quatRotat = glm::mix(qFirst, qSecond, fIncrement);
	matrix4 m4Rotat = glm::mat4_cast(quatRotat);
	viewMatrix = m4Rotat;
	viewMatrix *= storeLocation;
}

void CamManager::ChangeYaw(float fIncrement) {
	fIncrement = fIncrement / 180.0f * PI;
	matrix4 storeLocation = viewMatrix;
	viewMatrix = IDENTITY_M4;

	quaternion qFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	quaternion qSecond = glm::quat(vector3(0.0f, 0.0f, PI));
	quaternion quatRotat = glm::mix(qFirst, qSecond, fIncrement);
	matrix4 m4Rotat = glm::mat4_cast(quatRotat);
	viewMatrix = m4Rotat;
	viewMatrix *= storeLocation;
}

