// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <typeinfo>

// ���b�V���R���|�[�l���g�@owner�ƃX�L�����b�V�����̏������
MeshComponent::MeshComponent(Actor* owner, bool isSkeletal)
	:Component(owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mVisible(true)
	, mIsSkeletal(isSkeletal)
{
	GAMEINSTANCE.GetRenderer()->AddMeshComponent(this);
	printf("new MeshComponent : [%5d] owner->( 0x%p )\n", GetID(), owner);
}

MeshComponent::~MeshComponent()
{
	printf("remove MeshComponent : [%5d] owner->( 0x%p )\n", GetID(), mOwner);
	GAMEINSTANCE.GetRenderer()->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		// Set the world transform�@���[���h�ϊ����Z�b�g
		shader->SetMatrixUniform("uWorldTransform",
			 mOwner->GetWorldTransform());
		// Set specular power�@�X�y�L�������x�Z�b�g
		shader->SetFloatUniform("uSpecPower", 100);
		// Set the active texture�@�A�N�e�B�u�e�N�X�`���Z�b�g
		Texture* t = mMesh->GetTexture(mTextureIndex);
		if (t)
		{
			t->SetActive();
		}
		// Set the mesh's vertex array as active�@���_�z����A�N�e�B�u��
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();
		// Draw�@�`�悷��[
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
