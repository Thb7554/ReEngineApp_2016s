#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class CamManager
{
private:
	//Singleton declaration
	static CamManager* instance;
	CamManager() { projMatrix = glm::perspective(90.0f, 4.0f / 2.5f, .01f, 1000.0f); };
	CamManager(CamManager const& other) {};
	CamManager& operator=(CamManager const& other) {};

	matrix4 viewMatrix = matrix4();
	matrix4 projMatrix = matrix4();

	vector3 v3Position;
	vector3 v3Target;
	vector3 v3Up;

public:
	static CamManager* GetInstance() {
		if (instance == nullptr)
			instance = new CamManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != __nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
	matrix4 GetView();
	matrix4 GetProjection(bool bOrtographic);

	void SetPosition(vector3 v3PositionIn);

	void SetTarget(vector3 v3TargetIn);

	void SetUp(vector3 v3UpIn);
	//Translation
	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveUp(float fIncrement);
	//Rotation
	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);
};