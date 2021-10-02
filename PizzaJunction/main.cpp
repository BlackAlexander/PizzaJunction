#include <bits/stdc++.h>
#include <unistd.h>
#define timeWait 2
#define nrRoads 20
#define maxX 150
#define maxY 150
#define offset 3.6


using namespace std;


void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debu  g(x...)
#endif

ifstream AlextoSami("AlextoSami.txt"); // INPUT
ofstream SamitoAlex("SamitoAlex.txt"); // OUTPUT

void generateRoundabout()
{
    SamitoAlex << "false";
}

string interpretCode(string code, string state)
{
    if (code == "0000") {
        state = "exit";
    } else if (code == "0001") {
        state = "generateSuggestions";

    } else if (code == "0002") {
        state = "createSuggestion";
    } else if (code == "0003") {
        state = "simulateCars";
    }
    return state;
}

bool road[nrRoads];

vector <int> roadNodes;
double startingX[] = {0, maxX, maxX, cos()};
double startingY[] = {};

void readRoads()
{

    char word;
    for (int i = 1; i <= 16; ++i) {
        AlextoSami >> word;
        if (word == '0')
            road[i] = false;
        else
            road[i] = true;

        if (road[i] == true) {
            double x, y;

            roadNodes.push_back(x, y);
        }
    }

    for (int i = 1; i <= 16 ; ++i) {
        debug(road[i]);
    }
}

void readInfo()
{
    string code;
    string state;

//    string sacrifice;
//    AlextoSami >> sacrifice;

    state = "idle";

    while (true) {
        sleep(timeWait);
        AlextoSami.open("AlextoSami.txt");
        SamitoAlex.open("SamitoAlex.txt");

        AlextoSami >> code;
        debug(code);


        state = interpretCode(code, state);
        debug(state);



//        Possible states are:
//          exit
//          generateSuggestions
//          createSuggestion
//          simulateCars
        if (state == "exit")
            return;
        if (state == "generateSuggestions") {
            readRoads();
            generateRoundabout();
            //format for output is:
            // x y height
            // for each node
        }

        AlextoSami.close();
        SamitoAlex.close();
    }
}

//void writeInfo()
//{
//    SamitoAlex << code;
//    SamitoAlex.flush();
//}

int main()
{
    readInfo();
    return 0;
}