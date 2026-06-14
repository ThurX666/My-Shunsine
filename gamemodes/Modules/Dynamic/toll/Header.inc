#define MAX_TOLL 50
#define PosArrTollGate{%0} TollGate[%0][tPos][0], TollGate[%0][tPos][1], TollGate[%0][tPos][2], TollGate[%0][tPos][3], TollGate[%0][tPos][4], TollGate[%0][tPos][5]
#define MoveArrTollGate{%0} TollGate[%0][tMove][0], TollGate[%0][tMove][1], TollGate[%0][tMove][2], 3.0, TollGate[%0][tMove][3], TollGate[%0][tMove][4], TollGate[%0][tMove][5]

enum tollGate {
	tID,
	tObj,
	tStatus,
	tModel,
	Float:tPos[6],
	Float:tMove[6],
	tZone
};
new TollGate[MAX_TOLL][tollGate], Iterator:Tolls<MAX_TOLL>;
new TollGate_Timer[MAX_TOLL];