#include "stdafx.h" //stdafx�� ������ ��Ƴ��� ��������̹Ƿ� �ٸ������� stdafx�� ������ ��� ��ȣ������ 
					//�ƴϴ��� �����ϰ� cpp�� �������
#include "gameNode.h"

//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//	//_backBuffer�� ���� ������ ���� ���ۿ� �ٸ��� �� ��Ʈ�� �ʱ�ȭ �Լ� ���
//}

HRESULT gameNode::init(void) //WM_CREATE (���������ν��� �ݹ��Լ��� switch case�� �ش��ϴ� �޽���)
{
	_hdc = GetDC(_hWnd); //_hWnd (������ �ڵ��ȣ�� ����ִ� _hWnd�� ��ǲ���� ������ �� �������� DC�� ������)
	
	_managerInit = false;

	return S_OK; //S_OK : ������ Boolean TRUE ��(0X0)���� S_FALSE�� �Բ� ���Ǹ� �Լ��� �����Ͽ����� �ǹ��Ѵ�.
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd); //_hWnd (������ �ڵ��ȣ�� ����ִ� _hWnd�� ��ǲ���� ������ �� �������� DC�� ������)
	//GetDC�� ReleaseDC�� ����ϸ� WM_PAINT���� ���� BeginPaint�� EndPaint�� ���� �ʾƵ� �ȴ�.
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL); //_hWnd�� �� ������Ʈ���� ����ϴ� HWND�� �ν��Ͻ� �̸�, 1�� Ÿ�̸� �̸�, 10�� 10ms
									  //WM_TIMER���� �������� ���Ǵ� timer ����
		KEYMANAGER->init(); //KEYMANGER�� keyManager::getSingleton()
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		TXTDATA->init();
	}

	return S_OK;
}

void gameNode::release(void) //WM_DESTROY
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton(); //releaseSingleton�� keyManger�� ���� �θ��� singletoneBase�� ���ǵǾ�����
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		
		//RND->releaseSingleton(); Ŀ��ŧ�������� �ϰ� ���� ����
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void) //WM_TIMER
{
	//InvalidateRect(_hWnd, NULL, true);
	//InvalidateRect(_hWnd, NULL, false); //���� ���۸��� ����ϹǷ� ������ false�� ����
	//timeManager �߰��ϸ鼭 �̺κ� �ּ�ó��
	//WM_PAINT�� â ���ο� ��ȿȭ ������ ����� ������ �޽���(â�� ũ�⸦ �����Ѵٰų�, �ٸ� â�� �������ų�)
	//��ȿȭ ������ ������ WM_PAINT �ȵ��´�
	//WM_TIMER���� InvalidateRect�� �����ϸ�, �� ���������� ��ȿȭ�ǰ� ������ WM_PAINT �޽����� ������
	//==> TIMER �����ð����� ��ȿȭ ==> WM_PAINT �޽��� ����
	//timeManager �߰� �� render�� WM_PAINT �޽��� �����ð� �ƴ϶� �ƹ��� �޽����� ������ ���� �� �����ϹǷ�
	//InvalidateRect�� �ʿ������
	//InvalidateRect ����:http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=636
	//��ȿȭ������ �׸��� 
	// ��ȿȭ ����(Invalid Region)�� ���� ������ ��� ���� PAINTSTRUCT ����ü ������ �����մϴ�
	//PAINTSTRUCT ps;
	//
	// BeginPaint �Լ��� ������ ��ȿȭ ����(Invalid Region)���� �׸� �� �ִ� DC��
	// �̸� ������ PAINTSTRUCT ����ü ������ ��ȿȭ ����(Invalid Region)�� ������ 
	// ��� �ִ� ������ �մϴ�.
	// BeginPaint �Լ��� ȣ���� �������� �׸��� �۾��� ������ EndPaint �Լ��� ȣ���Ͽ�
	// �׸��� �۾��� �������� �˷��ݴϴ�.
	//HDC h_dc = BeginPaint(hWnd, &ps);
	//
	// ..... ��ȿȭ ����(Invalid Region)�� �ٽ� �׷��ִ� �۾� ....
	//
	//EndPaint(hWnd, &ps);

}

