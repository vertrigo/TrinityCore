/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Unit.h"
#include "Vehicle.h"
#include "VehicleDefines.h"

#define DATA_FIREFIGHTER 31803189
#define DATA_SET_UP_US_THE_BOMB 29893237


enum Yells
{
    SAY_AGGRO                                   = 0,
    SAY_HARDMODE_ON                             = 1,
    SAY_MKII_ACTIVATE                           = 2,
    SAY_MKII_SLAY                               = 3,
    SAY_MKII_DEATH                              = 4,
    SAY_VX001_ACTIVATE                          = 5,
    SAY_VX001_SLAY                              = 6,
    SAY_VX001_DEATH                             = 7,
    SAY_AERIAL_ACTIVATE                         = 8,
    SAY_AERIAL_SLAY                             = 9,
    SAY_AERIAL_DEATH                            = 10,
    SAY_V07TRON_ACTIVATE                        = 11,
    SAY_V07TRON_SLAY                            = 12,
    SAY_V07TRON_DEATH                           = 13,
    SAY_BERSERK                                 = 14,
    //Computer
    SAY_HARDMODE                                = 0,
    SAY_10_MIN                                  = 1,
    SAY_9_MIN                                   = 2,
    SAY_8_MIN                                   = 3,
    SAY_7_MIN                                   = 4,
    SAY_6_MIN                                   = 5,
    SAY_5_MIN                                   = 6,
    SAY_4_MIN                                   = 7,
    SAY_3_MIN                                   = 8,
    SAY_2_MIN                                   = 9,
    SAY_1_MIN                                   = 10,
    SAY_DESTROY_MIN                             = 11,
    SAY_OVERRIDE_MIN                            = 12,
    // MK II
    EMOTE_PLASMA_BLAST                          = 0,
    
};

enum Spells
{
    // Leviathan MK II
    SPELL_MINES_SPAWN                           = 65347,
    SPELL_PROXIMITY_MINES                       = 63027,
    SPELL_PLASMA_BLAST                          = 62997,
    SPELL_SHOCK_BLAST                           = 63631,
    SPELL_EXPLOSION                             = 66351,
    SPELL_NAPALM_SHELL                          = 63666,
    SPELL_TRIGGER_MISSILE                       = 65347,
    // VX-001
    SPELL_RAPID_BURST                           = 63382,
    SPELL_RAPID_BURST_LEFT_10                   = 63387,
    SPELL_RAPID_BURST_RIGHT_10                  = 64019,
    SPELL_RAPID_BURST_LEFT_25                   = 64531,
    SPELL_RAPID_BURST_RIGHT_25                  = 64532,
    SPELL_ROCKET_STRIKE                         = 63036,
    SPELL_ROCKET_STRIKE_AURA                    = 64064,
    SPELL_ROCKET_STRIKE_DMG                     = 63041,
    SPELL_SPINNING_UP                           = 63414,
    SPELL_HEAT_WAVE                             = 63677,
    SPELL_HAND_PULSE                            = 64348,
    // Aerial Command Unit
    SPELL_PLASMA_BALL                           = 63689,
    SPELL_MAGNETIC_CORE                         = 64436,
    SPELL_MAGNETIC_CORE_VISUAL                  = 64438,
    SPELL_BOOM_BOT                              = 63801,
    SPELL_MAGNETIC_FIELD                        = 64668,
    SPELL_HOVER                                 = 57764, // Set Hover position
    SPELL_BERSERK                               = 47008,
    // Hard Mode
    SPELL_SELF_DESTRUCTION                      = 64610,
    SPELL_SELF_DESTRUCTION_VISUAL               = 64613,
    SPELL_EMERGENCY_MODE                        = 64582,
    SPELL_FLAME_SUPPRESSANT                     = 64570,
    SPELL_FLAME_SUPPRESSANT_VX001               = 65192,
    SPELL_SUMMON_FLAMES_INITIAL                 = 64563,
    SPELL_FLAME                                 = 64561,
    SPELL_FROST_BOMB                            = 64624,
    SPELL_FROST_BOMB_EXPLOSION_10               = 64626,
    SPELL_FROST_BOMB_EXPLOSION_25               = 65333,
    SPELL_WATER_SPRAY                           = 64619,
    SPELL_DEAFENING_SIREN                       = 64616,
    // NPCs
    SPELL_BOMB_BOT                              = 63801,
    SPELL_NOT_SO_FRIENDLY_FIRE                  = 65040,
    // Achievement
    SPELL_NOT_SO_FRIENDLY_FIRE_CREDIT           = 65040,
};

enum Npcs
{
    NPC_ROCKET                                  = 34050,
    NPC_BURST_TARGET                            = 34211,
    NPC_JUNK_BOT                                = 33855,
    NPC_ASSAULT_BOT                             = 34057,
    NPC_BOOM_BOT                                = 33836,
    NPC_EMERGENCY_BOT                           = 34147,
    NPC_FLAME                                   = 34363,
    NPC_FLAME_SPREAD                            = 34121,
    NPC_FROST_BOMB                              = 34149,
    NPC_MKII_TURRET                             = 34071,
    NPC_COMPUTER                                = 34143,
    NPC_MINE                                    = 34362,
};

enum Events
{
    // Intro
    EVENT_INTRO_1,
    EVENT_INTRO_2,
    EVENT_INTRO_3,
    EVENT_INTRO_4,
    EVENT_HARD_1,
    EVENT_HARD_2,
    EVENT_VX001_1,
    EVENT_VX001_2,
    EVENT_VX001_3,
    EVENT_VX001_4,
    EVENT_VX001_5,
    EVENT_VX001_6,
    EVENT_VX001_7,
    EVENT_VX001_8,
    EVENT_VX001_9,
    EVENT_AERIAL_1,
    EVENT_AERIAL_2,
    EVENT_AERIAL_3,
    EVENT_AERIAL_4,
    EVENT_AERIAL_5,
    EVENT_AERIAL_6,
    EVENT_V0L7R0N_1,
    EVENT_V0L7R0N_2,
    EVENT_V0L7R0N_3,
    EVENT_V0L7R0N_4,
    // Misc
    EVENT_ENRAGE,
    EVENT_FLAME,
    EVENT_NONE,
    EVENT_CRAWL,
    EVENT_TIMER,
    EVENT_TIMEUP,
    EVENT_OVERRIDE,
    // Leviathan MK II
    EVENT_PROXIMITY_MINE,
    EVENT_NAPALM_SHELL,
    EVENT_PLASMA_BLAST,
    EVENT_SHOCK_BLAST,
    EVENT_FLAME_SUPPRESSANT,
    // VX-001
    EVENT_RAPID_BURST,
    EVENT_LASER_BARRAGE,
    EVENT_LASER_BARRAGE_END,
    EVENT_ROCKET_STRIKE,
    EVENT_HEAT_WAVE,
    EVENT_HAND_PULSE,
    EVENT_FROST_BOMB,
    EVENT_FLAME_SUPPRESSANT_VX001,
    // Aerial Command Unit
    EVENT_PLASMA_BALL,
    EVENT_REACTIVATE_AERIAL,
    EVENT_SUMMON_BOTS,
    // Thrash events
    EVENT_MAGNETIC_FIELD,
    EVENT_SPRAY,
    EVENT_FROST_BOMB_EXPLOSION,
};

enum Phases
{
    PHASE_NULL,
    PHASE_INTRO,
    PHASE_COMBAT,
    PHASE_LEVIATHAN_SOLO,
    PHASE_LEVIATHAN_ASSEMBLED,
    PHASE_VX001_ACTIVATION,
    PHASE_VX001_SOLO,
    PHASE_VX001_ASSEMBLED,
    PHASE_AERIAL_ACTIVATION,
    PHASE_AERIAL_SOLO,
    PHASE_AERIAL_ASSEMBLED,
    PHASE_V0L7R0N_ACTIVATION,
};

