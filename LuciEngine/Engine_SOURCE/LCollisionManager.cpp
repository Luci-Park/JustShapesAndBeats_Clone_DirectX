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
				if (rightCol == nullptr) continue;

				ColliderCollision(leftCol, rightCol);
			}
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// �� �浹ü�� ID bool���� Ȯ��
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// �浹������ �����´�
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// �浹
			if (iter->second == false)
			{
				//���� �浹
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				// �浹 ��
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹 X
			if (iter->second == true)
			{
				// �浹�ϰ� �ִٰ� ������
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		std::set<Vector3> normals;
		if (left->GetType() == eColliderType::Rect)
		{

		}
		// �׸� �׸� �浹
		// �и��� �̷�

		// To do... (����)
		// �и����� ��ƴ� �Ͻôºе���
		// �� - �� �浹

		return false;
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

}