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
    {"taxi_payout",        5000,     5000,     "Taxi 15min duty payout ($50.00)"},
    {"mechanic_payout",    5000,     5000,     "Mechanic 15min duty payout ($50.00)"},
    {"courier_packet",     3300,     3300,     "Courier per packet ($33.00)"},
    {"bus_lap",            5000,     5000,     "Bus per lap ($50.00)"},
    {"trucker_cargo",      6700,     6700,     "Trucker per cargo ($67.00)"},
    {"trucker_crate",      2000,     2000,     "Trucker per crate ($20.00)"},
    {"lumber_item",        200,      200,      "Lumber per item ($2.00)"},
    {"milker_cycle",       6700,     6700,     "Milker 10 cycles ($67.00)"},
    {"farmer_unit",        200,      200,      "Farmer per unit ($2.00)"},
    {"faction_duty",       20000,    20000,    "Faction 60min duty ($200.00)"},
    {"fuel_price",         5,        5,        "Fuel per unit ($0.05)"},
    {"toll_price",         2000,     2000,     "Toll price ($20.00)"},
    {"fish_price",         500,      500,      "Fish per lb ($5.00)"}
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


