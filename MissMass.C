#include "physics.h"

double randNum() {
	double randNum = gRandom->Uniform(-1,1);

	return randNum;
}

void MissMass(double energy, double m_t) {
	
	TH1D *h1 = new TH1D("h1", "Unsmeared Energy", 100, 120, 300);
	TH1D *h2 = new TH1D("h2", "Smeared Energy", 100, 120, 300);
	TH1D *h3 = new TH1D("h3", "Unsmeared Angle", 100, 0.0, 2*M_PI);
	TH1D *h4 = new TH1D("h4", "Smeared Angle", 100, 0.0, 2*M_PI);
	TH1D *h5 = new TH1D("h5", "Missing Mass", 100, 900, 1000);

	TLorentzVector k(energy, 0, 0, energy);
	TLorentzVector t(m_t, 0, 0, 0);

	for (int i = 0; i <= 1000000; i++) {
		
		double theta = TMath::ACos(randNum());
		double kEPr = k[0]/(1+(k[0]/t[0])*(1-cos(theta)));

		h1->Fill(kEPr);
		h3->Fill(theta);
//defining smearing factors
		double FWHMangle = (0.025*1.57)/2.35;
		double FWHMenergy = (0.10*kEPr)/2.35;
	//generates an angle within a range determined by Gaus function with mean of originally generated value, and sigma of smearing factor
		double smeared_angle = gRandom->Gaus(theta, FWHMangle); //Gaus(mean, sigma)
		double smeared_energy = gRandom->Gaus(kEPr, FWHMenergy);

	// compton scattering... for pion production, change kPr to q	
		TLorentzVector kPr(smeared_energy, 0, 0, smeared_energy);
		TLorentzVector tPr = k + t - kPr;
		TLorentzVector Mmiss = kPr + tPr - k;
		std::cout << Mmiss[0] << endl;

		h2->Fill(smeared_energy);
		h4->Fill(smeared_angle);
		h5->Fill(Mmiss[0]);
	}

	TCanvas *c1 = new TCanvas("c1", "Smeared vs. Unsmeared", 800, 800);
	c1->Divide(2,2);
	c1->cd(1);
	h1->Draw("HIST");
	c1->cd(2);
	h2->Draw("HIST");
	c1->cd(3);
	h3->Draw("HIST");
	c1->cd(4);
	h4->Draw("HIST");

	TCanvas *c2 = new TCanvas("c2", "Missing Mass", 800, 800);
	h5->Draw("HIST");
	
	int nbins = h5->GetNbinsX(); 

	for (int i = 1; i <= nbins; i++) {
  		printf("Bin %d: %g\n", i, h5->GetBinContent(i));
}
	



}

//E-Res -> 10%
//Angle-Res -> 2.5%
//


//Testing that kEPr is actually generated
double kEPrGen(double energy, double m_t) {
	TLorentzVector k(energy, 0, 0, energy);
	TLorentzVector t(m_t, 0, 0, 0);

	double theta = TMath::ACos(randNum());
	double kEPr = k[0]/(1+(k[0]/t[0])*(1-cos(theta)));

	TLorentzVector kPr(kEPr, 0, 0, kEPr);
	return kPr[0];
}
