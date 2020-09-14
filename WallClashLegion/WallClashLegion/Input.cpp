#include "Input.h"

Input::Input()
	: m_nowKey(0)
	, m_prevKey(1)
{
	for (int i = 0; i < 256; i++)
	{
		m_key[i] = 0;
		m_keyState[m_nowKey][i] = KEY_STATE_OFF;
		m_keyState[m_prevKey][i] = KEY_STATE_OFF;
	}
}

void Input::Update()
{
	// ���݂̃L�[��1�O�̃L�[�̓��͏�Ԃ����ւ���
	m_nowKey ^= 1;
	m_prevKey = m_nowKey ^ 1;

	// �L�[��Ԏ擾
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	memcpy(m_keyState[m_nowKey], keys, sizeof(char) * 256);

	for (int i = 0; i < 256; i++)
	{
		char nowInput = m_keyState[m_nowKey][i];
		char prevInput = m_keyState[m_prevKey][i];

		if (nowInput)	// ���݃L�[��������Ă���
		{
			// �O�̃t���[����������Ă�����
			if (prevInput)  m_key[i] = KEY_STATE_PRESSED;	// ��������ςȂ�
			else			m_key[i] = KEY_STATE_PUSHDOWN;	// �������ꂽ
		}
		else			// ���݃L�[�͉�����Ă��Ȃ�
		{
			// �O�̃t���[���ŉ�����Ă�����
			if (prevInput) m_key[i] = KEY_STATE_PULLUP;
			else		   m_key[i] = KEY_STATE_OFF;
		}
	}
}

char Input::GetInput(Uint8 _SDL_SCANCODE_key)
{
	return m_key[_SDL_SCANCODE_key];
}

bool Input::IsKeyPressed(Uint8 _SDL_SCANCODE_key)
{
	return m_key[_SDL_SCANCODE_key]==KEY_STATE_PRESSED;
}

bool Input::IsKeyPullUp(Uint8 _SDL_SCANCODE_key)
{
	return m_key[_SDL_SCANCODE_key] == KEY_STATE_PULLUP;
}

bool Input::IsKeyPushDown(Uint8 _SDL_SCANCODE_key)
{
	return m_key[_SDL_SCANCODE_key] == KEY_STATE_PUSHDOWN;
}

bool Input::IsKeyOff(Uint8 _SDL_SCANCODE_key)
{
	return m_key[_SDL_SCANCODE_key] == KEY_STATE_OFF;
}
