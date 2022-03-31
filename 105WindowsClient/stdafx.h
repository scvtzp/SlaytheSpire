// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <d3dx9.h>
// �ΰ����� ��ɵ��� ����ִ�. ����, ��ĵ�� �������� ����. 
//#pragma comment(lib, "d3dx9.lib")

// ��ġ ���õ� ��ɵ��� ������ �ִ� ���. 
#include <d3d9.h>
// pragma comment �� ������� �ʰ� ���̺귯���� �߰��ϴ� ����� . 
// ������Ʈ ��Ŭ�� -> �Ӽ� -> ��Ŀ -> �Է� -> �߰� ���Ӽ��� �߰��� ���ִ� �͵� �ϳ��� ���. 
//#pragma comment(lib, "d3d9.lib")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

using namespace std; 


// �׷��� ��ġ �� �ٸ� ��ġ (�ϵ���� ����, ��Ʈ�ѷ� )���� �����ϱ� ���� �ش�. 
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Extern.h"
#include "Define.h"
#include "Struct.h"
#include "Enum.h"
#include "Function.h"

//Manager
#include "Device.h"
#include "TextureMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "FrameMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"

// ����
#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")