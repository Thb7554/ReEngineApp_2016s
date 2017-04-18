#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bobadilla, Alberto - Gimbal Lock");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}
void AppClass::InitVariables(void)
{
	//Loading the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");

	//Set the axis of Steve visible
	m_pMeshMngr->SetVisibleAxis(true, "Steve");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Rotation matrices
	
	//linear combination
	m_mToWorld = m_mToWorld * m_m4Rotation;
	m_m4Rotation = matrix4();
	//Setting the model matrix
	m_pMeshMngr->SetModelMatrix(m_mToWorld, "Steve");

	//Adding the instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve");

<<<<<<< HEAD

	//Debug information about the world matrix
	m_pMeshMngr->PrintLine("");
=======
	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");//Add a line on top
>>>>>>> 1916e612cfe8ad2068b2a3999ca9918819abc11a
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_pMeshMngr->Print(std::to_string(m_mToWorld[i][j]) + " ", RERED);
		}
		m_pMeshMngr->PrintLine("");
	}
	

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	m_pMeshMngr->Render(); //renders the list of meshes in the system.
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release();
}