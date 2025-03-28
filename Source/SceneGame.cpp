#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "EffectManager.h"
#include "LightManager.h"
#include "StageManager.h"


//	�V���h�E�}�b�v�̃T�C�Y
static	const	UINT	SHADOWMAP_SIZE = 2048;

// ������
void SceneGame::Initialize()
{
	// �X�e�[�W������
	//stageManager = std::make_unique<StageManager>();

	stage = new Stage();

	earth = std::make_unique<Earth>();

	StageManager::Instance().Register(stage);
	StageManager::Instance().Register(earth.get());


	// �v���C���[
	player = new Player();
	//player->SetPosition({10,10,0});

	// �J���������ݒ�
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(-10, 2, 0),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	// �J�����R���g���[���[������
	cameraController = new CameraController();
	// ���s������ǉ�
	//LightManager::Instance().Register(new Light(LightType::Directional));

	{
		mainDirectionalLight = new Light(LightType::Directional);
		mainDirectionalLight->SetDirection({ 1, -1, -1 });
		LightManager::Instance().Register(mainDirectionalLight);
	}


	// �_������ǉ�
	{
		Light* light = new Light(LightType::Point);
		light->SetPosition(DirectX::XMFLOAT3(0, 4, 0));
		light->SetColor(DirectX::XMFLOAT4(1, 1, 1, 1));
		light->SetRange(5.0f);
		LightManager::Instance().Register(light);
	}
	// �_������ǉ�
	{
		Light* light = new Light(LightType::Point);
		light->SetPosition(DirectX::XMFLOAT3(5, 4, 0));
		light->SetColor(DirectX::XMFLOAT4(1, 1, 0, 1));
		light->SetRange(5.0f);
		LightManager::Instance().Register(light);
	}
	// �X�|�b�g���C�g��ǉ�
	{
		Light* light = new Light(LightType::Spot);
		light->SetPosition(DirectX::XMFLOAT3(-10, 10, 10));
		light->SetColor(DirectX::XMFLOAT4(1, 1, 1, 1));
		light->SetDirection(DirectX::XMFLOAT3(+1, -1, 0));

		light->SetRange(40.0f);
		LightManager::Instance().Register(light);
	}

	// �V���h�E�}�b�v�p�ɐ[�x�X�e���V���̐���
	{
		Graphics& graphics = Graphics::Instance();
		shadowmapDepthStencil = std::make_unique<DepthStencil>(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	}



	// �G�l�~�[������
	EnemyManager& enemyManager = EnemyManager::Instance();
	for (int i = 0; i < 2; ++i)
	{
		EnemySlime* slime = new EnemySlime();
		slime->SetPosition(DirectX::XMFLOAT3(i * 2.0f, 0, 5));
		enemyManager.Register(slime);
	}

	//�X�J�C�{�b�N�X
	skybox = new SkyBox("Data/SkyBox/town20220706.jpg");
}

// �I����
void SceneGame::Finalize()
{
	// �G�l�~�[�I����
	EnemyManager::Instance().Clear();

	// �J�����R���g���[���[�I����
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	// �v���C���[�I����
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	// �X�e�[�W�I����
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}

	delete skybox;
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	// �J�����R���g���[���[�X�V����
	
	//////////////////////////////////
	//���X�N���[���̏ꍇ�������O��
	//////////////////////////////////

	/*DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);*/

	// �X�e�[�W�X�V����

	StageManager::Instance().Update(elapsedTime);
	//stage->Update(elapsedTime);
	earth->Update(elapsedTime);

	// �v���C���[�X�V����
	player->Update(elapsedTime);

	// �G�l�~�[�X�V����
	EnemyManager::Instance().Update(elapsedTime);

	// �G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);
	
	// ���C�g�X�V����(��)
	Light*light = LightManager::Instance().GetLight(3);
	DirectX::XMFLOAT3 p = player->GetPosition();
	p.y += 1.5f;
	light->SetPosition(p);
	DirectX::XMFLOAT3 d = player->GetDirection();
	d.y -= 0.2f;
	light->SetDirection(d);

}

//-----------------------------------------------------
//              �`�揈��
//-----------------------------------------------------

