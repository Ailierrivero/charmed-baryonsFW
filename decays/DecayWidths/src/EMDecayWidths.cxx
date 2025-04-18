// EMDecay Class includes
#ifndef EMDECAYWIDTHS_CXX
#define EMDECAYWIDTHS_CXX

#include "EMDecayWidths.h"
#include "WignerSymbols.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
//#include <complex>


EMDecayWidths::EMDecayWidths()
{
}

EMDecayWidths::~EMDecayWidths(){}

double EMDecayWidths::execute(double ma_val, double sa_val, double ja_val, double la_val, double sla_val, double lla_val, double lra_val,
			      double mb_val, 
			      double al_val, double ar_val,
			      double mcharm_val, double mupdown_val, double mstrange_val,
			      int baryon, int excMode, int prodDecay){
  // decay product masses
  MA = ma_val;
  MB = mb_val;  
  if(MA<MB) return 0.; //energy conservation
  // if(MA>3.100) return 0.; // this was cascade p-wave

  // quark masses
  mcharm = mcharm_val;
  mupdown = mupdown_val;
  mstrange = mstrange_val;

  // which baryon, mode, decay product
  baryonFlag = baryon;
  modeExcitation = excMode;
  decayProd  = prodDecay;

  // std::cout<< la_val <<"          MENSAJE GRANDE      !!!!!!!!!!!!!!     "<<excMode<<std::endl;   

  // define the light effective mass for the h.o.
  if (baryonFlag==1)                      mlight = mstrange;
  else if(baryonFlag==2 or baryonFlag==5) mlight = 0.5*(mupdown_val + mstrange);
  else if(baryonFlag==3 or baryonFlag==4) mlight = mupdown;

  bool isSwave  = false;
  bool isPwaveL = false;
  bool isPwaveR = false;
  bool isDwaveL = false;
  bool isDwaveR = false;
  bool isMixed  = false;

  // if(la_val==0)                             isSwave  = true;
  // if(la_val==1 && lla_val==1 && lra_val==0) isPwaveL = true;
  // if(la_val==1 && lla_val==0 && lra_val==1) isPwaveR = true;
  // if(la_val==2 && lla_val==2 && lra_val==0) isDwaveL = true;
  // if(la_val==2 && lla_val==0 && lra_val==2) isDwaveR = true;
  // if(la_val==2 && lla_val==1 && lra_val==1) isMixed  = true;

  double alpha_rho = 0.,alpha_lam = 0.;
  alpha_rho = ar_val; alpha_lam = al_val;

  double sb_val=0.; double jb_val=0.; double lb_val=0.;
  double slb_val=0.; double llb_val=0.; double lrb_val=0.;

  double mu_qu = (+1.) * ((2./3.) * std::sqrt(1./137.)/(2. * mupdown));
  double mu_qd = (-1.) * ((1./3.) * std::sqrt(1./137.)/(2. * mupdown));
  double mu_qs = (-1.) * ((1./3.) * std::sqrt(1./137.)/(2. * mstrange));
  double mu_qc = (+1.) * ((2./3.) * std::sqrt(1./137.)/(2. * mcharm));
  double mu_sum_u_s = 0.5*(mu_qu + mu_qs); double mu_dif_u_s = 0.5*(mu_qu - mu_qs);
  double mu_sum_d_s = 0.5*(mu_qd + mu_qs); double mu_dif_d_s = 0.5*(mu_qd - mu_qs);
  double mu_sum_u_d = 0.5*(mu_qu + mu_qd); double mu_dif_u_d = 0.5*(mu_qu - mu_qd);

  if(baryonFlag==1){// omegas (decayProd=10x represents the GS and decayProd=20x represents the P-wave)
    if(decayProd== 101)    {flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //Omega_-  ground
    else if(decayProd==102){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //Omega_-* ground
    else if(decayProd==201){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //Omega_-  2p1/2-lam
    else if(decayProd==202){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //Omega_-* 4p1/2-lam
    else if(decayProd==203){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //Omega_-  2p3/2-lam
    else if(decayProd==204){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //Omega_-* 4p3/2-lam
    else if(decayProd==205){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //Omega_-* 4p5/2-lam
    else if(decayProd==206){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //Omega_-  2p1/2-rho
    else if(decayProd==207){flav_q1=mu_qs;       flav_q2=mu_qs;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //Omega_-  2p3/2-rho    
  }else if(baryonFlag==2){// cascades prime 
    // decaying cascade +
    if(decayProd==101)     {flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==201){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //+  2p1/2-lam
    else if(decayProd==202){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //+  2p3/2-lam
    else if(decayProd==203){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  2p1/2-rho
    else if(decayProd==204){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  4p1/2-rho
    else if(decayProd==205){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  2p3/2-rho
    else if(decayProd==206){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  4p3/2-rho
    else if(decayProd==207){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.;   sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  4p5/2-rho

    // decaying cascade 0
    else if(decayProd==102){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;    sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==208){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0  2p1/2-lam
    else if(decayProd==209){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0  2p3/2-lam
    else if(decayProd==210){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  2p1/2-rho
    else if(decayProd==211){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p1/2-rho
    else if(decayProd==212){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  2p3/2-rho
    else if(decayProd==213){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p3/2-rho
    else if(decayProd==214){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.;   sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p5/2-rho

    // decay to cascade prime +
    else if(decayProd==103){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==104){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==215){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  2p1/2-lam
    else if(decayProd==216){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p1/2-lam
    else if(decayProd==217){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  2p3/2-lam
    else if(decayProd==218){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p3/2-lam
    else if(decayProd==219){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p5/2-lam 
    else if(decayProd==220){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //+  2p1/2-rho
    else if(decayProd==221){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //+  2p3/2-rho

    // decay to cascade prime 0
    else if(decayProd==105){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==106){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==222){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p1/2-lam
    else if(decayProd==223){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p1/2-lam  
    else if(decayProd==224){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p3/2-lam
    else if(decayProd==225){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p3/2-lam
    else if(decayProd==226){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p5/2-lam
    else if(decayProd==227){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p1/2-rho
    else if(decayProd==228){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p3/2-rho

  }else if(baryonFlag==3){// sigmas
    // decay to sigma++
    if(decayProd==101)     {flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //++  ground
    else if(decayProd==102){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //++  ground
    else if(decayProd==201){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //++  2p1/2-lam
    else if(decayProd==202){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //++  4p1/2-lam
    else if(decayProd==203){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //++  2p3/2-lam
    else if(decayProd==204){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //++  4p3/2-lam
    else if(decayProd==205){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //++  4p5/2-lam
    else if(decayProd==206){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //++  2p1/2-rho
    else if(decayProd==207){flav_q1=mu_qu;      flav_q2=mu_qu;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //++  2p3/2-rho
    
    //decay to sigma +
    else if(decayProd==103){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==104){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==208){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  2p1/2-lam
    else if(decayProd==209){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p1/2-lam
    else if(decayProd==210){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  2p3/2-lam
    else if(decayProd==211){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p3/2-lam
    else if(decayProd==212){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //+  4p5/2-lam 
    else if(decayProd==213){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //+  2p1/2-rho
    else if(decayProd==214){flav_q1=mu_sum_u_d;  flav_q2=mu_sum_u_d;  flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //+  2p3/2-rho 

    // decay to sigma 0
    else if(decayProd==105){flav_q1=mu_qd;      flav_q2=mu_qd;      flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==106){flav_q1=mu_qd;      flav_q2=mu_qd;      flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==215){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p1/2-lam
    else if(decayProd==216){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p1/2-lam
    else if(decayProd==217){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p3/2-lam
    else if(decayProd==218){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p3/2-lam
    else if(decayProd==219){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p5/2-lam
    else if(decayProd==220){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p1/2-rho
    else if(decayProd==221){flav_q1=mu_qd;      flav_q2=mu_qd;       flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p3/2-rho

    // decay to lambda +
    else if(decayProd==107){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;} //+  ground
    else if(decayProd==222){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //+  2p1/2-lam
    else if(decayProd==223){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //+  2p3/2-lam
    else if(decayProd==224){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  2p1/2-rho
    else if(decayProd==225){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  4p1/2-rho
    else if(decayProd==226){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  2p3/2-rho
    else if(decayProd==227){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //+  4p3/2-rho
    else if(decayProd==228){flav_q1=mu_dif_u_d;  flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //+  4p5/2-rho
    
  }else if(baryonFlag==4){// lambdas
    // decay to lambda 0
    if(decayProd==101)     {flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;} //0 ground
    else if(decayProd==201){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0 2p1/2-lam
    else if(decayProd==202){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0 2p3/2-lam
    else if(decayProd==203){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0 2p1/2-rho
    else if(decayProd==204){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0 4p1/2-rho
    else if(decayProd==205){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0 2p3/2-rho
    else if(decayProd==206){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0 4p3/2-rho
    else if(decayProd==207){flav_q1=+mu_sum_u_d; flav_q2=+mu_sum_u_d; flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0 4p5/2-rho

    // decay to sigma 0
    else if(decayProd==102){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;    sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0 ground
    else if(decayProd==103){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0 ground
    else if(decayProd==208){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0 2p1/2-lam
    else if(decayProd==209){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0 4p1/2-lam
    else if(decayProd==210){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0 2p3/2-lam
    else if(decayProd==211){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0 4p3/2-lam
    else if(decayProd==212){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0 4p5/2-lam
    else if(decayProd==213){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0 2p1/2-rho
    else if(decayProd==214){flav_q1=+mu_dif_u_d; flav_q2=-mu_dif_u_d; flav_q3=0.;   sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0 2p3/2-rho

  }else if(baryonFlag==5){// cascades anti3_plet
    // decay cascade anti-triplet 0   
    if(decayProd==101)    { flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==201){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0  2p1/2-lam
    else if(decayProd==202){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;} //0  2p3/2-lam
    else if(decayProd==203){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  2p1/2-rho
    else if(decayProd==204){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p1/2-rho
    else if(decayProd==205){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  2p3/2-rho
    else if(decayProd==206){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p3/2-rho
    else if(decayProd==207){flav_q1=+mu_sum_u_s; flav_q2=+mu_sum_u_s; flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;} //0  4p5/2-rho

    // decay cascade anti-triplet -
    else if(decayProd==102){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=0; llb_val=0; lrb_val=0;}  //-  ground
    else if(decayProd==208){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;}  //-  2p1/2-lam
    else if(decayProd==209){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=1; lrb_val=0;}  //-  2p3/2-lam
    else if(decayProd==210){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //-  2p1/2-rho
    else if(decayProd==211){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //-  4p1/2-rho
    else if(decayProd==212){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //-  2p3/2-rho
    else if(decayProd==213){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //-  4p3/2-rho
    else if(decayProd==214){flav_q1=+mu_sum_d_s; flav_q2=+mu_sum_d_s; flav_q3=mu_qc; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=0; lrb_val=1;}  //-  4p5/2-rho

    // decay to cascade prime 0
    else if(decayProd==103){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==104){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //0  ground
    else if(decayProd==215){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p1/2-lam
    else if(decayProd==216){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p1/2-lam
    else if(decayProd==217){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  2p3/2-lam
    else if(decayProd==218){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p3/2-lam
    else if(decayProd==219){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //0  4p5/2-lam
    else if(decayProd==220){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p1/2-rho
    else if(decayProd==221){flav_q1=+mu_dif_u_s; flav_q2=-mu_dif_u_s; flav_q3=0.; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //0  2p3/2-rho

    // decay to cascade prime -
    else if(decayProd==105){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //-  ground
    else if(decayProd==106){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=1.5; jb_val=1.5; lb_val=0; slb_val=1; llb_val=0; lrb_val=0;} //-  ground
    else if(decayProd==222){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //-  2p1/2-lam
    else if(decayProd==223){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=1.5; jb_val=0.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //-  4p1/2-lam
    else if(decayProd==224){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //-  2p3/2-lam
    else if(decayProd==225){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=1.5; jb_val=1.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //-  4p3/2-lam
    else if(decayProd==226){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=1.5; jb_val=2.5; lb_val=1; slb_val=1; llb_val=1; lrb_val=0;} //-  4p5/2-lam
    else if(decayProd==227){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=0.5; jb_val=0.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //-  2p1/2-rho
    else if(decayProd==228){flav_q1=+mu_dif_d_s; flav_q2=-mu_dif_d_s; flav_q3=0.; sb_val=0.5; jb_val=1.5; lb_val=1; slb_val=0; llb_val=0; lrb_val=1;} //-  2p3/2-rho
  }

  //fetch quantum numbers and projections
  L   = 0;  mL = getMomentumProjections(L); //check if this is always the case
  JA  = ja_val;    mJA  = getMomentumProjections(JA, true);
  SA  = sa_val;    mSA  = getMomentumProjections(SA);
  SlA = sla_val;   mSlA = getMomentumProjections(SlA);
  LA  = la_val;    mLA  = getMomentumProjections(LA);
  LlA = lla_val;   mLlA = getMomentumProjections(LlA);
  LrA = lra_val;   mLrA = getMomentumProjections(LrA);

  SB  = sb_val;    mSB  = getMomentumProjections(SB);
  JB  = jb_val;    mJB  = getMomentumProjections(JB);
  SlB = slb_val;   mSlB = getMomentumProjections(SlB);
  LB  = lb_val;    mLB  = getMomentumProjections(LB);
  LlB = llb_val;   mLlB = getMomentumProjections(LlB);
  LrB = lrb_val;   mLrB = getMomentumProjections(LrB);

  S1  = 0.5;       mS1  = getMomentumProjections(S1);
  S2  = 0.5;       mS2  = getMomentumProjections(S2);
  S3  = 0.5;       mS3  = getMomentumProjections(S3);

  double k_value; k_value = K(MA, MB);
  double EB_value = EB(MB, k_value);
  double fi2_value  = FI2(EB_value, MA, k_value);

  double sum_value = ANGULAR_SUM_SQUARED(alpha_rho, alpha_lam, k_value, modeExcitation);
  double decayWidth = DecayWidth(fi2_value, sum_value);

  // std::cout<<decayProd<<"=decayProd "<<"  MB="<<MB<<std::endl;
  // std::cout<<"sb_val= "<<sb_val<<std::endl;
  // std::cout<<"flav_q1="<<flav_q1<<" flav_q2="<<flav_q2<<" flav_q3= "<<flav_q3<<" SB="<<sb_val<<" JB="<<jb_val<<" LB="<<lb_val<<" SlB="<<slb_val<<" LlamB="<<llb_val<<" LrhoB="<<lrb_val<<std::endl;
  // //testing integrals
  //alpha_rho = 0.4132549850060273; alpha_lam =0.5246260684382235;
  //k_value = 0.1422944563250534;
  //mlight = 0.382;  
  //std::cout<<mcharm<<"     QUARK MASSES    "<<mlight<<std::endl;
  //double thetak=1, phik=1;


  return decayWidth;
}

double EMDecayWidths::DecayWidth(double fi2_value, double angular_sum_value){
  double GeV2 = std::pow(1000., 2);
  double decayWidth =  fi2_value * (2./(std::pow(2.*pi_val, 3)*(2. * JA + 1))) * angular_sum_value;
  return (2.*pi_val) * decayWidth * GeV2;
}

std::vector<double> EMDecayWidths::getMomentumProjections(double j_angular, bool onlyPositive){
  // Method to obtain the projections "m_projection" for a given angular momentum "j_angular"
  // set onlyPositive = true, to obtain only m_projection > 0
  std::vector<double> angularProjections; angularProjections.clear();
  if(j_angular==0.){angularProjections.push_back(0); return angularProjections;}
  double m_projection = 0.;
  if(!onlyPositive) m_projection = (-1.0)*j_angular;
  else m_projection = (0.5)*(int)(std::ceil(j_angular)!=j_angular);
  do{
    angularProjections.push_back(m_projection);
    m_projection++;
  }while(m_projection<=j_angular);
  return angularProjections;
}

int EMDecayWidths::KroneckerDelta(double i, double j){
  if(i==j) return 1;
  else return 0;
}

double EMDecayWidths::EB(double MB, double K){
  double value = std::sqrt(std::pow(MB, 2) + std::pow(K, 2));
  return value;
}

double EMDecayWidths::K(double MA, double MB){
  double value = ((0.5)*(std::pow(MA, 2) - std::pow(MB, 2))) / MA;
  return value;
}

double EMDecayWidths::FI2(double EB, double MA, double k_value){
  double value = 4.* pi_val * (EB/MA) * std::pow(k_value, 2);
  return value;
}

double EMDecayWidths::ClebschGordan(WignerSymbols *m_wigner,
				    double l1, double l2, double l3,
				    double m1, double m2, double m3){
  double coef = std::pow(-1.0, l2-l1-m3) * std::pow(2.0*l3 + 1.0, 0.5);
  double three_j = m_wigner->wigner3j(l1, l2, l3, m1, m2, (-1.0)*m3);
  return coef * three_j;
}

double EMDecayWidths::ANGULAR_SUM_SQUARED(double alpha_rho, double alpha_lam, double k_value, int excMode){

  WignerSymbols *m_wigner = new WignerSymbols();
  double dummy = 0.;
  double AMP1_1 = 0.; double AMP1_2 = 0.; double AMP1 = 0.;
  double AMP2_1 = 0.; double AMP2_2 = 0.; double AMP2 = 0.; 
  double AMP3_1 = 0.; double AMP3_2 = 0.; double AMP3 = 0.;
  double TOT_AMP = 0.; double SUM_SQUARED_AMP = 0.;

  for(int iMJA = 0;  iMJA<(int)mJA.size(); iMJA++){//SUM SQUARED
    TOT_AMP = 0.;
    AMP1_1 = 0.; AMP1_2 = 0.; AMP1 = 0.;
    AMP2_1 = 0.; AMP2_2 = 0.; AMP2 = 0.;
    AMP3_1 = 0.; AMP3_2 = 0.; AMP3 = 0.;    
    for(int iMSA = 0;  iMSA<(int)mSA.size();  iMSA++)// AMP1, SPIN FLIP
      for(int iMSlA = 0; iMSlA<(int)mSlA.size(); iMSlA++)
	for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
	  for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
	    for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)
	      for(int iMSB = 0;  iMSB<(int)mSB.size(); iMSB++)
		for(int iMSlB = 0;  iMSlB<(int)mSlB.size(); iMSlB++)
		  for(int iMLB = 0;  iMLB<(int)mLB.size(); iMLB++)
		    for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
		      for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++)
			for(int iMJB = 0;  iMJB<(int)mJB.size(); iMJB++)
			  for(int iMS1 = 0; iMS1 <(int)mS1.size(); iMS1++)
			    for(int iMS2 = 0; iMS2 <(int)mS2.size(); iMS2++)
			      for(int iMS3 = 0; iMS3 <(int)mS3.size(); iMS3++){
				//    U1_rho_lambda(k_value, alpha_rho, alpha_lam, LA, MLA, MLB, mLrA,     mLlA,  mLrB,   mLlB, int excMode)
				dummy = U1_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLA.at(iMLA), mLB.at(iMLB), mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB), mLlB.at(iMLlB), excMode) *
				  std::sqrt((S1 + mS1.at(iMS1)) * (S1 - mS1.at(iMS1) + 1))*
				  ClebschGordan(m_wigner, LB,  SB,  JB,  mLB.at(iMLB),   mSB.at(iMSB),   mJB.at(iMJB))*
				  ClebschGordan(m_wigner, LA,  SA,  JA,  mLA.at(iMLA),   mSA.at(iMSA),   mJA.at(iMJA))*
				  ClebschGordan(m_wigner, LlA, LrA, LA,  mLlA.at(iMLlA), mLrA.at(iMLrA), mLA.at(iMLA))*
				  ClebschGordan(m_wigner, LlB, LrB, LB,  mLlB.at(iMLlB), mLrB.at(iMLrB), mLB.at(iMLB))*
				  ClebschGordan(m_wigner, SlB, S3,  SB,  mSlB.at(iMSlB), mS3.at(iMS3),   mSB.at(iMSB))*
				  ClebschGordan(m_wigner, S1,  S2,  SlB, mS1.at(iMS1)-1, mS2.at(iMS2),   mSlB.at(iMSlB))*
				  ClebschGordan(m_wigner, SlA, S3,  SA,  mSlA.at(iMSlA), mS3.at(iMS3),   mSA.at(iMSA))*
				  ClebschGordan(m_wigner, S1,  S2,  SlA, mS1.at(iMS1),   mS2.at(iMS2),   mSlA.at(iMSlA));
				AMP1_1+=dummy;
			      }
    AMP1_1 *= flav_q1 * (2.*std::sqrt(pi_val * k_value));

    for(int iMSA = 0; iMSA<(int)mSA.size(); iMSA++) // AMP1, ORBITAL FLIP
      for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
	for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
	  for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)
	    for(int iMJB = 0; iMJB<(int)mJB.size(); iMJB++)
	      for(int iMSB = 0; iMSB<(int)mSB.size(); iMSB++)
		for(int iMLB = 0; iMLB<(int)mLB.size(); iMLB++)
		  for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
		    for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++){
		      //      T1_rho_lambda(k_value, alpha_rho, alpha_lam, int LA, int mLrA, int MLlA, int MLrB, int MLlB, int excMode)
		      dummy = T1_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB),  mLlB.at(iMLlB), excMode)*
			KroneckerDelta_extended(mLrA.at(iMLrA), mLlA.at(iMLlA), excMode)*
			KroneckerDelta(mSB.at(iMSB), mSA.at(iMSA)) *
			ClebschGordan(m_wigner, LB,  SB,  JB, mLB.at(iMLB),   mSB.at(iMSB),    mJB.at(iMJB))*
			ClebschGordan(m_wigner, LlB, LrB, LB, mLlB.at(iMLlB), mLrB.at(iMLrB),  mLB.at(iMLB))*
			ClebschGordan(m_wigner, LlA, LrA, LA, mLlA.at(iMLlA), mLrA.at(iMLrA),  mLA.at(iMLA))*
			ClebschGordan(m_wigner, LA,  SA,  JA, mLA.at(iMLA),   mSA.at(iMSA),    mJA.at(iMJA));
		      AMP1_2+=dummy;
		    }
    AMP1_2 *= flav_q1 * KroneckerDelta(SlA, SlB) * KroneckerDelta(SA, SB) * (1.*std::sqrt(pi_val / k_value));
    AMP1 = AMP1_1 - AMP1_2;

    for(int iMSA = 0;  iMSA<(int)mSA.size();  iMSA++) // AMP2, SPIN FLIP
      for(int iMSlA = 0; iMSlA<(int)mSlA.size(); iMSlA++)
    	for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
    	  for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
    	    for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)
    	      for(int iMSB = 0;  iMSB<(int)mSB.size(); iMSB++)
    		for(int iMSlB = 0;  iMSlB<(int)mSlB.size(); iMSlB++)
    		  for(int iMLB = 0;  iMLB<(int)mLB.size(); iMLB++)
    		    for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
    		      for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++)
    			for(int iMJB = 0;  iMJB<(int)mJB.size(); iMJB++)
    			  for(int iMS1 = 0; iMS1 <(int)mS1.size(); iMS1++)
    			    for(int iMS2 = 0; iMS2 <(int)mS2.size(); iMS2++)
    			      for(int iMS3 = 0; iMS3 <(int)mS3.size(); iMS3++){
    				dummy = U2_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLA.at(iMLA),  mLB.at(iMLB), mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB), mLlB.at(iMLlB), excMode)*
    				  std::sqrt((S2 + mS2.at(iMS2)) * (S2 - mS2.at(iMS2) + 1))*
    				  ClebschGordan(m_wigner, LB,  SB,  JB,   mLB.at(iMLB),    mSB.at(iMSB),     mJB.at(iMJB))*
    				  ClebschGordan(m_wigner, LA,  SA,  JA,   mLA.at(iMLA),    mSA.at(iMSA),     mJA.at(iMJA))*
    				  ClebschGordan(m_wigner, LlA, LrA, LA,   mLlA.at(iMLlA),  mLrA.at(iMLrA),   mLA.at(iMLA))*
    				  ClebschGordan(m_wigner, LlB, LrB, LB,   mLlB.at(iMLlB),  mLrB.at(iMLrB),   mLB.at(iMLB))*
    				  ClebschGordan(m_wigner, SlB, S3,  SB,   mSlB.at(iMSlB),  mS3.at(iMS3),     mSB.at(iMSB))*
    				  ClebschGordan(m_wigner, S1,  S2,  SlB,  mS1.at(iMS1),    mS2.at(iMS2) - 1, mSlB.at(iMSlB))*
    				  ClebschGordan(m_wigner, SlA, S3,  SA,   mSlA.at(iMSlA),  mS3.at(iMS3),     mSA.at(iMSA))*
    				  ClebschGordan(m_wigner, S1,  S2,  SlA,  mS1.at(iMS1),    mS2.at(iMS2),     mSlA.at(iMSlA));			     
    				AMP2_1+=dummy;
    			      }
    AMP2_1 *= flav_q2 * (2.*std::sqrt(pi_val * k_value));

    for(int iMSA = 0; iMSA<(int)mSA.size(); iMSA++) // AMP2, ORBITAL FLIP
      for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
    	for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
    	  for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)                    
    	    for(int iMJB = 0; iMJB<(int)mJB.size(); iMJB++)
    	      for(int iMSB = 0; iMSB<(int)mSB.size(); iMSB++)
    		for(int iMLB = 0; iMLB<(int)mLB.size(); iMLB++)
    		  for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
    		    for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++){
    		      dummy = T2_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB), mLlB.at(iMLlB), excMode)*
    			KroneckerDelta_extended(mLrA.at(iMLrA), mLlA.at(iMLlA), excMode)*
    			KroneckerDelta(mSB.at(iMSB), mSA.at(iMSA))*
    			ClebschGordan(m_wigner, LB,   SB,  JB,  mLB.at(iMLB),    mSB.at(iMSB),    mJB.at(iMJB))*
    			ClebschGordan(m_wigner, LlB,  LrB, LB,  mLlB.at(iMLlB),  mLrB.at(iMLrB),  mLB.at(iMLB))*
    			ClebschGordan(m_wigner, LlA,  LrA, LA,  mLlA.at(iMLlA),  mLrA.at(iMLrA),  mLA.at(iMLA))*
    			ClebschGordan(m_wigner, LA,   SA,  JA,  mLA.at(iMLA),    mSA.at(iMSA),    mJA.at(iMJA));
    		      AMP2_2+=dummy;
    		    }		
    AMP2_2 *= flav_q2 * KroneckerDelta(SA, SB) * KroneckerDelta(SlA, SlB) * (1.*std::sqrt(pi_val / k_value));
    AMP2 = AMP2_1 - AMP2_2;
    
    for(int iMSA = 0;  iMSA<(int)mSA.size();  iMSA++) // AMP3, SPIN FLIP
      for(int iMSlA = 0; iMSlA<(int)mSlA.size(); iMSlA++)
    	for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
    	  for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
    	    for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)
    	      for(int iMSB = 0;  iMSB<(int)mSB.size(); iMSB++)
    		for(int iMSlB = 0;  iMSlB<(int)mSlB.size(); iMSlB++)
    		  for(int iMLB = 0;  iMLB<(int)mLB.size(); iMLB++)
    		    for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
    		      for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++)
    			for(int iMJB = 0;  iMJB<(int)mJB.size(); iMJB++)
    			  for(int iMS1 = 0; iMS1 <(int)mS1.size(); iMS1++)
    			    for(int iMS2 = 0; iMS2 <(int)mS2.size(); iMS2++)
    			      for(int iMS3 = 0; iMS3 <(int)mS3.size(); iMS3++){
    				dummy = U3_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLA.at(iMLA),  mLB.at(iMLB), mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB), mLlB.at(iMLlB), excMode)*
    				  std::sqrt((S3 + mS3.at(iMS3))*(S3 - mS3.at(iMS3) + 1))*
    				  ClebschGordan(m_wigner, LB,   SB,   JB,   mLB.at(iMLB),    mSB.at(iMSB),     mJB.at(iMJB))*
    				  ClebschGordan(m_wigner, LA,   SA,   JA,   mLA.at(iMLA),    mSA.at(iMSA),     mJA.at(iMJA))*
    				  ClebschGordan(m_wigner, LlA,  LrA,  LA,   mLlA.at(iMLlA),  mLrA.at(iMLrA),   mLA.at(iMLA))*
    				  ClebschGordan(m_wigner, LlB,  LrB,  LB,   mLlB.at(iMLlB),  mLrB.at(iMLrB),   mLB.at(iMLB))*
    				  ClebschGordan(m_wigner, SlB,  S3,   SB,   mSlB.at(iMSlB),  mS3.at(iMS3) - 1, mSB.at(iMSB))*
    				  ClebschGordan(m_wigner, S1,   S2,   SlB,  mS1.at(iMS1),    mS2.at(iMS2),     mSlB.at(iMSlB))*
    				  ClebschGordan(m_wigner, SlA,  S3,   SA,   mSlA.at(iMSlA),  mS3.at(iMS3),     mSA.at(iMSA))*
    				  ClebschGordan(m_wigner, S1,   S2,   SlA,  mS1.at(iMS1),    mS2.at(iMS2),     mSlA.at(iMSlA));
    				AMP3_1+=dummy;
    			      }
    AMP3_1 *= flav_q3 * (2.*std::sqrt(pi_val * k_value));

    for(int iMSA = 0; iMSA<(int)mSA.size(); iMSA++) // AMP3, ORBITAL FLIP
      for(int iMLA = 0; iMLA<(int)mLA.size(); iMLA++)
    	for(int iMLlA = 0; iMLlA<(int)mLlA.size(); iMLlA++)
    	  for(int iMLrA = 0; iMLrA<(int)mLrA.size(); iMLrA++)
    	    for(int iMJB = 0; iMJB<(int)mJB.size(); iMJB++)
    	      for(int iMSB = 0; iMSB<(int)mSB.size(); iMSB++)
    		for(int iMLB = 0; iMLB<(int)mLB.size(); iMLB++)
    		  for(int iMLlB = 0; iMLlB<(int)mLlB.size(); iMLlB++)
    		    for(int iMLrB = 0; iMLrB<(int)mLrB.size(); iMLrB++){
    		      dummy = T3_rho_lambda(k_value, alpha_rho, alpha_lam, LA, mLrA.at(iMLrA), mLlA.at(iMLlA), mLrB.at(iMLrB), mLlB.at(iMLlB), excMode)*
    			KroneckerDelta_extended(mLrA.at(iMLrA), mLlA.at(iMLlA), excMode)*
    			KroneckerDelta(mSB.at(iMSB), mSA.at(iMSA))*
    			ClebschGordan(m_wigner, LB,   SB,  JB, mLB.at(iMLB),   mSB.at(iMSB),   mJB.at(iMJB))*
    			ClebschGordan(m_wigner, LlB,  LrB, LB, mLlB.at(iMLlB), mLrB.at(iMLrB), mLB.at(iMLB))*
    			ClebschGordan(m_wigner, LlA,  LrA, LA, mLlA.at(iMLlA), mLrA.at(iMLrA), mLA.at(iMLA))*
    			ClebschGordan(m_wigner, LA,   SA,  JA, mLA.at(iMLA),   mSA.at(iMSA),   mJA.at(iMJA));
    		      AMP3_2+=dummy;
    		    }
    AMP3_2 *= flav_q3 * KroneckerDelta(SlA, SlB) * KroneckerDelta(SA, SB) * (1.*std::sqrt(pi_val / k_value));
    AMP3 = AMP3_1 - AMP3_2;

    // sum quark amplitudes, squared them and get squared the total
    TOT_AMP = AMP1 + AMP2 + AMP3;
    SUM_SQUARED_AMP += TOT_AMP * TOT_AMP;
  }
  delete m_wigner;
  return SUM_SQUARED_AMP;
}

double EMDecayWidths::T1_rho_lambda(double k_value, double alpha_rho, double alpha_lam, int LA, int MLrA, int MLlA, int MLrB, int MLlB, int excMode){
  double thetak=0., phik=0.;
    
  if(excMode==0){ //ground
    return 0.;
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return T1l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, MLlA) * KroneckerDelta(MLlA, 1); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return T1Dl2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Dlambda-> GS
      }else if(LB==1 && LlB==1){
	return T1Dl2Pll2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return T1Dl2Prl2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return T1r(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, MLlA) * KroneckerDelta(MLrA, 1); // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return T1Dr2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Drho-> GS
      }else if(LB==1 && LlB==1){
	return T1Dr2Plr2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return T1Dr2Prr2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLrB); // Drho-> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==0){
	return T1Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T1Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T1Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==0){
	return T1Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T1Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T1Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return T1Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T1Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T1Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){
    if(LB==0){
	return 0; // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return T1Rl2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return T1Rl2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial lambda-> Prho
      }
  }else if(excMode==4){
    if(LB==0){
	return 0; // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return T1Rr2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return T1Rr2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial rho-> Prho
      }
  }
  
  return 0.;
}

double EMDecayWidths::T2_rho_lambda(double k_value, double alpha_rho, double alpha_lam, int LA, int MLrA, int MLlA,  int MLrB, int MLlB, int excMode){
  double thetak=0., phik=0.;

  if(excMode==0){ //ground
    return 0.;
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return T2l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, MLlA) * KroneckerDelta(MLlA, 1); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return T2Dl2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Dlambda-> GS
      }else if(LB==1 && LlB==1){
	return T2Dl2Pll2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return T2Dl2Prl2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return T2r(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, MLlA) * KroneckerDelta(MLrA, 1); // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return T2Dr2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Drho-> GS
      }else if(LB==1 && LlB==1){
	return T2Dr2Plr2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return T2Dr2Prr2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLrB); // Drho-> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==0){
	return T2Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T2Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T2Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==0){
	return T2Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T2Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T2Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return T2Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T2Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T2Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){
    if(LB==0){
	return 0; // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return T2Rl2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return T2Rl2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial lambda-> Prho
      }
  }else if(excMode==4){
    if(LB==0){
	return 0; // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return T2Rr2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return T2Rr2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial rho-> Prho
      }
  }
  
  return 0.;
}

double EMDecayWidths::T3_rho_lambda(double k_value, double alpha_rho, double alpha_lam, int LA, int MLrA, int MLlA,  int MLrB, int MLlB, int excMode){
  double thetak=0., phik=0.;

  if(excMode==0){ //ground
    return 0.;
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return T3l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, MLlA) * KroneckerDelta(MLlA, 1); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return T3Dl2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Dlambda-> GS
      }else if(LB==1 && LlB==1){
	return T3Dl2Pll2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return T3Dl2Prl2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return T3r() * KroneckerDelta(MLrA, 1); // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return T3Dr2GS2mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // Drho-> GS
      }else if(LB==1 && LlB==1){
	return T3Dr2Plr2ml1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return T3Dr2Prr2mr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLrB); // Drho-> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==0){
	return T3Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T3Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T3Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==0){
	return T3Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T3Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T3Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return T3Mix2GS1mgs(k_value, alpha_lam, alpha_rho, thetak, phik, MLrA, MLlA); // mixed-> GS
      }else if(LB==1 && LlB==1){
	return T3Mix2Pl1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return T3Mix2Pr1m(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){
    if(LB==0){
	return 0; // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return T3Rl2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return T3Rl2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial lambda-> Prho
      }
  }else if(excMode==4){
    if(LB==0){
	return 0; // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return T3Rr2Pl(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLlB); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return T3Rr2Pr(k_value, alpha_lam, alpha_rho, thetak, phik, MLlA, MLrA, MLrB); // radial rho-> Prho
      }
  }
  
  return 0.;
}

// Dwave->Pwave lambda
double EMDecayWidths::U1Dl2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLlB_val){
  double value1 = SPINFLIP_U1_l2_m1_l1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 1);
  double value2 = SPINFLIP_U1_l2_m0_l1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, 0);
  double value3 = SPINFLIP_U1_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::U2Dl2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLlB_val){
  double value1 = SPINFLIP_U2_l2_m1_l1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 1);
  double value2 = SPINFLIP_U2_l2_m0_l1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, 0);
  double value3 = SPINFLIP_U2_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, -1)* KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::U3Dl2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLlB_val){
  double value1 = SPINFLIP_U3_l2_m1_l1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 1);
  double value2 = SPINFLIP_U3_l2_m0_l1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, 0);
  double value3 = SPINFLIP_U3_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::T1Dl2Pll2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLlB_val){
  double value1 = T1_l2_m2_l1_m1( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLlA_val, 2)* KroneckerDelta(MLlB_val, 1);
  double value2 = T1_l2_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 0);
  double value3 = T1_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val,0)   * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}
    
double EMDecayWidths::T2Dl2Pll2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLlB_val){
  double value1 = T2_l2_m2_l1_m1( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val, 2)  * KroneckerDelta(MLlB_val, 1);
  double value2 = T2_l2_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 0);
  double value3 = T2_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val,0)   * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::T3Dl2Pll2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLlB_val){
  double value1 = T3_l2_m2_l1_m1( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) *  KroneckerDelta(MLlA_val, 2) * KroneckerDelta(MLlB_val, 1);
  double value2 = T3_l2_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 0);
  double value3 = T3_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3;
}

// Dwave lambda ->Pwave rho 
double EMDecayWidths::U1Dl2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrB_val){
  double value = SPINFLIP_U1_l2_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, 0);
  return value;
}

double EMDecayWidths::U2Dl2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrB_val){
  double value = SPINFLIP_U2_l2_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLrB_val, 0);
  return value;
}

double EMDecayWidths::U3Dl2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrB_val){
  double value = SPINFLIP_U3_l2_m0_r1_m0() * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLrB_val, 0); // check
  return value;
}

double EMDecayWidths::T1Dl2Prl2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrB_val){
  double value1 = T1_l2_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  double value2 = T1_l2_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLrB_val, 0);
  return value1 + value2;
}

double EMDecayWidths::T2Dl2Prl2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrB_val){
  double value1 = T2_l2_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  double value2 = T2_l2_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLrB_val, 0);
  return value1 + value2;
}
double EMDecayWidths::T3Dl2Prl2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrB_val){
  double value1 = T3_l2_m0_r1_m1m()  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1); // check
  double value2 = T3_l2_m1_r1_m0()  * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLrB_val, 0); // check
  return value1 + value2;
}

// Dwave rho ->Pwave lambda 
double EMDecayWidths::U1Dr2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlB_val){
  double value = SPINFLIP_U1_r2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlB_val, 0);
  return value;
}

double EMDecayWidths::U2Dr2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlB_val){
  double value = SPINFLIP_U2_r2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlB_val, 0);
  return value;
}

double EMDecayWidths::U3Dr2Pl2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlB_val){
  double value = SPINFLIP_U3_r2_m0_l1_m0() * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLlB_val, 0); // check
  return value;
}

double EMDecayWidths::T1Dr2Plr2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlB_val){
  double value1 = T1_r2_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlB_val, -1);
  double value2 = T1_r2_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLlB_val, 0);
  return value1 + value2;
}

double EMDecayWidths::T2Dr2Plr2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlB_val){
  double value1 = T2_r2_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlB_val, -1);
  double value2 = T2_r2_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLlB_val, 0);
  return value1 + value2;
}

double EMDecayWidths::T3Dr2Plr2ml1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlB_val){
  double value1 = T3_r2_m0_l1_m1m()  *  KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlB_val, -1); // check
  double value2 = T3_r2_m1_l1_m0()  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLlB_val, 0); // check
  return value1 + value2;
}

// Dwave->Pwave rho
double EMDecayWidths::U1Dr2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U1_r2_m1_r1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1);
  double value2 = SPINFLIP_U1_r2_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0);
  double value3 = SPINFLIP_U1_r2_m1m_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::U2Dr2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U2_r2_m1_r1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1);
  double value2 = SPINFLIP_U2_r2_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0);
  double value3 = SPINFLIP_U2_r2_m1m_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::U3Dr2Pr2m1m(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U3_r2_m1_r1_m1()  * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1);
  double value2 = SPINFLIP_U3_r2_m0_r1_m0()  * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0);
  double value3 = SPINFLIP_U3_r2_m1m_r1_m1m()  * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::T1Dr2Prr2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLrB_val){
  double value1 = T1_r2_m2_r1_m1( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 2)* KroneckerDelta(MLrB_val, 1);
  double value2 = T1_r2_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value3 = T1_r2_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val,0)   * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}
    
double EMDecayWidths::T2Dr2Prr2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLrB_val){
  double value1 = T2_r2_m2_r1_m1( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 2)* KroneckerDelta(MLrB_val, 1);
  double value2 = T2_r2_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value3 = T2_r2_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val,0)   * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}

double EMDecayWidths::T3Dr2Prr2mr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLrB_val){
  double value1 = T3_r2_m2_r1_m1()  *  KroneckerDelta(MLrA_val, 2)* KroneckerDelta(MLrB_val, 1);
  double value2 = T3_r2_m1_r1_m0()  * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value3 = T3_r2_m0_r1_m1m() * KroneckerDelta(MLrA_val,0)   * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3;
}

// Mixed -> Pwave lambda
double EMDecayWidths::U1Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = SPINFLIP_U1_r1_m0_l1_m1_l1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 1) * KroneckerDelta(MLrA_val, 0);
  double value2 = SPINFLIP_U1_r1_m0_l1_m0_l1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, 0) * KroneckerDelta(MLrA_val, 0);
  double value3 = SPINFLIP_U1_r1_m0_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1) * KroneckerDelta(MLrA_val, 0);
  return value1 + value2 + value3;
}

double EMDecayWidths::U2Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = SPINFLIP_U2_r1_m0_l1_m1_l1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 1) * KroneckerDelta(MLrA_val, 0);
  double value2 = SPINFLIP_U2_r1_m0_l1_m0_l1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, 0) * KroneckerDelta(MLrA_val, 0);
  double value3 = SPINFLIP_U2_r1_m0_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1) * KroneckerDelta(MLrA_val, 0);
  return value1 + value2 + value3;
}

double EMDecayWidths::U3Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = SPINFLIP_U3_r1_m0_l1_m1_l1_m1()   * KroneckerDelta(MLlA_val, 1)  * KroneckerDelta(MLlB_val, 1) * KroneckerDelta(MLrA_val, 0);
  double value2 = SPINFLIP_U3_r1_m0_l1_m0_l1_m0()   * KroneckerDelta(MLlA_val, 0)  * KroneckerDelta(MLlB_val, 0) * KroneckerDelta(MLrA_val, 0);
  double value3 = SPINFLIP_U3_r1_m0_l1_m1m_l1_m1m()   * KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1) * KroneckerDelta(MLrA_val, 0);
  return value1 + value2 + value3;  // integrals = 0
}

double EMDecayWidths::T1Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = T1_r1_m0_l1_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  double value2 = T1_r1_m0_l1_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 0);
  double value3 = T1_r1_m1_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 1);
  double value4 = T1_r1_m1_l1_m0_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, 0);
  double value5 = T1_r1_m1_l1_m1m_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3 + value4 + value5;
}
    
double EMDecayWidths::T2Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = T2_r1_m0_l1_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  double value2 = T2_r1_m0_l1_m1_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 0);
  double value3 = T2_r1_m1_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 1);
  double value4 = T2_r1_m1_l1_m0_l1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, 0);
  double value5 = T2_r1_m1_l1_m1m_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3 + value4 + value5;
}

double EMDecayWidths::T3Mix2Pl1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLlB_val){
  double value1 = T3_r1_m0_l1_m0_l1_m1m() * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  double value2 = T3_r1_m0_l1_m1_l1_m0()  * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 0);
  double value3 = T3_r1_m1_l1_m1_l1_m1() * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLlB_val, 1);
  double value4 = T3_r1_m1_l1_m0_l1_m0() * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, 0);
  double value5 = T3_r1_m1_l1_m1m_l1_m1m()  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, -1) * KroneckerDelta(MLlB_val, -1);
  return value1 + value2 + value3 + value4 + value5; // tensors = 0
}

// Mixed -> Pwave rho
double EMDecayWidths::U1Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U1_r1_m1_l1_m0_r1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = SPINFLIP_U1_r1_m0_l1_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0) * KroneckerDelta(MLlA_val, 0);
  double value3 = SPINFLIP_U1_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1) * KroneckerDelta(MLlA_val, 0);
  return value1 + value2 + value3;
}

double EMDecayWidths::U2Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U2_r1_m1_l1_m0_r1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = SPINFLIP_U2_r1_m0_l1_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0) * KroneckerDelta(MLlA_val, 0);
  double value3 = SPINFLIP_U2_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1) * KroneckerDelta(MLlA_val, 0);
  return value1 + value2 + value3;
}

