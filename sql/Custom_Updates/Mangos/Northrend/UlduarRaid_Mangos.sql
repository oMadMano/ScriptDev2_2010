/* ULDUAR */

-- Flame Leviathan
UPDATE creature_template SET ScriptName = "boss_flame_leviathan" WHERE entry = 33113;
UPDATE creature_template SET ScriptName = "mob_defense_turret" WHERE entry = 33142;

-- Ignis
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_ignis' WHERE entry=33118;
UPDATE creature_template SET ScriptName = "mob_iron_construct" WHERE entry = 33121;
UPDATE creature_template SET minlevel=80, maxlevel=80, faction_h=1925, faction_a=1925, scale=0.5, scriptname='mob_scorch_target' WHERE entry=33221;

-- Razorscale
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_razorscale' WHERE entry=33186;
UPDATE creature_template SET ScriptName = "mob_dark_rune_watcher" WHERE entry = 33453;
UPDATE creature_template SET ScriptName = "mob_dark_rune_sentinel" WHERE entry = 33846;
UPDATE creature_template SET ScriptName = "mob_dark_rune_guardian" WHERE entry = 33388;
UPDATE creature_template SET ScriptName = "npc_expedition_commander" WHERE entry = 33210;
UPDATE creature_template SET ScriptName = "mob_devouring_flame_target" WHERE entry in (34189, 34188);

-- XT002
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_xt002' WHERE entry=33293;
UPDATE creature_template SET ScriptName = "mob_pummeler" WHERE entry = 33344;
UPDATE creature_template SET speed_run=0.5, faction_a=1925, faction_h=1925, scriptname='mob_boombot' WHERE entry=33346;
UPDATE creature_template SET speed_run=0.5 WHERE entry=33343;
UPDATE creature_template SET mechanic_immune_mask=652951551, scriptname='mob_xtheart' WHERE entry=33329;
UPDATE creature_template SET ScriptName = "mob_voidzone" WHERE entry = 34001;
UPDATE creature_template SET minhealth = 176400, maxhealth = 176400, minlevel = 80, maxlevel = 80, faction_a = 14, faction_h = 14, ScriptName = "mob_lifespark" WHERE entry = 34004;
Update creature set spawnMask = 0 where id in (34004);

-- Iron council
UPDATE creature_template SET mechanic_immune_mask=619395071, scriptname='boss_brundir' WHERE entry=32857;
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_molgeim' WHERE entry=32927;
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_steelbreaker' WHERE entry=32867;
UPDATE creature_template SET ScriptName = "mob_rune_of_power" WHERE entry = 33705;
UPDATE creature_template SET ScriptName = "mob_rune_of_summoning" WHERE entry = 33051;
UPDATE creature_template SET ScriptName = "mob_ulduar_lightning_elemental" WHERE entry = 32958;
#UPDATE `creature_template` SET `mechanic_immune_mask` = 619397115 WHERE `entry` in (32857, 33694);
UPDATE `creature_template` SET `mechanic_immune_mask` = 0 WHERE `entry` in (32857, 33694);

-- Kologarn
DELETE FROM creature WHERE id IN (32933, 32934);
INSERT INTO creature (id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType) VALUES (32933, 603, 3, 65535, 0, 0, 1799.68, -24.3599, 452.227, 3.14747, 604800, 0, 0, 543855, 0, 0, 0);
INSERT INTO creature (id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType) VALUES (32934, 603, 3, 65535, 0, 0, 1799.68, -24.3599, 452.227, 3.14747, 604800, 0, 0, 543855, 0, 0, 0);
UPDATE creature_model_info SET bounding_radius=15, combat_reach=15 WHERE modelid IN (28638, 28822, 28821);
UPDATE creature_template SET mechanic_immune_mask=617299803, scriptname='boss_kologarn' WHERE entry=32930;
UPDATE creature_template SET mechanic_immune_mask=652951551, scriptname='boss_right_arm' WHERE entry=32934;
UPDATE creature_template SET mechanic_immune_mask=652951551, scriptname='boss_left_arm' WHERE entry=32933;
UPDATE creature_template SET ScriptName = "mob_ulduar_rubble" WHERE entry in (33768, 33809, 33908, 33942);
update `gameobject` set `position_y` = -35.6824, `position_x` = 1837.59 where `id` in (195047);

