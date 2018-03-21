#include "TFile.h"
#include "TTree.h"
#include "TTreeFormula.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <random>
#include <algorithm>

class UnpackedTree
{
    public:
        TFile* outputFile_;
        TTree* tree_;
        
        
        static constexpr int maxEntries = 25;
        
        unsigned int jetorigin_isPU;
        unsigned int jetorigin_isUndefined;
        
        float jetorigin_displacement;
        float jetorigin_decay_angle;
        
        unsigned int jetorigin_isB;
        unsigned int jetorigin_isBB;
        unsigned int jetorigin_isGBB;
        unsigned int jetorigin_isLeptonic_B;
        unsigned int jetorigin_isLeptonic_C;
        unsigned int jetorigin_isC;
        unsigned int jetorigin_isCC;
        unsigned int jetorigin_isGCC;
        unsigned int jetorigin_isS;
        unsigned int jetorigin_isUD;
        unsigned int jetorigin_isG;
        unsigned int jetorigin_fromLLP;
        
        float global_pt;
        float global_eta;
        
        unsigned int ncpf;
        float cpf_trackEtaRel[maxEntries];
        float cpf_trackPtRel[maxEntries];
        float cpf_trackPPar[maxEntries];
        float cpf_trackDeltaR[maxEntries];
        float cpf_trackPtRatio[maxEntries];
        float cpf_trackPParRatio[maxEntries];
        float cpf_trackSip2dVal[maxEntries];
        float cpf_trackSip2dSig[maxEntries];
        float cpf_trackSip3dVal[maxEntries];
        float cpf_trackSip3dSig[maxEntries];
        float cpf_trackJetDistVal[maxEntries];
        float cpf_trackJetDistSig[maxEntries];
        float cpf_ptrel[maxEntries];
        float cpf_drminsv[maxEntries];
        float cpf_vertex_association[maxEntries];
        float cpf_puppi_weight[maxEntries];
        float cpf_track_chi2[maxEntries];
        float cpf_track_quality[maxEntries];
        float cpf_jetmassdroprel[maxEntries];
        float cpf_relIso01[maxEntries];
        
        float csv_trackSumJetEtRatio;
        float csv_trackSumJetDeltaR;
        float csv_vertexCategory;
        float csv_trackSip2dValAboveCharm;
        float csv_trackSip2dSigAboveCharm;
        float csv_trackSip3dValAboveCharm;
        float csv_trackSip3dSigAboveCharm;
        float csv_jetNSelectedTracks;
        float csv_jetNTracksEtaRel;
        
        unsigned int nnpf;
        float npf_ptrel[maxEntries];
        float npf_deltaR[maxEntries];
        float npf_isGamma[maxEntries];
        float npf_hcal_fraction[maxEntries];
        float npf_drminsv[maxEntries];
        float npf_puppi_weight[maxEntries];
        float npf_jetmassdroprel[maxEntries];
        float npf_relIso01[maxEntries];
        
        unsigned int nsv;
        float sv_pt[maxEntries];
        float sv_deltaR[maxEntries];
        float sv_ntracks[maxEntries];
        float sv_chi2[maxEntries];
        float sv_normchi2[maxEntries];
        float sv_dxy[maxEntries];
        float sv_dxysig[maxEntries];
        float sv_d3d[maxEntries];
        float sv_d3dsig[maxEntries];
        float sv_costhetasvpv[maxEntries];
        float sv_enratio[maxEntries];
        