enum eActions
{
    DO_START_ENCOUNTER                         = 1,
    DO_ACTIVATE_VX001                          = 2,
    DO_START_VX001                             = 3,
    DO_ACTIVATE_AERIAL                         = 4,
    DO_START_AERIAL                            = 5,
    DO_DISABLE_AERIAL                          = 6,
    DO_ACTIVATE_V0L7R0N                        = 7,
    DO_LEVIATHAN_ASSEMBLED                     = 8,
    DO_VX001_ASSEMBLED                         = 9,
    DO_AERIAL_ASSEMBLED                        = 10,
    DO_ACTIVATE_DEATH_TIMER                    = 11,
    DO_ENTER_ENRAGE                            = 12,
    DO_ACTIVATE_HARD_MODE                      = 13,
    DO_DESPAWN_SUMMONS                         = 14,
};

enum MimironDatas
{
    DATA_GET_HARD_MODE,
};
 
const Position SummonPos[9] =
{
    {2703.93f, 2569.32f, 364.397f, 0},
    {2715.33f, 2569.23f, 364.397f, 0},
    {2726.85f, 2569.28f, 364.397f, 0},
    {2765.24f, 2534.38f, 364.397f, 0},
    {2759.54f, 2544.30f, 364.397f, 0},
    {2753.82f, 2554.22f, 364.397f, 0},
    {2764.95f, 2604.11f, 364.397f, 0},
    {2759.19f, 2594.26f, 364.397f, 0},
    {2753.56f, 2584.30f, 364.397f, 0}
};

enum MimironChests
{
    CACHE_OF_INNOVATION_10                      = 194789,
    CACHE_OF_INNOVATION_HARDMODE_10             = 194957,
    CACHE_OF_INNOVATION_25                      = 194956,
    CACHE_OF_INNOVATION_HARDMODE_25             = 194958,
};

class boss_mimiron : public CreatureScript
{
    public:
        boss_mimiron() : CreatureScript("boss_mimiron") { }

        struct boss_mimironAI : public BossAI
        {
            boss_mimironAI(Creature* creature) : BossAI(creature, DATA_MIMIRON)
            {
                crawl=1;
                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_ROCKET_STRIKE_DMG, true);
                MimironHardMode = false;
                firefighter = false;
                me->SetReactState(REACT_PASSIVE);
                events.SetPhase(PHASE_NULL);
                events.ScheduleEvent(EVENT_CRAWL, 30000, 0, PHASE_NULL);
                timer=0;
            }

            void DespawnCreatures(uint32 entry, float distance, bool discs = false)
            {
                std::list<Creature*> Creatures;
                GetCreatureListWithEntryInGrid(Creatures, me, entry, distance);

                if (Creatures.empty())
                    return;

                for(std::list<Creature*>::iterator iter = Creatures.begin(); iter != Creatures.end(); ++iter)
                    (*iter)->DespawnOrUnsummon();
            }

