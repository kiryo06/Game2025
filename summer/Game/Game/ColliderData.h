#pragma once

namespace MyLib
{
	/// <summary>
	/// “–‚½‚è”»’è‚Ìƒf[ƒ^Šî’ê
	/// </summary>
	class ColliderData abstract
	{
	public:
		// “–‚½‚è”»’è‚Ì”»’èí•Ê
		enum class Kind
		{
			
		};

		ColliderData(Kind kind) { this->kind = kind;}
		virtual ~ColliderData() {/*ˆ—‚È‚µ*/}
		// “–‚½‚è”»’èí•Êæ“¾
		Kind GetKind() const { return kind; }
	private:
		Kind kind;
	};
}