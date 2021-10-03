#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <bits/stdc++.h>
#include <unistd.h>
#define timeWait 2
#define nrRoads 20
#define maxX 142
#define maxY 142
#define offset 4.6
#define addOffset 4.5
#define PI 3.14159265
#define ratioConstant 0.05

#pragma comment(lib, "shell32.lib")

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
#define debug(x...)
#endif

CHAR my_documents[MAX_PATH];
HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 1, my_documents);
string input(my_documents);

ifstream AlextoSami(input + "\\alextosami.txt"); // INPUT
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
string nextSuggestion;

vector <pair <double, double> > roadNodes(nrRoads);
const double startingX[17] = {0, maxX + addOffset, maxX + addOffset, //1 2
                      cos(toRad(45)) * maxX + offset * sqrt(2),  cos(toRad(45)) * maxX, //3 4
                      offset, -offset, //5 6
                      -(cos(toRad(45)) * maxX),  -(cos(toRad(45)) * maxX + offset * sqrt(2)), //7 8
                      -(maxX + addOffset), -(maxX + addOffset),  //9 10
                      -(cos(toRad(45)) * maxX + offset * sqrt(2)),  -(cos(toRad(45)) * maxX), //11 12
                      -offset, offset, //13 14
                      cos(toRad(45)) * maxX,  cos(toRad(45)) * maxX + offset * sqrt(2), //15 16
                    };
const double startingY[17] = {0, -offset, offset, //1 2
                      sin(toRad(45)) * maxY, sin(toRad(45)) * maxY + offset * sqrt(2), //3 4
                      maxY + addOffset, maxY + addOffset, //5 6
                      sin(toRad(45)) * maxY + offset* sqrt(2), sin(toRad(45)) * maxY, //7 8
                      offset, -offset, //9 10
                      -(sin(toRad(45)) * maxY), -(sin(toRad(45)) * maxY + offset * sqrt(2)), //11 12
                      -(maxY + addOffset), -(maxY + addOffset), //13 14
                      -(sin(toRad(45)) * maxY  + offset * sqrt(2)), -(sin(toRad(45)) * maxY), //15 16
                     };
int nrOfRoads;

void readRoads(string input)
{
    //AlextoSami.open(input);
    char word;
    nrOfRoads = 0;
    for (int i = 1; i <= 16; ++i) {
        AlextoSami >> word;
        if (word == '0')
            road[i] = false;
        else {
            road[i] = true;
            ++nrOfRoads;
        }

        if (road[i]) {
            double x, y;
            x = startingX[i];
            y = startingY[i];
            roadNodes[i] = {x, y};
        }
    }
    debug(roadNodes);
    //AlextoSami.close();
}

vector <pair <double, double> > traseu[nrRoads];


void generateCenteredJunction()
{
    double ratio = ratioConstant * nrOfRoads;
    double ratioStraight = ratio;
    double ratioDiagonal = ratio - ratioConstant;

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
    SamitoAlex.open(nextSuggestion);
    nextSuggestion[10]++;

    double lastX, lastY;
    double firstX, firstY;
    lastX = lastY = -1000;
    firstX = firstY = -1000;

    SamitoAlex << 2 * nrOfRoads << "\n";
    for (int i = 1; i <= 16; ++i) {
        for (int j = 0; j < traseu[i].size(); ++j) {
            if (j == 0) {
                SamitoAlex << traseu[i][j].first << " " << (-1)*(traseu[i][j].second) << " ";
            }
            else if (j == traseu[i].size() - 1) {
                if (firstX == -1000 && firstY == -1000) {
                    firstX = traseu[i][j].first;
                    firstY = int(-traseu[i][j].second);
                }
                SamitoAlex << traseu[i][j].first << " " << (-1)*(traseu[i][j].second) << " 0\n";
                if (lastX != -1000 and lastY != -1000) {
                    SamitoAlex << lastX << " " << lastY << " ";
                    SamitoAlex << traseu[i][j].first << " " << (-1)*(traseu[i][j].second) << " 0\n";
                }
                lastX = traseu[i][j].first;
                lastY = -traseu[i][j].second;

            }
        }
        traseu[i].clear();
    }

    SamitoAlex << firstX << " " << firstY << " " << lastX << " " << lastY << " 0\n";
    SamitoAlex << "Centered Junction\n";

    SamitoAlex.flush();
    SamitoAlex.close();
}

