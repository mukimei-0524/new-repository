#include "Graphics/Graphics.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneLoading.h"
#include "SceneManager.h"
#include "Input/Input.h"

// ������
void SceneTitle::Initialize()
{
	// �e�N�X�`���[������
	//texture = new Texture("Data/Sprite/Title.png");
	texture = std::make_unique<Texture>("Data/Sprite/Title.png");
	// �}�X�N�e�N�X�`���̓ǂݍ���
	maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");

	// �X�v���C�g������
	//sprite = new Sprite();
	sprite = std::make_unique<Sprite>();
	// �e�N�X�`���[�̐ݒ�
	sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());
	// 臒l�̏�����
	dissolveThreshold = 1.0f;
	edgeThreshold = 0.2f; 	// ����臒l
	edgeColor = { 1, 0, 0, 1 };		// ���̐F

}

// �I����
void SceneTitle::Finalize()
{
	//// �X�v���C�g�I����
	//if (sprite != nullptr)
	//{
	//	delete sprite;
	//	sprite = nullptr;
	//}
	//// �e�N�X�`���[�I����
	//if (texture != nullptr)
	//{
	//	delete texture;
	//	texture = nullptr;
	//}



}

// �X�V����
void SceneTitle::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	// �Ȃɂ��{�^�����������烍�[�f�B���O�V�[���֐؂�ւ�
	const GamePadButton anyButton =
		  GamePad::BTN_A
		| GamePad::BTN_B
		| GamePad::BTN_X
		| GamePad::BTN_Y
		;
	if (gamePad.GetButtonDown() & anyButton)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	}

	sprite->Update(0.0f, 0.0f,
		Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
		0.0f, 0.0f,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);



}

// �`�揈��
void SceneTitle::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.5f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 2D�X�v���C�g�`��
	{
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		float textureWidth = static_cast<float>(sprite->GetTextureWidth());
		float textureHeight = static_cast<float>(sprite->GetTextureHeight());
		// �^�C�g���X�v���C�g�`��
		//sprite->Render(dc,
		//	0, 0, screenWidth, screenHeight,
		//	0, 0, textureWidth, textureHeight,
		//	0,
		//	1, 1, 1, 1);
		//sprite->Update(
		//	0, 0, screenWidth, screenHeight,
		//	0, 0, textureWidth, textureHeight,
		//	0,
		//	1, 1, 1, 1);

	}

	// 2D�X�v���C�g�`��
	{
		RenderContext rc{};
		rc.deviceContext = dc;

		SpriteShader* shader = graphics.GetShader(SpriteShaderId::Mask);
		shader->Begin(rc);
		rc.uvScrollData.uvScrollValue = uvScrollData.uvScrollValue;
		rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
		rc.maskData.dissolveThreshold = dissolveThreshold;
		rc.maskData.edgeThreshold = edgeThreshold;
		rc.maskData.edgeColor = edgeColor;

		
		sprite->Render(rc, shader);

		shader->End(rc);
	}

	// 2D�f�o�b�OGUI�`��
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Debug Menu", nullptr, ImGuiWindowFlags_None))
		{

			if (ImGui::CollapsingHeader("UVScroll", ImGuiTreeNodeFlags_DefaultOpen))
			{

				float min_value = -1.0f;  // �X���C�_�[�̍ŏ��l
				float max_value = 1.0f;  // �X���C�_�[�̍ő�l

				// ImGui�̒��ŃX���C�_�[��`�悷��
				ImGui::SliderFloat("UVScroll_X", &uvScrollData.uvScrollValue.x, min_value, max_value);
				ImGui::SliderFloat("UVScroll_Y", &uvScrollData.uvScrollValue.y, min_value, max_value);
			}

			if (ImGui::CollapsingHeader("Mask", ImGuiTreeNodeFlags_DefaultOpen))
			{
			
				ImGui::SliderFloat("Dissolve Threshold", &dissolveThreshold, 0.0f, 1.0f);
				ImGui::SliderFloat("Edge Threshold", &edgeThreshold, 0.0f, 1.0f);
				ImGui::ColorEdit4("Edge Color", &edgeColor.x);

			}

		}
		ImGui::End();
	}




}
