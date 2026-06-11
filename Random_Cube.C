#include "TH3.h"

double num_gen() {
	TRandom *rnd = new TRandom3();
	rnd->SetSeed(0);
	double num = rnd->Rndm();

	return num;
}

void Random_cube() {
	TH3D *h3 = new TH3D("h3", "cube", 100, 0.0, 50, 100, 0.0, 50, 100, 0.0, 50);

	for(int i = 0; i < 10000; i++) {
		double x = num_gen()*100;
		double y = num_gen()*100;
		double z = num_gen()*100;

		h3->Fill(x,y,z);
	}
	TCanvas *c3 = new TCanvas("c3", "Cube", 800, 800);
	h3->Draw("LEGO2");
}
