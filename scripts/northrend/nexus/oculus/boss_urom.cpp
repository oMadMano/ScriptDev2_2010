/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Urom
SD%Complete: 80
SDComment: Is not working SPELL_ARCANE_SHIELD. SPELL_FROSTBOMB has some issues, the damage aura should not stack.
SDCategory: Instance Script
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

enum
{
	// yells
	SAY_SUMMON1					= -1578018,
	SAY_SUMMON2					= -1578019,
	SAY_SUMMON3					= -1578020,
	SAY_AGGRO					= -1578021,
	SAY_EXPLOSION1				= -1578022,
	SAY_EXPLOSION2				= -1578023,
	SAY_SLAY1					= -1578024,
	SAY_SLAY2					= -1578025,
	SAY_SLAY3					= -1578026,
	SAY_DEATH					= -1578027,

	// spells
	SPELL_ARCANE_SHIELD                           = 53813, //Dummy --> Channeled, shields the caster from damage.
	SPELL_EMPOWERED_ARCANE_EXPLOSION              = 51110,
	SPELL_EMPOWERED_ARCANE_EXPLOSION_2            = 59377,
	SPELL_FROSTBOMB                               = 51103, //Urom throws a bomb, hitting its target with the highest aggro which inflict directly 650 frost damage and drops a frost zone on the ground. This zone deals 650 frost damage per second and reduce the movement speed by 35%. Lasts 1 minute.
	SPELL_SUMMON_MENAGERIE                        = 50476, //Summons an assortment of creatures and teleports the caster to safety.
	SPELL_SUMMON_MENAGERIE_2                      = 50495,
	SPELL_SUMMON_MENAGERIE_3                      = 50496,
	SPELL_TELEPORT                                = 51112, //Teleports to the center of Oculus
	SPELL_TIME_BOMB                               = 51121, //Deals arcane damage to a random player, and after 6 seconds, deals zone damage to nearby equal to the health missing of the target afflicted by the debuff.
	SPELL_TIME_BOMB_2                             = 59376,

	NPC_PHANTASMAL_CLOUDSCRAPER                   = 27645,
	NPC_PHANTASMAL_MAMMOTH                        = 27642,
	NPC_PHANTASMAL_WOLF                           = 27644,

	NPC_PHANTASMAL_AIR                            = 27650,
	NPC_PHANTASMAL_FIRE                           = 27651,
	NPC_PHANTASMAL_WATER                          = 27653,

	NPC_PHANTASMAL_MURLOC                         = 27649,
	NPC_PHANTASMAL_NAGAL                          = 27648,
	NPC_PHANTASMAL_OGRE                           = 27647
};


