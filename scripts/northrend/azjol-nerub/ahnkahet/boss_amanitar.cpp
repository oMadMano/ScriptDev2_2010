/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Amanitar
SD%Complete: 80%
SDComment: Timers 
SDAuthor: Tassadar
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"
#include "ahnkahet.h"

enum
{
    //Amanitar spells
    SPELL_BASH               = 57094,
    SPELL_VENOM_BOLT         = 57088,
    SPELL_ENTANGLING_ROOTS   = 57095,
    SPELL_MINI               = 57055, // this one and SPELL_POTENT_FUNGUS MUST stack!

    //Mushroom spells
    SPELL_POISON_CLOUD       = 57061,
    SPELL_POISONOUS_MUSHROOM_VISUAL = 56741,
    SPELL_POTENT_FUNGUS      = 56648, // this one and SPELL_MINI MUST stack!
    SPELL_PUTRID_MUSHROOM    = 31690, // They should look like mushroom

    //Script thinks that all mushrooms which are spawned are only healthy, so change entry only for poisinous
    NPC_HEALTHY_MUSHROOM     = 30391,
    NPC_POISONOUS_MUSHROOM   = 30435,
};

struct LocationsXY
{
    float x, y, z;
    uint32 id;
};
static LocationsXY MushroomLoc[]=
{
    {338.361053f,-879.169312f,-74.346985f},
    {355.021393f,-864.248657f,-75.258141f},
    {382.234924f,-870.168640f,-74.763039f}, 
    {398.212097f,-882.812195f,-74.419968f},
    {391.769653f,-901.039368f,-78.281616f}, 
    {368.704224f,-907.145691f,-81.627701f},
    {354.933533f,-853.599854f,-74.380493f},
    {334.626862f,-843.550171f,-74.213554f},
    {387.515747f,-861.414978f,-72.161438f},
    {333.274994f,-894.845337f,-73.749512f},
};
/*######
## boss_amanitar
######*/

struct MANGOS_DLL_DECL boss_amanitarAI : public ScriptedAI
{
    boss_amanitarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiBashTimer;
    uint32 m_uiVenomBoltTimer;
    uint32 m_uiRootsTimer;
    uint32 m_uiMiniTimer;


    void Reset()
    {
        m_uiBashTimer = 8000;
        m_uiVenomBoltTimer = 12000;
        m_uiRootsTimer = 19000;
        m_uiMiniTimer = 30000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        SummonMushrooms();
        ShowMushrooms();

        if(m_bIsRegularMode == true)
            m_creature->ForcedDespawn();

        m_pInstance->SetData(TYPE_AMANITAR, IN_PROGRESS);
    }
    void EnterEvadeMode()
    {
        ShowMushrooms(false);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, FAIL);

        m_creature->GetMotionMaster()->MoveTargetedHome();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, DONE);
    }

    void SummonMushrooms()
    {
        for(uint8 i = 0; i < 10; i++)
        {
            uint32 MushroomId = 0;
            switch(urand(0, 1))
            {
            case 0: MushroomId = NPC_HEALTHY_MUSHROOM; break;
            case 1: MushroomId = NPC_POISONOUS_MUSHROOM; break;
            }
            m_creature->SummonCreature(MushroomId, MushroomLoc[i].x, MushroomLoc[i].y, MushroomLoc[i].z, 0, TEMPSUMMON_TIMED_DESPAWN, 600000);
        }
    }

    void ShowMushrooms(bool show = true)
    {
        std::list<Creature*> lMushroomsHealthy;
        GetCreatureListWithEntryInGrid(lMushroomsHealthy, m_creature, NPC_HEALTHY_MUSHROOM, 150.0f);
        for(std::list<Creature*>::iterator itr1 = lMushroomsHealthy.begin(); itr1 != lMushroomsHealthy.end(); itr1++)
        {
            if(show)
                (*itr1)->SetVisibility(VISIBILITY_ON);
            else
                (*itr1)->SetVisibility(VISIBILITY_OFF);
        }
        std::list<Creature*> lMushroomsPoison;
        GetCreatureListWithEntryInGrid(lMushroomsPoison, m_creature, NPC_POISONOUS_MUSHROOM, 150.0f);
        for(std::list<Creature*>::iterator itr2 = lMushroomsPoison.begin(); itr2 != lMushroomsPoison.end(); itr2++)
        {
            if(show)
                (*itr2)->SetVisibility(VISIBILITY_ON);
            else
                (*itr2)->SetVisibility(VISIBILITY_OFF);
        }

    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Bash
        if(m_uiBashTimer <= uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_BASH);
            m_uiBashTimer = 8000 + rand()%5000;
        }else m_uiBashTimer -= uiDiff;

        //Venom bolt volley
        if(m_uiVenomBoltTimer <= uiDiff)
        {
            DoCast(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_VENOM_BOLT);
            m_uiVenomBoltTimer = 15000 + rand()%5000;
        }else m_uiVenomBoltTimer -= uiDiff;

        //Entangling Roots
        if(m_uiRootsTimer <= uiDiff)
        {
            DoCast(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_ENTANGLING_ROOTS);
            m_uiRootsTimer = 18000 + rand()%5000;
        }else m_uiRootsTimer -= uiDiff;

        //Mini
        if(m_uiMiniTimer <= uiDiff)
        {
            DoCast(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_MINI);
            m_uiMiniTimer = 30000;
        }else m_uiMiniTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_amanitar(Creature* pCreature)
{
    return new boss_amanitarAI(pCreature);
}
/*######
## npc_amanitar_mushroom
######*/

