#pragma once

#include <vector>
#include <set>
#include "Enemy.h"

// �G�l�~�[�}�l�[�W���[
class EnemyManager
{
private:
	EnemyManager() {}
	~EnemyManager() {}

public:
	// �B��̃C���X�^���X�擾
	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}

	// �X�V����
	void Update(float elapsedTime);

	// �`�揈��
	void Render(const RenderContext& rc, ModelShader* shader);

	// �f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	// �G�l�~�[�o�^
	void Register(Enemy* enemy);

	// �G�l�~�[�S�폜
	void Clear();

	// �G�l�~�[�폜
	void Remove(Enemy* enemy);

	// �G�l�~�[���擾
	int GetEnemyCount() const { return static_cast<int>(enemies.size()); }

	// �G�l�~�[�擾
	Enemy* GetEnemy(int index) { return enemies.at(index); }

	// �f�o�b�O�pGUI�`��
	void DrawDebugGUI();

private:
	// �G�l�~�[���m�̏Փˏ���
	void CollisionEnemyVsEnemies();

private:
	std::vector<Enemy*>		enemies;
	std::set<Enemy*>		removes;
	bool					visibleDebugPrimitive = true;
};