            void Reset()
            {
                if (me->getFaction() == 35)
                    return;

                _Reset();
                uiBotTimer = 0;
                crawl=1;
                timer=0;
                MimironHardMode = false;
                checkBotAlive = true;
                Enraged = false;
                firefighter = false;
                DespawnCreatures(NPC_MINE, 100);
                DespawnCreatures(NPC_ROCKET, 100);
                DespawnCreatures(NPC_JUNK_BOT, 100);
                DespawnCreatures(NPC_ASSAULT_BOT, 100);
                DespawnCreatures(NPC_BOOM_BOT, 100);
                DespawnCreatures(NPC_EMERGENCY_BOT, 100);
                DespawnCreatures(NPC_FROST_BOMB, 100);

                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                me->SetVisible(true);
                me->ExitVehicle();
                me->GetMotionMaster()->MoveTargetedHome();
                events.SetPhase(PHASE_NULL);
                events.CancelEvent(EVENT_TIMER);
                events.ScheduleEvent(EVENT_CRAWL, 30000, 0, PHASE_NULL);
                instance->SetData(DATA_MIMIRON_ELEVATOR, GO_STATE_ACTIVE);

                if (Creature* aerial = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                    aerial->AI()->DoAction(DO_DESPAWN_SUMMONS);

                for (uint8 data = DATA_LEVIATHAN_MK_II; data <= DATA_AERIAL_UNIT; ++data)
                    if (Creature* creature = me->GetCreature(*me, instance->GetData64(data)))
                        if (creature->IsAlive())
                        {
                            creature->ExitVehicle();
                            creature->AI()->EnterEvadeMode();
                        }

                if (GameObject* go = me->FindNearestGameObject(GO_BIG_RED_BUTTON, 200))
                {
                    go->SetGoState(GO_STATE_READY);
                    go->SetLootState(GO_JUST_DEACTIVATED);
                    go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                }
            }

            void EnterCombat(Unit * /*who*/)
            {
                _EnterCombat();
                instance->SetBossState(DATA_MIMIRON, IN_PROGRESS);
                events.CancelEvent(EVENT_CRAWL);
                events.SetPhase(PHASE_INTRO);
                if (MimironHardMode)
                {
                    events.ScheduleEvent(EVENT_HARD_1, 4000, 0, PHASE_INTRO);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    events.ScheduleEvent(EVENT_TIMEUP, 599000);
                    events.ScheduleEvent(EVENT_ENRAGE, 600000);
                    events.ScheduleEvent(EVENT_FLAME, 30000);
                }
                else
                {
                    TalkToMap(SAY_AGGRO);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    events.ScheduleEvent(EVENT_INTRO_2, 10000, 0, PHASE_INTRO);
                    events.ScheduleEvent(EVENT_ENRAGE, 900000);
                }

                if (GameObject* button = me->FindNearestGameObject(GO_BIG_RED_BUTTON, 200))
                    button->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            }

            void EndEncounter()
            {
                TalkToMap(SAY_V07TRON_DEATH);
                DespawnCreatures(NPC_MINE, 100);
                me->setFaction(35);

                if (instance)
                {
                    instance->SetBossState(DATA_MIMIRON, DONE);
                    if (MimironHardMode)
                    {
                        DespawnCreatures(NPC_FLAME_SPREAD, 100);
                        DespawnCreatures(NPC_FLAME, 100);
                        me->SummonGameObject(RAID_MODE<uint32>(CACHE_OF_INNOVATION_HARDMODE_10, CACHE_OF_INNOVATION_HARDMODE_25), 2744.65f, 2569.46f,364.314f, 3.14159f, 0, 0, 0.7f, 0.7f, 604800);
                    }
                    else
                        me->SummonGameObject(RAID_MODE<uint32>(CACHE_OF_INNOVATION_10, CACHE_OF_INNOVATION_25), 2744.65f, 2569.46f, 364.314f, 3.14159f,0, 0, 0.7f, 0.7f, 604800);
                }

                EnterEvadeMode();
                me->DespawnOrUnsummon(5000);
            }

            uint32 GetData(uint32 type) const
            {
                switch (type)
                {
                    case DATA_GET_HARD_MODE:
                        return MimironHardMode ? 1 : 0;
                    case DATA_FIREFIGHTER:
                        return firefighter ? 1 : 0;
                    default:
                        return 0;
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case DO_ACTIVATE_VX001:
                        events.SetPhase(PHASE_VX001_ACTIVATION);
                        events.ScheduleEvent(EVENT_VX001_1, 200, 0, PHASE_VX001_ACTIVATION);
                        break;
                    case DO_ACTIVATE_AERIAL:
                        events.SetPhase(PHASE_AERIAL_ACTIVATION);
                        events.ScheduleEvent(EVENT_AERIAL_1, 200, 0, PHASE_AERIAL_ACTIVATION);
                        break;
                    case DO_ACTIVATE_V0L7R0N:
                        me->SetVisible(true);
                        events.SetPhase(PHASE_V0L7R0N_ACTIVATION);
                        events.ScheduleEvent(EVENT_V0L7R0N_1, 1000, 0, PHASE_V0L7R0N_ACTIVATION);
                        break;
                    case DO_ACTIVATE_DEATH_TIMER:
                        checkBotAlive = false;
                        break;
                    case DO_ACTIVATE_HARD_MODE:
                        MimironHardMode = true;
                        firefighter = true;
                        DoZoneInCombat();
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (checkBotAlive)
                    uiBotTimer = 0;
                else
                {
                    uiBotTimer += diff;
                    if (uiBotTimer > 10000)
                    {
                        if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                            Leviathan->AI()->DoAction(DO_LEVIATHAN_ASSEMBLED);
                        if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                            VX_001->AI()->DoAction(DO_VX001_ASSEMBLED);
                        if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                            AerialUnit->AI()->DoAction(DO_AERIAL_ASSEMBLED);

                        checkBotAlive = true;
                    }
                    else
                    {
                        if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                            if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                                    if (Leviathan->getStandState() == UNIT_STAND_STATE_DEAD)
                                        if (VX_001->getStandState() == UNIT_STAND_STATE_DEAD)
                                            if (AerialUnit->getStandState() == UNIT_STAND_STATE_DEAD)
                                            {
                                                Leviathan->DisappearAndDie();
                                                VX_001->DisappearAndDie();
                                                AerialUnit->DisappearAndDie();
                                                DespawnCreatures(NPC_ROCKET, 100);
                                                DespawnCreatures(NPC_MKII_TURRET, 100);
                                                me->ExitVehicle();
                                                EndEncounter();
                                                if (MimironHardMode)
                                                {
                                                    events.ScheduleEvent(EVENT_OVERRIDE, 10);
                                                }
                                                checkBotAlive = true;
                                            }
                    }
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CRAWL:
                            switch(crawl)
                            {
                                case 1:
                                    if (Creature* Leviathan = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                    {
                                        me->EnterVehicle(Leviathan, 4);
                                        me->SetFacingToObject(Leviathan);
                                    }
                                    crawl++;
                                    break;
                                case 2:
                                    if (Creature* Leviathan = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                    {
                                        me->ChangeSeat(2);
                                        me->SetFacingToObject(Leviathan);
                                    }
                                    crawl++;
                                    break;
                                case 3:
                                    me->ChangeSeat(3);
                                    if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                        Leviathan->ExitVehicle();
                                    crawl=1;
                                    break;
                            }
                            events.RescheduleEvent(EVENT_CRAWL, 30000, 0, PHASE_NULL);
                            break;
                        case EVENT_HARD_1:
                            if (Creature* computer = me->FindNearestCreature(NPC_COMPUTER,100.0f))
                                computer->AI()->TalkToMap(SAY_10_MIN);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            events.ScheduleEvent(EVENT_HARD_2, 2000, 0, PHASE_INTRO);
                            break;
                        case EVENT_HARD_2:
                            if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                me->EnterVehicle(Leviathan,5);
                            TalkToMap(SAY_HARDMODE_ON);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            events.ScheduleEvent(EVENT_INTRO_3, 10000, 0, PHASE_INTRO);
                            break;
                        case EVENT_INTRO_2:
                            if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                me->EnterVehicle(Leviathan,5);
                            TalkToMap(SAY_MKII_ACTIVATE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            events.ScheduleEvent(EVENT_INTRO_3, 10000, 0, PHASE_INTRO);
                            break;
                        case EVENT_INTRO_3:
                            me->ChangeSeat(6);
                            events.ScheduleEvent(EVENT_INTRO_4, 2000, 0, PHASE_INTRO);
                            break;
                        case EVENT_INTRO_4:
                            if (instance)
                                if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                {
                                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                                    if (MimironHardMode)
                                    {
                                        events.ScheduleEvent(EVENT_TIMER, 60000);
                                        events.ScheduleEvent(EVENT_TIMEUP, 600000);
                                    }
                                    Leviathan->AI()->DoAction(DO_START_ENCOUNTER);
                                    events.SetPhase(PHASE_COMBAT);
                                }
                            break;
                        case EVENT_VX001_1:
                            TalkToMap(SAY_MKII_DEATH);
                            events.ScheduleEvent(EVENT_VX001_2, 10000, 0, PHASE_VX001_ACTIVATION);
                            break;
                        case EVENT_VX001_2:
                            me->ChangeSeat(1);
                            events.ScheduleEvent(EVENT_VX001_3, 2000, 0, PHASE_VX001_ACTIVATION);
                        case EVENT_VX001_3:
                            if (instance)
                            {
                                instance->SetData(DATA_MIMIRON_ELEVATOR, GO_STATE_READY);
                                events.ScheduleEvent(EVENT_VX001_4, 5000, 0, PHASE_VX001_ACTIVATION);
                            }
                            break;
                        case EVENT_VX001_4:
                            if (instance)
                                if (Creature* VX_001 = me->SummonCreature(NPC_VX_001, 2744.65f, 2569.46f, 364.397f, 3.14159f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
                                {
                                    instance->SetData(DATA_MIMIRON_ELEVATOR, GO_STATE_ACTIVE_ALTERNATIVE);
                                    VX_001->SetVisible(true);
                                    for (uint8 n = 5; n < 7; n++)
                                    {
                                        if (Creature* Rocket = VX_001->SummonCreature(NPC_ROCKET, VX_001->GetPositionX(), VX_001->GetPositionY(), VX_001->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                                        {
                                            Rocket->SetReactState(REACT_PASSIVE);
                                            Rocket->EnterVehicle(VX_001, n);
                                        }
                                    }
                                }
                            events.ScheduleEvent(EVENT_VX001_5, 8000, 0, PHASE_VX001_ACTIVATION);
                            events.CancelEvent(EVENT_VX001_4);
                            break;
                        case EVENT_VX001_5:
                            if (instance)
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                    me->EnterVehicle(VX_001, 0);
                            events.ScheduleEvent(EVENT_VX001_6, 3500, 0, PHASE_VX001_ACTIVATION);
                            break;
                        case EVENT_VX001_6:
                            TalkToMap(SAY_VX001_ACTIVATE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            events.ScheduleEvent(EVENT_VX001_7, 10000, 0, PHASE_VX001_ACTIVATION);
                            events.CancelEvent(EVENT_VX001_6);
                            break;
                        case EVENT_VX001_7:
                            me->ChangeSeat(1);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SIT);
                            events.ScheduleEvent(EVENT_VX001_8, 2000, 0, PHASE_VX001_ACTIVATION);
                            break;
                        case EVENT_VX001_8:
                            if (instance)
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                    VX_001->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                            events.ScheduleEvent(EVENT_VX001_9, 3500, 0, PHASE_VX001_ACTIVATION);
                            break;
                        case EVENT_VX001_9:
                            if (instance)
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                {
                                    VX_001->AddAura(SPELL_HOVER, VX_001); // Hover
                                    VX_001->AI()->DoAction(DO_START_VX001);
                                    events.SetPhase(PHASE_COMBAT);
                                }
                            break;
                        case EVENT_AERIAL_1:
                            me->ChangeSeat(4);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                            events.ScheduleEvent(EVENT_AERIAL_2, 2500, 0, PHASE_AERIAL_ACTIVATION);
                            break;
                        case EVENT_AERIAL_2:
                            TalkToMap(SAY_VX001_DEATH);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            events.ScheduleEvent(EVENT_AERIAL_3, 5000, 0, PHASE_AERIAL_ACTIVATION);
                            break;
                        case EVENT_AERIAL_3:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                            if (instance)
                                if (Creature* AerialUnit = me->SummonCreature(NPC_AERIAL_COMMAND_UNIT, 2744.65f, 2569.46f, 380, 3.14159f,  TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
                                    AerialUnit->SetVisible(true);
                            events.ScheduleEvent(EVENT_AERIAL_4, 5000, 0, PHASE_AERIAL_ACTIVATION);
                            break;
                        case EVENT_AERIAL_4:
                            me->ExitVehicle();
                            if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                                 me->EnterVehicle(AerialUnit, 0);
                            events.ScheduleEvent(EVENT_AERIAL_5, 2000, 0, PHASE_AERIAL_ACTIVATION);
                            break;
                        case EVENT_AERIAL_5:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                            TalkToMap(SAY_AERIAL_ACTIVATE);
                            events.ScheduleEvent(EVENT_AERIAL_6, 8000, 0, PHASE_AERIAL_ACTIVATION);
                            break;
                        case EVENT_AERIAL_6:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                            if (instance)
                                if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                                {
                                    AerialUnit->AI()->DoAction(DO_START_AERIAL);
                                    events.SetPhase(PHASE_COMBAT);
                                }
                            break;
                        case EVENT_V0L7R0N_1:
                            if (instance)
                            {
                                if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                    Leviathan->GetMotionMaster()->MovePoint(0, 2744.65f, 2569.46f, 364.397f);
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                {
                                    me->EnterVehicle(VX_001, 1);
                                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                                    TalkToMap(SAY_AERIAL_DEATH);
                                }
                                events.ScheduleEvent(EVENT_V0L7R0N_2, 5000, 0, PHASE_V0L7R0N_ACTIVATION);
                            }
                            break;
                        case EVENT_V0L7R0N_2:
                            if (instance)
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                    if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                    {
                                        VX_001->SetStandState(UNIT_STAND_STATE_STAND);
                                        VX_001->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CUSTOM_SPELL_01);
                                        VX_001->EnterVehicle(Leviathan, 7);
                                    }
                            events.ScheduleEvent(EVENT_V0L7R0N_3, 2000, 0, PHASE_V0L7R0N_ACTIVATION);
                            break;
                        case EVENT_V0L7R0N_3:
                            if (instance)
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                    if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                                    {
                                        AerialUnit->CanFly();
                                        AerialUnit->SetDisableGravity(false);
                                        AerialUnit->EnterVehicle(VX_001, 3);
                                        TalkToMap(SAY_V07TRON_ACTIVATE);
                                    }
                            events.ScheduleEvent(EVENT_V0L7R0N_4, 10000, 0, PHASE_V0L7R0N_ACTIVATION);
                            break;
                        case EVENT_V0L7R0N_4:
                            if (instance)
                            {
                                if (Creature* Leviathan = me->GetCreature(*me, instance->GetData64(DATA_LEVIATHAN_MK_II)))
                                    Leviathan->AI()->DoAction(DO_LEVIATHAN_ASSEMBLED);
                                if (Creature* VX_001 = me->GetCreature(*me, instance->GetData64(DATA_VX_001)))
                                    VX_001->AI()->DoAction(DO_VX001_ASSEMBLED);
                                if (Creature* AerialUnit = me->GetCreature(*me, instance->GetData64(DATA_AERIAL_UNIT)))
                                    AerialUnit->AI()->DoAction(DO_AERIAL_ASSEMBLED);
                                events.SetPhase(PHASE_COMBAT);
                            }
                            break;
                        case EVENT_ENRAGE:
                            TalkToMap(SAY_BERSERK);
                            for (uint8 data = DATA_LEVIATHAN_MK_II; data <= DATA_AERIAL_UNIT; ++data)
                                 if (Creature* creature = me->GetCreature(*me, instance->GetData64(data)))
                                     creature->AI()->DoAction(DO_ENTER_ENRAGE);
                            Enraged = true;
                            if (MimironHardMode)
                            {
                                DoCast(me, SPELL_SELF_DESTRUCTION, true);
                                DoCast(me, SPELL_SELF_DESTRUCTION_VISUAL, true);
                                events.ScheduleEvent(EVENT_TIMEUP, 1);
                            }
                            break;
                        case EVENT_FLAME:
                            if (MimironHardMode)
                            {
                               for (uint8 i = 0; i < 3; ++i)
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                        DoCast(target, SPELL_SUMMON_FLAMES_INITIAL, true);
                               events.ScheduleEvent(EVENT_FLAME, 30000);
                            }
                            break;
                        case EVENT_TIMER:
                            if (Creature* computer = me->FindNearestCreature(NPC_COMPUTER,100.0f))
                            {
                                timer++;
                                switch(timer)
                                {
                                    case 1:
                                        computer->AI()->TalkToMap(SAY_9_MIN);
                                        break;
                                    case 2:
                                        computer->AI()->TalkToMap(SAY_8_MIN);
                                        break;
                                    case 3:
                                        computer->AI()->TalkToMap(SAY_7_MIN);
                                        break;
                                    case 4:
                                        computer->AI()->TalkToMap(SAY_6_MIN);
                                        break;
                                    case 5:
                                        computer->AI()->TalkToMap(SAY_5_MIN);
                                        break;
                                    case 6:
                                        computer->AI()->TalkToMap(SAY_4_MIN);
                                        break;
                                    case 7:
                                        computer->AI()->TalkToMap(SAY_3_MIN);
                                        break;
                                    case 8:
                                        computer->AI()->TalkToMap(SAY_2_MIN);
                                        break;
                                    case 9:
                                        computer->AI()->TalkToMap(SAY_1_MIN);
                                        break;
                                    default:
                                        break;
                                }
                                events.RescheduleEvent(EVENT_TIMER, 60000);
                            }
                            break;
                        case EVENT_TIMEUP:
                            if (Creature* computer = me->FindNearestCreature(NPC_COMPUTER,100.0f))
                                computer->AI()->TalkToMap(SAY_DESTROY_MIN);
                            break;
                        case EVENT_OVERRIDE:
                            if (Creature* computer = me->FindNearestCreature(NPC_COMPUTER,100.0f))
                                computer->AI()->TalkToMap(SAY_OVERRIDE_MIN);
                            break;
                    }
                }
            }

        private:
            uint32 EnrageTimer;
            uint32 FlameTimer;
            uint32 uiBotTimer;
            uint8 crawl;
            uint8 timer;
            bool checkBotAlive;
            bool Enraged;
            bool MimironHardMode;
            bool firefighter;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<boss_mimironAI>(creature);
        }
};

class boss_leviathan_mk : public CreatureScript
{
    public:
        boss_leviathan_mk() : CreatureScript("boss_leviathan_mk") { }

        struct boss_leviathan_mkAI : public BossAI 
        {
            boss_leviathan_mkAI(Creature* creature) : BossAI(creature, DATA_LEVIATHAN_MK_II), phase(PHASE_NULL), vehicle(creature->GetVehicleKit())
            {
                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_ROCKET_STRIKE_DMG, true);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                ASSERT(vehicle);
            }

            void Reset()
            {
                events.Reset();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetReactState(REACT_PASSIVE);
                me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                phase = PHASE_NULL;
                events.SetPhase(PHASE_NULL);
                if (Creature *turret = CAST_CRE(me->GetVehicleKit()->GetPassenger(3)))
                {
                    turret->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    turret->SetReactState(REACT_PASSIVE);
                }
            }

            void KilledUnit(Unit* /*who*/)
            {
                if (Creature* mimiron = me->FindNearestCreature(NPC_MIMIRON,100.0f))
                {
                    if (phase == PHASE_LEVIATHAN_SOLO)
                        mimiron->AI()->TalkToMap(SAY_MKII_SLAY);
                    else
                        mimiron->AI()->TalkToMap(SAY_V07TRON_SLAY);
                }
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (phase == PHASE_NULL)
                    damage = 0;

                if (phase == PHASE_LEVIATHAN_SOLO)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        events.SetPhase(PHASE_NULL);
                        phase = PHASE_NULL;
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_VX001);
                        if (Creature* turret = CAST_CRE(me->GetVehicleKit()->GetPassenger(3)))
                            turret->Kill(turret, false);
                        me->SetSpeed(MOVE_RUN, 1.5f, true);
                        me->GetMotionMaster()->MovePoint(0, 2790.11f, 2595.83f, 364.32f);
                    }

                if (phase == PHASE_LEVIATHAN_ASSEMBLED)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        me->SetStandState(UNIT_STAND_STATE_DEAD);
                        events.SetPhase(PHASE_NULL);
                        phase = PHASE_NULL;
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_DEATH_TIMER);
                    }
            }

            void EnterCombat(Unit* who)
            {
                if (Creature* Mimiron = me->GetCreature(*me, instance ? instance->GetData64(DATA_MIMIRON) : 0))
                    MimironHardMode = Mimiron->AI()->GetData(DATA_GET_HARD_MODE);

                if (MimironHardMode)
                {
                    DoCast(me, SPELL_EMERGENCY_MODE);
                    events.ScheduleEvent(EVENT_FLAME_SUPPRESSANT, 60000, 0, PHASE_LEVIATHAN_SOLO);
                }

                if (Creature* turret = CAST_CRE(me->GetVehicleKit()->GetPassenger(3)))
                {
                    turret->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    turret->SetReactState(REACT_AGGRESSIVE);
                    turret->AI()->DoZoneInCombat();
                }

                events.ScheduleEvent(EVENT_PROXIMITY_MINE, 1000);
                events.ScheduleEvent(EVENT_PLASMA_BLAST, 10000, 0, PHASE_LEVIATHAN_SOLO);
            }

            void DoAction(int32 action)
            {
                switch(action)
                {
                    case DO_START_ENCOUNTER:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        phase = PHASE_LEVIATHAN_SOLO;
                        events.SetPhase(PHASE_LEVIATHAN_SOLO);
                        DoZoneInCombat();
                        break;
                    case DO_LEVIATHAN_ASSEMBLED:
                        if (MimironHardMode)
                            DoCast(me, SPELL_EMERGENCY_MODE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetHealth(int32(me->GetMaxHealth() / 2));
                        me->SetSpeed(MOVE_RUN, 1.0f, true);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        phase = PHASE_LEVIATHAN_ASSEMBLED;
                        events.SetPhase(PHASE_LEVIATHAN_ASSEMBLED);
                        events.RescheduleEvent(EVENT_PROXIMITY_MINE, 1000);
                        events.RescheduleEvent(EVENT_SHOCK_BLAST, 30000);
                        break;
                    case DO_ENTER_ENRAGE:
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (phase == PHASE_LEVIATHAN_SOLO || phase == PHASE_LEVIATHAN_ASSEMBLED)
                {
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch(eventId)
                        {
                            case EVENT_PROXIMITY_MINE:
                                for (int i = 0; i < 10; i++)
                                    DoCast(SPELL_MINES_SPAWN);
                                DoCast(SPELL_PROXIMITY_MINES);
                                events.RescheduleEvent(EVENT_PROXIMITY_MINE, 35000);
                                break;
                            case EVENT_PLASMA_BLAST:
                                TalkToMap(EMOTE_PLASMA_BLAST);
                                DoCast(SPELL_PLASMA_BLAST);
                                events.RescheduleEvent(EVENT_PLASMA_BLAST, urand(30000, 35000), 0, PHASE_LEVIATHAN_SOLO);
                                events.RescheduleEvent(EVENT_SHOCK_BLAST, urand(6000, 10000));
                                break;
                            case EVENT_SHOCK_BLAST:
                                DoCastAOE(SPELL_SHOCK_BLAST);
                                events.RescheduleEvent(EVENT_SHOCK_BLAST, 35000);
                                break;
                            case EVENT_FLAME_SUPPRESSANT:
                                DoCastAOE(SPELL_FLAME_SUPPRESSANT);
                                events.CancelEvent(EVENT_FLAME_SUPPRESSANT);
                                break;
                        }
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            Phases phase;
            Vehicle* vehicle;
            EventMap events;
            bool MimironHardMode;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<boss_leviathan_mkAI>(creature);
        }
};

class boss_leviathan_mk_turret : public CreatureScript
{
    public:
        boss_leviathan_mk_turret() : CreatureScript("boss_leviathan_mk_turret") { }

        struct boss_leviathan_mk_turretAI : public ScriptedAI
        {
            boss_leviathan_mk_turretAI(Creature* creature) : ScriptedAI(creature) 
            {
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_NAPALM_SHELL, urand(4000, 8000));
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
            
            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetReactState(REACT_PASSIVE);
            }

            Unit* GetNapalmShellTarget()
            {
                Map* map = me->GetMap();
                if (map && map->IsDungeon())
                {
                    std::list<Player*> playerList;
                    Map::PlayerList const& Players = map->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = Players.begin(); itr != Players.end(); ++itr)
                    {
                        if (Player* player = itr->GetSource())
                        {
                            if (player->isDead() || player->IsGameMaster())
                                continue;

                            float Distance = player->GetDistance(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            if (Distance < 15.0f || Distance > 100.0f)
                                continue;

                            playerList.push_back(player);
                        }
                    }

                    if (playerList.empty())
                        return NULL;

                    return Trinity::Containers::SelectRandomContainerElement(playerList);
                }
                else
                    return NULL;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_NAPALM_SHELL:
                            Unit* shellTarget = GetNapalmShellTarget();
                            if (!shellTarget)
                                shellTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true);
                            if (shellTarget)
                                DoCast(shellTarget, SPELL_NAPALM_SHELL);
                            events.RescheduleEvent(EVENT_NAPALM_SHELL, urand(8000, 12000));
                            break;
                    }
                }
            }

        private:
            uint32 uiNapalmShell;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<boss_leviathan_mk_turretAI>(creature);
        }
};

class npc_proximity_mine : public CreatureScript
{
    public:
        npc_proximity_mine() : CreatureScript("npc_proximity_mine") { }

        struct npc_proximity_mineAI : public ScriptedAI
        {
            npc_proximity_mineAI(Creature* creature) : ScriptedAI(creature)
            {
               SetCombatMovement(false);
               me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
               uiBoomTimer = 35000;
               Boom = false;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!Boom && me->IsWithinDistInMap(who, 0.5f) && who->ToPlayer() && !who->ToPlayer()->IsGameMaster())
                {
                    DoCastAOE(SPELL_EXPLOSION);
                    me->DespawnOrUnsummon(1000);
                    Boom = true;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (uiBoomTimer <= diff)
                {
                    if (!Boom)
                    {
                        DoCastAOE(SPELL_EXPLOSION);
                        me->DespawnOrUnsummon(1000);
                        Boom = true;
                    }
                }
                else uiBoomTimer -= diff;
            }

        private:
            uint32 uiBoomTimer;
            bool Boom;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_proximity_mineAI>(creature);
        }
};

class boss_vx_001 : public CreatureScript
{
    public:
        boss_vx_001() : CreatureScript("boss_vx_001") { }

        struct boss_vx_001AI : public BossAI
        {
            boss_vx_001AI(Creature* creature) : BossAI(creature, DATA_MIMIRON), phase(PHASE_NULL)
            {
                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_ROCKET_STRIKE_DMG, true);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void Reset()
            {
                spinning = false;
                direction = false;
                spinTimer = 250;

                events.Reset();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_PASSIVE);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                me->SetVisible(false);
                me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                phase = PHASE_NULL;
                events.SetPhase(PHASE_NULL);

                // TODO: remove when Spinning Up is fixed properly
                me->ApplySpellImmune(0, IMMUNITY_ID, 48181, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 59161, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 59163, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 59164, true);
            }

            void KilledUnit(Unit * /*who*/)
            {
                if (Creature* mimiron = me->FindNearestCreature(NPC_MIMIRON,100.0f))
                {
                    if (phase == PHASE_VX001_SOLO)
                        mimiron->AI()->TalkToMap(SAY_VX001_SLAY);
                    else
                        mimiron->AI()->TalkToMap(SAY_V07TRON_SLAY);
                }
            }

            void EnterCombat(Unit * /*who*/)
            {
                if (Creature* Mimiron = me->GetCreature(*me, instance ? instance->GetData64(DATA_MIMIRON) : 0))
                    MimironHardMode = Mimiron->AI()->GetData(DATA_GET_HARD_MODE);

                if (MimironHardMode)
                {
                    DoCast(me, SPELL_EMERGENCY_MODE);
                    events.ScheduleEvent(EVENT_FROST_BOMB, 15000);
                    events.ScheduleEvent(EVENT_FLAME_SUPPRESSANT_VX001, 1000);
                }

                events.ScheduleEvent(EVENT_RAPID_BURST, 2500, 0, PHASE_VX001_SOLO);
                events.ScheduleEvent(EVENT_LASER_BARRAGE, urand(35000, 40000));
                events.ScheduleEvent(EVENT_ROCKET_STRIKE, 20000);
                events.ScheduleEvent(EVENT_HEAT_WAVE, urand(8000, 10000), 0, PHASE_VX001_SOLO);
                events.ScheduleEvent(EVENT_HAND_PULSE, 10000, 0, PHASE_VX001_ASSEMBLED);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case DO_START_VX001:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        phase = PHASE_VX001_SOLO;
                        events.SetPhase(PHASE_VX001_SOLO);
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoZoneInCombat();
                        break;
                    case DO_VX001_ASSEMBLED:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->SetHealth(int32(me->GetMaxHealth() / 2));
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        phase = PHASE_VX001_ASSEMBLED;
                        events.SetPhase(PHASE_VX001_ASSEMBLED);
                        events.RescheduleEvent(EVENT_LASER_BARRAGE, urand(35000, 40000));
                        events.RescheduleEvent(EVENT_ROCKET_STRIKE, 20000);
                        events.RescheduleEvent(EVENT_HAND_PULSE, 15000, 0, PHASE_VX001_ASSEMBLED);
                        if (MimironHardMode)
                        {
                            DoCast(me, SPELL_EMERGENCY_MODE);
                            events.RescheduleEvent(EVENT_FROST_BOMB, 15000);
                        }
                        break;
                    case DO_ENTER_ENRAGE:
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                }
            }

            void DamageTaken(Unit * /*who*/, uint32 &damage)
            {
                if (phase == PHASE_NULL)
                    damage = 0;

                if (phase == PHASE_VX001_SOLO)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        spinning = false;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->AttackStop();
                        me->GetMotionMaster()->Initialize();
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        me->SetStandState(UNIT_STAND_STATE_DEAD);
                        phase = PHASE_NULL;
                        events.SetPhase(PHASE_NULL);
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_AERIAL);
                    }

                if (phase == PHASE_VX001_ASSEMBLED)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        spinning = false;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->AttackStop();
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        me->SetStandState(UNIT_STAND_STATE_DEAD);
                        events.SetPhase(PHASE_NULL);
                        phase = PHASE_NULL;
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_DEATH_TIMER);
                    }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (spinning)
                {
                    if (spinTimer <= diff)
                    {
                        if (Creature* leviathan = me->GetVehicleCreatureBase())
                        {
                            float orient = leviathan->GetOrientation();
                            leviathan->SetFacingTo(orient + (direction ? M_PI/60 : -M_PI/60));
                            me->SetOrientation(orient + (direction ? M_PI/60 : -M_PI/60));
                        }
                        else
                        {
                            float orient = me->GetOrientation();
                            me->SetFacingTo(orient + (direction ? M_PI/60 : -M_PI/60));
                            float x, y, z;
                            z = me->GetPositionZ();
                            me->GetNearPoint2D(x, y, 10.0f, me->GetOrientation());
                            if (Creature* temp = me->SummonCreature(NPC_BURST_TARGET, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 250))
                                me->SetTarget(temp->GetGUID());
                        }
                        spinTimer = 250;
                    }
                    else spinTimer -= diff;
                }

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (phase == PHASE_VX001_SOLO || phase == PHASE_VX001_ASSEMBLED)
                {
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_RAPID_BURST:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                    if (Creature* BurstTarget = me->SummonCreature(NPC_BURST_TARGET, *target, TEMPSUMMON_TIMED_DESPAWN, 3100))
                                        DoCast(BurstTarget, SPELL_RAPID_BURST);
                                events.RescheduleEvent(EVENT_RAPID_BURST, 5000, 0, PHASE_VX001_SOLO);
                                break;
                            case EVENT_LASER_BARRAGE:
                                me->SetReactState(REACT_PASSIVE);
                                if (Creature* leviathan = me->GetVehicleCreatureBase())
                                {
                                    float orient = float(2*M_PI * rand_norm());
                                    leviathan->CastSpell(leviathan, 14821, true);
                                    leviathan->SetFacingTo(orient);
                                    leviathan->SetOrientation(orient);
                                    me->SetOrientation(orient);
                                }
                                direction = urand(0, 1);
                                spinning = true;
                                DoCast(SPELL_SPINNING_UP);
                                events.DelayEvents(14500);
                                events.RescheduleEvent(EVENT_LASER_BARRAGE, 40000);
                                events.RescheduleEvent(EVENT_LASER_BARRAGE_END, 14000);
                                break;
                            case EVENT_LASER_BARRAGE_END:
                                me->SetReactState(REACT_AGGRESSIVE);
                                if (me->GetVictim())
                                    AttackStart(me->GetVictim());
                                spinning = false;
                                break;
                            case EVENT_ROCKET_STRIKE:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                    if (Creature* missile = CAST_CRE(me->GetVehicleKit()->GetPassenger(5)))
                                        missile->CastSpell(target, SPELL_ROCKET_STRIKE, true);
                                if (phase == PHASE_VX001_ASSEMBLED)
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                        if (Creature* missile = CAST_CRE(me->GetVehicleKit()->GetPassenger(6)))
                                            missile->CastSpell(target, SPELL_ROCKET_STRIKE, true);
                                events.RescheduleEvent(EVENT_ROCKET_STRIKE, urand(20000, 25000));
                                break;
                            case EVENT_HEAT_WAVE:
                                DoCastAOE(SPELL_HEAT_WAVE);
                                events.RescheduleEvent(EVENT_HEAT_WAVE, 10000, 0, PHASE_VX001_SOLO);
                                break;
                            case EVENT_HAND_PULSE:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                    DoCast(target, SPELL_HAND_PULSE);
                                events.RescheduleEvent(EVENT_HAND_PULSE, urand(4000, 5000));
                                break;
                            case EVENT_FROST_BOMB:
                                {
                                std::list<Creature*> _flames;
                                me->GetCreatureListWithEntryInGrid(_flames, NPC_FLAME_SPREAD, 150.0f);
                                if (!_flames.empty())
                                {
                                    if (Creature* flame = Trinity::Containers::SelectRandomContainerElement(_flames))
                                        me->SummonCreature(NPC_FROST_BOMB, *flame, TEMPSUMMON_TIMED_DESPAWN, 11000);
                                }
                                else
                                    me->SummonCreature(NPC_FROST_BOMB, SummonPos[rand()%9], TEMPSUMMON_TIMED_DESPAWN, 11000);
                                events.RescheduleEvent(EVENT_FROST_BOMB, 45000);
                                break;
                                }
                            case EVENT_FLAME_SUPPRESSANT_VX001:
                                DoCastAOE(SPELL_FLAME_SUPPRESSANT_VX001);
                                events.RescheduleEvent(EVENT_FLAME_SUPPRESSANT_VX001, 10000);
                                break;
                        }
                    }
                }
            }

        private:
            Phases phase;
            EventMap events;
            bool spinning;
            bool direction;
            bool MimironHardMode;
            uint32 spinTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<boss_vx_001AI>(creature);
        }
};