-- Auriaya
UPDATE creature_template SET mechanic_immune_mask=583745371, equipment_id = 103000, scriptname='boss_auriaya' WHERE entry=33515;
UPDATE creature_template SET mechanic_immune_mask=619395071, scriptname='mob_feral_defender' WHERE entry=34035;
UPDATE creature_template SET minlevel=80, maxlevel=80, faction_h=14, faction_a=14, scriptname='mob_seeping_feral_essence' WHERE entry=34098;
UPDATE creature_template SET ScriptName = "mob_sanctum_sentry" WHERE entry = 34014;
UPDATE `creature_template` SET `mechanic_immune_mask` = 619397115 WHERE `entry` in (33515, 34175);
delete from creature_equip_template where entry = 103000;
insert into creature_equip_template values (103000, 45315, 0, 0);
DELETE FROM `creature_movement` WHERE `id`=94378;
INSERT INTO `creature_movement` (`id`,`point`,`position_x`,`position_y`,`position_z`,`waittime`,`textid1`,`textid2`,`textid3`,`textid4`,`textid5`,`emote`,`spell`,`wpguid`,`orientation`,`model1`,`model2`) VALUES

#(94378, 4, 1916.56, -69.9669, 417.718, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.2268, 0, 0),	-- after hodir up
#(94378, 3, 1900.26, -24.0211, 417.722, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.15909, 0, 0),	-- center kolgoran
#(94378, 2, 1916.97, 21.1583, 417.748, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.86988, 0, 0),	-- before yogg up

(94378, 1, 1925.012, 30.0067, 411.356, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.69685, 0, 0),	-- before yogg down
(94378, 2, 1957.04, 49.3067, 411.355, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.37071, 0, 0),	-- after yogg down
(94378, 3, 1967.38, 51.4931, 417.561, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.09545, 0, 0),	-- after yogg up
(94378, 4, 2013.07, 44.3788, 417.715, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.71365, 0, 0), 	-- before mimiron up
(94378, 5, 2021.35, 37.9771, 411.387, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.25205, 0, 0), 	-- before mimiron down
(94378, 6, 2046.36, 8.56725, 411.524, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.203, 0, 0),		-- after mimiron down 
(94378, 7, 2053.32, -7.1366, 421.78, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.85107, 0, 0),		-- before freya up
(94378, 8, 2052.87, -40.8556, 421.706, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.4223, 0, 0), 	-- after freya up
(94378, 9, 2045.00, -56.79369, 411.359, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.20538, 0, 0),	-- before thorim down
(94378, 10, 2022.18, -86.5468, 411.355, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.60096, 0, 0),	-- after thorim down
(94378, 11, 2012.94, -92.7106, 417.717, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.28968, 0, 0),	-- after thorim up
(94378, 12, 1968.83, -101.0946, 417.722, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.662873, 0, 0),-- before hodir up
(94378, 13, 1958.08, -96.7855, 411.864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.763719, 0, 0),	-- before hodir down
(94378, 14, 1924.12, -78.5404, 411.488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.210024, 0, 0),	-- after hodir down

(94378, 15, 1958.08, -96.7855, 411.864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.763719, 0, 0),	-- before hodir down
(94378, 16, 1968.83, -101.0946, 417.722, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.662873, 0, 0),-- before hodir up
(94378, 17, 2012.94, -92.7106, 417.717, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.28968, 0, 0),	-- after thorim up
(94378, 18, 2022.18, -86.5468, 411.355, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.60096, 0, 0),	-- after thorim down
(94378, 19, 2045.00, -56.79369, 411.359, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.20538, 0, 0),	-- before thorim down
(94378, 20, 2052.87, -40.8556, 421.706, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.4223, 0, 0), 	-- after freya up
(94378, 21, 2053.32, -7.1366, 421.78, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.85107, 0, 0),	-- before freya up
(94378, 22, 2046.36, 8.56725, 411.524, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.203, 0, 0),		-- after mimiron down
(94378, 23, 2021.35, 37.9771, 411.387, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.25205, 0, 0), 	-- before mimiron down
(94378, 24, 2013.07, 44.3788, 417.715, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.71365, 0, 0), 	-- before mimiron up
(94378, 25, 1967.38, 51.4931, 417.561, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.09545, 0, 0),	-- after yogg up
(94378, 26, 1957.04, 49.3067, 411.355, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.37071, 0, 0);	-- after yogg down