    public:
        UnpackedTree(const std::string& fileName):
            outputFile_(new TFile(fileName.c_str(),"RECREATE")),
            tree_(new TTree("jets","jets"))
        {
            tree_->SetDirectory(outputFile_); 

            tree_->Branch("jetorigin_isPU",&jetorigin_isPU,"jetorigin_isPU/I");
            tree_->Branch("jetorigin_isUndefined",&jetorigin_isUndefined,"jetorigin_isUndefined/I");
            
            tree_->Branch("jetorigin_displacement",&jetorigin_displacement,"jetorigin_displacement/F");
            tree_->Branch("jetorigin_decay_angle",&jetorigin_decay_angle,"jetorigin_decay_angle/F");
            
            tree_->Branch("jetorigin_isB",&jetorigin_isB,"jetorigin_isB/I");
            tree_->Branch("jetorigin_isBB",&jetorigin_isBB,"jetorigin_isBB/I");
            tree_->Branch("jetorigin_isGBB",&jetorigin_isGBB,"jetorigin_isGBB/I");
            tree_->Branch("jetorigin_isLeptonic_B",&jetorigin_isLeptonic_B,"jetorigin_isLeptonic_B/I");
            tree_->Branch("jetorigin_isLeptonic_C",&jetorigin_isLeptonic_C,"jetorigin_isLeptonic_C/I");
            tree_->Branch("jetorigin_isC",&jetorigin_isC,"jetorigin_isC/I");
            tree_->Branch("jetorigin_isCC",&jetorigin_isCC,"jetorigin_isCC/I");
            tree_->Branch("jetorigin_isGCC",&jetorigin_isGCC,"jetorigin_isGCC/I");
            tree_->Branch("jetorigin_isS",&jetorigin_isS,"jetorigin_isS/I");
            tree_->Branch("jetorigin_isUD",&jetorigin_isUD,"jetorigin_isUD/I");
            tree_->Branch("jetorigin_isG",&jetorigin_isG,"jetorigin_isG/I");
            tree_->Branch("jetorigin_fromLLP",&jetorigin_fromLLP,"jetorigin_fromLLP/I");
            
            tree_->Branch("global_pt",&global_pt);
            tree_->Branch("global_eta",&global_eta);

            tree_->Branch("ncpf",&ncpf,"ncpf/I");
            tree_->Branch("cpf_trackEtaRel",&cpf_trackEtaRel,"cpf_trackEtaRel[ncpf]/F");
            tree_->Branch("cpf_trackPtRel",&cpf_trackPtRel,"cpf_trackPtRel[ncpf]/F");
            tree_->Branch("cpf_trackPPar",&cpf_trackPPar,"cpf_trackPPar[ncpf]/F");
            tree_->Branch("cpf_trackDeltaR",&cpf_trackDeltaR,"cpf_trackDeltaR[ncpf]/F");
            tree_->Branch("cpf_trackPtRatio",&cpf_trackPtRatio,"cpf_trackPtRatio[ncpf]/F");
            tree_->Branch("cpf_trackPParRatio",&cpf_trackPParRatio,"cpf_trackPParRatio[ncpf]/F");
            tree_->Branch("cpf_trackSip2dVal",&cpf_trackSip2dVal,"cpf_trackSip2dVal[ncpf]/F");
            tree_->Branch("cpf_trackSip2dSig",&cpf_trackSip2dSig,"cpf_trackSip2dSig[ncpf]/F");
            tree_->Branch("cpf_trackSip3dVal",&cpf_trackSip3dVal,"cpf_trackSip3dVal[ncpf]/F");
            tree_->Branch("cpf_trackSip3dSig",&cpf_trackSip3dSig,"cpf_trackSip3dSig[ncpf]/F");
            tree_->Branch("cpf_trackJetDistVal",&cpf_trackJetDistVal,"cpf_trackJetDistVal[ncpf]/F");
            tree_->Branch("cpf_trackJetDistSig",&cpf_trackJetDistSig,"cpf_trackJetDistSig[ncpf]/F");
            tree_->Branch("cpf_ptrel",&cpf_ptrel,"cpf_ptrel[ncpf]/F");
            tree_->Branch("cpf_drminsv",&cpf_drminsv,"cpf_drminsv[ncpf]/F");
            tree_->Branch("cpf_vertex_association",&cpf_vertex_association,"cpf_vertex_association[ncpf]/F");
            tree_->Branch("cpf_puppi_weight",&cpf_puppi_weight,"cpf_puppi_weight[ncpf]/F");
            tree_->Branch("cpf_track_chi2",&cpf_track_chi2,"cpf_track_chi2[ncpf]/F");
            tree_->Branch("cpf_track_quality",&cpf_track_quality,"cpf_track_quality[ncpf]/F");
            tree_->Branch("cpf_jetmassdroprel",&cpf_jetmassdroprel,"cpf_jetmassdroprel[ncpf]/F");
            tree_->Branch("cpf_relIso01",&cpf_relIso01,"cpf_relIso01[ncpf]/F");
            
            tree_->Branch("csv_trackSumJetEtRatio",&csv_trackSumJetEtRatio,"csv_trackSumJetEtRatio/F");
            tree_->Branch("csv_trackSumJetDeltaR",&csv_trackSumJetDeltaR,"csv_trackSumJetDeltaR/F");
            tree_->Branch("csv_vertexCategory",&csv_vertexCategory,"csv_vertexCategory/F");
            tree_->Branch("csv_trackSip2dValAboveCharm",&csv_trackSip2dValAboveCharm,"csv_trackSip2dValAboveCharm/F");
            tree_->Branch("csv_trackSip2dSigAboveCharm",&csv_trackSip2dSigAboveCharm,"csv_trackSip2dSigAboveCharm/F");
            tree_->Branch("csv_trackSip3dValAboveCharm",&csv_trackSip3dValAboveCharm,"csv_trackSip3dValAboveCharm/F");
            tree_->Branch("csv_trackSip3dSigAboveCharm",&csv_trackSip3dSigAboveCharm,"csv_trackSip3dSigAboveCharm/F");
            tree_->Branch("csv_jetNSelectedTracks",&csv_jetNSelectedTracks,"csv_jetNSelectedTracks/F");
            tree_->Branch("csv_jetNTracksEtaRel",&csv_jetNTracksEtaRel,"csv_jetNTracksEtaRel/F");

            tree_->Branch("nnpf",&nnpf,"nnpf/I");
            tree_->Branch("npf_ptrel",&npf_ptrel,"npf_ptrel[nnpf]/F");
            tree_->Branch("npf_deltaR",&npf_deltaR,"npf_deltaR[nnpf]/F");
            tree_->Branch("npf_isGamma",&npf_isGamma,"npf_isGamma[nnpf]/F");
            tree_->Branch("npf_hcal_fraction",&npf_hcal_fraction,"npf_hcal_fraction[nnpf]/F");
            tree_->Branch("npf_drminsv",&npf_drminsv,"npf_drminsv[nnpf]/F");
            tree_->Branch("npf_puppi_weight",&npf_puppi_weight,"npf_puppi_weight[nnpf]/F");
            tree_->Branch("npf_jetmassdroprel",&npf_jetmassdroprel,"npf_jetmassdroprel[nnpf]/F");
            tree_->Branch("npf_relIso01",&npf_relIso01,"npf_relIso01[nnpf]/F");

            tree_->Branch("nsv",&nsv,"nsv/I");
            tree_->Branch("sv_pt",&sv_pt,"sv_pt[nsv]/F");
            tree_->Branch("sv_deltaR",&sv_deltaR,"sv_deltaR[nsv]/F");
            tree_->Branch("sv_ntracks",&sv_ntracks,"sv_ntracks[nsv]/F");
            tree_->Branch("sv_chi2",&sv_chi2,"sv_chi2[nsv]/F");
            tree_->Branch("sv_normchi2",&sv_normchi2,"sv_normchi2[nsv]/F");
            tree_->Branch("sv_dxy",&sv_dxy,"sv_dxy[nsv]/F");
            tree_->Branch("sv_dxysig",&sv_dxysig,"sv_dxysig[nsv]/F");
            tree_->Branch("sv_d3d",&sv_d3d,"sv_d3d[nsv]/F");
            tree_->Branch("sv_d3dsig",&sv_d3dsig,"sv_d3dsig[nsv]/F");
            tree_->Branch("sv_costhetasvpv",&sv_costhetasvpv,"sv_costhetasvpv[nsv]/F");
            tree_->Branch("sv_enratio",&sv_enratio,"sv_enratio[nsv]/F");
        }
        
