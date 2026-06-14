
alias:salary("mysalary")

CMD:salary(playerid, params[])
{
	if(pData[playerid][pPaycheck] < 0) return Error(playerid, "Sekarang belum waktunya anda mengambil paycheck.");
	DisplaySalary(playerid);
	return 1;
}