double EMDecayWidths::U3Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = SPINFLIP_U3_r1_m1_l1_m0_r1_m1(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 1)  * KroneckerDelta(MLrB_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = SPINFLIP_U3_r1_m0_l1_m0_r1_m0(  k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, 0)  * KroneckerDelta(MLrB_val, 0) * KroneckerDelta(MLlA_val, 0);
  double value3 = SPINFLIP_U3_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)   * KroneckerDelta(MLrA_val, -1) * KroneckerDelta(MLrB_val, -1) * KroneckerDelta(MLlA_val, 0);
  return value1 + value2 + value3;
}

double EMDecayWidths::T1Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = T1_r1_m0_l1_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  double value2 = T1_r1_m1_l1_m0_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, 0);
  double value3 = T1_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 1);
  double value4 = T1_r1_m0_l1_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value5 = T1_r1_m1_ml_1m_1r_1m_1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, -1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3 + value4 + value5;
}

double EMDecayWidths::T2Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = T2_r1_m0_l1_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  double value2 = T2_r1_m1_l1_m0_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, 0);
  double value3 = T2_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 1);
  double value4 = T2_r1_m0_l1_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value5 = T2_r1_m1_ml_1m_1r_1m_1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, -1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3 + value4 + value5;
}

double EMDecayWidths::T3Mix2Pr1m(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLlA_val, int MLrA_val, int MLrB_val){
  double value1 = T3_r1_m0_l1_m0_r1_m1m() * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1); //=0
  double value2 = T3_r1_m1_l1_m0_r1_m0()  * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, 0); //=0
  double value3 = T3_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 1);
  double value4 = T3_r1_m0_l1_m1_r1_m0( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, 0);
  double value5 = T3_r1_m1_ml_1m_1r_1m_1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  * KroneckerDelta(MLrA_val, -1)  *  KroneckerDelta(MLlA_val, 1) * KroneckerDelta(MLrB_val, -1);
  return value1 + value2 + value3 + value4 + value5;
}

