#include "stdafx.h"

void ItemManager::Update()
{
	auto iter = objects.begin();
	while (iter != objects.end())
	{
		(*iter)->Update();
		if ((*iter)->GetItem().itemid == 0) {
			objects.erase(iter++);
		}
		else iter++;
	}
}

void ItemManager::Render()
{
	for (auto& it : objects)
		it->Render();
}

void ItemManager::RenderHierarchy()
{
	for (auto& it : objects)
		it->RenderHierarchy();
}

void ItemManager::Spawn(Vector3 _pos, Item _item)
{
	ItemObject* temp = new ItemObject(_item);
	_pos.y += BLOCK_LENGTH;
	temp->SetLocalPos(_pos);
	objects.push_back(temp);
}

const char* ItemManager::GetItemName(int _itemid)
{
	const std::map<int, const char*> MyEnumStrings{
		{ 256	, "iron_shovel" },
		{ 257	, "iron_pickaxe" },
		{ 258	, "iron_axe" },
		{ 259	, "flint_and_steel" },
		{ 260	, "apple" },
		{ 261	, "bow" },
		{ 262	, "arrow" },
		{ 263	, "coal" },
		{ 264	, "diamond" },
		{ 265	, "iron_ingot" },
		{ 266	, "gold_ingot" },
		{ 267	, "iron_sword" },
		{ 268	, "wooden_sword" },
		{ 269	, "wooden_shovel" },
		{ 270	, "wooden_pickaxe" },
		{ 271	, "wooden_axe" },
		{ 272	, "stone_sword" },
		{ 273	, "stone_shovel" },
		{ 274	, "stone_pickaxe" },
		{ 275	, "stone_axe" },
		{ 276	, "diamond_sword" },
		{ 277	, "diamond_shovel" },
		{ 278	, "diamond_pickaxe" },
		{ 279	, "diamond_axe" },
		{ 280	, "stick" },
		{ 281	, "bowl" },
		{ 282	, "mushroom_stew" },
		{ 283	, "golden_sword" },
		{ 284	, "golden_shovel" },
		{ 285	, "golden_pickaxe" },
		{ 286	, "golden_axe" },
		{ 287	, "string" },
		{ 288	, "feather" },
		{ 289	, "gunpowder" },
		{ 290	, "wooden_hoe" },
		{ 291	, "stone_hoe" },
		{ 292	, "iron_hoe" },
		{ 293	, "diamond_hoe" },
		{ 294	, "golden_hoe" },
		{ 295	, "wheat_seeds" },
		{ 296	, "wheat" },
		{ 297	, "bread" },
		{ 298	, "leather_helmet" },
		{ 299	, "leather_tunic" },
		{ 300	, "leather_pants" },
		{ 301	, "leather_boots" },
		{ 302	, "chainmail_helmet" },
		{ 303	, "chainmail_chestplate" },
		{ 304	, "chainmail_leggings" },
		{ 305	, "chainmail_boots" },
		{ 306	, "iron_helmet" },
		{ 307	, "iron_chestplate" },
		{ 308	, "iron_leggings" },
		{ 309	, "iron_boots" },
		{ 310	, "diamond_helmet" },
		{ 311	, "diamond_chestplate" },
		{ 312	, "diamond_leggings" },
		{ 313	, "diamond_boots" },
		{ 314	, "golden_helmet" },
		{ 315	, "golden_chestplate" },
		{ 316	, "golden_leggings" },
		{ 317	, "golden_boots" },
		{ 318	, "flint" },
		{ 319	, "raw_porkchop" },
		{ 320	, "cooked_porkchop" },
		{ 321	, "painting" },
		{ 322	, "golden_apple" },
		{ 323	, "sign" },
		{ 324	, "oak_door" },
		{ 325	, "bucket" },
		{ 326	, "water_bucket" },
		{ 327	, "lava_bucket" },
		{ 328	, "minecart" },
		{ 329	, "saddle" },
		{ 330	, "iron_door" },
		{ 331	, "redstone" },
		{ 332	, "snowball" },
		{ 333	, "oak_boat" },
		{ 334	, "leather" },
		{ 335	, "milk_bucket" },
		{ 336	, "brick" },
		{ 337	, "clay" },
		{ 338	, "sugar_canes" },
		{ 339	, "paper" },
		{ 340	, "book" },
		{ 341	, "slimeball" },
		{ 342	, "minecart_with_chest" },
		{ 343	, "minecart_with_furnace" },
		{ 344	, "egg" },
		{ 345	, "compass" },
		{ 346	, "fishing_rod" },
		{ 347	, "clock" },
		{ 348	, "glowstone_dust" },
		{ 349	, "raw_fish" },
		{ 350	, "cooked_fish" },
		{ 351	, "ink_sack" },
		{ 352	, "bone" },
		{ 353	, "sugar" },
		{ 354	, "cake" },
		{ 355	, "bed" },
		{ 356	, "redstone_repeater" },
		{ 357	, "cookie" },
		{ 358	, "map" },
		{ 359	, "shears" },
		{ 360	, "melon" },
		{ 361	, "pumpkin_seeds" },
		{ 362	, "melon_seeds" },
		{ 363	, "raw_beef" },
		{ 364	, "steak" },
		{ 365	, "raw_chicken" },
		{ 366	, "cooked_chicken" },
		{ 367	, "rotten_flesh" },
		{ 368	, "ender_pearl" },
		{ 369	, "blaze_rod" },
		{ 370	, "ghast_tear" },
		{ 371	, "gold_nugget" },
		{ 372	, "nether_wart" },
		{ 373	, "potion" },
		{ 374	, "glass_bottle" },
		{ 375	, "spider_eye" },
		{ 376	, "fermented_spider_eye" },
		{ 377	, "blaze_powder" },
		{ 378	, "magma_cream" },
		{ 379	, "brewing_stand" },
		{ 380	, "cauldron" },
		{ 381	, "eye_of_ender" },
		{ 382	, "glistering_melon" },
		{ 384	, "bottle_o'_enchanting" },
		{ 385	, "fire_charge" },
		{ 386	, "book_and_quill" },
		{ 387	, "written_book" },
		{ 388	, "emerald" },
		{ 389	, "item_frame" },
		{ 390	, "flower_pot" },
		{ 391	, "carrot" },
		{ 392	, "potato" },
		{ 393	, "baked_potato" },
		{ 394	, "poisonous_potato" },
		{ 395	, "empty_map" },
		{ 396	, "golden_carrot" },
		{ 397	, "mob_head_(skeleton)" },
		{ 398	, "carrot_on_a_stick" },
		{ 399	, "nether_star" },
		{ 400	, "pumpkin_pie" },
		{ 401	, "firework_rocket" },
		{ 402	, "firework_star" },
		{ 403	, "enchanted_book" },
		{ 404	, "redstone_comparator" },
		{ 405	, "nether_brick" },
		{ 406	, "nether_quartz" },
		{ 407	, "minecart_with_tnt" },
		{ 408	, "minecart_with_hopper" },
		{ 409	, "prismarine_shard" },
		{ 410	, "prismarine_crystals" },
		{ 411	, "raw_rabbit" },
		{ 412	, "cooked_rabbit" },
		{ 413	, "rabbit_stew" },
		{ 414	, "rabbit's_foot" },
		{ 415	, "rabbit_hide" },
		{ 416	, "armor_stand" },
		{ 417	, "iron_horse_armor" },
		{ 418	, "golden_horse_armor" },
		{ 419	, "diamond_horse_armor" },
		{ 420	, "lead" },
		{ 421	, "name_tag" },
		{ 422	, "minecart_with_command_block" },
		{ 423	, "raw_mutton" },
		{ 424	, "cooked_mutton" },
		{ 425	, "banner" },
		{ 426	, "end_crystal" },
		{ 427	, "spruce_door" },
		{ 428	, "birch_door" },
		{ 429	, "jungle_door" },
		{ 430	, "acacia_door" },
		{ 431	, "dark_oak_door" },
		{ 432	, "chorus_fruit" },
		{ 433	, "popped_chorus_fruit" },
		{ 434	, "beetroot" },
		{ 435	, "beetroot_seeds" },
		{ 436	, "beetroot_soup" },
		{ 437	, "dragon's_breath" },
		{ 438	, "splash_potion" },
		{ 439	, "spectral_arrow" },
		{ 440	, "tipped_arrow" },
		{ 441	, "lingering_potion" },
		{ 442	, "shield" },
		{ 443	, "elytra" },
		{ 444	, "spruce_boat" },
		{ 445	, "birch_boat" },
		{ 446	, "jungle_boat" },
		{ 447	, "acacia_boat" },
		{ 448	, "dark_oak_boat" },
		{ 449	, "totem_of_undying" },
		{ 450	, "shulker_shell" },
		{ 452	, "iron_nugget" },
		{ 453	, "knowledge_book" },
		{ 2256	, "13_disc" },
		{ 2257	, "cat_disc" },
		{ 2258	, "blocks_disc" },
		{ 2259	, "chirp_disc" },
		{ 2260	, "far_disc" },
		{ 2261	, "mall_disc" },
		{ 2262	, "mellohi_disc" },
		{ 2263	, "stal_disc" },
		{ 2264	, "strad_disc" },
		{ 2265	, "ward_disc" },
		{ 2266	, "11_disc" },
		{ 2267	, "wait_disc" }
	};

	auto   it = MyEnumStrings.find(_itemid);
	return it == MyEnumStrings.end() ? "Unknown" : it->second;
}

