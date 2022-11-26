#include "stdafx.h"

Crafting::Crafting()
{
	Init();
}

void Crafting::LoadData()
{
	list1x1.push_back(Craft1x1{ int(BlockType::OAK_WOOD), Item{ int(BlockType::OAK_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::SPRUCE_WOOD), Item{ int(BlockType::SPRUCE_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::BIRCH_WOOD), Item{ int(BlockType::BIRCH_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::JUNGLE_WOOD), Item{ int(BlockType::JUNGLE_WOOD_PLANK), 4 } });

	list2x1.push_back(Craft2x1{ { 
		{ int(BlockType::OAK_WOOD_PLANK) }, 
		{ int(BlockType::OAK_WOOD_PLANK) } 
		}, Item{ GetItemId("stick"), 4 } });
	list2x1.push_back(Craft2x1{ { 
		{ int(BlockType::SPRUCE_WOOD_PLANK) },
		{ int(BlockType::SPRUCE_WOOD_PLANK) }
		}, Item{ GetItemId("stick"), 4 } });
	list2x1.push_back(Craft2x1{ { 
		{ int(BlockType::BIRCH_WOOD_PLANK) },
		{ int(BlockType::BIRCH_WOOD_PLANK) }
		}, Item{ GetItemId("stick"), 4 } });
	list2x1.push_back(Craft2x1{ { 
		{ int(BlockType::JUNGLE_WOOD_PLANK) },
		{ int(BlockType::JUNGLE_WOOD_PLANK) }
		}, Item{ GetItemId("stick"), 4 } });

	list2x2.push_back(Craft2x2{ { 
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) },
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x2.push_back(Craft2x2{ { 
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) },
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x2.push_back(Craft2x2{ { 
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) },
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x2.push_back(Craft2x2{ { 
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) },
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL) },
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL) },
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL) },
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL), int(BlockType::WHITE_WOOL) },
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) }
		}, Item{ int(BlockType::CRAFTING_TABLE), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::OAK_WOOD_PLANK), 0, int(BlockType::OAK_WOOD_PLANK) },
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) }
		}, Item{ GetItemId("oak_boat"), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::SPRUCE_WOOD_PLANK), 0, int(BlockType::SPRUCE_WOOD_PLANK) },
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) }
		}, Item{ GetItemId("oak_boat"), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::BIRCH_WOOD_PLANK), 0, int(BlockType::BIRCH_WOOD_PLANK) },
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) }
		}, Item{ GetItemId("oak_boat"), 1 } });
	list2x3.push_back(Craft2x3{ { 
		{ int(BlockType::JUNGLE_WOOD_PLANK), 0, int(BlockType::JUNGLE_WOOD_PLANK) },
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) }
		}, Item{ GetItemId("oak_boat"), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("stick"), 0, GetItemId("stick") },
		{ GetItemId("stick"), GetItemId("stick"), GetItemId("stick") },
		{ GetItemId("stick"), 0, GetItemId("stick") }
		}, Item{ int(BlockType::LADDER), 3 } });

	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) },
		{ int(BlockType::OAK_WOOD_PLANK), 0, int(BlockType::OAK_WOOD_PLANK) },
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) }
		}, Item{ int(BlockType::CHEST), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) },
		{ int(BlockType::SPRUCE_WOOD_PLANK), 0, int(BlockType::SPRUCE_WOOD_PLANK) },
		{ int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK), int(BlockType::SPRUCE_WOOD_PLANK) }
		}, Item{ int(BlockType::CHEST), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) },
		{ int(BlockType::BIRCH_WOOD_PLANK), 0, int(BlockType::BIRCH_WOOD_PLANK) },
		{ int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK), int(BlockType::BIRCH_WOOD_PLANK) }
		}, Item{ int(BlockType::CHEST), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) },
		{ int(BlockType::JUNGLE_WOOD_PLANK), 0, int(BlockType::JUNGLE_WOOD_PLANK) },
		{ int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK), int(BlockType::JUNGLE_WOOD_PLANK) }
		}, Item{ int(BlockType::CHEST), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::COBBLESTONE), int(BlockType::COBBLESTONE), int(BlockType::COBBLESTONE) },
		{ int(BlockType::COBBLESTONE), 0, int(BlockType::COBBLESTONE) },
		{ int(BlockType::COBBLESTONE), int(BlockType::COBBLESTONE), int(BlockType::COBBLESTONE) }
		}, Item{ int(BlockType::FURNACE), 1 } });

	list2x1.push_back(Craft2x1{ { 
		{ GetItemId("coal") },
		{ GetItemId("stick") }
		}, Item{ int(BlockType::TORCH), 4 } });
	
	list3x1.push_back(Craft3x1{ {
		{ int(BlockType::OAK_WOOD_PLANK) },
		{ int(BlockType::OAK_WOOD_PLANK) },
		{ GetItemId("stick") }
		}, Item{ GetItemId("wood_sword"), 1 } });
	list3x1.push_back(Craft3x1{ { 
		{ int(BlockType::OAK_WOOD_PLANK) },
		{ GetItemId("stick")},
		{ GetItemId("stick") }
		}, Item{ GetItemId("wood_shovel"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), 0 },
		{ int(BlockType::OAK_WOOD_PLANK), GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("wood_axe"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK), int(BlockType::OAK_WOOD_PLANK) },
		{ 0, GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("wood_pickaxe"), 1 } });
	
	list3x1.push_back(Craft3x1{ {
		{ int(BlockType::STONE) },
		{ int(BlockType::STONE) },
		{ GetItemId("stick") }
		}, Item{ GetItemId("stone_sword"), 1 } });
	list3x1.push_back(Craft3x1{ { 
		{ int(BlockType::STONE) },
		{ GetItemId("stick")},
		{ GetItemId("stick") }
		}, Item{ GetItemId("stone_shovel"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::STONE), int(BlockType::STONE), 0 },
		{ int(BlockType::STONE), GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("stone_axe"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::STONE), int(BlockType::STONE), int(BlockType::STONE) },
		{ 0, GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("stone_pickaxe"), 1 } });
	
	list3x1.push_back(Craft3x1{ {
		{ GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot") },
		{ GetItemId("stick") }
		}, Item{ GetItemId("iron_sword"), 1 } });
	list3x1.push_back(Craft3x1{ { 
		{ GetItemId("iron_ingot") },
		{ GetItemId("stick")},
		{ GetItemId("stick") }
		}, Item{ GetItemId("iron_shovel"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), 0 },
		{ GetItemId("iron_ingot"), GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("iron_axe"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ 0, GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("iron_pickaxe"), 1 } });
	
	list3x1.push_back(Craft3x1{ {
		{ GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot") },
		{ GetItemId("stick") }
		}, Item{ GetItemId("golden_sword"), 1 } });
	list3x1.push_back(Craft3x1{ { 
		{ GetItemId("gold_ingot") },
		{ GetItemId("stick")},
		{ GetItemId("stick") }
		}, Item{ GetItemId("golden_shovel"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), 0 },
		{ GetItemId("gold_ingot"), GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("golden_axe"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ 0, GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("golden_pickaxe"), 1 } });
	
	list3x1.push_back(Craft3x1{ {
		{ GetItemId("diamond") },
		{ GetItemId("diamond") },
		{ GetItemId("stick") }
		}, Item{ GetItemId("golden_sword"), 1 } });
	list3x1.push_back(Craft3x1{ { 
		{ GetItemId("diamond") },
		{ GetItemId("stick")},
		{ GetItemId("stick") }
		}, Item{ GetItemId("golden_shovel"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("diamond"), GetItemId("diamond"), 0 },
		{ GetItemId("diamond"), GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("golden_axe"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("diamond"), GetItemId("diamond"), GetItemId("diamond") },
		{ 0, GetItemId("stick"), 0},
		{ 0, GetItemId("stick"), 0 }
		}, Item{ GetItemId("golden_pickaxe"), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		{ 0, GetItemId("iron_ingot"), 0},
		}, Item{ GetItemId("bucket"), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ 0, GetItemId("iron_ingot"), 0 },
		{ GetItemId("iron_ingot"), GetItemId("redstone"), GetItemId("iron_ingot")},
		{ 0, GetItemId("iron_ingot"), 0},
		}, Item{ GetItemId("compass"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ 0, GetItemId("gold_ingot"), 0 },
		{ GetItemId("gold_ingot"), GetItemId("redstone"), GetItemId("gold_ingot")},
		{ 0, GetItemId("gold_ingot"), 0},
		}, Item{ GetItemId("clock"), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ 0, 0, GetItemId("stick") },
		{ 0, GetItemId("stick"), GetItemId("string") },
		{ GetItemId("stick"), 0, GetItemId("string") },
		}, Item{ GetItemId("clock"), 1 } });

	list2x2.push_back(Craft2x2{ { 
		{ GetItemId("iron_ingot"), 0 },
		{ 0, GetItemId("flint") }
		}, Item{ GetItemId("flint_and_steel"), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("paper"), GetItemId("paper"), GetItemId("paper") },
		{ GetItemId("paper"), GetItemId("compass"), GetItemId("paper") },
		{ GetItemId("paper"), GetItemId("paper"), GetItemId("paper") },
		}, Item{ GetItemId("map"), 1 } });

	list2x2.push_back(Craft2x2{ { 
		{ 0, GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), 0 }
		}, Item{ GetItemId("shears"), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gunpowder"), int(BlockType::SAND), GetItemId("gunpowder") },
		{ int(BlockType::SAND), GetItemId("gunpowder"), int(BlockType::SAND) },
		{ GetItemId("gunpowder"), int(BlockType::SAND), GetItemId("gunpowder") },
		}, Item{ int(BlockType::TNT), 1 } });

	list2x1.push_back(Craft2x1{ { 
		{ int(BlockType::PUMPKIN_CARVED) },
		{ int(BlockType::TORCH) }
		}, Item{ int(BlockType::JACK_O_LANTERN), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gunpowder"), int(BlockType::SAND), GetItemId("gunpowder") },
		{ int(BlockType::SAND), GetItemId("gunpowder"), int(BlockType::SAND) },
		{ GetItemId("gunpowder"), int(BlockType::SAND), GetItemId("gunpowder") },
		}, Item{ int(BlockType::TNT), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		}, Item{ int(BlockType::IRON_BLOCK), 1 } });

	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		}, Item{ int(BlockType::GOLD_BLOCK), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		}, Item{ GetItemId("iron_helmet"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		}, Item{ GetItemId("iron_chestplate"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("iron_ingot"), GetItemId("iron_ingot"), GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		}, Item{ GetItemId("iron_leggings"), 1 } });
	list2x3.push_back(Craft2x3{ {
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		{ GetItemId("iron_ingot"), 0, GetItemId("iron_ingot") },
		}, Item{ GetItemId("iron_boots"), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		}, Item{ GetItemId("golden_helmet"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		}, Item{ GetItemId("golden_chestplate"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("gold_ingot"), GetItemId("gold_ingot"), GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		}, Item{ GetItemId("golden_leggings"), 1 } });
	list2x3.push_back(Craft2x3{ {
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		{ GetItemId("gold_ingot"), 0, GetItemId("gold_ingot") },
		}, Item{ GetItemId("golden_boots"), 1 } });

	list2x3.push_back(Craft2x3{ { 
		{ GetItemId("diamond"), GetItemId("diamond"), GetItemId("diamond") },
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		}, Item{ GetItemId("golden_helmet"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		{ GetItemId("diamond"), GetItemId("diamond"), GetItemId("diamond") },
		{ GetItemId("diamond"), GetItemId("diamond"), GetItemId("diamond") },
		}, Item{ GetItemId("golden_chestplate"), 1 } });
	list3x3.push_back(Craft3x3{ { 
		{ GetItemId("diamond"), GetItemId("diamond"), GetItemId("diamond") },
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		}, Item{ GetItemId("golden_leggings"), 1 } });
	list2x3.push_back(Craft2x3{ {
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		{ GetItemId("diamond"), 0, GetItemId("diamond") },
		}, Item{ GetItemId("golden_boots"), 1 } });

	list2x3.push_back(Craft2x3{ {
		{ int(BlockType::OAK_WOOD_PLANK), 0, int(BlockType::OAK_WOOD_PLANK) },
		{ 0, int(BlockType::OAK_WOOD_PLANK), 0 },
		}, Item{ GetItemId("bowl"), 4 } });

	list1x3.push_back(Craft1x3{ {
		{ GetItemId("wheat"), GetItemId("wheat"), GetItemId("wheat") }
		}, Item{ GetItemId("bread"), 1 } });

	list3x3.push_back(Craft3x3{ {
		{ GetItemId("string"), GetItemId("stick"), 0 },
		{ GetItemId("string"), 0, GetItemId("stick") },
		{ GetItemId("string"), GetItemId("stick"), 0 },
		}, Item{ GetItemId("bow"), 1 } });

	list3x1.push_back(Craft3x1{ {
		{ GetItemId("flint") },
		{ GetItemId("stick") },
		{ GetItemId("feather") },
		}, Item{ GetItemId("arrow"), 4 } });
}

Item Crafting::GetCraftItem2x2(Item _table[][2])
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid && CheckEmptySlot2x2(_table, i, j, Int2{1, 1}))
					return it.output;
			}
		}
	}
	for (auto& it : list2x2)
	{
		bool chk = true;
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk && CheckEmptySlot2x2(_table, 0, 0, Int2{ 2, 2 }))
			return it.output;
	}
	for (auto& it : list2x1)
	{
		for (int i = 0; i < 2; i++) {
			bool chk = true;
			for (int x = 0; x < 2; x++)
			{
				if (it.table[x][0] != _table[x][i + 0].itemid)
					chk = false;
			}
			if (chk && CheckEmptySlot2x2(_table, 0, i, Int2{ 2, 1 }))
				return it.output;
		}
	}
	for (auto& it : list1x2)
	{
		for (int i = 0; i < 2; i++) {
			bool chk = true;
			for (int y = 0; y < 2; y++)
			{
				if (it.table[0][y] != _table[i + 0][y].itemid)
					chk = false;
			}
			if (chk && CheckEmptySlot2x2(_table, i, 0, Int2{ 1, 2 }))
				return it.output;
		}
	}
	return Item{ 0, 0 };
}

