#include"neuro.h"
#include<iostream>

int main() {
	string imageFile;
	vector<NeuroNetwork::Image> ims;
	NeuroNetwork::Image im;
	int n = 10;
	int m = 10;
	for (int i = 0; i < 3; i++) {
		cin >> imageFile;
		im.Read(imageFile, n, m);
		ims.push_back(im);
	}
	NeuroNetwork net;
	net.LearnNeuroNet(ims);
	string name;
	NeuroNetwork::Image res;
	while (true) {
		cin >> imageFile;
		NeuroNetwork::Image imTest;
		imTest.Read(imageFile, n, m);
		net.RecognizeImage(imTest.neuros, name, imTest, res);
		cout << name;
		imTest.Save(imageFile + "res.txt", n, m);
		res.Save(imageFile + "realre.txt",n,m);
	}
}