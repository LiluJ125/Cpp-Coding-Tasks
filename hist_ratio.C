//function to divide two histograms by eachother
//num_File should have form: "~/directories/rootFile"
//den_dir should have form: "~/directories/rootFile" 

/*void div_hist(std::string num_File = "~/opt/EvGen26/out/5cm/compton_p_200_in.root", std::string num_hist = "h3", std::string den_File = "~/opt/AR/acqu_user/ARout/CB/MC_p_200MeV.root", std::string den_hist = "PHYS_PhotonEnergy") {
*/

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

	// Rebin histograms equally in order to divide
	int n_new_bins = 40;
	double xMin = 0.0;
	double xMax = 800;

	double *edges = new double[n_new_bins + 1];
	double binWidth = (xMax - xMin) / n_new_bins;
	for (int i = 0; i <= n_new_bins; i++) {
		edges[i] = xMin + i * binWidth;
	}

	TH1F *new_hNumer = (TH1F*) hNumer->Rebin(n_new_bins, "new hNumer", edges);
	TH1F *new_hDenom = (TH1F*) hDenom->Rebin(n_new_bins, "new hDenom", edges);


	TH1F *h_ratio;
	h_ratio->Divide(hNumer, hDenom);

	TCanvas *c3 = new TCanvas("c3", "Ratio Hist", 800, 800);
	h_ratio->Draw("HIST");
	
}