//	�V���h�E�}�b�v�̕`��
void SceneGame::RenderShadowmap()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11DepthStencilView* dsv = shadowmapDepthStencil->GetDepthStencilView().Get();

	// ��ʃN���A
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	if (!mainDirectionalLight)
		return;

	// �����_�[�^�[�Q�b�g�ݒ�
	dc->OMSetRenderTargets(0, &rtv, dsv);

	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT	vp = {};
	vp.Width = static_cast<float>(shadowmapDepthStencil->GetWidth());
	vp.Height = static_cast<float>(shadowmapDepthStencil->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	dc->RSSetViewports(1, &vp);

	// �`�揈��
	RenderContext rc;
	rc.deviceContext = dc;

	// �J�����p�����[�^�ݒ�
	{
		// ���s��������J�����ʒu���쐬���A�������猴�_�̈ʒu������悤�Ɏ����s��𐶐�
		DirectX::XMVECTOR LightPosition = DirectX::XMLoadFloat3(&mainDirectionalLight->GetDirection());
		LightPosition = DirectX::XMVectorScale(LightPosition, -250.0f);//�J����250���
		DirectX::XMMATRIX V = DirectX::XMMatrixLookAtLH(LightPosition,
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

		// �V���h�E�}�b�v�ɕ`�悵�����͈͂̎ˉe�s��𐶐�
		DirectX::XMMATRIX P = DirectX::XMMatrixOrthographicLH(shadowDrawRect, shadowDrawRect, 0.1f, 1000.0f);//��������\��1000
		DirectX::XMStoreFloat4x4(&rc.view, V);
		DirectX::XMStoreFloat4x4(&rc.projection, P);
		DirectX::XMStoreFloat4x4(&lightViewProjection, V * P);
	}

	// 3D���f���`��
	{
		ModelShader* shader = graphics.GetShader(ModelShaderId::ShadowmapCaster);
		shader->Begin(rc);

		// �X�e�[�W�`��
		StageManager::Instance().Render(rc, shader);
		//stage->Render(rc, shader);
		earth->Render(rc, shader);

		// �v���C���[�`��
		player->Render(rc, shader);

		// �G�l�~�[�`��
		EnemyManager::Instance().Render(rc, shader);

		shader->End(rc);
	}
}

void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// �V���h�E�}�b�v�̕`��
	RenderShadowmap();

	// 3D��Ԃ̕`���ʂ̃o�b�t�@�ɑ΂��čs��
	//Render3DScene();


	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j
		// ���C�g�̏����l�ߍ���
	LightManager::Instance().PushRenderContext(rc);

	// �V���h�E�}�b�v�̐ݒ�
	rc.shadowMapData.shadowMap = shadowmapDepthStencil->GetShaderResourceView().Get();
	rc.shadowMapData.lightViewProjection = lightViewProjection;
	rc.shadowMapData.shadowColor = shadowColor;
	rc.shadowMapData.shadowBias = shadowBias;
	rc.shadowMapData.PCFKernelSize = PCFKernelSize;


	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT	vp = {};
	vp.Width = graphics.GetScreenWidth();
	vp.Height = graphics.GetScreenHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	dc->RSSetViewports(1, &vp);


	// �J�����p�����[�^�ݒ�
	Camera& camera = Camera::Instance();
	rc.viewPosition.x = camera.GetEye().x;
	rc.viewPosition.y = camera.GetEye().y;
	rc.viewPosition.z = camera.GetEye().z;
	rc.viewPosition.w = 1;
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();
	rc.outlinedata.outlineColor = outlineColor;
	rc.outlinedata.outlineSize = outlinewidth;
	rc.deviceContext = dc;

	// 3D���f���`��
	{
		//Shader* shader = graphics.GetShader();
		//ModelShader* shader = graphics.GetShader(ModelShaderId::Default);
		ModelShader* shader = graphics.GetShader(ModelShaderId::Phong);

		shader->Begin(rc);
		
		// �X�e�[�W�`��
		//stage->Render(rc, shader);
		StageManager::Instance().Render(rc, shader);

		earth->Render(rc, shader);

		// �v���C���[�`��
		player->Render(rc, shader);

		// �G�l�~�[�`��
		EnemyManager::Instance().Render(rc, shader);

		shader->End(rc);
	}
	//{
	//	Shader* shader = graphics.GetShader();
	//	ModelShader* shader = graphics.GetShader(ModelShaderId::Toon);

	//	shader->Begin(rc);
	//	
	//	 �v���C���[�`��
	//	player->Render(rc, shader);
	//	 �G�l�~�[�`��
	//	EnemyManager::Instance().Render(rc, shader);


	//	shader->End(rc);
	//}

	// 3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	//// 3D�f�o�b�O�`��
	//{

	//	// ���C�g�̃f�o�b�O�v���~�e�B�u�̕`��
	//	LightManager::Instance().DrawDebugPrimitive();

	//	// �v���C���[�f�o�b�O�`��
	//	player->DrawDebugPrimitive();

	//	// �G�l�~�[�f�o�b�O�`��
	//	EnemyManager::Instance().DrawDebugPrimitive();

	//	// ���C�������_���`����s
	//	graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

	//	// �f�o�b�O�����_���`����s
	//	graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	//}

	// 2D�X�v���C�g�`��
	{
		skybox->Render(dc, rc);
	}

	// 2D�f�o�b�OGUI�`��
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Debug Menu", nullptr, ImGuiWindowFlags_None))
		{
			int id = 0;
			// �f�o�b�O���̕\��
			ImGui::PushID(id++);
			{
				LightManager::Instance().DrawDebugGUI();

			}
			ImGui::PopID();

			// 
			ImGui::PushID(id++);
			{
				if (ImGui::CollapsingHeader("Toon", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::SliderFloat("OutLine", &outlinewidth, 0, 1.0f);
					ImGui::ColorEdit3("OutLineColor", &outlineColor.x);
				}

			}
			ImGui::PopID();

			// �v���C���[�f�o�b�O�`��
			ImGui::PushID(id++);
			{
				player->DrawDebugGUI();
			}
			ImGui::PopID();
			// �J�����f�o�b�O�`��
			ImGui::PushID(id++);
			{
				camera.DrawDebugGUI();
			}
			ImGui::PopID();

			// �J�����R���g���[���[�f�o�b�O�`��
			ImGui::PushID(id++);
			{
				cameraController->DrawDebugGUI();
			}
			ImGui::PopID();

			// �G�l�~�[�}�l�[�W���[�f�o�b�O�`��
			ImGui::PushID(id++);
			{
				EnemyManager::Instance().DrawDebugGUI();
			}
			ImGui::PopID();

			//�V���h�[�}�b�v
			ImGui::PushID(id++);
			{
				//ImGui::Separator();//��
				if (ImGui::CollapsingHeader("ShadowMap", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::SliderFloat("DrawRect", &shadowDrawRect, 1.0f,512.0f);//�r���Ȃ�
					ImGui::ColorEdit3("Color", &shadowColor.x);
					ImGui::SliderFloat("Bias", &shadowBias, 0.0f, 0.01f,"% 0.5f");
					ImGui::SliderInt("PCFKernelSize", &PCFKernelSize, 1, 15);
					ImGui::Text("texture");
					ImGui::Image(shadowmapDepthStencil->GetShaderResourceView().Get(), { 256, 256 }, { 0, 0 }, { 1, 1 }, { 1, 1, 1, 1 });//texture�̃T�C�Y256,256

					//ImGui::TreePop();
				}
				//ImGui::Separator();
			}
			ImGui::PopID();
		}
		ImGui::End();
	}
}

//// 3D��Ԃ̕`��
//void SceneGame::Render3DScene()
//{
//    // ���C�g�̏����l�ߍ���
//	LightManager::Instance().PushRenderContext(rc);
//
//	// �V���h�E�}�b�v�̐ݒ�
//	rc.shadowMapData.shadowMap = shadowmapDepthStencil->GetShaderResourceView().Get();
//	rc.shadowMapData.lightViewProjection = lightViewProjection;
//	rc.shadowMapData.shadowColor = shadowColor;
//	rc.shadowMapData.shadowBias = shadowBias;
//}




