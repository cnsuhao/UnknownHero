#include "GameAction_Bomb.h"
#include "Scene\GameManager.h"
#include "Actor\Hero.h"
#include "Actor\PlayerManager.h"
#include "Weapon\SkillList.h"


GameAction_Bomb::GameAction_Bomb(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 0;
	m_SkillID = 0;
}


GameAction_Bomb::~GameAction_Bomb(void)
{
}

void GameAction_Bomb::UseAction(int nlevel)
{
	//test
	if (GameManager::GetInstance()->GetFightST() == FightStatus::SF_Hero)
	{
		Hero* pHero = PlayerManager::GetInstance()->GetHero();
		if (pHero != nullptr && pHero->GetSkillList()!=nullptr)
		{
			pHero->GetSkillList()->UseSkill(m_SkillID, nlevel);
		}
	}
	//end
}