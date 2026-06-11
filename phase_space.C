#include "TH3.h"
#include "TMath.h"


// generate a num between -1 and 1 -> arccos number = theta -> cos(theta)

double num_gen() {
	TRandom *rnd = new TRandom3();
	rnd->SetSeed(0);
	double num = rnd->Rndm();

	return num;
}

double arccos_gen() {
	double arccos_num = gRandom->Uniform(-1, 1);

	return arccos_num;
}


void spherical_coord2() {
	TH3D *h3 = new TH3D("h3", "Sphere", 100, -20, 20, 100, -20, 20, 100, -20, 20);
	for(int i = 0; i < 100000; i++) {
		double r = cbrt(num_gen()*20);
		double p = num_gen()*M_PI;
		double get_theta = TMath::ACos(arccos_gen())*2*M_PI;

		double x = r*sin(p)*cos(get_theta);
		double y = r*sin(p)*sin(get_theta);
		double z = r*cos(p);

		h3->Fill(x,y,z);
	}

	TCanvas *c3 = new TCanvas("c3", "Sphere", 800, 800);
	h3->Draw("LEGO2");
}
