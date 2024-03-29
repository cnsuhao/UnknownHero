/********************************************************************
	created:	2015/01/19
	created:	19:1:2015   0:03
	filename: 	E:\cyvasse\TestAI\Soldier.h
	file path:	E:\cyvasse\TestAI
	file base:	Soldier
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Soldier_h__
#define Soldier_h__



#include "Vector2D.h"
#include "GridPos.h"

//
#include "Messaging/MessageListener.h"
#include "CreatureBase.h"

class AttackSystem;
class ShieldSystem;
class TargetingSystem;
//
class SoldierPF;
class AttackData;
class DamageData;

class SkillList;

class GameSkill;
//

//老虎机的三个轴

class Soldier:public MessageListener,public CreatureBase ,public AIProperty
{
	friend class SoldierManager;
public: 
	enum
	{
		Human,Orc
	};
public:

	static int NextCreateID;

	Soldier(int race);
	virtual ~Soldier();

	// add by Hitman [7/8/2015]
	virtual void Init();

	int	GetCampIndex(){return CampIndex;}
	void SetCampIndex(int c){CampIndex = c;}
	int	GetRaceIndex(){return RaceIndex;}
	void SetRaceIndex(int r){RaceIndex = r;}


	int	GetID(){return ID;}
	void SetID(int id){ ID = id;}//不要轻易用！！！
	//当soldier被deploy到chunk之后会调用一下
	virtual void OnDeployChunk(){}
	//这个函数还没确定在什么地方调用
	virtual void OnUndeployChunk(){}



	virtual void Update();
	virtual void Render();
	//这个move是瞬移的
	bool MoveForward(int step = 1);
	bool MoveBackward(int step = 1);
	bool MoveLeft(int step = 1);
	bool MoveRight(int step = 1);
	virtual void BeginMove();
	virtual void EndMove();
	bool MoveTo(const GridPos& GPos);
	//这个move是动画移动的,需要cocos2dx的支持
	virtual void BeginTraval() {}
	virtual void EndTraval();
	virtual bool TravalTo(const GridPos& GPos);
	//攻击操作
	//攻击动画完成后，去核算攻击数据
	virtual void Attack(Soldier* other , int number);
	virtual void Attack(const GridPos& gPos , int number);
	virtual void GetHurt(const DamageData& damageData);//这里传递的引用，如果要动画，应该memcpy

	//virtual void UseDeputyWeapon(Soldier* other, int DWeaponNumber);
	/* 攻击完成 */
	virtual void CallBack_AttackFinish();
	/* 攻击成功 */
	virtual void CallBack_AttackSuccess(const DamageData& damageData); //这里传递的引用，如果要动画，应该memcpy
	/* 结束了一个回合 */
	virtual void FinishRound(){}
	//得到一条到目标的路径
	void GetPathToTarget(const GridPos& A,const GridPos& B,std::vector<GridPos>& path);
	//向给定的GPos点靠近一步
	void MoveCloseToGPos(const GridPos& other,GridPos& out_nextGPos);
	//向给定的GPos点远离一步
	void MoveAwayFromGPos(const GridPos& other,GridPos& out_nextGPos);

	/*
		寻找在范围内的Soldier
	//	参数	@ RangeSize			范围尺寸
	//		@ ExceptSelf		释否除去自己
			@ RType				范围的Type
			@ out_SoldierList	结果列表

	*/
	void FindSoldiersInRange(int RangeSize, bool ExceptSelf , int RType ,std::vector<Soldier*>&	out_SoldierList);
	//释放显示攻击范围
	void SetShowAttackRange(bool s){bShowAttackRange = s;}
	bool IsShowAttackRange(){return bShowAttackRange;}
	//显示移动路径
	void SetShowMovePath(bool s){bShowMovePath = s;}
	bool IsShowMovePath(){return bShowMovePath;}
	//强制移动到GPos上,不建议直接使用
	void SetToGPos(const GridPos& GPos);
	bool CanSetTo(const GridPos& GPos){return canStay(GPos);}
	//是否可以在此GPos上停留
	virtual bool canStay(const GridPos& GPos);
	//Soldier* canAttack( const GridPos& GPos );
	bool canSelect( const GridPos& GPos );


	const GridPos& GetStayGPos() const {return StayGridPos;}
	const GridPos& GetLastStayGPos() const {return LastStayGridPos;}
	const Vector2D& GetPosition() const {return Position;}


	virtual void InitSkills(){}
	virtual void CancleSkill(){}
	bool IsUsingSkill();
	//GameSkill* GetAttackSystem() {return pMainWeapon;}
	SkillList* GetSkillList() 
	{
		return pSkillList;
	}
	ShieldSystem* GetShieldSystem() { return pShieldSystem;}
	TargetingSystem* GetTargetingSystem() {return pTargetingSystem;}
	SoldierPF*		GetSoldierPF() {return pSoldierPF;}
	/*
		Override
	*/
	virtual bool HandleMessage(const Telegram& telegram) override;
public:
	//玩家操作时候用的
	bool    bPossessed;
	bool    IsPossessed(){return bPossessed;}
	//Soldier 受到控制
	void    TakePossession();
	//Soldier 离开控制
	void    Exorcise();
public:
	//更新位置 WorldPos
	void UpdatePosition();
	//更新GPos
	void UpdateNodeWithGPos();
	//死亡时候删除nodedata用的
	void ClearNodeWithGPos();
	//更新PF位置
	void UpdateSoldierPFPosition();

	virtual void showAttackRange(const std::vector<GridPos>&	AttackGPosList);
private:
	Vector2D Position;				//所在的世界位置
	int		 ID;					//ID
	int		 RaceIndex;					//种族
	int		 CampIndex;					//阵营
	GridPos	 StayGridPos;			//所在的网格位置
	GridPos	 LastStayGridPos;		//上次所在的网格位置
	//
	bool	bShowAttackRange;
	bool	bShowMovePath;

	//GameSkill*	pCurUsingSkill;
	SkillList*  pSkillList;

	ShieldSystem*   pShieldSystem;
	TargetingSystem* pTargetingSystem;
	//
	SoldierPF*	pSoldierPF;

};

#endif // Soldier_h__
