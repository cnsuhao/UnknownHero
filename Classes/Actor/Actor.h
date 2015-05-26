#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Actor/ActorBody.h"
#include "Game/Soldier.h"

#include "Actor/ActorFSM.h"

class Actor : public Soldier, public cocos2d::Sprite
{
protected:
	enum  ActorAnimType
	{
		ActorAnim_Stand = 0,
		ActorAnim_Move,
		ActorAnim_Attack,
		ActorAnim_Die,
		ActorAnim_Win,
	};
public:
	Actor(void);
	~Actor(void);

	virtual void BeginTraval() override;
	virtual void EndTraval() override;
	virtual bool TravalTo(const GridPos& GPos) override;

	virtual void Attack(Soldier* other) override;

	virtual void playMoveAnimation(){};
	virtual void playAttackAnimation(){};
	// modify by Hitman [5/19/2015]
	// 很多攻击是跟着动画一起去完成的，所以，应该先得到合适的动画，然后在状态中去合成一个动作序列
	virtual cocos2d::Animate* createAttackAnimation(int ani_type);

	//------
	void SetResource(std::string name);	
	void UpdateToCCWorldPos();

	//------
	virtual void ActorReadyStart(){}
	virtual void ActorReadyUpdate(float dt){}
	virtual void ActorReadyEnd(){}

	virtual void ActorStandStart(){}
	virtual void ActorStandUpdate(float dt){}
	virtual void ActorStandEnd(){}

	virtual void ActorMoveStart(){}
	virtual void ActorMoveUpdate(float dt){}
	virtual void ActorMoveEnd(){}

	virtual void ActorAttackStart();
	virtual void ActorAttackUpdate(float dt);
	virtual void ActorAttackEnd();

	virtual void ActorDieStart(){}
	virtual void ActorDieUpdate(float dt){}
	virtual void ActorDieEnd(){}

	virtual void ActorWinStart(){}
	virtual void ActorWinUpdate(float dt){}
	virtual void ActorWinEnd(){}
	//------
	virtual void AIThink();

	virtual void CalcAttack( AttackData* pAtkData );
	//------
	virtual void ActorHurtStart(){}
	virtual void ActorHurtUpdate(float dt){}
	virtual void ActorHurtEnd(){}
	//------

protected:
	virtual void showAttackRange(const std::vector<GridPos>&	AttackGPosList) override;

public:
	ActorFSM* m_pFSM;
	//


	// add by Hitman [5/19/2015]
protected:
	AttackData* m_pTempAtkData;

protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;	

	static const float g_ActorMoveTime;
};

#endif //__ACTOR_H__