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

	// �X�V����
	void Update(float _deltaTime);

	// �A�^�b�`�����S�ẴR���|�[�l���g���X�V
	void UpdateComponent(float _deltaTime);

	// �A�N�^�[��p�̃A�b�v�f�[�g
	virtual void UpdateActor(float _deltaTime);

	// ���͊֘A
	void ProcessInput();

	// �ʒu�̃Q�b�^�[���Z�b�^�[
	const Vector3& GetPosition() const { return m_position; }
	void SetPosition(const Vector3& _pos) { m_position = _pos; m_isRecomputeWorldTransform = true; }

	// �X�P�[�����O�̃Q�b�^�[���Z�b�^�[
	float GetScale() const { return m_scale; }
	void SetScale(float _scale) { m_scale = _scale; m_isRecomputeWorldTransform = true; }

	// ��]�̃Q�b�^�[���Z�b�^�[
	const Quaternion& GetRotation() const { return m_rotation; }
	void SetRotation(const Quaternion& _rotation) { m_rotation = _rotation;  m_isRecomputeWorldTransform = true; }

	// ���[���h�ϊ��s��̌v�Z
	void ComputeWorldTransform();

	// ���[���h�ϊ��s��̃Q�b�g
	const Matrix4& GetWorldTransform() const { return m_worldTransform; }

	// �O�i�A�E�����x�N�g���̃Q�b�^�[
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, m_rotation); }
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, m_rotation); }

	// �A�N�^�[�̏�Ԃ̃Q�b�^�[���Z�b�^�[
	State GetState() const { return m_state; }
	void SetState(State _state) { m_state = _state; }

	// �X�s�[�h�̃Q�b�^�[
	float GetSpeed() const { return m_speed; }

	// �O�i�x�N�g���̃Z�b�^�[
	void RotateToNewForward(const Vector3& _forward);

	// �A�N�^�[ID�̃Q�b�^�[
	int GetID() { return m_id; };

	// �R���|�[�l���g�̒ǉ��E�폜
	void AddComponent(class Component* _component);
	void RemoveComponent(class Component* _component);

protected:
	State m_state;								// �A�N�^�[�̏��
	Matrix4 m_worldTransform;					// ���[���h�ϊ��s��
	Vector3 m_position;							// �ʒu
	Quaternion m_rotation;						// ��]
	float m_scale;								// �X�P�[�����O
	float m_speed;								// �X�s�[�h
	bool m_isRecomputeWorldTransform;			// ���[���h���W�̕ϊ��̍Čv�Z���K�v���H
	std::vector<class Component*> m_component;	// �R���|�[�l���g�̔z��
	class Game* m_game;							// �Q�[���V�X�e���N���X�ւ̃|�C���^
	int m_id;									// �Ǘ�ID
	static int m_globalActorNo;					// �Ǘ�ID�p�̐ÓI�J�E���^
};