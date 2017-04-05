#include "neuronetwork.h"
#include <random>
#include <algorithm>
#include<fstream>

void NeuroNetwork::LearnNeuroNet(const vector<Image>& images) {
    this->images = images;
    M = images.size();
    N = images[0].neuros.size();
    WM.resize(N);
    for (int i = 0; i < N; i++) {
        WM[i].resize(N);
    }
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < i; j++) {
            double temp = 0;
            for (int k = 0; k < M; k++) {
                temp += images[k].neuros[i] * images[k].neuros[j];
            }
            WM[i][j] = WM[j][i] = temp / double(N);
        }
        WM[i][i] = 0;
    }
}



//void NeuroNetwork::RecognizeImage(const vector<neuroState>& neuros, vector<neuroState>& result) {
void NeuroNetwork::RecognizeImage(const vector<char>& neuros, vector<char>& result) {
    if (neuros.size() != N) return;
    result = neuros;
    while (Step(result));
}

//void NeuroNetwork::RecognizeImage(const vector<neuroState>& neuros, Image& resul) {
void NeuroNetwork::RecognizeImage(const vector<char>& neuros, Image& resul) {
    //vector<neuroState> result;
    vector<char> result;
    RecognizeImage(neuros, result);
    resul.neuros = result;
    resul.name = "r";
   // int eps = N/4;
    int diff = 10000;
    int resIm;
    for (int i = 0; i < M; i++) {
        int d = 0;
        for (int j = 0; j < N; j++) {
            d += (result[j] != images[i].neuros[j]);
        }
            if (d < diff) {
                diff = d;
                resIm = i;
            }
    }
//    if (diff < eps) {
//        //name = images[resIm].name;
//        image = images[resIm];
//    }
//    else{
//        Image im;
//        im.neuros = vector<neuroState>(N);
//        im.name = "Not Found";
//        //name = "Not Found";
//    }
}

//bool NeuroNetwork::Step(vector<neuroState>& neuros) {
bool NeuroNetwork::Step(vector<char>& neuros) {
    bool wasChanged = false;
    vector<int> order;
    for (int i = 0; i < N; i++) {
        order.push_back(i);
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(order.begin(), order.end(), g);

    for (int i = 0; i < N; i++) {
        //neuroState temp = NeuronCalculate(neuros, order[i]);
        char temp = NeuronCalculate(neuros, order[i]);
        wasChanged |= (temp != neuros[order[i]]);
        neuros[order[i]] = temp;
        /*neuroState temp = NeuronCalculate(neuros, i);
        wasChanged |= (temp != neuros[i]);
        neuros[i] = temp;*/
    }
    return wasChanged;
}

//NeuroNetwork::neuroState NeuroNetwork::NeuronCalculate(const vector<neuroState>& neuros, int i) {
char NeuroNetwork::NeuronCalculate(const vector<char>& neuros, int i) {
    double temp = 0;
    for (int j = 0; j < N; j++) {
        temp += neuros[j] * WM[i][j];
    }
   // return (temp > 0) ? neuroState::Up : neuroState::Low;
    return (temp > 0) ? 1 : -1;
}

void NeuroNetwork::Image::Read(string filename, int n, int m) {
    neuros.resize(n*m);
    ifstream input(filename);
    input >> name;
    string temp;
    for (int i = 0; i < n; i++) {
        input >> temp;
        for (int j = 0; j < m; j++) {
            //neuros[i*n + j] = (temp[j] == '.') ? neuroState::Low : neuroState::Up;
            neuros[i*n + j] = (temp[j] == '.') ? -1 :1;
        }
    }
    input.close();
}

void NeuroNetwork::Image::Save(string filename, int n, int m) {
    if (neuros.size() != n*m) return;
    ofstream output(filename);
    output << name;
    output << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //char temp = (neuros[i*n + j] == neuroState::Up) ? '#' : '.';
            char temp = (neuros[i*n + j] == 1) ? '#' : '.';
            output << temp;
        }
        output << "\n";
    }
    output.close();
}
