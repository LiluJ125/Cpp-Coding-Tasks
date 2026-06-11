
void vector_scatter(double kE, double tM, double kPrTh) {

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

