#include "TH3.h"
#include "TMath.h"

// Radial Dist (r), Azimuthal Angle (theta(a)), Polar Angle (p)
// x = r sin(p)cos(a)
// y = r sin(p)sin(p)
// z = r cos(p)

double num_gen() {
	TRandom *rnd = new TRandom3();
	rnd->SetSeed(0);
	double num = rnd->Rndm();

	return num;
}

void spherical_coord() {
	TH3D *h3 = new TH3D("h3", "Sphere", 100, -20, 20, 100, -20, 20, 100, -20, 20);
	for(int i = 0; i < 100000; i++) {
		double r = num_gen()*20;
		double p = num_gen()*M_PI;
		double a = num_gen()*2*M_PI;

		double x = r*sin(p)*cos(a);
		double y = r*sin(p)*sin(a);
		double z = r*cos(p);


		h3->Fill(x,y,z);
	}

	TCanvas *c3 = new TCanvas("c3", "Sphere", 800, 800);
	h3->Draw("LEGO2");
}
