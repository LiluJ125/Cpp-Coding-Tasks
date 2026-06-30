#include "physics.h"

// scattered theta root histogram -> h4
// PHYS_PhotonTheta

//void det_eff(std::string num_File = "~/opt/EvGen26/out/5cm/compton_p_200_in.root", std::string num_hist = "h3", std::string den_File = "~/opt/AR/acqu_user/ARout/CB/MC_p_200MeV.root", std::string den_hist = "PHYS_PhotonEnergy") {

void det_eff(std::string num_File = "~/opt/EvGen26/out/5cm/compton_p_200_in.root", std::string num_hist = "h4", std::string den_File = "~/opt/AR/acqu_user/ARout/CB/MC_p_200MeV.root", std::string den_hist = "PHYS_PhotonTheta") {


	std::unique_ptr<TFile> numer(TFile::Open(num_File.c_str())); 
	std::unique_ptr<TFile> denom(TFile::Open(den_File.c_str())); 

	TH1F *hNumer = (TH1F*)numer->Get(num_hist.c_str()); 
	hNumer->SetDirectory(0); //pulls and saves histogram before Root can close the file

	//replot histograms as a function of angle
	TH2F *NumAngvsE = new TH2F("NumAngvsE", "NumAngvsE", 18, 0.0, M_PI, 100, 100, 200);
	for (int k=1; k <= hNumer->GetNbinsX(); k++) {
		double numcenter = hNumer->GetBinCenter(k);
		long double numtheta = TMath::ACos(1 - kMP_MEV*((1.0/numcenter)-(1.0/200.0)));
		NumAngvsE->Fill(numtheta, numcenter);
	}
	TCanvas *Ang = new TCanvas("Ang", "Ang", 800, 800);
	Ang->Divide(1,2);
	Ang->cd(1);
	NumAngvsE->DrawCopy("HIST");


	TH1F *hDenom = (TH1F*)denom->Get(den_hist.c_str());
	hDenom->SetDirectory(0); //also save this histogram before file closes

	TH2F *DenAngvsE = new TH2F("DenAngvsE", "DenAngvsE", 18, 0.0, M_PI, 100, 100, 200);
	for (int i=1; i <= hDenom->GetNbinsX(); i++) {
		double dencenter = hDenom->GetBinCenter(i);
		long double dentheta = TMath::ACos(1 - kMP_MEV*((1.0/dencenter)-(1.0/200.0)));
		DenAngvsE->Fill(dentheta, dencenter);
	}

	Ang->cd(2);
	DenAngvsE->DrawCopy("HIST");


	TH2F *Divided = (TH2F*)NumAngvsE->Clone("Divided");
	Divided->Divide(NumAngvsE, DenAngvsE);
	TCanvas *c1 = new TCanvas("c1", "Divided Histograms", 800, 800);
	Divided->DrawCopy("HIST");
}
/*
bool NumNameCheck(const char* name_to_check) {
	if (gDirectory->FindObject(name_to_check)) {
		return true;
	} else {
		return false;
	}
}

void det_reso() {
	std::string num_File;
	std::string num_hist; 
	std::string den_File;
       	std::string den_hist;

	std::cout << "enter the pathway to the numerator file: " << endl;
	std::cin >> num_File;
	std::cout << "enter the numerator histogram's name: " << endl;
	std::cin >> num_hist;
	std::cout << "enter the pathway to the denominator file: " << endl;
	std::cin >> den_File;
	std::cout << "enter the denominator histogram's name: " << endl;
	std::cin >> den_hist;

	std::unique_ptr<TFile> numer(TFile::Open(num_File.c_str())); 
	std::unique_ptr<TFile> denom(TFile::Open(den_File.c_str())); 

	TH1F *hNumer = (TH1F*)numer->Get(num_hist.c_str()); 
	hNumer->SetDirectory(0);

	TH1F *hDenom = (TH1F*)denom->Get(den_hist.c_str());
	hDenom->SetDirectory(0);


	int DegPerBin;
	double Mtarget;
	double energy;

	std::cout << "how many degrees should be in each bin? " << endl;
	std::cin >> DegPerBin;
	std::cout << "what was the target mass? " << endl;
	std::cin >> Mtarget;
	std::cout << "what was the energy? " << endl;
	std::cin >> energy;

	int NumberOfBins = 180/DegPerBin;

	TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
	c1->Divide(1,2);
	
	if (NumNameCheck("NumAngvsE") == false) {
		TH2F *NumAngvsE = new TH2F("NumAngvsE", "NumAngvsE", NumberOfBins, 0.0, M_PI, 100, 100, 200);

		for (int i=1; i <= hNumer->GetNbinsX(); i++) {
			double center = hNumer->GetBinCenter(i);
			long double theta = TMath::ACos(1-Mtarget*((1.0/center)-(1.0/energy)));
			NumAngvsE->Fill(theta, center);
			c1->cd(1);
			NumAngvsE->DrawCopy("HIST");
		}
	} else {
		TH2F *DenAngvsE = new TH2F("DenAngvsE", "DebAngvsE", NumberOfBins, 0.0, M_PI, 100, 100, 200); 

		for (int i=1; i <= hDenom->GetNbinsX(); i++) {
			double center = hDenom->GetBinCenter(i);
			long double theta = TMath::ACos(1-Mtarget*((1.0/center)-(1.0/energy)));
			DenAngvsE->Fill(theta, center);
			c1->cd(2);
			DenAngvsE->DrawCopy("HIST");
		}
	}

}
*/