Item Crafting::GetCraftItem3x3(Item _table[][3])
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid && CheckEmptySlot3x3(_table, i, j, Int2{ 1, 1 }))
					return it.output;
			}
		}
	}
	for (auto& it : list2x2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 2, 2 }))
					return it.output;
			}
		}
	}
	for (auto& it : list2x1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 1; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 2, 1 }))
					return it.output;
			}
		}
	}
	for (auto& it : list1x2)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 1; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 1, 2 }))
					return it.output;
			}
		}
	}
	for (auto& it : list1x2)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 1; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 1, 2 }))
					return it.output;
			}
		}
	}
	for (auto& it : list1x3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				bool chk = true;
				for (int x = 0; x < 1; x++)
				{
					for (int y = 0; y < 3; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 1, 3 }))
					return it.output;
			}
		}
	}
	for (auto& it : list2x3)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 3; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 2, 3 }))
					return it.output;
			}
		}
	}
	for (auto& it : list3x1)
	{
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				bool chk = true;
				for (int x = 0; x < 3; x++)
				{
					for (int y = 0; y < 1; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 3, 1 }))
					return it.output;
			}
		}
	}
	for (auto& it : list3x2)
	{
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 3; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, Int2{ 3, 2 }))
					return it.output;
			}
		}
	}
	for (auto& it : list3x3)
	{
		bool chk = true;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk && CheckEmptySlot3x3(_table, 0, 0, Int2{ 3, 3 }))
			return it.output;
	}
	return Item{ 0, 0 };
}

