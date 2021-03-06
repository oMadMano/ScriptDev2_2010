-- Script
UPDATE creature_template SET npcflag=1, AIName="",ScriptName="npc_spirit_azuregos" WHERE entry=15481;

DELETE FROM `npc_text` WHERE `ID` IN (1630011, 1630012, 1630013, 1630014, 1630015, 1630016, 1630017, 1630018, 1630019, 1630020, 1630021, 1630022, 1630023);
INSERT INTO npc_text (ID, prob0, em0_1, text0_0) VALUES
(1630011, 100, 163, "You seek the scepter shard charged to the protection of the Blue Flight?"),
(1630012, 100, 0, "Of course I do not have the shard. That would be asinine. I walk amongst savages in this cursed land! I cannot take five steps without some crazed orc or human trying to thrust a sharp stick into my hide. At any given time you could very well be speaking to my ghostly spirit.$B$B Anyhow... I hid it.$B$B Go on... ask me where."),
(1630013, 100, 0, "You are going to love this story, $R. See, here is the thing. As soon as Malygos charged me with protecting the scepter shard, I knew I was in for an eternity of headache and pain.$B$B All I want to do is study these magic rich shorelines and take in what artifacts might remain from the Sundering. You know, there was once a thriving Highborne civilization here! You don't have to tell me that there is going to be some solid magical items around here, $R. I can smell it!"),
(1630014, 100, 0, "As I was saying, I held on to that scepter shard for a good five-hundred years and it was nothing but trouble. It attracted all kinds of attention - the wrong kind of attention. I want to be left alone to my studies not babysit some would be hero's ticket to glory. So... I gave it to the fish."),
(1630015, 100, 0, "Not just any fish, mortal. This fish was a minnow. A very special minnow."),
(1630016, 100, 0, "Exactly!"),
(1630017, 100, 0, "Genius, I know... It will never be found; but, in case it is found, I gave the minnow some special powers."),
(1630018, 100, 60, "Correct. You've been listening! This minnow is really quite a terrible creature to of my own creation. When I am relaxing I like to think of the unlucky fishermen who have run into this minnow and been devoured whole. I bet they were quite surprised!"),
(1630019, 100, 0, "Genius is often misunderstood, $R. Now, about the scepter shard... If you want that shard and do not wish to spend the next ten thousand years searching for it, you are going to have to listen very carefully."),
(1630020, 100, 0, "Two words: Arcanite buoy."),
(1630021, 100, 0, "Right then... You have to build an arcanite buoy and place it in the ocean. My minnow will be attracted to the magical emanations. When he gets near the buoy - BLAMMO! It will explode in a glorious pulse of arcane energy, revealing the minnow's true form. Also, you may or may not incur the wrath of Neptulon. A 50/50 chance I would say."),
(1630022, 100, 0, "If I did not know better I would think that you were mocking me, mortal; but yes, that is mostly correct. You may remain fully clothed."),
(1630023, 100, 0, "Take this ledger to an old acquaintance of mine in Tanaris. His name is Neutral Narain Soothfancy - terrible, terrible psychic but an amazing engineer! He should be able to make sense of it all.$B$B No need to thank me, $N. It's the least I could do.$B$B Good day!");
