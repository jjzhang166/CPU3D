#include "c3dFrame.h"
#include <windows.h>

int c3dFrame::c3dInit()
{
	const int screenw = 1200;
	const int screenh = 800;
	TCHAR title[] = _T("c3d frame");
	cam.ration = screenw / screenh;


	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screen_events, 0, 0, 0, 
		NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), screenw, -screenh, 1, 32, BI_RGB, 
		screenw * screenh * 4, 0, 0, 0, 0 }  };

	RECT rect = {0,0,screenw,screenh};
	int wx, wy, sx, sy;
	LPVOID ptr;
	HDC hDC;
	close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	hwnd = CreateWindow(_T("SCREEN3.1415926"), title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == NULL) return -2;
	hDC = GetDC(hwnd);
	sHdc = CreateCompatibleDC(hDC);
	ReleaseDC(hwnd, hDC);

	hbitmap = CreateDIBSection(sHdc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (hbitmap == NULL) return -3;

	screen_ob = (HBITMAP)SelectObject(sHdc, hbitmap);
	screen_fb = (unsigned char*)ptr;
	screen_pitch = screenw * 4;

	AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(hwnd , NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(hwnd);

	ShowWindow(hwnd, SW_NORMAL);
	dispatch();

//	memset(screen_keys, 0, sizeof(int) * 512);
	memset(screen_fb, 0,screenw * screenh * 4);
	vec4 eye = vec4( 3, 0, 0, 1 );
	vec4 at = vec4 (0, 0, 0, 1 );
	vec4 up = vec4 ( 0, 0, 1, 1 );
	c3dLookAt(mview,eye,at,up);
	//matrix_set_lookat(&device->transform.view, &eye, &at, &up);
	//transform_update(&device->transform);
	transform = mworld * mview * project;
	return 0;
}

void c3dFrame::c3dUpdate()
{
	transform = mworld * mview * project;
}

void c3dFrame::c3dDraw()
{

}

void c3dFrame::c3dKeyPressed(int key)
{

}

void c3dFrame::c3dSetIdentity(mat4x4& m)
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; 
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void c3dFrame::c3dLookAt(mat4x4& m,vec4& eye,vec4& at,vec4& up)
{
	vec3 xaxis, yaxis;
	vec3 zaxis;
	vec4 z = at - eye;
	zaxis = vec3(z);
	normalize(zaxis);
	xaxis = cross(vec3(up),zaxis);
	normalize(xaxis);
	yaxis = cross(zaxis,xaxis);

	//vector_sub(&zaxis, at, eye);
	//vector_normalize(&zaxis);
	//vector_crossproduct(&xaxis, up, &zaxis);
	//vector_normalize(&xaxis);
	//vector_crossproduct(&yaxis, &zaxis, &xaxis);
	//vec3 xaxis3 = cross(up.xyz(),zaxis.xyz());
	m[0][0] = xaxis.x;
	m[1][0] = xaxis.y;
	m[2][0] = xaxis.z;
	m[3][0] = -1 * dot(xaxis,vec3(eye));
	// m[3][0] = -vector_dotproduct(&xaxis, eye);
	m[0][1] = yaxis.x;
	m[1][1] = yaxis.y;
	m[2][1] = yaxis.z;
	m[3][1] = -1 * dot(yaxis,vec3(eye));
	//	 m[3][1] = -vector_dotproduct(&yaxis, eye);
	m[0][2] = zaxis.x;
	m[1][2] = zaxis.y;
	m[2][2] = zaxis.z;
	m[3][2] = dot(zaxis,vec3(eye));
	//	 m[3][2] = -vector_dotproduct(&zaxis, eye);
	m[0][3] =  m[1][3] =  m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void c3dFrame::perspective(mat4x4& m, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);

	c3dSetZero(m);
	m[0][0] = (float)(fax / aspect);
	m[1][1] = (float)(fax);
	m[2][2] = zf / (zf - zn);
	m[3][2] = - zn * zf / (zf - zn);
	m[2][3] = 1;
}

void c3dFrame::c3dSetZero(mat4x4& m)
{
	m[0][0] =  m[0][1] =  m[0][2] =  m[0][3] = 0.0f;
	m[1][0] =  m[1][1] =  m[1][2] =  m[1][3] = 0.0f;
	m[2][0] =  m[2][1] =  m[2][2] =  m[2][3] = 0.0f;
	m[3][0] =  m[3][1] =  m[3][2] =  m[3][3] = 0.0f;
}

LRESULT c3dFrame::screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg) {
		/*case WM_CLOSE: screen_exit = 1; break;
		case WM_KEYDOWN: screen_keys[wParam & 511] = 1; break;
		case WM_KEYUP: screen_keys[wParam & 511] = 0; break;*/
	//case :break;
	//default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
	return 0;
}

void c3dFrame::close()
{
	if (sHdc) {
		if (sHdc) { 
			SelectObject(sHdc, hbitmap); 
			hbitmap = NULL; 
		}
		DeleteDC(sHdc);
		hbitmap = NULL;
	}
	if (hbitmap) { 
		DeleteObject(hbitmap); 
		hbitmap = NULL; 
	}
	if (hbitmap) { 
		CloseWindow(hwnd); 
		hwnd = NULL; 
	}
}

void c3dFrame::dispatch()
{
	MSG msg;
	while (1) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

c3dFrame::c3dFrame()
{
	this->c3dInit();
}

c3dFrame::~c3dFrame()
{

}

void c3dFrame::c3dDeviceSetTexture( void *bits, long pitch, int w, int h)
{
	// 设置当前纹理
		char *ptr = (char*)bits;
		int j;
		assert(w <= 1024 && h <= 1024);
		for (j = 0; j < h; ptr += pitch, j++) 	// 重新计算每行纹理的指针
			texture[j] = (unsigned int *)ptr;
		tex_width = w;
		tex_height = h;
		max_u = (float)(w - 1);
		max_v = (float)(h - 1);
}
