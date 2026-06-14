#define MAX_REPORTS  1000
#define INVALID_REPORT_ID -1

enum reportinfo
{
	HasBeenUsed,
	Report[128],
	ReportFrom,
	CheckingReport,
 	TimeToExpire,
	BeingUsed,
	ReportExpireTimer,
	ReplyTimerr,
	ReportHour,
	ReportMinutes,
	ReportSecond
}

new Reports[MAX_REPORTS][reportinfo];
new ListItemReportId[MAX_PLAYERS][40];
new CancelReport[MAX_PLAYERS];
