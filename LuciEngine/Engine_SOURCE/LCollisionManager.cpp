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
				if (mMatrix[row] == true)
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
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		Vector2 dist{ left->GetCenter() - right->GetCenter() };
		std::set<Vector2> normals;
		if (left->GetType() == eColliderType::Rect)
		{
			Vector2 topLeft, topRight, bottomRight, bottomLeft;
			GetColliderCorners(left, topLeft, topRight, bottomRight, bottomLeft);
			normals.insert((topLeft - topRight) * 0.5f);
			normals.insert((topRight - bottomRight) * 0.5f);
		}
		if (right->GetType() == eColliderType::Rect)
		{
			Vector2 topLeft, topRight, bottomRight, bottomLeft;
			GetColliderCorners(right, topLeft, topRight, bottomRight, bottomLeft);
			normals.insert((topLeft - topRight) * 0.5f);
			normals.insert((topRight - bottomRight) * 0.5f);
		}

		for (auto it = normals.begin(); it != normals.end(); ++it)
		{
			Vector2 u;
			it->Normalize(u);
			
			float sum = 0.f;
			for (auto iter = normals.begin(); iter != normals.end(); ++iter)
			{
				sum += abs(u.Dot(*iter));
			}
			float distance = abs(u.Dot(dist));
			if (distance >= sum)
			{
				return false;
			}
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

	void CollisionManager::GetColliderCorners(Collider2D* collider, Vector2& topLeft, Vector2& topRight, Vector2& bottomRight, Vector2& bottomLeft)
	{
		Vector2 halfSize = collider->GetSize() * 0.5f;

		Vector2 topLeftOffset = { -halfSize.x, halfSize.y };
		Vector2 topRightOffset = { halfSize.x, halfSize.y };
		Vector2 bottomRightOffset = { halfSize.x, -halfSize.y };
		Vector2 bottomLeftOffset = { -halfSize.x, -halfSize.y };

		topLeft = collider->GetCenter();
		topRight = collider->GetCenter();
		bottomLeft = collider->GetCenter();
		bottomRight = collider->GetCenter();

		topLeft += RotateVector(topLeftOffset, collider->GetRotation().z);
		topRight += RotateVector(topRightOffset, collider->GetRotation().z);
		bottomLeft += RotateVector(bottomLeftOffset, collider->GetRotation().z);
		bottomRight += RotateVector(bottomRightOffset, collider->GetRotation().z);
	}


}