// Dwave lambda -> ground state 
double EMDecayWidths::U1Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U1_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U2_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U3_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T1_l2_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 0)* KroneckerDelta(MLlA_val, 1);
  return value ;
}

double EMDecayWidths::T2Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T2_l2_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 0)* KroneckerDelta(MLlA_val, 1);
  return value ;
}

double EMDecayWidths::T3Dl2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T3_l2_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  *  KroneckerDelta(MLrA_val, 0)* KroneckerDelta(MLlA_val, 1);
  return value ;
}

// Dwave rho -> ground state
double EMDecayWidths::U1Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U1_r2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0);
  return value;
}

double EMDecayWidths::U2Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U2_r2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0);
  return value;
}

double EMDecayWidths::U3Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U3_r2_m0_GS() * KroneckerDelta(MLrA_val, 0);
  return value;
}

double EMDecayWidths::T1Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T1_r2_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  return value ;
}

double EMDecayWidths::T2Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T2_r2_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  return value ;
}

double EMDecayWidths::T3Dr2GS2mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value = T3_r2_m1_GS() * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  return value ;
}

// Mixed -> ground state
double EMDecayWidths::U1Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U1_r1_m0_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U2_r1_m0_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U3_r1_m0_l1_m0_GS() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value1 = T1_r1_m1_l1_m0_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = T1_r1_m0_l1_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 1);
  return value1 + value2;
}