void Crafting::MakeCraftItem2x2(Item _table[][2], Item& _outcome)
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid)
				{
					_table[i][j].ea--;
					return;
				}
			}
		}
	}
	for (auto& it : list2x2)
	{
		bool chk = true;
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk) {
			for (int x = 0; x < 2; x++)
			{
				for (int y = 0; y < 2; y++)
					_table[x][y].ea--;
			}
			return;
		}
	}
	for (auto& it : list2x1)
	{
		for (int i = 0; i < 2; i++) {
			bool chk = true;
			for (int x = 0; x < 2; x++)
			{
				if (it.table[x][i] != _table[x][i].itemid)
					chk = false;
			}
			if (chk)
			{
				for (int x = 0; x < 2; x++)
					_table[x][i].ea--;
				return;
			}
		}
	}
	for (auto& it : list1x2)
	{
		for (int i = 0; i < 2; i++) {
			bool chk = true;
			for (int y = 0; y < 2; y++)
			{
				if (it.table[0][y] != _table[i + 0][y].itemid)
					chk = false;
			}
			if (chk)
			{
				for (int y = 0; y < 2; y++)
					_table[i][y].ea--;
				return;
			}
		}
	}
}

void Crafting::MakeCraftItem3x3(Item _table[][3], Item& _outcome)
{
	Int2 _size = { 1, 1 };
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid && CheckEmptySlot3x3(_table, i, j, _size)) {
					_table[i][j].ea--;
					return;
				}
			}
		}
	}
	_size = { 2, 1 };
	for (auto& it : list2x1)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 1, 2 };
	for (auto& it : list1x2)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 2, 2 };
	for (auto& it : list2x2)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 1, 3 };
	for (auto& it : list1x3)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 2, 3 };
	for (auto& it : list2x3)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 3, 1 };
	for (auto& it : list3x1)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 3, 2 };
	for (auto& it : list3x2)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	_size = { 3, 3 };
	for (auto& it : list3x3)
	{
		for (int i = 0; i < 4 - _size.x; i++)
		{
			for (int j = 0; j < 4 - _size.y; j++)
			{
				bool chk = true;
				for (int x = 0; x < _size.x; x++)
				{
					for (int y = 0; y < _size.y; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk && CheckEmptySlot3x3(_table, i, j, _size)) {
					for (int x = 0; x < _size.x; x++)
					{
						for (int y = 0; y < _size.y; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
}

bool Crafting::CheckEmptySlot2x2(Item _table[][2], int _x, int _y, Int2 _size)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i < _x || i >= _x + _size.x || j < _y || j >= _y + _size.y)
			{
				if (_table[i][j].itemid != 0)
					return false;
			}
		}
	}
	return true;
}

bool Crafting::CheckEmptySlot3x3(Item _table[][3], int _x, int _y, Int2 _size)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i < _x || i >= _x + _size.x || j < _y || j >= _y + _size.y)
			{
				if (_table[i][j].itemid != 0)
					return false;
			}
		}
	}
	return true;
}

