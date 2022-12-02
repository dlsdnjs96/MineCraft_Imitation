#include "stdafx.h"



DataBase::DataBase()
{
    conn = nullptr;
	mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "9vn9dw", "minecraft", 3306, NULL, 0);
    if (conn == nullptr)
    {
        cout << "fail to connect" << endl;
    }
    

    WORLD->id = 0;
    SaveItemObject();
}

DataBase::~DataBase()
{
	mysql_close(&mysql);
}



void DataBase::UpdateWolrd()
{
    return;
    string query = "UPDATE world SET last_connected = CURRENT_TIMESTAMP WHERE name = '" + WORLD->name + "'";

    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            WORLD->id = atoi(row[0]);
        }
        else
            cout << "fail to fetch" << endl;
        mysql_free_result(result);
    }
    else {
        cout << "fail to update" << endl;
    }
}

void DataBase::UpdateWolrdId()
{
    string query = "SELECT * FROM world WHERE name = '" + WORLD->name + "'";

    //WORLD->id = -1;
    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            WORLD->id = atoi(row[0]);
        }
        else
            cout << "fail to fetch" << endl;
        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::LoadWolrd()
{
    string query = "SELECT * FROM world WHERE name = '" + WORLD->name + "'";

    WORLD->id = -1;
    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            WORLD->id = atoi(row[0]);
            WORLD->createdDate = row[2];
            WORLD->lastConnected = row[3];
        } else
            cout << "fail to fetch" << endl;
        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SaveWolrd()
{
    string query;
    query = "DELETE FROM world WHERE name = '" + WORLD->name + "'";
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;

    query = "INSERT INTO world(name, created_date, last_connected) VALUES('" + WORLD->name + "', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP)";

    if (mysql_query(conn, query.c_str()) != 0) {
        cout << "fail to insert" << endl;
    }
}

void DataBase::LoadPlayer()
{
    string query = "SELECT * FROM player WHERE worldid = " + to_string(WORLD->id);


    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            PlayerModel::user->state = PLAYER_STATE(atoi(row[2]));
            PlayerModel::user->SetLocalPos({ float(atof(row[3])), float(atof(row[4])), float(atof(row[5])) });
            PlayerModel::user->rotation =  { float(atof(row[6])), float(atof(row[7])), float(atof(row[8])) };
            PlayerModel::user->hp = atoi(row[6]);
            PlayerModel::user->hunger = atoi(row[10]);
        }
        else
            cout << "fail to fetch" << endl;
        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SavePlayer()
{
    string query = "";


    query = "DELETE FROM player WHERE worldid = " + to_string(WORLD->id);
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;


    query = "INSERT INTO player(worldid, state, positionX, positionY, positionZ, rotationX, rotationY, rotationZ, hp, hunger) VALUES(";
    query += to_string(WORLD->id) + ", " + to_string(int(PlayerModel::user->state)) + ", ";
    query += to_string(PlayerModel::user->GetLocalPos().x) + ", " + to_string(PlayerModel::user->GetLocalPos().y) + ", " + to_string(PlayerModel::user->GetLocalPos().z) + ", ";
    query += to_string(PlayerModel::user->rotation.x) + ", " + to_string(PlayerModel::user->rotation.y) + ", " + to_string(PlayerModel::user->rotation.z) + ", ";
    query += to_string(PlayerModel::user->hp) + ", " + to_string(PlayerModel::user->hunger) + ")";


    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to insert" << endl;

}

