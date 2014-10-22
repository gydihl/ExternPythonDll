// ExternPythonDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include "tchar.h"

#include <python.h>

#pragma comment(lib, "python27.lib")

static PyObject* mb_showMsg(PyObject *self, PyObject *args)
{
	const char *msg = NULL;
	const char *s = "s";
//	PyAPI_FUNC(int) PyArg_ParseTuple(PyObject*, const char *, ...);
	if (!PyArg_ParseTuple(args, s, &msg))
		return NULL;
	int r = ::MessageBox(NULL, _T("hello"), _T("Caption:From C module"),
		MB_ICONINFORMATION | MB_OK);

	::MessageBoxA(NULL, msg, "Caption:From C module",
		MB_ICONINFORMATION | MB_OK);

	return Py_BuildValue("i", r);
}

extern "C" __declspec(dllexport) 
void initExternPythonDll()
{
	static PyMethodDef mbMethods[] = {
		{
			"showMsg", mb_showMsg, METH_VARARGS
		},
		{
			NULL, NULL, NULL
		}
	};

	PyObject *m = Py_InitModule("ExternPythonDll", mbMethods);
}