double EMDecayWidths::T2Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value1 = T2_r1_m1_l1_m0_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = T2_r1_m0_l1_m1_GS( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 1);
  return value1 + value2;
}

double EMDecayWidths::T3Mix2GS1mgs(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val){
  double value1 = T3_r1_m1_l1_m0_GS() * KroneckerDelta(MLrA_val, 1) * KroneckerDelta(MLlA_val, 0);
  double value2 = T3_r1_m0_l1_m1_GS() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 1);
  return value1 + value2;
}

// Radial lambda -> ground state 
double EMDecayWidths::U1Rl2GS(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U1_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Rl2GS(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U2_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Rl2GS(double k_value, double alpha_lam, double alpha_rho, int MLlA_val){
  double value = SPINFLIP_U3_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA_val, 0);
  return value;
}

// Radial rho -> ground state 
double EMDecayWidths::U1Rr2GS(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U1_nr1_r0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0);
  return value;
}

double EMDecayWidths::U2Rr2GS(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U2_nr1_r0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0);
  return value;
}


double EMDecayWidths::U3Rr2GS(double k_value, double alpha_lam, double alpha_rho, int MLrA_val){
  double value = SPINFLIP_U3_nr1_r0_m0_GS() * KroneckerDelta(MLrA_val, 0);
  return value;
}

// Radial lambda -> P lambda 
double EMDecayWidths:: U1Rl2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U1_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths:: U2Rl2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U2_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths:: U3Rl2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U3_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Rl2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T1_nl1_l0_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T2Rl2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T2_nl1_l0_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T3Rl2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik,  int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T3_nl1_l0_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

// Radial lambda -> P rho 
double EMDecayWidths::U1Rl2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U1_nl1_l0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Rl2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U2_nl1_l0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Rl2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U3_nl1_l0_m0_r1_m0() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Rl2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T1_nl1_l0_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T2Rl2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T2_nl1_l0_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T3Rl2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T3_nl1_l0_m0_r1_m1m() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

// Radial rho -> P lambda  
double EMDecayWidths::U1Rr2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U1_nr1_r0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Rr2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U2_nr1_r0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Rr2Pl(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U3_nr1_r0_m0_l1_m0() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Rr2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T1_nr1_r0_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T2Rr2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T2_nr1_r0_m0_l1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

double EMDecayWidths::T3Rr2Pl(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLlB_val){
  double value = T3_nr1_r0_m0_l1_m1m() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLlB_val, -1);
  return value;
}

// Radial rho -> P rho  
double EMDecayWidths::U1Rr2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U1_nr1_r0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U2Rr2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U2_nr1_r0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::U3Rr2Pr(double k_value, double alpha_lam, double alpha_rho, int MLrA_val, int MLlA_val){
  double value = SPINFLIP_U3_nr1_r0_m0_r1_m0() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0);
  return value;
}

double EMDecayWidths::T1Rr2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLrB_val){
  double value = T1_nr1_r0_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  return value;
}

double EMDecayWidths::T2Rr2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLrB_val){
  double value = T2_nr1_r0_m0_r1_m1m( k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  return value;
}

double EMDecayWidths::T3Rr2Pr(double k_value, double alpha_lam, double alpha_rho, double thetak, double phik, int MLrA_val, int MLlA_val, int MLrB_val){
  double value = T3_nr1_r0_m0_r1_m1m() * KroneckerDelta(MLrA_val, 0) * KroneckerDelta(MLlA_val, 0) * KroneckerDelta(MLrB_val, -1);
  return value;
}

double EMDecayWidths::U1_rho_lambda(double k_value, double alpha_rho, double alpha_lam, double LA, int MLA, int MLB, int MLrA, int MLlA, int MLrB, int MLlB,  int excMode){
  double thetak=0., phik=0.;
    
  // if(MLlA!=0 && excMode==0) return 0.;
  // if(MLlA!=0 && excMode==1) return 0.;
  // if(MLrA!=0 && excMode==2) return 0.;

  if(excMode==0){ //ground
    return SPINFLIP_U1_GS_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA, 0);
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return SPINFLIP_U1_1l_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik, thetak) * KroneckerDelta(MLlA, 0); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return U1Dl2GS2mgs(k_value, alpha_lam, alpha_rho, MLlA); // Dlambda -> GS
      }else if(LB==1 && LlB==1){
	return U1Dl2Pl2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return U1Dl2Pr2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return SPINFLIP_U1_1r_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik, thetak) * KroneckerDelta(MLrA, 0); // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return U1Dr2GS2mgs(k_value, alpha_lam, alpha_rho, MLrA); // Drho -> GS
      }else if(LB==1 && LlB==1){
	return U1Dr2Pl2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return U1Dr2Pr2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLrB); // Drho -> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==1 && LlB==1){
	return U1Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U1Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==1 && LlB==1){
	return U1Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U1Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return U1Mix2GS1mgs(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // mixed -> GS
      }else if(LB==1 && LlB==1){
	return U1Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U1Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){ // radial lambda excitation initial baryon
    if(LB==0){
	return U1Rl2GS(k_value, alpha_lam, alpha_rho, MLlA); // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return U1Rl2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return U1Rl2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Prho
      }
  }else if(excMode==4){ // radial rho excitation initial baryon
    if(LB==0){
	return U1Rr2GS(k_value, alpha_lam, alpha_rho, MLrA); // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return U1Rr2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return U1Rr2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Prho
      }
  }
  return 0.;  
}

double EMDecayWidths::U2_rho_lambda(double k_value, double alpha_rho, double alpha_lam, double LA, int MLA, int MLB, int MLrA, int MLlA, int MLrB, int MLlB,  int excMode){
  double thetak=0., phik=0.;
  
  // if(MLlA!=0 && excMode==0) return 0.;
  // if(MLlA!=0 && excMode==1) return 0.;
  // if(MLrA!=0 && excMode==2) return 0.;

  if(excMode==0){ //ground
    return SPINFLIP_U2_GS_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight) * KroneckerDelta(MLlA, 0);
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return SPINFLIP_U2_1l_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik,thetak) * KroneckerDelta(MLlA, 0); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return U2Dl2GS2mgs(k_value, alpha_lam, alpha_rho, MLlA); // Dlambda -> GS
      }else if(LB==1 && LlB==1){
	return U2Dl2Pl2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return U2Dl2Pr2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return SPINFLIP_U2_1r_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik,thetak) * KroneckerDelta(MLrA, 0) ; // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return U2Dr2GS2mgs(k_value, alpha_lam, alpha_rho, MLrA); // Drho -> GS
      }else if(LB==1 && LlB==1){
	return U2Dr2Pl2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return U2Dr2Pr2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLrB); // Drho -> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==1 && LlB==1){
	return U2Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U2Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==1 && LlB==1){
	return U2Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U2Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return U2Mix2GS1mgs(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // mixed -> GS
      }else if(LB==1 && LlB==1){
	return U2Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U2Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){ // radial lambda excitation initial baryon
    if(LB==0){
	return U2Rl2GS(k_value, alpha_lam, alpha_rho, MLlA); // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return U2Rl2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return U2Rl2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Prho
      }
  }else if(excMode==4){ // radial rho excitation initial baryon
    if(LB==0){
	return U2Rr2GS(k_value, alpha_lam, alpha_rho, MLrA); // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return U2Rr2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return U2Rr2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Prho
      }
  }
  return 0.;
}

