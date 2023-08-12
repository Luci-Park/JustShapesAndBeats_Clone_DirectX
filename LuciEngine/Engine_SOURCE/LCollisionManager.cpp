#include "LCollisionManager.h"
#include "LGameObject.h"
#include "LScene.h"
#include "LSceneManager.h"
#include "LLayer.h"
#include "LCollider2D.h"

namespace lu
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};


	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
					LayerCollision((eLayerType)column, (eLayerType)row);
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;
		const std::vector<GameObject*>& lefts = activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights = activeScene->GetLayer(right).GetGameObjects();

		for (int i = 0; i < lefts.size(); ++i)
		{
			if (lefts[i]->GetState() != GameObject::eState::Active) continue;

			Collider2D* leftCol = lefts[i]->GetComponent<Collider2D>();
			if (leftCol == nullptr)	continue;

			for (int j = 0; j < rights.size(); ++j)
			{
				if (rights[i]->GetState() != GameObject::eState::Active) continue;

				Collider2D* rightCol = rights[i]->GetComponent<Collider2D>();
				if (rightCol == nullptr || leftCol == rightCol) continue;

				ColliderCollision(leftCol, rightCol);
			}
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				//최초 충돌
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				// 충돌 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		if (left->GetType() == eColliderType::Circle && right->GetType() == eColliderType::Circle)
		{
			float centerDistanceSqr = Vector2::DistanceSquared(left->GetCenter(), right->GetCenter());
			float radiusDistanceSqr = (left->GetSize().x + right->GetSize().x) * 0.5f;
			radiusDistanceSqr *= radiusDistanceSqr;
			if (radiusDistanceSqr < centerDistanceSqr)
				return false;
			return true;
		}
		std::vector<Vector2> axis;
		if (left->GetType() == eColliderType::Circle)
		{
			Vector2 acrossAxis = left->GetCenter() - right->GetCenter();
			acrossAxis.Normalize();
			axis.push_back(acrossAxis);
		}
		else if (left->GetType() == eColliderType::Rect)
		{
			Vector2 upA, rightA;
			upA.x = left->GetOwner()->mTransform->Up().x;
			upA.y = left->GetOwner()->mTransform->Up().y;

			rightA.x = left->GetOwner()->mTransform->Right().x;
			rightA.y = left->GetOwner()->mTransform->Right().y;

			axis.push_back(upA);
			axis.push_back(rightA);
		}
		if (right->GetType() == eColliderType::Circle)
		{
			Vector2 acrossAxis = left->GetCenter() - right->GetCenter();
			acrossAxis.Normalize();
			axis.push_back(acrossAxis);
		}
		else if (right->GetType() == eColliderType::Rect)
		{
			Vector2 upA, rightA;
			upA.x = right->GetOwner()->mTransform->Up().x;
			upA.y = right->GetOwner()->mTransform->Up().y;

			rightA.x = right->GetOwner()->mTransform->Right().x;
			rightA.y = right->GetOwner()->mTransform->Right().y;

			axis.push_back(upA);
			axis.push_back(rightA);
		}
		for (auto ax = axis.begin(); ax != axis.end(); ax++)
		{
			float leftmin, leftmax, rightmin, rightmax;
			if (left->GetType() == eColliderType::Rect) GetRectMinMax(left, *ax, leftmin, leftmax);
			else if (left->GetType() == eColliderType::Circle) GetCircleMinMax(left, *ax, leftmin, leftmax);

			if (right->GetType() == eColliderType::Rect) GetRectMinMax(right, *ax, rightmin, rightmax);
			else if (right->GetType() == eColliderType::Circle) GetCircleMinMax(right, *ax, rightmin, rightmax);
			if (leftmin > rightmax || rightmin > leftmax)
				return false;
		}
		return true;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}

	void CollisionManager::GetRectMinMax(Collider2D* col, Vector2 axis, float& min, float& max)
	{
		Vector2 center = col->GetCenter();
		Vector2 halfSize = col->GetSize() * 0.5;
		Matrix rotation = Matrix::CreateFromQuaternion(col->GetRotation());
		Vector2 localCorners[4] = {
			{-halfSize.x, -halfSize.y},
			{-halfSize.x, halfSize.y},
			{halfSize.x, -halfSize.y},
			{halfSize.x, halfSize.y},
		};
		for (int i = 0; i < 4; ++i) {
			DirectX::XMVECTOR localCorner = DirectX::XMLoadFloat2(&localCorners[i]);
			DirectX::XMVECTOR rotatedCorner = DirectX::XMVector2Transform(localCorner, rotation);
			rotatedCorner = DirectX::XMVectorAdd(DirectX::XMLoadFloat2(&center), rotatedCorner);
			float dot = axis.Dot(rotatedCorner);
			if (i == 0)
			{
				min = dot;
				max = min;
			}
			else
			{
				if (min > dot) min = dot;
				if (max < dot) max = dot;
			}
		}
	}

	void CollisionManager::GetCircleMinMax(Collider2D* col, Vector2 axis, float& min, float& max)
	{
		float center = axis.Dot(col->GetCenter());
		min = center - col->GetSize().x * 0.5;
		max = center + col->GetSize().x * 0.5;
	}


}