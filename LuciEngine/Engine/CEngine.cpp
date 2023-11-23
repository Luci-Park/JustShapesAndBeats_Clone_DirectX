#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
{
}

CEngine::~CEngine()
{
}

int CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hWnd = _hWnd;
	m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

	RECT rt = { 0, 0, (int)_iWidth, (int)_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hWnd, true);

	//Device 초기화
	// 
	//Managers 초기화

	return S_OK;
}

void CEngine::progress()
{
	//engine, object update
	tick();
	//render
	render();
	//LateUpdate
}

void CEngine::tick()
{
	//
}

void CEngine::render()
{
}