double EMDecayWidths::U3_rho_lambda(double k_value, double alpha_rho, double alpha_lam, double LA, int MLA, int MLB, int MLrA, int MLlA, int MLrB, int MLlB,  int excMode){
  double thetak=0., phik=0.;
  
  // if(MLlA!=0 && excMode==0) return 0.;
  // if(MLlA!=0 && excMode==1) return 0.;
  // if(MLrA!=0 && excMode==2) return 0.;

  if(excMode==0){ //ground
    return SPINFLIP_U3_GS_GS(k_value, alpha_lam, mcharm, mlight) * KroneckerDelta(MLlA, 0);
  }else if(excMode==1){ //lambda excitation initial baryon
    if(LA==1){
      return SPINFLIP_U3_1l_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik,thetak)* KroneckerDelta(MLlA, 0); // Plambda -> ground
    }else if(LA==2){
      if(LB==0){
	return U3Dl2GS2mgs(k_value, alpha_lam, alpha_rho, MLlA); // Dlambda -> GS
      }else if(LB==1 && LlB==1){
	return U3Dl2Pl2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLlB); // Dlambda -> Plambda
      }else if(LB==1 && LrB==1){
	return U3Dl2Pr2m1m(k_value, alpha_lam, alpha_rho, MLlA, MLrB); // Dlambda -> Prho
      }
    }
  }else if(excMode==2){ //rho excitation initial baryon
    if(LA==1){
      return SPINFLIP_U3_1r_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik, thetak) * KroneckerDelta(MLrA, 0); // Prho -> ground
    }else if(LA==2){
      if(LB==0){
	return U3Dr2GS2mgs(k_value, alpha_lam, alpha_rho, MLrA); // Drho -> GS
      }else if(LB==1 && LlB==1){
	return U3Dr2Pl2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLlB); // Drho -> Plambda
      }else if(LB==1 && LrB==1){
	return U3Dr2Pr2m1m(k_value, alpha_lam, alpha_rho, MLrA, MLrB); // Drho -> Prho
      }
    }
  }else if(excMode==5){ // mixed excitation initial baryon
    if(LA==0){
      if(LB==1 && LlB==1){
	return U3Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U3Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==1){
      if(LB==1 && LlB==1){
	return U3Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U3Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }else if(LA==2){
      if(LB==0){
	return U3Mix2GS1mgs(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // mixed -> GS
      }else if(LB==1 && LlB==1){
	return U3Mix2Pl1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLlB); // mixed-> Plambda
      }else if(LB==1 && LrB==1){
	return U3Mix2Pr1m(k_value, alpha_lam, alpha_rho, MLlA, MLrA, MLrB); // mixed-> Prho
      }
    }
  }else if(excMode==3){ // radial lambda excitation initial baryon
    if(LB==0){
	return U3Rl2GS(k_value, alpha_lam, alpha_rho, MLlA); // radial lambda-> GS
      }else if(LB==1 && LlB==1){
	return U3Rl2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Plambda
      }else if(LB==1 && LrB==1){
	return U3Rl2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial lambda-> Prho
      }
  }else if(excMode==4){ // radial rho excitation initial baryon
    if(LB==0){
	return U3Rr2GS(k_value, alpha_lam, alpha_rho, MLrA); // radial rho-> GS
      }else if(LB==1 && LlB==1){
	return U3Rr2Pl(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Plambda
      }else if(LB==1 && LrB==1){
	return U3Rr2Pr(k_value, alpha_lam, alpha_rho, MLrA, MLlA); // radial rho-> Prho
      }
  }
  return 0.;
}

int EMDecayWidths::KroneckerDelta_extended(double mLrA, double mLlA, int excMode){
  double thetak=0., phik=0.;
  return 1;
  if(excMode==0)
    return KroneckerDelta(0, 1);
  else if(excMode==1)
    return KroneckerDelta(mLlA, 1);
  else if(excMode==2)
    return KroneckerDelta(mLrA, 1);
  return 0.;
}

// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_GS_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = std::exp(value1 * (value2 + value3));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_GS_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / std::pow(alpha_lam * (mcharm + 2. * mlight), 2);
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = std::exp(value1 * (value2 + value3));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_GS_GS(double k_value, double alpha_lam,  double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = std::exp(value1);
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1l_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = p_imag * phik;
  double value = std::sqrt(6.) * p_imag * mcharm * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1l_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = (-1.0) * std::sqrt(3.) * p_imag * mcharm * k_value * std::exp(value1 + value2) * std::cos(thetak) / (2 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1l_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = (-1.0) * p_imag * phik;
  double value = (-1.0) * std::sqrt(6.) * p_imag * mcharm * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1l_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = std::sqrt(6.) * p_imag * mcharm * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1l_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = (-1.0) * std::sqrt(3.) * p_imag * mcharm * k_value * std::exp(value1 + value2) * std::cos(thetak)/ (2 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1l_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = (-1.0) * p_imag * phik;
  double value = (-1.0) * std::sqrt(6.) * p_imag * mcharm * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U3_1l_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = p_imag * phik;
  double value2 = (-3.0) * std::pow(mlight, 2) * std::pow(k_value, 2) / 2 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = (-1.0) * std::sqrt(6.) * p_imag * mlight * k_value * std::exp(value1 + value2) * std::sin(thetak)/ (2 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U3_1l_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-3.0) * std::pow(mlight, 2) * std::pow(k_value, 2) / (2 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = std::sqrt(3) * p_imag * mlight * k_value * std::exp(value1) * std::cos(thetak)/ (alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U3_1l_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * p_imag * phik;
  double value2 = (-3.0) * std::pow(mlight, 2) * std::pow(k_value, 2) / 2 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = std::sqrt(6) * p_imag * mlight * k_value * std::exp(value1 + value2) * std::sin(thetak)/ (2 * alpha_lam  * (mcharm + 2 * mlight) );
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1r_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = std::sqrt(2) * p_imag * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1r_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value =  (-1.0) * p_imag * k_value * std::exp(value1 + value2) * std::cos(thetak)/ (2 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U1_1r_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = (-1.0) * p_imag * phik;
  double value = (-1.0) * std::sqrt(2) * p_imag * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1r_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = (-1.0) * std::sqrt(2) * p_imag * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1r_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value =  p_imag * k_value * std::exp(value1 + value2) * std::cos(thetak)/ (2 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_1r_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = (-1.0) * p_imag * phik;
  double value = std::sqrt(2) * p_imag * k_value * std::exp(value1 + value2 + value3) * std::sin(thetak)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U3_1r_m1_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  k_value=0; alpha_lam=0; alpha_rho=0; mcharm=0; mlight=0; phik=0;  thetak=0;
  double value = 0;
  return value * k_value * alpha_lam * alpha_rho * mcharm * mlight * phik * thetak;
}

double EMDecayWidths::SPINFLIP_U3_1r_m0_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  k_value=0; alpha_lam=0; alpha_rho=0; mcharm=0; mlight=0; phik=0;  thetak=0;
  double value = 0;
  return value * k_value * alpha_lam * alpha_rho * mcharm * mlight * phik * thetak;
}

double EMDecayWidths::SPINFLIP_U3_1r_m1m_GS(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  k_value=0; alpha_lam=0; alpha_rho=0; mcharm=0; mlight=0; phik=0;  thetak=0;
  double value = 0;
  return value * k_value * alpha_lam * alpha_rho * mcharm * mlight * phik * thetak;
}

// ORBIT-SPLIT INTEGRALS
// U1_1lambda-1lambda
double EMDecayWidths::ORBITALSPLIT_U1_1l_m1_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = std::exp(value1 + value2) * (1 - value2 * std::pow(std::sin(thetak), 2)) ;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m1_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = 3. * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/ 16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m1_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = 2 * p_imag * phik;
  double value = 0.375 * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::pow(std::sin(thetak), 2)/ (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m0_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = (-1.0) * p_imag * phik;
  double value = 3. * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/ 16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m0_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = (((-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 4 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))) * std::pow(std::cos(thetak), 2) + 1) * k_value * std::exp(value1 + value2)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m0_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = (-1.0) * 0.1875 * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/(std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
} 

double EMDecayWidths::ORBITALSPLIT_U1_1l_m1m_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 2 * p_imag * phik;
  double value = 3 * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::pow(std::sin(thetak), 2)/ 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m1m_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = (-1.0) * p_imag * phik;
  double value = (-3.0) * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1l_m1m_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = (value2 * std::pow(std::sin(thetak), 2) + 1) * k_value * std::exp(value1 + value2)/ (4 * alpha_rho);
  return value;
}

// U2_1lambda-1lambda
double EMDecayWidths::ORBITALSPLIT_U2_1l_m1_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = std::exp(value1 + value2) * (1 - value2 * std::pow(std::sin(thetak), 2)) ;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m1_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8 * std::pow(alpha_rho, 2);
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = p_imag * phik;
  double value = 3. * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/ 16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m1_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 2 * p_imag * phik;
  double value = 0.375 * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::pow(std::sin(thetak), 2)/ (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m0_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = (-1.0) * p_imag * phik;
  double value = 3. * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/ 16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m0_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = (((-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 4 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))) * std::pow(std::cos(thetak), 2) + 1) * k_value * std::exp(value1 + value2)/ (4 * alpha_rho);
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m0_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = p_imag * phik;
  double value = (-1.0) * 0.1875 * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/(std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
} 

double EMDecayWidths::ORBITALSPLIT_U2_1l_m1m_1l_m1(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = 2 * p_imag * phik;
  double value = 3 * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::pow(std::sin(thetak), 2)/ (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m1m_1l_m0(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double phik, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / (8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value3 = (-1.0) * p_imag * phik;
  double value = (-3.0) * std::sqrt(2) * std::pow(mcharm, 2) * std::pow(k_value, 2) * std::exp(value1 + value2 + value3) * std::sin(2 * thetak)/(16 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1l_m1m_1l_m1m(double k_value, double alpha_lam, double alpha_rho,  double mcharm, double mlight, double thetak){
  double value1 = (-1.0) * std::pow(k_value, 2) / (8 * std::pow(alpha_rho, 2));
  double value2 = (-3.0) * std::pow(mcharm, 2) * std::pow(k_value, 2) / 8 * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = (value2 * std::pow(std::sin(thetak), 2) + 1) * k_value * std::exp(value1 + value2)/ (4 * alpha_rho);
  return value;
}


// New integrals
//U3 1lam->1lam;
double EMDecayWidths::ORBITALSPLIT_U3_1l_m1_1l_m1(double k_value, double alpha_lam, double mcharm, double mlight, double thetak){

  double value1 = (-3.) * std::pow(k_value,2) * std::pow(mlight,2) + 2 * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2)
    + 3 * std::pow(k_value,2) * std::pow(mlight,2) * std::pow(std::cos(thetak),2);
  double value2 =  (2.) * std::pow(alpha_lam,2) * std::exp((3 * std::pow(k_value,2) * std::pow(mlight,2))/(2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))) * std::pow(mcharm + 2 * mlight,2);
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U3_1l_m0_1l_m0(double k_value, double alpha_lam, double mcharm, double mlight, double thetak){
  double value1 = std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2) - 3 * std::pow(k_value,2) * std::pow(mlight,2) * std::pow(std::cos(thetak),2);
  double value2 = std::pow(alpha_lam,2) * std::exp((3 * std::pow(k_value,2) * std::pow(mlight,2)) / (2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))) * std::pow(mcharm + 2 * mlight,2);
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U3_1l_m1m_1l_m1m(double k_value, double alpha_lam, double mcharm, double mlight, double thetak){

  double value1 = -3 * std::pow(k_value,2) * std::pow(mlight,2) + 2 * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2) + 3 * std::pow(k_value,2) * std::pow(mlight,2) * std::pow(std::cos(thetak),2);
  double value2 = 2. * std::pow(alpha_lam,2) * std::exp((3 * std::pow(k_value,2) * std::pow(mlight,2))/(2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))) * std::pow(mcharm + 2 * mlight,2);
  double value = value1/value2;
  return value;
}

//U1 1lam->1rho
double EMDecayWidths::ORBITALSPLIT_U1_1l_m0_1r_m0(double k_value, double alpha_rho, double alpha_lam, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2) * mcharm * std::pow(std::cos(thetak),2);
  double value2 = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  double value2p = (4 * alpha_lam * alpha_rho * mcharm + 8 * alpha_lam * alpha_rho * mlight);
  value2 = value2 * value2p;
  double value = value1/value2;
  return (-1.0) * std::sqrt(3) * value;
}

//U2 1lam->1rho
double EMDecayWidths::ORBITALSPLIT_U2_1l_m0_1r_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2) * mcharm * std::pow(std::cos(thetak),2);
  double value2 = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  double value2p = 4 * alpha_lam * alpha_rho * mcharm + 8 * alpha_lam * alpha_rho * mlight;
  value2 = value2 * value2p;
  double value = value1/value2;
  return (-1.0) * std::sqrt(3) * value;
}


//U1 1rho->1rho
double EMDecayWidths::ORBITALSPLIT_U1_1r_m1_1r_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = 8 * std::pow(alpha_rho,2) - std::pow(k_value,2) + std::pow(k_value,2) * std::pow(std::cos(thetak),2);
  double value2 = 8. * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1r_m0_1r_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = 4 * std::pow(alpha_rho,2) - std::pow(k_value,2) * std::pow(std::cos(thetak),2);
  double value2 = 4. * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U1_1r_m1m_1r_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = 8 * std::pow(alpha_rho,2) - std::pow(k_value,2) + std::pow(k_value,2) * std::pow(std::cos(thetak),2);
  double value2 = 8. * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

//U2 1rho->1rho
double EMDecayWidths::ORBITALSPLIT_U2_1r_m1_1r_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 =(8 * std::pow(alpha_rho,2) - std::pow(k_value,2) + std::pow(k_value,2) * std::pow(std::cos(thetak),2));
  double value2 = 8. * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1r_m0_1r_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = (4 * std::pow(alpha_rho,2) - std::pow(k_value,2) * std::pow(std::cos(thetak),2));
  double value2 = 4. * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U2_1r_m1m_1r_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = 8 * std::pow(alpha_rho,2) - std::pow(k_value,2) + std::pow(k_value,2) * std::pow(std::cos(thetak),2);
  double value2 = 8 * std::pow(alpha_rho,2);
  double value2p = std::exp((std::pow(k_value,2) * (std::pow(alpha_rho,-2) + (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8.);
  value2 = value2 * value2p;
  double value = value1/value2;
  return value;
}

//U3 1rho->1rho
double EMDecayWidths::ORBITALSPLIT_U3_1r_m1_1r_m1(double k_value, double alpha_lam, double mcharm, double mlight){
  double value = std::exp((-3 * std::pow(k_value,2) * std::pow(mlight,2))/(2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2)));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U3_1r_m0_1r_m0(double k_value, double alpha_lam, double mcharm, double mlight){
  double value = std::exp((-3 * std::pow(k_value,2) * std::pow(mlight,2))/(2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2)));
  return value;
}

double EMDecayWidths::ORBITALSPLIT_U3_1r_m1m_1r_m1m(double k_value, double alpha_lam, double mcharm, double mlight){
  double value = std::exp((-3 * std::pow(k_value,2) * std::pow(mlight,2))/(2. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2)));
  return value;
}

//U1 1rho->1lam
double EMDecayWidths::ORBITALSPLIT_U1_1r_m0_1l_m0(double k_value, double alpha_lam, double alpha_rho,
						  double mcharm, double mlight, double thetak, double phik){
  double value1 = std::exp(-std::pow(k_value,2)/(8. * std::pow(alpha_rho,2)) -
			   (3 * std::pow(k_value,2) * std::pow(mcharm,2))/(8. * std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2)) + p_imag * phik);
  double value1p = std::pow(k_value,2) * mcharm * std::cos(thetak) * std::sin(thetak);
  value1 = value1 * value1p;
  double value2 = 4 * alpha_lam * alpha_rho * mcharm + 8 * alpha_lam * alpha_rho * mlight;
  double value = value1/value2;
  return std::sqrt(1.5) * value;
}

//U2 1rho->1lam
double EMDecayWidths::ORBITALSPLIT_U2_1r_m0_1l_m0(double k_value, double alpha_lam, double alpha_rho,
						  double mcharm, double mlight, double thetak, double phik){
  double value1 = std::exp(-(std::pow(k_value,2) * (std::pow(alpha_rho,-2) +
						    (3 * std::pow(mcharm,2))/(std::pow(alpha_lam,2) * std::pow(mcharm + 2 * mlight,2))))/8. + p_imag * phik);
  double value1p = std::pow(k_value,2) * mcharm * std::cos(thetak) * std::sin(thetak);
  value1 = value1 * value1p;
  double value2 = 4 * alpha_lam * alpha_rho * mcharm + 8 * alpha_lam * alpha_rho * mlight;
  double value = value1/value2;
  return -std::sqrt(1.5) * value;
}

//U1 2lam->gs (13.03.2023)
double EMDecayWidths::ORBITALSPLIT_U1_2l_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2)*std::pow(mcharm,2)*(1 + 3*std::cos(2*thetak));///
  double value2 = 16.*std::pow(alpha_lam,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value2p = std::pow(mcharm + 2*mlight,2);  
  value2 = value2 * value2p;
  double value = value1/value2;
  return (-1.0) * std::sqrt(3) * value;
}

//U2 2lam->gs
double EMDecayWidths::ORBITALSPLIT_U2_2l_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2)*std::pow(mcharm,2)*(1 + 3*std::cos(2*thetak));///
  double value2 = 16.*std::pow(alpha_lam,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value2p = std::pow(mcharm + 2*mlight,2);
  value2 = value2 * value2p;
  double value = value1/value2;
  return (-1.0) * std::sqrt(3) * value;
}

// U3 2lam->gs
double EMDecayWidths::ORBITALSPLIT_U3_2l_m0_GS(double k_value, double alpha_lam, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value, 2)*std::pow(mlight, 2)*(1 + 3.*std::cos(2.*thetak) );
  double value2 = 4.*std::pow(alpha_lam, 2)*std::exp((3.*std::pow(k_value,2)*std::pow(mlight, 2))/(2.*std::pow(alpha_lam, 2)*std::pow(mcharm + 2.*mlight, 2)));
  double value2p = std::pow(mcharm + 2.*mlight, 2);
  value2 = value2 * value2p;
  double value = value1/value2;
  return (-1.0) * std::sqrt(3.) * value;  
}

// U1 2rho->gs
double EMDecayWidths::ORBITALSPLIT_U1_2r_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2)*(1 - 3*std::pow(std::cos(thetak),2));///
  double value2 = 8.*std::sqrt(3)*std::pow(alpha_rho,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value = value1/value2;
  return value;
}

// U2 2rho->gs
double EMDecayWidths::ORBITALSPLIT_U2_2r_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight, double thetak){
  double value1 = std::pow(k_value,2)*(1 - 3*std::pow(std::cos(thetak),2));///
  double value2 = 8.*std::sqrt(3)*std::pow(alpha_rho,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value = value1/value2;
  return value;
}
  
// U1 1nlam->gs
double EMDecayWidths::ORBITALSPLIT_U1_1nl_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = std::pow(k_value,2)*std::pow(mcharm,2);///
  double value2 = 4.*std::pow(alpha_lam,2) * std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value2p = std::pow(mcharm + 2*mlight,2);
  value2 = value2 * value2p;
  double value = value1/value2;
  return std::sqrt(1.5)*value;
}

// U2 1nlam->gs
double EMDecayWidths::ORBITALSPLIT_U2_1nl_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = std::pow(k_value,2)*std::pow(mcharm,2);///  
  double value2 = 4.*std::pow(alpha_lam,2) * std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value2p = std::pow(mcharm + 2*mlight,2);
  value2 = value2 * value2p;
  double value = value1/value2;
  return std::sqrt(1.5)*value;
}

