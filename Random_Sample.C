#include "TH2.h"
#include "TRandom3.h"

double num_gen() {
	TRandom *rnd = new TRandom3();
	rnd->SetSeed(0);
	double num = rnd->Rndm();

	return num;
}

void Random_Sample() {
	TH2D *h2 = new TH2D("h2", "First Histogram", 50, 0.0, 100, 50, 0.0, 100);

	for(int i = 0; i < 1000; i++) {
		double x = num_gen()*100;
		double y = num_gen()*100;

		h2->Fill(x,y);
	}

	TCanvas *c2 = new TCanvas("c2", "First Histogram", 800, 800);
	c2->GetPad(0)->SetFillColor(kPink +10);
	h2->SetLineColor(kGreen);
	h2->SetLineWidth(1);
	h2->Draw("LEGO2");
}
