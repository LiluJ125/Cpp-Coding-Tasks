void Hist_present(TH1F* hist, std::string name; std::string x_axis; std:: string y_axis) {

	hist->SetTitle("name; x_axis; y_axis");

	hist->SetLineColor(kBlue);
	hist->SetLineWidth(2);
	hist->Draw("HIST");

	auto h_shade = (TH1F*)hist->Clone("h_shade");

	h_shade->SetFillColorAlpha(kBlue, 0.35);
	h_shade->SetFillStyle(1001);
	h_shade->Draw("HIST SAME");
}
