#include "AppClass.h"
#include "CamManager.h"

CamManager* CamManager::instance = nullptr;
CamManager* customCam = CamManager::GetInstance();
bool orthoPerspective;
float timer;
void AppClass::InitWindow(String a_sWindowName)
{
	timer = 10.0f;
	orthoPerspective = false;
	super::InitWindow("E06 - 3D Transformations");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Sets the camera
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);
	
	//Set up basic camera
	customCam->SetPosition(vector3(0, 0, -10));
	customCam->SetTarget(vector3(0, 0, 0));
	
	m_pCube = new PrimitiveClass();
	m_pCone = new PrimitiveClass();
	m_pCylinder = new PrimitiveClass();
	m_pTube = new PrimitiveClass();
	m_pSphere = new PrimitiveClass();
	m_pTorus = new PrimitiveClass();

	//Initializing the primitives
	m_pSphere->GenerateSphere(0.5f, 5, REWHITE);
}

void AppClass::Update(void)
{
	timer -= 1.5f;
	const float fSpeed = .3f;
	//This matrices will just place the objects int the right spots
	m_m4Sphere = glm::translate(IDENTITY_M4, vector3(2.5f, 2.5f, 0.0f));

	//This matrices will scale them to the right size
	m_m4Sphere = glm::scale(m_m4Sphere, vector3(2.0f, 2.0f, 2.0f));



	//---Keyboard Controls---
	//Translations
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		customCam->MoveForward(fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		customCam->MoveForward(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		customCam->MoveSideways(fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		customCam->MoveSideways(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		customCam->MoveUp(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		customCam->MoveUp(fSpeed);

	//Rotations
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		customCam->ChangePitch(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		customCam->ChangePitch(fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		customCam->ChangeRoll(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		customCam->ChangeRoll(fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		customCam->ChangeYaw(-fSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		customCam->ChangeYaw(fSpeed);

	//Switch between ortho and perspective
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && timer < 0.0f)
	{
		timer = 10.0f;
		if (orthoPerspective) {
			orthoPerspective = false;
		}
		else {
			orthoPerspective = true;
		}
	}



	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	//CONTROLS
	m_pMeshMngr->PrintLine("       -----Controls-----");
	m_pMeshMngr->PrintLine("Translate |  Rotate  | Perspective");
	m_pMeshMngr->Print("Q", RERED); 
	m_pMeshMngr->Print(" W ", REGREEN);
	m_pMeshMngr->Print("E", RERED);
	m_pMeshMngr->Print("         Y", REPURPLE);
	m_pMeshMngr->Print(" U ", RECYAN);
	m_pMeshMngr->Print("I", REPURPLE);
	m_pMeshMngr->Print("         P", REORANGE);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("A", REYELLOW);
	m_pMeshMngr->Print(" S ", REGREEN);
	m_pMeshMngr->Print("D", REYELLOW);
	m_pMeshMngr->Print("         H", REBLUE);
	m_pMeshMngr->Print(" J ", RECYAN);
	m_pMeshMngr->Print("K", REBLUE);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("View Matrix", RECYAN);

	//Print out view matrix
	m_pMeshMngr->PrintLine("");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_pMeshMngr->Print(std::to_string(customCam->GetView()[i][j]) + " ", REBLUE);
		}
		m_pMeshMngr->PrintLine("");
	}

	//Control rotation using mouse
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
	{
		POINT p;
		//Debug cursor position
		if (GetCursorPos(&p)) {
			m_pMeshMngr->PrintLine(("MouseX: " + std::to_string(p.x) + "MouseY: " + std::to_string(p.y)), REYELLOW);
		}
		//Horizontal Rotation
		customCam->ChangeRoll(-(650-p.x)/325.0f);
		//Vertical Rotation
		customCam->ChangePitch(-(300-p.y)/150.0f);
		//Force user's cursor to be in one spot for better controls
		SetCursorPos(650, 300);
	}
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = customCam->GetProjection(orthoPerspective);
	matrix4 m4View = customCam->GetView();

	//Renders the meshes using the specified position given by the matrix and in the specified color
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere);
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(5,5,5)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(-50, 10, -15)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(-2, -5, -100)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(80, 100, -100)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(10, 4, 30)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(0, -20, 6)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(0, -50, 6)));
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere + glm::translate(vector3(40, -20, 4)));
	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(m_pTube);
	SafeDelete(m_pSphere);
	SafeDelete(m_pTorus);

	super::Release(); //release the memory of the inherited fields
}