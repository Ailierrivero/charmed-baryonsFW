#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
---------------------------------------------------------------
 Code to calcualte heavy-baryon decay widths
 authors: A. Ramirez-Morales (andres.ramirez.morales@cern.ch)
          H. Garcia-Tecocoatzi
---------------------------------------------------------------
"""

import numpy as np

omega_mass    = 6.06400
omega_s_mass  = 6.09300
sigma_mass    = 5.80500
sigma_s_mass  = 5.83400
xi_p_mass     = 5.92500
xi_p_s_mass   = 5.95500
xi_mass       = 5.80600
lambda_mass   = 5.61400

def append_dic(baryons, state1, state2,state3,
               state4, state5, state6, state7):
    baryons.append(state1)
    baryons.append(state2)
    baryons.append(state3)
    baryons.append(state4)
    baryons.append(state5)
    baryons.append(state6)
    baryons.append(state7)
    return baryons

def state_labels(baryon, ModEx, decPr, L_tot):
    """
    Method to obtain a simple decay names
    """    
    if(baryon==1):
        baryon_name = "omega"
        if(decPr==101):
            decPr_name = "Omg+gamma"
        elif(decPr==102):
            decPr_name = "Omg*+gamma"
        if(decPr==201):
            decPr_name = "Omg 2p1/2-lam+gamma"
        if(decPr==202):
            decPr_name = "Omg 4p1/2-lam+gamma"
        if(decPr==203):
            decPr_name = "Omg 2p3/2-lam+gamma"
        if(decPr==204):
            decPr_name = "Omg 4p3/2-lam+gamma"
        if(decPr==205):
            decPr_name = "Omg 4p5/2-lam+gamma"
        if(decPr==206):
            decPr_name = "Omg 2p1/2-rho+gamma"
        if(decPr==207):
            decPr_name = "Omg 2p3/2-rho+gamma"
             
    elif(baryon==2 or baryon==5): #cascades and cascades_anti3
        if(baryon==2):
            baryon_name = 'cas_6'
        if(baryon==5):
            baryon_name = 'cas_3'
        if(decPr==101):
            decPr_name = "Xi+ +gamma"
        elif(decPr==102):
            decPr_name = "Xi0 +gamma"
        elif(decPr==103):
            decPr_name = "Xi'+ +gamma"
        elif(decPr==104):
            decPr_name = "Xi*+ +gamma"
        elif(decPr==105):
            decPr_name = "Xi'0 +gamma"
        elif(decPr==106):
            decPr_name = "Xi*0 +gamma"
        elif(decPr==201):
            decPr_name = "Xi+ 2p1/2-lam+gamma"
        elif(decPr==202):
            decPr_name = "Xi+ 2p3/2-lam+gamma"
        elif(decPr==203):
            decPr_name = "Xi+ 2p1/2-rho+gamma"
        elif(decPr==204):
            decPr_name = "Xi+ 4p1/2-rho+gamma"
        elif(decPr==205):
            decPr_name = "Xi+ 2p3/2-rho+gamma"
        elif(decPr==206):
            decPr_name = "Xi+ 4p3/2-rho+gamma"
        elif(decPr==207):
            decPr_name = "Xi+ 4p5/2-rho+gamma"
        elif(decPr==208):
            decPr_name = "Xi0 2p1/2-lam+gamma"
        elif(decPr==209):
            decPr_name = "Xi0 2p3/2-lam+gamma"
        elif(decPr==210):
            decPr_name = "Xi0 2p1/2-rho+gamma"
        elif(decPr==211):
            decPr_name = "Xi0 4p1/2-rho+gamma"
        elif(decPr==212):
            decPr_name = "Xi0 2p3/2-rho+gamma"
        elif(decPr==213):
            decPr_name = "Xi0 4p3/2-rho+gamma"
        elif(decPr==214):
            decPr_name = "Xi0 4p5/2-rho+gamma"
        elif(decPr==215):
            decPr_name = "Xi'+ 2p1/2-lam+gamma"
        elif(decPr==216):
            decPr_name = "Xi'+ 4p1/2-lam+gamma"
        elif(decPr==217):
            decPr_name = "Xi'+ 2p3/2-lam+gamma"
        elif(decPr==218):
            decPr_name = "Xi'+ 4p3/2-lam+gamma"
        elif(decPr==219):
            decPr_name = "Xi'+ 4p5/2-lam+gamma"
        elif(decPr==220):
            decPr_name = "Xi'+ 2p1/2-rho+gamma"
        elif(decPr==221):
            decPr_name = "Xi'+ 2p3/2-rho+gamma"
        elif(decPr==222):
            decPr_name = "Xi'0 2p1/2-lam+gamma"
        elif(decPr==223):
            decPr_name = "Xi'0 4p1/2-lam+gamma"
        elif(decPr==224):
            decPr_name = "Xi'0 2p3/2-lam+gamma"
        elif(decPr==225):
            decPr_name = "Xi'0 4p3/2-lam+gamma"
        elif(decPr==226):
            decPr_name = "Xi'0 4p5/2-lam+gamma"
        elif(decPr==227):
            decPr_name = "Xi'0 2p1/2-rho+gamma"
        elif(decPr==228):
            decPr_name = "Xi'0 2p3/2-rho+gamma"
    elif(baryon==3):
        baryon_name = "sigma"
        if(decPr==101):
            decPr_name = "Sig++ +gamma"
        elif(decPr==102):
            decPr_name = "Sig*++ +gamma"
        elif(decPr==103):
            decPr_name = "Sig+ +gamma"
        elif(decPr==104):
            decPr_name = "Sig*+ +gamma" 
        elif(decPr==105):
            decPr_name = "Sig0 +gamma"
        elif(decPr==106):
            decPr_name = "Sig*0 +gamma"
        elif(decPr==107):
            decPr_name = "Lamb+ +gamma"
        elif(decPr==201):
            decPr_name = "Sig++ 2p1/2-lam+gamma"
        elif(decPr==202):
            decPr_name = "Sig++ 4p1/2-lam+gamma"
        elif(decPr==203):
            decPr_name = "Sig++ 2p3/2-lam+gamma"
        elif(decPr==204):
            decPr_name = "Sig++ 4p3/2-lam+gamma"
        elif(decPr==205):
            decPr_name = "Sig++ 4p5/2-lam+gamma"
        elif(decPr==206):
            decPr_name = "Sig++ 2p1/2-rho+gamma"
        elif(decPr==207):
            decPr_name = "Sig++ 2p3/2-rho+gamma"
        elif(decPr==208):
            decPr_name = "Sig+ 2p1/2-lam+gamma"
        elif(decPr==209):
            decPr_name = "Sig+ 4p1/2-lam+gamma"
        elif(decPr==210):
            decPr_name = "Sig+ 2p3/2-lam+gamma"
        elif(decPr==211):
            decPr_name = "Sig+ 4p3/2-lam+gamma"
        elif(decPr==212):
            decPr_name = "Sig+ 4p5/2-lam+gamma"
        elif(decPr==213):
            decPr_name = "Sig+ 2p1/2-rho+gamma"
        elif(decPr==214):
            decPr_name = "Sig+ 2p3/2-rho+gamma"
        elif(decPr==215):
            decPr_name = "Sig0 2p1/2-lam+gamma"
        elif(decPr==216):
            decPr_name = "Sig0 4p1/2-lam+gamma"
        elif(decPr==217):
            decPr_name = "Sig0 2p3/2-lam+gamma"
        elif(decPr==218):
            decPr_name = "Sig0 4p3/2-lam+gamma"
        elif(decPr==219):
            decPr_name = "Sig0 4p5/2-lam+gamma"
        elif(decPr==220):
            decPr_name = "Sig0 2p1/2-rho+gamma"
        elif(decPr==221):
            decPr_name = "Sig0 2p3/2-rho+gamma"
        elif(decPr==222):
            decPr_name = "Lam 2p1/2-lam+gamma"
        elif(decPr==223):
            decPr_name = "Lam 2p3/2-lam+gamma"
        elif(decPr==224):
            decPr_name = "Lam 2p1/2-rho+gamma"
        elif(decPr==225):
            decPr_name = "Lam 4p1/2-rho+gamma"
        elif(decPr==226):
            decPr_name = "Lam 2p3/2-rho+gamma"
        elif(decPr==227):
            decPr_name = "Lam 4p3/2-rho+gamma"
        elif(decPr==228):
            decPr_name = "Lam 4p5/2-rho+gamma"
                   
    elif(baryon==4):
        baryon_name = 'lambda'
        if(decPr==101):
            decPr_name = "Lamb+ +gamma"
        elif(decPr==102):
            decPr_name = "Sig+ +gamma"
        elif(decPr==103):
            decPr_name = "Sig*+ +gamma"
        elif(decPr==201):
            decPr_name = "Lam 2p1/2-lam+gamma"
        elif(decPr==202):
            decPr_name = "Lam 2p3/2-lam+gamma"
        elif(decPr==203):
            decPr_name = "Lam 2p1/2-rho+gamma"
        elif(decPr==204):
            decPr_name = "Lam 4p1/2-rho+gamma"
        elif(decPr==205):
            decPr_name = "Lam 2p3/2-rho+gamma"
        elif(decPr==206):
            decPr_name = "Lam 4p3/2-rho+gamma"
        elif(decPr==207):
            decPr_name = "Lam 4p5/2-rho+gamma"
        elif(decPr==208):
            decPr_name = "Sig+ 2p1/2-lam+gamma"
        elif(decPr==209):
            decPr_name = "Sig+ 4p1/2-lam+gamma"
        elif(decPr==210):
            decPr_name = "Sig+ 2p3/2-lam+gamma"
        elif(decPr==211):
            decPr_name = "Sig+ 4p3/2-lam+gamma"
        elif(decPr==212):
            decPr_name = "Sig+ 4p5/2-lam+gamma"
        elif(decPr==213):
            decPr_name = "Sig+ 2p1/2-rho+gamma"
        elif(decPr==214):
            decPr_name = "Sig+ 2p3/2-rho+gamma"
    
    if(ModEx==0):
        ModEx_name ='Ground'
    elif(ModEx==1):
        if(L_tot==1):
            ModEx_name ='P-Wave-lam'
        elif(L_tot==2):
            ModEx_name ='D-Wave-lam'
    elif(ModEx==2):
        if(L_tot==1):
            ModEx_name ='P-Wave-rho'
        elif(L_tot==2):
            ModEx_name ='D-Wave-rho'
    elif(ModEx==3):
        ModEx_name ='Radial-lam'
    elif(ModEx==4):
        ModEx_name ='Radial-rho'
    elif(ModEx==5):
        ModEx_name ='Mixed'
    return baryon_name,ModEx_name,decPr_name

def asymmetric_decay_indi_error(list_array_decays):

    indi_up, indi_dn = ([]), ([])
    for i in range(len(list_array_decays[0])): # range == no.decays of a specific channel
        indi_channel = list_array_decays[:,i]
        indi_mean = np.mean(indi_channel)
        boot_size = indi_channel.size # array size == bootstrap size
        sort_indi_channel = np.sort(indi_channel)
        quantile_dn = int(boot_size*0.1587)   #int(np.floor(N*0.1587))
        quantile_up = int(boot_size*0.8413)+1 #int(np.floor(N*0.8413))
        indi_up = np.append(indi_up, sort_indi_channel[quantile_up-1] - indi_mean)
        indi_dn = np.append(indi_dn, sort_indi_channel[quantile_dn-1] - indi_mean)
    return indi_up, indi_dn

        
def latex_decay_label(baryon, decPr, charge=None):
    # test
    decPr_name = ("TEST", xi_p_mass)

    if(baryon==1 or baryon=='omegas'):
        baryon_name = "omega"
        if(decPr==1):
            decPr_name = (r"$\Omega_{c} \gamma$", xi_mass)
        elif(decPr==2):                                                                         
            decPr_name = (r"$\Omega^{*}_{c} \gamma$", xi_p_mass)
        else:                                                                     
            decPr_name = (r"$\Omega_{c} \gamma$", xi_p_mass)

    elif(baryon==2 or baryon==5 or baryon=='cascades' or baryon=='cascades_anti3'):
        if(baryon==2): baryon_name = 'cas_6'
        if(baryon==5): baryon_name = 'cas_3'        
        if charge == None:
            if(decPr==1):
                decPr_name = (r"$\Xi_{c}^{0} \gamma$", xi_mass)
            elif(decPr==2):             
                decPr_name = (r"$\Xi_{c}^{-} \gamma$", xi_mass)
            elif(decPr==3):                                                                                           
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_mass)
            elif(decPr==4):                                                                                           
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_mass)
            elif(decPr==5):                                                                                           
                decPr_name = (r"$\Xi'^{*0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==6):                                                                                           
                decPr_name = (r"$\Xi'^{*-}_{c} \gamma$", xi_p_s_mass)
        elif charge == "zero":
            if(decPr==1):
                decPr_name = (r"$\Xi_{c}^{0} \gamma$", xi_mass)
            elif(decPr==2):                                                                                           
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_mass)
            elif(decPr==3):                                                                                   
                decPr_name = (r"$\Xi^{*0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==4):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==5):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==6):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==7):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==8):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==9):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==10):
                decPr_name = (r"$\Xi^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==11):
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==12):                                                                                           
                decPr_name = (r"$\Xi^{*0}_{c} \gamma$", xi_p_mass)
            elif(decPr==13):
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==14):                                                                     
                decPr_name = (r"$\Xi^{*0}_{c} \gamma$", xi_p_mass)
            elif(decPr==15):                                                                     
                decPr_name = (r"$\Xi^{*0}_{c} \gamma$", xi_p_mass)
            elif(decPr==16):
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==17):
                decPr_name = (r"$\Xi'^{0}_{c} \gamma$", xi_p_s_mass)
        elif charge == "negative":
            if(decPr==1):
                decPr_name = (r"$\Xi_{c}^{-} \gamma$", xi_mass)
            elif(decPr==2):                                                                                           
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_mass)
            elif(decPr==3):                                                                                   
                decPr_name = (r"$\Xi^{*-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==4):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==5):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==6):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==7):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==8):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==9):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==10):
                decPr_name = (r"$\Xi^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==11):
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==12):                                                                                           
                decPr_name = (r"$\Xi^{*-}_{c} \gamma$", xi_p_mass)
            elif(decPr==13):
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==14):                                                                     
                decPr_name = (r"$\Xi^{*-}_{c} \gamma$", xi_p_mass)
            elif(decPr==15):                                                                     
                decPr_name = (r"$\Xi^{*-}_{c} \gamma$", xi_p_mass)
            elif(decPr==16):
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_s_mass)
            elif(decPr==17):
                decPr_name = (r"$\Xi'^{-}_{c} \gamma$", xi_p_s_mass)
            
    elif(baryon==3 or baryon=='sigmas'):
        baryon_name = 'sigma'
        if charge == "charged":
            if(decPr==1):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==2):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==3):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==4):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==5):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==6):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==7):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==8):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==9):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==10):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==11):
                decPr_name = (r"$\Sigma_{c}^{+} \gamma$", sigma_s_mass)
            elif(decPr==12):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==13):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==14):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass) 
            elif(decPr==15):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==16):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==17):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)
            elif(decPr==18):
                decPr_name = (r"$\Sigma_{c}^{-} \gamma$", sigma_s_mass)

        elif charge == "zero":
            if(decPr==1):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            elif(decPr==2):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            elif(decPr==3):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==4):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==5):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==6):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==7):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==8):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==9):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            elif(decPr==10):
                decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
            if(decPr==11):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            if(decPr==12):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass) 
            if(decPr==13):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            if(decPr==14):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            if(decPr==15):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            if(decPr==16):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
            if(decPr==17):
                decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
    
        
            
            
    elif(baryon==4 or baryon=='lambdas'):
        baryon_name = 'lamda'
        if(decPr==1):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", lambda_mass)
        elif(decPr==2):
            decPr_name = (r"$\Sigma_{c}^{0} \gamma$", sigma_s_mass)
        elif(decPr==3):
            decPr_name = (r"$\Sigma_{c}^{*} \gamma$", sigma_mass)
        elif(decPr==4):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==5):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==6):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==7):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==8):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==9):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==10):
            decPr_name = (r"$\Lambda_{c}^{0} \gamma$", sigma_mass)
        elif(decPr==11):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==12):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==13):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==14):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==15):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==16):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)
        elif(decPr==17):
            decPr_name = (r"$\Sigma_{c} \gamma$", sigma_mass)  
    return decPr_name


def notation_spect(baryon, decPr, charge=None):
    notation = "keV"
    if baryon == "cascades" or baryon=="cascades_anti3" or baryon=="lambdas":
        if(decPr==1):
            notation = r"$^2S_{1/2}$"
        elif(decPr==2):
            notation = r"$^2S_{1/2}$"
        elif(decPr==3):
            notation = r"$^4S_{3/2}$"
        elif(decPr==4):
            notation = r"$^2_{\lambda}P_{1/2}$"
        elif(decPr==5):
            notation = r"$^2_{\lambda}P_{3/2}$"
        elif(decPr==6):
            notation = r"$^2_{\rho}P_{1/2}$"
        elif(decPr==7):
            notation = r"$^4_{\rho}P_{1/2}$"
        elif(decPr==8):
            notation = r"$^2_{\rho}P_{3/2}$"
        elif(decPr==9):
            notation = r"$^4_{\rho}P_{3/2}$"
        elif(decPr==10):
            notation = r"$^4_{\rho}P_{5/2}$"
        elif(decPr==11):
            notation = r"$^2_{\lambda}P_{1/2}$"
        elif(decPr==12):
            notation = r"$^4_{\lambda}P_{1/2}$"
        elif(decPr==13):
            notation = r"$^2_{\lambda}P_{3/2}$"
        elif(decPr==14):
            notation = r"$^4_{\lambda}P_{3/2}$"
        elif(decPr==15):
            notation = r"$^4_{\lambda}P_{5/2}$"
        elif(decPr==16):
            notation = r"$^2_{\rho}P_{1/2}$"
        elif(decPr==17):
            notation = r"$^2_{\rho}P_{3/2}$"
    if baryon=="omegas":
        if(decPr==1):
            notation = r"$^2S_{1/2}$"
        elif(decPr==2):
            notation = r"$^4S_{3/2}$"
        elif(decPr==3):
            notation = r"$^2_{\lambda}P_{1/2}$"
        elif(decPr==4):
            notation = r"$^4_{\lambda}P_{1/2}$"
        elif(decPr==5):
            notation = r"$^2_{\lambda}P_{3/2}$"
        elif(decPr==6):
            notation = r"$^4_{\lambda}P_{3/2}$"
        elif(decPr==7):
            notation = r"$^4_{\lambda}P_{5/2}$"
        elif(decPr==8):
            notation = r"$^2_{\rho}P_{1/2}$"
        elif(decPr==9):
            notation = r"$^2_{\rho}P_{3/2}$"

    if baryon=="sigmas":
        if charge == "zero":
            if(decPr==1):
                notation = r"$^2S_{1/2}$"
            elif(decPr==2):
                notation = r"$^4S_{3/2}$"
            elif(decPr==3):
                notation = r"$^2S_{1/2}$"
            elif(decPr==4):
                notation = r"$^2_{\lambda}P_{1/2}$"
            elif(decPr==5):
                notation = r"$^4_{\lambda}P_{1/2}$"
            elif(decPr==6):
                notation = r"$^2_{\lambda}P_{3/2}$"
            elif(decPr==7):
                notation = r"$^4_{\lambda}P_{3/2}$"
            elif(decPr==8):
                notation = r"$^4_{\lambda}P_{5/2}$"
            elif(decPr==9):
                notation = r"$^2_{\rho}P_{1/2}$"
            elif(decPr==10):
                notation = r"$^2_{\rho}P_{3/2}$"
            elif(decPr==11):
                notation = r"$^2_{\lambda}P_{1/2}$"
            elif(decPr==12):
                notation = r"$^4_{\lambda}P_{1/2}$"
            elif(decPr==13):
                notation = r"$^2_{\lambda}P_{3/2}$"
            elif(decPr==14):
                notation = r"$^4_{\lambda}P_{3/2}$"
            elif(decPr==15):
                notation = r"$^4_{\lambda}P_{5/2}$"
            elif(decPr==16):
                notation = r"$^2_{\rho}P_{1/2}$"
            elif(decPr==17):
                notation = r"$^2_{\rho}P_{3/2}$"
        elif charge == "charged":
            if(decPr==1):
                notation = r"$^2S_{1/2}$"
            elif(decPr==2):
                notation = r"$^4S_{3/2}$"
            if(decPr==3):
                notation = r"$^2S_{1/2}$"
            elif(decPr==4):
                notation = r"$^4S_{3/2}$"
            elif(decPr==5):
                notation = r"$^2_{\lambda}P_{1/2}$"
            elif(decPr==6):
                notation = r"$^4_{\lambda}P_{1/2}$"
            elif(decPr==7):
                notation = r"$^2_{\lambda}P_{3/2}$"
            elif(decPr==8):
                notation = r"$^4_{\lambda}P_{3/2}$"
            elif(decPr==9):
                notation = r"$^4_{\lambda}P_{5/2}$"
            elif(decPr==10):
                notation = r"$^2_{\rho}P_{1/2}$"
            elif(decPr==11):
                notation = r"$^2_{\rho}P_{3/2}$"
            elif(decPr==12):
                notation = r"$^2_{\lambda}P_{1/2}$"
            elif(decPr==13):
                notation = r"$^4_{\lambda}P_{1/2}$"
            elif(decPr==14):
                notation = r"$^2_{\lambda}P_{3/2}$"
            elif(decPr==15):
                notation = r"$^4_{\lambda}P_{3/2}$"
            elif(decPr==16):
                notation = r"$^4_{\lambda}P_{5/2}$"
            elif(decPr==17):
                notation = r"$^2_{\rho}P_{1/2}$"
            elif(decPr==18):
                notation = r"$^2_{\rho}P_{3/2}$"        
    return notation

def round_custom(number, round_number):
    if round_number ==0:
        return round(number)
    else:
        return round(number, round_number)

def print_row_latex(compare, mass_a, masses_b, state_name, state_decays, errors_up, errors_dn, cqm_widths, f_out):
    """
    Method to print a single row in latex format for the EM decays
    """
    nstate=len(state_decays)
    no_errors = False # for no bootstrap for decay widths
    if(errors_up is None or errors_dn is None):
        no_errors = True
        
    # no_errors = True
    cons_energy_count = 0
    print(state_name, end='',file=f_out)
    for i in range(nstate):
        value=0
        if(state_decays[i]==0.0):
            if mass_a < masses_b[i] : # check if the width is zero for energy conservation
                cons_energy_count+=1
                value = '$0$'
                print(value, end='', file=f_out)
                if (i < nstate-1): print("  &", end='', file=f_out)
            else:
                value = '0' # CHECK this, before was value="-"
                print(value, end='', file=f_out)
                if (i < nstate-1): print("  &", end='', file=f_out)
        else:
            round_number = 1
            if state_decays[i]>=5 : round_number = 0
            value = round_custom(state_decays[i], round_number)
            value_comp = "$xx$"
            if compare and cqm_widths!=[]: value_comp = round(cqm_widths[i], 1)
            if not no_errors:
                error_up = abs(round_custom(errors_up[i], round_number))
                error_dn = abs(round_custom(errors_dn[i], round_number))
                # print("$",value,"$", end='', file=f_out)
                print("$",value,"_{-",error_dn, "}^{+",error_up,"}$  ", end='', file=f_out)
                if (i < nstate-1): print("  &  ", end='', file=f_out)
            else:
                print(value, end='', file=f_out)
                if (i < nstate-1): print("  &", end='', file=f_out)
                if compare:
                    if i < nstate-1:
                        print(value_comp,"  &", end='', file=f_out)
                    else:
                        print(value_comp, end='', file=f_out)
    
    if compare:
        print(" \\\\", file=f_out)
        return
    else:
        print(" \\\\", file=f_out)
        return

def print_header_latex(name_header, name_states, compare, f_out):
    nNames = len(name_states)
    print(r"\\begin{tabular}{c c c c|", end='',file=f_out)
    if compare : nNames=int(2*nNames)
    for i in range(nNames-1):
        print(r"  p{1.0cm}", end='',file=f_out)        
    separator = " & "
    if compare:
        nNames=int(0.5*nNames)
        separator = " && "
        print(r"} \hline \hline", file=f_out)
    else:
        # print("p{0.85cm}} \hline \hline", file=f_out) # Gamma total
        print(r"} \hline \hline", file=f_out)
        
    for i in range(nNames-1): print(name_header[i]," & ", end='',file=f_out)
    print(name_header[nNames-1], r"\\\\", file=f_out)
    for i in range(nNames-1): print(name_states[i], separator, end='',file=f_out)
    print(name_states[nNames-1], r" \\\\ \hline", file=f_out)

def print_charm_latex(baryons,f_decay):
    print(r'\hline \hline', file=f_decay)
    print(r'\end{tabular}', file=f_decay)
    #print("\caption{Decay widths in MeV, for states: $", baryons,"$}",file=f_decay)
    #print("\label{tab:gordo}", file=f_decay)


def decay_masses(baryons, decPr):
    """
    Method to fetch decay masses
    """
    if(baryons=='omegas'):
        if(decPr==1):     return omega_mass
        elif(decPr==2):   return omega_s_mass
    elif(baryons=='cascades' or baryons=='cascades_anti3'):
        if(decPr==1):     return xi_mass
        elif(decPr==2):   return xi_mass
        elif(decPr==3):   return xi_p_mass
        elif(decPr==4):   return xi_p_mass
        elif(decPr==5):   return xi_p_s_mass
        elif(decPr==6):   return xi_p_s_mass
    elif(baryons=='sigmas'):
        if(decPr==1):     return sigma_mass
        elif(decPr==2):   return sigma_mass
        elif(decPr==3):   return sigma_mass
        elif(decPr==4):   return lambda_mass
        elif(decPr==5):   return xi_p_s_mass
        elif(decPr==6):   return xi_p_s_mass
        elif(decPr==7):   return xi_p_s_mass
    elif(baryons=='lambdas'):
        if(decPr==1):     return lambda_mass
        elif(decPr==2):   return sigma_mass
        elif(decPr==3):   return sigma_mass

def baryon_symbol(baryons="omegas"):
    if baryons=="omegas":
        return r"\Omega"
    elif baryons=="sigmas":
        return r"\Sigma"
    elif baryons=="lambdas":
        return r"\Lambda"
    elif baryons=="cascades":
        return r"\Xi'"
    else:
        return r"\Xi"

def baryon_quarks(baryons="omegas"):
    if baryons=="omegas":
        return "ssc"
    elif baryons=="sigmas":
        return "nnc"
    elif baryons=="lambdas":
        return "nnc"
    elif baryons=="cascades":
        return "snc"
    else:
        return "snc"
