//======== Forklift ===========
new RuteForklift[MAX_PLAYERS] = -1;
new CountForklift[MAX_PLAYERS] = 0;

enum forkliftR {
	forklift_load,
	Float:forklift_posx,
    Float:forklift_posy,
    Float:forklift_posz
};

stock const forkliftrute[][forkliftR] = {
    {1, 2787.9470,-2424.3013,13.6336},  // forklift unload
    {1, 2745.0681,-2431.8979,13.6432}, // forklift unload
    {1, 2787.5383,-2449.0837,13.6337},  // forklift unload
    {1, 2787.3491,-2500.9392,13.6508},  // forklift unload
    {2, 2473.6274,-2568.4834,13.6589}, // forklift load
    {2, 2402.5598,-2564.4839,13.6494},  // forklift load
    {2, 2366.1287,-2312.4795,13.5469},  // forklift load
    {2, 2543.9194,-2466.3792,13.6229},  // forklift load
    {2, 2764.1018,-2514.0686,13.6426}, // forklift load
    {3, 2741.5383,-2393.0317,13.6328} // forklift finish
};
