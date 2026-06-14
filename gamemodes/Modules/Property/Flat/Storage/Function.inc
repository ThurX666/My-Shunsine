
function OnLoadFlatStorage(id) {
  new
    rows = cache_num_rows(),
    str[32],
    slot = cellmin;

  Iter_Init(FlatStorages);
  for (new i = 0; i != rows; i ++) if((slot = Iter_Free(FlatStorages[id])) != cellmin) {
    Iter_Add(FlatStorages[id], slot);

    cache_get_value_int(i, "itemID", FlatStorage[id][slot][rItemID]);
    cache_get_value_int(i, "itemModel", FlatStorage[id][slot][rItemModel]);
    cache_get_value_int(i, "itemQuantity", FlatStorage[id][slot][rItemQuantity]);

    cache_get_value(i, "itemName", str, sizeof(str));
    strpack(FlatStorage[id][slot][rItemName], str, 32 char);
  }
  return 1;
}

function OnFlatLoadWeapon(roomid)
{
  new
    rows = cache_num_rows();

  for (new i = 0; i != rows; i ++) {
    cache_get_value_int(i, "weaponid", FlatRoom[roomid][flatRoomWeapon][i]);
    cache_get_value_int(i, "ammo", FlatRoom[roomid][flatRoomAmmo][i]);
    cache_get_value_int(i, "durability", FlatRoom[roomid][flatRoomDurability][i]);
    cache_get_value_int(i, "typeammo", FlatRoom[roomid][flatRoomTypeAmmo][i]);
  }
  return 1;
}

function OnFlatStorageAdd(roomid, itemid)
{
  FlatStorage[roomid][itemid][rItemID] = cache_insert_id();
  return 1;
}

Flat_ShowItems(playerid, roomid)
{
  if(!Iter_Contains(FlatRooms, roomid))
    return 0;

  static
    string[MAX_FLAT_STORAGE * 32],
    name[32];

  string[0] = 0;

  for (new i = 0; i != MAX_FLAT_STORAGE; i ++)
  {
    if(!Iter_Contains(FlatStorages[roomid], i))
      format(string, sizeof(string), "%sEmpty Slot\n", string);

    else {
      strunpack(name, FlatStorage[roomid][i][rItemName]);

      if(FlatStorage[roomid][i][rItemQuantity] == 1) {
        format(string, sizeof(string), "%s%s\n", string, name);
      }
      else format(string, sizeof(string), "%s%s (%d)\n", string, name, FlatStorage[roomid][i][rItemQuantity]);
    }
  }
  Dialog_Show(playerid, Dialog_FlatItems, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
  return 1;
}

Flat_OpenStorage(playerid, roomid)
{
  if(!Iter_Contains(FlatRooms, roomid))
    return 0;

  new
    items[2],
    string[MAX_FLAT_STORAGE * 32];

  items[0] = Iter_Count(FlatStorages[roomid]);
  for (new i = 0; i < 3; i ++) if(FlatRoom[roomid][flatRoomWeapon][i]) {
    items[1]++;
  }
  format(string, sizeof(string), "Item Storage (%d/%d)\nWeapon Storage (%d/3)\nMoney Safe (%s)", items[0], MAX_FLAT_STORAGE, items[1], FormatMoney(FlatRoom[roomid][flatRoomMoney]));
  Dialog_Show(playerid, Dialog_FlatStorage, DIALOG_STYLE_LIST, "Room Storage", string, "Select", "Cancel");
  return 1;
}

Flat_RemoveAllItems(roomid)
{
  if (!Iter_Contains(FlatRooms, roomid))
    return 0;

  for (new i = 0; i != MAX_FLAT_STORAGE; i ++) {
    FlatStorage[roomid][i][rItemModel] = 0;
    FlatStorage[roomid][i][rItemQuantity] = 0;
  }
  Iter_Clear(FlatStorages[roomid]);

  new query[128];
  mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_storage` WHERE `ID` = '%d'", FlatRoom[roomid][flatRoomID]);
  mysql_tquery(g_SQL, query);
  for (new i = 0; i < 3; i ++) {
    FlatRoom[roomid][flatRoomWeapon][i] = 0;
    FlatRoom[roomid][flatRoomAmmo][i] = 0;
    FlatRoom[roomid][flatRoomDurability][i] = 0;
    FlatRoom[roomid][flatRoomTypeAmmo][i] = 0;
  }
  mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_weapon` WHERE `flatroomid` = '%d'", FlatRoom[roomid][flatRoomID]);
  mysql_tquery(g_SQL, query);
  return 1;
}

GetTypeAmmoFlat(roomid) {
  new type[52];
  for (new i = 0; i < 3; i ++) {
      if(FlatRoom[roomid][flatRoomWeapon][i]) {
          if(FlatRoom[roomid][flatRoomTypeAmmo][i]) {
              format(type, sizeof(type), "%d Surplus", FlatRoom[roomid][flatRoomAmmo][i]);
          }
          else {
              format(type, sizeof(type), "%d", FlatRoom[roomid][flatRoomAmmo][i]);
          }
      }
  }
  return type;
}

Flat_WeaponStorage(playerid, roomid)
{
  if(!Iter_Contains(FlatRooms, roomid))
    return 0;

  new
    string[320];

  for (new i = 0; i < 3; i ++)
  {
    if(!FlatRoom[roomid][flatRoomWeapon][i]) format(string, sizeof(string), "%sEmpty Slot\n", string);
    else format(string, sizeof(string), "%s%s ("YELLOW_E"Ammo: %s"WHITE_E") ("YELLOW_E"Durability: %d"WHITE_E")\n", string, ReturnWeaponName(FlatRoom[roomid][flatRoomWeapon][i]), GetTypeAmmoFlat(roomid), FlatRoom[roomid][flatRoomDurability][i]);
  }
  Dialog_Show(playerid, FlatWeapons, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
  return 1;
}
