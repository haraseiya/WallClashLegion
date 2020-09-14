#pragma once
#include "Game.h"

class Input
{
public:
	enum KEY_STATE
	{
		KEY_STATE_OFF = 0,	// 押されていない
		KEY_STATE_PUSHDOWN,	// 押された瞬間
		KEY_STATE_PRESSED,	// 押され続けている
		KEY_STATE_PULLUP	// 離した瞬間
	};

	// インスタンス
	static Input& InputInstance()
	{
		static Input InputInstance;
		return InputInstance;
	}

	~Input() {};

	// 入力状態の更新
	void Update();

	// キーの入力状態の取得
	char GetInput(Uint8 _SDL_SCANCODE_key);

	// キーが押され続けられている状態か？
	bool IsKeyPressed(Uint8 _SDL_SCANCODE_key);

	// キーが離されたか？
	bool IsKeyPullUp(Uint8 _SDL_SCANCODE_key);

	// キーが押されたか？
	bool IsKeyPushDown(Uint8 _SDL_SCANCODE_key);

	// キーが押されていたか？
	bool IsKeyOff(Uint8 _SDL_SCANCODE_key);

private:
	Input();

	char m_key[256];			// 全キーの状態取得用
	char m_keyState[2][256];	// キー状態[現在/過去フレーム][全キーコード]

	int m_nowKey, m_prevKey;	// 現フレーム、過去フレーム
};

#define INPUT_INSTANCE Input::InputInstance()