// U3 1nlam->gs
double EMDecayWidths::ORBITALSPLIT_U3_1nl_m0_GS(double k_value, double alpha_lam, double mcharm, double mlight){
  double value1 = std::pow(k_value,2)*std::pow(mlight,2);///
  double value2 = std::pow(alpha_lam,2)*std::exp((3*std::pow(k_value,2)*std::pow(mlight,2))/(2.*std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2)));
  double value2p = std::pow(mcharm + 2*mlight,2);
  value2 = value2 * value2p;
  double value = value1/value2;
  return std::sqrt(1.5)*value;
}


// U1 1nrho->gs
double EMDecayWidths::ORBITALSPLIT_U1_1nr_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = std::pow(k_value,2);///
  double value2 = 4.*std::sqrt(6.)*std::pow(alpha_rho,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value = value1/value2;
  return value;
}

// U2 1nrho->gs
double EMDecayWidths::ORBITALSPLIT_U2_1nr_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = std::pow(k_value,2);///
  double value2 = 4.*std::sqrt(6.)*std::pow(alpha_rho,2)*std::exp((std::pow(k_value,2)*(std::pow(alpha_rho,-2) + (3*std::pow(mcharm,2))/(std::pow(alpha_lam,2)*std::pow(mcharm + 2*mlight,2))))/8.);
  double value = value1/value2;
  return value;
}

//Tensor operators
//T1l
double EMDecayWidths::T1l(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik, double mLlA){
  double value1 = ORBITALSPLIT_U1_1l_m1_1l_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, phik, thetak);
  double value2 = ORBITALSPLIT_U1_2l_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value3 = SPINFLIP_U1_GS_GS(k_value, alpha_lam, alpha_rho,  mcharm, mlight);
  double value4 = ORBITALSPLIT_U1_1nl_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value = value1 + std::sqrt(1./3.) * value2 +  value3 +  std::sqrt(2./3.) * value4;
  return p_imag * std::sqrt(1./6.) * alpha_lam * value;
}

//T2l
double EMDecayWidths::T2l(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik, double mLlA){
  double value1 = ORBITALSPLIT_U2_1l_m1_1l_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value2 = ORBITALSPLIT_U2_2l_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value3 = SPINFLIP_U2_GS_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value4 = ORBITALSPLIT_U2_1nl_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value = value1 + std::sqrt(1/3) * value2 +  value3 +  std::sqrt(2/3) * value4;
  return p_imag * std::sqrt(1./6.) * alpha_lam * value;
}

//T3l
double EMDecayWidths::T3l(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik, double mLlA){
  double value1 = ORBITALSPLIT_U3_1l_m1_1l_m1(k_value, alpha_lam, mcharm, mlight, thetak);
  double value2 = ORBITALSPLIT_U3_2l_m0_GS(k_value, alpha_lam, mcharm, mlight, thetak);
  double value3 = SPINFLIP_U3_GS_GS(k_value, alpha_lam, mcharm, mlight);
  double value4 = ORBITALSPLIT_U3_1nl_m0_GS(k_value, alpha_lam, mcharm, mlight);
  double value = value1 + std::sqrt(1./3.) * value2 +  value3 +  std::sqrt(2./3.) * value4;
  return (-1.0) * p_imag * std::sqrt(2./3.) * alpha_lam * value;
}

//T1r
double EMDecayWidths::T1r(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik, double mLrA){
  double value1 = ORBITALSPLIT_U1_1r_m1_1r_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value2 = ORBITALSPLIT_U1_2r_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value3 = SPINFLIP_U1_GS_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value4 = ORBITALSPLIT_U1_1nr_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value = value1 + std::sqrt(1./3.) * value2 +  value3 +  std::sqrt(2./3.) * value4;
  return p_imag * std::sqrt(1./2.) * alpha_rho * value;
}

//T2r
double EMDecayWidths::T2r(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik, double mLrA){
  double value1 = ORBITALSPLIT_U2_1r_m1_1r_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value2 = ORBITALSPLIT_U2_2r_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak);
  double value3 = SPINFLIP_U2_GS_GS(k_value, alpha_lam, alpha_rho,  mcharm, mlight);
  double value4 = ORBITALSPLIT_U2_1nr_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight);
  double value = value1 + std::sqrt(1./3.) * value2 +  value3 +  std::sqrt(2./3.) * value4;
  return (-1.0) * p_imag * std::sqrt(1./2.) * alpha_rho * value;
}

//T3r
double EMDecayWidths::T3r(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-wave lambda to P-wave lambda
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_l2_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3.) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_l2_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * std::pow(k_value, 2) * std::pow(mcharm, 2) - 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * k_value * mcharm * value4 * std::exp(value1 * (value2 + value3)))/(8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 3)));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_l2_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3.) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_l2_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3.) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_l2_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * std::pow(k_value, 2) * std::pow(mcharm, 2) - 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * k_value * mcharm * value4 * std::exp(value1 * (value2 + value3)))/(8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 3)));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_l2_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3.) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_l2_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * std::sqrt(3.) * k_value * mlight * std::exp(value1))/(alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_l2_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value2 = (3. * std::pow(k_value, 2) * std::pow(mlight, 2) - 2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-1.0) * p_imag * k_value * mlight * value2 * std::exp(value1))/(std::pow(alpha_lam * (mcharm + 2. * mlight), 3));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_l2_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * std::sqrt(3.) * k_value * mlight * std::exp(value1))/(alpha_lam * (mcharm + 2. * mlight));
  return value;
}

// ORBIT-FLIP Tensor operators
//T1l2m2l1m1
double EMDecayWidths::T1_l2_m2_l1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = (2. * p_imag * alpha_lam * std::exp(value1 * (value2 + value3)))/(std::sqrt(3.));
  return value;
}

//T1l2m1l1m0
double EMDecayWidths::T1_l2_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value5  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = (p_imag * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6.) * value5);
  return value;
}

//T1l2m0l1m1m
double EMDecayWidths::T1_l2_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value5  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = (p_imag * value4 * std::exp(value1 * (value2 + value3)))/(6. * std::sqrt(2.) * value5);
  return value;
}

//T2l2m2l1m1
double EMDecayWidths::T2_l2_m2_l1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = (2. * p_imag * alpha_lam * std::exp(value1 * (value2 + value3)))/(std::sqrt(3.));
  return value;
}

//T2l2m1l1m0
double EMDecayWidths::T2_l2_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value5  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = (p_imag * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6.) * value5);
  return value;
}

//T2l2m0l1m1m
double EMDecayWidths::T2_l2_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value5  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = (p_imag * value4 * std::exp(value1 * (value2 + value3)))/(6. * std::sqrt(2.) * value5);
  return value;
}

//T3l2m2l1m1
double EMDecayWidths::T3_l2_m2_l1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-4.0) * p_imag * alpha_lam * std::exp(value1))/(std::sqrt(3.));
  return value;
}

//T3l2m1l1m0
double EMDecayWidths::T3_l2_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value2 = ((std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mlight, 2));
  double value3  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = ((-2.0) * p_imag * std::sqrt(2. / 3.) * value2 * std::exp(value1))/(value3);
  return value;
}

//T3l2m0l1m1m
double EMDecayWidths::T3_l2_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value2 = ((std::pow(alpha_lam * (mcharm + 2. * mlight), 2)) - 3. * std::pow(k_value, 2) * std::pow(mlight, 2));
  double value3  = (alpha_lam * std::pow((mcharm + 2. * mlight), 2));
  double value = ((-2.0) * p_imag * std::sqrt(2.) * value2 * std::exp(value1))/(3. * value3);
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-wave rho to P-wave rho
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r2_m1_r1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r2_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * (std::pow(k_value, 2) - 8. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(8. * std::sqrt(3.) * std::pow(alpha_rho,3));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r2_m1m_r1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r2_m1_r1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r2_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * (std::pow(k_value, 2) - 8. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(8. * std::sqrt(3.) * std::pow(alpha_rho,3));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r2_m1m_r1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r2_m1_r1_m1(){
  double value = 0;
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r2_m0_r1_m0(){
  double value = 0;
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r2_m1m_r1_m1m(){
  double value = 0;
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r2m2r1m1
double EMDecayWidths::T1_r2_m2_r1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = (2. * p_imag * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T1r2m1r1m0
double EMDecayWidths::T1_r2_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * (std::pow(k_value, 2) - 4. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho);
  return value;
}

//T1r2m0r1m1m
double EMDecayWidths::T1_r2_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * (std::pow(k_value, 2) - 4. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6.) * alpha_rho);
  return value;
}

//T2r2m2r1m1
double EMDecayWidths::T2_r2_m2_r1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-2.0) * p_imag * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T2r2m1r1m0
double EMDecayWidths::T2_r2_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * (std::pow(k_value, 2) - 4. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho);
  return value;
}

//T2r2m0r1m1m
double EMDecayWidths::T2_r2_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * (std::pow(k_value, 2) - 4. * std::pow(alpha_rho,2)) * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6.) * alpha_rho);
  return value;
}

//T3r2m2r1m1
double EMDecayWidths::T3_r2_m2_r1_m1(){
  double value = 0;
  return value;
}

//T3r2m1r1m0
double EMDecayWidths::T3_r2_m1_r1_m0(){
  double value = 0;
  return value;
}

//T3r2m0r1m1m
double EMDecayWidths::T3_r2_m0_r1_m1m(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-wave lambda to P-wave rho
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_l2_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(3) * std::pow(k_value, 3) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(8. * alpha_rho * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_l2_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3) * std::pow(k_value, 3) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(8. * alpha_rho * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_l2_m0_r1_m0(){
  double value = 0;
  return value;
}


// ORBIT-FLIP Tensor operators
//T1l2m0r1m1m
double EMDecayWidths::T1_l2_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
				      double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * alpha_rho * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(2. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T1l2m1r1m0
double EMDecayWidths::T1_l2_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
				     double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T2l2m0r1m1m
double EMDecayWidths::T2_l2_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(1.5) * alpha_rho * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(2. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T2l2m1r1m0
double EMDecayWidths::T2_l2_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T3l2m0r1m1m
double EMDecayWidths::T3_l2_m0_r1_m1m(){
  double value = 0;
  return value;
}

//T3l2m1r1m0
double EMDecayWidths::T3_l2_m1_r1_m0(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-wave rho to P-wave lambda
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r2_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(k_value, 3) * mcharm * std::exp(value1 * (value2 + value3)))/(8. * std::pow(alpha_rho, 2) * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r2_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(k_value, 3) * mcharm * std::exp(value1 * (value2 + value3)))/(8. * std::pow(alpha_rho, 2) * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r2_m0_l1_m0(){
  double value = 0;
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r2m0l1m1m
double EMDecayWidths::T1_r2_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * alpha_lam * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/(6. * std::sqrt(2) * std::pow(alpha_rho, 2));
  return value;
}

//T1r2m1l1m0
double EMDecayWidths::T1_r2_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T2r2m0l1m1m
double EMDecayWidths::T2_r2_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * alpha_lam * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/(6. * std::sqrt(2) * std::pow(alpha_rho, 2));
  return value;
}

//T2r2m1l1m0
double EMDecayWidths::T2_r2_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T3r2m0l1m1m
double EMDecayWidths::T3_r2_m0_l1_m1m(){
  double value = 0;
  return value;
}

//T3r2m1l1m0
double EMDecayWidths::T3_r2_m1_l1_m0(){
  double value = 0;
  return value;
}


//Definitions of the Integrals and Tensor Operators for decays from Mixed to P-wave rho
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r1_m1_l1_m0_r1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r1_m0_l1_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (std::pow(k_value, 2) - 4. * std::pow(alpha_rho, 2));
  double value = ( p_imag * std::sqrt(3) * k_value *  mcharm * value4 * std::exp(value1 * (value2 + value3)))/(8. * std::pow(alpha_rho, 2) * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r1_m1m_l1_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m1_l1_m0_r1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m0_l1_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (std::pow(k_value, 2) - 4. * std::pow(alpha_rho, 2));
  double value = ( p_imag * std::sqrt(3) * k_value *  mcharm * value4 * std::exp(value1 * (value2 + value3)))/(8. * std::pow(alpha_rho, 2) * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m1m_l1_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3) * k_value * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m1_l1_m0_r1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * std::sqrt(3.) * k_value * mlight * std::exp(value1))/(alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m0_l1_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * std::sqrt(3.) * k_value * mlight * std::exp(value1))/(alpha_lam * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m1m_l1_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-3.0) * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( p_imag * std::sqrt(3.) * k_value * mlight * std::exp(value1))/(alpha_lam * (mcharm + 2. * mlight));
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r1m0l1m0r1m1m
double EMDecayWidths::T1_r1_m0_l1_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T1r1m1l1m0r1m0
double EMDecayWidths::T1_r1_m1_l1_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T1r1m1l1m1r1m1
double EMDecayWidths::T1_r1_m1_l1_m1_r1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(2./3., 0.5) * alpha_lam * std::exp(value1 * (value2 + value3)));
  return value;
}

//T1r1m0l1m1r1m0
double EMDecayWidths::T1_r1_m0_l1_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (std::pow(k_value, 2) - 4. * std::pow(alpha_rho, 2));
  double value = ( (-1.0) * p_imag * alpha_lam * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6) * std::pow(alpha_rho, 2));
  return value;
}

//T1r1m1ml1m1r1m1m
double EMDecayWidths::T1_r1_m1_ml_1m_1r_1m_1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(2./3., 0.5) * alpha_lam * std::exp(value1 * (value2 + value3)));
  return value;
}

//T2r1m0l1m0r1m1m
double EMDecayWidths::T2_r1_m0_l1_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T2r1m1l1m0r1m0
double EMDecayWidths::T2_r1_m1_l1_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T2r1m1l1m1r1m1
double EMDecayWidths::T2_r1_m1_l1_m1_r1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(2./3., 0.5) * alpha_lam * std::exp(value1 * (value2 + value3)));
  return value;
}

//T2r1m0l1m1r1m0
double EMDecayWidths::T2_r1_m0_l1_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (std::pow(k_value, 2) - 4. * std::pow(alpha_rho, 2));
  double value = ( (-1.0) * p_imag * alpha_lam * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(6) * std::pow(alpha_rho, 2));
  return value;
}

//T2r1m1ml1m1r1m1m
double EMDecayWidths::T2_r1_m1_ml_1m_1r_1m_1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(2./3., 0.5) * alpha_lam * std::exp(value1 * (value2 + value3)));
  return value;
}

//T3r1m0l1m0r1m1m
double EMDecayWidths::T3_r1_m0_l1_m0_r1_m1m(){
  double value = 0;
  return value;
}

//T3r1m1l1m0r1m0
double EMDecayWidths::T3_r1_m1_l1_m0_r1_m0(){
  double value = 0;
  return value;
}

//T3r1m1l1m1r1m1
double EMDecayWidths::T3_r1_m1_l1_m1_r1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-2.0) * p_imag * std::sqrt(2. / 3.) * alpha_lam * std::exp(value1));
  return value;
}

//T3r1m0l1m1r1m0
double EMDecayWidths::T3_r1_m0_l1_m1_r1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-2.0) * p_imag * std::sqrt(2. / 3.) * alpha_lam * std::exp(value1));
  return value;
}

