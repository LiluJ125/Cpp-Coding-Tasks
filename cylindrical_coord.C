#include "TMath.h"
#include "TH3.h"

// cylindrical coords in terms of r, theta(a), and z
// x = r cos(a)
// y = r sin(a)
// z = z

double num_gen() {
	TRandom *rnd = new TRandom3();
	rnd->SetSeed(0);
	double num = rnd->Rndm();

	return num;
}

void cylindrical_coord() {
	TH3D *cy = new TH3D("cy", "Cylinder", 100, -50, 50, 100, -50, 50, 100, -50, 50);

	double x;
	double y;
	double z;

	for (int i = 0; i < 100000; i++) {
		double r = num_gen()*20;
		double a = num_gen()*2*M_PI;
		z = num_gen()*70;

		x = r*cos(a);
		y = r*sin(a);
		cy->Fill(x,y,z);
	}

	TCanvas *c3 = new TCanvas("c3", "Cylinder", 800, 800);
	cy->Draw("LEGO2");
}