class npc_rocket_strike : public CreatureScript
{
    public:
        npc_rocket_strike() : CreatureScript("npc_rocket_strike") { }

        struct npc_rocket_strikeAI : public ScriptedAI
        {
            npc_rocket_strikeAI(Creature* creature) : ScriptedAI(creature)
            {
                SetCombatMovement(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                me->DespawnOrUnsummon(10000);
                DoCast(me, SPELL_ROCKET_STRIKE_AURA);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_rocket_strikeAI>(creature);
        }
};

class boss_aerial_unit : public CreatureScript
{
    public:
        boss_aerial_unit() : CreatureScript("boss_aerial_unit") { }

        struct boss_aerial_unitAI : public BossAI
        {
            boss_aerial_unitAI(Creature* creature) : BossAI(creature, DATA_MIMIRON), phase(PHASE_NULL)
            {
                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_ROCKET_STRIKE_DMG, true);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void Reset()
            {
                events.Reset();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_PASSIVE);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetVisible(false);
                me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                me->SetDisableGravity(true);
                me->CanFly();
                phase = PHASE_NULL;
                events.SetPhase(PHASE_NULL);
                summons.DespawnAll();
                spawnedAdds = 0;
            }

            void KilledUnit(Unit * /*who*/)
            {
                if (Creature* mimiron = me->FindNearestCreature(NPC_MIMIRON,100.0f))
                {
                    if (phase == PHASE_AERIAL_SOLO)
                        mimiron->AI()->TalkToMap(SAY_AERIAL_SLAY);
                    else
                        mimiron->AI()->TalkToMap(SAY_V07TRON_SLAY);
                }
            }

