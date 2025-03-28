#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"

// �v���C���[
class Player : public Character
{
public:
	Player();
	~Player() override;

	// �C���X�^���X�擾
	static Player& Instance();


	// �X�V����
	void Update(float elapsedTime);

	// �`�揈��
	void Render(const RenderContext& rc, ModelShader* shader);

	// �f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	// �f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	// �O���擾�֐�
	DirectX::XMFLOAT3 GetDirection() { return direction; }


protected:
	// ���n�������ɌĂ΂��
	void OnLanding() override;

private:
	// �X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec() const;

	// �ړ����͏���
	void InputMove(float elapsedTime);

	// �W�����v���͏���
	void InputJump();

	// �e�ۓ��͏���
	void InputProjectile();

	// �v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
	void CollisionPlayerVsEnemies();

	// �e�ۂƓG�̏Փˏ���
	void CollisionProjectilesVsEnemies();
private:
	// �A�j���[�V����
	enum Animation
	{
		Anim_Attack,
		Anim_Death,
		Anim_Falling,
		Anim_GetHit1,
		Anim_GetHit2,
		Anim_Idle,
		Anim_Jump,
		Anim_Jump_Flip,
		Anim_Landing,
		Anim_Revive,
		Anim_Running,
		Anim_Walking
	};


private:
	Model*				model = nullptr;
	float				moveSpeed = 5.0f;
	float				turnSpeed = DirectX::XMConvertToRadians(720);
	float				jumpSpeed = 20.0f;
	int					jumpCount = 0;
	int					jumpLimit = 2;
	ProjectileManager	projectileManager;
	Effect*				hitEffect = nullptr;
	bool				visibleDebugPrimitive = true;
	DirectX::XMFLOAT3	direction = {0,0,1}; // �O��
};
