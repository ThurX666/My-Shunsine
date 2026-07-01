// Economy Configuration System v1.1.0

#define MAX_ECONOMY_KEYS 13

enum E_ECONOMY_DATA
{
    e_EconomyKey[32],
    e_EconomyValue,
    e_EconomyDefault,
    e_EconomyDesc[64]
};

new g_Economy[MAX_ECONOMY_KEYS][E_ECONOMY_DATA] =
{
    {"taxi_payout",        1500,     1500,     "Taxi 15min duty payout"},
    {"mechanic_payout",    1500,     1500,     "Mechanic 15min duty payout"},
    {"courier_packet",     25000,    25000,    "Courier per packet"},
    {"bus_lap",            15000,    15000,    "Bus per lap"},
    {"trucker_cargo",      25000,    25000,    "Trucker per cargo"},
    {"trucker_crate",      1250,     1250,     "Trucker per crate"},
    {"lumber_item",        150,      150,      "Lumber per item"},
    {"milker_cycle",       25000,    25000,    "Milker 10 cycles"},
    {"farmer_unit",        150,      150,      "Farmer per unit"},
    {"faction_duty",       50000,    50000,    "Faction 60min duty"},
    {"fuel_price",         2,        2,        "Fuel per unit (cents)"},
    {"toll_price",         5000,     5000,     "Toll price"},
    {"fish_price",         500,      500,      "Fish per lb (cents)"}
};

stock GetEconomyValue(const key[])
{
    for(new i = 0; i < MAX_ECONOMY_KEYS; i++)
    {
        if(!strcmp(g_Economy[i][e_EconomyKey], key, true))
            return g_Economy[i][e_EconomyValue];
    }
    return 0;
}

stock SetEconomyValue(const key[], value)
{
    for(new i = 0; i < MAX_ECONOMY_KEYS; i++)
    {
        if(!strcmp(g_Economy[i][e_EconomyKey], key, true))
        {
            g_Economy[i][e_EconomyValue] = value;
            new query[256];
            mysql_format(g_SQL, query, sizeof(query),
                "INSERT INTO `economy_config` (`key`, `value`) VALUES ('%e', '%d') ON DUPLICATE KEY UPDATE `value` = '%d'",
                key, value, value);
            mysql_tquery(g_SQL, query);
            return 1;
        }
    }
    return 0;
}

function LoadEconomyConfig()
{
    new cache_rows = cache_num_rows();
    if(cache_rows > 0)
    {
        new key[32], value;
        for(new i = 0; i < cache_rows; i++)
        {
            cache_get_value_name(i, "key", key, 32);
            cache_get_value_name_int(i, "value", value);
            for(new j = 0; j < MAX_ECONOMY_KEYS; j++)
            {
                if(!strcmp(g_Economy[j][e_EconomyKey], key, true))
                {
                    g_Economy[j][e_EconomyValue] = value;
                    break;
                }
            }
        }
    }
    printf("[Economy] Loaded %d config keys.", cache_rows);
    return 1;
}


