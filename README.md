ExternPythonDll
===============
Python简单扩展

参考：http://bbs.chinaunix.net/thread-1593255-1-1.html

一般的包装模式

每一个包装函数主要做三件事：
1.把输入的Python对象转换为C/C++对象；
2.调用C/C++函数；
3.转换C/C++函数处理的输出结果为Python对象，并返回；


相关说明
    每个包装函数都有如下形式：
         PyObject * wrap_function(PyObject *, PyObject * args)
     函数第一个参数，有特殊用途，通常选择忽略。第二个参数是一个PyTuple(PyObject的子类型，和Python中的Tuple对应)，是调用时Python传入的参数。
    函数PyArg_ParseTuple把Python对象转换为C的数据类型，其声明如下:
         int PyArg_ParseTuple(PyObject* args, char* format, ...);
     参数args必须是一个tuple对象，包含传递过来的参数， format 参数必须是格式化字符串。剩余参数是各个变量的地址，类型要与格式化字符串对应。如：
        int arg1, arg2;
        PyArg_ParseTuple(args, "ii", &arg1, &arg2);
     函数Py_BuildValue可以说是PyArg_ParseTuple的逆过程，它把C的数据类型包装为Python对象。
        return (PyObject*)Py_BuildValue("i", result);
     把调用C函数的结果result包装为Python的int对象，并返回。
        static PyMethodDef wrap_methods[] ={
            {"add", wrap_add, METH_VARARGS},
            {NULL, NULL}
        };
     这个数组包含多个数组，其中的每个数组都包含了一个函数的信息，以便解释器能够导入并调用它们，最后一个NULL数组表示列表的结束。METH_VARARGS常量表示参数以元组形式传入。
        PyMODINIT_FUNC initwrap (void)
        {
            Py_InitModule("wrap ", wrap_methods);
        }
     模块初始化函数void initModuleName(),这部分代码在模块被导入的时候被解释器调用。这样所有的包装就已经完成了。