void Crafting::ShowCraftTable(bool _on)
{
	if (_on)
	{
		for (int i = 0; i < 27; i++)
			INVENTORY->UpdateInven(i, table);
		for (int i = 1; i <= 9; i++)
			INVENTORY->UpdateQuickSlot(i, table);
		UpdateMouse();

		active = true;
	}
	else {
		active = false;
	}
}

int Crafting::GetItemId(const char* _itemName)
{
	return ITEM_MANAGER->GetItemId(_itemName);
}

void Crafting::UpdateCombineSlot(int _slotX, int _slotY)
{
	if (combineSlot[_slotX][_slotY].ea <= 0) {
		table->Find("cItemImg" + to_string((3 * _slotX) + _slotY))->visible = false;
		combineSlot[_slotX][_slotY].Remove();
	}
	else {
		table->Find("cItemImg" + to_string((3 * _slotX) + _slotY))->visible = true;
		ITEM_MANAGER->SetItemImage(table->Find("cItemImg" + to_string((3 * _slotX) + _slotY)), combineSlot[_slotX][_slotY]);
		dynamic_cast<Text*>(table->Find("cItemEa" + to_string((3 * _slotX) + _slotY)))->ChangeText(to_string(combineSlot[_slotX][_slotY].ea));
	}
	outcomeSlot = GetCraftItem3x3(combineSlot);
	UpdateOutcomeSlot();
}