struct MANGOS_DLL_DECL boss_uromAI : public ScriptedAI
{
	boss_uromAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
		Reset();
	}

	ScriptedInstance* m_pInstance;
	bool m_bIsRegularMode;

	float x,y;

	bool bCanCast;
	bool bCanGoBack;

	uint8 uiGroup[3];

	uint32 uiTeleportTimer;
	uint32 uiArcaneExplosionTimer;
	uint32 uiCastArcaneExplosionTimer;
	uint32 uiFrostBombTimer;
	uint32 uiTimeBombTimer;

	void Reset()
	{
		//if (pInstance && pInstance->GetData(DATA_VAROS_EVENT) != DONE)
		//	DoCast(SPELL_ARCANE_SHIELD);

		//if (pInstance)
		//	pInstance->SetData(DATA_UROM_EVENT, NOT_STARTED);

		/*if (pInstance && pInstance->GetData(DATA_UROM_PLATAFORM) == 0)
		{
			uiGroup[0] = 0;
			uiGroup[1] = 0;
			uiGroup[2] = 0;
		}*/

		x,y = 0.0f;
		bCanCast = false;
		bCanGoBack = false;

		//me->GetMotionMaster()->MoveIdle();

		uiTeleportTimer = urand(30000,35000);
		uiArcaneExplosionTimer = 9000;
		uiCastArcaneExplosionTimer = 2000;
		uiFrostBombTimer = urand(5000,8000);
		uiTimeBombTimer = urand(20000,25000);
	}

	void EnterCombat(Unit* pWho)
	{
		/*if (pInstance)
			pInstance->SetData(DATA_UROM_EVENT, IN_PROGRESS);

		SetGroups();
		SummonGroups();
		CastTeleport();

		if (pInstance && pInstance->GetData(DATA_UROM_PLATAFORM) != 3)
			pInstance->SetData(DATA_UROM_PLATAFORM,pInstance->GetData(DATA_UROM_PLATAFORM)+1);*/
	}

	void AttackStart(Unit* pWho)
	{
		/*if (!pWho)
			return;

		if (me->GetPositionZ() > 518.63f)
			DoStartNoMovement(pWho);

		if (me->GetPositionZ() < 518.63f)
		{
			if (me->Attack(pWho, true))
			{
				DoScriptText(SayAggro[3],me);

				me->SetInCombatWith(pWho);
				pWho->SetInCombatWith(me);

				me->GetMotionMaster()->MoveChase(pWho, 0,0);
			}
		}*/
	}

	void SetGroups()
	{
		/*if (!pInstance || pInstance->GetData(DATA_UROM_PLATAFORM) != 0)
			return;

		while (uiGroup[0] == uiGroup[1] || uiGroup[0] == uiGroup[2] || uiGroup[1] == uiGroup[2])
		{
			uiGroup[0] = urand(0,2);
			uiGroup[1] = urand(0,2);
			uiGroup[2] = urand(0,2);
		}*/
	}

	void SetPosition(uint8 uiI)
	{
		/*switch(uiI)
		{
		case 0:
			x = me->GetPositionX() + 4;
			y = me->GetPositionY() - 4;
			break;
		case 1:
			x = me->GetPositionX() + 4;
			y = me->GetPositionY() + 4;
			break;
		case 2:
			x = me->GetPositionX() - 4;
			y = me->GetPositionY() + 4;
			break;
		case 3:
			x = me->GetPositionX() - 4;
			y = me->GetPositionY() - 4;
			break;
		default:
			break;
		}*/
	}

	void SummonGroups()
	{
		/*if (!pInstance || pInstance->GetData(DATA_UROM_PLATAFORM) > 2)
			return;

		for (uint8 uiI = 0; uiI < 4 ; uiI++)
		{
			SetPosition(uiI);
			me->SummonCreature(Group[uiGroup[pInstance->GetData(DATA_UROM_PLATAFORM)]].uiEntry[uiI],x,y,me->GetPositionZ(),me->GetOrientation());
		}*/
	}

	void CastTeleport()
	{
		/*if (!pInstance || pInstance->GetData(DATA_UROM_PLATAFORM) > 2)
			return;

		DoScriptText(SayAggro[pInstance->GetData(DATA_UROM_PLATAFORM)],me);
		DoCast(TeleportSpells[pInstance->GetData(DATA_UROM_PLATAFORM)]);
		*/
	}

	void UpdateAI(const uint32 uiDiff)
	{
		/*Return since we have no target
		if (!UpdateVictim())
			return;

		if (!pInstance || pInstance->GetData(DATA_UROM_PLATAFORM) < 2)
			return;

		if (uiTeleportTimer <= uiDiff)
		{
			me->InterruptNonMeleeSpells(false);
			DoScriptText(SAY_TELEPORT,me);
			me->GetMotionMaster()->MoveIdle();
			DoCast(SPELL_TELEPORT);
			uiTeleportTimer = urand(30000,35000);

		} else uiTeleportTimer -= uiDiff;

		if (bCanCast && !me->FindCurrentSpellBySpellId(SPELL_EMPOWERED_ARCANE_EXPLOSION))
		{
			if (uiCastArcaneExplosionTimer <= uiDiff)
			{
				bCanCast = false;
				bCanGoBack = true;
				DoCastAOE(SPELL_EMPOWERED_ARCANE_EXPLOSION);
				uiCastArcaneExplosionTimer = 2000;
			}else uiCastArcaneExplosionTimer -= uiDiff;
		}

		if (bCanGoBack)
		{
			if (uiArcaneExplosionTimer <= uiDiff)
			{
				Position pPos;
				me->getVictim()->GetPosition(&pPos);

				me->NearTeleportTo(pPos.GetPositionX(),pPos.GetPositionY(),pPos.GetPositionZ(),pPos.GetOrientation());
				me->GetMotionMaster()->MoveChase(me->getVictim(),0,0);
				me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);

				bCanCast = false;
				bCanGoBack = false;
				uiArcaneExplosionTimer = 9000;
			} else uiArcaneExplosionTimer -= uiDiff;
		}

		if (!me->IsNonMeleeSpellCasted(false, true, true))
		{
			if (uiFrostBombTimer <= uiDiff)
			{
				DoCastVictim(SPELL_FROSTBOMB);
				uiFrostBombTimer = urand(5000,8000);
			} else uiFrostBombTimer -= uiDiff;

			if (uiTimeBombTimer <= uiDiff)
			{
				if (Unit* pUnit = SelectTarget(SELECT_TARGET_RANDOM))
					DoCast(pUnit,SPELL_TIME_BOMB);

				uiTimeBombTimer = urand(20000,25000);
			} else uiTimeBombTimer -= uiDiff;
		}*/

		DoMeleeAttackIfReady();
	}

	void JustDied(Unit* killer)
	{
		//if (pInstance)
		//	pInstance->SetData(DATA_UROM_EVENT, DONE);
	}

	void JustSummoned(Creature* pSummon)
	{
		//pSummon->SetInCombatWithZone();
	}

	void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
	{
		/*switch(pSpell->Id)
		{
		case SPELL_SUMMON_MENAGERIE:
			me->SetHomePosition(968.66f,1042.53f,527.32f,0.077f);
			LeaveCombat();
			break;
		case SPELL_SUMMON_MENAGERIE_2:
			me->SetHomePosition(1164.02f,1170.85f,527.321f,3.66f);
			LeaveCombat();
			break;
		case SPELL_SUMMON_MENAGERIE_3:
			me->SetHomePosition(1118.31f,1080.377f,508.361f,4.25f);
			LeaveCombat();
			break;
		case SPELL_TELEPORT:
			me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY); // with out it the npc will fall down while is casting
			bCanCast = true;
			break;
		default:
			break;
		}*/
	}
};

CreatureAI* GetAI_boss_urom(Creature* pCreature)
{
	return new boss_uromAI (pCreature);
}

void AddSC_boss_urom()
{
	Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_urom";
    newscript->GetAI = &GetAI_boss_urom;
    newscript->RegisterSelf();
}
