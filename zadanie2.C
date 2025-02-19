#include <iostream>
#include <fstream>
#include <string>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <cmath>  

using namespace std;

class MySignal {
public:
    Float_t amplitude;  
    Float_t T0;         
    Float_t charge;     
    Float_t TOT;        

    MySignal() : amplitude(0), T0(0), charge(0), TOT(0) {}
    ClassDef(MySignal, 1);  
};

void zadanie2() {

    const string& file = "wave_0.dat";
    const Int_t maxEvents = 5020;
    const Int_t window = 1024;
    const Double_t adc2mV = 1 / 4.096;
    const Double_t thresholdOffset = 10.0;  
    const Int_t integrationWindow = 400;  

    ifstream input(file, ios::binary);
    if (!input) {
        cout << "File not open" << endl;
        return;
    }

    cout << "File with data is open" << endl;

    TFile* outputFile = new TFile("output.root", "RECREATE");
    TTree* tree = new TTree("tree", "Signal Data");

    MySignal signal;
    tree->Branch("signal", &signal);

    Int_t n = 0;
    Float_t data;
    while (input.read(reinterpret_cast<char*>(&data), sizeof(data)) && n < maxEvents) {
        
        Double_t base = 0;

        for (Int_t i = 0; i < 50; i++) {

            base = base + data * adc2mV;
            input.read(reinterpret_cast<char*>(&data), sizeof(data));

        }
        base = base/50.0;

        Double_t threshold = base - thresholdOffset;
        Double_t maxAmp = 1000;  
        Double_t T0 = -1;     
        Double_t TOT = 0;     
        Bool_t aboveThreshold = false;

        for (Int_t i = 0; i < window; i++) {

            input.read(reinterpret_cast<char*>(&data), sizeof(data));
            Double_t mV = data * adc2mV;  

            if (mV < threshold && mV < maxAmp) {
                maxAmp = mV;
            }

            if (mV < threshold && T0 < 0) {
                T0 = i;
            }

            if (mV < threshold) {
                aboveThreshold = true;
                TOT++;
            } else if (aboveThreshold) {
                break;  
            }
        }

        Double_t sum = 0;
        if (TOT < integrationWindow && T0 >= 0) {
            input.clear();
            input.seekg(n * window * sizeof(data) + T0 * sizeof(data), ios::beg);  

            for (Int_t i = 0; i < TOT; i++) {
                input.read(reinterpret_cast<char*>(&data), sizeof(data));
                Double_t mV = data * adc2mV;  
                sum = sum + base - mV;  
            }
        } else {
            input.clear();
            input.seekg(n * window * sizeof(data) + T0 * sizeof(data), ios::beg);  

            for (Int_t i = 0; i < integrationWindow; i++) {
                input.read(reinterpret_cast<char*>(&data), sizeof(data));
                Double_t mV = data * adc2mV;  
                sum = sum + base - mV;  
            }
        }

        signal.amplitude = base - maxAmp;  
        signal.T0 = T0;
        signal.charge = sum;
        signal.TOT = TOT;

        tree->Fill();
        n++;
    }

    input.close();
    outputFile->Write();
    outputFile->Close();

    TFile* inputFile = new TFile("output.root", "READ");
    TTree* inputTree = (TTree*)inputFile->Get("tree");

    TH1F* hT0 = new TH1F("hT0", "Time T0;time [ns];Counts", 100, 0, window);
    TH1F* hCharge = new TH1F("hCharge", "Charge;charge [mV*ns];Counts", 100, 0, window); 
    TH1F* hAmplitude = new TH1F("hAmplitude", "Amplitude;amplitude [mV];Counts", 100, 0, window);  
    TH1F* hTOT = new TH1F("hTOT", "Time Over Threshold;time [ns];Counts", 100, 0, window);
    TH2F* hTOTVsT0 = new TH2F("hTOTVsT0", "TOT vs T0;time [ns];time [ns]", 100, 0, window, 100, 0, 600);
    TH2F* hAmplitudeVsCharge = new TH2F("hAmplitudeVsCharge", "Amplitude vs Charge;charge [mV*ns];amplitude [mV]", 100, 0, 1000, 100, 0, 500);
    TH2F* hChargeVsT0 = new TH2F("hChargeVsT0", "Charge vs T0;time [ns];charge [mV*ns]", 100, 0, window, 100, 0, 1000);
    TH2F* hChargeVsTOT = new TH2F("hChargeVsTOT", "Charge vs TOT;time [ns];charge [mV*ns]", 100, 0, window, 100, 0, 1000);
    TH2F* hAmplitudeVsTOT = new TH2F("hAmplitudeVsTOT", "Amplitude vs TOT;time [ns];charge [mV]", 100, 0, window, 100, 0, 1000);
    
    inputTree->Draw("T0>>hT0");
    inputTree->Draw("charge>>hCharge");
    inputTree->Draw("amplitude>>hAmplitude");
    inputTree->Draw("TOT>>hTOT");
    inputTree->Draw("TOT:T0>>hTOTVsT0");
    inputTree->Draw("amplitude:charge>>hAmplitudeVsCharge");
    inputTree->Draw("charge:T0>>hChargeVsT0");
    inputTree->Draw("charge:TOT>>hChargeVsTOT");
    inputTree->Draw("amplitude:TOT>>hAmplitudeVsTOT");

    TCanvas* c1 = new TCanvas("c1", "Canvas", 1000, 600);
    c1->Divide(3, 3);
    c1->cd(1); hT0->Draw();
    c1->cd(2); hCharge->Draw();
    c1->cd(3); hAmplitude->Draw();
    c1->cd(4); hTOT->Draw();
    c1->cd(5); hTOTVsT0->Draw("COLZ");
    c1->cd(6); hAmplitudeVsCharge->Draw("COLZ");
    c1->cd(7); hChargeVsT0->Draw("COLZ");
    c1->cd(8); hChargeVsTOT->Draw("COLZ");
    c1->cd(9); hAmplitudeVsTOT->Draw("COLZ");

    c1->WaitPrimitive();

    c1->SaveAs("histograms.png");

    inputFile->Close();
}
