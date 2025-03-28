#pragma once

#include <DirectXMath.h>
#include <D3D11.h>

struct DirectionalLightData
{
	DirectX::XMFLOAT4	direction;	// ����
	DirectX::XMFLOAT4	color;		// �F
};
// �_�������
struct PointLightData
{
	DirectX::XMFLOAT4	position;	// ���W
	DirectX::XMFLOAT4	color;		// �F
	float				range;		// �͈�
	float				influence;	// ���̉e����
	DirectX::XMFLOAT2	dummy;
};

// �_�����̍ő吔
static	constexpr	int	PointLightMax = 8;

// �X�|�b�g���C�g���
struct SpotLightData
{
	DirectX::XMFLOAT4	position;	// ���W
	DirectX::XMFLOAT4	direction;	// ����
	DirectX::XMFLOAT4	color;		// �F
	float			range;		// �͈�
	float			innerCorn; 	// �C���i�[�p�x�͈�
	float			outerCorn; 	// �A�E�^�[�p�x�͈�
	float			influence; // ���̉e����;
};

// �X�|�b�g���C�g�̍ő吔
static	constexpr	int	SpotLightMax = 8;


// �}�X�N�f�[�^
struct MaskData
{
	ID3D11ShaderResourceView* maskTexture;
	float					dissolveThreshold;
	float					edgeThreshold; 	// ����臒l
	DirectX::XMFLOAT4		edgeColor;		// ���̐F

};


//	UV�X�N���[�����
struct UVScrollData
{
	DirectX::XMFLOAT2	uvScrollValue;	// UV�X�N���[���l
};

// �g�D�[���V�F�[�f�B���O�p�A�E�g���C��
struct OutlineData
{
	DirectX::XMFLOAT4X4		viewProjection;
	DirectX::XMFLOAT4		outlineColor;
	float					outlineSize;
	DirectX::XMFLOAT3		dummy;
};

//	�V���h�E�}�b�v�p���
struct ShadowMapData
{
	ID3D11ShaderResourceView* shadowMap;				//	�V���h�E�}�b�v�e�N�X�`��
	DirectX::XMFLOAT4X4			lightViewProjection;	//	���C�g�r���[�v���W�F�N�V�����s��
	DirectX::XMFLOAT3			shadowColor;			//	�e�̐F
	float						shadowBias;				//	�[�x��r�p�̃I�t�Z�b�g�l
	int                         PCFKernelSize;          // �\�t�g�V���h�[�̍s��T�C�Y
	//DirectX::XMFLOAT3           dummy;
};



// �����_�[�R���e�L�X�g
struct RenderContext
{
	ID3D11DeviceContext*	deviceContext;		// ���ύX
	DirectX::XMFLOAT4		viewPosition;
	DirectX::XMFLOAT4X4		view;
	DirectX::XMFLOAT4X4		projection;
	DirectX::XMFLOAT4		lightDirection;

	UVScrollData			uvScrollData;
	MaskData				maskData;

	//	���C�g���
	DirectX::XMFLOAT4		ambientLightColor;
	DirectionalLightData	directionalLightData;
	PointLightData		pointLightData[PointLightMax];	// �_�������
	int					pointLightCount = 0;			// �_������
	SpotLightData		spotLightData[SpotLightMax];	// �X�|�b�g���C�g���
	int					spotLightCount = 0;			// �X�|�b�g���C�g��
	OutlineData				outlinedata;

	//	�V���h�E�}�b�v���
	ShadowMapData			shadowMapData;

};


