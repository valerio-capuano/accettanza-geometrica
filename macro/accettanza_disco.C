#define N 1E7

void accettanza_disco()
    {
        TCanvas *c[6];                                                     
        Double_t D,R,r;                                                     
        cout<<"distanza dal rivelatore: ";                                  
        cin>>D;
        cout<<"raggio del rivelatore: ";
        cin>>R;
        cout<<"raggio della sorgente: ";
        cin>>r;
        Double_t rho,phi,theta,x_0,y_0,x,y,z;                               
        Double_t X,Y,a,err_a;                                               
        Int_t count=0;
        TH3D *htot=new TH3D("","",100,-1,1,100,-1,1,100,-1,1);            
        TH3D *hinc=new TH3D("","",100,-1,1,100,-1,1,100,-1,1);              
        TH2D *hsorgente=new TH2D("","sorgente",100,-r,r,100,-r,r);          
        TH2D *hrivelatore=new TH2D("","rivelatore",100,-R,R,100,-R,R);     
        TF1 *f_0=new TF1("f_0","x",0,r);                                    
        TF1 *f=new TF1("f","TMath::Sin(x)",0,TMath::Pi()/2.);               

        for(Int_t i=0;i<N;i++)
            {
                rho=f_0->GetRandom(0,r);                                   
                phi=gRandom->Uniform(0,2*TMath::Pi());
                x_0=rho*TMath::Cos(phi);
                y_0=rho*TMath::Sin(phi);
                hsorgente->Fill(x_0,y_0);

                phi=gRandom->Uniform(0,2*TMath::Pi());   
                theta=f->GetRandom(0,TMath::Pi()/2);                  
                x=TMath::Sin(theta)*TMath::Cos(phi);
                y=TMath::Sin(theta)*TMath::Sin(phi);
                z=TMath::Cos(theta);
                htot->Fill(x,y,z);

                X=x_0+D*TMath::Tan(theta)*TMath::Cos(phi);                  
                Y=y_0+D*TMath::Tan(theta)*TMath::Sin(phi);
                if(X*X+Y*Y<R*R)
                    {
                        count++;
                        hinc->Fill(x,y,z);
                        hrivelatore->Fill(X,Y);
                    }
            }

        a=count/(2*N);                                                      
        err_a=TMath::Sqrt(count)/(2*N);
        cout<<"accettanza: "<<a<<" pm " <<err_a<<endl;
        for(Int_t i=0;i<6;i++)
            {
                c[i]=new TCanvas("","",500,500);
            }
        c[0]->cd();
        htot->SetStats(0);
        htot->Draw();
        c[1]->cd();
        hinc->SetStats(0);
        hinc->Draw();
        c[2]->cd();
        hsorgente->SetStats(0);
        hsorgente->Draw("COLZ");
        c[3]->cd();
        hsorgente->SetStats(0);
        hsorgente->Draw("LEGO2Z");
        c[4]->cd();
        hrivelatore->Draw("COLZ");
        c[5]->cd();
        hrivelatore->SetStats(0);
        hrivelatore->Draw("LEGO2Z");
    }