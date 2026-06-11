#include "physics.h"
#include "TLorentzVector.h"

/*void vector_scatter(double kE, double tM, double kPrTh) {

	//Lab Frame
	double kPrRad = kPrTh * (M_PI/180);
	TLorentzVector k(kE, 0, 0, kE);
	TLorentzVector t(0, 0, 0, tM);

	double kEPr = kE/(1+(kE/tM)*(1-cos(kPrRad)));
	double tEPr = kE + tM - kEPr;

	double kMomPr = kEPr;
	double kMomxPr = kMomPr*cos(kPrRad);
	double kMomyPr = kMomPr*sin(kPrRad);

	TLorentzVector kPr(kMomxPr, kMomyPr, 0, kEPr);
	TLorentzVector tPr = k + t - kPr;

	std::cout << "------------------------------------------------------------------------------------------------" << endl;
	std::cout << "Lab frame final state: " << endl;
	kPr.Print();
	tPr.Print(); 


	//CM Frame
	TLorentzVector ktPr = kPr + tPr;
	
	TVector3 beta = ktPr.BoostVector();
	
	TLorentzVector kPr_str = kPr;
	kPr_str.Boost(-beta);

	TLorentzVector tPr_str = tPr; 
	tPr_str.Boost(-beta);

	std::cout << "CM frame final state: " << endl;
	kPr_str.Print();
	tPr_str.Print();
}
*/
/*double kEPr_find(double kE, double tM) {

	for (double kPrRad = 0; kPrRad <= 200; kPrRad += 0.1) {
		double kEPr = kE/(1+(kE/tM)*(1-cos(kPrRad)));
	}
	return kEPr;
	
}
*/

void compton_plot(double kE, double tM) {
	//Things to plot as function of scattered photon theta:
	//scattered photon energy
	TH2D *h1 = new TH2D("h1", "Scattered k Energy vs. Theta", 50, 0.0, 2*M_PI, 100, 0.0, 500);
	for (double kScatTh = 0; kScatTh <= 200; kScatTh += 0.1) {
		double kEPr = kE/(1+(kE/tM)*(1-cos(kScatTh)));
		h1->Fill(kScatTh, kEPr);
	}
/*
	//recoil kinetic energy
	TH2D *h2 = new TH2D("h2", "Recoil KE vs. Theta", 100, 0.0, 2*M_PI, 100, 0.0, ???);

	//recoil target angle
	TH2D *h3 = new TH2D("h3", "Recoil Target Angle vs. Theta", 100, 0.0, 2*M_PI, 100, 0.0, ???);
*/
	}
