#pragma once

namespace MyLib
{
	/// <summary>
	/// �����蔻��̃f�[�^���
	/// </summary>
	class ColliderData abstract
	{
	public:
		// �����蔻��̔�����
		enum class Kind
		{
			
		};

		ColliderData(Kind kind) { this->kind = kind;}
		virtual ~ColliderData() {/*�����Ȃ�*/}
		// �����蔻���ʎ擾
		Kind GetKind() const { return kind; }
	private:
		Kind kind;
	};
}