void Crafting::UpdateOutcomeSlot()
{
	if (outcomeSlot.ea <= 0) {
		table->Find("oItemImg")->visible = false;
		outcomeSlot.Remove();
	}
	else {
		table->Find("oItemImg")->visible = true;
		ITEM_MANAGER->SetItemImage(table->Find("oItemImg"), outcomeSlot);
		dynamic_cast<Text*>(table->Find("oItemEa"))->ChangeText(to_string(outcomeSlot.ea));
	}
}



void Crafting::UpdateMouse()
{
	if (mousePick.ea <= 0) {
		mouse->visible = false;
		mousePick.Remove();
	}
	else {
		mouse->visible = true;
		ITEM_MANAGER->SetItemImage(mouse, mousePick);
		dynamic_cast<Text*>(mouse->Find("ea"))->ChangeText(to_string(mousePick.ea));
	}
}

void Crafting::Init()
{
	table = UI::Create("Table");
	table->LoadFile("Ingame/Table.xml");

	mouse = UI::Create("MousePick");
	mouse->LoadFile("Ingame/MousePick.xml");

	LoadData();
	active = false;

	table->Update();
	for (int i = 0; i < 27; i++) {
		UI* temp = UI::Create("slot" + to_string(i));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.37f + float((i % 9) * 0.0925f)) / 0.8999f;
		float _y = (-0.082f - float((i / 9) * 0.175f)) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.00f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("itemImg" + to_string(i));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("itemEa" + to_string(i));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	for (int i = 0; i < 9; i++) {
		UI* temp = UI::Create("qSlot" + to_string(i + 1));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.37f + float((i % 9) * 0.0925f)) / 0.8999f;
		float _y = (-0.645) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.05f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("qItemImg" + to_string(i + 1));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("qItemEa" + to_string(i + 1));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	for (int i = 0; i < 9; i++) {
		UI* temp = UI::Create("cSlot" + to_string(i));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.255f + float((i % 3) * 0.0925f)) / 0.8999f;
		float _y = (0.56f - float((i / 3) * 0.175f)) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.05f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("cItemImg" + to_string(i));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("cItemEa" + to_string(i));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	UI* temp = UI::Create("outcome");
	temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
	temp->scale = { 0.1f, 0.1f, 1.f };
	float _x = (0.225f) / 0.8999f;
	float _y = (0.380f) / 1.6f;
	temp->SetLocalPos({ _x, _y, -0.05f });
	table->AddChild(temp);

	UI* temp2 = UI::Create("oItemImg");
	temp2->material = RESOURCE->materials.Load("Items/100.mtl");
	temp2->scale = { 0.9f, 0.9f, 1.f };
	temp2->SetLocalPos({ 0, 0, -0.1f });
	temp->AddChild(temp2);

	Text* temp3 = Text::Create("oItemEa");
	temp3->scale = { 3.0f, 3.0f, 1.f };
	temp3->fromLeft = false;
	temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
	temp3->ChangeText("10");
	temp2->AddChild(temp3);



	for (int i = 0; i < 27; i++) {
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseOver = [=]() { table->Find("slot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseNotOver = [=]() { table->Find("slot" + to_string(i))->SetLocalPosZ(0.05f); };
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetInvenItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetInvenItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetInvenItem(i), mousePick);
			INVENTORY->UpdateInven(i, table);
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseDownR = [=]() {
			if (INVENTORY->GetInvenItem(i).itemid == 0 and mousePick.itemid != 0)
			{
				INVENTORY->GetInvenItem(i).itemid = mousePick.itemid;
				INVENTORY->GetInvenItem(i).ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and INVENTORY->GetInvenItem(i).itemid != 0)
			{
				mousePick.itemid = INVENTORY->GetInvenItem(i).itemid;
				mousePick.ea = int(INVENTORY->GetInvenItem(i).ea / 2);
				INVENTORY->GetInvenItem(i).ea -= mousePick.ea;
			}
			else if (INVENTORY->GetInvenItem(i).itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				INVENTORY->GetInvenItem(i).ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(INVENTORY->GetInvenItem(i), mousePick);
			INVENTORY->UpdateInven(i, table);
			UpdateMouse(); };
	}
	for (int i = 1; i <= 9; i++) {
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseOver = [=]() { table->Find("qSlot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseNotOver = [=]() { table->Find("qSlot" + to_string(i))->SetLocalPosZ(0.f); };
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetQuickItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetQuickItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetQuickItem(i), mousePick);
			INVENTORY->UpdateQuickSlot(i, table);
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseDownR = [=]() {
			if (INVENTORY->GetQuickItem(i).itemid == 0 and mousePick.itemid != 0)
			{
				INVENTORY->GetQuickItem(i).itemid = mousePick.itemid;
				INVENTORY->GetQuickItem(i).ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and INVENTORY->GetQuickItem(i).itemid != 0)
			{
				mousePick.itemid = INVENTORY->GetQuickItem(i).itemid;
				mousePick.ea = int(INVENTORY->GetQuickItem(i).ea / 2);
				INVENTORY->GetQuickItem(i).ea -= mousePick.ea;
			}
			else if (INVENTORY->GetQuickItem(i).itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				INVENTORY->GetQuickItem(i).ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(INVENTORY->GetQuickItem(i), mousePick);
			INVENTORY->UpdateQuickSlot(i, table);
			UpdateMouse(); };
	}
	for (int i = 0; i < 9; i++) {
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseOver = [=]() { table->Find("cSlot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseNotOver = [=]() { table->Find("cSlot" + to_string(i))->SetLocalPosZ(0.f); };
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseDown = [=]() {
			if (combineSlot[i / 3][i % 3].itemid == mousePick.itemid)
			{
				combineSlot[i / 3][i % 3].ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(combineSlot[i / 3][i % 3], mousePick);
			outcomeSlot = GetCraftItem3x3(combineSlot);
			UpdateCombineSlot(i / 3, i % 3);
			UpdateOutcomeSlot();
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseDownR = [=]() {
			if (combineSlot[i / 3][i % 3].itemid == 0 and mousePick.itemid != 0)
			{
				combineSlot[i / 3][i % 3].itemid = mousePick.itemid;
				combineSlot[i / 3][i % 3].ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and combineSlot[i / 3][i % 3].itemid != 0)
			{
				mousePick.itemid = combineSlot[i / 3][i % 3].itemid;
				mousePick.ea = int(combineSlot[i / 3][i % 3].ea / 2);
				combineSlot[i / 3][i % 3].ea -= mousePick.ea;
			}
			else if (combineSlot[i / 3][i % 3].itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				combineSlot[i / 3][i % 3].ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(combineSlot[i / 3][i % 3], mousePick);
			outcomeSlot = GetCraftItem3x3(combineSlot);
			UpdateCombineSlot(i / 3, i % 3);
			UpdateOutcomeSlot();
			UpdateMouse(); };
	}
	dynamic_cast<UI*>(table->Find("outcome"))->mouseOver = [=]() { table->Find("outcome")->SetLocalPosZ(-0.05f); };
	dynamic_cast<UI*>(table->Find("outcome"))->mouseNotOver = [=]() { table->Find("outcome")->SetLocalPosZ(0.f); };
	dynamic_cast<UI*>(table->Find("outcome"))->mouseDown = [=]() {
		if (outcomeSlot.itemid != 0 && mousePick.itemid == 0) {
			MakeCraftItem3x3(combineSlot, outcomeSlot);
			Util::Swap(outcomeSlot, mousePick);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					UpdateCombineSlot(j, i);
			}
			UpdateOutcomeSlot();
			UpdateMouse();
		}
		else if (outcomeSlot.itemid == mousePick.itemid && mousePick.itemid != 0)
		{
			MakeCraftItem3x3(combineSlot, outcomeSlot);
			mousePick.ea += outcomeSlot.ea;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					UpdateCombineSlot(j, i);
			}
			UpdateOutcomeSlot();
			UpdateMouse();
		}
	};
}

void Crafting::Update()
{
	if (not active)
		return;

	table->Update();

	if (mousePick.itemid != 0)
	{
		mouse->SetLocalPos({ INPUT->NDCPosition.x, INPUT->NDCPosition.y, mouse->GetLocalPos().z });
		mouse->Update();
	}

	if (INPUT->KeyDown(VK_LBUTTON) && not table->MouseOver() && mousePick.itemid != 0)
	{
		ITEM_MANAGER->Spawn(Player::user->GetWorldPos(), mousePick);
		mousePick.Remove();
		UpdateMouse();
	}
}

void Crafting::Render()
{
	if (not active)
		return;

	table->Render();
	mouse->Render();
}

void Crafting::RenderHierarchy()
{
	table->RenderHierarchy();
}

void Crafting::Release()
{
}