void generateRoundabout()
{
    double ratio = ratioConstant * nrOfRoads;
    double ratioStraight = ratio;
    double ratioDiagonal = ratio - ratioConstant;

    for (int i = 1; i <= 16; ++i) {
        traseu[i].push_back({startingX[i], startingY[i]});

        if (i == 1 or i == 2) {
            traseu[i].push_back({ratioStraight * startingX[i], startingY[i]});
        }
        if (i == 3 or i == 4) {
            traseu[i].push_back({ratioDiagonal * startingX[i], ratioDiagonal * startingY[i]});
        }
        if (i == 5 or i == 6) {
            traseu[i].push_back({startingX[i], ratioStraight * startingY[i]});
        }
        if (i == 7 or i == 8) {
            traseu[i].push_back({ratioDiagonal * startingX[i], ratioDiagonal * startingY[i]});
        }
        if (i == 9 or i == 10) {
            traseu[i].push_back({ratioStraight * startingX[i], startingY[i]});
        }
        if (i == 11 or i == 12) {
            traseu[i].push_back({ratioDiagonal * startingX[i], ratioDiagonal * startingY[i]});
        }
        if (i == 13 or i == 14) {
            traseu[i].push_back({startingX[i], ratioStraight * startingY[i]});
        }
        if (i == 15 or i == 16) {
            traseu[i].push_back({ratioDiagonal * startingX[i], ratioDiagonal * startingY[i]});
        }
    }
}

void outputRoundabout()
{
    SamitoAlex.open(nextSuggestion);
    nextSuggestion[10]++;

    SamitoAlex << nrOfRoads + 16 << "\n";
    for (int i = 1; i <= 16; ++i) {
        for (int j = 0; j < traseu[i].size(); ++j) {
            if (road[i] and j == 0) {
                SamitoAlex << traseu[i][j].first << " " << (-1)*(traseu[i][j].second) << " ";
            }
            if (road[i] and j == 1) {
                SamitoAlex << traseu[i][j].first << " " << (-1)*(traseu[i][j].second) << " 0\n";
            }
        }
    }

    vector <pair <double, double> > points(nrRoads);
    for (int i = 1; i <= 16; ++i) {
        debug(i, traseu[i]);
        points[i] = traseu[i][1];
        debug(i, points[i]);
        traseu[i].clear();
    }

    for (int i = 2; i <= 16; ++i) {
        SamitoAlex << points[i - 1].first << " " << (-1)*(points[i - 1].second) << " " << points[i].first <<  " " << (-1)*points[i].second << " 0\n";

    }
    SamitoAlex << points[1].first << " " << (-1)*(points[1].second) << " " << points[16].first <<  " " << (-1)*points[16].second << " 0\n";
    SamitoAlex << "Roundabout\n";
    points.clear();
    SamitoAlex.flush();
    SamitoAlex.close();
}

bool checkIfValidFlower()
{
    int comingIn, goingOut;
    comingIn = goingOut = 0;
    for (int i = 1; i <= 16; ++i) {
        if (road[i]) {
            if (i % 2 == 0) {
                ++comingIn;
            } else {
                ++goingOut;
            }
        }
    }

    return comingIn == 1;
}

void generateFlower()
{
    for (int i = 1; i <= 16; ++i) {
        if (road[i]) {
            traseu[i].push_back({roadNodes[i].first, roadNodes[i].second});
        }
    }
}

void outputFlower()
{
    SamitoAlex.open(nextSuggestion);
    nextSuggestion[10]++;
    SamitoAlex << nrOfRoads << "\n";
    for (int i = 1; i <= 16; ++i) {
        if (road[i]) {
            SamitoAlex << traseu[i][0].first << " " << (-1) * traseu[i][0].second << " 0 0 0\n";
        }
        traseu[i].clear();
    }
    SamitoAlex << "Flower Junction\n";
    SamitoAlex.flush();
    SamitoAlex.close();
}

