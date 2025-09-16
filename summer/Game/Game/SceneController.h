#pragma once
// スマートポーンターを使う
#include <memory>
#include <list>

class Input;
class BaseScene;

/// <summary>
/// 各シーンを管理するためのクラス
/// 管理はするがシーン遷移は管理しない
/// インターフェースを提供するためのクラス
/// </summary>
class SceneController
{
private:
	std::list<std::shared_ptr<BaseScene>> _scenes; ///< シーンのリスト
public:
	SceneController();

	/// <summary>
	///  Applicationから呼ばれる関数。現在のシーンのInitをそのまま実行。
	/// </summary>
	void Init();
	/// <summary>
	/// Applicationから呼ばれる関数。現在のシーンのUpdateをそのまま実行。
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input, float deltaTime);
	/// <summary>
	/// Applicationから呼ばれる関数。現在のシーンのDrawをそのまま実行。
	/// </summary>
	void Draw();
	/// <summary>
	/// 次の状態をセットする(セットするのは各状態の役割)
	/// 各シーンがコントローラーを見て切り替えさせる？
	/// </summary>
	/// <param name="">次の状態のポインタ（スマポ）</param>
	void ChangeScene(std::shared_ptr<BaseScene>);

	/// <summary>
	/// 現在実行中のシーンの上に別のシーンを乗っける
	/// </summary>
	/// <param mane="scene">乗っけたいシーン</param>
	void PushScene(std::shared_ptr<BaseScene> scene);

	/// <summary>
	/// 現在、一番上にある実行中のシーンを取り除く
	/// </summary>
	void PopScene();
};

