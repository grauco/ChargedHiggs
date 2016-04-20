#include "interface/AnalysisBase.hpp"
#include <iostream>

//#define VERBOSE 2

void AnalysisBase::Book(string name, string title, int nBins,double xmin,double xmax)
{
#ifdef VERBOSE
    if(VERBOSE>0)Log(__FUNCTION__,"DEBUG","Booking histo "+name);
#endif
    output_ -> Book(name,title,nBins,xmin,xmax);
}

void AnalysisBase::Book2D(string name, string title, int nBins,double xmin,double xmax,int nBins2,double ymin,double ymax)
{
    output_ -> Book2D(name,title,nBins,xmin,xmax,nBins2,ymin,ymax);
}

void AnalysisBase::Book(string name, string title, int nBins,double *xbound)
{
    output_ -> Book(name,title,nBins,xbound);
}


void AnalysisBase::Fill(string name,string syst, double value, double weight){
    output_ -> Fill(name,syst,value,weight);
}

void AnalysisBase::Fill2D(string name,string syst, double valueX,double valueY, double weight){
    output_ -> Fill2D(name,syst,valueX,valueY,weight);
}

TH1D* AnalysisBase::GetHisto(string name,string systname)
{
    return output_ -> Get(name,systname);	
}

TH2D* AnalysisBase::GetHisto2D(string name,string systname)
{
    return output_ -> Get2D(name,systname);	
}

string AnalysisBase::GetLabel(Event *e){

    // remember if just done
    //static int lastRun = -1;
    //static string label = "";
    string label = "";

    //if (lastRun == e->runNum() ) 
    //	return label;

    label = "Other";

    if (e->IsRealData()) label = "Data";
    else{
        for (string& s:  AllLabel() )
        {
            if (e-> GetWeight() -> GetMC() . find(s) != string::npos ) {
                label = s; 
                break;
            }
        }
    } // end else (MC)

    #ifdef VERBOSE
    if (VERBOSE>1) Log(__FUNCTION__,"DEBUG","mc is '" + e->GetWeight()->GetMC() +"' and label is '"+ label +"'");
    #endif
    return label;
}

//#include "interface/Logger.hpp"
//void AnalysisBase::Log(const string& function, const string& level, const string& message){ Logger::getInstance().Log(this,function,level,message ); }

void AnalysisBase::SetCuts(Event *e)
{
    for (auto& l : e->leps_) SetLeptonCuts(l);
    for (auto& p : e->phos_) SetPhotonCuts(p);
    for (auto& t : e->taus_) SetTauCuts(t);
    for (auto& j : e->jets_) SetJetCuts(j);
    for (auto& g : e->genparticles_) SetGenCuts(g);
    return;
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4 
