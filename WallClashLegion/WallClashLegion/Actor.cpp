#include "Actor.h"
#include "Game.h"
#include <algorithm>
#include <typeinfo>

int Actor::m_globalActorNo = 0;

Actor::Actor()
	: m_state(EActive)
	, m_position(Vector3::Zero)
	, m_rotation(Quaternion::Identity)
	, m_scale(1.0f)
	, m_isRecomputeWorldTransform(true)
	, m_id(m_globalActorNo)
	, m_speed(0.0f)
{
	GAMEINSTANCE.AddActor(this);
	m_globalActorNo++;
}

Actor::~Actor()
{
	// アクターが持っているコンポーネント削除
	while (!m_component.empty()) delete m_component.back();

	// ゲームシステム本体にこのアクターの削除を依頼
	GAMEINSTANCE.RemoveActor(this);
}

void Actor::Update(float _deltaTime)
{
	// アクターが生きているときのみ
	if (m_state == EActive)
	{
		ComputeWorldTransform();

		UpdateComponent(_deltaTime);
		UpdateActor(_deltaTime);

		ComputeWorldTransform();
	}
}

void Actor::UpdateComponent(float _deltaTime)
{
}

void Actor::UpdateActor(float _deltaTime)
{
}

void Actor::ProcessInput()
{
}

void Actor::ComputeWorldTransform()
{
}

void Actor::RotateToNewForward(const Vector3& _forward)
{
}

void Actor::AddComponent(Component* _component)
{
}

void Actor::RemoveComponent(Component* _component)
{
}
