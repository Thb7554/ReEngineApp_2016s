#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//Reset world rotation and current expected rotation
		m_mToWorld = matrix4();
		m_m4Rotation = matrix4();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (!bModifier) m_m4Rotation = QuaterionMatrix(1, 0, 0, .025f);
		else m_m4Rotation = QuaterionMatrix(1, 0, 0, -.025f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (!bModifier) m_m4Rotation = QuaterionMatrix(0, 1, 0, .025f);
		else m_m4Rotation = QuaterionMatrix(0, 1, 0, -.025f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (!bModifier) m_m4Rotation = QuaterionMatrix(0, 0, 1, .025f);
		else m_m4Rotation = QuaterionMatrix(0, 0, 1, -.025f);
	}

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);
	m_pCameraMngr->CalculateView();
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}

//Store quaterion information in a 4x4 matrix for rotation
matrix4 AppClass::QuaterionMatrix(float x, float y, float z, float w)
{
	/* LeftHand Verison
	return matrix4	((1 - 2 * y*y - 2 * z*z	, 2 * x*y - 2 * z*w		, 2*x*z + 2 * y*w		, 0,
					2 * x*y + 2 * z*w		, 1 - 2 * x*x - 2 * z*z	, 2 * y*z - 2 * x*w		, 0,
					2 * x*z - 2 * y*w		, 2 * y*z + 2 * x*w		, 1 - 2 * x*x - 2 * y*y	, 0,
					0						,0						, 0						, 1));
	*/
	return matrix4(cos(w) + x*x*(1-cos(w))	, x*y*(1-cos(w))-z*sin(w)	, x*z*(1-cos(w)) + y*sin(w)	, 0,
					y*x*(1-cos(w))+z*sin(w)	, cos(w) +y*y*(1-cos(w))	, y*z*(1-cos(w))-x*sin(w)	, 0,
					z*x*(1-cos(w))-y*sin(w)	, z*y*(1-cos(w))+x*sin(w)	, cos(w)+z*z*(1-cos(w))		, 0,
					0						, 0							, 0							, 1);
}
