void Hist_present(TH1F* hist, std::string name, std::string Xaxis, std::string Yaxis) {	

	hist->SetLineColor(kBlue);
	hist->SetLineWidth(2);
	hist->Draw("HIST");

	hist->SetTitle(name.c_str());
	hist->GetXaxis()->SetTitle(Xaxis.c_str());
	hist->GetYaxis()->SetTitle(Yaxis.c_str());

	auto h_shade = (TH1F*)hist->Clone("h_shade");

	h_shade->SetFillColorAlpha(kBlue, 0.35);
	h_shade->SetFillStyle(1001);
	h_shade->Draw("HIST SAME");
}