-- Freya
UPDATE creature_template SET ScriptName = "boss_freya" WHERE entry = 32906;
UPDATE creature_template SET ScriptName = "boss_elder_brightleaf" WHERE entry = 32915;
UPDATE creature_template SET ScriptName = "boss_elder_ironbranch" WHERE entry = 32913;
UPDATE creature_template SET ScriptName = "boss_elder_stonebark" WHERE entry = 32914;
UPDATE creature_template SET ScriptName = "mob_nature_bomb" WHERE entry = 34129;
UPDATE creature_template SET ScriptName = "mob_iron_roots" WHERE entry in (33088, 33168);

-- Hodir
UPDATE creature_template SET ScriptName = "boss_hodir" WHERE entry = 32845;
UPDATE creature_template SET ScriptName = "mob_snowdrift" WHERE entry = 33174;
UPDATE creature_template SET ScriptName = "mob_flashFreeze" WHERE entry in (32926, 32938);
Update creature set spawnMask = 0 where id in (32926, 32938);
UPDATE creature_template SET ScriptName = "npc_hodir_priest" WHERE entry in (32897, 33326, 32948, 33330);
UPDATE creature_template SET ScriptName = "npc_hodir_druid" WHERE entry in (33325, 32901, 32941, 33333);
UPDATE creature_template SET ScriptName = "npc_hodir_shaman" WHERE entry in (33328, 32900, 33332, 32950);
UPDATE creature_template SET ScriptName = "npc_hodir_mage" WHERE entry in (32893, 33327, 33331, 32946);

-- Mimiron
UPDATE creature_template SET `AIName` = '', ScriptName = "boss_mimiron" WHERE entry = 33350;
UPDATE creature_template SET `RegenHealth`= 0, ScriptName = "boss_leviathan_mk" WHERE entry = 33432;
UPDATE creature_template SET ScriptName = "leviathan_turret" WHERE entry = 34071;
UPDATE creature_template SET `RegenHealth`= 0, ScriptName = "boss_vx001" WHERE entry = 33651;
UPDATE creature_template SET `RegenHealth`= 0, ScriptName = "boss_aerial_command_unit" WHERE entry = 33670;
update creature set position_x = 2784.35, position_y = 2578.03, orientation = 3.2 where id = 33350;
update creature set position_x = 2794.86, position_y = 2597.83, orientation = 3.57, spawnMask = 3 where id = 33432;
UPDATE gameobject_template SET ScriptName="go_red_button" WHERE entry = 194739;
UPDATE creature_template SET ScriptName = "mob_proximity_mine" WHERE entry = 34362;
UPDATE creature_template SET ScriptName = "mob_bomb_bot" WHERE entry in (33836, 34192);
UPDATE creature_template SET `faction_A` = 14, `faction_H` = 14, `minlevel` = 80, `maxlevel` = 80, ScriptName = "mob_emergency_bot" WHERE entry = 34147;
UPDATE creature_template SET `faction_A` = 14, `faction_H` = 14, ScriptName = "mob_frost_bomb" WHERE entry = 34149;
update `gameobject` set `position_x` = 2734.73 where `id` in (194789, 194956);

-- Thorim
UPDATE creature_template SET `unit_flags` = 0, ScriptName = "boss_thorim" WHERE entry = 32865;
UPDATE creature_template SET ScriptName = "boss_runic_colossus" WHERE entry = 32872;
UPDATE creature_template SET ScriptName = "boss_ancient_rune_giant" WHERE entry = 32873;
update creature set spawnMask = 3 where id = 32873;
UPDATE creature_template SET `faction_A` = 14, `faction_H` = 14, ScriptName = "npc_sif" WHERE entry = 33196;
UPDATE creature_template SET `faction_A` = 14, `faction_H` = 14 WHERE entry = 33138;
update `gameobject` set `position_y` = -286.67, `position_z` = 419.50 where `id` in (194312, 194313, 194314, 194315);
UPDATE gameobject_template SET ScriptName="go_door_lever" WHERE entry = 194264;
delete from gameobject where id = 194264; 
insert into gameobject VALUES (110010,194264,603,3,65535,2173.276, -252.805, 420.146, 3.027,0,0,0,0,604800,0,1);
update `creature` set `phaseMask` = 128 where `id` in (32907, 32883); 	-- horde soldiers: phase 128 for aly: 65535
update `creature` set `phaseMask` = 64 where `id` in (32885, 32908);	-- alliance soldiers: phase 64 for horde
-- reset pos to some creatures 
update `creature` set `position_x` = 2222.69 where `guid` = 129413;
update `creature` set `position_x` = 2222.69 where `guid` = 129412;
update `creature` set `position_x` = 2227.34 where `guid` = 129856;
update `creature` set `position_x` = 2227.34 where `guid` = 129857;

