void compton_scatter(double kE, double pM, double kScatTheta) {

	double kScatE = kE/((kE/pM)*(1-cos(kScatTheta))+1);
	double pScatP = sqrt(TMath::Power(kScatE, 2)-TMath::Power(pM, 2));
	double pScatE = pM + TMath::Power(kE, 2)-((2*TMath::Power(kE, 2))/((kE/pM)*(1-cos(kScatTheta))+1))+((TMath::Power(kE, 2))/TMath::Power(((kE/pM)*(1-cos(kScatTheta))+1), 2));
	double kScatP = kE - pScatP;


	std::cout << "-------------------------------------------------" << endl;
	std::cout << "Scattered photon energy: " << kScatE << endl;
	std::cout << "Scattered target momentum: " << pScatP << endl;
	std::cout << "Final target energy: " << pScatE << endl;
	std::cout << "Final photon momentum: " << kScatP << endl;

}
