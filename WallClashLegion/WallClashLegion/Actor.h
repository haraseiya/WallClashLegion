#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor();
	virtual ~Actor();

	// 更新処理
	void Update(float _deltaTime);

	// アタッチされる全てのコンポーネントを更新
	void UpdateComponent(float _deltaTime);

	// アクター専用のアップデート
	virtual void UpdateActor(float _deltaTime);

	// 入力関連
	void ProcessInput();

	// 位置のゲッター＆セッター
	const Vector3& GetPosition() const { return m_position; }
	void SetPosition(const Vector3& _pos) { m_position = _pos; m_isRecomputeWorldTransform = true; }

	// スケーリングのゲッター＆セッター
	float GetScale() const { return m_scale; }
	void SetScale(float _scale) { m_scale = _scale; m_isRecomputeWorldTransform = true; }

	// 回転のゲッター＆セッター
	const Quaternion& GetRotation() const { return m_rotation; }
	void SetRotation(const Quaternion& _rotation) { m_rotation = _rotation;  m_isRecomputeWorldTransform = true; }

	// ワールド変換行列の計算
	void ComputeWorldTransform();

	// ワールド変換行列のゲット
	const Matrix4& GetWorldTransform() const { return m_worldTransform; }

	// 前進、右方向ベクトルのゲッター
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, m_rotation); }
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, m_rotation); }

	// アクターの状態のゲッター＆セッター
	State GetState() const { return m_state; }
	void SetState(State _state) { m_state = _state; }

	// スピードのゲッター
	float GetSpeed() const { return m_speed; }

	// 前進ベクトルのセッター
	void RotateToNewForward(const Vector3& _forward);

	// アクターIDのゲッター
	int GetID() { return m_id; };

	// コンポーネントの追加・削除
	void AddComponent(class Component* _component);
	void RemoveComponent(class Component* _component);

protected:
	State m_state;								// アクターの状態
	Matrix4 m_worldTransform;					// ワールド変換行列
	Vector3 m_position;							// 位置
	Quaternion m_rotation;						// 回転
	float m_scale;								// スケーリング
	float m_speed;								// スピード
	bool m_isRecomputeWorldTransform;			// ワールド座標の変換の再計算が必要か？
	std::vector<class Component*> m_component;	// コンポーネントの配列
	class Game* m_game;							// ゲームシステムクラスへのポインタ
	int m_id;									// 管理ID
	static int m_globalActorNo;					// 管理ID用の静的カウンタ
};