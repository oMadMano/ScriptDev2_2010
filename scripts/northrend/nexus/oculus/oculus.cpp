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

#include "precompiled.h"
#include "oculus.h"

#define GOSSIP_ITEM_DRAKES         "So where do we go from here?"
#define GOSSIP_ITEM_BELGARISTRASZ1 "I want to fly on the wings of the Red Flight"
#define GOSSIP_ITEM_BELGARISTRASZ2 "What abilities do Ruby Drakes have?"
#define GOSSIP_ITEM_VERDISA1       "I want to fly on the wings of the Green Flight"
#define GOSSIP_ITEM_VERDISA2       "What abilities do Emerald Drakes have?"
#define GOSSIP_ITEM_ETERNOS1       "I want to fly on the wings of the Bronze Flight"
#define GOSSIP_ITEM_ETERNOS2       "What abilities do Amber Drakes have?"

enum
{
    GOSSIP_TEXTID_DRAKES                          = 13267,
    GOSSIP_TEXTID_BELGARISTRASZ1                  = 12916,
    GOSSIP_TEXTID_BELGARISTRASZ2                  = 13466,
    GOSSIP_TEXTID_BELGARISTRASZ3                  = 13254,
    GOSSIP_TEXTID_VERDISA1                        = 1,
    GOSSIP_TEXTID_VERDISA2                        = 1,
    GOSSIP_TEXTID_VERDISA3                        = 1,
    GOSSIP_TEXTID_ETERNOS1                        = 1,
    GOSSIP_TEXTID_ETERNOS2                        = 1,
    GOSSIP_TEXTID_ETERNOS3                        = 13256,

    ITEM_EMERALD_ESSENCE                          = 37815,
    ITEM_AMBER_ESSENCE                            = 37859,
    ITEM_RUBY_ESSENCE                             = 37860,
};

bool GossipHello_oculus_dragons(Player* pPlayer, Creature* pCreature)
{
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetGUID());

	ScriptedInstance* m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData(); 
	if (m_pInstance->GetData(TYPE_DRAKOS) == DONE)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DRAKES, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DRAKES, pCreature->GetGUID());
	}

	return true;
}

bool GossipSelect_oculus_dragons(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData(); 
	if (m_pInstance->GetData(TYPE_DRAKOS) != DONE)
		return false;

	switch(pCreature->GetEntry())
	{
	case NPC_VERDISA: //Verdisa
		switch(uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
			if (!pPlayer->HasItemCount(ITEM_EMERALD_ESSENCE, 1))
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA1, pCreature->GetGUID());
			}
			else
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA2, pCreature->GetGUID());
			}
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			{
				ItemPosCountVec dest;
				uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_EMERALD_ESSENCE, 1);
				if (msg == EQUIP_ERR_OK)
					pPlayer->StoreNewItem(dest, ITEM_EMERALD_ESSENCE, true);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA3, pCreature->GetGUID());
			break;
		}
		break;
	case NPC_BELGARISTRASZ: //Belgaristrasz
		switch(uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
			if (!pPlayer->HasItemCount(ITEM_AMBER_ESSENCE, 1))
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ1, pCreature->GetGUID());
			}
			else
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ2, pCreature->GetGUID());
			}
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			{
				ItemPosCountVec dest;
				uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_RUBY_ESSENCE, 1);
				if (msg == EQUIP_ERR_OK)
					pPlayer->StoreNewItem(dest, ITEM_RUBY_ESSENCE, true);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ3, pCreature->GetGUID());
			break;
		}
		break;
	case NPC_ETERNOS: //Eternos
		switch(uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
			if (!pPlayer->HasItemCount(ITEM_RUBY_ESSENCE, 1))
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS1, pCreature->GetGUID());
			}
			else
			{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS2, pCreature->GetGUID());
			}
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			{
				ItemPosCountVec dest;
				uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_AMBER_ESSENCE, 1);
				if (msg == EQUIP_ERR_OK)
					pPlayer->StoreNewItem(dest, ITEM_AMBER_ESSENCE, true);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS3, pCreature->GetGUID());
			break;
		}
		break;
	}

	return true;
}

// override teleporters until spells get fixed
bool GoHello_oculus_teleporter( Player *pPlayer, GameObject *pGo )
{
	if(pGo->GetEntry() == GO_ORB_OF_NEXUS)
		pPlayer->TeleportTo(571, 3872.43f, 6984.34f, 108.055f, 6.20f);
	if(pGo->GetEntry() == GO_NEXUS_PORTAL)
		pPlayer->TeleportTo(578, 988.303f, 1056.88f, 359.967f, 3.42f);

	return true;
}

void AddSC_oculus()
{
	Script* newscript;
    newscript = new Script;
    newscript->Name = "oculus_teleporter";
    newscript->pGOHello = &GoHello_oculus_teleporter;
    newscript->RegisterSelf();

    //newscript = new Script;
    //newscript->Name = "oculus_dragons";
    //newscript->pGossipHello = &GossipHello_oculus_dragons;
    //newscript->pGossipSelect = &GossipSelect_oculus_dragons;
    //newscript->RegisterSelf();
}