        //root does not behave properly
        UnpackedTree(UnpackedTree&&) = delete;
        UnpackedTree(const UnpackedTree&) = delete;
        
        ~UnpackedTree()
        {
            if (outputFile_)
            {
                delete outputFile_;
            }
            //Note: TTree is managed by TFile and gets deleted by ROOT when file is closed
        }
        
        
        void fill()
        {
            outputFile_->cd();
            tree_->SetDirectory(outputFile_);
            tree_->Fill();
        }
        
        void close()
        {
            outputFile_->cd();
            tree_->SetDirectory(outputFile_);
            tree_->Write();
            outputFile_->Close();
        }
};

class NanoXTree
{
    public:
        std::shared_ptr<TFile> file_;
        TTree* tree_;
        
        unsigned int ientry_;
        
        static constexpr int maxEntries = 500;
        
        unsigned int nJet;
        float Jet_eta[maxEntries];
        float Jet_pt[maxEntries];
        unsigned int Jet_jetId[maxEntries];
        unsigned int Jet_cleanmask[maxEntries];
        
        unsigned int njetorigin;
        float jetorigin_isPU[maxEntries];
        float jetorigin_isUndefined[maxEntries];
        
        float jetorigin_displacement[maxEntries];
        float jetorigin_decay_angle[maxEntries];
        
        float jetorigin_isB[maxEntries];
        float jetorigin_isBB[maxEntries];
        float jetorigin_isGBB[maxEntries];
        float jetorigin_isLeptonic_B[maxEntries];
        float jetorigin_isLeptonic_C[maxEntries];
        float jetorigin_isC[maxEntries];
        float jetorigin_isCC[maxEntries];
        float jetorigin_isGCC[maxEntries];
        float jetorigin_isS[maxEntries];
        float jetorigin_isUD[maxEntries];
        float jetorigin_isG[maxEntries];
        float jetorigin_fromLLP[maxEntries];
        
        unsigned int nglobal;
        float global_pt[maxEntries];
        float global_eta[maxEntries];
        
        unsigned int ncpflength;
        float cpflength_length[maxEntries];
        
        unsigned int ncpf[maxEntries];
        float cpf_trackEtaRel[maxEntries];
        float cpf_trackPtRel[maxEntries];
        float cpf_trackPPar[maxEntries];
        float cpf_trackDeltaR[maxEntries];
        float cpf_trackPtRatio[maxEntries];
        float cpf_trackPParRatio[maxEntries];
        float cpf_trackSip2dVal[maxEntries];
        float cpf_trackSip2dSig[maxEntries];
        float cpf_trackSip3dVal[maxEntries];
        float cpf_trackSip3dSig[maxEntries];
        float cpf_trackJetDistVal[maxEntries];
        float cpf_trackJetDistSig[maxEntries];
        float cpf_ptrel[maxEntries];
        float cpf_drminsv[maxEntries];
        float cpf_vertex_association[maxEntries];
        float cpf_puppi_weight[maxEntries];
        float cpf_track_chi2[maxEntries];
        float cpf_track_quality[maxEntries];
        float cpf_jetmassdroprel[maxEntries];
        float cpf_relIso01[maxEntries];
        
        unsigned int ncsv[maxEntries];
        float csv_trackSumJetEtRatio[maxEntries];
        float csv_trackSumJetDeltaR[maxEntries];
        float csv_vertexCategory[maxEntries];
        float csv_trackSip2dValAboveCharm[maxEntries];
        float csv_trackSip2dSigAboveCharm[maxEntries];
        float csv_trackSip3dValAboveCharm[maxEntries];
        float csv_trackSip3dSigAboveCharm[maxEntries];
        float csv_jetNSelectedTracks[maxEntries];
        float csv_jetNTracksEtaRel[maxEntries];
        