            void EnterCombat(Unit * /*who*/)
            {
                if (Creature* Mimiron = me->GetCreature(*me, instance ? instance->GetData64(DATA_MIMIRON) : 0))
                    MimironHardMode = Mimiron->AI()->GetData(DATA_GET_HARD_MODE);

                if (MimironHardMode)
                    DoCast(me, SPELL_EMERGENCY_MODE);

                events.ScheduleEvent(EVENT_PLASMA_BALL, 1000);
                events.ScheduleEvent(EVENT_SUMMON_BOTS, 10000, 0, PHASE_AERIAL_SOLO);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case DO_START_AERIAL:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        phase = PHASE_AERIAL_SOLO;
                        events.SetPhase(PHASE_AERIAL_SOLO);
                        DoZoneInCombat();
                        break;
                    case DO_DISABLE_AERIAL:
                        if (phase != PHASE_AERIAL_SOLO)
                            return;
                        me->CastStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->GetMotionMaster()->Clear(true);
                        DoCast(me, SPELL_MAGNETIC_CORE);
                        DoCast(me, SPELL_MAGNETIC_CORE_VISUAL);
                        if (Creature* MagneticCore = me->GetCreature(*me, instance->GetData64(DATA_MAGNETIC_CORE)))
                            if (MagneticCore->IsAlive())
                                me->NearTeleportTo(MagneticCore->GetPositionX(), MagneticCore->GetPositionY(), 368.965f, 0, false);
                        events.RescheduleEvent(EVENT_PLASMA_BALL, 22000, 0, PHASE_AERIAL_SOLO);
                        events.RescheduleEvent(EVENT_SUMMON_BOTS, 24000, 0, PHASE_AERIAL_SOLO);
                        events.ScheduleEvent(EVENT_REACTIVATE_AERIAL, 20000, 0, PHASE_AERIAL_SOLO);
                        break;
                    case DO_AERIAL_ASSEMBLED:
                        if (MimironHardMode)
                            DoCast(me, SPELL_EMERGENCY_MODE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetHealth(int32(me->GetMaxHealth() / 2));
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        phase = PHASE_AERIAL_ASSEMBLED;
                        events.SetPhase(PHASE_AERIAL_ASSEMBLED);
                        events.RescheduleEvent(EVENT_PLASMA_BALL, 2000);
                        break;
                    case DO_DESPAWN_SUMMONS:
                        summons.DespawnAll();
                        break;
                    case DO_ENTER_ENRAGE:
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (phase == PHASE_AERIAL_SOLO || phase == PHASE_AERIAL_ASSEMBLED)
                {
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_PLASMA_BALL:
                                if (phase == PHASE_AERIAL_SOLO && me->GetVictim())
                                {
                                    float x = me->GetVictim()->GetPositionX();
                                    float y = me->GetVictim()->GetPositionY();
                                    float z = me->GetVictim()->GetPositionZ();
                                    if (me->IsWithinDist3d(x, y, z, 30))
                                    {
                                        me->GetMotionMaster()->Initialize();
                                        DoCastVictim(SPELL_PLASMA_BALL);
                                    }
                                    else me->GetMotionMaster()->MovePoint(0, x, y, 380.04f);
                                }
                                else if (phase == PHASE_AERIAL_ASSEMBLED && me->GetVictim())
                                {
                                    if (me->GetVictim()->IsWithinDist3d(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 30))
                                        DoCastVictim(SPELL_PLASMA_BALL);
                                    else if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0))
                                        DoCast(target, SPELL_PLASMA_BALL);
                                }
                                events.RescheduleEvent(EVENT_PLASMA_BALL, 2000);
                                break;
                            case EVENT_REACTIVATE_AERIAL:
                                me->RemoveAurasDueToSpell(SPELL_MAGNETIC_CORE_VISUAL);
                                me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), 380.04f, 3.14159f, false);
                                me->SetReactState(REACT_AGGRESSIVE);
                                events.CancelEvent(EVENT_REACTIVATE_AERIAL);
                                break;
                            case EVENT_SUMMON_BOTS:
                                if (phase == PHASE_AERIAL_SOLO)
                                {
                                    spawnAdd();
                                    events.RescheduleEvent(EVENT_SUMMON_BOTS, 10000, 0, PHASE_AERIAL_SOLO);
                                }
                                break;
                        }
                    }
                }
            }

            void spawnAdd()
            {
                switch (spawnedAdds)
                {
                    case 0:
                        for (uint8 n = 0; n < 2; n++)
                            me->SummonCreature(NPC_JUNK_BOT, SummonPos[rand()%9], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                        break;
                    case 1:
                        me->SummonCreature(NPC_ASSAULT_BOT, SummonPos[rand()%9], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                        if (MimironHardMode)
                            for (uint8 i = 0; i < 2; ++i)
                                me->SummonCreature(NPC_EMERGENCY_BOT, SummonPos[rand()%9], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                        break;
                    case 2:
                        me->SummonCreature(NPC_BOOM_BOT, 2744.65f, 2569.46f, 364.397f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                        break;
                }

                spawnedAdds++;
                if (spawnedAdds > 2)
                    spawnedAdds = 0;
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);

                if (summon->GetEntry() == NPC_EMERGENCY_BOT)
                    return;

                summon->AI()->DoZoneInCombat();
                if (MimironHardMode)
                    summon->CastSpell(summon, SPELL_EMERGENCY_MODE, true);
            }

            void DamageTaken(Unit * /*who*/, uint32 &damage)
            {
                if (phase == PHASE_NULL)
                    damage = 0;

                if (phase == PHASE_AERIAL_SOLO)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        me->GetMotionMaster()->Clear(true);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        events.CancelEvent(EVENT_SUMMON_BOTS);
                        phase = PHASE_NULL;
                        events.SetPhase(PHASE_NULL);
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_V0L7R0N);
                    }

                if (phase == PHASE_AERIAL_ASSEMBLED)
                    if (damage >= me->GetHealth())
                    {
                        damage = 0;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);
                        me->SetHealth(me->GetMaxHealth());
                        me->SetStandState(UNIT_STAND_STATE_DEAD);
                        events.SetPhase(PHASE_NULL);
                        phase = PHASE_NULL;
                        if (Creature* Mimiron = me->GetCreature(*me, instance->GetData64(DATA_MIMIRON)))
                            Mimiron->AI()->DoAction(DO_ACTIVATE_DEATH_TIMER);
                    }
            }

        private:
            Phases phase;
            EventMap events;
            uint8 spawnedAdds;
            bool MimironHardMode;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<boss_aerial_unitAI>(creature);
        }
};

