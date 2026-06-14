// Definition
#define MAX_ACTOR (1000)

// Enum
enum actorData {
    actorID,
    actorDisplay,
    actorSkin,
    actorName[24],
    actorAnimlib[32],
    actorAnimname[32],
    Text3D:actorLabel,
    Float:actorPos[4],
    actorVirtualWorld,
    actorInterior
};

// Enum variable & Iterator
new ActorData[MAX_ACTOR][actorData],
    Iterator:Actors<MAX_ACTOR>;
