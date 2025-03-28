#include <imgui.h>
#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

// �X�V����
void CameraController::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();
	// �J�����̉�]���x
	float speed = rollSpeed * elapsedTime;

	// �X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
	//angle.x += ay * speed;
	//angle.y += ax * speed;

	angle.x += ay * speed;
	angle.y = DirectX::XM_PI * 0.5f;

	// X���̃J������]�𐧌�
	if (angle.x < minAngleX)
	{
		angle.x = minAngleX;
	}
	if (angle.x > maxAngleX)
	{
		angle.x = maxAngleX;
	}
	// Y���̉�]�l��-3.14�`3.14�Ɏ��܂�悤�ɂ���
	if (angle.y < -DirectX::XM_PI)
	{
		angle.y += DirectX::XM_2PI;
	}
	if (angle.y > DirectX::XM_PI)
	{
		angle.y -= DirectX::XM_2PI;
	}

	// �J������]�l����]�s��ɕϊ�
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	// ��]�s�񂩂�O�����x�N�g�������o��
	DirectX::XMVECTOR Front = Transform.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	// �����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
	DirectX::XMFLOAT3 eye;
	eye.x = target.x - front.x * range;
	eye.y = target.y - front.y * range;
	eye.z = target.z - front.z * range;

	// �J�����Ɏ��_�𒍎��_��ݒ�
	Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

// �f�o�b�O�pGUI�`��
void CameraController::DrawDebugGUI()
{
	if (ImGui::CollapsingHeader("CameraController", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// �A���O��
		DirectX::XMFLOAT3 a;
		a.x = DirectX::XMConvertToDegrees(angle.x);
		a.y = DirectX::XMConvertToDegrees(angle.y);
		a.z = DirectX::XMConvertToDegrees(angle.z);
		ImGui::InputFloat3("Angle", &a.x);
		angle.x = DirectX::XMConvertToRadians(a.x);
		angle.y = DirectX::XMConvertToRadians(a.y);
		angle.z = DirectX::XMConvertToRadians(a.z);
		// �^�[�Q�b�g
		ImGui::InputFloat3("Target", &target.x);
		// ��]���x
		float rollSpeedDeg = DirectX::XMConvertToDegrees(rollSpeed);
		ImGui::InputFloat("RollSpeed", &rollSpeedDeg);
		rollSpeed = DirectX::XMConvertToRadians(rollSpeedDeg);
		// �����W
		ImGui::InputFloat("Range", &range);
		// �p�x����
		float minAngleDeg = DirectX::XMConvertToDegrees(minAngleX);
		float maxAngleDeg = DirectX::XMConvertToDegrees(maxAngleX);
		ImGui::InputFloat("MinAngleX", &minAngleDeg);
		ImGui::InputFloat("MaxAngleX", &maxAngleDeg);
		minAngleX = DirectX::XMConvertToRadians(minAngleDeg);
		maxAngleX = DirectX::XMConvertToRadians(maxAngleDeg);
	}
}