
CMD:createvoucher(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	
	new voucid = Iter_Free(Vouchers), query[128];
	if(voucid == -1) return Error(playerid, "You cant create more voucher!");
	new vip, viptime, gold;
	if(sscanf(params, "ddd", vip, viptime, gold)) return Usage(playerid, "/createvoucher [VIP] [VIP-TIME(Days)] [GOLD]");
	if(vip < 0 || vip > 4) return Error(playerid, "Invalid vip 0-3.");
	if(viptime < 0 || viptime > 60) return Error(playerid, "Invalid vip time 0 - 60 days.");

	new drank[32];
	switch(vip)
	{
		case 1: drank = "Basic Donator";
		case 2: drank = "Advanced Donator";
		case 3: drank = "Professional Donator";
		case 4: drank = "Lifetime Donator";
		default: drank = "{00FF00}None{FFFFFF}";
	}
	switch(vip)
	{
		case 1: {
			VoucData[voucid][voucClaimVIP][0] = 2;
			VoucData[voucid][voucClaimVIP][1] = 1;
			VoucData[voucid][voucClaimVIP][2] = 0;
		}
		case 2: {
			VoucData[voucid][voucClaimVIP][0] = 4;
			VoucData[voucid][voucClaimVIP][1] = 2;
			VoucData[voucid][voucClaimVIP][2] = 1;
		}
		case 3: {
			VoucData[voucid][voucClaimVIP][0] = 6;
			VoucData[voucid][voucClaimVIP][1] = 2;
			VoucData[voucid][voucClaimVIP][2] = 1;
		}
		case 4: {
			VoucData[voucid][voucClaimVIP][0] = 10;
			VoucData[voucid][voucClaimVIP][1] = 2;
			VoucData[voucid][voucClaimVIP][2] = 1;
		}
		default: {
			VoucData[voucid][voucClaimVIP][0] = 0;
			VoucData[voucid][voucClaimVIP][1] = 0;
			VoucData[voucid][voucClaimVIP][2] = 0;
		}
	}
	VoucData[voucid][voucCode] = GenerateRandomVIP();
	VoucData[voucid][voucVIP] = vip;
	VoucData[voucid][voucVIPTime] = viptime;
	VoucData[voucid][voucGold] = gold;
	format(VoucData[voucid][voucAdmin], 16, pData[playerid][pAdminname]);
	format(VoucData[voucid][voucDonature], 16, "None");
	VoucData[voucid][voucClaim] = 0;
	Iter_Add(Vouchers, voucid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO vouchers SET id='%d', code='%s', vip='%d', vip_time='%d', gold='%d', claimvip='%d|%d|%d', admin='%s'", voucid, VoucData[voucid][voucCode], VoucData[voucid][voucVIP], VoucData[voucid][voucVIPTime], VoucData[voucid][voucGold], VoucData[voucid][voucClaimVIP][0], VoucData[voucid][voucClaimVIP][1], VoucData[voucid][voucClaimVIP][2], pData[playerid][pAdminname]);
	mysql_tquery(g_SQL, query, "OnVoucherCreated", "i", voucid);
	
	SendCustomMessage(playerid, "VOUCHER", ""YELLOW_E"%d | code: %s | vip: %s | vip-time: %d | gold: %d  | claims: %d|%d|%d | admin: %s", voucid, VoucData[voucid][voucCode], drank, VoucData[voucid][voucVIPTime], VoucData[voucid][voucGold], VoucData[voucid][voucClaimVIP][0], VoucData[voucid][voucClaimVIP][1], VoucData[voucid][voucClaimVIP][2], pData[playerid][pAdminname]);
	return 1;
}

CMD:giftcode(playerid, params[])
{
	if(sscanf(params, "s[36]", params)) return Usage(playerid, "/giftcode [code]");
	foreach(new vo : Vouchers)
	{
		if(strcmp(params, VoucData[vo][voucCode])) return Error(playerid, "Invalid code.");
		if(VoucData[vo][voucClaim] == 0)
		{
			if(VoucData[vo][voucVIP] == 0)
			{
				pData[playerid][pGold] += VoucData[vo][voucGold];
				VoucData[vo][voucClaim] = 1;
				format(VoucData[vo][voucDonature], 16, pData[playerid][pName]);
				Voucher_Save(vo);
				
				SendCustomMessage(playerid, "REDEEM", ""YELLOW_E"You have successfully claimed voucher "AQUA_E"code %s", VoucData[vo][voucCode]);
			}
			else
			{
				new dayz = VoucData[vo][voucVIPTime];
				pData[playerid][pGold] += VoucData[vo][voucGold];
				pData[playerid][pClaimVIP][0] += VoucData[vo][voucClaimVIP][0];
				pData[playerid][pClaimVIP][1] += VoucData[vo][voucClaimVIP][1];
				pData[playerid][pClaimVIP][2] += VoucData[vo][voucClaimVIP][2];
				pData[playerid][pVip] = VoucData[vo][voucVIP];
				pData[playerid][pVipTime] = gettime() + (dayz * 86400);
				
				VoucData[vo][voucClaim] = 1;
				format(VoucData[vo][voucDonature], 16, pData[playerid][pName]);
				Voucher_Save(vo);
				SendCustomMessage(playerid, "REDEEM", ""YELLOW_E"You have successfully claimed voucher "AQUA_E"code %s", VoucData[vo][voucCode]);
				SendCustomMessage(playerid, "VIP", ""YELLOW_E"You got "AQUA_E"%s "YELLOW_E"expired on: "GREEN_E"%s"YELLOW_E" and Gold: "AQUA_E"%d.", GetVipRank(playerid), GetVipTime(playerid), VoucData[vo][voucGold]);
			}
		}
		else return Error(playerid, "Voucher has been expired!");
	}
	return 1;
}

CMD:redeem(playerid, params[])
{
	if(sscanf(params, "s[36]", params)) return Usage(playerid, "/redeem [code]");
	new query[512];
	format(query, sizeof(query), "SELECT * FROM `vouchers` WHERE `code`='%s'", params);
	new Cache:checkfamily = mysql_query(g_SQL, query);
	
	new rows = cache_num_rows(), name[52], claimvouch, vouchid, vip, viptime, gold, claimvip[52], claim1, claim2, claim3, claimorg;
	
	if(rows)
	{
		cache_get_value_name_int(0, "id", vouchid);
		cache_get_value_name_int(0, "vip", vip);
		cache_get_value_name_int(0, "vip_time", viptime);
		cache_get_value_name_int(0, "gold", gold);
		cache_get_value_name(0, "claimvip", claimvip);
		sscanf(claimvip, "p<|>ddd", claim1, claim2, claim3);
		cache_get_value_name_int(0, "claim", claimorg);
		if(claimorg == 0)
		{
			if(vip == 0)
			{
				pData[playerid][pGold] += gold;
				claimvouch = 1;
				format(name, 16, pData[playerid][pName]);
				SendCustomMessage(playerid, "REDEEM", ""YELLOW_E"You have successfully claimed voucher "AQUA_E"code %s", params);
				new cQuery[512];
				format(cQuery, sizeof(cQuery), "UPDATE vouchers SET donature='%s', claim='%d' WHERE id='%d'",
				name,
				claimvouch,
				vouchid
				);
				mysql_tquery(g_SQL, cQuery);
			}
			else
			{
				new dayz = viptime;
				pData[playerid][pGold] += gold;
				pData[playerid][pClaimVIP][0] += claim1;
				pData[playerid][pClaimVIP][1] += claim2;
				pData[playerid][pClaimVIP][2] += claim3;
				pData[playerid][pVip] = vip;
				pData[playerid][pVipTime] = gettime() + (dayz * 86400);
				
				claimvouch = 1;
				format(name, 16, pData[playerid][pName]);
				new cQuery[512];
				format(cQuery, sizeof(cQuery), "UPDATE vouchers SET donature='%s', claim='%d' WHERE id='%d'",
				name,
				claimvouch,
				vouchid
				);
				mysql_tquery(g_SQL, cQuery);
				SendCustomMessage(playerid, "REDEEM", ""YELLOW_E"You have successfully claimed voucher "AQUA_E"code %s", params);
				SendCustomMessage(playerid, "VIP", ""YELLOW_E"You got "AQUA_E"%s "YELLOW_E"expired on: "GREEN_E"%s"YELLOW_E" and Gold: "AQUA_E"%d.", GetVipRank(playerid), GetVipTime(playerid), gold);
			}
			cache_delete(checkfamily);
		}
		else return Error(playerid, "Voucher has been expired!");
	}
	else return Error(playerid, "Invalid code.");
	return 1;
}


		