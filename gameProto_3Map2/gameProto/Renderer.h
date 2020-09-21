#pragma once
#include <string>
#include <unordered_map>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Math.h"

typedef struct _DirectionalLight
{
	Vector3 mDirection;     // ���C�g����
	Vector3 mDiffuseColor;	// ���C�g�J���[
	Vector3 mSpecColor;	    // �X�y�L�����[�J���[
}DirectionalLight;


class Renderer
{
public:
	Renderer();
	~Renderer();
	bool                   Initialize(int screenWidth, int screenHeight, bool fullScreen);     // SDL & GL������
	void                   Shutdown();                                                         // �I��
	void                   Draw();                                                             // �`��

	// �Z�b�^�[�n
	void                   SetViewMatrix(const Matrix4& view) { mView = view; }                // �r���[�s��̃Z�b�g
	void                   SetAmbientLight(const Vector3& ambientColor)                        // �A���r�G���g���C�g�̃Z�b�g
	                                       { mAmbientLight = ambientColor; }
	// �Q�b�^�[�n
	SDL_Renderer*          GetSDLRenderer() { return mSDLRenderer; }                           // SDL�n�̕`��ɕK�v��SDLrenderer�𓾂�
	class Texture*         GetTexture(const std::string& fileName);                            // �e�N�X�`�����t�@�C��������Ԃ�
	class Mesh*            GetMesh(const std::string& fileName);                               // ���b�V�����t�@�C��������Ԃ�
	const class Skeleton*  GetSkeleton(const char* fileName);                                  // �X�P���^�����f���̎擾
	const class Animation* GetAnimation(const char* fileName, bool loop);                      // �X�P���^���A�j���[�V�����̎擾

	float                  GetScreenWidth() { return static_cast<float>(mScreenWidth); }       // �X�N���[����
	float                  GetScreenHeight() { return static_cast<float>(mScreenHeight); }     // �X�N���[������
	DirectionalLight&      GetDirectionalLight() { return mDirectionalLight; }                 // �f�B���N�V���i�����C�g
	const Matrix4&         GetViewMatrix() { return mView; }
	const Matrix4&         GetProjectionMatrix() { return mProjection; }

	void                   AddMeshComponent(class MeshComponent* mesh);                        // ���b�V���R���|�[�l���g�̒ǉ�
	void                   RemoveMeshComponent(class MeshComponent* mesh);                     // ���b�V���R���|�[�l���g�̍폜
	void                   ShowResource();                                                     // �o�^����Ă��� �e�N�X�`���E���b�V�����\�[�X�̕\���i�f�o�b�O�p�j
	void                   WindowClear(){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);} // �E�B���h�E�`��N���A
	void                   WindowFlip() { SDL_GL_SwapWindow(mWindow); }                        // �E�B���h�E�t���b�v
	void                   SetWindowTitle(const std::string& title);                           // �E�B���h�E�^�C�g���̃Z�b�g

private:

	bool                                              LoadShaders();                          // �V�F�[�_�[�̏�����
	void                                              SetLightUniforms(class Shader* shader); // ���C�g�l���V�F�[�_�[�ɃZ�b�g

	int                                               mScreenWidth;      // �X�N���[����                                                           
	int                                               mScreenHeight;     // �X�N���[������
	std::unordered_map<std::string, class Texture*>   mTextures;         // �e�N�X�`���o�^�z��
	std::unordered_map<std::string, class Mesh*>      mMeshs;            // ���b�V���o�^�z��
	std::vector<class MeshComponent*>                 mMeshComponents;   // ���b�V���R���|�[�l���g�o�^�z��
	std::vector<class SkeletalMeshComponent*>         mSkeletalMeshes;   // �X�P���^�����b�V���̕`��Ɏg����
	std::unordered_map<std::string, class Skeleton*>  mSkeletons; // �X�P���^���f�[�^
	std::unordered_map<std::string, class Animation*> mAnims;    // �A�j���[�V�����f�[�^


	//�V�F�[�_�[�֘A
	class Shader*                                     mMeshShader;       // ���b�V���V�F�[�_�[
	class Shader*                                     mSkinnedShader;    // �X�L�����b�V���V�F�[�_�[

	// ��{�s��֘A
	Matrix4                                           mView;             // �r���[�s��
	Matrix4                                           mProjection;       // �v���W�F�N�V�����s��

	// ���C�e�B���O�֘A
	Vector3                                           mAmbientLight;     // �A���r�G���g���C�g
	DirectionalLight                                  mDirectionalLight; // �f�B���N�V���i�����C�g

	// �����_�����O�x�[�X���֘A
	SDL_Window*                                       mWindow;           // SDL�E�B���h�E�n���h�� 
	SDL_GLContext                                     mContext;          // OpenGL�R���e�L�X�g
	SDL_Renderer*                                     mSDLRenderer;      // SDL�����_�����O�n���h��
};

bool GLErrorHandle(const char* location);                              // OpenGL�̃G���[�n���h���擾