void DataBase::LoadInventory()
{
    string query = "SELECT * FROM inventory WHERE worldid = " + to_string(WORLD->id);


    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        while ((row = mysql_fetch_row(result)) != NULL) {
            int slot = atoi(row[4]);
            if (slot >= 0)
                INVENTORY->SetInvenItem(slot, Item{ atoi(row[2]), atoi(row[3]) });
            else 
                INVENTORY->SetPickedItem(-slot, Item{ atoi(row[2]), atoi(row[3]) });
        }

        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SaveInventory()
{
    string query = "";

    query = "DELETE FROM inventory WHERE worldid = " + to_string(WORLD->id);
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;


    for (int i = 0;i < 27;i++)
    {
        if (INVENTORY->GetInvenItem(i).itemid == 0)
            continue;

        query = "INSERT INTO inventory(worldid, itemid, ea, slot) VALUES(";
        query += to_string(WORLD->id) + ", " + to_string(INVENTORY->GetInvenItem(i).itemid) + ", ";
        query += to_string(INVENTORY->GetInvenItem(i).ea) + ", " + to_string(i) + ")";

        if (mysql_query(conn, query.c_str()) != 0)
            cout << "fail to insert" << endl;
    }
    for (int i = 1;i < 10;i++)
    {
        if (INVENTORY->GetQuickItem(i).itemid == 0)
            continue;

        query = "INSERT INTO inventory(worldid, itemid, ea, slot) VALUES(";
        query += to_string(WORLD->id) + ", " + to_string(INVENTORY->GetQuickItem(i).itemid) + ", ";
        query += to_string(INVENTORY->GetQuickItem(i).ea) + ", " + to_string(-i) + ")";

        if (mysql_query(conn, query.c_str()) != 0)
            cout << "fail to insert" << endl;
    }
}

void DataBase::LoadItemObject()
{
    string query = "SELECT * FROM itemobject WHERE worldid = " + to_string(WORLD->id);


    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        while ((row = mysql_fetch_row(result)) != NULL) {
            ITEM_MANAGER->Spawn({ float(atof(row[4])), float(atof(row[5])), float(atof(row[6])) }, Item{ atoi(row[2]), atoi(row[3]) }, ItemObjectState(atoi(row[7])));
        }

        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SaveItemObject()
{
    string query = "";

    query = "DELETE FROM itemobject WHERE worldid = "+ to_string(WORLD->id);
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;


    for (auto& it : ITEM_MANAGER->objects)
    {
        query = "INSERT INTO itemobject(worldid, itemid, ea, positionX, positionY, positionZ, state) VALUES(";
        query += to_string(WORLD->id) + ", " + to_string(it->item.itemid) + ", " + to_string(it->item.ea) + ", ";
        query += to_string(it->GetLocalPos().x) + ", " + to_string(it->GetLocalPos().y) + ", " + to_string(it->GetLocalPos().z);
        query += to_string(int(it->state)) + ")";


        if (mysql_query(conn, query.c_str()) != 0)
            cout << "fail to insert" << endl;
    }
    ITEM_MANAGER->objects.clear();
}

void DataBase::LoadMonster()
{
    string query = "SELECT * FROM monster WHERE worldid = " + to_string(WORLD->id);


    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        while ((row = mysql_fetch_row(result)) != NULL) {
            MONSTER_MANAGER->Spawn(MonsterType(atoi(row[2])), { float(atof(row[4])), float(atof(row[5])), float(atof(row[6])) }, MonsterState(atoi(row[3])));
        }

        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SaveMonster()
{
    string query = "";


    query = "DELETE FROM monster WHERE worldid = " + to_string(WORLD->id);
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;


    for (auto& it : MONSTER_MANAGER->monsters)
    {
        for (auto& it2 : it.second) {
            for (auto& it3 : it2.second) {
                query = "INSERT INTO monster(worldid, type, state, positionX, positionY, positionZ) VALUES(";
                query += to_string(WORLD->id) + ", " + to_string(int(it3->type)) + ", " + to_string(int(it3->state)) + ", ";
                query += to_string(it3->GetLocalPos().x) + ", " + to_string(it3->GetLocalPos().y) + ", " + to_string(it3->GetLocalPos().z) + ")";


                if (mysql_query(conn, query.c_str()) != 0)
                    cout << "fail to insert" << endl;
            }
        }
    }
    MONSTER_MANAGER->monsters.clear();
}



void DataBase::LoadFurnace()
{
    string query = "SELECT * FROM furnace WHERE worldid = " + to_string(WORLD->id);


    if (mysql_query(conn, query.c_str()) == 0) {
        result = mysql_store_result(conn);
        while ((row = mysql_fetch_row(result)) != NULL) {
            Furnace* furnace = new Furnace();
            furnace->fire_time = atof(row[4]);
            furnace->progress_time = atof(row[5]);
            furnace->inputSlot = Item{ atoi(row[6]), atoi(row[7]) };
            furnace->outputSlot = Item{ atoi(row[8]), atoi(row[9]) };
            furnace->fuelSlot = Item{ atoi(row[10]), atoi(row[11]) };
            FURNACE_MANAGER->AddFurnace(Int3{ atoi(row[1]), atoi(row[2]), atoi(row[3]) }, furnace);
        }

        mysql_free_result(result);
    }
    else {
        cout << "fail to select" << endl;
    }
}

void DataBase::SaveFurnace()
{
    string query = "";


    query = "DELETE FROM furnace WHERE worldid = " + to_string(WORLD->id);
    if (mysql_query(conn, query.c_str()) != 0)
        cout << "fail to delete" << endl;


    for (auto& it : FURNACE_MANAGER->furnaces)
    {
        for (auto& it2 : it.second) {
            for (auto& it3 : it2.second) {
                query = "INSERT INTO furnace(worldid, posX, posY, posZ, fireT, progressT, inputId, inputEa, outputId, outputEa, fuelId, fuelEa) VALUES(";
                query += to_string(WORLD->id) + ", " + to_string(it.first) + ", " + to_string(it2.first) + ", " + to_string(it3.first) + ", ";
                query += to_string(it3.second->fire_time) + ", " + to_string(it3.second->progress_time) + ", ";
                query += to_string(it3.second->inputSlot.itemid) + ", " + to_string(it3.second->inputSlot.ea) + ", ";
                query += to_string(it3.second->outputSlot.itemid) + ", " + to_string(it3.second->outputSlot.ea) + ", ";
                query += to_string(it3.second->fuelSlot.itemid) + ", " + to_string(it3.second->fuelSlot.ea) + ")";


                if (mysql_query(conn, query.c_str()) != 0)
                    cout << "fail to insert" << endl;
            }
        }
    }
    FURNACE_MANAGER->furnaces.clear();
}
