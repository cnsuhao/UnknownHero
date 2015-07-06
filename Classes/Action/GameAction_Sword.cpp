#include "GameAction_Sword.h"
#include "Scene\GameManager.h"
#include "Actor\PlayerManager.h"
#include "Actor\Hero.h"
#include "Weapon\SkillList.h"
#include "Actor\BossManager.h"
#include "Actor\Boss\Boss.h"


GameAction_Sword::GameAction_Sword(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 1;
	m_SkillID = 0;
}


GameAction_Sword::~GameAction_Sword(void)
{
}

void GameAction_Sword::UseAction(int nlevel)
{
	//如果是玩家行动 那么就是玩家去挥剑
	if (GameManager::GetInstance()->GetFightST() == FightStatus::SF_Hero)
	{
		Hero* pHero = PlayerManager::GetInstance()->GetHero();
		if (pHero != nullptr && pHero->GetSkillList()!=nullptr)
		{
			pHero->GetSkillList()->UseSkill(m_SkillID, nlevel);
		}
	}
	else if (GameManager::GetInstance()->GetFightST() == FightStatus::SF_BOSS)
	{
		Boss* pBoss = BossManager::GetInstance()->GetBoss();
		if (pBoss != nullptr)
		{
			pBoss->UseBossAction(m_ActionTypeID, nlevel);
		}
	}
}

//void GameAction_Sword::UseActionBeforeSelectRange(int nlevel)
//{
//	;
//}