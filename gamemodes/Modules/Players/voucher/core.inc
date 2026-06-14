#define MAX_VOUCHER 50

enum E_VOUCHER
{
	voucID,
	voucCode[52],
	voucVIP,
	voucVIPTime,
	voucGold,
	voucClaimVIP[3],
	voucAdmin[16],
	voucDonature[16],
	voucClaim,
};
new VoucData[MAX_VOUCHER][E_VOUCHER],
	Iterator: Vouchers<MAX_VOUCHER>;
	