// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <d3dx9.h>
// 부가적인 기능들이 들어있다. 벡터, 행렬등등 수학적인 연산. 
//#pragma comment(lib, "d3dx9.lib")

// 장치 관련된 기능들을 가지고 있는 헤더. 
#include <d3d9.h>
// pragma comment 를 사용하지 않고 라이브러리를 추가하는 방법은 . 
// 프로젝트 우클릭 -> 속성 -> 링커 -> 입력 -> 추가 종속성에 추가를 해주는 것도 하나의 방법. 
//#pragma comment(lib, "d3d9.lib")

// C 런타임 헤더 파일입니다.
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


// 그래픽 장치 및 다른 장치 (하드웨어 사운드, 컨트롤러 )등을 제어하기 위한 해더. 
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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

// 사운드
#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")