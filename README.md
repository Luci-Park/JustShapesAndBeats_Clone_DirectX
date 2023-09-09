# Just Shapes and Beats Clone

- 개발 기간 : 2023.05.15 ~ 진행 중
- 스택 : C++, WinAPI, DirectX11
- 개발 인원 : 1
- 대상 플랫폼 : Windows

---

# 📜프로젝트 설명

DirectX11와 게임 엔진 대해 공부하기 위해 제작 중인 Just Shapes and Beats 모작입니다. 특히 graphics pipeline과 particle 생성에 집중하고 있습니다. 

Just Shapes and Beats는 Berzerk Studio에서 개발 된 리듬 탄막 게임입니다. 이펙트와 파티클이 많은 게임이기 때문에 모작 대상으로 선택했습니다.

Shader를 많이 다뤄볼 수 있는 기회라 좋습니다.

# 기본 기능

## Particle System

`ParticleSystem`은 파티클들의 모양과 움직임, 시간 등을 관리하는 클래스이다. 특히 플레이어가 움직일때 움직임 정도에 따라 개수가 변하므로 `RateOverDistance`를 신경써서 만들었다.

이것으로 플레이어 이동을 만들었으며 추후에 스테이지에 쓰일 이펙트를 만들 것이다.


<img src = "https://github.com/Luci-Park/JustShapesAndBeats_Clone_DirectX/assets/97658764/7e9027dd-a24d-4df7-8a48-f196a282bb27" width=50% height=50%>
<img src = "https://github.com/Luci-Park/JustShapesAndBeats_Clone_DirectX/assets/97658764/b46fb27d-f77d-4da9-ace5-026e30279f31" width=50% height=50%>

생각해 두었으나 시간상 문제로 보류해 둔것:

- Unity의 Shape module처럼 파티클의 시작 모양을 잡는 것

- SpriteSheet을 주어 파티클에 에니메이션을 만드는 것.

## Collider2D & CollisionManager

두 클래스가 충돌의 처리를 담당한다. `Collider2D`가 컬라이더의 크기와 상태를, `CollisionManager`가 충돌 여부를 확인한다.

이 때 충돌을 확인하는 함수는 `CollisionManager::Intersect`에서 처리한다. 분리축 이론에 의거하여 사각형과 원이 회전 상황에서도 충돌하도록 만들었다.

## Animator

`GameObject`의 다양한 `Component`들을 에니매이팅 할 수 있는 컴포넌트. `Transform`, `Collider`, `MeshRenderer`를 에니메이팅 할 수 있다. 타이밍에 맞춘 function call 또한 가능하다. Keyframe에 상태를 저장하여 시간에 따라 interpolation으로 애니메이션을 처리한다.



처음에 `KeyFrame`을 `Union`으로 설정했는데 `shared_ptr`이나 `function<void()>`에서 오류가 났었기 때문에 각자의 구조체로 분리하였다.

그 오류란 `Union`에서 초기화 과정을 거치지 않는다는 점에서 일어났다. `shared_ptr`나 `function`은 `=` 오퍼레이션 때 그 전 정보를 삭제하고 새로운 정보를 집어넣는다. 헌데 `Union`에서 초기화를 하지 않았기 때문에 접근 오류가 났었다. `Union`은 런타임 때 타입이 바뀌기 때문에 미리 초기화 시킬 수가 없었다. 복잡한 형식은 Union을 하지 않는게 좋다는 것을 배웠다.