class npc_magnetic_core : public CreatureScript
{
    public:
        npc_magnetic_core() : CreatureScript("npc_magnetic_core") { }

        struct npc_magnetic_coreAI : public ScriptedAI
        {
            npc_magnetic_coreAI(Creature* creature) : ScriptedAI(creature)
            {
                SetCombatMovement(false);
                DoCast(SPELL_MAGNETIC_CORE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                me->DespawnOrUnsummon(21000);
                if (Creature* AerialUnit = me->FindNearestCreature(NPC_AERIAL_COMMAND_UNIT, 20, true))
                    AerialUnit->AI()->DoAction(DO_DISABLE_AERIAL);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_magnetic_coreAI>(creature);
        }
};

class npc_assault_bot : public CreatureScript
{
    public:
        npc_assault_bot() : CreatureScript("npc_assault_bot") { }

        struct npc_assault_botAI : public ScriptedAI
        {
            npc_assault_botAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            void Reset()
            {
                events.ScheduleEvent(EVENT_MAGNETIC_FIELD, urand(4000, 6000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MAGNETIC_FIELD:
                            DoCastVictim(SPELL_MAGNETIC_FIELD);
                            events.RescheduleEvent(EVENT_MAGNETIC_FIELD, urand(15000, 20000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_ROCKET_STRIKE_DMG && instance)
                    instance->DoCastSpellOnPlayers(SPELL_NOT_SO_FRIENDLY_FIRE_CREDIT);
            }

        private:
            InstanceScript* instance;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_assault_botAI>(creature);
        }
};

class npc_emergency_bot : public CreatureScript
{
    public:
        npc_emergency_bot() : CreatureScript("npc_emergency_bot") { }

        struct npc_emergency_botAI : public ScriptedAI
        {
            npc_emergency_botAI(Creature* creature) : ScriptedAI(creature)
            {
                me->setFaction(14);
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MoveRandom(15);
                events.ScheduleEvent(EVENT_SPRAY, 5000);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SPRAY:
                            DoCast(SPELL_WATER_SPRAY);
                            events.RescheduleEvent(EVENT_SPRAY, 10000);
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_emergency_botAI>(creature);
        }
};

class npc_mimiron_bomb_bot : public CreatureScript
{
    public:
        npc_mimiron_bomb_bot() : CreatureScript("npc_mimiron_bomb_bot") { }

        struct npc_mimiron_bomb_botAI : public ScriptedAI
        {
            npc_mimiron_bomb_botAI(Creature* creature) : ScriptedAI(creature) { }

            Unit* SelectPlayerTargetInRange(float range)
            {
                Player* target = NULL;
                Trinity::AnyPlayerInObjectRangeCheck u_check(me, range);
                Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, target, u_check);
                me->VisitNearbyObject(range, searcher);
                return target;
            }

            void Reset()
            {
                despawn = false;
                if (Unit* target = SelectPlayerTargetInRange(500.0f))
                {
                    me->AddThreat(target, 999999.0f);
                    AttackStart(target);
                }
            }

            void JustDied(Unit * /*killer*/)
            {
                DoCast(me, SPELL_BOMB_BOT, true);
            }

            void UpdateAI(uint32 /*diff*/)
            {
                if (!UpdateVictim())
                    return;

                if (!despawn && me->IsWithinMeleeRange(me->GetVictim()))
                {
                    despawn = true;
                    DoCast(me, SPELL_BOMB_BOT, true);
                    me->DespawnOrUnsummon(500);
                }
            }

        private:
            bool despawn;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_mimiron_bomb_botAI>(creature);
        }
};

class npc_frost_bomb : public CreatureScript
{
    public:
        npc_frost_bomb() : CreatureScript("npc_frost_bomb") { }

        struct npc_frost_bombAI : public ScriptedAI
        {
            npc_frost_bombAI(Creature* creature) : ScriptedAI(creature)
            {
                SetCombatMovement(false);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                DoCast(me, SPELL_FROST_BOMB, true);
                events.ScheduleEvent(EVENT_FROST_BOMB_EXPLOSION, 10000);
            }
            
            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FROST_BOMB_EXPLOSION:
                            DoCast(me, RAID_MODE(SPELL_FROST_BOMB_EXPLOSION_10, SPELL_FROST_BOMB_EXPLOSION_25), true);
                            events.RescheduleEvent(EVENT_FROST_BOMB_EXPLOSION, 10000);
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_frost_bombAI>(creature);
        }
};

class npc_mimiron_flame_trigger : public CreatureScript
{
    public:
        npc_mimiron_flame_trigger() : CreatureScript("npc_mimiron_flame_trigger") { }

        struct npc_mimiron_flame_triggerAI : public ScriptedAI
        {
            npc_mimiron_flame_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                me->SetInCombatWithZone();
                events.ScheduleEvent(EVENT_FLAME, 2000);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                switch (spell->Id)
                {
                    case SPELL_FLAME_SUPPRESSANT:
                    case SPELL_FLAME_SUPPRESSANT_VX001:
                    case SPELL_FROST_BOMB_EXPLOSION_10:
                    case SPELL_FROST_BOMB_EXPLOSION_25:
                    case SPELL_WATER_SPRAY:
                        events.ScheduleEvent(EVENT_FLAME, 1000);
                        me->DespawnOrUnsummon(500);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FLAME:
                            me->SummonCreature(NPC_FLAME_SPREAD, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            events.RescheduleEvent(EVENT_FLAME, 4000);
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_mimiron_flame_triggerAI>(creature);
        }
};

class npc_mimiron_flame_spread : public CreatureScript
{
    public:
        npc_mimiron_flame_spread() : CreatureScript("npc_mimiron_flame_spread") { }

        struct npc_mimiron_flame_spreadAI : public ScriptedAI
        {
            npc_mimiron_flame_spreadAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED | UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_PASSIVE);
                DoCast(me, SPELL_FLAME, true);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                switch (spell->Id)
                {
                    case SPELL_FLAME_SUPPRESSANT:
                    case SPELL_FLAME_SUPPRESSANT_VX001:
                    case SPELL_FROST_BOMB_EXPLOSION_10:
                    case SPELL_FROST_BOMB_EXPLOSION_25:
                    case SPELL_WATER_SPRAY:
                        me->DespawnOrUnsummon(500);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (instance && instance->GetBossState(DATA_MIMIRON) != IN_PROGRESS)
                    me->DespawnOrUnsummon();
            }

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetUlduarAI<npc_mimiron_flame_spreadAI>(creature);
        }
};

class spell_ulduar_proximity_mines : public SpellScriptLoader
{
    public:
        spell_ulduar_proximity_mines() : SpellScriptLoader("spell_ulduar_proximity_mines") { }

        class spell_ulduar_proximity_minesSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ulduar_proximity_minesSpellScript)

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                for (uint8 i = 0; i < 10; ++i)
                    GetCaster()->CastSpell(GetCaster(), SPELL_TRIGGER_MISSILE, true);
            }

            void Register() OVERRIDE
            {
                OnEffectHitTarget += SpellEffectFn(spell_ulduar_proximity_minesSpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const OVERRIDE
        {
            return new spell_ulduar_proximity_minesSpellScript();
        }
};

class spell_rapid_burst : public SpellScriptLoader
{
    public:
        spell_rapid_burst() : SpellScriptLoader("spell_rapid_burst") { }

        class spell_rapid_burst_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rapid_burst_AuraScript);

            void HandleDummyTick(AuraEffect const* aurEff)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();

                switch (caster->GetMap()->GetDifficulty())
                {
                    case RAID_DIFFICULTY_10MAN_NORMAL:
                        caster->CastSpell(GetTarget(), RAND(SPELL_RAPID_BURST_LEFT_10, SPELL_RAPID_BURST_RIGHT_10), true, NULL, aurEff);
                        break;
                    case RAID_DIFFICULTY_25MAN_NORMAL:
                        caster->CastSpell(GetTarget(), RAND(SPELL_RAPID_BURST_LEFT_25, SPELL_RAPID_BURST_RIGHT_25), true, NULL, aurEff);
                        break;
                    default:
                        break;
                }
            }


            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rapid_burst_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rapid_burst_AuraScript::HandleDummyTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rapid_burst_AuraScript();
        }
};

class go_not_push_button : public GameObjectScript
{
    public:
        go_not_push_button() : GameObjectScript("go_not_push_button") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            InstanceScript* _instance = go->GetInstanceScript();

