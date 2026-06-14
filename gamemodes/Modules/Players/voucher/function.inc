
function LoadVouchers()
{
    new voucid, admin[16], code[52], donature[16], claimvip[52];
	
	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", voucid);
			cache_get_value_name(i, "code", code);
			format(VoucData[voucid][voucCode], 52, code);
			cache_get_value_name_int(i, "vip", VoucData[voucid][voucVIP]);
			cache_get_value_name_int(i, "vip_time", VoucData[voucid][voucVIPTime]);
			cache_get_value_name_int(i, "gold", VoucData[voucid][voucGold]);
			cache_get_value_name(0, "claimvip", claimvip);
			sscanf(claimvip, "p<|>ddd", VoucData[voucid][voucClaimVIP][0], VoucData[voucid][voucClaimVIP][1], VoucData[voucid][voucClaimVIP][2]);
			cache_get_value_name(i, "admin", admin);
			format(VoucData[voucid][voucAdmin], 16, admin);
			cache_get_value_name(i, "donature", donature);
			format(VoucData[voucid][voucDonature], 16, donature);
			cache_get_value_name_int(i, "claim", VoucData[voucid][voucClaim]);
			Iter_Add(Vouchers, voucid);
		}
		printf("*** [Database: Loaded] voucher data (%d count).", rows);
	}
}
	
Voucher_Save(voucid)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE vouchers SET code='%s', vip='%d', vip_time='%d', gold='%d', claimvip='%d|%d|%d', admin='%s', donature='%s', claim='%d' WHERE id='%d'",
	VoucData[voucid][voucCode],
	VoucData[voucid][voucVIP],
	VoucData[voucid][voucVIPTime],
	VoucData[voucid][voucGold],
	VoucData[voucid][voucClaimVIP][0], 
	VoucData[voucid][voucClaimVIP][1], 
	VoucData[voucid][voucClaimVIP][2],
	VoucData[voucid][voucAdmin],
	VoucData[voucid][voucDonature],
	VoucData[voucid][voucClaim],
	voucid
	);
	return mysql_tquery(g_SQL, cQuery);
}

function OnVoucherCreated(voucid)
{
	Voucher_Save(voucid);
	return 1;
}