        unsigned int nnpflength;
        float npflength_length[maxEntries];
        
        unsigned int nnpf[maxEntries];
        float npf_ptrel[maxEntries];
        float npf_deltaR[maxEntries];
        float npf_isGamma[maxEntries];
        float npf_hcal_fraction[maxEntries];
        float npf_drminsv[maxEntries];
        float npf_puppi_weight[maxEntries];
        float npf_jetmassdroprel[maxEntries];
        float npf_relIso01[maxEntries];
        
        unsigned int nsvlength;
        float svlength_length[maxEntries];
        
        unsigned int nsv[maxEntries];
        float sv_pt[maxEntries];
        float sv_deltaR[maxEntries];
        float sv_ntracks[maxEntries];
        float sv_chi2[maxEntries];
        float sv_normchi2[maxEntries];
        float sv_dxy[maxEntries];
        float sv_dxysig[maxEntries];
        float sv_d3d[maxEntries];
        float sv_d3dsig[maxEntries];
        float sv_costhetasvpv[maxEntries];
        float sv_enratio[maxEntries];
        
        
        std::mt19937 randomGenerator_;
        std::uniform_real_distribution<> uniform_dist_;
        
    public:
        NanoXTree(TFile* file, TTree* tree):
            file_(file),
            tree_(tree),
            randomGenerator_(12345),
            uniform_dist_(0,1.)
        {
            tree_->SetBranchAddress("nJet",&nJet);
            tree_->SetBranchAddress("Jet_eta",&Jet_eta);
            tree_->SetBranchAddress("Jet_pt",&Jet_pt);
            tree_->SetBranchAddress("Jet_jetId",&Jet_jetId);
            tree_->SetBranchAddress("Jet_cleanmask",&Jet_cleanmask);
        
        
            tree_->SetBranchAddress("njetorigin",&njetorigin);
            
            tree_->SetBranchAddress("jetorigin_isPU",&jetorigin_isPU);
            tree_->SetBranchAddress("jetorigin_isUndefined",&jetorigin_isUndefined);
            
            tree_->SetBranchAddress("jetorigin_displacement",&jetorigin_displacement);
            tree_->SetBranchAddress("jetorigin_decay_angle",&jetorigin_decay_angle);
            
            tree_->SetBranchAddress("jetorigin_isB",&jetorigin_isB);
            tree_->SetBranchAddress("jetorigin_isBB",&jetorigin_isBB);
            tree_->SetBranchAddress("jetorigin_isGBB",&jetorigin_isGBB);
            tree_->SetBranchAddress("jetorigin_isLeptonic_B",&jetorigin_isLeptonic_B);
            tree_->SetBranchAddress("jetorigin_isLeptonic_C",&jetorigin_isLeptonic_C);
            tree_->SetBranchAddress("jetorigin_isC",&jetorigin_isC);
            tree_->SetBranchAddress("jetorigin_isCC",&jetorigin_isCC);
            tree_->SetBranchAddress("jetorigin_isGCC",&jetorigin_isGCC);
            tree_->SetBranchAddress("jetorigin_isS",&jetorigin_isS);
            tree_->SetBranchAddress("jetorigin_isUD",&jetorigin_isUD);
            tree_->SetBranchAddress("jetorigin_isG",&jetorigin_isG);
            tree_->SetBranchAddress("jetorigin_fromLLP",&jetorigin_fromLLP);
            
            tree_->SetBranchAddress("nglobal",&nglobal);
            tree_->SetBranchAddress("global_pt",&global_pt);
            tree_->SetBranchAddress("global_eta",&global_eta);
            
            
            tree_->SetBranchAddress("ncpflength",&ncpflength);
            tree_->SetBranchAddress("cpflength_length",&cpflength_length);
            
            tree_->SetBranchAddress("ncpf",&ncpf);
            tree_->SetBranchAddress("cpf_trackEtaRel",&cpf_trackEtaRel);
            tree_->SetBranchAddress("cpf_trackPtRel",&cpf_trackPtRel);
            tree_->SetBranchAddress("cpf_trackPPar",&cpf_trackPPar);
            tree_->SetBranchAddress("cpf_trackDeltaR",&cpf_trackDeltaR);
            tree_->SetBranchAddress("cpf_trackPtRatio",&cpf_trackPtRatio);
            tree_->SetBranchAddress("cpf_trackPParRatio",&cpf_trackPParRatio);
            tree_->SetBranchAddress("cpf_trackSip2dVal",&cpf_trackSip2dVal);
            tree_->SetBranchAddress("cpf_trackSip2dSig",&cpf_trackSip2dSig);
            tree_->SetBranchAddress("cpf_trackSip3dVal",&cpf_trackSip3dVal);
            tree_->SetBranchAddress("cpf_trackSip3dSig",&cpf_trackSip3dSig);
            tree_->SetBranchAddress("cpf_trackJetDistVal",&cpf_trackJetDistVal);
            tree_->SetBranchAddress("cpf_trackJetDistSig",&cpf_trackJetDistSig);
            tree_->SetBranchAddress("cpf_ptrel",&cpf_ptrel);
            tree_->SetBranchAddress("cpf_drminsv",&cpf_drminsv);
            tree_->SetBranchAddress("cpf_vertex_association",&cpf_vertex_association);
            tree_->SetBranchAddress("cpf_puppi_weight",&cpf_puppi_weight);
            tree_->SetBranchAddress("cpf_track_chi2",&cpf_track_chi2);
            tree_->SetBranchAddress("cpf_track_quality",&cpf_track_quality);
            tree_->SetBranchAddress("cpf_jetmassdroprel",&cpf_jetmassdroprel);
            tree_->SetBranchAddress("cpf_relIso01",&cpf_relIso01);
            
            tree_->SetBranchAddress("ncsv",&ncsv);
            tree_->SetBranchAddress("csv_trackSumJetEtRatio",&csv_trackSumJetEtRatio);
            tree_->SetBranchAddress("csv_trackSumJetDeltaR",&csv_trackSumJetDeltaR);
            tree_->SetBranchAddress("csv_vertexCategory",&csv_vertexCategory);
            tree_->SetBranchAddress("csv_trackSip2dValAboveCharm",&csv_trackSip2dValAboveCharm);
            tree_->SetBranchAddress("csv_trackSip2dSigAboveCharm",&csv_trackSip2dSigAboveCharm);
            tree_->SetBranchAddress("csv_trackSip3dValAboveCharm",&csv_trackSip3dValAboveCharm);
            tree_->SetBranchAddress("csv_trackSip3dSigAboveCharm",&csv_trackSip3dSigAboveCharm);
            tree_->SetBranchAddress("csv_jetNSelectedTracks",&csv_jetNSelectedTracks);
            tree_->SetBranchAddress("csv_jetNTracksEtaRel",&csv_jetNTracksEtaRel);
           
            tree_->SetBranchAddress("nnpflength",&nnpflength);
            tree_->SetBranchAddress("npflength_length",&npflength_length);
            
            tree_->SetBranchAddress("nnpf",&nnpf);
            tree_->SetBranchAddress("npf_ptrel",&npf_ptrel);
            tree_->SetBranchAddress("npf_deltaR",&npf_deltaR);
            tree_->SetBranchAddress("npf_isGamma",&npf_isGamma);
            tree_->SetBranchAddress("npf_hcal_fraction",&npf_hcal_fraction);
            tree_->SetBranchAddress("npf_drminsv",&npf_drminsv);
            tree_->SetBranchAddress("npf_puppi_weight",&npf_puppi_weight);
            tree_->SetBranchAddress("npf_jetmassdroprel",&npf_jetmassdroprel);
            tree_->SetBranchAddress("npf_relIso01",&npf_relIso01);
            
            tree_->SetBranchAddress("nsvlength",&nsvlength);
            tree_->SetBranchAddress("svlength_length",&svlength_length);
            
            tree_->SetBranchAddress("nsv",&nsv);
            tree_->SetBranchAddress("sv_pt",&sv_pt);
            tree_->SetBranchAddress("sv_deltaR",&sv_deltaR);
            tree_->SetBranchAddress("sv_ntracks",&sv_ntracks);
            tree_->SetBranchAddress("sv_chi2",&sv_chi2);
            tree_->SetBranchAddress("sv_normchi2",&sv_normchi2);
            tree_->SetBranchAddress("sv_dxy",&sv_dxy);
            tree_->SetBranchAddress("sv_dxysig",&sv_dxysig);
            tree_->SetBranchAddress("sv_d3d",&sv_d3d);
            tree_->SetBranchAddress("sv_d3dsig",&sv_d3dsig);
            tree_->SetBranchAddress("sv_costhetasvpv",&sv_costhetasvpv);
            tree_->SetBranchAddress("sv_enratio",&sv_enratio);
            
            getEvent(0,true);
        }
        