            if (!_instance)
                return false;

            if ((_instance->GetBossState(DATA_MIMIRON) != IN_PROGRESS || _instance->GetBossState(DATA_MIMIRON) != DONE) && player)
            {
                if (Creature* mimiron = player->GetCreature((*player), _instance->GetData64(DATA_MIMIRON)))
                {
                    if (Creature* computer = mimiron->FindNearestCreature(NPC_COMPUTER,100.0f))
                    {
                        computer->AI()->TalkToMap(SAY_HARDMODE);
                        mimiron->AI()->DoAction(DO_ACTIVATE_HARD_MODE);
                    }
                }
            }

            go->UseDoorOrButton();

            return true;
        }
};

class achievement_mimiron_firefighter : public AchievementCriteriaScript
{
    public:
        achievement_mimiron_firefighter() : AchievementCriteriaScript("achievement_mimiron_firefighter") { }

        bool OnCheck(Player* /*source*/, Unit* target)
        {
            if (!target)
                return false;

            if (Creature* mimiron = target->ToCreature())
                if (mimiron->AI()->GetData(DATA_FIREFIGHTER))
                    return true;

            return false;
        }
};

void AddSC_boss_mimiron()
{
    new boss_mimiron();
    new boss_leviathan_mk();
    new boss_leviathan_mk_turret();
    new npc_proximity_mine();
    new boss_vx_001();
    new npc_rocket_strike();
    new boss_aerial_unit();
    new npc_magnetic_core();
    new npc_assault_bot();
    new npc_emergency_bot();
    new npc_mimiron_bomb_bot();
    new npc_frost_bomb();
    new npc_mimiron_flame_trigger();
    new npc_mimiron_flame_spread();
    new spell_ulduar_proximity_mines();
    new spell_rapid_burst();
    new go_not_push_button();
    new achievement_mimiron_firefighter();
}
