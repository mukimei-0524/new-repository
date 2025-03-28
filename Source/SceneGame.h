#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
//#include "Graphics/RenderTarget.h"
#include "Graphics/DepthStencil.h"
#include "Light.h"
#include "Graphics/SkyBox.h"
//#include "PostprocessingRenderer.h"

// ゲームシーン
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

private:

	// 3D空間の描画
	//void Render3DScene();

	// シャドウマップの描画
	void RenderShadowmap();


private:
	Stage*				stage = nullptr;

	//std::unique_ptr<StageManager> stageManager;
	std::unique_ptr<Stage> earth;
	std::unique_ptr<Earth> earth2;

	Player*				player = nullptr;
	CameraController*	cameraController = nullptr;
	//// 平行光源データ
	//std::unique_ptr<Light>	directional_light;
	//DirectX::XMFLOAT4		ambientLightColor;

	float   outlinewidth = 0.0f;
	DirectX::XMFLOAT4  outlineColor{ 0,0,0,1 };
	SkyBox* skybox = nullptr;//初期値null

	//	シャドウマップ用情報
	Light* mainDirectionalLight = nullptr;					//	シャドウマップを生成する平行光源
	std::unique_ptr<DepthStencil> shadowmapDepthStencil;	//	シャドウマップ用深度ステンシルバッファ
	float	shadowDrawRect = 500.0f;	//	シャドウマップに描画する範囲
	DirectX::XMFLOAT4X4	lightViewProjection;				//	ライトビュープロジェクション行列
	DirectX::XMFLOAT3	shadowColor = { 0.2f, 0.2f, 0.2f };	//	影の色
	float				shadowBias = 0.001f;				//	深度比較用のオフセット値
	int                 PCFKernelSize = 1;                  // ソフトシャドーの行列サイズ


	//	ポストプロセス
	//std::unique_ptr<PostprocessingRenderer>	postprocessingRenderer;


};
