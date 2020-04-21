#include <Python.h>
#include "cfunct.h"
#include <numpy/arrayobject.h>
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

static PyObject *py_VAR_RR_(PyObject *self, PyObject *args) {   
    PyObject *py_x, *py_y, *py_para; 
    int is_debias, is_eta;
    double eta, alpha;


    if(!PyArg_ParseTuple(args,"OOOdidi", &py_y, &py_x, &py_para, &eta, &is_debias, &alpha, &is_eta)){
        return NULL;
    }

    PyObject *py_x_array = PyArray_FROM_OTF(py_x, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_y_array = PyArray_FROM_OTF(py_y, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_para_array = PyArray_FROM_OTF(py_para, NPY_INT, NPY_IN_ARRAY);

    if (py_x_array == NULL || py_y_array== NULL || py_para_array==NULL) {
        Py_XDECREF(py_x_array);
        Py_XDECREF(py_y_array);
        Py_XDECREF(py_para_array);
        return NULL;
    }

    double *x = (double*) PyArray_DATA(py_x_array);
    double *y = (double*) PyArray_DATA(py_y_array);
    int *para = (int*)    PyArray_DATA(py_para_array);

    int nx = para[0], px = para[1];
    double sigma2;

    // Call the external C function.
    sigma2 = _VAR_RR_(y, x, para, eta, is_debias, alpha, is_eta);

    Py_DECREF(py_x_array);
    Py_DECREF(py_y_array);
    Py_DECREF(py_para_array);

    return Py_BuildValue("d", sigma2);
}


static PyObject *py_VAR_MM_(PyObject *self, PyObject *args) {   
    PyObject *py_x, *py_y, *py_para, *py_Sigma; 
    int is_identity, is_NULL;


    if(!PyArg_ParseTuple(args,"OOOOii", &py_y, &py_x, &py_para, &py_Sigma, &is_identity, &is_NULL)){
        return NULL;
    }

    PyObject *py_x_array = PyArray_FROM_OTF(py_x, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_y_array = PyArray_FROM_OTF(py_y, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_para_array = PyArray_FROM_OTF(py_para, NPY_INT, NPY_IN_ARRAY);
    PyObject *py_Sigma_array = PyArray_FROM_OTF(py_Sigma, NPY_DOUBLE, NPY_IN_ARRAY);


    if (py_x_array == NULL || py_y_array== NULL || py_para_array==NULL || py_Sigma_array==NULL) {
        Py_XDECREF(py_x_array);
        Py_XDECREF(py_y_array);
        Py_XDECREF(py_para_array);
        Py_XDECREF(py_Sigma_array);
        return NULL;
    }

    double *x = (double*) PyArray_DATA(py_x_array);
    double *y = (double*) PyArray_DATA(py_y_array);
    int *para = (int*)    PyArray_DATA(py_para_array);
    double *Sigma_ = (double*)    PyArray_DATA(py_Sigma_array);

    int nx = para[0], px = para[1];
    double sigma2;

    // Call the external C function.
    sigma2 = _VAR_MM_(y, x, para, Sigma_, is_identity, is_NULL);

    //npy_intp dims[1] = {1};
    //PyObject *ret = PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, sigma2);

    Py_DECREF(py_x_array);
    Py_DECREF(py_y_array);
    Py_DECREF(py_para_array);
    Py_DECREF(py_Sigma_array);
    
    return Py_BuildValue("d", sigma2);
}


static PyObject *py_VAR_MLE_(PyObject *self, PyObject *args) {   
    PyObject *py_x, *py_y, *py_para; 
    int max_iter;
    double tol;


    if(!PyArg_ParseTuple(args,"OOOid", &py_y, &py_x, &py_para, &max_iter, &tol)){
        return NULL;
    }

    PyObject *py_x_array = PyArray_FROM_OTF(py_x, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_y_array = PyArray_FROM_OTF(py_y, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *py_para_array = PyArray_FROM_OTF(py_para, NPY_INT, NPY_IN_ARRAY);


    if (py_x_array == NULL || py_y_array== NULL || py_para_array==NULL) {
        Py_XDECREF(py_x_array);
        Py_XDECREF(py_y_array);
        Py_XDECREF(py_para_array);
        return NULL;
    }

    double *x = (double*) PyArray_DATA(py_x_array);
    double *y = (double*) PyArray_DATA(py_y_array);
    int *para = (int*)    PyArray_DATA(py_para_array);

    int nx = para[0], px = para[1];
    double sigma2;

    // Call the external C function.
    sigma2 = _VAR_MLE_(y, x, para, max_iter, tol);

    //npy_intp dims[1] = {1};
    //PyObject *ret = PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, sigma2);

    Py_DECREF(py_x_array);
    Py_DECREF(py_y_array);
    Py_DECREF(py_para_array);
    
    return Py_BuildValue("d", sigma2);
}

/* Documentations */
static char module_docs[] = "Estimate error's variance via ridge regression, MM and MLE.";

static char cfunct_rr_docs[] = "Estimate error's variance via ridge regression.";
static char cfunct_mm_docs[] = "Estimate error's variance via MM.";
static char cfunct_mle_docs[] = "Estimate error's variance via MLE.";
/* Module method table */
static PyMethodDef MydemoMethods[] = {// "CFACTORIAL_" in py_CFACTORIAL_ must be exactly same as the output function "CFACTORIAL_"
  {"VAR_RR_",  py_VAR_RR_, METH_VARARGS, cfunct_rr_docs},
  {"VAR_MM_",  py_VAR_MM_, METH_VARARGS, cfunct_mm_docs},
  {"VAR_MLE_",  py_VAR_MLE_, METH_VARARGS, cfunct_mle_docs},
  /* If your extension module has many export functions, you need write interfaces for each of them. */
  /* And then add them to Module method table. For example: */
  /* {"mycfunc2",  py_mycfunc2, METH_VARARGS, cfunction2_docs}, */
  { NULL, NULL, 0, NULL}
};

/* Module structure */
static struct PyModuleDef RidgeVarpymodule = {
    PyModuleDef_HEAD_INIT,
    "_RidgeVarpy",           /* name of module */
    module_docs,        /* Doc string (may be NULL) */
    -1,                 /* Size of per-interpreter state or -1 */
    MydemoMethods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC PyInit__RidgeVarpy(void) {
    PyObject *object = PyModule_Create(&RidgeVarpymodule);
    if(object == NULL) {
        return NULL;
    }
    import_array();
    return object;
}