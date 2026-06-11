#include "TH1.h"

void oneD_Hist() {
	TH1F *h1 = new TH1F("h1", "Points", 100, 0.0, 50);
	TCanvas *c1 = new TCanvas("c1", "Points", 800, 800);

	TF1 *f1 = new TF1("f1", "sin(x)*x", 0, 50); 
	h1->FillRandom("f1", 100);
	//h1->Draw("E"); <- with error bars
	h1->Draw();
}