void gameNode::render()
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND HDC ����:https://m.blog.naver.com/PostView.nhn?blogId=winterwolfs&logNo=10165689957&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
	//hWnd : ��� �����쿡�� �޽����� �߻��ϴ��� üũ�Ѵ� //�ڵ� �������� ����, �� ���α׷����� �������� â�� ��� �� �ִ�(������ Theta APIâ �Ѱ�).
	//�� �������߿��� ������â���� ������ ��ȣ��(HWND)�� ���� �����Ѵ�.
	//iMessage : �޽��� ���� ��ȣ
	//wParam : Ű���� �Է� && ���콺 Ŭ�� �޽��� ����
	//lParam : ���콺 ��ǥ�� �޽����� ����

	//WndProc�� �μ��� ��� 4���̸� MSG ����ü�� ��� 4���� �����ϴ�.hWnd�� �޽����� ���� �������� �ڵ��̸� iMessage�� � ������ �޽����ΰ�, 
	//�� � ��ȭ�� �߻��ߴ°��� ���� ������ ������.iMessage�� WM_MOVE�̸� �������� ��ġ�� ����Ǿ����� �˸��� WM_DESTROY�̸� �����찡 �ı��Ǿ����� �˸��� ���̴�.

	//wParam, lParam�� iMessage�� �޽����� ���� �ΰ����� ������ ������.���� ��� ���콺 ��ư�� �������ٴ� WM_LBUTTONDOWN �޽����� �ԷµǾ��ٸ� 
	//ȭ���� ����뿡�� ���콺 ��ư�� �������°�, �׶��� Ű���� ��Ȳ(Shift, Ctrl, Alt)�� ��Ѱ��� ���� ������ �߰��� �ʿ��ϸ� WM_CHAR �޽���, 
	//�� Ű����κ��� Ű�� �ԷµǾ��ٴ� �޽����� �ԷµǾ��ٸ� � Ű�� �ԷµǾ��°��� ���� �߰����� ������ �ʿ��ϴ�.�̷� �߰� �������� wParam, lParam���� ���޵ȴ�.
	//wParam, lParam�� ������ � ���� ���޵Ǵ����� �޽������� �ٸ���.

	//PAINTSTRUCT ps; //�׸��� �׷��ִ� �װ��� ����ü
	//HDC hdc; //Handle Device Context. Device Context�� ��¿� �ʿ��� ������ ������ ������ ����ü�� ��ǥ, ��, ���� �� ��¿� �ʿ��� ��� ������ ��� �ִ�. %%HDC�� �����Ͱ� �ƴϴ� (���� �ǹ�?)
	//%%���̻� WM_PAINT���� BeginPaint, EndPaint�� �׸��� �ʰ� �ܺ�(mainGame�� render)���� �׸��Ƿ� �� �κ����� �ʿ����.

	////HDC hMemDC; //�޸� �ӿ��� �̸� �׸��� �׷����� �� ����� ��
	////HBITMAP hBitmap, OldBitmap; //HBITMAP�� ������ ��Ʈ�� ��ȭ��.  ����:http://soen.kr/lecture/win32api/lec6/lec6-4-2.htm ����2:http://hyeongjin-kim.blogspot.kr/2013/05/ddb-dib.html (DDB(HBITMAP)�� DIB ����)
	//////RECT windowRect; //������ â�� ũ�⸦ ��Ƴ��� RECT //WINSIZEX�� WINSIZEY�� ��� ����غ���

	switch (iMessage)
	{
		//�����찡 ó�� ������ �� �� �� ����Ǵ� ��(�ʱ�ȭ)
		//�����찡 ó�� �����ٴ� ��ȣ�� WM_CREATE
	case WM_CREATE:
	{
		//this->init(); �̺κп��� init()�� ���������� �ʾƵ� 
		//winMain�� FAILED(_mg.init())�� �˾Ƽ� ��������ش�
		break;
	}

	//timeManager ������ �� ����
	//case WM_PAINT:
	//{
	//	//������۸� ����1:http://3dmpengines.tistory.com/1520
	//	//����2:http://heart4u.co.kr/tblog/330
	//	//BitBlt, TransparentBlt ���� ���� ���� ����:http://skmagic.tistory.com/255
	//
	//
	//	//BeginPaint : �ʱ�ȭ �Լ�? �Ǵ� ���� ������ �־��ִ� �Լ�
	//	hdc = BeginPaint(hWnd, &ps); //&ps�� ps�� �ƴ϶� ps�� �ּ� //��: int a = 33; int *b = &a; 
	//
	//	//////GetClientRect(hWnd, &windowRect); //hWnd�� â ������ windowRect�� �����Ѵ�.
	//	////
	//	////hMemDC = CreateCompatibleDC(hdc); //hMemDC�� ���� DC�� ������ ��ǥ, ��, ������� ������ �ֱ�
	//	////hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //hdc�� ����(��, ���� ��)�� ������ windowRect ũ���� ��Ʈ�� ��ȭ�� ����
	//	////														   //hdc�� ȣȯ�Ǵ� ������ ��Ʈ���� windowRect.righ, windowRect.bottom ũ��� �����. ���⼭ "ȣȯ�ȴ�"�� ���� ���� ������ ���ٴ�
	//	////														   //���̸� �� ��Ȯ�ϰ� ǥ�����ڸ� ������ �ȼ��� ��Ʈ���� ���ٴ� ���̴�.
	//	////														   //�� ȭ���� 256���� ��Ʈ�ʵ� 256��Ʈ���� �ǰ� Ʈ�� �÷� ȭ���̸� ��Ʈ�ʵ� Ʈ�� �÷��� ����� ���ٴ� ���̴�. http://hyeongjin-kim.blogspot.kr/2013/05/ddb-dib.html
	//	////
	//	////OldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap); //SelectObject�� HBITMAP�� ���� GDI ������Ʈ���� �ڵ�(����) ���� �����ϴ� �Լ� ����:http://blog.naver.com/PostView.nhn?blogId=tipsware&logNo=220988055352&categoryNo=57&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
	//	////													//SelectObject(HDC ��ü�� ������Ʈ�� ���� DC,HGDIOBJ ���Ӱ� ������ GDI ������Ʈ�� �ڵ鰪) bitmap, pen, brush, font, region ���氡��
	//	////													//�� �Լ��� GDI ������Ʈ ��ü �۾��� �����ϸ�, DC�� ������ ����ϰ� �ִ� GDI ������Ʈ�� �ڵ鰪�� ��ȯ�ϰ� (���⼭ �� ���� OldBitmap�� �����ϰ��ִ�.) �����ϸ� NULL ���� ��ȯ�Ѵ�.
	//	////													//��: �� Brush ��ü�� �ڵ鰪�� 0x10000012�̰� ������ DC�� ����Ǿ� �ִ� Brush ��ü �ڵ� ���� 0x30000412�� ���, 
	//	////													//�Լ��� ����ϸ� DC�� ����Ǿ��ִ� brush �ڵ� ���� 0x10000012�� ����ǰ� 0x30000412�� ��ȯ�Ѵ�.    
	//	////
	//	////													//����ȯ�� �ϴ� ������ �ι�° �μ��� Ÿ������ �Լ��� �������� Return ���� �ڷ����� HGDIOBJ�� HBITMAP,HPEN, HBRUSH, HFONT�� �����ϴ� �����ڷ����̱⶧����
	//	////													//HGDIOBJ h_gdiobj = h_brush; �� ���������� �ݴ�� HBRUSH h_brush = h_gdiobj�� ������ ����. ==>HBRUSH h_brush = (HBITMAP)h_gdiobj���� ����ȯ�� �� �ʿ䰡 �ִ�.
	//	////
	//	//////������ BITMAP (��ȭ��)�� ��ü�Ͽ����Ƿ�, ��ȭ���� �Ͼ�� ĥ�Ѵ�. (��Ʈ���� �⺻ ������ ����� ����)
	//	////HBRUSH BkBrush = CreateSolidBrush(RGB(255, 255, 255));
	//	////RECT windowRect = { WINSIZEX , WINSIZEY };
	//	////FillRect(hMemDC, &windowRect, BkBrush);
	//	////DeleteObject(BkBrush);
	//	//////delete &windowRECT;
	//	////
	//	////this->render(hMemDC); //���⼭ this�� �ڼտ��� MainProc�� ����� ��� �� �ڼ��� ��Ī 
	//	//////���� ���۸��� ����ϹǷ� ���� hdc�� �ƴ϶� hMemDC�� ��ǲ���� �ִ´�
	//	////BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, hMemDC, 0, 0, SRCCOPY); //hMemDC�ȿ� 0,0 ��ǥ��������, windowRect.right�� �ʺ�, windowRect.bottom�� ���̸� ������ �κ��� hdc�� 0,0��ǥ�� SRCCOPY������� �����Ѵ�.
	//	////															  //SRCCOPY : �ҽ� ������ ��� ������ �����Ѵ�.
	//	////															  //DSTINVERT: ȭ���� ������Ų��.
	//	////															  //MERGECOPY: �ҽ� ��Ʈ�ʰ� ��� ȭ���� AND �����Ѵ�.
	//	////															  //MERGEPAINT: �ҽ� ��Ʈ�ʰ� ��� ȭ���� OR �����Ѵ�.
	//	////															  //WHITENESS: ��󿵿��� ������� ä���.
	//	////															  //BLACKNESS: ��󿵿��� ���������� ���� ä���.
	//	////															  //����:http://soen.kr/lecture/win32api/lec6/lec6-4-3.htm
	//	////
	//	////DeleteObject(SelectObject(hMemDC, OldBitmap)); //SelectObject�� ������Ʈ�� ��ü�԰� ���ÿ� ��ü�Ǿ� ���� ������Ʈ�� �����ϹǷ� OldBitmap�� hMemDC�� �ٽ� �ǵ����� hBitmap�� ��������
	//	////											   // �ٷ� �ؿ��� DC ������ �����ִµ� ������Ʈ�� �ٲٰ� ���� �ʿ䰡 ������?
	//	////											   // �̰� ������ ���ҽ� ��ũ�� �Ͼ��? https://stackoverflow.com/questions/8875395/win32-double-buffering-drawing-black-background �� ���
	//	////											   // %%%%% hMemDC���� SelectObject�� ���� OldBitmap�� ����DeleteDC(hMemDC);���� ����������, hBitmap�� ���� hMemDC������ ���� �����ְԵȴ�. �ݵ�� DeleteObject�� �޸� �Ҵ��� Ǯ����� �Ѵ�.
	//	////DeleteDC(hMemDC);
	//	//////ReleaseDC()�� �޸𸮿� �Ҵ�� ȭ�� DC�� �����ϱ� ���� �뵵�� ���˴ϴ�.
	//	//////ȭ�� DC ���� �޸𸮿� �Ҵ�� DC�� �ڵ��� ������ �ֱ� ������ �ݵ�� �����ؾ� �մϴ�.
	//	//////DeleteDC()�� �޸𸮿� �Ҵ�ǰ� �޸𸮻󿡼� ����ϴ� DC�� �����ϱ� ���� �뵵�� ���˴ϴ�.
	//	//////�����ϱ� �����ڸ�, ȭ�鿡 ���̴� ���� ReleaseDC()�� ȭ�鿡 ������ �ʰ� �޸𸮻󿡸� �Ҵ��
	//	//////DC�� DeleteDC()�� �����ؾ� �մϴ�. ����:http://myfreechild.tistory.com/m/37
	//
	//
	//	this->render();
	//	EndPaint(hWnd, &ps); //hdc�� GetDC�� �޾ƿ��� �ʰ� BeginPaint�� ��������Ƿ�
	//						 //ReleaseDC��� EndPaint ���
	//	break;
	//}
	//
	//case WM_TIMER:
	//{
	//	this->update();
	//	break;
	//}

	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		//_ptMouse.x = LOWORD(lParam); 
		//_ptMouse.y = HIWORD(lParam);
		//�� ���� ����ȯ�ؼ� ����� .

		//c++ ����ȯ
		//static_cast
		//reinterpret_cast
		//������ �ؿ��� 2�� ���θ��ض�
		//dynamic_cast
		//const_cast

		break;
	}

	//Ű���� �̺�Ʈ ���� : http://jurang5.tistory.com/
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			PostMessage(hWnd, WM_DESTROY, 0, 0); //hWnd�� iMessage�� WM_DESTROY �޼����� ������
			break;
		}
		}
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}