        //this class does not play well with memory -> prevent funny usage
        NanoXTree(NanoXTree&&) = delete;
        NanoXTree(const NanoXTree&) = delete;
        
        ~NanoXTree()
        {
            //file_->Close();
        }

        inline unsigned int entries() const
        {
            return tree_->GetEntries();
        }
        
        inline unsigned int entry() const
        {
            return ientry_;
        }
        
        bool getEvent(unsigned int entry, bool force=false)
        {
            if (force or entry!=ientry_)
            {
                tree_->GetEntry(entry);
                ientry_ = entry;
                return true;
            }
            if (entry>=entries())
            {
                return false;
            }
            return true;
        }
        
        bool nextEvent()
        {
            return getEvent(ientry_+1);
        }
       
        inline int njets()
        {
            return nJet;
        }
        
        bool isSelected(unsigned int jet)
        {
            
            //nJet should be lower than e.g. njetorigin since pT selection on Jet's are applied
            if (jet>=nJet)
            {
                return false;
            }
            
            //just a sanity check
            if (std::fabs(Jet_eta[jet]/global_eta[jet]-1)>0.01)
            {
                std::cout<<"Encountered mismatch between standard nanoaod jets and xtag info"<<std::endl;
                return false;
            }
            
            if (njetorigin<jet)
            {
                std::cout<<"Not enough jets to unpack"<<std::endl;
                return false;
            }
            
            
            //jetId is 2**0*loose_id+2**1*tight_id; so jetId>0 is passed by all loose jets
            if (Jet_jetId[jet]==0 or Jet_cleanmask[jet]==0)
            {
                return false;
            }
            
            if (Jet_pt[jet]<20. or std::fabs(Jet_eta[jet])>2.4)
            {
                return false;
            }
            
            if (jetorigin_isPU[jet]>0.5 or jetorigin_isUndefined[jet]>0.5)
            {
                return false;
            }
            
            if (jetorigin_fromLLP[jet]<0.5)
            {
                //keep only 5% of all gluon jets
                if (jetorigin_isG[jet]>0.5)
                {
                    if (uniform_dist_(randomGenerator_)<0.95)
                    {
                        return false;
                    }
                }
                
                //keep only 30% of all light jets
                if (jetorigin_isUD[jet]>0.5 or jetorigin_isS[jet]>0.5)
                {
                    if (uniform_dist_(randomGenerator_)<0.7)
                    {
                        return false;
                    }
                }
            }
            
            return true;
        }
        
