void det_eff(std::string num_File = "~/opt/EvGen26/out/5cm/compton_p_200_in.root", std::string num_hist = "h3", std::string den_File = "~/opt/AR/acqu_user/ARout/CB/MC_p_200MeV.root", std::string den_hist = "PHYS_PhotonEnergy") {

	std::unique_ptr<TFile> numer(TFile::Open(num_File.c_str())); 
	std::unique_ptr<TFile> denom(TFile::Open(den_File.c_str())); 
	
	TCanvas *c1 = new TCanvas("c1", "Original Histograms", 800, 800); //create divided canvas
	c1->Divide(1,2);

	TH1F *hNumer = (TH1F*)numer->Get(num_hist.c_str()); 
	hNumer->SetDirectory(0); //pulls and saves histogram before Root can close the file

	TH1F *hDenom = (TH1F*)denom->Get(den_hist.c_str());
	hDenom->SetDirectory(0); //also save this histogram before file closes

	TH1F *Real_num = new TH1F("Real_num", "Numerator", 30, 0.0, 300);
	Real_num->SetMaximum(70000);

	for(int i=1; i <= hNumer->GetNbinsX(); i++) {
		double center = hNumer->GetBinCenter(i);
		double content = hNumer->GetBinContent(i);
		Real_num->Fill(center, content);
	}

	Int_t nbins = Real_num->GetNbinsX();
/*	for (Int_t i = 1; i <= nbins; i++) {
   		printf("Bin %d (x = %g): Content = %g\n", i, Real_num->GetBinCenter(i), Real_num->GetBinContent(i));
	}
*/
	TH1F *Real_den = new TH1F("Real_den", "Denominator", 30, 0.0, 300);
	Real_den->SetMaximum(70000);

	for(int i=1; i <= hDenom->GetNbinsX(); i++) {
		double center = hDenom->GetBinCenter(i);
		double content = hDenom->GetBinContent(i);
		Real_den->Fill(center, content);
	}

	Int_t rbins = Real_den->GetNbinsX();
/*	for (Int_t i = 1; i <= rbins; i++) {
   		printf("Bin %d (x = %g): Content = %g\n", i, Real_den->GetBinCenter(i), Real_den->GetBinContent(i));
	}
*/
	c1->cd(1); //pick first space on canvas
	hNumer->Draw("HIST");

	c1->cd(2); //pick second space on canvas
	hDenom->Draw("HIST");

	//clone one histogram and clear it, then use divide function to create new histogram

	TH1F *h_div = (TH1F*)Real_num->Clone("h_div");
	h_div->Reset();
	h_div->Divide(Real_num, Real_den);
	h_div->SetTitle("Divided Histogram");

	Int_t sbins = h_div->GetNbinsX();
/*	for (Int_t i = 1; i <= sbins; i++) {
   		printf("Bin %d (x = %g): Content = %g\n", i, h_div->GetBinCenter(i), h_div->GetBinContent(i));
	}
*/
	TCanvas *c2 = new TCanvas("c2", "Divided Histograms", 800, 800); 
	h_div->DrawCopy("HIST");
	std::cout << h_div->GetEntries() << endl;
}


