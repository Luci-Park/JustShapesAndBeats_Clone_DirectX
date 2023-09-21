#pragma once
#define NOMINMAX
#include <string>
#include <Windows.h>
#include <assert.h>

#include <vector> // �迭
#include <list> //��ũ�帮��Ʈ 
#include <map> // 2��Ʈ��
#include <bitset> // ��Ʈ �迭 ���ϰ� ������ִ� ���̺귯��
#include <set> // �ؽ� ���̺�
#include <unordered_set>
#include <functional> // �Լ� ������

#include <cmath> //����
#include <random>
#include <algorithm> //���� �˰���
#include <limits> //�ε� �Ҽ��� ǥ�� �� �ݿø��� ���õ� Ŭ���� ���ø� numeric_limits �� �� ���� �������� �����մϴ�.
#include <memory> //�޸� ���õ� ���̺귯��
#include <filesystem> // ��������� ���ϰ� �����ִ� ���̺귯��
#include <wrl.h>
#include <windef.h>

#include "CommonInclude.h"
#include "LEnums.h"
#include "LMath.h"

#define PI 3.141592
#define DEBUGLOG(x) OutputDebugStringA(x)
#define LERP(start, end, t) (start + ((t > 1.0) ? 1.0 : ((t < 0.0) ? 0.0 : t)) * (end - start))