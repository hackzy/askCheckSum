/*计算数据库Checksum*/
#define PY_SSIZE_T_CLEAN
#include <Python.h>
int sub_a(int nSeed, const char* pData, int nLength) {
    int a = nSeed;
    int b = 0;
    int mod = 65521;
    int i = 0;
    for (i = 0; i < nLength; i++) {
        a = (a + (unsigned char)pData[i]) % mod;
        b = (b + a) % mod;
    }
    return (b << 16) | a;
}
int sub_b(const char * szTest) {
    int checkSum = sub_a(1, szTest, strlen(szTest)) ^ 0xAB7932CF;
    return checkSum;
}



static PyObject *
askCheckSum(PyObject *self,PyObject *args){
    unsigned char *szTest;
    int nSeed;
    if(!PyArg_ParseTuple(args, "s", &szTest))
        return NULL;
    nSeed = sub_b(szTest);
    return Py_BuildValue("i", nSeed);
}

static PyMethodDef pyMethod[] = {
    {
        "getCheckSum", askCheckSum, METH_VARARGS,
        "计算数据库Checksum"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef mod_askCheckSum =
{
    PyModuleDef_HEAD_INIT,
    "askCheckSum",
    "askChecksum计算",
    -1,
    pyMethod
};

PyMODINIT_FUNC PyInit_askCheckSum(void){
    return PyModule_Create(&mod_askCheckSum);
}