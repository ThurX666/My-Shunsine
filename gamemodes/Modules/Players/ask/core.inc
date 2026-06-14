#define MAX_ASK                         (50)
enum askData {
    askExists,
    askPlayer,
    askQuestion[128 char]
};
new AskData[MAX_ASK][askData];
