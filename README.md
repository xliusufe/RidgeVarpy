# ridgevar
Python package "ridgevar" for estimation of error variance via ridge regression. Provide several methods to estimate the error variance for high-dimensional linear regression models, which includes the ridge regression based method of Liu et al. (2020), the maximum likelihood based method of Dicker and Erdogdu (2016), and the moments based method of Dicker (2014).

# Installation

    pip install git+https://github.com/xliusufe/RidgeVarpy.git

# Usage

   - There are three functions: `VAR_RR`, `VAR_MM`, and `VAR_MLE` 

   - Details of the usage of the package can be found in corresponding R package [RidgeVar-manual.pdf](https://github.com/xliusufe/RidgeVar/blob/master/inst/RidgeVar-manual.pdf)

   - The correponding R package named [RidgeVar](https://github.com/xliusufe/RidgeVar/) can be found on GitHub.
# Example
    from ridgevar import *
    import numpy as np

    n, p = 60, 100
    beta = np.append(np.sqrt(0.1/p)*np.repeat(1,p/2),np.repeat(0,p/2))
    x = np.random.randn(n,p)
    eps = np.random.randn(n)
    y = x.dot(beta) + eps

    sigma2_RR = VAR_RR(y,x)
    sigma2_MLE = VAR_MLE(y,x)
    sigma2_MM = VAR_MM(y,x)
    print([sigma2_RR,sigma2_MLE,sigma2_MM])
    
# References
Dicker, L. H. (2014). Variance estimation in high-dimensional linear models.  Biometrika 101, 269-284.

Dicker, L. H. and Erdogdu, M. A. (2016). Maximum likelihood for variance estimation in high-dimensional linear models. In  Proceedings     of the 19th International Conference on Artificial Intelligence and Statistics (AISTATS 2016), 159-167. JMLR Workshop & Conference     Proceedings.

Fan, J., Guo, S. and Hao, N. (2012). Variance estimation using refitted cross-validation in ultrahigh-dimensional regression. Journal of Royal Statistical Society Series B 74, 37-65.

Liu, X., Zheng, S. and Feng, X. (2020). Estimation of error variance via ridge regression. Biometrika. [DOI: 10.1093/biomet/asz074](DOI:10.1093/biomet/asz074)

# Development
This Python package is developed by Xu Liu (liu.xu@sufe.edu.cn).