        int getJetClass(unsigned int jet)
        {
            if (jetorigin_fromLLP[jet]<0.5)
            {
                if  (jetorigin_isB[jet]>0.5) return 0;
                if  (jetorigin_isBB[jet]>0.5) return 1;
                if  (jetorigin_isGBB[jet]>0.5) return 2;
                if  (jetorigin_isLeptonic_B[jet]>0.5) return 3;
                if  (jetorigin_isLeptonic_C[jet]>0.5) return 4;
                if  (jetorigin_isC[jet]>0.5) return 5;
                if  (jetorigin_isCC[jet]>0.5) return 6;
                if  (jetorigin_isGCC[jet]>0.5) return 7;
                if  (jetorigin_isS[jet]>0.5) return 8;
                if  (jetorigin_isUD[jet]>0.5) return 9;
                if  (jetorigin_isG[jet]>0.5) return 10;
            }
            else
            {
                return 11;
            }
            return -1;
        }
        
        bool unpackJet(
            unsigned int jet,
            UnpackedTree& unpackedTree
        )
        {
            //tree_->GetEntry(entry);

            if (njetorigin!=nglobal or njetorigin!=ncpflength or njetorigin!=nnpflength or njetorigin!=nsvlength)
            {
                std::cout<<"Encountered weird event with unclear numbers of jets"<<std::endl;
                std::cout<<"\tnjetorigin = "<<njetorigin<<std::endl;
                std::cout<<"\tnglobal = "<<nglobal<<std::endl;
                std::cout<<"\tncpflength = "<<ncpflength<<std::endl;
                std::cout<<"\tnnpflength = "<<nnpflength<<std::endl;
                std::cout<<"\tnsvlength = "<<nsvlength<<std::endl;

                return false;
            }
            
            unpackedTree.jetorigin_isPU = jetorigin_isPU[jet];
            unpackedTree.jetorigin_isUndefined = jetorigin_isUndefined[jet];
            
            unpackedTree.jetorigin_displacement = jetorigin_displacement[jet];
            unpackedTree.jetorigin_decay_angle = jetorigin_decay_angle[jet];
            
            //make DJ and LLP categories exclusive
            unpackedTree.jetorigin_isB = jetorigin_isB[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isBB = jetorigin_isBB[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isGBB = jetorigin_isGBB[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isLeptonic_B = jetorigin_isLeptonic_B[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isLeptonic_C = jetorigin_isLeptonic_C[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isC = jetorigin_isC[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isCC = jetorigin_isCC[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isGCC = jetorigin_isGCC[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isS = jetorigin_isS[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isUD = jetorigin_isUD[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_isG = jetorigin_isG[jet]>0.5 and jetorigin_fromLLP[jet]<0.5;
            unpackedTree.jetorigin_fromLLP = jetorigin_fromLLP[jet]>0.5;
            
            
            unpackedTree.global_pt = global_pt[jet];
            unpackedTree.global_eta = global_eta[jet];
            
            int cpf_offset = 0;
            for (size_t i = 0; i < jet; ++i)
            {
                cpf_offset += cpflength_length[i];
            }
            
            unpackedTree.ncpf = std::min<int>(25,cpflength_length[jet]);
            
            for (size_t i = 0; i < unpackedTree.ncpf; ++i)
            {
                unpackedTree.cpf_trackEtaRel[i] = cpf_trackEtaRel[cpf_offset+i];
                unpackedTree.cpf_trackPtRel[i] = cpf_trackPtRel[cpf_offset+i];
                unpackedTree.cpf_trackPPar[i] = cpf_trackPPar[cpf_offset+i];
                unpackedTree.cpf_trackDeltaR[i] = cpf_trackDeltaR[cpf_offset+i];
                unpackedTree.cpf_trackPtRatio[i] = cpf_trackPtRatio[cpf_offset+i];
                unpackedTree.cpf_trackPParRatio[i] = cpf_trackPParRatio[cpf_offset+i];
                unpackedTree.cpf_trackSip2dVal[i] = cpf_trackSip2dVal[cpf_offset+i];
                unpackedTree.cpf_trackSip2dSig[i] = cpf_trackSip2dSig[cpf_offset+i];
                unpackedTree.cpf_trackSip3dVal[i] = cpf_trackSip3dVal[cpf_offset+i];
                unpackedTree.cpf_trackSip3dSig[i] = cpf_trackSip3dSig[cpf_offset+i];
                unpackedTree.cpf_trackJetDistVal[i] = cpf_trackJetDistVal[cpf_offset+i];
                unpackedTree.cpf_trackJetDistSig[i] = cpf_trackJetDistSig[cpf_offset+i];
                unpackedTree.cpf_ptrel[i] = cpf_ptrel[cpf_offset+i];
                unpackedTree.cpf_drminsv[i] = cpf_drminsv[cpf_offset+i];
                unpackedTree.cpf_vertex_association[i] = cpf_vertex_association[cpf_offset+i];
                unpackedTree.cpf_puppi_weight[i] = cpf_puppi_weight[cpf_offset+i];
                unpackedTree.cpf_track_chi2[i] = cpf_track_chi2[cpf_offset+i];
                unpackedTree.cpf_track_quality[i] = cpf_track_quality[cpf_offset+i];
                unpackedTree.cpf_jetmassdroprel[i] = cpf_jetmassdroprel[cpf_offset+i];
                unpackedTree.cpf_relIso01[i] = cpf_relIso01[cpf_offset+i];
            }
            
            unpackedTree.csv_trackSumJetEtRatio = csv_trackSumJetEtRatio[jet];
            
            unpackedTree.csv_trackSumJetDeltaR = csv_trackSumJetDeltaR[jet];
            unpackedTree.csv_vertexCategory = csv_vertexCategory[jet];
            unpackedTree.csv_trackSip2dValAboveCharm = csv_trackSip2dValAboveCharm[jet];
            unpackedTree.csv_trackSip2dSigAboveCharm = csv_trackSip2dSigAboveCharm[jet];
            unpackedTree.csv_trackSip3dValAboveCharm = csv_trackSip3dValAboveCharm[jet];
            unpackedTree.csv_trackSip3dSigAboveCharm = csv_trackSip3dSigAboveCharm[jet];
            unpackedTree.csv_jetNSelectedTracks = csv_jetNSelectedTracks[jet];
            unpackedTree.csv_jetNTracksEtaRel = csv_jetNTracksEtaRel[jet];
        
        
            int npf_offset = 0;
            for (size_t i = 0; i < jet; ++i)
            {
                npf_offset += npflength_length[i];
            }
            
            unpackedTree.nnpf = std::min<int>(25,npflength_length[jet]);
            for (size_t i = 0; i < unpackedTree.nnpf; ++i)
            {
                unpackedTree.npf_ptrel[i] = npf_ptrel[npf_offset+i];
                unpackedTree.npf_deltaR[i] = npf_deltaR[npf_offset+i];
                unpackedTree.npf_isGamma[i] = npf_isGamma[npf_offset+i];
                unpackedTree.npf_hcal_fraction[i] = npf_hcal_fraction[npf_offset+i];
                unpackedTree.npf_drminsv[i] = npf_drminsv[npf_offset+i];
                unpackedTree.npf_puppi_weight[i] = npf_puppi_weight[npf_offset+i];
                unpackedTree.npf_jetmassdroprel[i] = npf_jetmassdroprel[npf_offset+i];
                unpackedTree.npf_relIso01[i] = npf_relIso01[npf_offset+i];
            }
            

            int sv_offset = 0;
            for (size_t i = 0; i < jet; ++i)
            {
                sv_offset += svlength_length[i];
            }
            
            unpackedTree.nsv = std::min<int>(4,svlength_length[jet]);
            for (size_t i = 0; i < unpackedTree.nsv; ++i)
            {
                unpackedTree.sv_pt[i] = sv_pt[sv_offset+i];
                unpackedTree.sv_deltaR[i] = sv_deltaR[sv_offset+i];
                unpackedTree.sv_ntracks[i] = sv_ntracks[sv_offset+i];
                unpackedTree.sv_chi2[i] = sv_chi2[sv_offset+i];
                unpackedTree.sv_normchi2[i] = sv_normchi2[sv_offset+i];
                unpackedTree.sv_dxy[i] = sv_dxy[sv_offset+i];
                unpackedTree.sv_dxysig[i] = sv_dxysig[sv_offset+i];
                unpackedTree.sv_d3d[i] = sv_d3d[sv_offset+i];
                unpackedTree.sv_d3dsig[i] = sv_d3dsig[sv_offset+i];
                unpackedTree.sv_costhetasvpv[i] = sv_costhetasvpv[sv_offset+i];
                unpackedTree.sv_enratio[i] = sv_enratio[sv_offset+i];
            }
            
            unpackedTree.fill();
            return true;
        }
       
};



void printSyntax()
{
    std::cout<<"Syntax: "<<std::endl;
    std::cout<<"          unpackNanoX outputfile N infile [infile [infile ...]]"<<std::endl<<std::endl;
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main(int argc, char **argv)
{
    if (argc<4)
    {
        printSyntax();
        return 1;
    }
    int nOutputs = std::atoi(argv[2]);
    if (nOutputs==0 and strcmp(argv[2],"0")!=0)
    {
        std::cout<<"Error - cannot convert '"<<argv[2]<<"' to integer"<<std::endl;
        return 1;
    }
    else if (nOutputs<=0)
    {
        std::cout<<"Error - noutputs need to be positive but got '"<<argv[2]<<"'"<<std::endl;
        return 1;
    }
    
    std::vector<std::unique_ptr<NanoXTree>> trees;
    std::cout<<"Input files: "<<std::endl;
    
    std::vector<unsigned int> entries;
    unsigned int total_entries = 0;
    
    std::vector<std::string> inputFileNames;
    for (unsigned int iarg = 3; iarg<argc; ++iarg)
    {
        std::string s(argv[iarg]);
        if (ends_with(s,".root"))
        {
            inputFileNames.push_back(s);
        }
        else if(ends_with(s,".txt"))
        {
            std::ifstream input(s);
            for( std::string line; getline( input, line ); )
            {
                if (line.size()>0)
                {
                    inputFileNames.push_back(line);
                }
            }
        }
        else
        {
            std::cout<<"Cannot parse file '"<<s<<"'"<<std::endl;
            return 0;
        }
    }
    
    for (const auto& inputFileName: inputFileNames)
    {
        //std::cout<<"   "<<argv[iarg]<<", nEvents="<<;
        TFile* file = TFile::Open(inputFileName.c_str());
        if (not file)
        {
            std::cout<<"File '"<<inputFileName<<"' cannot be read"<<std::endl;
            continue;
        }
        
        TTree* tree = dynamic_cast<TTree*>(file->Get("Events"));
        
        if (not tree)
        {
            std::cout<<"Tree in file '"<<inputFileName<<"' cannot be read"<<std::endl;
            continue;
        }
        int nEvents = tree->GetEntries();
        std::cout<<"   "<<inputFileName<<", nEvents="<<nEvents<<std::endl;
        entries.push_back(nEvents);
        total_entries += nEvents;
        trees.emplace_back(std::make_unique<NanoXTree>(file,tree));
    }
    
    std::vector<std::unique_ptr<UnpackedTree>> unpackedTrees;
    std::vector<std::vector<int>> eventsPerClassPerFile(12,std::vector<int>(nOutputs,0));

    for (unsigned int i = 0; i < nOutputs; ++i)
    {
        unpackedTrees.emplace_back(std::make_unique<UnpackedTree>(
            std::string(argv[1])+"_"+std::to_string(i+1)+".root"
        ));
    }
    
    
    std::vector<unsigned int> readEvents(entries.size(),0);
    for (unsigned int ientry = 0; ientry<total_entries; ++ientry)
    {
        if (ientry%10000==0)
        {
            std::cout<<"Processing ... "<<100.*ientry/total_entries<<std::endl;
        }
    
        //choose input file pseudo-randomly
        unsigned int hash = ((ientry >> 16) ^ ientry) * 0x45d9f3b;
        hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
        hash = (hash >> 16) ^ hash;
        hash = (hash+hash/total_entries)%total_entries;
        
        unsigned int sum_entries = 0;
        unsigned int ifile = 0;
        for (;ifile<entries.size(); ++ifile)
        {
            sum_entries += entries[ifile];
            if (hash<sum_entries) break;
        }
    
        //ensure that file is not yet at last event; otherwise move to next input file
        while (trees[ifile]->entry()>=entries[ifile])
        {
            ifile=(ifile+1)%trees.size();
        }
        
        //std::cout<<ifile<<": "<<trees[ifile]->entry()<<"/"<<entries[ifile]<<std::endl;
        trees[ifile]->nextEvent();
        readEvents[ifile]+=1;
        
        for (size_t j = 0; j <trees[ifile]->njets(); ++j)
        {
            if (trees[ifile]->isSelected(j))
            {
                int jet_class = trees[ifile]->getJetClass(j);
                if (jet_class>=0 and jet_class<eventsPerClassPerFile.size())
                {
                    unsigned int ofile = std::distance(
                        eventsPerClassPerFile[jet_class].begin(), 
                        std::min_element(
                            eventsPerClassPerFile[jet_class].begin(), 
                            eventsPerClassPerFile[jet_class].end()
                        )
                    );
                    //std::cout<<ofile<<std::endl;
                    eventsPerClassPerFile[jet_class][ofile]+=1;
                    trees[ifile]->unpackJet(j,*unpackedTrees[ofile]);
                }
            }
        }
    }
    
    for (size_t i = 0; i < entries.size(); ++i)
    {
        std::cout<<"infile "<<i<<": found = "<<entries[i]<<", read = "<<readEvents[i]<<std::endl;
    }
    
    for (size_t c = 0; c < eventsPerClassPerFile.size(); ++c)
    {
        std::cout<<"jet class "<<c<<": ";
        for (size_t i = 0; i < nOutputs; ++i)
        {
            std::cout<<eventsPerClassPerFile[c][i]<<", ";
        }
        std::cout<<std::endl;
    }
    
    
    /*
    for (unsigned int i = 0; i < trees.back().entries(); ++i)
    {
        if (i%1000==0)
        {
            std::cout<<"Processing ... "<<100.*i/trees.back().entries()<<std::endl;
        }
        for (size_t j = 0; j <trees.back().njets(i); ++j)
        {
            if (isSelected)
        
            int classIndex = trees.back().unpackJet(i,j,unpackedTrees.back());
            if (classIndex>0 and classIndex<=12)
            {
                eventsPerClassPerFile[classIndex-1]
            }
        }
    }
    */
    
    for (auto& unpackedTree: unpackedTrees)
    {
        unpackedTree->close();
    }
    
    return 0;
}
