#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);
	m_pMesh = new MyMesh();
	
	vector3 topPoint = vector3(0, sqrt(3), 0);

	//Zero out array
	int PascalTriangle[100][100];
	for (int i = 0; i < 65; i++) {
		for (int j = 0; j < 65; j++) {
			PascalTriangle[i][j] = 0;
		}
	}
	//Set First Number to 1
	PascalTriangle[0][1] = 1;

	//Compute the rest of the triangle using first point
	//0 reference in the array is used for calculations, data starts at 1
	for (int i = 1; i < 50; i++) {
		for (int j = 1; j < 50; j++) {
			PascalTriangle[i][j] = PascalTriangle[i - 1][j - 1] + PascalTriangle[i - 1][j];
		}
	}

	//Display the first 16 rows (3 iterations) 
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 100; j++) {
			if (PascalTriangle[i][j] != 0 && PascalTriangle[i][j] % 2 != 0)
			{
				//Calculate where the triangle would be in space based on its place in the array
				topPoint = vector3(0, sqrt(3), 0) + vector3(-2.0f * ((float)(i)/2-j), -sqrt(3) * i, 0.0f);
				m_pMesh->AddVertexPosition(topPoint);
				m_pMesh->AddVertexColor(REGREEN);
				m_pMesh->AddVertexPosition(topPoint + vector3(-1.0f, -sqrt(3), 0.0f));
				m_pMesh->AddVertexColor(RERED);
				m_pMesh->AddVertexPosition(topPoint + vector3(1.0f, -sqrt(3), 0.0f));
				m_pMesh->AddVertexColor(REBLUE);
			}
		}
	}


	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();


}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)											   //clear the screen
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
void AppClass::Triangle(vector3 topPoint, int depth, MyMesh* mMesh) {
	//had issues doing standard recurison
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}

