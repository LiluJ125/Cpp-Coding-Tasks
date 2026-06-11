void shadeHistogram() {
   // Create and fill a dummy histogram
   auto h1 = new TH1F("h1", "Shaded Area Under Histogram;X;Y", 100, -5, 5);
   h1->FillRandom("gaus", 5000);
   
   // Draw the original histogram as a standard line
   h1->SetLineColor(kBlue);
   h1->SetLineWidth(2);
   h1->Draw("HIST");

   // Clone the histogram to create the shaded area
   auto h_shade = (TH1F*)h1->Clone("h_shade");

 /*  // Define the region to shade (e.g., from x = 2 to the end)
   int startBin = h1->FindFixBin(2.0);
   int endBin = h1->GetNbinsX();

    // Zero out the bins outside the shading region
   for (int i = 1; i < startBin; ++i) {
      h_shade->SetBinContent(i, 0);
   }
*/
   // Set the fill attributes for the shaded section
   h_shade->SetFillColorAlpha(kRed, 0.35); // Semi-transparent red
   h_shade->SetFillStyle(1001);          // Solid fill

   // Draw the shaded copy on top of the original
   h_shade->Draw("HIST SAME");
}