struct MANGOS_DLL_DECL npc_amanitar_mushroomAI : public ScriptedAI
{
    npc_amanitar_mushroomAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiMushroomType; //0 = healthy, 1 = poisinous
    bool m_bIsDead;
    uint32 m_uiRespawnTimer;

    void Reset()
    {
        m_bIsDead = false;
        m_uiRespawnTimer = 30000;

        DoCast(m_creature,SPELL_PUTRID_MUSHROOM,true);
        m_creature->SetVisibility(VISIBILITY_OFF);

        ResetMushroom();
    }

    void ResetMushroom()
    {
        m_uiMushroomType = urand(0, 1);
        if(m_uiMushroomType == 1)
        {
            m_creature->UpdateEntry(NPC_POISONOUS_MUSHROOM);
            m_creature->CastSpell(m_creature, SPELL_POISONOUS_MUSHROOM_VISUAL, true);
        }else{
            m_creature->RemoveAurasDueToSpell(SPELL_POISONOUS_MUSHROOM_VISUAL);
            m_creature->UpdateEntry(NPC_HEALTHY_MUSHROOM);
        }
        DoCast(m_creature,SPELL_PUTRID_MUSHROOM,true);
        if(m_bIsDead)
            m_creature->SetVisibility(VISIBILITY_OFF);
    }
    void AttackStart(Unit *pWho)
    {
        return;
    }
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_bIsDead)
        {
            uiDamage = 0;
            return;
        }

        if (uiDamage > m_creature->GetHealth())
        {
            m_bIsDead = true;
            uiDamage = 0;
            if(m_uiMushroomType == 0)
            {
                m_creature->CastSpell(m_creature, SPELL_POTENT_FUNGUS, true);
                ThreatList const& tList = m_creature->getThreatManager().getThreatList();
                    for (ThreatList::const_iterator iter = tList.begin();iter != tList.end(); ++iter)
                    {
                        Unit* pUnit = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid());
                        if (pUnit && (pUnit->GetTypeId() == TYPEID_PLAYER))
                        {
                            if (pUnit->HasAura(SPELL_MINI))
                                pDoneBy->RemoveAurasDueToSpell(SPELL_MINI);
                        }
                    }
            }
            else
                m_creature->CastSpell(m_creature, SPELL_POISON_CLOUD, true);

            m_creature->SetHealth(1);
            m_creature->SetVisibility(VISIBILITY_OFF);
        }
    }
    void JustDied(Unit* pKiller)
    {
        m_creature->Respawn();
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if(m_bIsDead)
        {
            if(m_uiRespawnTimer <= uiDiff)
            {
                m_bIsDead = false;
                ResetMushroom();
                m_creature->SetHealth(m_creature->GetMaxHealth());
                m_creature->SetVisibility(VISIBILITY_ON);
                m_uiRespawnTimer = 30000;                
            }else m_uiRespawnTimer -= uiDiff;
        }       
    }
};

CreatureAI* GetAI_npc_amanitar_mushroom(Creature* pCreature)
{
    return new npc_amanitar_mushroomAI(pCreature);
}
void AddSC_boss_amanitar()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_amanitar";
    newscript->GetAI = &GetAI_boss_amanitar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_amanitar_mushroom";
    newscript->GetAI = &GetAI_npc_amanitar_mushroom;
    newscript->RegisterSelf();
}
