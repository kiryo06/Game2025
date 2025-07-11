#pragma once

namespace MyLib
{
	/// <summary>
	/// 当たり判定のデータ基底
	/// </summary>
	class ColliderData abstract
	{
	public:
		// 当たり判定の判定種別
		enum class Kind
		{
			
		};

		ColliderData(Kind kind) { this->kind = kind;}
		virtual ~ColliderData() {/*処理なし*/}
		// 当たり判定種別取得
		Kind GetKind() const { return kind; }
	private:
		Kind kind;
	};
}