#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	static float inBetweenTimer = 0;
	//Ball Coordinates
	static std::vector<vector3> pointsArr = { vector3(-4.0f,-2.0f, 5.0f),
		vector3(1.0f,-2.0f, 5.0f),
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};
	
	//Tracks which ball the WallEye was last at
	static int currentPoint = 0;

	matrix4 positionMatrix;
	//Go from current point to next in list
	if (currentPoint <= pointsArr.size() - 2) {
		vector3 distanceMove = glm::lerp(pointsArr[currentPoint], pointsArr[currentPoint+1], inBetweenTimer/fDuration);
		positionMatrix = glm::translate(distanceMove);
	}
	//Unless at the end, then go from current to the first point
	else {
		vector3 distanceMove = glm::lerp(pointsArr[currentPoint], pointsArr[0], inBetweenTimer / fDuration);
		positionMatrix = glm::translate(distanceMove);
	}
	//If enough time has passed to where it would go pass a point
	//use the left over time for lerping to the next point
	if (inBetweenTimer >= 1) {
		inBetweenTimer-= fDuration;
		currentPoint++;
		//If current ball is larger than last point, reset back to 0
		if (currentPoint >= pointsArr.size()) {
			currentPoint = 0;
		}
	}
	inBetweenTimer += fTimeSpan;

	m_pMeshMngr->SetModelMatrix(positionMatrix, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);


	static DWORD startTimeSystem = GetTickCount();
	matrix4 m4sphere1;
	float timer = (float)((GetTickCount() - startTimeSystem) / 1000.0f);
	float timerMapped = MapValue(timer, 0.0f, 5.0f, 0.0f, 1.0f);

	//m_pMeshMngr->AddSphereToRenderList(m4sphere1, RERED, WIRE);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine("Actual time is :" + std::to_string(timer), REYELLOW);
	//Add points in render list
	for (int i = 0; i < pointsArr.size(); i++) {
		m4sphere1 = glm::translate(pointsArr[i]);
		m_pMeshMngr->AddSphereToRenderList(m4sphere1, RERED, WIRE);
	}
	//vector3 v3lerp = glm::lerp(vector3(0, 0, 0), vector3(1, 0, 0), ((float)(GetTickCount() - startTimeSystem) / 1000.0f));
	//m4sphere1 = glm::translate(v3lerp);
	//m_pMeshMngr->SetModelMatrix(m4sphere1);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}