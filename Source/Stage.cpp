#include "Stage.h"

static Stage* instance = nullptr;

// �C���X�^���X�擾 
Stage& Stage::Instance()
{
	
	return *instance;
}

// �R���X�g���N�^
Stage::Stage()
{
	instance = this;
	// �X�e�[�W���f����ǂݍ���
	model = new Model("Data/Model/ExampleStage/test_stage.mdl");
}
Stage::Stage(const char* filename)
{
	instance = this;
	// �X�e�[�W���f����ǂݍ���
	model = new Model(filename);
}

Stage::~Stage()
{
	// �X�e�[�W���f����j��
	delete model;
}

// �X�V����
void Stage::Update(float elapsedTime)
{
	// ���͓��ɂ�邱�Ƃ͂Ȃ�
}

// ���C�L���X�g 
bool Stage::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	return Collision::IntersectRayVsModel(start, end, model, hit);
}



// �`�揈��
void Stage::Render(const RenderContext& rc, ModelShader* shader)
{
	// �V�F�[�_�[�Ƀ��f����`�悵�Ă��炤
	shader->Draw(rc, model);
}

///////////////////////////////////////////////////////////////////

// �R���X�g���N�^
Earth::Earth()
{
	// �X�e�[�W���f����ǂݍ���
	model = new Model("Data/Model/earth/earth.mdl");
}

Earth::~Earth()
{
	// �X�e�[�W���f����j��
	//delete model;
}

// �X�V����
void Earth::Update(float elapsedTime)
{
	// ���͓��ɂ�邱�Ƃ͂Ȃ�
	DirectX::XMFLOAT4X4 mat(
		 0.05f,	0,		0,		0 ,
		 0,		0.05f,	0,		0 ,
		 0,		0,		0.05f,	0 ,
		 0,		3.0f,	0,		1 
	);
	
	model->UpdateTransform(mat);
}

