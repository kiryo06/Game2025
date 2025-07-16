#include "SceneMain.h"
#include "DxLib.h"

void SceneMain::init()
{
	// �ȍ~�̃t�@�C���̓ǂݍ��݂��񓯊��������
	SetUseASyncLoadFlag(true);
	// �ǂݍ���
	for (auto& handle : m_handle)
	{
		handle = LoadGraph("dummy000.bmp");
	}
	// �f�t�H���g�̐ݒ�ɂ��ǂ��Ă���
	SetUseASyncLoadFlag(false);
	m_textPosX = 0;
	m_textVecX = 4;

	m_isEnd = false;
}

void SceneMain::update()
{
	// �񓯊��ǂݍ��݂�1�ȏ�s���Ă���ꍇ��update�������s��Ȃ�
	if (GetASyncLoadNum() > 0)
	{
		// �O���t�B�b�N���g�����������s���Ă���\��������̂�
		// �ŏ��Ƀ`�F�b�N���ă��[�h���I����Ă��Ȃ���΂�����update�I��
		return;
	}


	// �����̈ړ�
	m_textPosX += m_textVecX;
	if (m_textPosX < 0)
	{
		m_textPosX = 0;
		m_textVecX = 4;
	}
	if (m_textPosX > 300)
	{
		m_textPosX = 300;
		m_textVecX = -4;
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_2)
	{
		m_isEnd = true;
	}
}

void SceneMain::draw()
{
	// �񓯊��ǂݍ��݂��I���܂ł�draw�̏������s��Ȃ�
	if (GetASyncLoadNum() > 0)
	{
		// ���݉��p�[�Z���g���[�h���������Ă��邩��\������
		// �t�@�C���̐��������Ă��Ȃ��̂�(�T�C�Y�����Ă��Ȃ�)���Ԃ������镔���Ƃ�����Ȃ�����������
		// �̂Ŏ��ۂ̎��ԂƂ͂����ꍇ������
		int total = _countof(m_handle);	// �ǂݍ��ރt�@�C���̑���
		int now = total - GetASyncLoadNum();
		float rate = static_cast<float>(now) / total;
		DrawFormatString(0, 0, 0xffffff, "���[�h��...�@%.1f%%", rate * 100);
		return;
	}
	DrawGraph(0, 0, m_handle[2047], true);
	DrawString(m_textPosX, 0,"���C�����",GetColor(255,255,255));
}