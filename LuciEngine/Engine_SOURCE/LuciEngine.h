#pragma once
#define NOMINMAX
#include <string>
#include <Windows.h>
#include <assert.h>

#include <vector> // 배열
#include <list> //링크드리스트 
#include <map> // 2진트리
#include <bitset> // 비트 배열 편하게 사용해주는 라이브러리
#include <set> // 해시 테이블
#include <unordered_set>
#include <functional> // 함수 포인터

#include <cmath> //수학
#include <random>
#include <algorithm> //정렬 알고리즘
#include <limits> //부동 소수점 표현 및 반올림과 관련된 클래스 템플릿 numeric_limits 및 두 개의 열거형을 정의합니다.
#include <memory> //메모리 관련된 라이브러리
#include <filesystem> // 파일입출력 편하게 도와주는 라이브러리
#include <wrl.h>
#include <windef.h>

#include "CommonInclude.h"
#include "LEnums.h"
#include "LMath.h"

#define PI 3.141592
#define DEBUGLOG(x) OutputDebugStringA(x)
#define LERP(start, end, t) (start + ((t > 1.0) ? 1.0 : ((t < 0.0) ? 0.0 : t)) * (end - start))