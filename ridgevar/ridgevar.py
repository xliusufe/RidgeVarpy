from ._RidgeVarpy import VAR_RR_, VAR_MM_, VAR_MLE_
import numpy as np


def VAR_RR(y,x,eta=None,alpha=0.1):
    para = np.array(x.shape)
    is_debias = 0
    if eta is None:
        is_eta = 1
        eta = 0.0
    else:
        is_eta = 0   
  
    sigma2 = VAR_RR_(y, x, para, eta, is_debias, alpha, is_eta)    
    return sigma2

def VAR_MLE(y,x,max_iter=50,tol=1e-4):
    para = np.array(x.shape)      
    sigma2 = VAR_MLE_(y, x, para, max_iter, tol)    
    return sigma2

def VAR_MM(y,x,identity=False,Sigma=None):
    para = np.array(x.shape)
    if identity==True or identity==1:
        is_identity = 1
    else:
        is_identity = 0 
        
    if Sigma==None:
        is_NULL = 1
        Sigma = np.array(0.0)
    else:
        is_NULL = 0        
    
    sigma2 = VAR_MM_(y, x, para, Sigma, is_identity, is_NULL)    
    return sigma2