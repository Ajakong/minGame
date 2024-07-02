#pragma once
#include"Dxlib.h"
#include <functional>
#include<iostream>
#include"Loader.h"

class SphereCollision;
class Physic;

enum class Tag
{ Player, Enemy, EnemyAttackSphere ,FightBackObj,EnemyAttackBox,EnemyAttackBomb };


class Object : public std::enable_shared_from_this<Object>
{
public:
	Object(VECTOR pos=VGet(0,0,0));
	virtual  ~Object();

	virtual void Update()=0;
	virtual void Draw() = 0;
	virtual void Hit()=0;

	VECTOR GetPos()const { return m_pos; }

	void CollisionSetPos(VECTOR pos);
	void CollisonSetRadius(float& radius);

	std::shared_ptr<SphereCollision> GetSphereCol() { return m_SphereCol; }

	Tag GetTag() { return m_tag; }

	/// <summary>
	/// �����蔻�肪�������Ă��邩
	/// </summary>
	bool GetHitFlag() { return m_isHitFlag; }
	bool GetExtinctionFlag() { return m_isExtinction; }
protected:
	Tag m_tag;


	VECTOR m_pos;
	std::shared_ptr<SphereCollision> m_SphereCol;

	bool m_isHitFlag = true;
	//�I�u�W�F�N�g�����ł���Ƃ���true;
	bool m_isExtinction = false;
};