const char* ItemManager::GetBlockId(int _blockid)
{
	const std::map<int, const char*> MyEnumStrings{
		{ 0		, "AIR" },
		{ 1		, "FLOWING_WATER" },
		{ 2		, "STILL_WATER" },
		{ 3		, "OAK_LEAVES" },
		{ 4		, "SPRUCE_LEAVES" },
		{ 5		, "BIRCH_LEAVES" },
		{ 6		, "JUNGLE_LEAVES" },
		{ 7		, "GLASS" },
		{ 10	, "STONE" },
		{ 11	, "GRASS" },
		{ 12	, "DIRT" },
		{ 13	, "COBBLESTONE" },
		{ 14	, "BEDROCK" },
		{ 15	, "FLOWING_LAVA" },
		{ 16	, "STILL_LAVA" },
		{ 17	, "SAND" },
		{ 18	, "GRAVEL" },
		{ 19	, "GOLD_ORE" },
		{ 20	, "IRON_ORE" },
		{ 21	, "COAL_ORE" },
		{ 22	, "LAPIS_LAZULI_ORE" },
		{ 23	, "LAPIS_LAZULI_BLOCK" },
		{ 24	, "DISPENSER" },
		{ 25	, "SANDSTONE" },
		{ 30	, "COBWEB" },
		{ 31	, "GRASS" },
		{ 37	, "DANDELION" },
		{ 39	, "BROWN_MUSHROOM" },
		{ 40	, "RED_MUSHROOM" },
		{ 41	, "GOLD_BLOCK" },
		{ 42	, "IRON_BLOCK" },
		{ 45	, "BRICKS" },
		{ 46	, "TNT" },
		{ 47	, "BOOKSHELF" },
		{ 48	, "MOSS_STONE" },
		{ 49	, "OBSIDIAN" },
		{ 50	, "TORCH" },
		{ 51	, "FIRE" },
		{ 54	, "CHEST" },
		{ 56	, "DIAMOND_ORE" },
		{ 57	, "DIAMOND_BLOCK" },
		{ 58	, "CRAFTING_TABLE" },
		{ 59	, "WHEAT_CROPS" },
		{ 60	, "FARMLAND" },
		{ 61	, "FURNACE" },
		{ 62	, "BURNING_FURNACE" },
		{ 64	, "OAK_DOOR_BLOCK" },
		{ 65	, "LADDER" },
		{ 66	, "RAIL" },
		{ 78	, "SNOW" },
		{ 79	, "ICE" },
		{ 80	, "SNOW_BLOCK" },
		{ 82	, "CLAY" },
		{ 85	, "OAK_FENCE" },
		{ 86	, "PUMPKIN" },
		{ 87	, "PUMPKIN_CARVED" },
		{ 89	, "GLOWSTONE" },
		{ 91	, "JACK_O'LANTERN" },
		{ 92	, "CAKE_BLOCK" },
		{ 93	, "FARMLAND_WET" },

		{ 100	, "OAK_WOOD" },
		{ 101	, "SPRUCE_WOOD" },
		{ 102	, "BIRCH_WOOD" },
		{ 103	, "JUNGLE_WOOD" },
		{ 104	, "OAK_WOOD_PLANK" },
		{ 105	, "SPRUCE_WOOD_PLANK" },
		{ 106	, "BIRCH_WOOD_PLANK" },
		{ 107	, "JUNGLE_WOOD_PLANK" },
		{ 108	, "ACACIA_WOOD_PLANK" },
		{ 109	, "DARK_OAK_WOOD_PLANK" },
		{ 110	, "OAK_SAPLING" },
		{ 111	, "SPRUCE_SAPLING" },
		{ 112	, "BIRCH_SAPLING" },
		{ 113	, "JUNGLE_SAPLING" },
		{ 114	, "ACACIA_SAPLING" },
		{ 115	, "DARK_OAK_SAPLING" },

		{ 120	, "WHITE_WOOL" },
		{ 121	, "ORANGE_WOOL" },
		{ 122	, "MAGENTA_WOOL" },
		{ 123	, "LIGHT_BLUE_WOOL" },
		{ 124	, "YELLOW_WOOL" },
		{ 125	, "LIME_WOOL" },
		{ 126	, "PINK_WOOL" },
		{ 127	, "GRAY_WOOL" },
		{ 128	, "LIGHT_GRAY_WOOL" },
		{ 129	, "CYAN_WOOL" },
		{ 130	, "PURPLE_WOOL" },
		{ 131	, "BLUE_WOOL" },
		{ 132	, "BROWN_WOOL" },
		{ 133	, "GREEN_WOOL" },
		{ 134	, "RED_WOOL" },
		{ 135	, "BLACK_WOOL" },

		{ 140	, "POPPY" },
		{ 141	, "BLUE_ORCHID" },
		{ 142	, "ALLIUM" },
		{ 143	, "AZURE_BLUET" },
		{ 144	, "RED_TULIP" },
		{ 145	, "ORANGE_TULIP" },
		{ 146	, "WHITE_TULIP" },
		{ 147	, "PINK_TULIP" },
		{ 148	, "OXEYE_DAISY" },

		{ 150	, "STONE_SLAB" },
		{ 151	, "SANDSTONE_SLAB" },
		{ 152	, "WOODEN_SLAB" },
		{ 153	, "COBBLESTONE_SLAB" },
		{ 154	, "BRICK_SLAB" },
		{ 155	, "STONE_BRICK_SLAB" },
		{ 156	, "NETHER_BRICK_SLAB" },
		{ 157	, "QUARTZ_SLAB" },

		{ 154	, "HOPPER" },
		{ 155	, "QUARTZ_BLOCK" },
		{ 156	, "CHISELED_QUARTZ_BLOCK" },
		{ 157	, "PILLAR_QUARTZ_BLOCK" },
		{ 158	, "QUARTZ_STAIRS" },
		{ 163	, "ACACIA_WOOD_STAIRS" },
		{ 164	, "DARK_OAK_WOOD_STAIRS" },
		{ 165	, "SLIME_BLOCK" },
		{ 166	, "BARRIER" },
		{ 167	, "IRON_TRAPDOOR" },
		{ 169	, "SEA_LANTERN" },
		{ 170	, "HAY_BALE" },
		{ 172	, "HARDENED_CLAY" },
		{ 173	, "BLOCK_OF_COAL" },
		{ 174	, "PACKED_ICE" },
		{ 175	, "SUNFLOWER" },
		{ 176	, "FREE-STANDING_BANNER" },
		{ 177	, "WALL-MOUNTED_BANNER" },
		{ 178	, "INVERTED_DAYLIGHT_SENSOR" },
		{ 179	, "RED_SANDSTONE" },
		{ 180	, "RED_SANDSTONE_STAIRS" },
		{ 181	, "DOUBLE_RED_SANDSTONE_SLAB" },
		{ 182	, "RED_SANDSTONE_SLAB" },
		{ 183	, "SPRUCE_FENCE_GATE" },
		{ 184	, "BIRCH_FENCE_GATE" },
		{ 185	, "JUNGLE_FENCE_GATE" },
		{ 186	, "DARK_OAK_FENCE_GATE" },
		{ 187	, "ACACIA_FENCE_GATE" },
		{ 188	, "SPRUCE_FENCE" },
		{ 189	, "BIRCH_FENCE" },
		{ 190	, "JUNGLE_FENCE" },
		{ 191	, "DARK_OAK_FENCE" },
		{ 192	, "ACACIA_FENCE" },
		{ 193	, "SPRUCE_DOOR_BLOCK" },
		{ 194	, "BIRCH_DOOR_BLOCK" },
		{ 195	, "JUNGLE_DOOR_BLOCK" },
		{ 196	, "ACACIA_DOOR_BLOCK" },
		{ 197	, "DARK_OAK_DOOR_BLOCK" },

	};

	auto   it = MyEnumStrings.find(_blockid);
	return it == MyEnumStrings.end() ? "Unknown" : it->second;
}

