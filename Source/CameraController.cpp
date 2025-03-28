#include <imgui.h>
#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

// 更新処理
void CameraController::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();
	// カメラの回転速度
	float speed = rollSpeed * elapsedTime;

	// スティックの入力値に合わせてX軸とY軸を回転
	//angle.x += ay * speed;
	//angle.y += ax * speed;

	angle.x += ay * speed;
	angle.y = DirectX::XM_PI * 0.5f;

	// X軸のカメラ回転を制限
	if (angle.x < minAngleX)
	{
		angle.x = minAngleX;
	}
	if (angle.x > maxAngleX)
	{
		angle.x = maxAngleX;
	}
	// Y軸の回転値を-3.14〜3.14に収まるようにする
	if (angle.y < -DirectX::XM_PI)
	{
		angle.y += DirectX::XM_2PI;
	}
	if (angle.y > DirectX::XM_PI)
	{
		angle.y -= DirectX::XM_2PI;
	}

	// カメラ回転値を回転行列に変換
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	// 回転行列から前方向ベクトルを取り出す
	DirectX::XMVECTOR Front = Transform.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	// 注視点から後ろベクトル方向に一定距離離れたカメラ視点を求める
	DirectX::XMFLOAT3 eye;
	eye.x = target.x - front.x * range;
	eye.y = target.y - front.y * range;
	eye.z = target.z - front.z * range;

	// カメラに視点を注視点を設定
	Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

// デバッグ用GUI描画
void CameraController::DrawDebugGUI()
{
	if (ImGui::CollapsingHeader("CameraController", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// アングル
		DirectX::XMFLOAT3 a;
		a.x = DirectX::XMConvertToDegrees(angle.x);
		a.y = DirectX::XMConvertToDegrees(angle.y);
		a.z = DirectX::XMConvertToDegrees(angle.z);
		ImGui::InputFloat3("Angle", &a.x);
		angle.x = DirectX::XMConvertToRadians(a.x);
		angle.y = DirectX::XMConvertToRadians(a.y);
		angle.z = DirectX::XMConvertToRadians(a.z);
		// ターゲット
		ImGui::InputFloat3("Target", &target.x);
		// 回転速度
		float rollSpeedDeg = DirectX::XMConvertToDegrees(rollSpeed);
		ImGui::InputFloat("RollSpeed", &rollSpeedDeg);
		rollSpeed = DirectX::XMConvertToRadians(rollSpeedDeg);
		// レンジ
		ImGui::InputFloat("Range", &range);
		// 角度制限
		float minAngleDeg = DirectX::XMConvertToDegrees(minAngleX);
		float maxAngleDeg = DirectX::XMConvertToDegrees(maxAngleX);
		ImGui::InputFloat("MinAngleX", &minAngleDeg);
		ImGui::InputFloat("MaxAngleX", &maxAngleDeg);
		minAngleX = DirectX::XMConvertToRadians(minAngleDeg);
		maxAngleX = DirectX::XMConvertToRadians(maxAngleDeg);
	}
}