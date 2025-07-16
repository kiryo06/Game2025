#pragma once
#include "SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_textPosX = 0;
		m_textVecX = 0;
		m_isEnd = false;
	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end() {}

	virtual void update();
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:
	// グラフィックハンドル
	int m_handle[2048];

	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	bool m_isEnd;
};