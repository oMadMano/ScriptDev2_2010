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
SDName: boss_rotface
SD%Complete: 0%
SDComment:
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    // yells
    SAY_AGGRO           = -1609461,
    SAY_SLIME_SPRAY     = -1609462,
    SAY_OOZE_EXPLODE    = -1609463,
    SAY_SLIME_FLOW1     = -1609464,     //by putricide
    SAY_SLIME_FLOW2     = -1609465,
    SAY_KILL1           = -1609466,
    SAY_KILL2           = -1609467,
    SAY_BERSERK         = -1609468,
    SAY_DEATH1          = -1609469,
    SAY_DEATH2          = -1609470,     //by putricide

    // spells
    SPELL_OOZE_FLOOD_10         = 69783, //69789,
    SPELL_OOZE_FLOOD_25         = 69797, //71215,
    SPELL_OOZE_FLOOD_10HC       = 69799, //71587,
    SPELL_OOZE_FLOOD_25HC       = 69802, //71588,
    SPELL_OOZE_FLOOD_VISUAL     = 69788,
    SPELL_SLIME_SPRAY           = 69508,
    SPELL_MUTATED_INFECTION_10  = 69674,
    SPELL_MUTATED_INFECTION_10HC= 73022,
    SPELL_MUTATED_INFECTION_25  = 71224,
    SPELL_MUTATED_INFECTION_25HC= 73023,
    SPELL_MUTATED_INFECTION     = 69706,
    SPELL_BERSERK               = 47008,
    SPELL_OOZE_COMBINE          = 69538,

    // small ooze
    SPELL_STICKY_OOZE           = 69774,
    SPELL_STICKY_OOZE_SUMM      = 69775,
    SPELL_STICKY_OOZE_TRIG      = 69776,
    SPELL_WEAK_RADIATING_OOZE   = 69750,

    // big ooze
    SPELL_RADIATING_OOZE_10     = 69760,
    SPELL_RADIATING_OOZE_10HC   = 71212,
    SPELL_RADIATING_OOZE_25     = 73026,
    SPELL_RADIATING_OOZE_25HC   = 73027,
    SPELL_UNSTABLE_OOZE         = 69558,
    SPELL_OOZE_EXPLOSION_10     = 69839,
    SPELL_OOZE_EXPLOSION_25     = 73029,
    SPELL_OOZE_EXPLOSION_25HC   = 73030,

    NPC_BIG_OOZE                = 36899,	
    NPC_SMALL_OOZE              = 36897,
    NPC_STICKY_OOZE             = 37006,	// casted by big / small ooze
	NPC_OOZE_PUDDLE				= 37013,	// used for ooze flood
};

struct Locations
{
    float x, y, z, o;
    uint32 id;
};

static Locations PipeLoc[]=
{
	// pipe z = 370-> should be a pipe stalker which triggers the spell
	{4424.396f, 3097.622f, 360.385f, 1.04f},	// 0
	{4406.661f, 3116.535f, 360.385f, 0.66f},
	{4407.328f, 3156.501f, 360.385f, 5.79f},	// 2
	{4425.439f, 3176.543f, 360.385f, 5.31f},
	{4465.495f, 3176.470f, 360.385f, 4.13f},	// 4
	{4484.887f, 3156.339f, 360.385f, 3.79f},
	{4483.696f, 3118.172f, 360.385f, 2.65f},	// 6
	{4465.826f, 3098.206f, 360.385f, 2.26f},
};

struct MANGOS_DLL_DECL boss_rotfaceAI : public ScriptedAI
{
    boss_rotfaceAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Difficulty = pCreature->GetMap()->GetDifficulty();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 Difficulty;

    uint32 m_uiOozeFloodTimer;
    uint32 m_uiSlimeSprayTimer;
    uint32 m_uiMutatedInfectionTimer;
    uint32 m_uiMutatedSummonTimer;
    uint8 m_uiOozeCount;
    uint32 m_uiWaitTimer;
    uint32 m_uiBerserkTimer;
	uint32 m_uiPipeloc;

    uint64 m_uiOozeTargetGUID;
    uint64 m_uiBigOozeGUID;

    void Reset()
    {
        m_uiOozeFloodTimer          = 25000;
        m_uiSlimeSprayTimer         = 15000;
        m_uiMutatedInfectionTimer   = 13000;
        m_uiMutatedSummonTimer      = 60000;
        m_uiWaitTimer               = 60000;
        m_uiOozeCount               = 0;
        m_uiBerserkTimer            = 300000;  // 5 min

        m_uiOozeTargetGUID          = 0;
        m_uiBigOozeGUID             = 0;
		m_uiPipeloc					= 0;
    }

	void JustReachedHome()
	{
		if(m_pInstance)
            m_pInstance->SetData(TYPE_ROTFACE, NOT_STARTED);
	}

