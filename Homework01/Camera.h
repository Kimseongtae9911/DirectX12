#pragma once
#include "Mesh.h"

class CViewport
{
private:
	int m_nLeft = 0;
	int m_nTop = 0;
	int m_nWidth = 0;
	int m_nHeight = 0;

public:
	CViewport() {}
	virtual ~CViewport() {}

public:
	void SetViewport(int nLeft, int nTop, int nWidth, int nHeight);
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetLeft() { return m_nLeft; }
	int GetTop() { return m_nTop; }
};

class CPlayer;

class CCamera
{
private:
	XMFLOAT3 m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

private:
	float m_fFOVAngle = 90.0f;
	float m_fProjectRectDistance = 1.0f;
	float m_fAspectRatio = float(FRAMEBUFFER_WIDTH) / float(FRAMEBUFFER_HEIGHT);

private:
	BoundingFrustum	 m_xmFrustumView = BoundingFrustum();
	BoundingFrustum	 m_xmFrustumWorld = BoundingFrustum();
	XMFLOAT4X4 m_xmf4x4InverseView = Matrix4x4::Identity();

public:
	XMFLOAT4X4 m_xmf4x4View = Matrix4x4::Identity();
	XMFLOAT4X4 m_xmf4x4PerspectiveProject = Matrix4x4::Identity();
	XMFLOAT4X4 m_xmf4x4ViewPerspectiveProject = Matrix4x4::Identity();
			   
	XMFLOAT4X4 m_xmf4x4OrthographicProject = Matrix4x4::Identity();
	XMFLOAT4X4 m_xmf4x4ViewOrthographicProject = Matrix4x4::Identity();

	CViewport m_Viewport;

public:
	CCamera();
	virtual ~CCamera();

public:
	void SetFOVAngle(float fFOVAngle);

	void GenerateViewMatrix();
	void GeneratePerspectiveProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fFOVAngle);
	void GenerateOrthographicProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fWidth, float hHeight);
	void SetViewport(int nLeft, int nTop, int nWidth, int nHeight);

	void SetLookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);
	void SetLookAt(XMFLOAT3& xmf3Position, XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	void Move(XMFLOAT3& xmf3Shift);
	void Move(float x, float y, float z);
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
	void Update(CPlayer* pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed = 0.016f);

	bool IsInFrustum(BoundingOrientedBox& xmBoundingBox);
};
