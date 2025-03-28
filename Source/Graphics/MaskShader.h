#pragma once

#include <memory>
#include <wrl.h>
#include "Graphics/Shader.h"

class MaskShader : public SpriteShader
{
public:
	MaskShader(ID3D11Device* device);
	~MaskShader() override {}

	//void Begin(ID3D11DeviceContext* dc, const RenderContext& rc) override;
	//void Draw(ID3D11DeviceContext* dc, const Sprite* sprite) override;
	//void End(ID3D11DeviceContext* dc) override;
	void Begin(const RenderContext& rc) override;
	void Draw(const RenderContext& rc, const Sprite* sprite) override;
	void End(const RenderContext& rc) override;




private:

	struct CbScroll
	{
		DirectX::XMFLOAT2	uvScrollValue;	//	UV�X�N���[���l
		DirectX::XMFLOAT2	dummy;			//	�_�~�[
	};

	// 臒l�𑗂邽�߂̒萔�o�b�t�@�p�\����
	struct CbMask
	{
		float				dissolveThreshold;	// �f�B�]���u��
		float edgeThreshold; // ����臒l
		DirectX::XMFLOAT2	dummy;
		DirectX::XMFLOAT4 edgeColor; // ���̐F

	};

	Microsoft::WRL::ComPtr<ID3D11Buffer>				maskConstantBuffer; 	// �萔�o�b�t�@


	Microsoft::WRL::ComPtr<ID3D11Buffer>				scrollConstantBuffer;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			inputLayout;

	Microsoft::WRL::ComPtr<ID3D11BlendState>			blendState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>			samplerState;
};
