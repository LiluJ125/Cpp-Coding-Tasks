double randNum() {
	double ramdNum = gRandom->Uniform(-1,1);

	return randNum;
}

/*void MissMass(double energy, double target) {
	
	TH2D *h1= new TH2D("h1", "Missing Mass", 100, 0.0, 50, 100. 0.0, 50);
	
	TLorentzVector k(k, 0, 0, k);
	TLorentzVector t(m_t, 0, 0, 0);
	double x = 0;

	for () {
		
		double theta = TMath::ACos(randNum());
		double kEPr = k[0]/(1+(k[0]/t[0])*(1-cos(theta)));

		double FWHMangle = 2.35*0.025;
		double FWHMenergy = 2.35*0.10;
		TLorentzVector kPr(kEPr, 0, 0, kEPr);
		TLorentzVector tPr = k + t - kPr;
		Mmiss = kPr + tPr - k;
		x += 1;
	}
	h1->Fill(x, Mmiss);


}

sigma = TMath::Sqrt(TMath::Power(x-kEPr, 2)/100000);
gaus = (1/(sigma*TMath::Sqrt(2*M_PI)))*TMath::Exp((-1/2)*TMath::Power((x-kEPr)/sigma, 2))
*/

void gauss_trials() {
	TF1 *f1 = new TF1("f1", "gaus(200)", 0, 20);
       f1->SetParameter(0,(1/((0.10	
}

//E-Res -> 10%
//Angle-Res -> 2.5%
