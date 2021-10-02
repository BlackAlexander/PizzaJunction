#include <bits/stdc++.h>
#include <unistd.h>
#define timeWait 2
#define nrRoads 20
#define maxX 150
#define maxY 150
#define offset 4.6
#define PI 3.14159265


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
ofstream SamitoAlex; // OUTPUT


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

double toRad(int x)
{
    return x * PI / 180;
}

bool road[nrRoads];

vector <pair <double, double> > roadNodes(nrRoads);
const double startingX[17] = {0, maxX, maxX, //1 2
                      cos(toRad(45)) * maxX + offset / 2,  cos(toRad(45)) * maxX, //3 4
                      offset, -offset, //5 6
                      -(cos(toRad(45)) * maxX),  -(cos(toRad(45)) * maxX + offset / 2), //7 8
                      -maxX, -maxX,  //9 10
                      -(cos(toRad(45)) * maxX  + offset / 2),  -(cos(toRad(45)) * maxX), //11 12
                      -offset, offset, //13 14
                      cos(toRad(45)) * maxX,  cos(toRad(45)) * maxX  + offset / 2, //15 16
                    };
const double startingY[17] = {0, -offset, offset, //1 2
                      sin(toRad(45)) * maxY, sin(toRad(45)) * maxY + offset / 2, //3 4
                      maxY, maxY, //5 6
                      sin(toRad(45)) * maxY + offset / 2, sin(toRad(45)) * maxY, //7 8
                      offset, -offset, //9 10
                      -(sin(toRad(45)) * maxY), -(sin(toRad(45)) * maxY + offset / 2), //11 12
                      -maxY, -maxY, //13 14
                      -(sin(toRad(45)) * maxY  + offset / 2), -(sin(toRad(45)) * maxY), //15 16
                     };

void readRoads()
{

    char word;
    for (int i = 1; i <= 16; ++i) {
        AlextoSami >> word;
        if (word == '0')
            road[i] = false;
        else
            road[i] = true;

        if (road[i]) {
            double x, y;
            x = startingX[i];
            y = startingY[i];
            roadNodes[i] = {x, y};
        }
    }
    debug(roadNodes);

//    for (int i = 1; i <= 16 ; ++i) {
//        debug(i, startingX[i], startingY[i]);
//    }
}

vector <pair <double, double> > traseu[nrRoads];
int nrOfRoads;

void generateCenteredJunction()
{
    nrOfRoads = 0;
    for (int i = 1; i <= 16; ++i) {
        if (road[i])
            ++nrOfRoads;
    }
    double ratio = 0.05 * nrOfRoads;
    double ratioStraight = ratio;
    double ratioDiagonal = ratio - 0.05;

    for (int i = 1; i <= 16; ++i) {
        if (road[i]) {
            traseu[i].push_back({roadNodes[i].first, roadNodes[i].second});
            if (i == 1 or i == 2) {
                traseu[i].push_back({ratioStraight * roadNodes[i].first, roadNodes[i].second});
            }
            if (i == 3 or i == 4) {
                traseu[i].push_back({ratioDiagonal * roadNodes[i].first, ratioDiagonal * roadNodes[i].second});
            }
            if (i == 5 or i == 6) {
                traseu[i].push_back({roadNodes[i].first, ratioStraight * roadNodes[i].second});
            }
            if (i == 7 or i == 8) {
                traseu[i].push_back({ratioDiagonal * roadNodes[i].first, ratioDiagonal * roadNodes[i].second});
            }
            if (i == 9 or i == 10) {
                traseu[i].push_back({ratioStraight * roadNodes[i].first, roadNodes[i].second});
            }
            if (i == 11 or i == 12) {
                traseu[i].push_back({ratioDiagonal * roadNodes[i].first, ratioDiagonal * roadNodes[i].second});
            }
            if (i == 13 or i == 14) {
                traseu[i].push_back({roadNodes[i].first, ratioStraight * roadNodes[i].second});
            }
            if (i == 15 or i == 16) {
                traseu[i].push_back({ratioDiagonal * roadNodes[i].first, ratioDiagonal * roadNodes[i].second});
            }
        }
    }
}

void outputCenteredJunction()
{
    SamitoAlex.open("Sugestion1.txt");

    double lastX, lastY;
    double firstX, firstY;
    lastX = lastY = -1000;
    firstX = firstY = -1000;

    SamitoAlex << 2 * nrOfRoads << "\n";
    for (int i = 1; i <= 16; ++i) {
        for (int j = 0; j < traseu[i].size(); ++j) {
            if (j == 0) {
                SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << " ";
            }
            else if (j == traseu[i].size() - 1) {
                if (firstX == -1000 && firstY == -1000) {
                    firstX = int(traseu[i][j].first);
                    firstY = int(-traseu[i][j].second);
                }
                SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << " 0\n";
                if (lastX != -1000 and lastY != -1000) {
                    SamitoAlex << lastX << " " << lastY << " ";
                    SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << " 0\n";
                }
                lastX = int(traseu[i][j].first);
                lastY = int(-traseu[i][j].second);

            }
//            else {
//                SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << "\n\n";
//
//                if (lastX != -1000 and lastY != -1000) {
//                    SamitoAlex << lastX << " " << lastY << "\n";
//                    SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << "\n\n";
//                }
//                lastX = int(traseu[i][j].first);
//                lastY = int(-traseu[i][j].second);
//
//                SamitoAlex << int(traseu[i][j].first) << " " << (-1)*int(traseu[i][j].second) << "\n";
//            }
            //debug(lastX, lastY);
        }
        traseu[i].clear();
    }

    SamitoAlex << firstX << " " << firstY << " " << lastX << " " << lastY << " 0\n";

    SamitoAlex.flush();
    SamitoAlex.close();
}

void generateRoundabout()
{
    nrOfRoads = 0;
    for (int i = 1; i <= 16; ++i) {
        if (road[i])
            ++nrOfRoads;
    }
    double ratio = 0.05 * nrOfRoads;
    double ratioStraight = ratio;
    double ratioDiagonal = ratio - 0.05;

    for (int i = 1; i <= 16; ++i) {
        if (road[i]) {
            traseu[i].push_back({startingX[i].first, startingY[i].second});
        }
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

            SamitoAlex.open("StoA.txt");
            SamitoAlex << "1\n";
            SamitoAlex.flush();
            SamitoAlex.close();

//            Generate Centered Junction
            generateCenteredJunction();

            SamitoAlex.open("StoA.txt", ios::app);
            SamitoAlex << "Centered Junction\n";
            SamitoAlex.flush();
            SamitoAlex.close();

            outputCenteredJunction();

//            Generate Roundabout
            //generateRoundabout();

            SamitoAlex.open("StoA.txt", ios::app);
            SamitoAlex << "Roundabout\n";
            SamitoAlex.flush();
            SamitoAlex.close();

            //outputCenteredJunction();


            //format for output is:
            // x1 y1 x2 y2 height
            // for each street
        }
        AlextoSami.close();
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