//T3r1m1ml1m1r1m1m
double EMDecayWidths::T3_r1_m1_ml_1m_1r_1m_1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-2.0) * p_imag * std::sqrt(2. / 3.) * alpha_lam * std::exp(value1));
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Mixed to P-wave lambda
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r1_m0_l1_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r1_m0_l1_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * std::pow(k_value, 2) * std::pow(mcharm, 2) - 4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = ( p_imag * k_value * value4 * std::exp(value1 * (value2 + value3)))/(8. * alpha_rho * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::SPINFLIP_U1_r1_m0_l1_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m0_l1_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m0_l1_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * std::pow(k_value, 2) * std::pow(mcharm, 2) - 4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value = ( (-1.0) * p_imag * k_value * value4 * std::exp(value1 * (value2 + value3)))/(8. * alpha_rho * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m0_l1_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * std::exp(value1 * (value2 + value3)))/(2. * alpha_rho);
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m0_l1_m1_l1_m1(){
  double value = 0;
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m0_l1_m0_l1_m0(){
  double value = 0;
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m0_l1_m1m_l1_m1m(){
  double value = 0;
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r1m0l1m0l1m1m
double EMDecayWidths::T1_r1_m0_l1_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T1r1m0l1m1l1m0
double EMDecayWidths::T1_r1_m0_l1_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T1r1m1l1m1l1m1
double EMDecayWidths::T1_r1_m1_l1_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(2.) * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T1r1m1l1m0l1m0
double EMDecayWidths::T1_r1_m1_l1_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value = ( p_imag * alpha_rho * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2) * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T1r1m1l1m1ml1m1m
double EMDecayWidths::T1_r1_m1_l1_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(2) * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T2r1m0l1m0l1m1m
double EMDecayWidths::T2_r1_m0_l1_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T2r1m0l1m1l1m0
double EMDecayWidths::T2_r1_m0_l1_m1_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2.) * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

//T2r1m1l1m1l1m1
double EMDecayWidths::T2_r1_m1_l1_m1_l1_m1(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(2.) * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T2r1m1l1m0l1m0
double EMDecayWidths::T2_r1_m1_l1_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2) - 3. * std::pow(k_value, 2) * std::pow(mcharm, 2));
  double value = ( (-1.0) * p_imag * alpha_rho * value4 * std::exp(value1 * (value2 + value3)))/(2. * std::sqrt(2) * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T2r1m1l1m1ml1m1m
double EMDecayWidths::T2_r1_m1_l1_m1m_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( (-1.0) * p_imag * std::sqrt(2) * alpha_rho * std::exp(value1 * (value2 + value3)));
  return value;
}

//T3r1m0l1m0l1m1m
double EMDecayWidths::T3_r1_m0_l1_m0_l1_m1m(){
  double value = 0;
  return value;
}

//T3r1m0l1m1l1m0
double EMDecayWidths::T3_r1_m0_l1_m1_l1_m0(){
  double value = 0;
  return value;
}

//T3r1m1l1m1l1m1
double EMDecayWidths::T3_r1_m1_l1_m1_l1_m1(){
  double value = 0;
  return value;
}

//T3r1m1l1m0l1m0
double EMDecayWidths::T3_r1_m1_l1_m0_l1_m0(){
  double value = 0;
  return value;
}

//T3r1m1l1m1ml1m1m
double EMDecayWidths::T3_r1_m1_l1_m1m_l1_m1m(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-lambda to ground state
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_l2_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::sqrt(3) * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_l2_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::sqrt(3) * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(4. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_l2_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ((-1.0) * std::sqrt(3) * std::pow(k_value, 2) * std::pow(mlight, 2) * std::exp(value1))/ (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

// ORBIT-FLIP Tensor operators
//T1rl2m1GS
double EMDecayWidths::T1_l2_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( k_value * mcharm * std::exp(value1 * (value2 + value3)))/(std::sqrt(2.) * (mcharm + 2. * mlight));
  return value;
}

//T2rl2m1GS
double EMDecayWidths::T2_l2_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( k_value * mcharm * std::exp(value1 * (value2 + value3)))/(std::sqrt(2.) * (mcharm + 2. * mlight));
  return value;
}

//T3rl2m1GS
double EMDecayWidths::T3_l2_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( 2. * std::sqrt(2) * k_value * mlight * std::exp(value1))/ (mcharm + 2. * mlight);
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from D-rho to ground state
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r2_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(3) * std::pow(alpha_rho, 2));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r2_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(3) * std::pow(alpha_rho, 2));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r2_m0_GS(){
  double value = 0;
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r2m1GS
double EMDecayWidths::T1_r2_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( k_value * std::exp(value1 * (value2 + value3)))/ (std::sqrt(2));
  return value;
}

//T2r2m1GS
double EMDecayWidths::T2_r2_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( k_value * std::exp(value1 * (value2 + value3)))/ (std::sqrt(2));
  return value;
}

//T3r2m1GS
double EMDecayWidths::T3_r2_m1_GS(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Mixed to ground state
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_r1_m0_l1_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::sqrt(3) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/ (4. * alpha_lam * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U2_r1_m0_l1_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::sqrt(3) * std::pow(k_value, 2) * mcharm * std::exp(value1 * (value2 + value3)))/ (4. * alpha_lam * alpha_rho * (mcharm + 2. * mlight));
  return value;
}

double EMDecayWidths::SPINFLIP_U3_r1_m0_l1_m0_GS(){
  double value = 0;
  return value;
}

// ORBIT-FLIP Tensor operators
//T1r1m1l1m0GS
double EMDecayWidths::T1_r1_m1_l1_m0_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::sqrt(1.5) * alpha_rho * k_value * mcharm * std::exp(value1 * (value2 + value3)))/ (alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T1r1m0l1m1GS
double EMDecayWidths::T1_r1_m0_l1_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( alpha_lam * k_value * std::exp(value1 * (value2 + value3)))/ (std::sqrt(6) * alpha_rho);
  return value;
}

//T2r1m1l1m0GS
double EMDecayWidths::T2_r1_m1_l1_m0_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * std::sqrt(1.5) * alpha_rho * k_value * mcharm * std::exp(value1 * (value2 + value3)))/ (alpha_lam * (mcharm + 2. * mlight));
  return value;
}

//T2r1m0l1m1GS
double EMDecayWidths::T2_r1_m0_l1_m1_GS(double k_value, double alpha_lam, double alpha_rho,
			  double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * alpha_lam * k_value * std::exp(value1 * (value2 + value3)))/ (std::sqrt(6) * alpha_rho);
  return value;
}

//T3r1m1l1m0GS
double EMDecayWidths::T3_r1_m1_l1_m0_GS(){
  double value = 0;
  return value;
}

