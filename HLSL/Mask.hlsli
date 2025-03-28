struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
};

//	�X�v���C�g�`��P�ʂŎw�肷��p�����[�^�[
cbuffer CbScene : register(b0)
{
    float2 uvScrollValue; // UV�X�N���[���l
    float2 dummy1; // �_�~�[
};

////	�X�v���C�g�`��P�ʂŎw�肷��p�����[�^�[
//cbuffer CbMask : register(b1) // 1�Ԃɂ���萔�o�b�t�@������ŗ��p����
//{
//    float dissolveThreshold; // �f�B�]���u��
//    float3 dummy2;
//};

//	�X�v���C�g�`��P�ʂŎw�肷��p�����[�^�[
cbuffer CbMask : register(b1) // 0�Ԃɂ���萔�o�b�t�@������ŗ��p����
{
    float dissolveThreshold; // �f�B�]���u��
    float edgeThreshold; // ����臒l
    float2 dummy2;
    float4 edgeColor; // ���̐F
};
