#pragma once
#include<vector>
#include<string>
using namespace std;

class NeuroNetwork {
private:
	enum neuroState {
		Low = -1, Up = 1
	};
public:
	
	struct Image {
		/*Image(string name) {
			this->name = name;
			neuros.resize(0);
		}*/
		vector<neuroState> neuros;
		string name;
		void Read(string filename, int n, int m);
		void Save(string filename, int n, int m);
	};
private:
	vector<Image> images;
	vector<vector<double>> WM;
	int N;//amount of neuros
	int M;//amount of images
public:
	//NeuroNetwork(vector<Image> im): images(im) {}
	void LearnNeuroNet(const vector<Image>& images);
	void RecognizeImage(const vector<neuroState>& neuros, vector<neuroState>& result);
	void RecognizeImage(const vector<neuroState>& neuros, string& name, Image& image, Image& result);
	neuroState NeuronCalculate(const vector<neuroState>& neuros, int i);
	bool Step(vector<neuroState>& neuros);
};