    void Aggro(Unit *who) 
    {
        DoScriptText(SAY_AGGRO, m_creature);
        if(m_pInstance) 
            m_pInstance->SetData(TYPE_ROTFACE, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 1))
        {
            case 0: DoScriptText(SAY_KILL1, m_creature); break;
            case 1: DoScriptText(SAY_KILL2, m_creature); break;
        }
    }

    void JustDied(Unit *killer)
    {
        DoScriptText(SAY_DEATH1, m_creature);
		if (Creature* pPutricide = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_PUTRICIDE)))
            DoScriptText(SAY_DEATH2, pPutricide);
        if(m_pInstance) 
            m_pInstance->SetData(TYPE_ROTFACE, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiOozeFloodTimer < uiDiff)
        {
            if (Creature* pPutricide = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_PUTRICIDE)))
            {
                switch(urand(0, 1))
                {
                case 0: DoScriptText(SAY_SLIME_FLOW1, pPutricide); break;
                case 1: DoScriptText(SAY_SLIME_FLOW2, pPutricide); break;
                }
            }

			switch(urand(0, 4))
			{
			case 0:
				m_uiPipeloc = 0;
				break;
			case 2:
				m_uiPipeloc = 2;
				break;
			case 3:
				m_uiPipeloc = 4;
				break;
			case 4:
				m_uiPipeloc = 6;
				break;
			}

			for(uint8 i = 0; i < 2; i++)
			{
				if(Creature* pTemp = m_creature->SummonCreature(NPC_OOZE_PUDDLE, PipeLoc[m_uiPipeloc + i].x, PipeLoc[m_uiPipeloc + i].y, PipeLoc[m_uiPipeloc + i].z, PipeLoc[m_uiPipeloc + i].o, TEMPSUMMON_TIMED_DESPAWN, 20000))
				{
					pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					pTemp->SetDisplayId(11686);     // make invisible
					pTemp->setFaction(14);
					pTemp->AttackStop();
					pTemp->GetMotionMaster()->MoveIdle();
					if(Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
						pTemp->CastSpell(pTemp, SPELL_OOZE_FLOOD_10, false);
					if(Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
						pTemp->CastSpell(pTemp, SPELL_OOZE_FLOOD_25, false);
					if(Difficulty == RAID_DIFFICULTY_10MAN_HEROIC)
						pTemp->CastSpell(pTemp, SPELL_OOZE_FLOOD_10HC, false);
					if(Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
						pTemp->CastSpell(pTemp, SPELL_OOZE_FLOOD_25HC, false);
				}
			}
            m_uiOozeFloodTimer = 20000;
        }
        else
            m_uiOozeFloodTimer -= uiDiff;

        if (m_uiSlimeSprayTimer < uiDiff)
        {
			m_creature->InterruptNonMeleeSpells(true);
            DoScriptText(SAY_SLIME_SPRAY, m_creature);
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(target, SPELL_SLIME_SPRAY);
            m_uiSlimeSprayTimer = 20000;
        }
        else
            m_uiSlimeSprayTimer -= uiDiff;

        if (m_uiMutatedSummonTimer < uiDiff)
        {
            if (Unit* target = m_creature->GetMap()->GetUnit(m_uiOozeTargetGUID)) 
                DoCast(target, SPELL_MUTATED_INFECTION);
            m_uiOozeCount += 1;
            m_uiWaitTimer = 10000;
            m_uiMutatedSummonTimer = 90000;
        }
        else
            m_uiMutatedSummonTimer -= uiDiff;

        if (m_uiMutatedInfectionTimer < uiDiff)
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                m_uiOozeTargetGUID = target->GetGUID();
                if(Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
                    DoCast(target, SPELL_MUTATED_INFECTION_10);
                if(Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
                    DoCast(target, SPELL_MUTATED_INFECTION_25);
                if(Difficulty == RAID_DIFFICULTY_10MAN_HEROIC)
                    DoCast(target, SPELL_MUTATED_INFECTION_10HC);
                if(Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
                    DoCast(target, SPELL_MUTATED_INFECTION_25HC);
            }
            m_uiMutatedSummonTimer    = 12000;
            m_uiMutatedInfectionTimer = 15000;
        }
        else
            m_uiMutatedInfectionTimer -= uiDiff;

        if(m_uiWaitTimer < uiDiff)
        {
            if(m_uiOozeCount == 2)
            {
                std::list<Creature*> lOoze;
                GetCreatureListWithEntryInGrid(lOoze, m_creature, NPC_SMALL_OOZE, DEFAULT_VISIBILITY_INSTANCE);
                if (!lOoze.empty())
                {
                    for(std::list<Creature*>::iterator iter = lOoze.begin(); iter != lOoze.end(); ++iter)
                    {
                        if ((*iter) && (*iter)->isAlive())
                            (*iter)->ForcedDespawn();
                    }
                }
                if(Creature* pOoze = m_creature->SummonCreature(NPC_BIG_OOZE, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000))
                    m_uiBigOozeGUID = pOoze->GetGUID();
            }
            else if (m_uiOozeCount > 2)
            {
                std::list<Creature*> lOoze;
                GetCreatureListWithEntryInGrid(lOoze, m_creature, NPC_SMALL_OOZE, DEFAULT_VISIBILITY_INSTANCE);
                if (!lOoze.empty())
                {
                    for(std::list<Creature*>::iterator iter = lOoze.begin(); iter != lOoze.end(); ++iter)
                    {
                        if ((*iter) && (*iter)->isAlive())
                            (*iter)->ForcedDespawn();
                    }
                }
                if(Creature* pOoze = m_pInstance->instance->GetCreature(m_uiBigOozeGUID))
                    pOoze->CastSpell(pOoze, SPELL_UNSTABLE_OOZE, false);
            }
            m_uiWaitTimer = 90000;
        }
        else
            m_uiWaitTimer -= uiDiff;

        // berserk
        if (m_uiBerserkTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_BERSERK);
            DoScriptText(SAY_BERSERK, m_creature);
            m_uiBerserkTimer = 60000;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_rotface(Creature* pCreature)
{
    return new boss_rotfaceAI(pCreature);
}

struct MANGOS_DLL_DECL mob_small_oozeAI : public ScriptedAI
{
    mob_small_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiStickyOozeTimer;

    void Reset()
    {
        m_uiStickyOozeTimer = 10000;
		m_creature->SetRespawnDelay(DAY);
        DoCast(m_creature, SPELL_WEAK_RADIATING_OOZE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
		if (m_pInstance && m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStickyOozeTimer < uiDiff)
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(target, SPELL_STICKY_OOZE_SUMM);
            m_uiStickyOozeTimer = 30000;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_small_ooze(Creature* pCreature)
{
    return new mob_small_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_big_oozeAI : public ScriptedAI
{
    mob_big_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Difficulty = pCreature->GetMap()->GetDifficulty();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 Difficulty;

    uint32 m_uiStickyOozeTimer;
    uint32 m_uiDieTimer;
	bool m_bHasCasted;

    void Reset()
    {
        m_uiStickyOozeTimer = 10000;
        m_uiDieTimer        = 600000;
		m_bHasCasted		= false;
		m_creature->SetRespawnDelay(DAY);

        if(Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
            DoCast(m_creature, SPELL_RADIATING_OOZE_10);
        if(Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
            DoCast(m_creature, SPELL_RADIATING_OOZE_25);
        if(Difficulty == RAID_DIFFICULTY_10MAN_HEROIC)
            DoCast(m_creature, SPELL_RADIATING_OOZE_10HC);
        if(Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
            DoCast(m_creature, SPELL_RADIATING_OOZE_25HC);
    }

    void UpdateAI(const uint32 uiDiff)
    {
		if (m_pInstance && m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStickyOozeTimer < uiDiff)
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(target, SPELL_STICKY_OOZE_SUMM);
            m_uiStickyOozeTimer = 30000;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        if(m_uiDieTimer < uiDiff)
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        else m_uiDieTimer -= uiDiff;

        if(m_creature->HasAura(SPELL_UNSTABLE_OOZE, EFFECT_INDEX_0) && !m_bHasCasted)
        {
            if(m_creature->GetAura(SPELL_UNSTABLE_OOZE, EFFECT_INDEX_0)->GetStackAmount() == 5)
            {
                if(Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
                    DoCast(m_creature, SPELL_OOZE_EXPLOSION_10);
                if(Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
                    DoCast(m_creature, SPELL_OOZE_EXPLOSION_25);
                if(Difficulty == RAID_DIFFICULTY_10MAN_HEROIC)
                    DoCast(m_creature, SPELL_OOZE_EXPLOSION_25);
                if(Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
                    DoCast(m_creature, SPELL_OOZE_EXPLOSION_25HC);

                if (Creature* pRotface = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_ROTFACE)))
                {
                    DoScriptText(SAY_OOZE_EXPLODE, pRotface);
                    ((boss_rotfaceAI*)pRotface->AI())->m_uiOozeCount = 0;
                }
				m_bHasCasted	= true;
                m_uiDieTimer	= 4200;
            }
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_big_ooze(Creature* pCreature)
{
    return new mob_big_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_sticky_oozeAI : public ScriptedAI
{
    mob_sticky_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
		pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		pCreature->SetDisplayId(11686);     // make invisible
        pCreature->setFaction(14);
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {
		m_creature->SetRespawnDelay(DAY);
        DoCast(m_creature, SPELL_STICKY_OOZE_TRIG);
    }

    void UpdateAI(const uint32 uiDiff)
    {
		if (m_pInstance && m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_sticky_ooze(Creature* pCreature)
{
    return new mob_sticky_oozeAI(pCreature);
}

void AddSC_boss_rotface()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_rotface";
    newscript->GetAI = &GetAI_boss_rotface;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_small_ooze";
    newscript->GetAI = &GetAI_mob_small_ooze;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_big_ooze";
    newscript->GetAI = &GetAI_mob_big_ooze;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_sticky_ooze";
    newscript->GetAI = &GetAI_mob_sticky_ooze;
    newscript->RegisterSelf();
}