Item ItemManager::GetDropItem(BlockType _blockType)
{
	switch (_blockType)
	{
	case BlockType::STONE:
	case BlockType::COBBLESTONE:
		return Item{ int(BlockType::COBBLESTONE), 1 };
	}
	return Item{ 0, 0};
}

void ItemManager::SetItemImage(GameObject* _gameObject, Item _item)
{
	if (_item.itemid == 0)
		return;
	if (_item.itemid < 200) {
		_gameObject->material = RESOURCE->materials.Load("Items/" + to_string(_item.itemid) + ".mtl");
	}
	else {
		string str = "";
		_gameObject->material = RESOURCE->materials.Load(str + "Items/" + GetItemName(_item.itemid) + ".mtl");
	}
}

void ItemManager::SetItemObjectImage(GameObject* _gameObject, Item _item)
{
	if (_item.itemid == 0)
		return;
	if (_item.itemid < 200) {
		_gameObject->mesh = RESOURCE->meshes.Load("Block/" + to_string(_item.itemid) + ".mesh");
		_gameObject->shader = RESOURCE->shaders.Load("Block.hlsl");
		_gameObject->material = RESOURCE->materials.Load("BaseBlock.mtl");
	}
	else {
		string str = "";
		_gameObject->mesh = RESOURCE->meshes.Load("item.mesh");
		_gameObject->shader = RESOURCE->shaders.Load("Item.hlsl");
		_gameObject->material = RESOURCE->materials.Load(str + "items/" + ITEM_MANAGER->GetItemName(_item.itemid) + ".mtl");
	}
}

