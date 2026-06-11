//function to divide two histograms by eachother
//num_File should have form: "~/directories/rootFile"
//den_dir should have form: "~/directories/rootFile" 

/*void div_hist(std::string num_File = "~/opt/EvGen26/out/5cm/compton_p_200_in.root", std::string num_hist = "h3", std::string den_File = "~/opt/AR/acqu_user/ARout/CB/MC_p_200MeV.root", std::string den_hist = "PHYS_PhotonEnergy") {
*/

void rebin_hist(TH1F oldHist, TH1F refHist) {
	//getting the information from one histogram that will determine the bins of the new histogram
	int nbins = refHist->GetNbinsX();
	double xMin = refHist->GetXaxis()->GetXmin();
	double xMax = refHist->GetXaxis()->GetXmax();

	//clones the histogram you're rebinning and resets its bin sizes to match refHist
	TH1F *h_rebinned = (TH1F*)oldHist->Clone("h_rebinned");
	h_rebinned->Reset();

	//loops through each of the original histogram bins, takes the center of the bin and everything in it, and adds it to h_rebinned, where the information is sorted into the new bins
	for (int i = 1; i <= oldHist->GetNbinsX(); i++) {
		double center = oldHist->GetBinCenter(i);
		double content = oldHist->GetBinContent(i);
		h_rebinned->Fill(center, content);
	}
}
/*
void div_hist() {

	std::string num_File;
	std::string num_hist;
	std::string den_File;
	std::string den_hist;

	std::cout << "Enter first pathway and file: " << endl;
	std::cin >> num_File;
	std::cout << "Enter first histogram name: ";
	std::cin >> num_hist;
	std::cout << "Enter second pathway and file: " << endl;
	std::cin >> den_File;
	std::cout << "Enter second histogram name: " << endl;
	std::cin >> den_hist;

	std::unique_ptr<TFile> numer(TFile::Open(num_File.c_str())); 
	std::unique_ptr<TFile> denom(TFile::Open(den_File.c_str())); //Root doesn't like std::string for some functions, so have to use the .c_str() modifier to convert

	TCanvas *c1 = new TCanvas("c1", "Hist 1", 800, 800); //create divided canvas
	c1->Divide(1,2);

	TH1F *hNumer = (TH1F*)numer->Get(num_hist.c_str()); 
	hNumer->SetDirectory(0); //pulls and saves histogram before Root can close the file

	c1->cd(1); //pick first space on canvas
	hNumer->Draw("HIST");

	TH1F *hDenom = (TH1F*)denom->Get(den_hist.c_str());
	hDenom->SetDirectory(0); //save this histogram also before file closes

	c1->cd(2); //pick second space on canvas
	hDenom->Draw("HIST");

	// Check to see if histograms have same number of bins. If not, rebin histograms equally in order to divide
	if (hNumer->GetNbinsX() > hDenom->GetNbinsX()) {
		rebin_hist(hDenom, hNumer);
	} else if (hNumer->GetNbinsX() < hDenom->GetNbinsX()){
		rebin_hist(hNumer, hDenom);
	}


	TH1F *h_ratio;
	h_ratio->Divide(hNumer, hDenom);

	TCanvas *c3 = new TCanvas("c3", "Ratio Hist", 800, 800);
	h_ratio->Draw("HIST");
	
}
*/