update `creature` set `position_y` = -437.73 where `guid` = 129860;
update `creature` set `position_y` = -437.73 where `guid` = 129861;
update `creature` set `position_y` = -434.64 where `guid` = 129862;
update `creature` set `position_y` = -434.64 where `guid` = 129863;
update `creature` set `position_y` = -434.64 where `guid` = 129391;

-- Vezax
UPDATE creature_template SET ScriptName = "boss_vezax" WHERE entry = 33271;
UPDATE creature_template SET MinHealth = 23009250, MaxHealth = 23009250, ScriptName = "boss_vezax" WHERE entry = 33449;
UPDATE `creature_template` SET `mechanic_immune_mask` = 619397115 WHERE `entry` in (33271, 33449);
UPDATE creature_template SET ScriptName = "mob_saronite_animus" WHERE entry = 33524;
UPDATE creature_template SET ScriptName = "mob_saronite_vapor", movementType = 1  WHERE entry = 33488;

-- Yogg
UPDATE creature_template SET ScriptName = "boss_yogg_saron" WHERE entry = 33288;
update creature_template set `RegenHealth`= 0, `flags_extra` = 1,`type_flags` = 108, ScriptName = "boss_sara" where entry = 33134;
update creature set spawnMask = 3, MovementType = 0 where id = 33134;
update creature_template set `RegenHealth`= 0, ScriptName = "boss_brain_of_yogg_saron" where entry = 33890;
update creature set `spawntimesecs` = 604800 where `id` = 33134;
UPDATE creature_template SET ScriptName = "mob_corruptor_tentacle" WHERE entry = 33985;
UPDATE creature_template SET ScriptName = "mob_constrictor_tentacle" WHERE entry = 33983;
UPDATE creature_template SET MinHealth = 40000, MaxHealth = 40000, minLevel = 80, maxLevel = 80, ScriptName = "mob_vision_tentacle" WHERE entry = 33943;
UPDATE creature_template SET MinHealth = 400000, MaxHealth = 400000, ScriptName = "mob_crusher_tentacle" WHERE entry = 33966;
UPDATE creature_template SET MinHealth = 220000, MaxHealth = 220000, ScriptName = "mob_guardian_of_yogg_saron" WHERE entry = 33136;
UPDATE creature_template SET ScriptName = "mob_immortal_guardian" WHERE entry = 33988;
UPDATE creature_template SET `faction_A` = 14, `faction_H` = 14, ScriptName = "mob_death_orb" WHERE entry = 33882;
UPDATE creature_template SET ScriptName = "mob_sanity_well" WHERE entry = 33991;
UPDATE creature_template SET scriptname='mob_madness_portal' WHERE `entry`=34072;
-- Keepers
UPDATE creature_template SET ScriptName = "keeper_hodir" WHERE entry = 33411;
UPDATE creature_template SET ScriptName = "keeper_freya" WHERE entry = 33410;
UPDATE creature_template SET ScriptName = "keeper_thorim" WHERE entry = 33413;
UPDATE creature_template SET ScriptName = "keeper_mimiron" WHERE entry = 33412;
-- Keepers images
UPDATE creature_template SET ScriptName = "hodir_image" WHERE entry = 33879;
UPDATE creature_template SET ScriptName = "freya_image" WHERE entry = 33876;
UPDATE creature_template SET ScriptName = "thorim_image" WHERE entry = 33878;
UPDATE creature_template SET ScriptName = "mimiron_image" WHERE entry = 33880;
-- insert the brain and keepers imagees into the db
delete from creature where id in (33890, 33876, 33880, 33879, 33878);
insert into creature VALUES (800000,33890,603,3,65535,0,0,1981.422,-22.442,255.011,0,604800,0,0,1371428,0,0,0),	-- Brain
(800001, 33876, 603, 3, 65535,0,0, 1888.782, -3.919, 333.446, 5.91, 604800,0,0, 5647, 0, 0, 0),		-- Freya 
(800002, 33880, 603, 3, 65535,0,0, 1891.667, 3.103, 333.051, 5.82, 604800,0,0, 5647, 0, 0, 0),		-- Mimiron
(800003, 33879, 603, 3, 65535,0,0, 1888.782, -45.434, 333.434, 0.26, 604800,0,0, 5647, 0, 0, 0), 	-- Hodir
(800004, 33878, 603, 3, 65535,0,0, 1891.667, -53.316, 333.031, 0.38, 604800,0,0, 5647, 0, 0, 0); 	-- Thorim
-- insert doors & portals into the brain room
delete from gameobject where id in (194635);
insert into gameobject VALUES (110000,194635,603,3,65535,2022.490,-25.389,261.961,0,0,0,0,0,604800,0,1);
delete from gameobject where guid = 110001;
insert into gameobject VALUES (110001,194462,603,3,65535,2104.555, -25.635,242.646,0,0,0,0,0,604800,100,1);
delete from areatrigger_teleport where id = 10000;
delete from gameobject_template where entry = 500000;
#insert into gameobject VALUES (110002,500000,603,3,65535,1999.690, -54.931, 242.418,0,0,0,0,0,604800,100,1);
#insert into gameobject VALUES (110003,500000,603,3,65535,1946.898, -25.769, 242.169,0,0,0,0,0,604800,100,1);


