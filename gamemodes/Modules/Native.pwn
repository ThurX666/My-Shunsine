
//----------[ Native Login Register]----------


UpdatePlayerData(playerid)
{
	if(pData[playerid][IsLoggedIn] == false) return 0;
	
	if (IsPlayerInEvent(playerid)) {
		ResetPlayerWeapons(playerid);
		eventTeams[playerid] = TEAM_NONE;
		SetPlayerTeam(playerid, NO_TEAM);
		pData[playerid][pHealth] = pData[playerid][pEventHealth];
		pData[playerid][pArmour] = pData[playerid][pEventArmour];
		pData[playerid][pPosX] = pData[playerid][pPos][0];
		pData[playerid][pPosY] = pData[playerid][pPos][1];
		pData[playerid][pPosZ] = pData[playerid][pPos][2];
		pData[playerid][pPosA] = pData[playerid][pPos][3];
		pData[playerid][pInt] = pData[playerid][pIntEvent];
		pData[playerid][pWorld] = pData[playerid][pWorldEvent];
	} else {
		if(pData[playerid][pAdminDuty] == 1)
		{
			pData[playerid][pHealth] = HealthDuty[playerid];
			GetPlayerArmour(playerid, pData[playerid][pArmour]);
			GetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
			GetPlayerFacingAngle(playerid, pData[playerid][pPosA]);
			pData[playerid][pInt] = GetPlayerInterior(playerid);
			pData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
		}
		else
		{
			pData[playerid][pInt] = GetPlayerInterior(playerid);
			pData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			GetPlayerHealth(playerid, pData[playerid][pHealth]);
			GetPlayerArmour(playerid, pData[playerid][pArmour]);
			GetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
			GetPlayerFacingAngle(playerid, pData[playerid][pPosA]);
		}
	}
	
	new cQuery[5000], PlayerIP[16];
	GetPlayerIp(playerid, PlayerIP, sizeof(PlayerIP));
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `players` SET ");
	for (new i = 0; i != 13; i ++) {
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Gun%d` = '%d', ", cQuery, i+1, PlayerGuns[playerid][i][weapon_id]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Ammo%d` = '%d', ", cQuery, i+1, PlayerGuns[playerid][i][weapon_ammo]);
	}
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`AmmoType` = '%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d', ", cQuery, 
	PlayerGuns[playerid][0][weapon_typesurplus], PlayerGuns[playerid][1][weapon_typesurplus], PlayerGuns[playerid][2][weapon_typesurplus],
	PlayerGuns[playerid][3][weapon_typesurplus], PlayerGuns[playerid][4][weapon_typesurplus], PlayerGuns[playerid][5][weapon_typesurplus],
	PlayerGuns[playerid][6][weapon_typesurplus], PlayerGuns[playerid][7][weapon_typesurplus], PlayerGuns[playerid][8][weapon_typesurplus],
	PlayerGuns[playerid][9][weapon_typesurplus], PlayerGuns[playerid][10][weapon_typesurplus], PlayerGuns[playerid][11][weapon_typesurplus],
	PlayerGuns[playerid][12][weapon_typesurplus]);
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`adminname` = '%e', ", cQuery, pData[playerid][pAdminname]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ucpname` = '%e', ", cQuery, charData[playerid][cName]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ip` = '%s', ", cQuery, PlayerIP);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`division` = '%d', ", cQuery, pData[playerid][pDivision]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`admin` = '%d', ", cQuery, pData[playerid][pAdmin]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`admintime` = '%d', ", cQuery, pData[playerid][pAdminTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`helper` = '%d', ", cQuery, pData[playerid][pHelper]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`level` = '%d', ", cQuery, pData[playerid][pLevel]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`levelup` = '%d', ", cQuery, pData[playerid][pLevelUp]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cschar` = '%d', ", cQuery, pData[playerid][pCS]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`vip` = '%d', ", cQuery, pData[playerid][pVip]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`vip_time` = '%d', ", cQuery, pData[playerid][pVipTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gold` = '%d', ", cQuery, pData[playerid][pGold]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`money` = '%d', ", cQuery, pData[playerid][pMoney]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`bmoney` = '%d', ", cQuery, pData[playerid][pBankMoney]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`brek` = '%d', ", cQuery, pData[playerid][pBankRek]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`phone` = '%d', ", cQuery, pData[playerid][pPhone]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`phonestatus` = '%d', ", cQuery, pData[playerid][pPhoneStatus]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`phonekuota` = '%d', ", cQuery, pData[playerid][pKuota]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`phonecredit` = '%d', ", cQuery, pData[playerid][pPhoneCredit]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`phonebook` = '%d', ", cQuery, pData[playerid][pPhoneBook]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`twitter` = '%d', ", cQuery, pData[playerid][pTwitter]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`twitterstatus` = '%d', ", cQuery, pData[playerid][pTwitterStatus]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`wt` = '%d', ", cQuery, pData[playerid][pWT]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`hours` = '%d', ", cQuery, pData[playerid][pHours]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`minutes` = '%d', ", cQuery, pData[playerid][pMinutes]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seconds` = '%d', ", cQuery, pData[playerid][pSeconds]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`paycheck` = '%d', ", cQuery, pData[playerid][pPaycheck]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`skin` = '%d', ", cQuery, pData[playerid][pSkin]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`facskin` = '%d', ", cQuery, pData[playerid][pFacSkin]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gender` = '%d', ", cQuery, pData[playerid][pGender]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`newp` = '%d', ", cQuery, pData[playerid][pnewplayer]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`age` = '%s', ", cQuery, pData[playerid][pAge]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`posx` = '%f', ", cQuery, pData[playerid][pPosX]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`posy` = '%f', ", cQuery, pData[playerid][pPosY]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`posz` = '%f', ", cQuery, pData[playerid][pPosZ]+0.3);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`posa` = '%f', ", cQuery, pData[playerid][pPosA]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`interior` = '%d', ", cQuery, pData[playerid][pInt]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`world` = '%d', ", cQuery, pData[playerid][pWorld]);
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`health` = '%f', ", cQuery, pData[playerid][pHealth]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`armour` = '%f', ", cQuery, pData[playerid][pArmour]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`maxhealth` = '%f', ", cQuery, pData[playerid][pMaxHealth]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`hunger` = '%.1f', ", cQuery, pData[playerid][pHunger]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`energy` = '%.1f', ", cQuery, pData[playerid][pEnergy]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`sick` = '%d', ", cQuery, pData[playerid][pSick]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`hospital` = '%d', ", cQuery, pData[playerid][pHospital]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`injured` = '%d', ", cQuery, pData[playerid][pInjured]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`duty` = '%d', ", cQuery, pData[playerid][pOnDuty]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`dutytime` = '%d', ", cQuery, pData[playerid][pOnDutyTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`faction` = '%d', ", cQuery, pData[playerid][pFaction]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`factionrank` = '%d', ", cQuery, pData[playerid][pFactionRank]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`factionlead` = '%d', ", cQuery, pData[playerid][pFactionLead]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`family` = '%d', ", cQuery, pData[playerid][pFamily]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`familyrank` = '%d', ", cQuery, pData[playerid][pFamilyRank]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`jail` = '%d', ", cQuery, pData[playerid][pJail]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`jail_time` = '%d', ", cQuery, pData[playerid][pJailTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`arrest` = '%d', ", cQuery, pData[playerid][pArrest]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`arrest_time` = '%d', ", cQuery, pData[playerid][pArrestTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`warn` = '%d', ", cQuery, pData[playerid][pWarn]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`job` = '%d', ", cQuery, pData[playerid][pJob]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`job2` = '%d', ", cQuery, pData[playerid][pJob2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`exitjob` = '%d', ", cQuery, pData[playerid][pExitJob]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`taxitime` = '%d', ", cQuery, pData[playerid][pTaxiTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`medicine` = '%d', ", cQuery, pData[playerid][pMedicine]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`medkit` = '%d', ", cQuery, pData[playerid][pMedkit]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`mask` = '%d', ", cQuery, pData[playerid][pMask]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`helmet` = '%d', ", cQuery, pData[playerid][pHelmet]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`snack` = '%d', ", cQuery, pData[playerid][pSnack]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`sprunk` = '%d', ", cQuery, pData[playerid][pSprunk]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gas` = '%d', ", cQuery, pData[playerid][pGas]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`bandage` = '%d', ", cQuery, pData[playerid][pBandage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gps` = '%d', ", cQuery, pData[playerid][pGPS]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`material` = '%d', ", cQuery, pData[playerid][pMaterial]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`component` = '%d', ", cQuery, pData[playerid][pComponent]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`food` = '%d', ", cQuery, pData[playerid][pFood]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seedwheat` = '%d', ", cQuery, pData[playerid][pSeedWheat]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seedonion` = '%d', ", cQuery, pData[playerid][pSeedOnion]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seedcarrot` = '%d', ", cQuery, pData[playerid][pSeedCarrot]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seedpotato` = '%d', ", cQuery, pData[playerid][pSeedPotato]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`seedcorn` = '%d', ", cQuery, pData[playerid][pSeedCorn]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`wheat` = '%d', ", cQuery, pData[playerid][pWheat]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`onion` = '%d', ", cQuery, pData[playerid][pOnion]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`carrot` = '%d', ", cQuery, pData[playerid][pCarrot]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`potato` = '%d', ", cQuery, pData[playerid][pPotato]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`corn` = '%d', ", cQuery, pData[playerid][pCorn]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`price1` = '%d', ", cQuery, pData[playerid][pPrice1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`price2` = '%d', ", cQuery, pData[playerid][pPrice2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`price3` = '%d', ", cQuery, pData[playerid][pPrice3]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`price4` = '%d', ", cQuery, pData[playerid][pPrice4]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`crack` = '%d', ", cQuery, pData[playerid][pCrack]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`pot` = '%d', ", cQuery, pData[playerid][pPot]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plant` = '%d', ", cQuery, pData[playerid][pPlant]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plant_time` = '%d', ", cQuery, pData[playerid][pPlantTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fishtool` = '%d', ", cQuery, pData[playerid][pFishTool]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fish0` = '%.1f', ", cQuery, FishWeight[playerid][0]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fish1` = '%.1f', ", cQuery, FishWeight[playerid][1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fish2` = '%.1f', ", cQuery, FishWeight[playerid][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fish3` = '%.1f', ", cQuery, FishWeight[playerid][3]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fish4` = '%.1f', ", cQuery, FishWeight[playerid][4]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`worm` = '%d', ", cQuery, pData[playerid][pWorm]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`drivelic` = '%d', ", cQuery, pData[playerid][pDriveLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`drivelic_time` = '%d', ", cQuery, pData[playerid][pDriveLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`flylic` = '%d', ", cQuery, pData[playerid][pFlyLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`flylic_time` = '%d', ", cQuery, pData[playerid][pFlyLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`boatlic` = '%d', ", cQuery, pData[playerid][pBoatLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`boatlic_time` = '%d', ", cQuery, pData[playerid][pBoatLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gunlic` = '%d', ", cQuery, pData[playerid][pGunLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gunlic_time` = '%d', ", cQuery, pData[playerid][pGunLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trucker` = '%d', ", cQuery, pData[playerid][pTruckerLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trucker_time` = '%d', ", cQuery, pData[playerid][pTruckerLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`lumber` = '%d', ", cQuery, pData[playerid][pLumberLic]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`lumber_time` = '%d', ", cQuery, pData[playerid][pLumberLicTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`hbemode` = '%d', ", cQuery, pData[playerid][pHBEMode]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togpm` = '%d', ", cQuery, pData[playerid][pTogPM]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togads` = '%d', ", cQuery, pData[playerid][pTogAds]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togwt` = '%d', ", cQuery, pData[playerid][pTogWT]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togglobalooc` = '%d', ", cQuery, pData[playerid][pTogGlobalOoc]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togquizvote` = '%d', ", cQuery, pData[playerid][pTogQuizVote]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togstaffquestion` = '%d', ", cQuery, pData[playerid][pTogStaffQuestion]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togstaffreport` = '%d', ", cQuery, pData[playerid][pTogStaffReport]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togstaffchat` = '%d', ", cQuery, pData[playerid][pTogStaffChat]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togfaction` = '%d', ", cQuery, pData[playerid][pTogFaction]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togradio` = '%d', ", cQuery, pData[playerid][pTogRadio]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togpaycheck` = '%d', ", cQuery, pData[playerid][pTogPaycheck]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togseatbelt` = '%d', ", cQuery, pData[playerid][pTogSealtbelt]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togchat` = '%d', ", cQuery, pData[playerid][pTogChat]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`toghelmet` = '%d', ", cQuery, pData[playerid][pTogHelmet]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togmask` = '%d', ", cQuery, pData[playerid][pTogMask]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`togammo` = '%d', ", cQuery, pData[playerid][pTogAmmo]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`pbanned` = '%d', ", cQuery, pData[playerid][pBanned]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`pbanreason` = '%s', ", cQuery, pData[playerid][pBanReason]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`pbanby` = '%s', ", cQuery, pData[playerid][pBanBy]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`workshop` = '%d', ", cQuery, pData[playerid][pWorkshop]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`workshoprank` = '%d', ", cQuery, pData[playerid][pWorkshopRank]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`rokok` = '%d', ", cQuery, pData[playerid][pRokok]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cgun` = '%d', ", cQuery, pData[playerid][pCgun]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fightstyle` = '%d', ", cQuery, pData[playerid][FightStyle]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`married` = '%d', ", cQuery, pData[playerid][pMarried]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`marriedto` = '%e', ", cQuery, pData[playerid][pMarriedTo]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`paytoll` = '%d', ", cQuery, pData[playerid][pPayToll]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`apart` = '%d', ", cQuery, pData[playerid][pApart]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ladang` = '%d', ", cQuery, pData[playerid][pLadang]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ladangrank` = '%d', ", cQuery, pData[playerid][pLadangRank]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`maskid` = '%d', ", cQuery, pData[playerid][pMaskID]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`mutewt` = '%d', ", cQuery, pData[playerid][pMuteWt]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`skillbuilder` = '%d', ", cQuery, pData[playerid][pSkillBuilder]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`skillmecha` = '%d', ", cQuery, pData[playerid][pSkillMecha]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`rentveh` = '%d', ", cQuery, pData[playerid][pRents]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`accent` = '%d', ", cQuery, pData[playerid][pAccent1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`furnstore` = '%d', ", cQuery, pData[playerid][pFurnStore]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`GYMMember` = '%d|%d', ", cQuery, pData[playerid][pGYMMember], pData[playerid][pGYMMemberTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`FitnessRating` = '%f|%f|%f|%f|%f|%f', ", cQuery, pData[playerid][pFitnessRating][0], pData[playerid][pFitnessRating][1], pData[playerid][pFitnessRating][2], pData[playerid][pFitnessRating][3], pData[playerid][pFitnessRating][4], pData[playerid][pFitnessRating][5]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Cough` = '%d|%d', ", cQuery, pData[playerid][pCough], pData[playerid][pCoughPills]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Fever` = '%d|%d|%d', ", cQuery, pData[playerid][pFever], pData[playerid][pFiverPills], pData[playerid][pFeverUsed]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Migrain` = '%d|%d|%d|%d', ", cQuery, pData[playerid][pMigrainTime], pData[playerid][pMigrainRate], pData[playerid][pMigrainPills], pData[playerid][pMigrainUsed]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`UsePills` = '%d', ", cQuery, pData[playerid][pUsePills]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Badge` = '%s|%s', ", cQuery, pData[playerid][pBadge], pData[playerid][pFactionRankName]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`InInt` = '%d|%d|%d|%d', ", cQuery, pData[playerid][pInDoor], pData[playerid][pInHouse], pData[playerid][pInBiz], pData[playerid][pInFlat]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`scoreskill` = '%d|%d|%d|%d', ", cQuery, pData[playerid][pScoreTrucker], pData[playerid][pScoreFishing], pData[playerid][pScoreMecha], pData[playerid][pScoreFarmer]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`skilljob` = '%d|%d|%d|%d', ", cQuery, pData[playerid][pSkillTrucker], pData[playerid][pSkillFishing], pData[playerid][pSkillMecha], pData[playerid][pSkillFarmer]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`streamer` = '%d', ", cQuery, pData[playerid][pStreamer]);	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`claimvip` = '%d|%d|%d', ", cQuery, pData[playerid][pClaimVIP][0], pData[playerid][pClaimVIP][1], pData[playerid][pClaimVIP][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`schematicgun` = '%d|%d|%d|%d|%d|%d', ", cQuery, pData[playerid][pSchematic][0], pData[playerid][pSchematic][1], pData[playerid][pSchematic][2], pData[playerid][pSchematic][3], pData[playerid][pSchematic][4], pData[playerid][pSchematic][5]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`skillweapon` = '%d|%d|%d|%d|%d', ", cQuery, pData[playerid][pSkillWeapon][0], pData[playerid][pSkillWeapon][1], pData[playerid][pSkillWeapon][2], pData[playerid][pSkillWeapon][3], pData[playerid][pSkillWeapon][4]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`TogAuto` = '%d|%d|%d|%d|%d|%d|%d|%d', ", cQuery, pData[playerid][pTogPaycheck], pData[playerid][pTogHandbrake], pData[playerid][pTogHelmet], pData[playerid][pRadioStream], pData[playerid][pTogChat], pData[playerid][pTogMask], pData[playerid][pTogSealtbelt], pData[playerid][pTogHandbrake], pData[playerid][pTogAmmo]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Toggle` = '%d|%d|%d|%d|%d', ", cQuery, TogglePlayer[playerid][ToggleDate], TogglePlayer[playerid][ToggleTime], TogglePlayer[playerid][ToggleMoney], TogglePlayer[playerid][ToggleGPS], TogglePlayer[playerid][ToggleWeb]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Delay` = '%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d', ", cQuery, DelayPlayer[playerid][DelaySweeper], DelayPlayer[playerid][DelayTrashmaster], DelayPlayer[playerid][DelayCourier], 
	DelayPlayer[playerid][DelayBusDriver], DelayPlayer[playerid][DelayForklift], DelayPlayer[playerid][DelayFishing], DelayPlayer[playerid][DelayDelivery],
	DelayPlayer[playerid][DelayHauling], DelayPlayer[playerid][DelayLumberJack], DelayPlayer[playerid][DelaySmuggler], DelayPlayer[playerid][DelayWeaponCreate], 
	DelayPlayer[playerid][DelayTraining], DelayPlayer[playerid][DelayAdvertisement], DelayPlayer[playerid][DelayMiner]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Bush` = '%d|%d', ", cQuery, DelayPlayer[playerid][DelayForager], pData[playerid][pBushForager]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`starterpack` = '%d', ", cQuery, pData[playerid][pStarterPack]);

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`last_login` = CURRENT_TIMESTAMP() WHERE `reg_id` = '%d'", cQuery, pData[playerid][pID]);
	mysql_tquery(g_SQL, cQuery);
	foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) {
		hData[i][hLastVisited] = gettime();
		House_Save(i);
	}

	for (new i = 0; i != MAX_BISNIS; i ++) if (Player_OwnsBisnis(playerid, i)) {
		bData[i][bLastVisited] = gettime();
		Bisnis_Save(i);
	}
	// foreach (new i : WORKSHOPS) if (pData[playerid][pWorkshop] == i && pData[playerid][pWorkshopRank] == 6) {
	// 	wData[i][wLastVisited] = gettime();
	// 	Workshop_Save(i);
	// }
	foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) {
		FlatRoom[i][flatRoomLastVisited] = gettime();
		FlatRoom_Save(i);
	}
	UpdateCharData(playerid);
	return 1;
}

UpdateCharData(playerid)
{
	new cQuery[3048];

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `ucp` SET ");
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName` = '%d', ", cQuery, charData[playerid][cCharName]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName2` = '%d', ", cQuery, charData[playerid][cCharName2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName3` = '%d' ", cQuery, charData[playerid][cCharName3]);
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `username` = '%s'", cQuery, charData[playerid][cName]);
	mysql_tquery(g_SQL, cQuery);
	return 1;
}

SetPlayerHunger(playerid, Float:hunger)
{
    pData[playerid][pHunger] = hunger;

    if(pData[playerid][pHunger] > 100)
        pData[playerid][pHunger] = 100;

    else if(pData[playerid][pHunger] < 0)
        pData[playerid][pHunger] = 0;
    return 1;
}

SetPlayerEnergy(playerid, Float:energi)
{
    pData[playerid][pEnergy] = energi;

    if(pData[playerid][pEnergy] > 100)
        pData[playerid][pEnergy] = 100;

    else if(pData[playerid][pEnergy] < 0)
        pData[playerid][pEnergy] = 0;

    return 1;
}

ResetVariables(playerid)
{
	static const empty_player[E_PLAYERS];
	pData[playerid] = empty_player;
	pData[playerid][pLevel] = 1;
	pData[playerid][pActivityTime] = -1;
	pData[playerid][pActivity] = -1;
	pData[playerid][pRconAttemp] = -1;
	pData[playerid][IsLoggedIn] = false;
	pData[playerid][pHealth] = 100.0;
	pData[playerid][pArmour] = 0.0;
	pData[playerid][pMaxHealth] = 100.0;
	pData[playerid][pSpec] = -1;
	pData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
	pData[playerid][pFlareActive] = false;
	pData[playerid][pAdoActive] = false;
	pData[playerid][pNewsGuest] = INVALID_PLAYER_ID;
	pData[playerid][pFindEms] = INVALID_PLAYER_ID;
	pData[playerid][pOffer] = -1;
	pData[playerid][pFill] = -1;
	pData[playerid][nspectOffer] = INVALID_PLAYER_ID;
	//Time
	pData[playerid][pSeconds] = pData[playerid][pMinutes] = pData[playerid][pHours] = 0;
	//Maried
	pData[playerid][pMarriedAccept] = INVALID_PLAYER_ID;	
	pData[playerid][pMarriedCancel] = INVALID_PLAYER_ID;	
	//Animation
	gPlayerUsingLoopingAnim[playerid] = 0;
	gPlayerAnimLibsPreloaded[playerid] = 0;
	//Contatc
	for (new i = 0; i != MAX_CONTACTS; i ++) {
	    ContactData[playerid][i][contactExists] = false;
	    ContactData[playerid][i][contactID] = 0;
	    ContactData[playerid][i][contactNumber] = 0;
	    ListedContacts[playerid][i] = -1;
	}
	//DYOC
	for (new i = 0; i != MAX_ACC; i ++) if(AccData[playerid][i][accExists]) {
        AccData[playerid][i][accExists] = false;
        AccData[playerid][i][accID] = 0;
        AccData[playerid][i][accModel] = 0;
        AccData[playerid][i][accBone] = 1;
        AccData[playerid][i][accShow] = 0;

        AccData[playerid][i][accColor1][0] = AccData[playerid][i][accColor1][1] = AccData[playerid][i][accColor1][2] = 0;
        AccData[playerid][i][accColor2][0] = AccData[playerid][i][accColor2][1] = AccData[playerid][i][accColor2][2] = 0;

        AccData[playerid][i][accOffset][0] = AccData[playerid][i][accOffset][1] = AccData[playerid][i][accOffset][2] = 0.0;
        AccData[playerid][i][accRot][0] = AccData[playerid][i][accRot][1] = AccData[playerid][i][accRot][2] = 0.0;
        AccData[playerid][i][accScale][0] = AccData[playerid][i][accScale][1] = AccData[playerid][i][accScale][2] = 0.0;
    }
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	//Accesories
	pData[playerid][pAksesoris] = EditingWeapon[playerid] = -1;
	//Other
	AimbotWarnings[playerid] = 0;
	// pData[playerid][pPemberitahuan] = 0;
	pData[playerid][pBunnyHopTick] = 0;
	pData[playerid][pUsedFlashlight] =0;
	pData[playerid][pListitems] = -1;
	Jump[playerid] = 0;
	pData[playerid][pNameTag] = Text3D:INVALID_3DTEXT_ID;
	pData[playerid][pMaskOn] = 0;
	pData[playerid][pUndercover] = 0;
	SetPVarInt(playerid, "GiveUptime", 0);
	ResetVariableTazer(playerid);
	StopStream(playerid);
	for(new idx = 0; idx < 100; idx++) 	gListedItems[playerid][idx] = -1;
	ResetNameTag(playerid);
	for(new i = 0; i < 3; i++)
	{
		BusSteps[playerid][i] = 0;
		BusCDSteps[playerid][i] = 0;
	}
	//Sweeper
	KerjaSweeper[playerid] = -1;
	for(new i = 0; i < 4; i++)
	{
		SweeperSteps[playerid][i] = 0;
	}
	//Training
	TrainingSelectWeap[playerid] = -1;
	CountTraining[playerid] = 0;
	IsTraining[playerid] = 0;
	TimeTraning[playerid] = 0;
	//UCP
	format(charData[playerid][cChar1], 52, "None");
	charData[playerid][cCharLevel1] = 0;
	format(charData[playerid][cCharLastLogin1], 52, "None");
	format(charData[playerid][cChar2], 52, "None");
	charData[playerid][cCharLevel2] = 0;
	format(charData[playerid][cCharLastLogin2], 52, "None");
	format(charData[playerid][cChar3], 52, "None");
	charData[playerid][cCharLevel3] = 0;
	format(charData[playerid][cCharLastLogin3], 52, "None");
	//HBE
	pData[playerid][fuelbar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][damagebar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][hungrybar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][energybar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][healtbar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][armorbar] = INVALID_PLAYER_BAR_ID;
	pData[playerid][pHBEMode] = 1;
	//Job
	pData[playerid][pHarvestID] = -1;
	pData[playerid][pDelayCrate] = 0;
	pData[playerid][pCrate] = 0;
	pData[playerid][pCrateType] = 0;
	pData[playerid][pJobsForklift1] = -1;
	TrashTotal[playerid] = 0;
	//Reports
	for(new s = 0; s < 40; s++)
	{
		ListItemReportId[playerid][s] = -1;
	}
	CancelReport[playerid] = -1;
	for(new i = 0; i < MAX_REPORTS; i++)
	{
	    if(Reports[i][ReportFrom] == playerid)
	    {
	        Reports[i][ReportFrom] = 999;
			Reports[i][BeingUsed] = 0;
			Reports[i][TimeToExpire] = 0;
		}
	}
	//Property
	pData[playerid][pWorkshop] = -1;
	pData[playerid][pLadang] = -1;
	pData[playerid][pFacInvite] = -1;
	pData[playerid][pFacOffer] = -1;
	pData[playerid][pFamInvite] = -1;
	pData[playerid][pFamOffer] = -1;
	pData[playerid][pWorkInvite] = -1;
	pData[playerid][pWorkOffer] = -1;
	pData[playerid][pLadangInvite] = -1;
	pData[playerid][pLadangOffer] = -1;
	//Rental
	pData[playerid][pRents] = -1;
	//Call
	pData[playerid][pTaxiCall] = -1;
	pData[playerid][pMechaCall] = -1;
	pData[playerid][pPhoneOff] = 0;
	Mobile[playerid] = INVALID_PLAYER_ID;
	pData[playerid][pCall] = INVALID_PLAYER_ID;
	//ADS
	for (new i = 0; i != 10; i ++) {
        ListedAds[playerid][i] = -1;
    }
	//Fishing
	for(new i = 0; i < 5; i++) FishWeight[playerid][i] = 0.0;
	//Hauling
	SedangHauling[playerid] = -1;
	pData[playerid][pMission] = -1;
	pData[playerid][pHauling] = -1;
	for(new i; i <= 10; i++) // 9 = Total Dialog , Jadi kita mau tau kalau Player Ini Apakah Ambil Dialog dari 3 tersebut apa ga !
	{
		if(DialogSaya[playerid][i] == true) // Cari apakah dia punya salah satu diantara 10 dialog tersebut
		{
		    DialogSaya[playerid][i] = false; // Ubah Jadi Dia ga punya dialog lagi Kalau Udah Disconnect (Bukan dia lagi pemilik)
		    DialogHauling[i] = false; // Jadi ga ada yang punya nih dialog
		    DestroyVehicle(TrailerHauling[playerid]);
		}
	}
	//Courier Jobs
	TimerCourier[playerid] = 0;
    CourierCount[playerid] = 0;
    CourierJob[playerid] = false;
    for(new i; i < 11; i++)
    {
        RemovePlayerMapIcon(playerid, i);
		CourierStatus[playerid][i] = false;
    }
	//Race
	for(new i = 0; i < MAX_ROUTE; i++) {
		RacePos[playerid][i][0] = 0;
		RacePos[playerid][i][1] = 0;
		RacePos[playerid][i][2] = 0;
	}
	InRace[playerid] = false;
	RaceIndex[playerid] = -1;
	RaceWith[playerid] = INVALID_PLAYER_ID;
	//In Interior
	pData[playerid][pInFlat] = -1;
	pData[playerid][pInBiz] = -1;
	pData[playerid][pFamily] = -1;
	pData[playerid][pInGarageH] = -1;
	pData[playerid][pInDoor] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInApart] = -1;
	pData[playerid][pInDoorFlat] = -1;
	//EditObject
	pData[playerid][pEditSpeed] = -1;
	pData[playerid][CuttingTreeID] = -1;
	pData[playerid][CarryingLumber] = false;
	pData[playerid][EditingTreeID] = -1;
	SetPVarInt(playerid, "editingcd", -1);
	editing_object[playerid] = INVALID_STREAMER_ID;
	EditingObject[playerid] = -1;
	EditingMatext[playerid] = -1;
	pData[playerid][EditingATMID] = -1;
	Player_EditVehicleObject[playerid] = -1;
    Player_EditVehicleObjectSlot[playerid] = -1;
    Player_EditingObject[playerid] = 0;
	pData[playerid][pEditFlatStructure] = -1;
	pData[playerid][pEditStaticStructure] = -1;
	pData[playerid][pEditStructure] = -1;
	pData[playerid][pEditFlatStructure] = -1;
	pData[playerid][pEditFurniture] = -1;
	pData[playerid][pEditFurnHouse] = -1;
	pData[playerid][pEditStaticStructure] = -1;
	editDoorFlat[playerid] = -1;
	pData[playerid][pEditHouseStructure] = -1;
	pData[playerid][pEditStructure] = -1;
	pData[playerid][pEditRoadblock] = -1;
	pData[playerid][gEditID] = -1;
	pData[playerid][pEditGYMObject] = -1;
	pEditPoint[playerid][pEditObject] = -1;
    pEditPoint[playerid][pEditObjectSel] = -1;
	//Vehicle
	pData[playerid][pLastCar] = -1;
	TempCarID[playerid] = -1;
	InVeh[playerid] = -1;
	EnterVeh[playerid] = -1;
	pData[playerid][pKeyVehicle] = INVALID_VEHICLE_ID;
	//AFK
	pData[playerid][pPaused] = -1;
	pData[playerid][pAFK] = -1;
	//Ask Player
	pData[playerid][pAsk] = false;
	pData[playerid][pAskTime] = -1;
	//Drugs
	pData[playerid][pDrugTime] = -1;
	pData[playerid][pDrugUsed] = -1;
	//Toll
	pData[playerid][pTollDelays] = -1;
	SetPVarInt(playerid, "editTollGateID", -1);
	SetPVarInt(playerid, "editTollGateMode", -1);
	//DoorFaction
	SetPVarInt(playerid, "editTDoorFactionID", -1);
	SetPVarInt(playerid, "editDoorFactionMode", -1);
	//Event
	eventJoin[playerid] = 0;
	eventTeams[playerid] = 0;
	eventScore_DM[playerid] = 0;
	eventZombieSkin[playerid] = 0; 
	eventZombieCD[playerid] = 0;
	eventWaitingSpawn[playerid] = 0;
	//Streamer
	pData[playerid][pStreamer] = 2;
	//Skill
	pData[playerid][pSkillTrucker] = 1;
	pData[playerid][pSkillMecha] = 1;
	pData[playerid][pSkillFishing] = 1;
	pData[playerid][pSkillFarmer] = 1;
	//Vehicle
	SellPriceVehicle[playerid] = -1;
	SellIDPlayerVehicle[playerid] = -1; 
	SellIDVehiclePlayer[playerid] = -1;
	TradePlayerID[playerid] = -1;
	TradeVehicleID[playerid] = -1;
	//House Structure/Furniture
	EditingHouseFurniture[playerid] = -1;
	EditingHouseStructure[playerid] = -1;
	//Anti-Cheat
	hack_health[playerid] = 0;
    hack_armour[playerid] = 0;
    hack_teleport[playerid] = 0;
    hack_airbreak[playerid] = 0;
    hack_vehiclehealth[playerid] = 0;
    hack_vehtele[playerid] = 0;
    hack_fly[playerid] = 0;
    wrap_veh[playerid] = 0;
    veh_speedhack[playerid] = 0;
    onfoot_speedhack[playerid] = 0;
	//Weapon
	for (new i = 0; i < MAX_WEAPON_SLOT; i ++) if(PlayerGuns[playerid][i][weapon_id]) {
		PlayerGuns[playerid][i][weapon_id] = 0;
		PlayerGuns[playerid][i][weapon_ammo] = 0;
		PlayerGuns[playerid][i][weapon_slot] = 0;
	}
	ResetPlayerWeapons(playerid);
	//Fitness
	pData[playerid][pFitnessRating][0] = 100.00; 
	pData[playerid][pFitnessRating][1] = 100.00; 
	pData[playerid][pFitnessRating][2] = 100.00; 
	pData[playerid][pFitnessRating][3] = 100.00;
	pData[playerid][pFitnessRating][4] = 100.00;
	pData[playerid][pFitnessRating][5] = 100.00;
}

ResetNameTag(playerid)
{
    foreach (new i : Player) {
        ShowPlayerNameTagForPlayer(i, playerid, 1);
    }
    if(IsValidDynamic3DTextLabel(pData[playerid][pNameTag]))
        DestroyDynamic3DTextLabel(pData[playerid][pNameTag]);
    pData[playerid][pNameTag] = Text3D:INVALID_STREAMER_ID;
    return 1;
}

KickEx(playerid, time = 1900)
{
	SetTimerEx("_KickPlayerDelayed", time, false, "i", playerid);
	return 1;
}

IsValidName(const name[]) {
    if(!name[0] || strfind(name, "_") == -1)
        return 0;

    else for (new i = 0, len = strlen(name); i != len; i ++) {
    if((i == 0) && (name[i] < 'A' || name[i] > 'Z'))
            return 0;

        else if((i != 0 && i < len  && name[i] == '_') && (name[i + 1] < 'A' || name[i + 1] > 'Z'))
            return 0;

        else if((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != '.')
            return 0;
    }
    return 1;
}

IsValidPassword(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9', ']', '[', '(', ')', '_', '.', '@', '#': continue;
			default: return false;
		}
	}
	return true;
}

//----------[ Anti-Cheat Native ]------
//Anti Money Hack
GivePlayerMoneyEx(playerid, cashgiven)
{
	pData[playerid][pMoney] += cashgiven;
	GivePlayerMoney(playerid, cashgiven);
}

ResetPlayerMoneyEx(playerid)
{
	pData[playerid][pMoney] = 0;
	ResetPlayerMoney(playerid);
}

//Anti Health and Armour Hack
SetPlayerHealthEx(playerid, Float:heal)
{
	pData[playerid][pHealth] = heal;
	if(pData[playerid][pHealth] >= pData[playerid][pMaxHealth]) pData[playerid][pHealth] = pData[playerid][pMaxHealth];
	new Float:totalhealth = pData[playerid][pHealth]/pData[playerid][pMaxHealth] * 100.0;
	SetPlayerHealth(playerid, totalhealth);
}

SetPlayerArmourEx(playerid, Float:armor)
{
	pData[playerid][pArmour] = armor;
	SetPlayerArmour(playerid, armor);
}

//----------[ Admin Native ]----------
GetStaffRank(playerid)
{
	new name[40];
	if(pData[playerid][pAdmin] == 1)
	{
		name = ""RED_E"Volunteer";
	}
	else if(pData[playerid][pAdmin] == 2)
	{
		name = ""RED_E"Helper";
	}
	else if(pData[playerid][pAdmin] == 3)
	{
		name = ""RED_E"Administrator";
	}
	else if(pData[playerid][pAdmin] == 4)
	{
		name = ""RED_E"Lead Administrator";
	}
	else if(pData[playerid][pAdmin] == 5)
	{
		name = ""RED_E"Management";
	}
	else if(pData[playerid][pAdmin] == 6)
	{
		name = ""RED_E"Executive";
	}
	else if(pData[playerid][pAdmin] == 7)
	{
		name = ""RED_E"none";
	}
	else if(pData[playerid][pAdmin] == 8)
	{
		name = ""RED_E"none";
	}
	else if(pData[playerid][pHelper] == 1 && pData[playerid][pAdmin] == 0)
	{
		name = ""GREEN_E"Junior Helper";
	}
	else if(pData[playerid][pHelper] == 2 && pData[playerid][pAdmin] == 0)
	{
		name = ""GREEN_E"Senior Helper";
	}
	else if(pData[playerid][pHelper] == 3 && pData[playerid][pAdmin] == 0)
	{
		name = ""GREEN_E"Head Helper";
	}
	else
	{
		name = "None";
	}
	return name;
}

GetAdminRank(playerid)
{
	new name[40];
	if(pData[playerid][pAdmin] == 1)
	{
		name = "Volunteer";
	}
	else if(pData[playerid][pAdmin] == 2)
	{
		name = "Helper";
	}
	else if(pData[playerid][pAdmin] == 3)
	{
		name = "Administrator";
	}
	else if(pData[playerid][pAdmin] == 4)
	{
		name = "Lead Administrator";
	}
	else if(pData[playerid][pAdmin] == 5)
	{
		name = "Management";
	}
	else if(pData[playerid][pAdmin] == 6)
	{
		name = "Executive";
	}
	else if(pData[playerid][pAdmin] == 7)
	{
		name = "none";
	}
	else if(pData[playerid][pAdmin] == 8)
	{
		name = "none";
	}
	else if(pData[playerid][pHelper] == 1 && pData[playerid][pAdmin] == 0)
	{
		name = "JH";
	}
	else if(pData[playerid][pHelper] == 2 && pData[playerid][pAdmin] == 0)
	{
		name = "SH";
	}
	else if(pData[playerid][pHelper] == 3 && pData[playerid][pAdmin] == 0)
	{
		name = "HH";
	}
	else
	{
		name = "None";
	}
	return name;
}

SendStaffMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pAdmin] >= 1 || pData[i][pHelper] >= 1) {
                SendClientMessageEx(i, color, ""TOMATO_E"%s", string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pAdmin] >= 1 || pData[i][pHelper] >= 1) {
            SendClientMessageEx(i, color, ""TOMATO_E"%s", string);
        }
    }
    return 1;
}



SendAdminMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[512]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pAdmin] >= 1/*&& !pData[i][pDisableAdmin]*/) {
				SendClientMessageEx(i, color, ""TOMATO_E"%s", string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pAdmin] >= 1/*&& !pData[i][pDisableAdmin]*/) {
			SendClientMessageEx(i, color, ""TOMATO_E"%s", string);
        }
    }
    return 1;
}

SendAdminChatMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pAdmin] > 0 && pData[i][pTogStaffChat] == 0) {
                SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pAdmin] > 0 && pData[i][pTogStaffChat] == 0) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}

stock SendQuizVoteMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pTogQuizVote] == 0) {
                SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pTogQuizVote] == 0) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}


StaffCommandLog(const command[], adminid, player = INVALID_PLAYER_ID, logstr[] = '*')
{
	// Set the logging message to be correct
	new logStrEscaped[128], query[512];
	if(logstr[0] == '*')
		logStrEscaped = "*", printf("AdminCommandLog: logstr detected as unnecessary, logStrEscaped = '%s' (must be '*')", logStrEscaped);
	else
		mysql_escape_string(logstr, logStrEscaped), printf("AdminCommandLog: logstr detected necessary, escaped from '%s' to '%s'", logstr, logStrEscaped);

	if(player != INVALID_PLAYER_ID)
	{
		// The action involves a player, get their name
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO logstaff (command,admin,adminid,player,playerid,str,time) VALUES('%s','%s(%s)',%d,'%s',%d,'%s',UNIX_TIMESTAMP())", command, pData[adminid][pName], pData[adminid][pAdminname], pData[adminid][pID], pData[player][pName], pData[player][pID], logStrEscaped);
	}
	else
	{
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO logstaff (command,admin,adminid,str,time) VALUES('%s','%s(%s)',%d,'%s',UNIX_TIMESTAMP())", command, pData[adminid][pName], pData[adminid][pAdminname], pData[adminid][pID], logStrEscaped);
	}

	// Send the query!
	mysql_tquery(g_SQL, query);
	return 1;
}

//----------[ VIP Native ]----------
GetVipRank(playerid)
{
	new name[40];
	if(pData[playerid][pVip] == 1)
	{
		name = ""GREEN_E"Basic";
	}
	else if(pData[playerid][pVip] == 2)
	{
		name = ""GREEN_E"Advanced";
	}
	else if(pData[playerid][pVip] == 3)
	{
		name = ""GREEN_E"Professional";
	}
	else if(pData[playerid][pVip] == 4)
	{
		name = ""GREEN_E"Lifetime";
	}
	else
	{
		name = "None";
	}
	return name;
}

GetPlayerCS(playerid)
{
	new name[40];
	if(pData[playerid][pCS] == 1)
	{
		name = ""GREEN_E"Approve";
	}
	else
	{
		name = ""RED_E"None";
	}
	return name;
}

//----------[ Faction Native ]----------
SetFactionColor(playerid)
{
    new factionid = pData[playerid][pFaction];

    if(factionid == 1)
	{
		SetPlayerColor(playerid, COLOR_RADIO);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RADIO, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	else if(factionid == 2)
	{
		SetPlayerColor(playerid, COLOR_LBLUE);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_LBLUE, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	else if(factionid == 3)
	{
		SetPlayerColor(playerid, COLOR_PINK2);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_PINK2, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	else if(factionid == 4)
	{
		SetPlayerColor(playerid, COLOR_ORANGE2);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_ORANGE2, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	else
	{
		SetPlayerColor(playerid, COLOR_WHITE);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	return 1;
}

PropertiesCommercial_GetCount(playerid) {
    new count = 0, string[32], maxProperties;

    foreach(new i : Bisnis) if(Player_OwnsBisnis(playerid, i)) {
        count++;
    }
    foreach(new i : FARMS) if(Player_OwnsFarms(playerid, i)) {
        count++;
    }
    // foreach(new i : WORKSHOPS) if(pData[playerid][pWorkshop] == i) {
    //     count++;
    // }
	foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) {
		count++;
	}
	foreach(new i : Dealership) if(IsPlayerOwnerOfCDEx(playerid, i)) {
        count++;
    }
	foreach(new i : PrivateGarage) if(OwnerPvGarage(playerid, i)) {
        count++;
    }
    if (pData[playerid][pVip] == 2) maxProperties = MAX_OWN_COMMERCIAL+3;
    else if (pData[playerid][pVip] == 3) maxProperties = MAX_OWN_COMMERCIAL+4;
    else if (pData[playerid][pVip] == 4) maxProperties = MAX_OWN_COMMERCIAL+4;
    else maxProperties = MAX_OWN_COMMERCIAL;

    format(string, sizeof(string), "%d/%d", count, maxProperties);

    return string;
}

PropertiesCommercial_Max(playerid) {
    new maxProperties;

    if (pData[playerid][pVip] == 2) maxProperties = MAX_OWN_COMMERCIAL+3;
    else if (pData[playerid][pVip] == 3) maxProperties = MAX_OWN_COMMERCIAL+4;
    else if (pData[playerid][pVip] == 4) maxProperties = MAX_OWN_COMMERCIAL+4;
    else maxProperties = MAX_OWN_COMMERCIAL;

    return maxProperties;
}

PropertiCommercial_CountMax(playerid) {
    new count = 0;

    foreach(new i : Bisnis) if(Player_OwnsBisnis(playerid, i)) {
        count++;
    }
    foreach(new i : FARMS) if(Player_OwnsFarms(playerid, i)) {
        count++;
    }
    // foreach(new i : WORKSHOPS) if(pData[playerid][pWorkshop] == i) {
    //     count++;
    // }
	foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) {
		count++;
	}
	foreach (new i : Dealership) if(IsPlayerOwnerOfCDEx(playerid, i)) {
        count++;
    }
	foreach (new i : PrivateGarage) if(OwnerPvGarage(playerid, i)) {
        count++;
    }
    return count;
}

PropertiesResidential_GetCount(playerid) {
    new count = 0, string[32], maxProperties;

    foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) {
        count++;
    }
    foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) {
        count++;
    }
    if (pData[playerid][pVip] == 2) maxProperties = MAX_OWN_RESIDENTIAL+2;
    else if (pData[playerid][pVip] == 3) maxProperties = MAX_OWN_RESIDENTIAL+3;
    else if (pData[playerid][pVip] == 4) maxProperties = MAX_OWN_RESIDENTIAL+3;
    else maxProperties = MAX_OWN_RESIDENTIAL;

    format(string, sizeof(string), "%d/%d", count, maxProperties);

    return string;
}

PropertiesResidential_Max(playerid) {
    new maxProperties;

    if (pData[playerid][pVip] == 2) maxProperties = MAX_OWN_RESIDENTIAL+2;
    else if (pData[playerid][pVip] == 3) maxProperties = MAX_OWN_RESIDENTIAL+3;
    else if (pData[playerid][pVip] == 4) maxProperties = MAX_OWN_RESIDENTIAL+3;
    else maxProperties = MAX_OWN_RESIDENTIAL;

    return maxProperties;
}

PropertiResidential_CountMax(playerid) {
    new count = 0;

    foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) {
        count++;
    }
    foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) {
        count++;
    }
    return count;
}

SendFactionMessage(factionid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(pData[i][pFaction] == factionid && pData[i][pTogFaction] == 0/*&& !pData[i][pDisableFaction]*/) 
        {
            SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(pData[i][pFaction] == factionid && pData[i][pTogFaction] == 0/*&& !pData[i][pDisableFaction]*/) 
    {
        SendClientMessage(i, color, str);
    }
    return 1;
}

//----------[ Family Native]----------
GetFamilyRank(playerid)
{
	new rank[24];
	if(pData[playerid][pFamily] != -1)
	{
		if(pData[playerid][pFamilyRank] == 1)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank1]);
		else if(pData[playerid][pFamilyRank] == 2)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank2]);
		else if(pData[playerid][pFamilyRank] == 3)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank3]);
		else if(pData[playerid][pFamilyRank] == 4)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank4]);
		else if(pData[playerid][pFamilyRank] == 5)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank5]);
		else if(pData[playerid][pFamilyRank] == 6)  format(rank, sizeof(rank), "%s", fData[pData[playerid][pFamily]][fNameRank6]);
		else rank = "None";
	}
	else rank = "None";
	return rank;
}

GetPlayerFactionName(playerid)
{
	new faction[40];
	switch(pData[playerid][pFaction])
	{
		case 1: format(faction, sizeof(faction), "SAPD");
		case 2: format(faction, sizeof(faction), "SAGS");
		case 3: format(faction, sizeof(faction), "SAMD");
		case 4: format(faction, sizeof(faction), "SANA");
		default: format(faction, sizeof(faction), "None");
	}
	return faction;
}

GetPlayerFamilyName(playerid)
{
	new family[50];
	if(pData[playerid][pFamily] != -1) format(family, sizeof(family), "%s", fData[pData[playerid][pFamily]][fName]);
	else format(family, sizeof(family), "None");
	return family;
}

SendFamilyMessage(familyid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144],
        mstr[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(pData[i][pFamily] == familyid /*&& !pData[i][pDisableFaction]*/) 
        {
            SendClientMessage(i, color, string);
           	format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", string);
			SetPlayerChatBubble(i, mstr, COLOR_PINK, 10.0, 3000);
        }
        return 1;
    }
    foreach (new i : Player) if(pData[i][pFamily] == familyid /*&& !pData[i][pDisableFaction]*/) 
    {
        SendClientMessage(i, color, str);
        format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", str);
		SetPlayerChatBubble(i, mstr, COLOR_PINK, 10.0, 3000);
    }
    return 1;
}

//----------[ Job Native ]----------
GetJobName(type)
{
    static
        str[24];

    switch (type)
    {
        case 1: str = "Taxi Driver";
        case 2: str = "Mechanic";
		case 3: str = "Lumber Jack";
		case 4: str = "Trucker";
		case 5: str = "Farmer";
		case 6: str = "Arms dealer";
		case 7: str = "Drugs dealer";
		case 8: str = "Smuggle dealer";
		case 9: str = "Builder";
        default: str = "None";
    }
    return str;
}

//-----------[ Player Native ]----------
GetID(const name[])
{
	foreach(new i : Player)
	{
		if(!strcmp(name, pData[i][pName]))
			return i;
	}
	return -1;
}

DisplayStats(playerid, p2)
{
	new count = CountPlayerVehicle(p2), limit = LimitSlotPlayerVehicle(p2), nameveh[250];
	foreach(new i : PVehicles) if(IsValidPlayerVehicle(p2, i)) {
		format(nameveh, sizeof(nameveh), "%s %s (VID%d)", nameveh, GetVehicleModelName(pvData[i][cModel]), pvData[i][cID]);
	}
	new coordsString[2000], S3MP4K[3000], idiot[212];
	format(idiot, sizeof(idiot), ""ARWIN_E"%s(pid: %d)", pData[p2][pName], pData[p2][pID]);
	//SendClientMessageEx(playerid,COLOR_WHITE,coordsString);
	format(coordsString, sizeof(coordsString), ""YELLOW_E"IC Information:\n");
	strcat(S3MP4K, coordsString);
	new phoneStr[32], factionRank[40], familyRank[40];
	if(pData[p2][pPhone] > 0) format(phoneStr, sizeof(phoneStr), "%d", pData[p2][pPhone]);
	else format(phoneStr, sizeof(phoneStr), "Tidak Ada");
	if(pData[p2][pFaction] > 0) format(factionRank, sizeof(factionRank), "%s (%d)", pData[p2][pFactionRankName], pData[p2][pFactionRank]);
	else format(factionRank, sizeof(factionRank), "None");
	if(pData[p2][pFamily] != -1) format(familyRank, sizeof(familyRank), "%s (%d)", GetFamilyRank(p2), pData[p2][pFamilyRank]);
	else format(familyRank, sizeof(familyRank), "None");
	format(coordsString, sizeof(coordsString), ""WHITE_E"Gender: ["ARWIN_E"%s"WHITE_E"] Origin: ["ARWIN_E"%s"WHITE_E"]\n",(pData[p2][pGender] == 2) ? ("Female") : ("Male"), GetPlayerAccent(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Money: ["GREEN_E"$%s"WHITE_E"] Bank: ["GREEN_E"$%s"WHITE_E"]\n", FormatMoney(pData[p2][pMoney]), FormatMoney(pData[p2][pBankMoney]));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Phone number: ["ARWIN_E"%s"WHITE_E"] Phone credit: ["ARWIN_E"%d Points"WHITE_E"]\n", phoneStr, pData[p2][pPhoneCredit]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Jobs: [%s, %s"WHITE_E"]\n", GetJobName(pData[p2][pJob]), GetJobName(pData[p2][pJob2]));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Faction: ["ARWIN_E"%s"WHITE_E"] Rank: ["ARWIN_E"%s"WHITE_E"]\n", GetPlayerFactionName(p2), factionRank);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Family: ["ARWIN_E"%s"WHITE_E"] Rank: ["ARWIN_E"%s"WHITE_E"]\n", GetPlayerFamilyName(p2), familyRank);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Married with: ["ARWIN_E"%s"WHITE_E"]\n", GetCoupleName(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "\n"YELLOW_E"OOC Information:\n");
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"User: ["AQUA_E"%s"WHITE_E"] Player rank: ["ARWIN_E"%s"WHITE_E"]\n", charData[p2][cName], ORANK(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Paychecks: ["ARWIN_E"%d"WHITE_E"] Time played: ["AQUA_E"%d hour(s) %d minute(s) %02d second(s)"WHITE_E"]\n", pData[p2][pPaycheck]/60, pData[p2][pHours], pData[p2][pMinutes], pData[p2][pSeconds]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Vehicle (%d/%d): ["ARWIN_E"%s"WHITE_E" ]\n",count, limit, nameveh);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Warns: ["YELLOW_E"%d"WHITE_E"/"RED_E"20"WHITE_E"] Donator rank: [%s"WHITE_E"] Character Story: [%s"WHITE_E"]\n", pData[p2][pWarn], GetVipRank(p2), GetPlayerCS(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Word: ["ARWIN_E"%d"WHITE_E"] Interior: ["ARWIN_E"%d"WHITE_E"] MaxHP: ["AQUA_E"%.1f"WHITE_E"] Health: ["RED_E"%.1f"WHITE_E"] Armour: ["ARWIN_E"%.1f"WHITE_E"] Gold Points: ["YELLOW_E"%d"WHITE_E"]\n",GetPlayerVirtualWorld(p2), GetPlayerInterior(p2), pData[p2][pMaxHealth], pData[p2][pHealth], pData[p2][pArmour], pData[p2][pGold]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Property list moved to "WHITE_E"'"YELLOW_E"/myproperty"WHITE_E"' or '"YELLOW_E"/mp"WHITE_E"'");
    strcat(S3MP4K, coordsString);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, idiot, S3MP4K,"Close","");	
	return 1;
}

DisplayStatsStream(playerid, p2)
{
	new count = CountPlayerVehicle(p2), limit = LimitSlotPlayerVehicle(p2), nameveh[250];
	foreach(new i : PVehicles) if(IsValidPlayerVehicle(p2, i)) {
		format(nameveh, sizeof(nameveh), "%s %s (VID%d)", nameveh, GetVehicleModelName(pvData[i][cModel]), pvData[i][cID]);
	}
	new coordsString[2000], S3MP4K[3000], idiot[212];
	format(idiot, sizeof(idiot), ""ARWIN_E"%s", pData[p2][pName]);
	//SendClientMessageEx(playerid,COLOR_WHITE,coordsString);
	format(coordsString, sizeof(coordsString), ""YELLOW_E"IC Information:\n");
	strcat(S3MP4K, coordsString);
	new phoneStr2[32], factionRank[40], familyRank[40];
	if(pData[p2][pPhone] > 0) format(phoneStr2, sizeof(phoneStr2), "%d", pData[p2][pPhone]);
	else format(phoneStr2, sizeof(phoneStr2), "Tidak Ada");
	if(pData[p2][pFaction] > 0) format(factionRank, sizeof(factionRank), "%s (%d)", pData[p2][pFactionRankName], pData[p2][pFactionRank]);
	else format(factionRank, sizeof(factionRank), "None");
	if(pData[p2][pFamily] != -1) format(familyRank, sizeof(familyRank), "%s (%d)", GetFamilyRank(p2), pData[p2][pFamilyRank]);
	else format(familyRank, sizeof(familyRank), "None");
	format(coordsString, sizeof(coordsString), ""WHITE_E"Gender: ["ARWIN_E"%s"WHITE_E"] Origin: ["ARWIN_E"%s"WHITE_E"]\n",(pData[p2][pGender] == 2) ? ("Female") : ("Male"), GetPlayerAccent(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Money: ["GREEN_E"$%s"WHITE_E"] Bank: ["GREEN_E"$%s"WHITE_E"]\n", FormatMoney(pData[p2][pMoney]), FormatMoney(pData[p2][pBankMoney]));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Phone number: ["ARWIN_E"%s"WHITE_E"] Phone credit: ["ARWIN_E"%d Points"WHITE_E"]\n", phoneStr2, pData[p2][pPhoneCredit]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Jobs: [%s, %s"WHITE_E"]\n", GetJobName(pData[p2][pJob]), GetJobName(pData[p2][pJob2]));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Faction: ["ARWIN_E"%s"WHITE_E"] Rank: ["ARWIN_E"%s"WHITE_E"]\n", GetPlayerFactionName(p2), factionRank);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Family: ["ARWIN_E"%s"WHITE_E"] Rank: ["ARWIN_E"%s"WHITE_E"]\n", GetPlayerFamilyName(p2), familyRank);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Married with: ["ARWIN_E"%s"WHITE_E"] Bank Account: ["LG_E"%d"WHITE_E"]\n", GetCoupleName(p2), pData[p2][pBankRek]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "\n"YELLOW_E"OOC Information:\n");
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Player rank: ["ARWIN_E"%s"WHITE_E"] Paychecks: ["ARWIN_E"%d"WHITE_E"]\n", ORANK(p2), pData[p2][pPaycheck]/60);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), ""WHITE_E"Time played: ["AQUA_E"%d hour(s) %d minute(s) %02d second(s)"WHITE_E"]\n", pData[p2][pHours], pData[p2][pMinutes], pData[p2][pSeconds]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Vehicles (%d/%d): ["ARWIN_E"%s"WHITE_E" ] \n",count, limit, nameveh);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Warns:["YELLOW_E"%d"WHITE_E"/"RED_E"20"WHITE_E"] Donatur Rank : [%s"WHITE_E"] Character Story : [%s"WHITE_E"]\n",pData[p2][pWarn], GetVipRank (p2), GetPlayerCS(p2));
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "World: ["ARWIN_E"%d"WHITE_E"] Interior: ["ARWIN_E"%d"WHITE_E"] MaxHP: ["AQUA_E"%.1f"WHITE_E"] Health: ["RED_E"%.1f"WHITE_E"] Armour: ["ARWIN_E"%.1f"WHITE_E"] Gold Points: ["YELLOW_E"%d"WHITE_E"]\n",GetPlayerVirtualWorld(p2), GetPlayerInterior(p2), pData[p2][pMaxHealth], pData[p2][pHealth], pData[p2][pArmour], pData[p2][pGold]);
    strcat(S3MP4K, coordsString);
	format(coordsString, sizeof(coordsString), "Property list moved to "WHITE_E"'"YELLOW_E"/myproperty"WHITE_E"' or '"YELLOW_E"/mp"WHITE_E"'");
    strcat(S3MP4K, coordsString);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, idiot, S3MP4K,"Close","");	
	return 1;
}

GetPlayerCallsign(playerid) {
    new callsign[24];

    if (pData[playerid][pOnDuty]) 
    {
        if (!strcmp(pData[playerid][pUnit], "None", true)) format(callsign, sizeof(callsign), RED_E"UNASSIGNED");
        else format(callsign, sizeof(callsign), "%s", pData[playerid][pUnit]);
    } else format(callsign, sizeof(callsign), GREY_E"OFF");
    return callsign;
}

GetCoupleName(playerid) {
    new couple[MAX_PLAYER_NAME];

    if (pData[playerid][pMarried]) {
        format(couple, sizeof(couple), "%s", pData[playerid][pMarriedTo]);
    } else format(couple, sizeof(couple), "None");
    return couple;
}

DisplayItems(playerid, p2)
{
	new mstr[512], lstr[1024];
	format(mstr, sizeof(mstr), "Items (%s)", pData[p2][pName]);
    format(lstr, sizeof(lstr), "Name\tAmmount\nCash\t$%s\n", FormatMoney(pData[p2][pMoney]));
	if(pData[p2][pSnack] > 0) format(lstr, sizeof(lstr), "%s\nSnack\t%d", lstr, pData[p2][pSnack]);
	if(pData[p2][pSprunk] > 0) format(lstr, sizeof(lstr), "%s\nSprunk\t%d", lstr, pData[p2][pSprunk]);
	if(pData[p2][pRokok] > 0) format(lstr, sizeof(lstr), "%s\nCigarettes\t%d", lstr, pData[p2][pRokok]);
	if(pData[p2][pBandage] > 0) format(lstr, sizeof(lstr), "%s\nBandage\t%d", lstr, pData[p2][pBandage]);
	if(pData[p2][pMedicine] > 0) format(lstr, sizeof(lstr), "%s\nMedicine\t%d", lstr, pData[p2][pMedicine]);
	if(pData[p2][pMedkit] > 0) format(lstr, sizeof(lstr), "%s\nMedkit\t%d", lstr, pData[p2][pMedkit]);
	if(pData[p2][pComponent] > 0) format(lstr, sizeof(lstr), "%s\nComponent\t%d", lstr, pData[p2][pComponent]);
	if(pData[p2][pFood] > 0) format(lstr, sizeof(lstr), "%s\nFood\t%d", lstr, pData[p2][pFood]);
	if(pData[p2][pFishTool] > 0) format(lstr, sizeof(lstr), "%s\nFish pole\t%d use(s) left", lstr, pData[p2][pFishTool]);
	if(pData[p2][pWorm] > 0) format(lstr, sizeof(lstr), "%s\nBait\t%d", lstr, pData[p2][pWorm]);
	if(pData[p2][pPayToll] > 0) format(lstr, sizeof(lstr), "%s\nToll Card\t%d use(s) left", lstr, pData[p2][pPayToll]);
	if(pData[p2][pCoughPills] > 0) format(lstr, sizeof(lstr), "%s\nNeladryl Acetate\t%d", lstr, pData[p2][pCoughPills]);
	if(pData[p2][pMigrainPills] > 0) format(lstr, sizeof(lstr), "%s\nKratotamax Plus 1.0\t%d", lstr, pData[p2][pMigrainPills]);
	if(pData[p2][pFiverPills] > 0) format(lstr, sizeof(lstr), "%s\nLazattavitus Extra\t%d", lstr, pData[p2][pFiverPills]);
	for(new i = 0; i < 5; i++) {
        if(FishWeight[playerid][i] > 0.0)
            format(lstr, sizeof(lstr), "%s\n[FISH] Ocean fish\t%.1f lb(s)", lstr, FishWeight[playerid][i]);
    } 
	if(pData[p2][pSeedWheat] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Wheat\t%d units", lstr, pData[p2][pSeedWheat]);
	if(pData[p2][pSeedOnion] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Onion\t%d units", lstr, pData[p2][pSeedOnion]);
	if(pData[p2][pSeedCarrot] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Carrot\t%d units", lstr, pData[p2][pSeedCarrot]);
	if(pData[p2][pSeedPotato] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Potato\t%d units", lstr, pData[p2][pSeedPotato]);
	if(pData[p2][pSeedCorn] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Corn\t%d units", lstr, pData[p2][pSeedCorn]);
	if(pData[p2][pWheat] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Wheat\t%d units", lstr, pData[p2][pWheat]);
	if(pData[p2][pOnion] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Onion\t%d units", lstr, pData[p2][pOnion]);
	if(pData[p2][pCarrot] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Carrot\t%d units", lstr, pData[p2][pCarrot]);
	if(pData[p2][pPotato] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Potato\t%d units", lstr, pData[p2][pPotato]);
	if(pData[p2][pCorn] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Corn\t%d units", lstr, pData[p2][pCorn]);
	if(pData[p2][pBushForager] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Wild Berries\t%d units", lstr, pData[p2][pBushForager]);
	if(pData[p2][pCrack] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Crack\t"RED_E"%d gram(s)", lstr, pData[p2][pCrack]);
	if(pData[p2][pPot] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Pot\t"RED_E"%d gram(s)", lstr, pData[p2][pPot]);
	if(pData[p2][pMaterial] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Material\t%d units", lstr, pData[p2][pMaterial]);
	if(pData[p2][pSchematic][0] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Country Rifle\t%d units", lstr, pData[p2][pSchematic][0]);
	if(pData[p2][pSchematic][1] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Shotgun\t%d units", lstr, pData[p2][pSchematic][1]);
	if(pData[p2][pSchematic][2] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Sawn Of Shotgun\t%d units", lstr, pData[p2][pSchematic][2]);
	if(pData[p2][pSchematic][3] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Desert Eagle\t%d units", lstr, pData[p2][pSchematic][3]);
	if(pData[p2][pSchematic][4] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] MP-5\t%d units", lstr, pData[p2][pSchematic][4]);
	if(pData[p2][pSchematic][5] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] AK-47\t%d units", lstr, pData[p2][pSchematic][5]);

	for (new i = 1; i != MAX_WEAPON_SLOT; i++) if(PlayerGuns[p2][i][weapon_id]) {
        format(lstr, sizeof(lstr), "%s\n"RED_E"[WEAPON] %s \t%s ammo\n", lstr, ReturnWeaponName(PlayerGuns[p2][i][weapon_id]), (i == 1) ? (" ") :  (sprintf("%d", PlayerGuns[p2][i][weapon_ammo])));
    }
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, mstr, lstr,"Close","");
	return 1;
}

DisplayItems2(playerid, p2)
{
	new mstr[512], lstr[1024];
	format(mstr, sizeof(mstr), "Inventory of "YELLOW_E"%s", pData[p2][pName]);
    format(lstr, sizeof(lstr), "Item\tAmount\nCash\t$%s\n", FormatMoney(pData[p2][pMoney]));
	if(pData[p2][pSnack] > 0) format(lstr, sizeof(lstr), "%s\nSnack\t%d", lstr, pData[p2][pSnack]);
	if(pData[p2][pSprunk] > 0) format(lstr, sizeof(lstr), "%s\nSprunk\t%d", lstr, pData[p2][pSprunk]);
	if(pData[p2][pRokok] > 0) format(lstr, sizeof(lstr), "%s\nCigarettes\t%d", lstr, pData[p2][pRokok]);
	if(pData[p2][pBandage] > 0) format(lstr, sizeof(lstr), "%s\nBandage\t%d", lstr, pData[p2][pBandage]);
	if(pData[p2][pMedicine] > 0) format(lstr, sizeof(lstr), "%s\nMedicine\t%d", lstr, pData[p2][pMedicine]);
	if(pData[p2][pMedkit] > 0) format(lstr, sizeof(lstr), "%s\nMedkit\t%d", lstr, pData[p2][pMedkit]);
	if(pData[p2][pComponent] > 0) format(lstr, sizeof(lstr), "%s\nComponent\t%d", lstr, pData[p2][pComponent]);
	if(pData[p2][pFood] > 0) format(lstr, sizeof(lstr), "%s\nFood\t%d", lstr, pData[p2][pFood]);
	if(pData[p2][pFishTool] > 0) format(lstr, sizeof(lstr), "%s\nFish pole\t%d use(s) left", lstr, pData[p2][pFishTool]);
	if(pData[p2][pWorm] > 0) format(lstr, sizeof(lstr), "%s\nBait\t%d", lstr, pData[p2][pWorm]);
	if(pData[p2][pPayToll] > 0) format(lstr, sizeof(lstr), "%s\nToll Card\t%d use(s) left", lstr, pData[p2][pPayToll]);
	if(pData[p2][pCoughPills] > 0) format(lstr, sizeof(lstr), "%s\nNeladryl Acetate\t%d", lstr, pData[p2][pCoughPills]);
	if(pData[p2][pMigrainPills] > 0) format(lstr, sizeof(lstr), "%s\nKratotamax Plus 1.0\t%d", lstr, pData[p2][pMigrainPills]);
	if(pData[p2][pFiverPills] > 0) format(lstr, sizeof(lstr), "%s\nLazattavitus Extra\t%d", lstr, pData[p2][pFiverPills]);
	for(new i = 0; i < 5; i++) {
        if(FishWeight[playerid][i] > 0.0)
            format(lstr, sizeof(lstr), "%s\n[FISH] Ocean fish\t%.1f lb(s)", lstr, FishWeight[playerid][i]);
    } 
	if(pData[p2][pSeedWheat] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Wheat\t%d units", lstr, pData[p2][pSeedWheat]);
	if(pData[p2][pSeedOnion] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Onion\t%d units", lstr, pData[p2][pSeedOnion]);
	if(pData[p2][pSeedCarrot] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Carrot\t%d units", lstr, pData[p2][pSeedCarrot]);
	if(pData[p2][pSeedPotato] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Potato\t%d units", lstr, pData[p2][pSeedPotato]);
	if(pData[p2][pSeedCorn] > 0) format(lstr, sizeof(lstr), "%s\n[SEED] Corn\t%d units", lstr, pData[p2][pSeedCorn]);
	if(pData[p2][pWheat] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Wheat\t%d units", lstr, pData[p2][pWheat]);
	if(pData[p2][pOnion] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Onion\t%d units", lstr, pData[p2][pOnion]);
	if(pData[p2][pCarrot] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Carrot\t%d units", lstr, pData[p2][pCarrot]);
	if(pData[p2][pPotato] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Potato\t%d units", lstr, pData[p2][pPotato]);
	if(pData[p2][pCorn] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Corn\t%d units", lstr, pData[p2][pCorn]);
	if(pData[p2][pBushForager] > 0) format(lstr, sizeof(lstr), "%s\n[PLANT] Wild Berries\t%d units", lstr, pData[p2][pBushForager]);
	if(pData[p2][pCrack] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Crack\t"RED_E"%d gram(s)", lstr, pData[p2][pCrack]);
	if(pData[p2][pPot] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Pot\t"RED_E"%d gram(s)", lstr, pData[p2][pPot]);
	if(pData[p2][pMaterial] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"Material\t%d units", lstr, pData[p2][pMaterial]);
	if(pData[p2][pSchematic][0] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Country Rifle\t%d units", lstr, pData[p2][pSchematic][0]);
	if(pData[p2][pSchematic][1] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Shotgun\t%d units", lstr, pData[p2][pSchematic][1]);
	if(pData[p2][pSchematic][2] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Sawn Of Shotgun\t%d units", lstr, pData[p2][pSchematic][2]);
	if(pData[p2][pSchematic][3] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] Desert Eagle\t%d units", lstr, pData[p2][pSchematic][3]);
	if(pData[p2][pSchematic][4] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] MP-5\t%d units", lstr, pData[p2][pSchematic][4]);
	if(pData[p2][pSchematic][5] > 0) format(lstr, sizeof(lstr), "%s\n"RED_E"[SCHEMATIC] AK-47\t%d units", lstr, pData[p2][pSchematic][5]);

	for (new i = 1; i != MAX_WEAPON_SLOT; i++) if(PlayerGuns[p2][i][weapon_id]) {
        format(lstr, sizeof(lstr), "%s\n"RED_E"[WEAPON] %s \t%s ammo\n", lstr, ReturnWeaponName(PlayerGuns[p2][i][weapon_id]), (i == 1) ? (" ") :  (sprintf("%d", PlayerGuns[p2][i][weapon_ammo])));
    }
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, mstr, lstr,"Close","");
	return 1;
}

DisplaySkills(playerid, p2)
{
	new string[512];
	format(string, sizeof(string), "Name Skills\tScore\tLevel\n");
	if(pData[p2][pScoreTrucker] != -1)
	{
		if(pData[p2][pScoreTrucker] <= 50)  format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/50]\t"WHITE_E"1\n", string, pData[p2][pScoreTrucker]);
		else if(pData[p2][pScoreTrucker] <= 150) format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/150]\t"WHITE_E"2\n", string, pData[p2][pScoreTrucker]);
		else if(pData[p2][pScoreTrucker] <= 200) format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/200]\t"WHITE_E"3\n", string, pData[p2][pScoreTrucker]);
		else if(pData[p2][pScoreTrucker] <= 300) format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/300]\t"WHITE_E"4\n", string, pData[p2][pScoreTrucker]);
		else if(pData[p2][pScoreTrucker] >= 300) format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/350]\t"WHITE_E"5\n", string, pData[p2][pScoreTrucker]);
	}
	if(pData[p2][pScoreFishing] != -1)
	{
		if(pData[p2][pScoreFishing] <= 99) format(string, sizeof(string), "%sFish\t"YELLOW_E"[%d/100]\t"WHITE_E"1\n", string, pData[p2][pScoreFishing]);
		if(pData[p2][pScoreFishing] >= 99) format(string, sizeof(string), "%sFish\t"YELLOW_E"[%d/200]\t"WHITE_E"2\n", string, pData[p2][pScoreFishing]);
	}
	if(pData[p2][pScoreMecha] != -1)
	{
		if(pData[p2][pScoreMecha] <= 500) format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/500]\t"WHITE_E"1\n", string, pData[p2][pScoreMecha]);
		else if(pData[p2][pScoreMecha] <= 1500) format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/1500]\t"WHITE_E"2\n", string, pData[p2][pScoreMecha]);
		else if(pData[p2][pScoreMecha] <= 2500) format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/2500]\t"WHITE_E"3\n", string, pData[p2][pScoreMecha]);
		else if(pData[p2][pScoreMecha] <= 3500) format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/3500]\t"WHITE_E"4\n", string, pData[p2][pScoreMecha]);
		else if(pData[p2][pScoreMecha] >= 3500) format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/3500]\t"WHITE_E"5\n", string, pData[p2][pScoreMecha]);
	}
	if(pData[p2][pScoreFarmer] != -1)
	{
		if(pData[p2][pScoreFarmer] <= 1500) format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/1500]\t"WHITE_E"1\n", string, pData[p2][pScoreFarmer]);
		else if(pData[p2][pScoreFarmer] <= 3500) format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/3500]\t"WHITE_E"2\n", string, pData[p2][pScoreFarmer]);
		else if(pData[p2][pScoreFarmer] <= 6500) format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/6500]\t"WHITE_E"3\n", string, pData[p2][pScoreFarmer]);
		else if(pData[p2][pScoreFarmer] <= 8500) format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/8500]\t"WHITE_E"4\n", string, pData[p2][pScoreFarmer]);
		else if(pData[p2][pScoreFarmer] >= 8500) format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/8500]\t"WHITE_E"5\n", string, pData[p2][pScoreFarmer]);
	}
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Skills Player", string,"Close","");
	return 1;
}

GetPlayerGender(playerid)
{
	new gender[26];
	switch(pData[playerid][pGender]) 	
	{
		case 1: gender = "Male";
		case 2: gender = "Female";
	}
	return gender;
}

GetPlayerAccent(playerid) 
{
	new accent[26];
	switch(pData[playerid][pAccent1]) 	
	{
		case 0: accent = "United States Of America";
		case 1: accent = "Singapore";
		case 2: accent = "Indonesia";
		case 3: accent = "Afganistan";
		case 4: accent = "Albania";
		case 5: accent = "Pakistan";
		case 6: accent = "Phillpines";
		case 7: accent = "Russian";
		case 8: accent = "Qatar";
		case 9: accent = "Spanish";
		case 10: accent = "Argentina";
		case 11: accent = "Arabic";
		case 12: accent = "Australia";
		case 13: accent = "Bangladesh";
		case 14: accent = "Brazil";
		case 15: accent = "Bulgaria";
		case 16: accent = "Canada";
		case 17: accent = "China";
		case 18: accent = "Colombia";
		case 19: accent = "Congo";
		case 20: accent = "Denmark";
		case 21: accent = "Italian";
		case 22: accent = "Germany";
		case 23: accent = "HongKong";
		case 24: accent = "India";
		case 25: accent = "Iran";
		case 26: accent = "Iraq";
		case 27: accent = "Jamaica";
		case 28: accent = "Japan";
		case 29: accent = "Korea";
		case 30: accent = "Mexico";
	}
	return accent;
}

GetLicenseDriver(playerid) 
{
	new str[512];
	if(pData[playerid][pDriveLic] == 1) 
	{
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pDriveLicTime]));
	}
	else if(pData[playerid][pDriveLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pDriveLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pDriveLicTime])); 
	}
	
	return str;
}

GetLicenseFly(playerid) 
{
	new str[500];
	if(pData[playerid][pFlyLic] == 1) 
	{ 
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pFlyLicTime])); 
	}
	else if(pData[playerid][pFlyLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pFlyLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pFlyLicTime])); 
	}
	
	return str;
}

GetLicenseBoat(playerid) 
{
	new str[500];
	if(pData[playerid][pBoatLic] == 1) 
	{ 
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pBoatLicTime])); 
	}
	else if(pData[playerid][pBoatLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pBoatLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]",  ConvertTimestamp(Timestamp:pData[playerid][pBoatLicTime])); 
	}
	return str;
}

GetLicenseGun(playerid) 
{
	new str[500];
	if(pData[playerid][pGunLic] == 1) 
	{ 
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pGunLicTime])); 
	}
	else if(pData[playerid][pGunLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pGunLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pGunLicTime])); 
	}
	
	return str;
}

GetLicenseTrucker(playerid) 
{
	new str[500];
	if(pData[playerid][pTruckerLic] == 1) 
	{ 
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pTruckerLicTime])); 
	}
	else if(pData[playerid][pTruckerLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pTruckerLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pTruckerLicTime])); 
	}
	
	return str;
}

GetLicenseLumber(playerid) 
{
	new str[500];
	if(pData[playerid][pLumberLic] == 1) 
	{ 
		format(str, sizeof(str), ""WHITE_E"["GREEN_E"Valid until %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pLumberLicTime])); 
	}
	else if(pData[playerid][pLumberLic] == 0)
	{ 
		format(str, sizeof(str), ""WHITE_E"[{FF0000}Not passed"WHITE_E"]"); 
	} 
	else if(pData[playerid][pLumberLic] == 2)
	{ 
		format(str, sizeof(str), ""WHITE_E"["RED_E"Experied %s"WHITE_E"]", ConvertTimestamp(Timestamp:pData[playerid][pLumberLicTime])); 
	}
	
	return str;
}

//----------[ Vehicle Native ]---------
IsVehicleEmpty(vehicleid)
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
			if(IsPlayerInVehicle(i, vehicleid)) return 0;
	}
	return 1;
}

JB_IsBicycle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 481, 509, 510: return 1;
	}
	return 0;
}

IsABoat(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return 1;
    }
    return 0;
}

IsABike(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 448, 461..463, 468, 521..523, 581, 586, 481, 509, 510: return 1;
    }
    return 0;
}

IsAPlane(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 460, 464, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return 1;
    }
    return 0;
}

IsAHelicopter(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: return 1;
    }
    return 0;
}

IsATowTruck(vehicleid)
{
	if(GetVehicleModel(vehicleid) == 485 || GetVehicleModel(vehicleid) == 525 || GetVehicleModel(vehicleid) == 583 || GetVehicleModel(vehicleid) == 574)
	{
		return 1;
	}
	return 0;
}

IsATruckCrate(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
	    case 456, 414, 499, 455: return 1;
	    default: return 0;
	}

	return 0;
}

IsAPickup(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 478, 422, 543, 554: return 1;
    }
    return 0;
}

IsAMechanic(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 422, 543, 525: return 1;
    }
    return 0;
}

IsAVehicleTransfender(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 400, 401, 402, 404, 405, 409, 410, 411, 415, 418, 419, 420,
		421, 422, 426, 429, 436, 438, 439, 442, 445, 451, 458, 466, 467, 
		474, 475, 477, 478, 479, 480, 489, 491, 492, 496, 500, 506, 507, 
		516, 517, 518, 526, 527, 529, 533, 540, 541, 542, 545, 546, 547, 
		549, 550, 551, 555, 579, 580, 585, 587, 589, 600, 602, 603: return 1;
    }
    return 0;
}

IsAVehicleNone(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 403, 406, 407, 408, 413, 414, 416, 417, 423, 424, 425, 427, 
		428, 430, 431, 432, 433, 434, 435, 436, 437, 440, 441, 443, 444,
		446, 447, 448, 449, 450, 452, 453, 454, 455, 456, 457, 459, 460, 
		461, 462, 463, 464, 465, 468, 469, 470, 471, 472, 473, 476, 481, 
		482, 483, 484, 485, 486, 487, 488, 490, 493, 494, 495, 497, 498,
		499, 501, 502, 503, 504, 505, 508, 509, 510, 511, 512, 513, 514,
		515, 519, 520, 521, 522, 523, 524, 525, 528, 530, 531, 532, 537,
		538, 539, 543, 544, 548, 552, 553, 554, 556, 557, 563, 564, 568,
		569, 570, 572, 573, 574, 577, 578, 581, 582, 583, 584, 586, 588,
		590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 601, 604, 605, 
		606, 607, 608, 609, 610, 611: return 1;
    }
    return 0;
}

IsAVehicleWaaLocolow(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 412, 534, 535, 536, 558, 559, 560, 561, 562, 565, 566, 567,
		575, 576: return 1;
    }
    return 0;
}

IsEngineVehicle(vehicleid)
{
    static const g_aEngineStatus[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
    };
    new modelid = GetVehicleModel(vehicleid);

    if(modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

GetVehicleMaxSeats(vehicleid)
{
    static const g_arrMaxSeats[] = {
        4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
        1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4, 4,
        2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2,
        4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
        4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 4,
        4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0, 4,
        0, 0
    };
    new
        model = GetVehicleModel(vehicleid);

    if(400 <= model <= 611)
        return g_arrMaxSeats[model - 400];

    return 0;
}

RemoveFromVehicle(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        static
        Float:fX,
        Float:fY,
        Float:fZ;

        GetPlayerPos(playerid, fX, fY, fZ);
        SetPlayerPos(playerid, fX, fY, fZ + 1.5);
    }
    return 1;
}

GetAvailableSeat(vehicleid, start = 1)
{
    new seats = GetVehicleMaxSeats(vehicleid);

    for (new i = start; i < seats; i ++) if(!IsVehicleSeatUsed(vehicleid, i)) {
        return i;
    }
    return -1;
}

IsVehicleSeatUsed(vehicleid, seat)
{
    foreach (new i : Player) if(IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seat) {
        return 1;
    }
    return 0;
}

//----------[ Other Native]----------

GetFightStyleName(playerid)
{
	new accent[212];
	switch(pData[playerid][FightStyle])
	{
		case 0: accent = "Fight Style Normal";
		case 4: accent = "Fight Style Normal";
		case 5: accent = "Fight Style Boxing";
		case 6: accent = "Fight Style Kunfu";
		case 7: accent = "Fight Style Kneehead";
		case 15: accent = "Fight Style Grabkick";
		case 16: accent = "Fight Style Elbow";
	}
	return accent;
}

GetVehicleCost(carid)
{
	//Ini Kendaraan saat beli pakai uang IC

	//Category kendaraan laut
	if(carid == 453) return 125000; //Reefer
	if(carid == 452) return 350000; //Speeder
	if(carid == 473) return 75000; //Dinghy
	if(carid == 484) return 520000; //Marquis
	if(carid == 493) return 650000; //Jetmax
	if(carid == 446) return 380000; //Squalo

	//Category Kendaraan Bike
	if(carid == 481) return 35000;  //Bmx
	if(carid == 509) return 25000; //Bike
	if(carid == 510) return 25000; //Mt bike
	if(carid == 463) return 100000; //Freeway
	if(carid == 521) return 550000; //Fcr 900
	if(carid == 461) return 175000; //Pcj 600
	if(carid == 581) return 125000; //Bf
	if(carid == 468) return 95000; //Sanchez
	if(carid == 586) return 75000; //Wayfarer
	if(carid == 462) return 55000; //Faggio

	//Category Kendaraan Cars
	if(carid == 445) return 175000; //Admiral
	if(carid == 496) return 170000; //Blista Compact
	if(carid == 401) return 150000; //Bravura
	if(carid == 518) return 80000; //Buccaneer
	if(carid == 527) return 130000; //Cadrona
	if(carid == 483) return 125000; //Camper
	if(carid == 542) return 95000; //Clover
	if(carid == 589) return 140000; //Club
	if(carid == 507) return 150000; //Elegant
	if(carid == 540) return 132000; //Vincent
	if(carid == 585) return 115000; //Emperor
	if(carid == 419) return 10000; //Esperanto
	if(carid == 526) return 95000; //Fortune
	if(carid == 466) return 120000; //Glendale
	if(carid == 492) return 125000; //Greenwood
	if(carid == 474) return 150000; //Hermes
	if(carid == 546) return 156000; //Intruder
	if(carid == 517) return 125000; //Majestic
	if(carid == 410) return 140000; //Manana
	if(carid == 551) return 140000; //Merit
	if(carid == 516) return 140000; //Nebula
	if(carid == 467) return 125000; //Oceanic
	if(carid == 404) return 132000; //Perenniel
	if(carid == 600) return 125000; //Picador
	if(carid == 426) return 125000; //Premier
	if(carid == 436) return 116000; //Previon
	if(carid == 547) return 121000; //Primo
	if(carid == 405) return 122000; //Sentinel
	if(carid == 458) return 133000; //Solair
	if(carid == 439) return 135000; //Stallion
	if(carid == 550) return 240000; //Sunrise
	if(carid == 566) return 120000; //Tahoma
	if(carid == 549) return 100000; //Tampa
	if(carid == 491) return 100000; //Virgo
	if(carid == 412) return 100000; //Voodoo
	if(carid == 421) return 220000; //Washington
	if(carid == 529) return 300000; //Willard
	if(carid == 555) return 130000; //Windsor
	if(carid == 580) return 160000; //Stafford
	if(carid == 475) return 130000; //Sabre
	if(carid == 545) return 150000; //Hustler
	
	//Category Kendaraan Lowriders
	if(carid == 536) return 110000; //Blade
	if(carid == 575) return 85000; //Broadway
	if(carid == 533) return 130000; //Feltzer
	if(carid == 534) return 130000; //Remington
	if(carid == 567) return 150000; //Savanna
	if(carid == 535) return 100000; //Slamvan
	if(carid == 576) return 130000; //Tornado
	if(carid == 566) return 150000; //Tahoma
	if(carid == 412) return 100000; //Voodoo
	
	//Category Kendaraan SUVS Cars
	if(carid == 579) return 240000; //Huntley
	if(carid == 400) return 210000; //Landstalker
	if(carid == 500) return 220000; //Mesa
	if(carid == 489) return 250000; //Rancher
	if(carid == 479) return 210000; //Regina
	if(carid == 482) return 230000; //Burrito
	if(carid == 418) return 270000; //Moonbeam
	if(carid == 413) return 210000; //Pony
	//if(carid == 554) return 18000; //Yosemite
	
	//Category Kendaraan Sports
	if(carid == 602) return 185000; //Alpha
	if(carid == 429) return 850000; //Banshee
	if(carid == 562) return 350000; //Elegy
	if(carid == 587) return 250000; //Euros
	if(carid == 565) return 320000; //Flash
	if(carid == 559) return 250000; //Jester
	if(carid == 561) return 220000; //Stratum
	if(carid == 560) return 670000; //Sultan
	if(carid == 506) return 580000; //Super GT
	if(carid == 558) return 150000; //Uranus
	if(carid == 477) return 380000; //Zr-350
	if(carid == 480) return 270000; //Comet
	
	//Category Kendaraan Non Dealer
	if(carid == 434) return 1200000; //Hotknife
	if(carid == 502) return 1500000; //Hotring Racer
	if(carid == 495) return 2000000; //Sandking
	if(carid == 451) return 1300000; //Turismo
	if(carid == 470) return 2000000; //Patriot
	if(carid == 424) return 150000; //BF Injection
	if(carid == 522) return 700000; //Nrg
	if(carid == 411) return 1250000; //Infernus
	if(carid == 541) return 950000; //Bullet
	if(carid == 504) return 1200000; //Bloodring Banger
	if(carid == 603) return 700000; //Phoenix
	if(carid == 415) return 1200000; //Cheetah
	if(carid == 402) return 250000; //Buffalo
	if(carid == 508) return 500000; //Journey
	if(carid == 457) return 2500000; //Caddy
	if(carid == 471) return 700000; //Quad

	//Category Kendaraan Job
	if(carid == 420) return 85000; //Taxi
	if(carid == 438) return 55000; //Cabbie
	if(carid == 403) return 250000; //Linerunner
	if(carid == 414) return 75000; //Mule
	if(carid == 422) return 125000; //Bobcat
	if(carid == 440) return 150000; //Rumpo
	if(carid == 455) return 200000; //Flatbead
	if(carid == 456) return 75000; //Yankee
	if(carid == 478) return 90000; //Walton
	if(carid == 498) return 100000; //Boxville
	if(carid == 499) return 75000; //Benson
	if(carid == 514) return 250000; //Tanker
	if(carid == 515) return 400000; //Roadtrain
	if(carid == 524) return 200000; //Cement Truck
	if(carid == 525) return 85000; //Towtruck
	if(carid == 543) return 90000; //Sadler
	if(carid == 552) return 200000; //Utility Van
	if(carid == 554) return 150000; //Yosemite
	if(carid == 578) return 200000; //DFT-30
	if(carid == 609) return 100000; //Boxville
	if(carid == 423) return 120000; //Mr Whoopee/Ice cream
	if(carid == 588) return 100000; //Hotdog
 	return -1;
}

GetVehicleDealerCost(carid)
{
	if(carid == 401) return 230000; //Bravura
	if(carid == 585) return 950000;  //Emperor
	if(carid == 546) return 220000; //Intruder
	if(carid == 547) return 220000; //Primo
	if(carid == 549) return 260000; //Tampa
	if(carid == 560) return 560000; //Sultan
	if(carid == 550) return 280000; //Sunrise
	if(carid == 551) return 210000; //Merit
	if(carid == 562) return 530000; //Elegy
	if(carid == 540) return 210000; //Vincent
	if(carid == 542) return 280000; //Clover
	if(carid == 529) return 260000; //Willard
	if(carid == 527) return 85000; //Cadrona
	if(carid == 517) return 210000; //Majestic
	if(carid == 518) return 200000; //Buccaneer
	if(carid == 507) return 140000; //Elegant
	if(carid == 516) return 210000; //Nebula
	if(carid == 492) return 180000; //Greenwood
	if(carid == 491) return 170000; //Virgo
	if(carid == 474) return 90000; //Hermes
	if(carid == 436) return 220000; //Previon
	if(carid == 445) return 250000; //Admiral
	if(carid == 419) return 100000; //Esperanto
	if(carid == 426) return 290000; //Premier
	if(carid == 421) return 230000; //Washington
	if(carid == 410) return 200000; //Manana
	if(carid == 405) return 190000; //Sentinel
	if(carid == 466) return 200000; //Glendale
	if(carid == 467) return 190000; //Oceanic
	if(carid == 581) return 160000; //BF-400
	if(carid == 586) return 140000; //Wayfarer
	if(carid == 521) return 540000; //FCR-900
	if(carid == 468) return 100000; //Sanchez
	if(carid == 471) return 310000; //Quad
	if(carid == 462) return 60000; //Faggio
	if(carid == 463) return 190000; //Freeway
	if(carid == 461) return 180000; //PCJ-600
	if(carid == 404) return 190000; //Perenniel
	if(carid == 458) return 380000; //Solair
	if(carid == 561) return 400000; //Stratum
	if(carid == 479) return 290000; //Regina
	if(carid == 418) return 290000; //Moonbeam
	if(carid == 534) return 290000; //Remington
	if(carid == 535) return 390000; //Slamvan
	if(carid == 536) return 290000; //Blade
	if(carid == 566) return 270000; //Tahoma
	if(carid == 567) return 270000; //Savanna
	if(carid == 575) return 250000; //Broadway
	if(carid == 576) return 180000; //Tornado
	if(carid == 412) return 190000; //Voodoo
	if(carid == 400) return 320000; //Landstalker
	if(carid == 500) return 360000; //Mesa
	if(carid == 579) return 500000; //Huntley
	if(carid == 554) return 390000; //Yosemite
	if(carid == 545) return 300000; //Hustler
	if(carid == 483) return 125000; //Camper
	if(carid == 508) return 490000; //Journey
	if(carid == 480) return 350000; //Comet
	if(carid == 439) return 430000; //Stallion
	if(carid == 533) return 420000; //Feltzer
	if(carid == 413) return 230000; //Pony
	if(carid == 543) return 140000; //Sadler
	if(carid == 422) return 170000; //Bobcat
	if(carid == 478) return 120000; //Walton
	if(carid == 482) return 95000; //Burrito
	if(carid == 600) return 130000; //Picador
	if(carid == 602) return 220000; //Alpha
	if(carid == 587) return 250000; //Euros
	if(carid == 589) return 330000; //Club
	if(carid == 565) return 330000; //Flash
	if(carid == 559) return 250000; //Jester
	if(carid == 558) return 150000; //Uranus
	if(carid == 429) return 900000; //Banshee
	if(carid == 402) return 280000; //Bufallo
	if(carid == 415) return 750000; //Cheetah
	if(carid == 475) return 170000; //Sabre
	if(carid == 477) return 380000; //ZR-350
	if(carid == 496) return 150000; //Blista Compact
 	return -1;
}

GetVehicleCostVIP(carid)
{
	if(carid == 522) return 2000000; //NRG-500
	if(carid == 411) return 1500000; //Infernus
	if(carid == 451) return 1250000; //Turismo
	if(carid == 494) return 1250000; //Hotring
	if(carid == 541) return 1100000; //Bullet
	if(carid == 573) return 2000000; //Duneride
 	return -1;
}

SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
    static
        args,
            str[144];

    if((args = numargs()) == 3)
    {
            SendClientMessage(playerid, color, text);
    }
    else
    {
        while (--args >= 3)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit PUSH.S 8
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessage(playerid, color, str);

        #emit RETN
    }
    return 1;
}

SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
    static
        args,
            str[144];

    if((args = numargs()) == 2)
    {
            SendClientMessageToAll(color, text);
    }
    else
    {
        while (--args >= 2)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessageToAll(color, str);

        #emit RETN
    }
    return 1;
}

SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 16)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 16); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit CONST.alt 4
        #emit SUB
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(NearPlayer(i, playerid, radius)) {
                SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(NearPlayer(i, playerid, radius)) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}

SetPlayerPosition(playerid, Float:X, Float:Y, Float:Z, Float:a, inter = 0)
{
    SetPlayerInterior(playerid, inter);
    SetPlayerPos(playerid, X, Y, Z);
	SetPlayerFacingAngle(playerid, a);
	SetCameraBehindPlayer(playerid);
	//SetPlayerWorldBounds(playerid, 20000, -20000, 20000, -20000);
}

SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, Float:a, time = 2000)
{
    if(pData[playerid][pFreeze])
    {
        KillTimer(pData[playerid][pFreezeTimer]);
        pData[playerid][pFreeze] = 0;
        TogglePlayerControllable(playerid, 1);
    }
	TogglePlayerControllable(playerid, 0);
    SetCameraBehindPlayer(playerid);
    pData[playerid][pFreeze] = 1;
    SetPlayerPos(playerid, x, y, z + 0.5);
	SetPlayerFacingAngle(playerid, a);
	pData[playerid][pPosX] = x;
	pData[playerid][pPosY] = y;
	pData[playerid][pPosZ] = z;
	pData[playerid][pPosA] = a;
	pData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "iffff", playerid, x, y, z, a);
}

SendPlayerToPlayer(playerid, targetid)
{
    new
        Float:x,
        Float:y,
        Float:z;
		
	if(pData[targetid][pSpawned] == 0 || pData[playerid][pSpawned] == 0)
	{
		Error(playerid, "Player/Target sedang tidak spawn!");
		return 1;
	}
	if(pData[playerid][pJail] > 0 || pData[targetid][pJail] > 0)
		return Error(playerid, "Player/Target sedang di jail");
		
	if(pData[playerid][pArrest] > 0 || pData[targetid][pArrest] > 0)
		return Error(playerid, "Player/Target sedang di arrest");
		
    GetPlayerPos(targetid, x, y, z);

    if(IsPlayerInAnyVehicle(playerid))
    {
        SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
        LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
    }
    else
    {
        SetPlayerPosition(playerid, x + 1, y, z, 750);
    }
    SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

    pData[playerid][pInHouse] = pData[targetid][pInHouse];
    pData[playerid][pInBiz] = pData[targetid][pInBiz];
    pData[playerid][pInDoor] = pData[targetid][pInDoor];
    return 1;
}

ProxDetector(Float: f_Radius, playerid, string[],col1,col2,col3,col4,col5) 
{
		new
			Float: f_playerPos[3];

		GetPlayerPos(playerid, f_playerPos[0], f_playerPos[1], f_playerPos[2]);
		foreach(new i : Player) 
		{
			if(!pData[i][pSPY]) 
			{
				if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) 
				{
					if(IsPlayerInRangeOfPoint(i, f_Radius / 16, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
						SendClientMessage(i, col1, string);
					}
					else if(IsPlayerInRangeOfPoint(i, f_Radius / 8, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
						SendClientMessage(i, col2, string);
					}
					else if(IsPlayerInRangeOfPoint(i, f_Radius / 4, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
						SendClientMessage(i, col3, string);
					}
					else if(IsPlayerInRangeOfPoint(i, f_Radius / 2, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
						SendClientMessage(i, col4, string);
					}
					else if(IsPlayerInRangeOfPoint(i, f_Radius, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
						SendClientMessage(i, col5, string);
					}
				}
			}
			else SendClientMessage(i, col1, string);
		}
		return 1;
}

NearPlayer(playerid, targetid, Float:radius)
{
    static
        Float:fX,
        Float:fY,
        Float:fZ;

    GetPlayerPos(targetid, fX, fY, fZ);

    return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock GetPlayerLocationEx(playerid, &Float:fX, &Float:fY, &Float:fZ)
{
    new
        id = -1;

    if((id = House_Inside(playerid)) != -1)
    {
        fX = hData[id][hExtposX];
        fY = hData[id][hExtposY];
        fZ = hData[id][hExtposZ];
    }
    else if((id = Business_Inside(playerid)) != -1)
    {
        fX = bData[id][bExtposX];
        fY = bData[id][bExtposY];
        fZ = bData[id][bExtposZ];
    }
   	else if((id = Entrance_Inside(playerid)) != -1)
   	{
    	fX = dData[id][dExtposX];
    	fY = dData[id][dExtposY];
 	    fZ = dData[id][dExtposZ];
   	}
    else GetPlayerPos(playerid, fX, fY, fZ);
    return 1;
}

GetPlayerLocation(playerid)
{
    new
        Float:fX,
        Float:fY,
        Float:fZ,
        string[32],
        id = -1;

    if((id = House_Inside(playerid)) != -1)
    {
        fX = hData[id][hExtposX];
        fY = hData[id][hExtposY];
        fZ = hData[id][hExtposZ];
    }
    else if((id = Business_Inside(playerid)) != -1)
    {
        fX = bData[id][bExtposX];
        fY = bData[id][bExtposY];
        fZ = bData[id][bExtposZ];
    }
   	else if((id = Entrance_Inside(playerid)) != -1)
	{
	   	fX = dData[id][dExtposX];
	    fY = dData[id][dExtposY];
	    fZ = dData[id][dExtposZ];
    }
    else GetPlayerPos(playerid, fX, fY, fZ);

    format(string, 32, GetLocation(fX, fY, fZ));
    return string;
}

GetLocation(Float:fX, Float:fY, Float:fZ)
{
    enum e_ZoneData
    {
            e_ZoneName[32 char],
        Float:e_ZoneArea[6]
    };
    static const g_arrZoneData[][e_ZoneData] =
    {
        {!"The Big Ear",                {-410.00, 1403.30, -3.00, -137.90, 1681.20, 200.00}},
        {!"Aldea Malvada",                {-1372.10, 2498.50, 0.00, -1277.50, 2615.30, 200.00}},
        {!"Angel Pine",                   {-2324.90, -2584.20, -6.10, -1964.20, -2212.10, 200.00}},
        {!"Arco del Oeste",               {-901.10, 2221.80, 0.00, -592.00, 2571.90, 200.00}},
        {!"Avispa Country Club",          {-2646.40, -355.40, 0.00, -2270.00, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2831.80, -430.20, -6.10, -2646.40, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2361.50, -417.10, 0.00, -2270.00, -355.40, 200.00}},
        {!"Avispa Country Club",          {-2667.80, -302.10, -28.80, -2646.40, -262.30, 71.10}},
        {!"Avispa Country Club",          {-2470.00, -355.40, 0.00, -2270.00, -318.40, 46.10}},
        {!"Avispa Country Club",          {-2550.00, -355.40, 0.00, -2470.00, -318.40, 39.70}},
        {!"Back o Beyond",                {-1166.90, -2641.10, 0.00, -321.70, -1856.00, 200.00}},
        {!"Battery Point",                {-2741.00, 1268.40, -4.50, -2533.00, 1490.40, 200.00}},
        {!"Bayside",                      {-2741.00, 2175.10, 0.00, -2353.10, 2722.70, 200.00}},
        {!"Bayside Marina",               {-2353.10, 2275.70, 0.00, -2153.10, 2475.70, 200.00}},
        {!"Beacon Hill",                  {-399.60, -1075.50, -1.40, -319.00, -977.50, 198.50}},
        {!"Blackfield",                   {964.30, 1203.20, -89.00, 1197.30, 1403.20, 110.90}},
        {!"Blackfield",                   {964.30, 1403.20, -89.00, 1197.30, 1726.20, 110.90}},
        {!"Blackfield Chapel",            {1375.60, 596.30, -89.00, 1558.00, 823.20, 110.90}},
        {!"Blackfield Chapel",            {1325.60, 596.30, -89.00, 1375.60, 795.00, 110.90}},
        {!"Blackfield Intersection",      {1197.30, 1044.60, -89.00, 1277.00, 1163.30, 110.90}},
        {!"Blackfield Intersection",      {1166.50, 795.00, -89.00, 1375.60, 1044.60, 110.90}},
        {!"Blackfield Intersection",      {1277.00, 1044.60, -89.00, 1315.30, 1087.60, 110.90}},
        {!"Blackfield Intersection",      {1375.60, 823.20, -89.00, 1457.30, 919.40, 110.90}},
        {!"Blueberry",                    {104.50, -220.10, 2.30, 349.60, 152.20, 200.00}},
        {!"Blueberry",                    {19.60, -404.10, 3.80, 349.60, -220.10, 200.00}},
        {!"Blueberry Acres",              {-319.60, -220.10, 0.00, 104.50, 293.30, 200.00}},
        {!"Caligula's Palace",            {2087.30, 1543.20, -89.00, 2437.30, 1703.20, 110.90}},
        {!"Caligula's Palace",            {2137.40, 1703.20, -89.00, 2437.30, 1783.20, 110.90}},
        {!"Calton Heights",               {-2274.10, 744.10, -6.10, -1982.30, 1358.90, 200.00}},
        {!"Chinatown",                    {-2274.10, 578.30, -7.60, -2078.60, 744.10, 200.00}},
        {!"City Hall",                    {-2867.80, 277.40, -9.10, -2593.40, 458.40, 200.00}},
        {!"Come-A-Lot",                   {2087.30, 943.20, -89.00, 2623.10, 1203.20, 110.90}},
        {!"Commerce",                     {1323.90, -1842.20, -89.00, 1701.90, -1722.20, 110.90}},
        {!"Commerce",                     {1323.90, -1722.20, -89.00, 1440.90, -1577.50, 110.90}},
        {!"Commerce",                     {1370.80, -1577.50, -89.00, 1463.90, -1384.90, 110.90}},
        {!"Commerce",                     {1463.90, -1577.50, -89.00, 1667.90, -1430.80, 110.90}},
        {!"Commerce",                     {1583.50, -1722.20, -89.00, 1758.90, -1577.50, 110.90}},
        {!"Commerce",                     {1667.90, -1577.50, -89.00, 1812.60, -1430.80, 110.90}},
        {!"Conference Center",            {1046.10, -1804.20, -89.00, 1323.90, -1722.20, 110.90}},
        {!"Conference Center",            {1073.20, -1842.20, -89.00, 1323.90, -1804.20, 110.90}},
        {!"Cranberry Station",            {-2007.80, 56.30, 0.00, -1922.00, 224.70, 100.00}},
        {!"Creek",                        {2749.90, 1937.20, -89.00, 2921.60, 2669.70, 110.90}},
        {!"Dillimore",                    {580.70, -674.80, -9.50, 861.00, -404.70, 200.00}},
        {!"Doherty",                      {-2270.00, -324.10, -0.00, -1794.90, -222.50, 200.00}},
        {!"Doherty",                      {-2173.00, -222.50, -0.00, -1794.90, 265.20, 200.00}},
        {!"Downtown",                     {-1982.30, 744.10, -6.10, -1871.70, 1274.20, 200.00}},
        {!"Downtown",                     {-1871.70, 1176.40, -4.50, -1620.30, 1274.20, 200.00}},
        {!"Downtown",                     {-1700.00, 744.20, -6.10, -1580.00, 1176.50, 200.00}},
        {!"Downtown",                     {-1580.00, 744.20, -6.10, -1499.80, 1025.90, 200.00}},
        {!"Downtown",                     {-2078.60, 578.30, -7.60, -1499.80, 744.20, 200.00}},
        {!"Downtown",                     {-1993.20, 265.20, -9.10, -1794.90, 578.30, 200.00}},
        {!"Downtown Los Santos",          {1463.90, -1430.80, -89.00, 1724.70, -1290.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1430.80, -89.00, 1812.60, -1250.90, 110.90}},
        {!"Downtown Los Santos",          {1463.90, -1290.80, -89.00, 1724.70, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1384.90, -89.00, 1463.90, -1170.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1250.90, -89.00, 1812.60, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1170.80, -89.00, 1463.90, -1130.80, 110.90}},
        {!"Downtown Los Santos",          {1378.30, -1130.80, -89.00, 1463.90, -1026.30, 110.90}},
        {!"Downtown Los Santos",          {1391.00, -1026.30, -89.00, 1463.90, -926.90, 110.90}},
        {!"Downtown Los Santos",          {1507.50, -1385.20, 110.90, 1582.50, -1325.30, 335.90}},
        {!"East Beach",                   {2632.80, -1852.80, -89.00, 2959.30, -1668.10, 110.90}},
        {!"East Beach",                   {2632.80, -1668.10, -89.00, 2747.70, -1393.40, 110.90}},
        {!"East Beach",                   {2747.70, -1668.10, -89.00, 2959.30, -1498.60, 110.90}},
        {!"East Beach",                   {2747.70, -1498.60, -89.00, 2959.30, -1120.00, 110.90}},
        {!"East Los Santos",              {2421.00, -1628.50, -89.00, 2632.80, -1454.30, 110.90}},
        {!"East Los Santos",              {2222.50, -1628.50, -89.00, 2421.00, -1494.00, 110.90}},
        {!"East Los Santos",              {2266.20, -1494.00, -89.00, 2381.60, -1372.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1494.00, -89.00, 2421.00, -1454.30, 110.90}},
        {!"East Los Santos",              {2281.40, -1372.00, -89.00, 2381.60, -1135.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1454.30, -89.00, 2462.10, -1135.00, 110.90}},
        {!"East Los Santos",              {2462.10, -1454.30, -89.00, 2581.70, -1135.00, 110.90}},
        {!"Easter Basin",                 {-1794.90, 249.90, -9.10, -1242.90, 578.30, 200.00}},
        {!"Easter Basin",                 {-1794.90, -50.00, -0.00, -1499.80, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1499.80, -50.00, -0.00, -1242.90, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1794.90, -730.10, -3.00, -1213.90, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -730.10, 0.00, -1132.80, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1242.90, -50.00, 0.00, -1213.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -50.00, -4.50, -947.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1315.40, -405.30, 15.40, -1264.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1354.30, -287.30, 15.40, -1315.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1490.30, -209.50, 15.40, -1264.40, -148.30, 25.40}},
        {!"Easter Bay Chemicals",         {-1132.80, -768.00, 0.00, -956.40, -578.10, 200.00}},
        {!"Easter Bay Chemicals",         {-1132.80, -787.30, 0.00, -956.40, -768.00, 200.00}},
        {!"El Castillo del Diablo",       {-464.50, 2217.60, 0.00, -208.50, 2580.30, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2123.00, -7.60, 114.00, 2337.10, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2337.10, 0.00, 8.40, 2487.10, 200.00}},
        {!"El Corona",                    {1812.60, -2179.20, -89.00, 1970.60, -1852.80, 110.90}},
        {!"El Corona",                    {1692.60, -2179.20, -89.00, 1812.60, -1842.20, 110.90}},
        {!"El Quebrados",                 {-1645.20, 2498.50, 0.00, -1372.10, 2777.80, 200.00}},
        {!"Esplanade East",               {-1620.30, 1176.50, -4.50, -1580.00, 1274.20, 200.00}},
        {!"Esplanade East",               {-1580.00, 1025.90, -6.10, -1499.80, 1274.20, 200.00}},
        {!"Esplanade East",               {-1499.80, 578.30, -79.60, -1339.80, 1274.20, 20.30}},
        {!"Esplanade North",              {-2533.00, 1358.90, -4.50, -1996.60, 1501.20, 200.00}},
        {!"Esplanade North",              {-1996.60, 1358.90, -4.50, -1524.20, 1592.50, 200.00}},
        {!"Esplanade North",              {-1982.30, 1274.20, -4.50, -1524.20, 1358.90, 200.00}},
        {!"Fallen Tree",                  {-792.20, -698.50, -5.30, -452.40, -380.00, 200.00}},
        {!"Fallow Bridge",                {434.30, 366.50, 0.00, 603.00, 555.60, 200.00}},
        {!"Fern Ridge",                   {508.10, -139.20, 0.00, 1306.60, 119.50, 200.00}},
        {!"Financial",                    {-1871.70, 744.10, -6.10, -1701.30, 1176.40, 300.00}},
        {!"Fisher's Lagoon",              {1916.90, -233.30, -100.00, 2131.70, 13.80, 200.00}},
        {!"Flint Intersection",           {-187.70, -1596.70, -89.00, 17.00, -1276.60, 110.90}},
        {!"Flint Range",                  {-594.10, -1648.50, 0.00, -187.70, -1276.60, 200.00}},
        {!"Fort Carson",                  {-376.20, 826.30, -3.00, 123.70, 1220.40, 200.00}},
        {!"Foster Valley",                {-2270.00, -430.20, -0.00, -2178.60, -324.10, 200.00}},
        {!"Foster Valley",                {-2178.60, -599.80, -0.00, -1794.90, -324.10, 200.00}},
        {!"Foster Valley",                {-2178.60, -1115.50, 0.00, -1794.90, -599.80, 200.00}},
        {!"Foster Valley",                {-2178.60, -1250.90, 0.00, -1794.90, -1115.50, 200.00}},
        {!"Frederick Bridge",             {2759.20, 296.50, 0.00, 2774.20, 594.70, 200.00}},
        {!"Gant Bridge",                  {-2741.40, 1659.60, -6.10, -2616.40, 2175.10, 200.00}},
        {!"Gant Bridge",                  {-2741.00, 1490.40, -6.10, -2616.40, 1659.60, 200.00}},
        {!"Ganton",                       {2222.50, -1852.80, -89.00, 2632.80, -1722.30, 110.90}},
        {!"Ganton",                       {2222.50, -1722.30, -89.00, 2632.80, -1628.50, 110.90}},
        {!"Garcia",                       {-2411.20, -222.50, -0.00, -2173.00, 265.20, 200.00}},
        {!"Garcia",                       {-2395.10, -222.50, -5.30, -2354.00, -204.70, 200.00}},
        {!"Garver Bridge",                {-1339.80, 828.10, -89.00, -1213.90, 1057.00, 110.90}},
        {!"Garver Bridge",                {-1213.90, 950.00, -89.00, -1087.90, 1178.90, 110.90}},
        {!"Garver Bridge",                {-1499.80, 696.40, -179.60, -1339.80, 925.30, 20.30}},
        {!"Glen Park",                    {1812.60, -1449.60, -89.00, 1996.90, -1350.70, 110.90}},
        {!"Glen Park",                    {1812.60, -1100.80, -89.00, 1994.30, -973.30, 110.90}},
        {!"Glen Park",                    {1812.60, -1350.70, -89.00, 2056.80, -1100.80, 110.90}},
        {!"Green Palms",                  {176.50, 1305.40, -3.00, 338.60, 1520.70, 200.00}},
        {!"Greenglass College",           {964.30, 1044.60, -89.00, 1197.30, 1203.20, 110.90}},
        {!"Greenglass College",           {964.30, 930.80, -89.00, 1166.50, 1044.60, 110.90}},
        {!"Hampton Barns",                {603.00, 264.30, 0.00, 761.90, 366.50, 200.00}},
        {!"Hankypanky Point",             {2576.90, 62.10, 0.00, 2759.20, 385.50, 200.00}},
        {!"Harry Gold Parkway",           {1777.30, 863.20, -89.00, 1817.30, 2342.80, 110.90}},
        {!"Hashbury",                     {-2593.40, -222.50, -0.00, -2411.20, 54.70, 200.00}},
        {!"Hilltop Farm",                 {967.30, -450.30, -3.00, 1176.70, -217.90, 200.00}},
        {!"Hunter Quarry",                {337.20, 710.80, -115.20, 860.50, 1031.70, 203.70}},
        {!"Idlewood",                     {1812.60, -1852.80, -89.00, 1971.60, -1742.30, 110.90}},
        {!"Idlewood",                     {1812.60, -1742.30, -89.00, 1951.60, -1602.30, 110.90}},
        {!"Idlewood",                     {1951.60, -1742.30, -89.00, 2124.60, -1602.30, 110.90}},
        {!"Idlewood",                     {1812.60, -1602.30, -89.00, 2124.60, -1449.60, 110.90}},
        {!"Idlewood",                     {2124.60, -1742.30, -89.00, 2222.50, -1494.00, 110.90}},
        {!"Idlewood",                     {1971.60, -1852.80, -89.00, 2222.50, -1742.30, 110.90}},
        {!"Jefferson",                    {1996.90, -1449.60, -89.00, 2056.80, -1350.70, 110.90}},
        {!"Jefferson",                    {2124.60, -1494.00, -89.00, 2266.20, -1449.60, 110.90}},
        {!"Jefferson",                    {2056.80, -1372.00, -89.00, 2281.40, -1210.70, 110.90}},
        {!"Jefferson",                    {2056.80, -1210.70, -89.00, 2185.30, -1126.30, 110.90}},
        {!"Jefferson",                    {2185.30, -1210.70, -89.00, 2281.40, -1154.50, 110.90}},
        {!"Jefferson",                    {2056.80, -1449.60, -89.00, 2266.20, -1372.00, 110.90}},
        {!"Julius Thruway East",          {2623.10, 943.20, -89.00, 2749.90, 1055.90, 110.90}},
        {!"Julius Thruway East",          {2685.10, 1055.90, -89.00, 2749.90, 2626.50, 110.90}},
        {!"Julius Thruway East",          {2536.40, 2442.50, -89.00, 2685.10, 2542.50, 110.90}},
        {!"Julius Thruway East",          {2625.10, 2202.70, -89.00, 2685.10, 2442.50, 110.90}},
        {!"Julius Thruway North",         {2498.20, 2542.50, -89.00, 2685.10, 2626.50, 110.90}},
        {!"Julius Thruway North",         {2237.40, 2542.50, -89.00, 2498.20, 2663.10, 110.90}},
        {!"Julius Thruway North",         {2121.40, 2508.20, -89.00, 2237.40, 2663.10, 110.90}},
        {!"Julius Thruway North",         {1938.80, 2508.20, -89.00, 2121.40, 2624.20, 110.90}},
        {!"Julius Thruway North",         {1534.50, 2433.20, -89.00, 1848.40, 2583.20, 110.90}},
        {!"Julius Thruway North",         {1848.40, 2478.40, -89.00, 1938.80, 2553.40, 110.90}},
        {!"Julius Thruway North",         {1704.50, 2342.80, -89.00, 1848.40, 2433.20, 110.90}},
        {!"Julius Thruway North",         {1377.30, 2433.20, -89.00, 1534.50, 2507.20, 110.90}},
        {!"Julius Thruway South",         {1457.30, 823.20, -89.00, 2377.30, 863.20, 110.90}},
        {!"Julius Thruway South",         {2377.30, 788.80, -89.00, 2537.30, 897.90, 110.90}},
        {!"Julius Thruway West",          {1197.30, 1163.30, -89.00, 1236.60, 2243.20, 110.90}},
        {!"Julius Thruway West",          {1236.60, 2142.80, -89.00, 1297.40, 2243.20, 110.90}},
        {!"Juniper Hill",                 {-2533.00, 578.30, -7.60, -2274.10, 968.30, 200.00}},
        {!"Juniper Hollow",               {-2533.00, 968.30, -6.10, -2274.10, 1358.90, 200.00}},
        {!"K.A.C.C. Military Fuels",      {2498.20, 2626.50, -89.00, 2749.90, 2861.50, 110.90}},
        {!"Kincaid Bridge",               {-1339.80, 599.20, -89.00, -1213.90, 828.10, 110.90}},
        {!"Kincaid Bridge",               {-1213.90, 721.10, -89.00, -1087.90, 950.00, 110.90}},
        {!"Kincaid Bridge",               {-1087.90, 855.30, -89.00, -961.90, 986.20, 110.90}},
        {!"King's",                       {-2329.30, 458.40, -7.60, -1993.20, 578.30, 200.00}},
        {!"King's",                       {-2411.20, 265.20, -9.10, -1993.20, 373.50, 200.00}},
        {!"King's",                       {-2253.50, 373.50, -9.10, -1993.20, 458.40, 200.00}},
        {!"LVA Freight Depot",            {1457.30, 863.20, -89.00, 1777.40, 1143.20, 110.90}},
        {!"LVA Freight Depot",            {1375.60, 919.40, -89.00, 1457.30, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1277.00, 1087.60, -89.00, 1375.60, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1315.30, 1044.60, -89.00, 1375.60, 1087.60, 110.90}},
        {!"LVA Freight Depot",            {1236.60, 1163.40, -89.00, 1277.00, 1203.20, 110.90}},
        {!"Las Barrancas",                {-926.10, 1398.70, -3.00, -719.20, 1634.60, 200.00}},
        {!"Las Brujas",                   {-365.10, 2123.00, -3.00, -208.50, 2217.60, 200.00}},
        {!"Las Colinas",                  {1994.30, -1100.80, -89.00, 2056.80, -920.80, 110.90}},
        {!"Las Colinas",                  {2056.80, -1126.30, -89.00, 2126.80, -920.80, 110.90}},
        {!"Las Colinas",                  {2185.30, -1154.50, -89.00, 2281.40, -934.40, 110.90}},
        {!"Las Colinas",                  {2126.80, -1126.30, -89.00, 2185.30, -934.40, 110.90}},
        {!"Las Colinas",                  {2747.70, -1120.00, -89.00, 2959.30, -945.00, 110.90}},
        {!"Las Colinas",                  {2632.70, -1135.00, -89.00, 2747.70, -945.00, 110.90}},
        {!"Las Colinas",                  {2281.40, -1135.00, -89.00, 2632.70, -945.00, 110.90}},
        {!"Las Payasadas",                {-354.30, 2580.30, 2.00, -133.60, 2816.80, 200.00}},
        {!"Las Venturas Airport",         {1236.60, 1203.20, -89.00, 1457.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1203.20, -89.00, 1777.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1143.20, -89.00, 1777.40, 1203.20, 110.90}},
        {!"Las Venturas Airport",         {1515.80, 1586.40, -12.50, 1729.90, 1714.50, 87.50}},
        {!"Last Dime Motel",              {1823.00, 596.30, -89.00, 1997.20, 823.20, 110.90}},
        {!"Leafy Hollow",                 {-1166.90, -1856.00, 0.00, -815.60, -1602.00, 200.00}},
        {!"Liberty City",                 {-1000.00, 400.00, 1300.00, -700.00, 600.00, 1400.00}},
        {!"Lil' Probe Inn",               {-90.20, 1286.80, -3.00, 153.80, 1554.10, 200.00}},
        {!"Linden Side",                  {2749.90, 943.20, -89.00, 2923.30, 1198.90, 110.90}},
        {!"Linden Station",               {2749.90, 1198.90, -89.00, 2923.30, 1548.90, 110.90}},
        {!"Linden Station",               {2811.20, 1229.50, -39.50, 2861.20, 1407.50, 60.40}},
        {!"Little Mexico",                {1701.90, -1842.20, -89.00, 1812.60, -1722.20, 110.90}},
        {!"Little Mexico",                {1758.90, -1722.20, -89.00, 1812.60, -1577.50, 110.90}},
        {!"Los Flores",                   {2581.70, -1454.30, -89.00, 2632.80, -1393.40, 110.90}},
        {!"Los Flores",                   {2581.70, -1393.40, -89.00, 2747.70, -1135.00, 110.90}},
        {!"Los Santos International",     {1249.60, -2394.30, -89.00, 1852.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1852.00, -2394.30, -89.00, 2089.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1382.70, -2730.80, -89.00, 2201.80, -2394.30, 110.90}},
        {!"Los Santos International",     {1974.60, -2394.30, -39.00, 2089.00, -2256.50, 60.90}},
        {!"Los Santos International",     {1400.90, -2669.20, -39.00, 2189.80, -2597.20, 60.90}},
        {!"Los Santos International",     {2051.60, -2597.20, -39.00, 2152.40, -2394.30, 60.90}},
        {!"Marina",                       {647.70, -1804.20, -89.00, 851.40, -1577.50, 110.90}},
        {!"Marina",                       {647.70, -1577.50, -89.00, 807.90, -1416.20, 110.90}},
        {!"Marina",                       {807.90, -1577.50, -89.00, 926.90, -1416.20, 110.90}},
        {!"Market",                       {787.40, -1416.20, -89.00, 1072.60, -1310.20, 110.90}},
        {!"Market",                       {952.60, -1310.20, -89.00, 1072.60, -1130.80, 110.90}},
        {!"Market",                       {1072.60, -1416.20, -89.00, 1370.80, -1130.80, 110.90}},
        {!"Market",                       {926.90, -1577.50, -89.00, 1370.80, -1416.20, 110.90}},
        {!"Market Station",               {787.40, -1410.90, -34.10, 866.00, -1310.20, 65.80}},
        {!"Martin Bridge",                {-222.10, 293.30, 0.00, -122.10, 476.40, 200.00}},
        {!"Missionary Hill",              {-2994.40, -811.20, 0.00, -2178.60, -430.20, 200.00}},
        {!"Montgomery",                   {1119.50, 119.50, -3.00, 1451.40, 493.30, 200.00}},
        {!"Montgomery",                   {1451.40, 347.40, -6.10, 1582.40, 420.80, 200.00}},
        {!"Montgomery Intersection",      {1546.60, 208.10, 0.00, 1745.80, 347.40, 200.00}},
        {!"Montgomery Intersection",      {1582.40, 347.40, 0.00, 1664.60, 401.70, 200.00}},
        {!"Mulholland",                   {1414.00, -768.00, -89.00, 1667.60, -452.40, 110.90}},
        {!"Mulholland",                   {1281.10, -452.40, -89.00, 1641.10, -290.90, 110.90}},
        {!"Mulholland",                   {1269.10, -768.00, -89.00, 1414.00, -452.40, 110.90}},
        {!"Mulholland",                   {1357.00, -926.90, -89.00, 1463.90, -768.00, 110.90}},
        {!"Mulholland",                   {1318.10, -910.10, -89.00, 1357.00, -768.00, 110.90}},
        {!"Mulholland",                   {1169.10, -910.10, -89.00, 1318.10, -768.00, 110.90}},
        {!"Mulholland",                   {768.60, -954.60, -89.00, 952.60, -860.60, 110.90}},
        {!"Mulholland",                   {687.80, -860.60, -89.00, 911.80, -768.00, 110.90}},
        {!"Mulholland",                   {737.50, -768.00, -89.00, 1142.20, -674.80, 110.90}},
        {!"Mulholland",                   {1096.40, -910.10, -89.00, 1169.10, -768.00, 110.90}},
        {!"Mulholland",                   {952.60, -937.10, -89.00, 1096.40, -860.60, 110.90}},
        {!"Mulholland",                   {911.80, -860.60, -89.00, 1096.40, -768.00, 110.90}},
        {!"Mulholland",                   {861.00, -674.80, -89.00, 1156.50, -600.80, 110.90}},
        {!"Mulholland Intersection",      {1463.90, -1150.80, -89.00, 1812.60, -768.00, 110.90}},
        {!"North Rock",                   {2285.30, -768.00, 0.00, 2770.50, -269.70, 200.00}},
        {!"Ocean Docks",                  {2373.70, -2697.00, -89.00, 2809.20, -2330.40, 110.90}},
        {!"Ocean Docks",                  {2201.80, -2418.30, -89.00, 2324.00, -2095.00, 110.90}},
        {!"Ocean Docks",                  {2324.00, -2302.30, -89.00, 2703.50, -2145.10, 110.90}},
        {!"Ocean Docks",                  {2089.00, -2394.30, -89.00, 2201.80, -2235.80, 110.90}},
        {!"Ocean Docks",                  {2201.80, -2730.80, -89.00, 2324.00, -2418.30, 110.90}},
        {!"Ocean Docks",                  {2703.50, -2302.30, -89.00, 2959.30, -2126.90, 110.90}},
        {!"Ocean Docks",                  {2324.00, -2145.10, -89.00, 2703.50, -2059.20, 110.90}},
        {!"Ocean Flats",                  {-2994.40, 277.40, -9.10, -2867.80, 458.40, 200.00}},
        {!"Ocean Flats",                  {-2994.40, -222.50, -0.00, -2593.40, 277.40, 200.00}},
        {!"Ocean Flats",                  {-2994.40, -430.20, -0.00, -2831.80, -222.50, 200.00}},
        {!"Octane Springs",               {338.60, 1228.50, 0.00, 664.30, 1655.00, 200.00}},
        {!"Old Venturas Strip",           {2162.30, 2012.10, -89.00, 2685.10, 2202.70, 110.90}},
        {!"Palisades",                    {-2994.40, 458.40, -6.10, -2741.00, 1339.60, 200.00}},
        {!"Palomino Creek",               {2160.20, -149.00, 0.00, 2576.90, 228.30, 200.00}},
        {!"Paradiso",                     {-2741.00, 793.40, -6.10, -2533.00, 1268.40, 200.00}},
        {!"Pershing Square",              {1440.90, -1722.20, -89.00, 1583.50, -1577.50, 110.90}},
        {!"Pilgrim",                      {2437.30, 1383.20, -89.00, 2624.40, 1783.20, 110.90}},
        {!"Pilgrim",                      {2624.40, 1383.20, -89.00, 2685.10, 1783.20, 110.90}},
        {!"Pilson Intersection",          {1098.30, 2243.20, -89.00, 1377.30, 2507.20, 110.90}},
        {!"Pirates in Men's Pants",       {1817.30, 1469.20, -89.00, 2027.40, 1703.20, 110.90}},
        {!"Playa del Seville",            {2703.50, -2126.90, -89.00, 2959.30, -1852.80, 110.90}},
        {!"Prickle Pine",                 {1534.50, 2583.20, -89.00, 1848.40, 2863.20, 110.90}},
        {!"Prickle Pine",                 {1117.40, 2507.20, -89.00, 1534.50, 2723.20, 110.90}},
        {!"Prickle Pine",                 {1848.40, 2553.40, -89.00, 1938.80, 2863.20, 110.90}},
        {!"Prickle Pine",                 {1938.80, 2624.20, -89.00, 2121.40, 2861.50, 110.90}},
        {!"Queens",                       {-2533.00, 458.40, 0.00, -2329.30, 578.30, 200.00}},
        {!"Queens",                       {-2593.40, 54.70, 0.00, -2411.20, 458.40, 200.00}},
        {!"Queens",                       {-2411.20, 373.50, 0.00, -2253.50, 458.40, 200.00}},
        {!"Randolph Industrial Estate",   {1558.00, 596.30, -89.00, 1823.00, 823.20, 110.90}},
        {!"Redsands East",                {1817.30, 2011.80, -89.00, 2106.70, 2202.70, 110.90}},
        {!"Redsands East",                {1817.30, 2202.70, -89.00, 2011.90, 2342.80, 110.90}},
        {!"Redsands East",                {1848.40, 2342.80, -89.00, 2011.90, 2478.40, 110.90}},
        {!"Redsands West",                {1236.60, 1883.10, -89.00, 1777.30, 2142.80, 110.90}},
        {!"Redsands West",                {1297.40, 2142.80, -89.00, 1777.30, 2243.20, 110.90}},
        {!"Redsands West",                {1377.30, 2243.20, -89.00, 1704.50, 2433.20, 110.90}},
        {!"Redsands West",                {1704.50, 2243.20, -89.00, 1777.30, 2342.80, 110.90}},
        {!"Regular Tom",                  {-405.70, 1712.80, -3.00, -276.70, 1892.70, 200.00}},
        {!"Richman",                      {647.50, -1118.20, -89.00, 787.40, -954.60, 110.90}},
        {!"Richman",                      {647.50, -954.60, -89.00, 768.60, -860.60, 110.90}},
        {!"Richman",                      {225.10, -1369.60, -89.00, 334.50, -1292.00, 110.90}},
        {!"Richman",                      {225.10, -1292.00, -89.00, 466.20, -1235.00, 110.90}},
        {!"Richman",                      {72.60, -1404.90, -89.00, 225.10, -1235.00, 110.90}},
        {!"Richman",                      {72.60, -1235.00, -89.00, 321.30, -1008.10, 110.90}},
        {!"Richman",                      {321.30, -1235.00, -89.00, 647.50, -1044.00, 110.90}},
        {!"Richman",                      {321.30, -1044.00, -89.00, 647.50, -860.60, 110.90}},
        {!"Richman",                      {321.30, -860.60, -89.00, 687.80, -768.00, 110.90}},
        {!"Richman",                      {321.30, -768.00, -89.00, 700.70, -674.80, 110.90}},
        {!"Robada Intersection",          {-1119.00, 1178.90, -89.00, -862.00, 1351.40, 110.90}},
        {!"Roca Escalante",               {2237.40, 2202.70, -89.00, 2536.40, 2542.50, 110.90}},
        {!"Roca Escalante",               {2536.40, 2202.70, -89.00, 2625.10, 2442.50, 110.90}},
        {!"Rockshore East",               {2537.30, 676.50, -89.00, 2902.30, 943.20, 110.90}},
        {!"Rockshore West",               {1997.20, 596.30, -89.00, 2377.30, 823.20, 110.90}},
        {!"Rockshore West",               {2377.30, 596.30, -89.00, 2537.30, 788.80, 110.90}},
        {!"Rodeo",                        {72.60, -1684.60, -89.00, 225.10, -1544.10, 110.90}},
        {!"Rodeo",                        {72.60, -1544.10, -89.00, 225.10, -1404.90, 110.90}},
        {!"Rodeo",                        {225.10, -1684.60, -89.00, 312.80, -1501.90, 110.90}},
        {!"Rodeo",                        {225.10, -1501.90, -89.00, 334.50, -1369.60, 110.90}},
        {!"Rodeo",                        {334.50, -1501.90, -89.00, 422.60, -1406.00, 110.90}},
        {!"Rodeo",                        {312.80, -1684.60, -89.00, 422.60, -1501.90, 110.90}},
        {!"Rodeo",                        {422.60, -1684.60, -89.00, 558.00, -1570.20, 110.90}},
        {!"Rodeo",                        {558.00, -1684.60, -89.00, 647.50, -1384.90, 110.90}},
        {!"Rodeo",                        {466.20, -1570.20, -89.00, 558.00, -1385.00, 110.90}},
        {!"Rodeo",                        {422.60, -1570.20, -89.00, 466.20, -1406.00, 110.90}},
        {!"Rodeo",                        {466.20, -1385.00, -89.00, 647.50, -1235.00, 110.90}},
        {!"Rodeo",                        {334.50, -1406.00, -89.00, 466.20, -1292.00, 110.90}},
        {!"Royal Casino",                 {2087.30, 1383.20, -89.00, 2437.30, 1543.20, 110.90}},
        {!"San Andreas Sound",            {2450.30, 385.50, -100.00, 2759.20, 562.30, 200.00}},
        {!"Santa Flora",                  {-2741.00, 458.40, -7.60, -2533.00, 793.40, 200.00}},
        {!"Santa Maria Beach",            {342.60, -2173.20, -89.00, 647.70, -1684.60, 110.90}},
        {!"Santa Maria Beach",            {72.60, -2173.20, -89.00, 342.60, -1684.60, 110.90}},
        {!"Shady Cabin",                  {-1632.80, -2263.40, -3.00, -1601.30, -2231.70, 200.00}},
        {!"Shady Creeks",                 {-1820.60, -2643.60, -8.00, -1226.70, -1771.60, 200.00}},
        {!"Shady Creeks",                 {-2030.10, -2174.80, -6.10, -1820.60, -1771.60, 200.00}},
        {!"Sobell Rail Yards",            {2749.90, 1548.90, -89.00, 2923.30, 1937.20, 110.90}},
        {!"Spinybed",                     {2121.40, 2663.10, -89.00, 2498.20, 2861.50, 110.90}},
        {!"Starfish Casino",              {2437.30, 1783.20, -89.00, 2685.10, 2012.10, 110.90}},
        {!"Starfish Casino",              {2437.30, 1858.10, -39.00, 2495.00, 1970.80, 60.90}},
        {!"Starfish Casino",              {2162.30, 1883.20, -89.00, 2437.30, 2012.10, 110.90}},
        {!"Temple",                       {1252.30, -1130.80, -89.00, 1378.30, -1026.30, 110.90}},
        {!"Temple",                       {1252.30, -1026.30, -89.00, 1391.00, -926.90, 110.90}},
        {!"Temple",                       {1252.30, -926.90, -89.00, 1357.00, -910.10, 110.90}},
        {!"Temple",                       {952.60, -1130.80, -89.00, 1096.40, -937.10, 110.90}},
        {!"Temple",                       {1096.40, -1130.80, -89.00, 1252.30, -1026.30, 110.90}},
        {!"Temple",                       {1096.40, -1026.30, -89.00, 1252.30, -910.10, 110.90}},
        {!"The Camel's Toe",              {2087.30, 1203.20, -89.00, 2640.40, 1383.20, 110.90}},
        {!"The Clown's Pocket",           {2162.30, 1783.20, -89.00, 2437.30, 1883.20, 110.90}},
        {!"The Emerald Isle",             {2011.90, 2202.70, -89.00, 2237.40, 2508.20, 110.90}},
        {!"The Farm",                     {-1209.60, -1317.10, 114.90, -908.10, -787.30, 251.90}},
        {!"The Four Dragons Casino",      {1817.30, 863.20, -89.00, 2027.30, 1083.20, 110.90}},
        {!"The High Roller",              {1817.30, 1283.20, -89.00, 2027.30, 1469.20, 110.90}},
        {!"The Mako Span",                {1664.60, 401.70, 0.00, 1785.10, 567.20, 200.00}},
        {!"The Panopticon",               {-947.90, -304.30, -1.10, -319.60, 327.00, 200.00}},
        {!"The Pink Swan",                {1817.30, 1083.20, -89.00, 2027.30, 1283.20, 110.90}},
        {!"The Sherman Dam",              {-968.70, 1929.40, -3.00, -481.10, 2155.20, 200.00}},
        {!"The Strip",                    {2027.40, 863.20, -89.00, 2087.30, 1703.20, 110.90}},
        {!"The Strip",                    {2106.70, 1863.20, -89.00, 2162.30, 2202.70, 110.90}},
        {!"The Strip",                    {2027.40, 1783.20, -89.00, 2162.30, 1863.20, 110.90}},
        {!"The Strip",                    {2027.40, 1703.20, -89.00, 2137.40, 1783.20, 110.90}},
        {!"The Visage",                   {1817.30, 1863.20, -89.00, 2106.70, 2011.80, 110.90}},
        {!"The Visage",                   {1817.30, 1703.20, -89.00, 2027.40, 1863.20, 110.90}},
        {!"Unity Station",                {1692.60, -1971.80, -20.40, 1812.60, -1932.80, 79.50}},
        {!"Valle Ocultado",               {-936.60, 2611.40, 2.00, -715.90, 2847.90, 200.00}},
        {!"Verdant Bluffs",               {930.20, -2488.40, -89.00, 1249.60, -2006.70, 110.90}},
        {!"Verdant Bluffs",               {1073.20, -2006.70, -89.00, 1249.60, -1842.20, 110.90}},
        {!"Verdant Bluffs",               {1249.60, -2179.20, -89.00, 1692.60, -1842.20, 110.90}},
        {!"Verdant Meadows",              {37.00, 2337.10, -3.00, 435.90, 2677.90, 200.00}},
        {!"Verona Beach",                 {647.70, -2173.20, -89.00, 930.20, -1804.20, 110.90}},
        {!"Verona Beach",                 {930.20, -2006.70, -89.00, 1073.20, -1804.20, 110.90}},
        {!"Verona Beach",                 {851.40, -1804.20, -89.00, 1046.10, -1577.50, 110.90}},
        {!"Verona Beach",                 {1161.50, -1722.20, -89.00, 1323.90, -1577.50, 110.90}},
        {!"Verona Beach",                 {1046.10, -1722.20, -89.00, 1161.50, -1577.50, 110.90}},
        {!"Vinewood",                     {787.40, -1310.20, -89.00, 952.60, -1130.80, 110.90}},
        {!"Vinewood",                     {787.40, -1130.80, -89.00, 952.60, -954.60, 110.90}},
        {!"Vinewood",                     {647.50, -1227.20, -89.00, 787.40, -1118.20, 110.90}},
        {!"Vinewood",                     {647.70, -1416.20, -89.00, 787.40, -1227.20, 110.90}},
        {!"Whitewood Estates",            {883.30, 1726.20, -89.00, 1098.30, 2507.20, 110.90}},
        {!"Whitewood Estates",            {1098.30, 1726.20, -89.00, 1197.30, 2243.20, 110.90}},
        {!"Willowfield",                  {1970.60, -2179.20, -89.00, 2089.00, -1852.80, 110.90}},
        {!"Willowfield",                  {2089.00, -2235.80, -89.00, 2201.80, -1989.90, 110.90}},
        {!"Willowfield",                  {2089.00, -1989.90, -89.00, 2324.00, -1852.80, 110.90}},
        {!"Willowfield",                  {2201.80, -2095.00, -89.00, 2324.00, -1989.90, 110.90}},
        {!"Willowfield",                  {2541.70, -1941.40, -89.00, 2703.50, -1852.80, 110.90}},
        {!"Willowfield",                  {2324.00, -2059.20, -89.00, 2541.70, -1852.80, 110.90}},
        {!"Willowfield",                  {2541.70, -2059.20, -89.00, 2703.50, -1941.40, 110.90}},
        {!"Yellow Bell Station",          {1377.40, 2600.40, -21.90, 1492.40, 2687.30, 78.00}},
        {!"Los Santos",                   {44.60, -2892.90, -242.90, 2997.00, -768.00, 900.00}},
        {!"Las Venturas",                 {869.40, 596.30, -242.90, 2997.00, 2993.80, 900.00}},
        {!"Bone County",                  {-480.50, 596.30, -242.90, 869.40, 2993.80, 900.00}},
        {!"Tierra Robada",                {-2997.40, 1659.60, -242.90, -480.50, 2993.80, 900.00}},
        {!"Tierra Robada",                {-1213.90, 596.30, -242.90, -480.50, 1659.60, 900.00}},
        {!"San Fierro",                   {-2997.40, -1115.50, -242.90, -1213.90, 1659.60, 900.00}},
        {!"Red County",                   {-1213.90, -768.00, -242.90, 2997.00, 596.30, 900.00}},
        {!"Flint County",                 {-1213.90, -2892.90, -242.90, 44.60, -768.00, 900.00}},
        {!"Whetstone",                    {-2997.40, -2892.90, -242.90, -1213.90, -1115.50, 900.00}}
    };
    new
        name[32] = "San Andreas";

    for (new i = 0; i != sizeof(g_arrZoneData); i ++) if((fX >= g_arrZoneData[i][e_ZoneArea][0] && fX <= g_arrZoneData[i][e_ZoneArea][3]) && (fY >= g_arrZoneData[i][e_ZoneArea][1] && fY <= g_arrZoneData[i][e_ZoneArea][4]) && (fZ >= g_arrZoneData[i][e_ZoneArea][2] && fZ <= g_arrZoneData[i][e_ZoneArea][5])) {
        strunpack(name, g_arrZoneData[i][e_ZoneName]);

        break;
    }
    return name;
}

ReplaceString(text[])
{
    new replace[128];
    format(replace, sizeof(replace), text);

    strreplace(replace, "(e)", "\n");
    strreplace(replace, "(n)", "\n");
    strreplace(replace, "(b)", "{0049FF}");
    strreplace(replace, "(bl)", "{000000}");
    strreplace(replace, "(w)", "{FFFFFF}");
    strreplace(replace, "(r)", "{FF3333}");
    strreplace(replace, "(g)", "{37DB45}");
	strreplace(replace, "(gr)", "{BABABA}");
	strreplace(replace, "(p)", "{FFB6C1}");
    strreplace(replace, "(y)", "{F3FF02}");
	strreplace(replace, "(o)", "{DB881A}");
	strreplace(replace, "(a)", "{00FFFF}");
    return replace;
}

Update_PlayerMask(playerid) 
{
	if (pData[playerid][pMaskOn]) {
      		if (IsValidDynamic3DTextLabel(pData[playerid][pNameTag])) {
        		UpdateDynamic3DTextLabelText(pData[playerid][pNameTag], COLOR_WHITE, sprintf("Mask_%d\nH: ["RED_E"%.1f"WHITE_E"] A: [%.1f]", pData[playerid][pMaskID], pData[playerid][pHealth], pData[playerid][pArmour]));
	    }
	}
	return 1;
}

GetMaskOwner(mask) {
    foreach (new i : Player) if (pData[i][pMaskOn] && pData[i][pMaskID] == mask) {
        return i;
    }
    
    return INVALID_PLAYER_ID;
}

FormatRadio(playerid, text[]) {
    new replace[128];
    format(replace, sizeof(replace), text);

    strreplace(replace, "@", sprintf("%s", pData[playerid][pBadge]));
	strreplace(replace, "~", sprintf("%s %s %s:", pData[playerid][pFactionRankName], ReturnName2(playerid), pData[playerid][pUnit]));
    // strreplace(replace, "~", sprintf("%s", pData[playerid][pUnit]));
    return replace;
}

// FormatRadio(playerid, text[]) {
//     new replace[128];
//     format(replace, sizeof(replace), text);

//     strreplace(replace, "@", "%s", pData[playerid][pBadge]);
//     return replace;
// }

// ConvertTimestamp(Timestamp:timestamp, bool:date = true)
// {
//     new output[256];

//     if(date) TimeFormat(timestamp + Timestamp:UTC_07, "%a %d %b %Y, %T", output);
//     else TimeFormat(timestamp + Timestamp:UTC_07, "%T", output);

//     return output;
// }

ReturnName(playerid)
{
    static
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));
    return name;
}

ReturnName2(playerid)
{
    static
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));
	for (new i = 0, len = strlen(name); i < len; i ++) {
			if(name[i] == '_') name[i] = ' ';
	}
    return name;
}

//Format Money
FormatMoney(Float:amount, delimiter[2]=".", comma[2]=",")
{
	#define MAX_MONEY_String 16
	new txt[MAX_MONEY_String];
	format(txt, MAX_MONEY_String, "%d", floatround(amount));
	new l = strlen(txt);
	if (amount < 0) // -
	{
		if (l > 2) strins(txt,delimiter,l-2);
		if (l > 5) strins(txt,comma,l-5);
		if (l > 8) strins(txt,comma,l-8);
	}
	else
	{//1000000
		if (l > 2) strins(txt,delimiter,l-2);
		if (l > 5) strins(txt,comma,l-5);
		if (l > 9) strins(txt,comma,l-8);
	}
//	if (l <= 2) format(txt,sizeof( szStr ),"00,%s",txt);
	return txt;
}

RandomEx(min, max)
{
    return random(max - min) + min;
}
IsNumeric(const str[])
{
	for (new i = 0, l = strlen(str); i != l; i ++)
    {
        if(i == 0 && str[0] == '-')
        continue;

      	else if(str[i] < '0' || str[i] > '9')
		return 0;
	}
	return 1;
}

//Date and Time
GetMonth(bulan)
{
    static
        month[12];

    switch (bulan) {
        case 1: month = "January";
        case 2: month = "February";
        case 3: month = "March";
        case 4: month = "April";
        case 5: month = "May";
        case 6: month = "June";
        case 7: month = "July";
        case 8: month = "August";
        case 9: month = "September";
        case 10: month = "October";
        case 11: month = "November";
        case 12: month = "December";
    }
    return month;
}

ReturnTime()
{
    static
        date[6],
        string[72];

    getdate(date[2], date[1], date[0]);
    gettime(date[3], date[4], date[5]);

    format(string, sizeof(string), "%02d %s %d, %02d:%02d:%02d", date[0],GetMonth(date[1]), date[2], date[3], date[4], date[5]);
    return string;
}

/*ConvertHBEColor(value) {
    new color;
    if(value >= 90 && value <= 100) color = 0x15a014FF;
    else if(value >= 80 && value < 90) color = 0x1b9913FF;
    else if(value >= 70 && value < 80) color = 0x1a7f08FF;
    else if(value >= 60 && value < 70) color = 0x326305FF;
    else if(value >= 50 && value < 60) color = 0x375d04FF;
    else if(value >= 40 && value < 50) color = 0x603304FF;
    else if(value >= 30 && value < 40) color = 0xd72800FF;
    else if(value >= 10 && value < 30) color = 0xfb3508FF;
    else if(value >= 0 && value < 10) color = 0xFF0000FF;
    else color = COLOR_WHITE;
    return color;
}*/

/*ConvertDamageVehicleColor(Float:value)
{
    new color;
    if(value >= 900 && value <= 1000)
        color = 0x1b9913FF;
    else if(value >= 800 && value < 900)
        color = 0x1b9913FF;
    else if(value >= 700 && value < 800)
        color = 0x1a7f08FF;
    else if(value >= 600 && value < 700)
        color = 0x326305FF;
    else if(value >= 500 && value < 600)
        color = 0x375d04FF;
    else if(value >= 400 && value < 500)
        color = 0x603304FF;
    else if(value >= 300 && value < 400)
        color = 0xFF0000FF;
    else 
        color = COLOR_WHITE;

    return color;
}*/

/*ConvertFuelVehicleColor(value)
{
    new color;
    if(value >= 900 && value <= 1000)
        color = 0x1b9913FF;
    else if(value >= 800 && value < 900)
        color = 0x1b9913FF;
    else if(value >= 700 && value < 800)
        color = 0x1a7f08FF;
    else if(value >= 600 && value < 700)
        color = 0x326305FF;
    else if(value >= 500 && value < 600)
        color = 0x375d04FF;
    else if(value >= 400 && value < 500)
        color = 0x603304FF;
    else if(value >= 300 && value < 400)
        color = 0xd72800FF;
    else if(value >= 100 && value < 300)
        color = 0xfb3508FF;
    else if(value >= 0 && value < 100)
        color = 0xFF0000FF;
    else 
        color = COLOR_WHITE;

    return color;
}*/

ConvertTdColor(value) {
    new color;
    if(value >= 60 && value < 70) color = 0xC2A756FF;
    else if(value >= 50 && value < 60) color = 0xC2A756FF;
    else if(value >= 40 && value < 50) color = 0xC2A756FF;
    else if(value >= 30 && value < 40) color = 0x670E10FF;
    else if(value >= 10 && value < 30) color = 0x670E10FF;
    else if(value >= 0 && value < 10) color = 0x670E10FF;
    else color = COLOR_WHITE;
    return color;
}

ConvertDamageVehColor(Float:value) 
{
    new color;
	if(value >= 600.0 && value < 700.0)
        color = 0xC2A756FF;
    else if(value >= 500.0 && value < 600.0)
        color = 0xC2A756FF;
    else if(value >= 400.0 && value < 500.0)
        color = 0xC2A756FF;
    else if(value >= 300.0 && value < 400.0)
        color = 0x670E10FF;
    else 
        color = COLOR_WHITE;

    return color;
}

ConvertFuelVehColor(value) 
{
    new color;
   	if(value >= 600 && value < 700)
        color = 0xC2A756FF;
    else if(value >= 500 && value < 600)
        color = 0xC2A756FF;
    else if(value >= 400 && value < 500)
        color = 0xC2A756FF;
    else if(value >= 300 && value < 400)
        color = 0x670E10FF;
    else if(value >= 100 && value < 300)
        color = 0x670E10FF;
    else if(value >= 0 && value < 100)
        color = 0x670E10FF;
    else 
        color = COLOR_WHITE;

    return color;
}

GetKecepatanPlayer(playerid)
{
    new Float: x, Float: y, Float: z;
    if(IsPlayerInAnyVehicle(playerid))
    {
        new kendaraansetan = GetPlayerVehicleID(playerid);
        GetVehicleVelocity(kendaraansetan, x, y, z);
    }
    else GetPlayerVelocity(playerid, x, y, z);

    return floatround(floatsqroot(x*x+y*y+z*z)*100);
}

AnticheatCheck(playerid)
{
	// Speedhacking
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleSpeed(GetPlayerVehicleID(playerid)) > 350 && pData[playerid][pAdmin] < 2)
	{
		SendStaffMessage(COLOR_YELLOW, "AdmWarning: %s[%i] is possibly speedhacking, speed: %.1f km/h.", ReturnName(playerid), playerid, GetVehicleSpeed(GetPlayerVehicleID(playerid)));
	}

	// Jetpack
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && pData[playerid][pAdmin] < 1 && pData[playerid][pHelper] < 1)
	{
		SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: %s was auto-kicked by %s, reason: Jetpack", ReturnName(playerid));
		KickEx(playerid);
	}

	// Flying hacks
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		switch(GetPlayerAnimationIndex(playerid))
		{
			case 958, 1538, 1539, 1543:
			{
				new
					Float:z,
					Float:vx,
					Float:vy,
					Float:vz;

				GetPlayerPos(playerid, z, z, z);
				GetPlayerVelocity(playerid, vx, vy, vz);

				if((z > 20.0) && (0.9 <= floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) <= 1.9) && pData[playerid][pAdmin] < 2)
				{
					SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: %s was auto-kicked by BotCmd, reason: Flying Hacks", ReturnName(playerid));
					KickEx(playerid);
				}
			}
		}
	}
}

ProxDetectorS(Float:radi, playerid, targetid) 
{

	if(WatchingTV[playerid] != 1)
	{
	    if(Spectating[targetid] != 0 && pData[playerid][pAdmin] < 2)
	    {
	    	return 0;
	    }

		new
			Float: fp_playerPos[3];

		GetPlayerPos(targetid, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]);

		if(IsPlayerInRangeOfPoint(playerid, radi, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
		{
			return 1;
		}
	}
	return 0;
}

ColouredText(text[])
{
	//Credits to RyDeR`
	new
	    pos = -1,
	    string[(128 + 16)]
	;
	strmid(string, text, 0, 128, (sizeof(string) - 16));

	while((pos = strfind(string, "#", true, (pos + 1))) != -1)
	{
	    new
	        i = (pos + 1),
	        hexCount
		;
		for( ; ((string[i] != 0) && (hexCount < 6)); ++i, ++hexCount)
		{
		    if (!(('a' <= string[i] <= 'f') || ('A' <= string[i] <= 'F') || ('0' <= string[i] <= '9')))
		    {
		        break;
		    }
		}
		if ((hexCount == 6) && !(hexCount < 6))
		{
			string[pos] = '{';
			strins(string, "}", i);
		}
	}
	return string;
}

FixText(text[])
{
	new len = strlen(text);
	if (len > 1)
	{
		for(new i = 0; i < len; i++)
		{
			if (text[i] == 92)
			{
			    if (text[i+1] == 'n')
			    {
					text[i] = '\n';
					for(new j = i+1; j < len; j++) text[j] = text[j+1], text[j+1] = 0;
					continue;
			    }
			}
		}
	}
	return 1;
}

GetRGB(color, &r, &g, &b)
{
    new col[3 char];
    col[0] = color;
    r = col{0};
    g = col{1};
    b = col{2};
}

GetRGBColor(playerid, id, type = 0)
{
    if(!type) return 0;
    else if(type == 1) return AccData[playerid][id][accColor1][0] << 24 | AccData[playerid][id][accColor1][0] << 16 | AccData[playerid][id][accColor1][0] << 8 | 0xFF;
    else if(type == 2) return AccData[playerid][id][accColor2][0] << 24 | AccData[playerid][id][accColor2][0] << 16 | AccData[playerid][id][accColor2][0] << 8 | 0xFF;
    else return 0;
}

GetVehicleOffset(vehicleid, OffsetTypes:type,&Float:x,&Float:y,&Float:z)
{
	new Float:fPos[4],Float:fSize[3];

	if(!IsValidVehicle(vehicleid)){
		x = y =	z = 0.0;
		return 0;
	} else {
		GetVehiclePos(vehicleid,fPos[0],fPos[1],fPos[2]);
		GetVehicleZAngle(vehicleid,fPos[3]);
		GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,fSize[0],fSize[1],fSize[2]);

		switch(type){
			case VEHICLE_OFFSET_BOOT: {
				x = fPos[0] - (floatsqroot(fSize[1] + fSize[1]) * floatsin(-fPos[3],degrees));
				y = fPos[1] - (floatsqroot(fSize[1] + fSize[1]) * floatcos(-fPos[3],degrees));
 				z = fPos[2];
			}
			case VEHICLE_OFFSET_HOOD: {
				x = fPos[0] + (floatsqroot(fSize[1] + fSize[1]) * floatsin(-fPos[3],degrees));
				y = fPos[1] + (floatsqroot(fSize[1] + fSize[1]) * floatcos(-fPos[3],degrees));
	 			z = fPos[2];
			}
			case VEHICLE_OFFSET_ROOF: {
				x = fPos[0];
				y = fPos[1];
				z = fPos[2] + floatsqroot(fSize[2]);
			}
		}
	}
	return 1;
}

function OnPlayerJumping(playerid)
{
    if (strfind(GetAllBodyPartStatus(playerid),"Broken Bone",true) != -1 && !pData[playerid][pAdminDuty])
        return ApplyAnimation(playerid, "PED", "KO_skid_front", 4.1, 0, 1, 1, 1, 0, 1), SetTimerEx("BunnyHopReset", 3000, false, "d", playerid);

    if(++pData[playerid][pPemberitahuan] > 1 && !pData[playerid][pAdminDuty]) {
        ApplyAnimation(playerid, "PED", "KO_skid_front", 4.1, 0, 1, 1, 1, 0, 1);
        SetTimerEx("BunnyHopReset", 3000, false, "d", playerid);
    }
    SetTimerEx("TimerBunnyHop", 4000, false, "d", playerid);
    return 1;
}

GetAllBodyPartStatus(playerid) {
    new status[128];
    for (new i = 7; i < 9; i ++) {
        format(status,sizeof(status),"%s%s",status,GetPlayerBodypartStatus(playerid, i));
    }
    return status;
}

function BunnyHopReset(playerid) {
    pData[playerid][pPemberitahuan] = 0;
    ClearAnimations(playerid, 1);
    return 1;
}

function TimerBunnyHop(playerid)
{
    pData[playerid][pPemberitahuan] = 0;
    return 1;
}

SetPlayerStreamerSettings(playerid) {
    switch (pData[playerid][pStreamer]) {
        case 0: {
            Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 250, playerid);
            Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 0.2, playerid);
        }
        case 1: {
            Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 500, playerid);
            Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 0.5, playerid);
        }
        case 2: {
            Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 700, playerid);
            Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.0, playerid);
        }
        case 3: {
            Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 800, playerid);
            Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.5, playerid);
        }
        default: {
            Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 700, playerid);
            Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.0, playerid);
        }
    }
}

stock SetArmour(playerid, Float:armour)
{
    pData[playerid][pArmour] = armour;

    if(pData[playerid][pArmour] > 100)
        pData[playerid][pArmour] = 100;

    else if(pData[playerid][pArmour] <= 0)
        pData[playerid][pArmour] = 0;

    SetPlayerArmour(playerid, pData[playerid][pArmour]);
    return 1;
}

stock SetHealth(playerid, Float:health)
{
    if(IsPlayerInEvent(playerid))
        return 0;

    pData[playerid][pHealth] = health;

    if(pData[playerid][pHealth] > 100)
    {
        pData[playerid][pHealth] = 100.0;
        SetPlayerHealth(playerid, 100);
    }
    else
    {
        SetPlayerHealth(playerid, pData[playerid][pHealth]);
    }
    return 1;
}

//Global Function Server Side Health
Float:GetHealth(playerid)
{
    return pData[playerid][pHealth]; 
}
Float:GetArmour(playerid)
{
    return pData[playerid][pArmour]; 
}

Float:ReturnArmour2(playerid) {
    static
        Float:amount;

    GetPlayerArmour(playerid, amount);
    return amount;
}

ConvertTimestamp(Timestamp:timestamp, bool:date = true)
{
    new output[256];

    if(date) TimeFormat(timestamp + Timestamp:UTC_07, "%a %d %b %Y", output);
    else TimeFormat(timestamp + Timestamp:UTC_07, "%T", output);

    return output;
}

FlipVehicle(vehicleid)
{
    new
        Float:fAngle;

    GetVehicleZAngle(vehicleid, fAngle);

    SetVehicleZAngle(vehicleid, fAngle);
    SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
}

GetVipTime(playerid) {
  static time[64];

  if (pData[playerid][pVip] >= 1) {
    if (pData[playerid][pVipTime] != 0) {
      format(time,sizeof(time), "%s", ConvertTimestamp(Timestamp:pData[playerid][pVipTime]));
    } else {
      format(time,sizeof(time), ""RED_E"Expired");
    }
  } else format(time,sizeof(time),""RED_E"None");

  return time;
}

GetElapsedTime(time, &hours, &minutes, &seconds)
{
    hours = 0;
    minutes = 0;
    seconds = 0;

    if(time >= 3600) //jika lebih dari 1 jam (3600 = 1 jam)
    {
        hours = (time / 3600); //pembagian waktu per jam di bagi time/3600
        time -= (hours * 3600); //pengurangan di time , ex 2 jam terpakai maka di kalikan 2 * 3600 = time-7200
    }
    while (time >= 60) //hitungan menit.
    {
        minutes++; //hitungan menit bertambah selama time masih bervalue 60.
        time -= 60; // waktu berkurang per menit hitungan 60 sec dari time.
    }
    return (seconds = time);
}

SaveAll()
{
    new time = GetTickCount();
    foreach(new i : Player) if(IsPlayerConnected(i))
    {
        UpdatePlayerData(i);
		RemovePlayerVehicle(i);
    }
    printf("Done save player data: %d ms", GetTickCount() - time);

    // foreach(new i : WORKSHOPS) 
    // {
    //     Workshop_Save(i);
    // }
    // printf("Done save workshop data: %d ms", GetTickCount() - time);

    for (new i; i < MAX_BISNIS; i++){
        Bisnis_Save(i);
    }
    printf("Done save business data: %d ms", GetTickCount() - time);

    for (new i; i < MAX_HOUSES; i++){
        House_Save(i);

        for (new id = 0; id != MAX_FURNITURE; id ++){
            Furniture_Save(id, i);
        }
    }
    printf("Done save houses data: %d ms", GetTickCount() - time);

    printf("Done save all data: %d ms", GetTickCount() - time);
    return 1;
}

SchematicRequire(playerid, type)
{
    static
        str[212];

    switch (type)
    {
        case 0: 
		{
			if(pData[playerid][pSchematic][0] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
        case 1: 
		{
			if(pData[playerid][pSchematic][1] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
		case 2: 
		{
			if(pData[playerid][pSchematic][2] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
		case 3: 
		{
			if(pData[playerid][pSchematic][3] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
		case 4: 
		{
			if(pData[playerid][pSchematic][4] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
		case 5: 
		{
			if(pData[playerid][pSchematic][5] == 0) str = ""RED_E"Not Have"WHITE_E"";
			else str = ""GREEN_E"Have"WHITE_E"";
		}
    }
    return str;
}

LimitSlotPlayerVehicle(playerid)
{
	new limit = MAX_PLAYER_VEHICLE;
	if(pData[playerid][pVip] == 2) limit += 1;
	else if(pData[playerid][pVip] == 3 || pData[playerid][pVip] == 4) limit += 2;
	foreach(new hid : Houses) {
		if(Player_OwnsHouse(playerid, hid)) {
			limit += 2;
		}
	}
	foreach (new flatroom : FlatRooms) {
		if(FlatRoom_IsOwner(playerid, flatroom)) {
			limit += 2;
		}
	}
	return limit;
}