//T3r1m0l1m1GS
double EMDecayWidths::T3_r1_m0_l1_m1_GS(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial lambda to ground state
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nl1_l0_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::sqrt(1.5) * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nl1_l0_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::sqrt(1.5) * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nl1_l0_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value = ( std::sqrt(1.5) * std::pow(k_value, 2) * std::pow(mlight, 2) * std::exp(value1))/ (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial rho to ground state
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nr1_r0_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(6.) * std::pow(alpha_rho, 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nr1_r0_m0_GS(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(6.) * std::pow(alpha_rho, 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nr1_r0_m0_GS(){
  double value = 0; 
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial lambda to P wave lambda
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nl1_l0_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * (std::pow(k_value, 2) * std::pow(mcharm, 2)) - 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ((-1.0) * p_imag * k_value  * mcharm * value4 * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(2.) * std::pow(alpha_lam * (mcharm + 2. * mlight), 3)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nl1_l0_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * (std::pow(k_value, 2) * std::pow(mcharm, 2)) - 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ((-1.0) * p_imag * k_value  * mcharm * value4 * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(2.) * std::pow(alpha_lam * (mcharm + 2. * mlight), 3)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nl1_l0_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2)));
  double value2 = (3. * (std::pow(k_value, 2) * std::pow(mlight, 2)) - 2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ( p_imag * k_value  * mlight * value2 * std::exp(value1))/ (std::sqrt(2.) * std::pow(alpha_lam * (mcharm + 2. * mlight), 3)); 
  return value;
}

// ORBIT-FLIP Tensor operators
//T1nl1l0m0l1m1m
double EMDecayWidths::T1_nl1_l0_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * (std::pow(k_value, 2) * std::pow(mcharm, 2)) + 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ( p_imag * value4 * std::exp(value1 * (value2 + value3)))/ (12. * alpha_lam * std::pow((mcharm + 2. * mlight), 2)); 
  return value;
}

//T2nl1l0m0l1m1m
double EMDecayWidths::T2_nl1_l0_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = (3. * (std::pow(k_value, 2) * std::pow(mcharm, 2)) + 8. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ( p_imag * value4 * std::exp(value1 * (value2 + value3)))/ (12. * alpha_lam * std::pow((mcharm + 2. * mlight), 2)); 
  return value;
}

//T3nl1l0m0l1m1m
double EMDecayWidths::T3_nl1_l0_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = ((-1.0) * 3. * std::pow(k_value, 2) * std::pow(mlight, 2)) / (2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value2 = (3. * (std::pow(k_value, 2) * std::pow(mlight, 2)) + 2. * (std::pow(alpha_lam * (mcharm + 2. * mlight), 2))); 
  double value = ((-2.0) * p_imag * value2 * std::exp(value1))/ (3. * alpha_lam * std::pow((mcharm + 2. * mlight), 2)); 
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial lambda to P wave rho
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nl1_l0_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(1.5) * std::pow(k_value, 3)  * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/ (8. * alpha_rho *  std::pow(alpha_lam * (mcharm + 2. * mlight), 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nl1_l0_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(1.5) * std::pow(k_value, 3)  * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/ (8. * alpha_rho *  std::pow(alpha_lam * (mcharm + 2. * mlight), 2)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nl1_l0_m0_r1_m0(){
  double value = 0; 
  return value;
}

// ORBIT-FLIP Tensor operators
//T1nl1l0m0r1m1m
double EMDecayWidths::T1_nl1_l0_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * std::sqrt(3.) * alpha_rho * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T2nl1l0m0r1m1m
double EMDecayWidths::T2_nl1_l0_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::sqrt(3.) * alpha_rho * std::pow(k_value, 2) * std::pow(mcharm, 2) * std::exp(value1 * (value2 + value3)))/(4. * std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  return value;
}

//T3nl1l0m0r1m1m
double EMDecayWidths::T3_nl1_l0_m0_r1_m1m(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial rho to P wave lambda
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nr1_r0_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::pow(k_value, 3)  * mcharm * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(2.) * alpha_lam * std::pow(alpha_rho, 2) * (mcharm + 2. * mlight)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nr1_r0_m0_l1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * std::pow(k_value, 3)  * mcharm * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(2.) * alpha_lam * std::pow(alpha_rho, 2) * (mcharm + 2. * mlight)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nr1_r0_m0_l1_m0(){
  double value = 0; 
  return value;
}

// ORBIT-FLIP Tensor operators
//T1nr1r0m0l1m1m
double EMDecayWidths::T1_nr1_r0_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * alpha_lam * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/(12. * std::pow(alpha_rho, 2));
  return value;
}

//T2nr1r0m0l1m1m
double EMDecayWidths::T2_nr1_r0_m0_l1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value = ( p_imag * alpha_lam * std::pow(k_value, 2) * std::exp(value1 * (value2 + value3)))/(12. * std::pow(alpha_rho, 2));
  return value;
}

//T3nr1r0m0l1m1m
double EMDecayWidths::T3_nr1_r0_m0_l1_m1m(){
  double value = 0;
  return value;
}

//Definitions of the Integrals and Tensor Operators for decays from Radial rho to P rho
// SPIN-FLIP INTEGRALS
double EMDecayWidths::SPINFLIP_U1_nr1_r0_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = std::pow(k_value, 2) - 8. * std::pow(alpha_rho, 2);
  double value = ((-1.0) * p_imag * k_value * value4 * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(6.) * std::pow(alpha_rho, 3)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U2_nr1_r0_m0_r1_m0(double k_value, double alpha_lam, double alpha_rho, double mcharm, double mlight){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = std::pow(k_value, 2) - 8. * std::pow(alpha_rho, 2);
  double value = ( p_imag * k_value * value4 * std::exp(value1 * (value2 + value3)))/ (8. * std::sqrt(6.) * std::pow(alpha_rho, 3)); 
  return value;
}

double EMDecayWidths::SPINFLIP_U3_nr1_r0_m0_r1_m0(){
  double value = 0; 
  return value;
}

// ORBIT-FLIP Tensor operators
//T1nr1r0m0r1m1m
double EMDecayWidths::T1_nr1_r0_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = 8. * std::pow(alpha_rho, 2) + std::pow(k_value, 2);
  double value = ( p_imag * value4 * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(3.) * alpha_rho); 
  return value;
}

//T2nr1r0m0r1m1m
double EMDecayWidths::T2_nr1_r0_m0_r1_m1m(double k_value, double alpha_lam, double alpha_rho,
        double mcharm, double mlight, double thetak, double phik){
  double value1 = (-1.0) * std::pow(k_value, 2) / 8.;
  double value2 = (3. * std::pow(mcharm, 2)) / (std::pow(alpha_lam * (mcharm + 2. * mlight), 2));
  double value3 = 1./std::pow(alpha_rho, 2);
  double value4 = 8. * std::pow(alpha_rho, 2) + std::pow(k_value, 2);
  double value = ((-1.0) * p_imag * value4 * std::exp(value1 * (value2 + value3)))/ (4. * std::sqrt(3.) * alpha_rho); 
  return value;
}

//T3nr1r0m0r1m1m
double EMDecayWidths::T3_nr1_r0_m0_r1_m1m(){
  double value = 0; 
  return value;
}


#endif

  // Definitions of the Integrals and Tensor Operators for decays from D-wave lambda to P-wave lambda
  //std::cout<<T1_l2_m2_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T1_l2_m2_l1_m1(k_"<<std::endl;
  //std::cout<<T1_l2_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T1_l2_m1_l1_m0(k_"<<std::endl;
  //std::cout<<T1_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho,mcharm, mlight, thetak, phik)<<"    T1_l2_m0_l1_m1m(k"<<std::endl;
  //std::cout<<T2_l2_m2_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T2_l2_m2_l1_m1(k_"<<std::endl;
  //std::cout<<T2_l2_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T2_l2_m1_l1_m0(k_"<<std::endl;
  //std::cout<<T2_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho,mcharm, mlight, thetak, phik)<<"    T2_l2_m0_l1_m1m(k"<<std::endl;
  //std::cout<<T3_l2_m2_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T3_l2_m2_l1_m1(k_"<<std::endl;
  //std::cout<<T3_l2_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T3_l2_m1_l1_m0(k_"<<std::endl;
  //std::cout<<T3_l2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak,phik)<<"    T3_l2_m0_l1_m1m(k"<<std::endl;
  //std::cout<<SPINFLIP_U1_l2_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U1_l2_m1_l1_m1(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U1_l2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U1_l2_m0_l1_m0(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U1_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  <<"    SPINFLIP_U1_l2_m1m_l1_m1m(k"<<std::endl;
  //std::cout<<SPINFLIP_U2_l2_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U2_l2_m1_l1_m1(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U2_l2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U2_l2_m0_l1_m0(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U2_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  <<"    SPINFLIP_U2_l2_m1m_l1_m1m(k"<<std::endl;
  //std::cout<<SPINFLIP_U3_l2_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U3_l2_m1_l1_m1(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U3_l2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)    <<"    SPINFLIP_U3_l2_m0_l1_m0(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U3_l2_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)  <<"    SPINFLIP_U3_l2_m1m_l1_m1m(k"<<std::endl;

  
  // // Definitions of the Integrals and Tensor Operators for decays from D-wave rho to P-wave rho
  // // SPIN-FLIP INTEGRALS
  //std::cout<<SPINFLIP_U1_r2_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight) <<" SPINFLIP_U1_r2_m1_r1_m1 "<<std::endl;
  //std::cout<<SPINFLIP_U1_r2_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight) <<" SPINFLIP_U1_r2_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U1_r2_m1m_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_r2_m1m_r1_m1m "<<std::endl;
  //std::cout<<SPINFLIP_U2_r2_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r2_m1_r1_m1 "<<std::endl;
  //std::cout<<SPINFLIP_U2_r2_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r2_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_r2_m1m_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r2_m1m_r1_m1m "<<std::endl;
  //std::cout<<SPINFLIP_U3_r2_m1_r1_m1()<<" SPINFLIP_U3_r2_m1_r1_m1 "<<std::endl;
  //std::cout<<SPINFLIP_U3_r2_m0_r1_m0()<<" SPINFLIP_U3_r2_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U3_r2_m1m_r1_m1m()<<" SPINFLIP_U3_r2_m1m_r1_m1m "<<std::endl;
  
  // // ORBIT-FLIP Tensor operators D_rho->P_rho
  //std::cout<<T1_r2_m2_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r2_m2_r1_m1 "<<std::endl;
  //std::cout<<T1_r2_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r2_m1_r1_m0 "<<std::endl;
  //std::cout<<T1_r2_m0_r1_m1m(k_value, alpha_lam, alpha_rho,mcharm, mlight, thetak, phik)<<" T1_r2_m0_r1_m1m "<<std::endl;
  //std::cout<<T2_r2_m2_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r2_m2_r1_m1 "<<std::endl;
  //std::cout<<T2_r2_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r2_m1_r1_m0 "<<std::endl;
  //std::cout<<T2_r2_m0_r1_m1m(k_value, alpha_lam, alpha_rho,mcharm, mlight, thetak, phik)<<" T2_r2_m0_r1_m1m "<<std::endl;  


  ////Definitions of the Integrals and Tensor Operators for decays from D-wave lambda to P-wave rho
  //std::cout<<T1_l2_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_l2_m0_r1_m1m "<<std::endl;
  //std::cout<<T1_l2_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_l2_m1_r1_m0 "<<std::endl;
  //std::cout<<T2_l2_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_l2_m0_r1_m1m "<<std::endl;
  //std::cout<<T2_l2_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_l2_m1_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U1_l2_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_l2_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_l2_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_l2_m0_r1_m0 "<<std::endl;

  // //Definitions of the Integrals and Tensor Operators for decays from D-wave rho to P-wave lambda
  //std::cout<<T1_r2_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r2_m1_l1_m0 "<<std::endl;
  //std::cout<<T1_r2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r2_m0_l1_m1m "<<std::endl;
  //std::cout<<T2_r2_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r2_m1_l1_m0 "<<std::endl;
  //std::cout<<T2_r2_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r2_m0_l1_m1m "<<std::endl;
  //std::cout<<SPINFLIP_U1_r2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_r2_m0_l1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_r2_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r2_m0_l1_m0 "<<std::endl;



  // //Definitions of the Integrals and Tensor Operators for decays from Mixed to P-wave rho
  //std::cout<<T1_r1_m0_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)     <<"   T1_r1_m0_l1_m0_r1_m1m(k_value, "<<std::endl;
  //std::cout<<T1_r1_m1_l1_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T1_r1_m1_l1_m0_r1_m0(k_value, a"<<std::endl;
  //std::cout<<T1_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T1_r1_m1_l1_m1_r1_m1(k_value, a"<<std::endl;
  //std::cout<<T1_r1_m0_l1_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T1_r1_m0_l1_m1_r1_m0(k_value, a"<<std::endl;
  //std::cout<<T1_r1_m1_ml_1m_1r_1m_1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)   <<"   T1_r1_m1_ml_1m_1r_1m_1m(k_value"<<std::endl;
  //std::cout<<T2_r1_m0_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)     <<"   T2_r1_m0_l1_m0_r1_m1m(k_value, "<<std::endl;
  //std::cout<<T2_r1_m1_l1_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T2_r1_m1_l1_m0_r1_m0(k_value, a"<<std::endl;
  //std::cout<<T2_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T2_r1_m1_l1_m1_r1_m1(k_value, a"<<std::endl;
  //std::cout<<T2_r1_m0_l1_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T2_r1_m0_l1_m1_r1_m0(k_value, a"<<std::endl;
  //std::cout<<T2_r1_m1_ml_1m_1r_1m_1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)   <<"   T2_r1_m1_ml_1m_1r_1m_1m(k_value"<<std::endl;
  //std::cout<<T3_r1_m1_l1_m1_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T3_r1_m1_l1_m1_r1_m1(k_value, a"<<std::endl;
  //std::cout<<T3_r1_m0_l1_m1_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)      <<"   T3_r1_m0_l1_m1_r1_m0(k_value, a"<<std::endl;
  //std::cout<<T3_r1_m1_ml_1m_1r_1m_1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)   <<"   T3_r1_m1_ml_1m_1r_1m_1m(k_value"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m1_l1_m0_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U1_r1_m1_l1_m0_r1_m1(k"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m0_l1_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U1_r1_m0_l1_m0_r1_m0(k"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)         <<"   SPINFLIP_U1_r1_m1m_l1_m0_r1_m1m"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m1_l1_m0_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U2_r1_m1_l1_m0_r1_m1(k"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m0_l1_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U2_r1_m0_l1_m0_r1_m0(k"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)         <<"   SPINFLIP_U2_r1_m1m_l1_m0_r1_m1m"<<std::endl;
  //std::cout<<SPINFLIP_U3_r1_m1_l1_m0_r1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U3_r1_m1_l1_m0_r1_m1(k"<<std::endl;
  //std::cout<<SPINFLIP_U3_r1_m0_l1_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)           <<"   SPINFLIP_U3_r1_m0_l1_m0_r1_m0(k"<<std::endl;
  //std::cout<<SPINFLIP_U3_r1_m1m_l1_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)         <<"   SPINFLIP_U3_r1_m1m_l1_m0_r1_m1m"<<std::endl;


  // //Definitions of the Integrals and Tensor Operators for decays from Mixed to P-wave lambda
  //std::cout<<T1_r1_m0_l1_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) <<"    T1_r1_m0_l1_m0_l1_m1m(k_value, alph"<<std::endl;
  //std::cout<<T1_r1_m0_l1_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T1_r1_m0_l1_m1_l1_m0(k_value, alpha"<<std::endl;
  //std::cout<<T1_r1_m1_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T1_r1_m1_l1_m1_l1_m1(k_value, alpha"<<std::endl;
  //std::cout<<T1_r1_m1_l1_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T1_r1_m1_l1_m0_l1_m0(k_value, alpha"<<std::endl;
  //std::cout<<T1_r1_m1_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T1_r1_m1_l1_m1m_l1_m1m(k_value, alp"<<std::endl;
  //std::cout<<T2_r1_m0_l1_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik) <<"    T2_r1_m0_l1_m0_l1_m1m(k_value, alph"<<std::endl;
  //std::cout<<T2_r1_m0_l1_m1_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T2_r1_m0_l1_m1_l1_m0(k_value, alpha"<<std::endl;
  //std::cout<<T2_r1_m1_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T2_r1_m1_l1_m1_l1_m1(k_value, alpha"<<std::endl;
  //std::cout<<T2_r1_m1_l1_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)  <<"    T2_r1_m1_l1_m0_l1_m0(k_value, alpha"<<std::endl;
  //std::cout<<T2_r1_m1_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<"    T2_r1_m1_l1_m1m_l1_m1m(k_value, alp"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m0_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)       <<"    SPINFLIP_U1_r1_m0_l1_m1_l1_m1(k_val"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m0_l1_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)       <<"    SPINFLIP_U1_r1_m0_l1_m0_l1_m0(k_val"<<std::endl;
  //std::cout<<SPINFLIP_U1_r1_m0_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)     <<"    SPINFLIP_U1_r1_m0_l1_m1m_l1_m1m(k_v"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m0_l1_m1_l1_m1(k_value, alpha_lam, alpha_rho, mcharm, mlight)       <<"    SPINFLIP_U2_r1_m0_l1_m1_l1_m1(k_val"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m0_l1_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)       <<"    SPINFLIP_U2_r1_m0_l1_m0_l1_m0(k_val"<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m0_l1_m1m_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight)     <<"    SPINFLIP_U2_r1_m0_l1_m1m_l1_m1m(k_v"<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from D-lambda to ground state
  //std::cout<<SPINFLIP_U1_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm,  mlight)<<" SPINFLIP_U1_l2_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U2_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm,  mlight)<<" SPINFLIP_U2_l2_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U3_l2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm,  mlight)<<" SPINFLIP_U3_l2_m0_GS "<<std::endl;
  //std::cout<<T1_l2_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<< " T1_l2_m1_GS" <<std::endl;
  //std::cout<<T2_l2_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<< " T2_l2_m1_GS" <<std::endl;
  //std::cout<<T3_l2_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<< " T3_l2_m1_GS" <<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from D-rho to ground state
  //std::cout<<SPINFLIP_U1_r2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_r2_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U2_r2_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r2_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U3_r2_m0_GS()<<" SPINFLIP_U3_r2_m0_GS "<<std::endl;
  //std::cout<<T1_r2_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r2_m1_GS "<<std::endl;
  //std::cout<<T2_r2_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r2_m1_GS "<<std::endl;
  //std::cout<<T3_r2_m1_GS()<<" T3_r2_m1_GS "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Mixed to ground state
  //std::cout<<SPINFLIP_U1_r1_m0_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_r1_m0_l1_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U2_r1_m0_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_r1_m0_l1_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U3_r1_m0_l1_m0_GS()<<" SPINFLIP_U3_r1_m0_l1_m0_GS "<<std::endl;
  //std::cout<<T1_r1_m1_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r1_m1_l1_m0_GS "<<std::endl;
  //std::cout<<T1_r1_m0_l1_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_r1_m0_l1_m1_GS "<<std::endl;
  //std::cout<<T2_r1_m1_l1_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r1_m1_l1_m0_GS "<<std::endl;
  //std::cout<<T2_r1_m0_l1_m1_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_r1_m0_l1_m1_GS "<<std::endl;
  //std::cout<<T3_r1_m1_l1_m0_GS()<<" T3_r1_m1_l1_m0_GS "<<std::endl;
  //std::cout<<T3_r1_m0_l1_m1_GS()<<" T3_r1_m0_l1_m1_GS "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial lambda to ground state
  //std::cout<<SPINFLIP_U1_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nl1_l0_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U2_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nl1_l0_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U3_nl1_l0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U3_nl1_l0_m0_GS "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial rho to ground state
  //std::cout<<SPINFLIP_U1_nr1_r0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nr1_r0_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U2_nr1_r0_m0_GS(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nr1_r0_m0_GS "<<std::endl;
  //std::cout<<SPINFLIP_U3_nr1_r0_m0_GS()<<" SPINFLIP_U3_nr1_r0_m0_GS "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial lambda to P wave lambda
  //std::cout<<SPINFLIP_U1_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nl1_l0_m0_l1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nl1_l0_m0_l1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U3_nl1_l0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U3_nl1_l0_m0_l1_m0 "<<std::endl;
  //std::cout<<T1_nl1_l0_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_nl1_l0_m0_l1_m1m "<<std::endl;
  //std::cout<<T2_nl1_l0_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_nl1_l0_m0_l1_m1m "<<std::endl;
  //std::cout<<T3_nl1_l0_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T3_nl1_l0_m0_l1_m1m "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial lambda to P wave rho
  //std::cout<<SPINFLIP_U1_nl1_l0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nl1_l0_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_nl1_l0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nl1_l0_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U3_nl1_l0_m0_r1_m0()<<" SPINFLIP_U3_nl1_l0_m0_r1_m0 "<<std::endl;
  //std::cout<<T1_nl1_l0_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_nl1_l0_m0_r1_m1m "<<std::endl;
  //std::cout<<T2_nl1_l0_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_nl1_l0_m0_r1_m1m "<<std::endl;
  //std::cout<<T3_nl1_l0_m0_r1_m1m()<<" T3_nl1_l0_m0_r1_m1m "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial rho to P wave lambda
  //std::cout<<SPINFLIP_U1_nr1_r0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nr1_r0_m0_l1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_nr1_r0_m0_l1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nr1_r0_m0_l1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U3_nr1_r0_m0_l1_m0()<<" SPINFLIP_U3_nr1_r0_m0_l1_m0 "<<std::endl;
  //std::cout<<T1_nr1_r0_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_nr1_r0_m0_l1_m1m "<<std::endl;
  //std::cout<<T2_nr1_r0_m0_l1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_nr1_r0_m0_l1_m1m "<<std::endl;
  //std::cout<<T3_nr1_r0_m0_l1_m1m()<<" T3_nr1_r0_m0_l1_m1m "<<std::endl;

  //Definitions of the Integrals and Tensor Operators for decays from Radial rho to P rho
  //std::cout<<SPINFLIP_U1_nr1_r0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U1_nr1_r0_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U2_nr1_r0_m0_r1_m0(k_value, alpha_lam, alpha_rho, mcharm, mlight)<<" SPINFLIP_U2_nr1_r0_m0_r1_m0 "<<std::endl;
  //std::cout<<SPINFLIP_U3_nr1_r0_m0_r1_m0()<<" SPINFLIP_U3_nr1_r0_m0_r1_m0 "<<std::endl;
  //std::cout<<T1_nr1_r0_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T1_nr1_r0_m0_r1_m1m "<<std::endl;
  //std::cout<<T2_nr1_r0_m0_r1_m1m(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik)<<" T2_nr1_r0_m0_r1_m1m "<<std::endl;
  //std::cout<<T3_nr1_r0_m0_r1_m1m()<<" T3_nr1_r0_m0_r1_m1m "<<std::endl;



  // // test function
  // double thetak = 0; double phik = 0; double mLlA=1;
  // double tensor1 = T1l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, mLlA);
  // double tensor2 = T2l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, mLlA);
  // double tensor3 = T3l(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, mLlA);
  // double tensor4 = T1r(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, mLlA);
  // double tensor5 = T2r(k_value, alpha_lam, alpha_rho, mcharm, mlight, thetak, phik, mLlA);
  // std::cout<<tensor1<<"    "<<tensor2<<"   "<<tensor3<<"   "<<tensor4<<"   "<<tensor5<<std::endl;
