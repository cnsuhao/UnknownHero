#include "Goal_Attack.h"
#include "Msg_Type.h"
#include "Actor/Monster.h"


Goal_Attack::Goal_Attack( Monster* pBot,Soldier* pTargetBot )
	:Goal<Monster>(pBot, goal_attack),m_pTargetBot(pTargetBot)
{

}

void Goal_Attack::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->Attack(m_pTargetBot, 0);
	//
	m_iStatus = completed;
}

int Goal_Attack::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Attack::Terminate()
{

}

bool Goal_Attack::HandleMessage( const Telegram& msg )
{
	return true;
}