void outputBouquet()
{
    SamitoAlex.open(nextSuggestion);
    nextSuggestion[10]++;
    SamitoAlex << nrOfRoads - 1 << "\n";

    double firstX, firstY;
    for (int i = 1; i <= 16; ++i) {
        if (road[i] && i % 2 == 0) {
            firstX = roadNodes[i].first;
            firstY = roadNodes[i].second;
        }
    }

    for (int i = 1; i <= 16; ++i) {
        if (road[i] && i % 2 == 1) {
            SamitoAlex << firstX << " " << (-1) * firstY << " " << roadNodes[i].first << " " << (-1) * roadNodes[i].second << " 0\n";
        }
    }

    SamitoAlex << "Bouquet Junction\n";
    SamitoAlex.flush();
    SamitoAlex.close();
}

void outputValcele()
{
    SamitoAlex.open(nextSuggestion);
    nextSuggestion[10]++;
    SamitoAlex << 10 << "\n";

    SamitoAlex << startingX[1] << " " << -startingY[1] << " " << startingX[10] << " " << -startingY[10] << " 0\n";
    SamitoAlex << startingX[2] << " " << -startingY[2] << " " << startingX[9] << " " << -startingY[9] << " 0\n";

    SamitoAlex << startingX[6] << " " << -startingY[6] << " " << "-15.65 -107.95" << " 0\n";
    SamitoAlex << "-15.65 -107.95 -44.5 -52.8" << " 0\n";
    SamitoAlex << "-44.5 -52.8 -127 " << -startingY[2] << " 0\n";

    SamitoAlex << startingX[5] << " " << -startingY[5] << " " << startingX[5] << " -45" << " 0\n";
    SamitoAlex << startingX[5] << " -45 " << startingX[5] << " 37.35" << " 1\n";
    SamitoAlex << startingX[5] << " 37.35 55 80.05" << " 0\n";
    SamitoAlex << "55 80.05 93.1 80.75" << " 0\n";
    SamitoAlex << "93.1 80.75 130.6 " << -startingY[1] << " 0\n";



    SamitoAlex << "Valcele\n";
    SamitoAlex.flush();
    SamitoAlex.close();
}

void readInfo()
{
    string code;
    string state;
    int nrOfOutputs;

    state = "idle";


    debug(input);

    while (true) {

        sleep(timeWait);
        AlextoSami.open(input + "\\alextosami.txt");
        AlextoSami >> code;
        debug(code);


        state = interpretCode(code, state);
        nextSuggestion = "Suggestion1.txt";
        nrOfOutputs = 0;
        debug(state);



//        Possible states are:
//          exit
//          generateSuggestions
//          createSuggestion
//          simulateCars
        if (state == "exit")
            return;
        if (state == "generateSuggestions") {
            readRoads(input);

            //format for output is:
            // x1 y1 x2 y2 height
            // for each street

//            Generate Centered Junction
            generateCenteredJunction();
            outputCenteredJunction();
            ++nrOfOutputs;

//            Generate Flower Junction
            if (checkIfValidFlower()) {
                generateFlower();
                outputFlower();
                ++nrOfOutputs;
            }

//             Generate Bouquet Junction
            if (checkIfValidFlower()) {
                outputBouquet();
                ++nrOfOutputs;
            }

//            Generate Roundabout
            generateRoundabout();
            outputRoundabout();
            ++nrOfOutputs;


            if (road[1] == true and road[2] == true
                and road[3] == false and road[4] == false
                and road[5] == true and road[6] == true
                and road[7] == false and road[8] == false
                and road[9] == true and road[10] == true
                and road[11] == false and road[12] == false
                and road[13] == false and road[14] == false
                and road[15] == false and road[16] == false) {
//            Generate Valcele
                outputValcele();
                ++nrOfOutputs;
            }


        }
        SamitoAlex.open("samitoalex.txt");
        SamitoAlex << nrOfOutputs << "\n";
        SamitoAlex.flush();
        SamitoAlex.close();

        AlextoSami.close();
    }
}

int main()
{
    readInfo();
    return 0;
}