-- Algalon
UPDATE creature_template SET ScriptName = "boss_algalon" WHERE entry = 32871;
UPDATE creature_template SET ScriptName = "mob_collapsing_star" WHERE entry = 32955;
UPDATE creature_template SET ScriptName = "mob_living_constellation" WHERE entry = 33052;
UPDATE creature_template SET ScriptName = "mob_black_hole" WHERE entry = 32953;
update creature_template set minhealth = 39099, maxhealth = 39099 where entry = 33089;

-- Teleporter
UPDATE gameobject_template SET ScriptName="ulduar_teleporter" WHERE entry = 194569;
-- Destination Locations for Ulduar Teleporter spells
REPLACE INTO spell_target_position VALUES
(64014, 603, -706.122, -92.6024, 429.876, 0),      /* Expedition Base Camp */
(64032, 603, 131.248, -35.3802, 409.804, 0),       /* Formation Grounds */
(64028, 603, 553.233, -12.3247, 409.679, 0),       /* Colossal Forge */
(64031, 603, 926.292, -11.4635, 418.595, 3.14159), /* Scrapyard */
(64030, 603, 1498.09, -24.246, 420.967, 0),        /* Antechamber of Ulduar */
(64029, 603, 1859.45, -24.1, 448.9, 0),            /* Shattered Walkway */
(64024, 603, 2086.27, -24.3134, 421.239, 0),       /* Conservatory of Life */
(65061, 603, 2517.31, 2568.87, 412.299, 0),        /* Spark of Imagination */
(65042, 603, 1854.73, -11.637, 334.575, 0);        /* Prison of Yogg-Saron */

-- Doors 
UPDATE gameobject_template SET faction = 114 WHERE entry in (194553, 194554, 194556, 194555, 194148, 194634, 194635, 194905, 194441,
194442, 194416, 194774, 194775, 194776, 194560, 194557, 194558, 194750, 194910, 194559, 194635, 194636, 194637);
UPDATE gameobject_template SET faction = 0 WHERE entry in (194255, 194630, 194631);
-- Doors from the siege && descent into madness: to be added later
#UPDATE gameobject_template SET faction = 114 WHERE entry in (194255, 194630, 194631);

-- loot chests
UPDATE gameobject_template SET faction = 0 WHERE entry in (195046, 195047, 194307, 194308, 194200, 194201, 194312, 194313, 194314, 194315, 194821,
194822, 194823, 194324, 194325, 194326, 194327, 194328, 194329, 194330, 194331, 194789, 194956);
update gameobject set spawntimesecs = -604800 where id in (195046, 195047, 194307, 194308, 194200, 194201, 194312, 194313, 194314, 194315, 194821,
194822, 194823, 194324, 194325, 194326, 194327, 194328, 194329, 194330, 194331, 194789, 194956);

-- Iron council loot -->> event fixed. Loot ids removed; Only steelbreaker has loot
update `creature_template` set `lootid` = 0 where `entry` in (32927, 32857);

-- Mobs
UPDATE creature_template SET ScriptName = "generic_creature" WHERE entry in (34086, 34085, 34069, 33237, 34234, 33236, 33264, 34164, 34196, 34199, 34198, 
34190, 34197, 33699, 34134, 34135, 34133, 33430, 33528, 33431, 33527, 33526, 33525, 33355, 33354, 34193, 34183, 32908, 32885, 32907, 32883, 33125, 33110, 32874, 
32877, 32878, 32904, 32876, 33110, 33822, 33818, 33824, 33823, 33772, 33838, 33819, 33820, 32882, 32875, 33346, 34057, 33228, 32918, 33202, 32919, 32916, 33203);