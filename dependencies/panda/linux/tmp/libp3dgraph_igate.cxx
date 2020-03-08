/*
 * This file was generated by:
 * built/bin/interrogate -srcdir panda/src/dgraph -Ipanda/src/dgraph -DCPPPARSER -D__STDC__=1 -D__cplusplus=201103L -D__attribute__(x)= -D_LP64 -oc built/tmp/libp3dgraph_igate.cxx -od built/pandac/input/libp3dgraph.in -fnames -string -refcount -assert -python-native -Sbuilt/include/parser-inc -Ipanda/src/dgraph -Sbuilt/tmp -Sbuilt/include -S/usr/include/eigen3 -module panda3d.core -library libp3dgraph config_dgraph.h dataGraphTraverser.h dataNode.h dataNodeTransmit.h p3dgraph_composite1.cxx p3dgraph_composite2.cxx
 *
 */

#include "dtoolbase.h"
#include "interrogate_request.h"
#include "dconfig.h"
#include "pnotify.h"
#include <sstream>
#include "py_panda.h"
#include "extension.h"
#include "dcast.h"

#include "config_dgraph.h"
#include "dataGraphTraverser.h"
#include "dataNode.h"
#include "dataNodeTransmit.h"
#include "notifyCategoryProxy.h"
#include "pandaNode.h"
#include "pandabase.h"
#include "pmap.h"
#include "pointerTo.h"
#include "pvector.h"

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#define PY_SSIZE_T_CLEAN 1

#if PYTHON_FRAMEWORK
  #include <Python/Python.h>
#else
  #include "Python.h"
#endif

/**
 * Forward declarations for top-level class DataGraphTraverser
 */
typedef DataGraphTraverser DataGraphTraverser_localtype;
Define_Module_Class(panda3d.core, DataGraphTraverser, DataGraphTraverser_localtype, DataGraphTraverser);
static struct Dtool_PyTypedObject *const Dtool_Ptr_DataGraphTraverser = &Dtool_DataGraphTraverser;
static void Dtool_PyModuleClassInit_DataGraphTraverser(PyObject *module);

/**
 * Forward declarations for top-level class DataNode
 */
typedef DataNode DataNode_localtype;
Define_Module_ClassRef(panda3d.core, DataNode, DataNode_localtype, DataNode);
static struct Dtool_PyTypedObject *const Dtool_Ptr_DataNode = &Dtool_DataNode;
static void Dtool_PyModuleClassInit_DataNode(PyObject *module);

/**
 * Declarations for exported classes
 */
static const Dtool_TypeDef exports[] = {
  {"DataGraphTraverser", &Dtool_DataGraphTraverser},
  {"DataNode", &Dtool_DataNode},
  {nullptr, nullptr},
};

/**
 * Extern declarations for imported classes
 */
#ifndef LINK_ALL_STATIC
static Dtool_TypeDef imports[] = {
  {"std::ostream", nullptr},
#define Dtool_Ptr_std_ostream (imports[0].type)
  {"TypeHandle", nullptr},
#define Dtool_Ptr_TypeHandle (imports[1].type)
  {"TypedObject", nullptr},
#define Dtool_Ptr_TypedObject (imports[2].type)
  {"Namable", nullptr},
#define Dtool_Ptr_Namable (imports[3].type)
  {"ReferenceCount", nullptr},
#define Dtool_Ptr_ReferenceCount (imports[4].type)
  {"Thread", nullptr},
#define Dtool_Ptr_Thread (imports[5].type)
  {"TypedWritable", nullptr},
#define Dtool_Ptr_TypedWritable (imports[6].type)
  {"TypedWritableReferenceCount", nullptr},
#define Dtool_Ptr_TypedWritableReferenceCount (imports[7].type)
  {"PandaNode", nullptr},
#define Dtool_Ptr_PandaNode (imports[8].type)
  {nullptr, nullptr},
};
#endif

// std::ostream
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_std_ostream;
static struct Dtool_PyTypedObject *const Dtool_Ptr_std_ostream = &Dtool_std_ostream;
#endif
// TypeHandle
#ifndef LINK_ALL_STATIC
inline static TypeHandle *Dtool_Coerce_TypeHandle(PyObject *args, TypeHandle &coerced) {
  nassertr(Dtool_Ptr_TypeHandle != nullptr, nullptr);
  nassertr(Dtool_Ptr_TypeHandle->_Dtool_Coerce != nullptr, nullptr);
  return ((TypeHandle *(*)(PyObject *, TypeHandle &))Dtool_Ptr_TypeHandle->_Dtool_Coerce)(args, coerced);
}
#else
extern struct Dtool_PyTypedObject Dtool_TypeHandle;
static struct Dtool_PyTypedObject *const Dtool_Ptr_TypeHandle = &Dtool_TypeHandle;
extern TypeHandle *Dtool_Coerce_TypeHandle(PyObject *args, TypeHandle &coerced);
#endif
// TypedObject
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_TypedObject;
static struct Dtool_PyTypedObject *const Dtool_Ptr_TypedObject = &Dtool_TypedObject;
#endif
// Namable
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_Namable;
static struct Dtool_PyTypedObject *const Dtool_Ptr_Namable = &Dtool_Namable;
#endif
// ReferenceCount
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_ReferenceCount;
static struct Dtool_PyTypedObject *const Dtool_Ptr_ReferenceCount = &Dtool_ReferenceCount;
#endif
// Thread
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_Thread;
static struct Dtool_PyTypedObject *const Dtool_Ptr_Thread = &Dtool_Thread;
#endif
// TypedWritable
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_TypedWritable;
static struct Dtool_PyTypedObject *const Dtool_Ptr_TypedWritable = &Dtool_TypedWritable;
#endif
// TypedWritableReferenceCount
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_TypedWritableReferenceCount;
static struct Dtool_PyTypedObject *const Dtool_Ptr_TypedWritableReferenceCount = &Dtool_TypedWritableReferenceCount;
#endif
// PandaNode
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_PandaNode;
static struct Dtool_PyTypedObject *const Dtool_Ptr_PandaNode = &Dtool_PandaNode;
#endif

/**
 * Python wrappers for global functions
 */
/**
 * Python wrappers for functions of class DataGraphTraverser
 */
/**
 * Python function wrapper for:
 * inline Thread *DataGraphTraverser::get_current_thread(void) const
 */
static PyObject *Dtool_DataGraphTraverser_get_current_thread_4(PyObject *self, PyObject *) {
  DataGraphTraverser *local_this = nullptr;
  if (!DtoolInstance_GetPointer(self, local_this, Dtool_DataGraphTraverser)) {
    return nullptr;
  }
  // 1-inline Thread *DataGraphTraverser::get_current_thread(void) const
  Thread *return_value = ((*(const DataGraphTraverser*)local_this).get_current_thread)();
  if (return_value != nullptr) {
    return_value->ref();
  }
  if (Dtool_CheckErrorOccurred()) {
    if (return_value != nullptr) {
      unref_delete(return_value);
    }
    return nullptr;
  }
  if (return_value == nullptr) {
    Py_INCREF(Py_None);
    return Py_None;
  } else {
    return DTool_CreatePyInstanceTyped((void *)return_value, *Dtool_Ptr_Thread, true, false, return_value->as_typed_object()->get_type_index());
  }
}

#ifndef NDEBUG
static const char *Dtool_DataGraphTraverser_get_current_thread_4_comment =
  "C++ Interface:\n"
  "get_current_thread(DataGraphTraverser self)\n"
  "\n"
  "/**\n"
  " * Returns the currently-executing thread object, as passed to the\n"
  " * DataGraphTraverser constructor.\n"
  " */";
#else
static const char *Dtool_DataGraphTraverser_get_current_thread_4_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void DataGraphTraverser::traverse(PandaNode *node)
 */
static PyObject *Dtool_DataGraphTraverser_traverse_5(PyObject *self, PyObject *arg) {
  DataGraphTraverser *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_DataGraphTraverser, (void **)&local_this, "DataGraphTraverser.traverse")) {
    return nullptr;
  }
  // 1-void DataGraphTraverser::traverse(PandaNode *node)
  PandaNode *arg_this = (PandaNode *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_PandaNode, 1, "DataGraphTraverser.traverse", false, true);
  if (arg_this != nullptr) {
    ((*local_this).traverse)(arg_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "traverse(const DataGraphTraverser self, PandaNode node)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_DataGraphTraverser_traverse_5_comment =
  "C++ Interface:\n"
  "traverse(const DataGraphTraverser self, PandaNode node)\n"
  "\n"
  "/**\n"
  " * Starts the traversal of the data graph at the indicated root node.\n"
  " */";
#else
static const char *Dtool_DataGraphTraverser_traverse_5_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void DataGraphTraverser::collect_leftovers(void)
 */
static PyObject *Dtool_DataGraphTraverser_collect_leftovers_7(PyObject *self, PyObject *) {
  DataGraphTraverser *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_DataGraphTraverser, (void **)&local_this, "DataGraphTraverser.collect_leftovers")) {
    return nullptr;
  }
  // 1-void DataGraphTraverser::collect_leftovers(void)
  ((*local_this).collect_leftovers)();
  return Dtool_Return_None();
}

#ifndef NDEBUG
static const char *Dtool_DataGraphTraverser_collect_leftovers_7_comment =
  "C++ Interface:\n"
  "collect_leftovers(const DataGraphTraverser self)\n"
  "\n"
  "/**\n"
  " * Pick up any nodes that didn't get completely traversed.  These must be\n"
  " * nodes that have multiple parents, with at least one parent completely\n"
  " * outside of the data graph.\n"
  " */";
#else
static const char *Dtool_DataGraphTraverser_collect_leftovers_7_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * inline DataGraphTraverser::DataGraphTraverser(DataGraphTraverser const &) = default
 * explicit DataGraphTraverser::DataGraphTraverser(Thread *current_thread = Thread::get_current_thread())
 */
static int Dtool_Init_DataGraphTraverser(PyObject *self, PyObject *args, PyObject *kwds) {
  int parameter_count = (int)PyTuple_Size(args);
  if (kwds != nullptr) {
    parameter_count += (int)PyDict_Size(kwds);
  }
  switch (parameter_count) {
  case 0:
    {
      // 1-explicit DataGraphTraverser::DataGraphTraverser(Thread *current_thread)
      DataGraphTraverser *return_value = new DataGraphTraverser();
      if (return_value == nullptr) {
        PyErr_NoMemory();
        return -1;
      }
      if (Dtool_CheckErrorOccurred()) {
        delete return_value;
        return -1;
      }
      return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_DataGraphTraverser, true, false);
    }
    break;
  case 1:
    {
      {
        // -2 inline DataGraphTraverser::DataGraphTraverser(DataGraphTraverser const &) = default
        PyObject *param0;
        if (Dtool_ExtractArg(&param0, args, kwds)) {
          DataGraphTraverser const *param0_this = nullptr;
          DtoolInstance_GetPointer(param0, param0_this, *Dtool_Ptr_DataGraphTraverser);
          if (param0_this != nullptr) {
            DataGraphTraverser *return_value = new DataGraphTraverser(*param0_this);
            if (return_value == nullptr) {
              PyErr_NoMemory();
              return -1;
            }
            if (Dtool_CheckErrorOccurred()) {
              delete return_value;
              return -1;
            }
            return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_DataGraphTraverser, true, false);
          }
        }
      }

      {
        // -2 explicit DataGraphTraverser::DataGraphTraverser(Thread *current_thread)
        PyObject *param0;
        if (Dtool_ExtractArg(&param0, args, kwds, "current_thread")) {
          Thread *param0_this = (Thread *)DTOOL_Call_GetPointerThisClass(param0, Dtool_Ptr_Thread, 0, "DataGraphTraverser.DataGraphTraverser", false, false);
          if (param0_this != nullptr) {
            DataGraphTraverser *return_value = new DataGraphTraverser(param0_this);
            if (return_value == nullptr) {
              PyErr_NoMemory();
              return -1;
            }
            if (Dtool_CheckErrorOccurred()) {
              delete return_value;
              return -1;
            }
            return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_DataGraphTraverser, true, false);
          }
        }
      }

      // No coercion possible: inline DataGraphTraverser::DataGraphTraverser(DataGraphTraverser const &) = default
      // No coercion possible: explicit DataGraphTraverser::DataGraphTraverser(Thread *current_thread)
    }
    break;
#ifndef NDEBUG
  default:
    PyErr_Format(PyExc_TypeError,
                 "DataGraphTraverser() takes 0 or 1 arguments (%d given)",
                 parameter_count);
    return -1;
#endif
  }
  if (!_PyErr_OCCURRED()) {
    Dtool_Raise_BadArgumentsError(
      "DataGraphTraverser()\n"
      "DataGraphTraverser(const DataGraphTraverser param0)\n"
      "DataGraphTraverser(Thread current_thread)\n");
  }
  return -1;
}

static void *Dtool_UpcastInterface_DataGraphTraverser(PyObject *self, Dtool_PyTypedObject *requested_type) {
  Dtool_PyTypedObject *type = DtoolInstance_TYPE(self);
  if (type != &Dtool_DataGraphTraverser) {
    printf("DataGraphTraverser ** Bad Source Type-- Requesting Conversion from %s to %s\n", Py_TYPE(self)->tp_name, requested_type->_PyType.tp_name); fflush(nullptr);
    return nullptr;
  }

  DataGraphTraverser *local_this = (DataGraphTraverser *)DtoolInstance_VOID_PTR(self);
  if (requested_type == &Dtool_DataGraphTraverser) {
    return local_this;
  }
  return nullptr;
}

static void *Dtool_DowncastInterface_DataGraphTraverser(void *from_this, Dtool_PyTypedObject *from_type) {
  if (from_this == nullptr || from_type == nullptr) {
    return nullptr;
  }
  if (from_type == Dtool_Ptr_DataGraphTraverser) {
    return from_this;
  }
  return nullptr;
}

/**
 * Python wrappers for functions of class DataNode
 */
/**
 * Python function wrapper for:
 * void DataNode::write_inputs(std::ostream &out) const
 */
static PyObject *Dtool_DataNode_write_inputs_11(PyObject *self, PyObject *arg) {
  DataNode *local_this = nullptr;
  if (!DtoolInstance_GetPointer(self, local_this, Dtool_DataNode)) {
    return nullptr;
  }
  // 1-void DataNode::write_inputs(std::ostream &out) const
  std::ostream *arg_this = (std::ostream *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_std_ostream, 1, "DataNode.write_inputs", false, true);
  if (arg_this != nullptr) {
    ((*(const DataNode*)local_this).write_inputs)(*arg_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "write_inputs(DataNode self, ostream out)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_DataNode_write_inputs_11_comment =
  "C++ Interface:\n"
  "write_inputs(DataNode self, ostream out)\n"
  "\n"
  "/**\n"
  " * Writes to the indicated ostream a list of all the inputs this DataNode\n"
  " * might expect to receive.\n"
  " */";
#else
static const char *Dtool_DataNode_write_inputs_11_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void DataNode::write_outputs(std::ostream &out) const
 */
static PyObject *Dtool_DataNode_write_outputs_12(PyObject *self, PyObject *arg) {
  DataNode *local_this = nullptr;
  if (!DtoolInstance_GetPointer(self, local_this, Dtool_DataNode)) {
    return nullptr;
  }
  // 1-void DataNode::write_outputs(std::ostream &out) const
  std::ostream *arg_this = (std::ostream *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_std_ostream, 1, "DataNode.write_outputs", false, true);
  if (arg_this != nullptr) {
    ((*(const DataNode*)local_this).write_outputs)(*arg_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "write_outputs(DataNode self, ostream out)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_DataNode_write_outputs_12_comment =
  "C++ Interface:\n"
  "write_outputs(DataNode self, ostream out)\n"
  "\n"
  "/**\n"
  " * Writes to the indicated ostream a list of all the outputs this DataNode\n"
  " * might generate.\n"
  " */";
#else
static const char *Dtool_DataNode_write_outputs_12_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void DataNode::write_connections(std::ostream &out) const
 */
static PyObject *Dtool_DataNode_write_connections_13(PyObject *self, PyObject *arg) {
  DataNode *local_this = nullptr;
  if (!DtoolInstance_GetPointer(self, local_this, Dtool_DataNode)) {
    return nullptr;
  }
  // 1-void DataNode::write_connections(std::ostream &out) const
  std::ostream *arg_this = (std::ostream *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_std_ostream, 1, "DataNode.write_connections", false, true);
  if (arg_this != nullptr) {
    ((*(const DataNode*)local_this).write_connections)(*arg_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "write_connections(DataNode self, ostream out)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_DataNode_write_connections_13_comment =
  "C++ Interface:\n"
  "write_connections(DataNode self, ostream out)\n"
  "\n"
  "/**\n"
  " * Writes to the indicated ostream a list of all the connections currently\n"
  " * showing between this DataNode and its parent(s).\n"
  " */";
#else
static const char *Dtool_DataNode_write_connections_13_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * static TypeHandle DataNode::get_class_type(void)
 */
static PyObject *Dtool_DataNode_get_class_type_14(PyObject *, PyObject *) {
  // 1-static TypeHandle DataNode::get_class_type(void)
  TypeHandle *return_value = new TypeHandle((DataNode::get_class_type)());
  if (return_value == nullptr) {
    return PyErr_NoMemory();
  }
  if (Dtool_CheckErrorOccurred()) {
    delete return_value;
    return nullptr;
  }
  return DTool_CreatePyInstance((void *)return_value, *Dtool_Ptr_TypeHandle, true, false);
}

#ifndef NDEBUG
static const char *Dtool_DataNode_get_class_type_14_comment =
  "C++ Interface:\n"
  "get_class_type()\n";
#else
static const char *Dtool_DataNode_get_class_type_14_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * inline explicit DataNode::DataNode(std::string const &name)
 */
static int Dtool_Init_DataNode(PyObject *self, PyObject *args, PyObject *kwds) {
  int parameter_count = (int)PyTuple_Size(args);
  if (kwds != nullptr) {
    parameter_count += (int)PyDict_Size(kwds);
  }
  if (parameter_count != 1) {
#ifdef NDEBUG
    Dtool_Raise_TypeError("function takes exactly 1 argument");
    return -1;
#else
    PyErr_Format(PyExc_TypeError,
                 "DataNode() takes exactly 1 argument (%d given)",
                 parameter_count);
    return -1;
#endif
  }
  PyObject *arg;
  if (Dtool_ExtractArg(&arg, args, kwds, "name")) {
    // 1-inline explicit DataNode::DataNode(std::string const &name)
    const char *param0_str = nullptr;
    Py_ssize_t param0_len;
#if PY_MAJOR_VERSION >= 3
    param0_str = PyUnicode_AsUTF8AndSize(arg, &param0_len);
#else
    if (PyString_AsStringAndSize(arg, (char **)&param0_str, &param0_len) == -1) {
      param0_str = nullptr;
    }
#endif
    if (param0_str != nullptr) {
      DataNode *return_value = new DataNode(std::string(param0_str, param0_len));
      if (return_value == nullptr) {
        PyErr_NoMemory();
        return -1;
      }
      return_value->ref();
      if (Dtool_CheckErrorOccurred()) {
        unref_delete(return_value);
        return -1;
      }
      return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_DataNode, true, false);
    }
  }
  if (!_PyErr_OCCURRED()) {
    Dtool_Raise_BadArgumentsError(
      "DataNode(str name)\n");
  }
  return -1;
}

static void *Dtool_UpcastInterface_DataNode(PyObject *self, Dtool_PyTypedObject *requested_type) {
  Dtool_PyTypedObject *type = DtoolInstance_TYPE(self);
  if (type != &Dtool_DataNode) {
    printf("DataNode ** Bad Source Type-- Requesting Conversion from %s to %s\n", Py_TYPE(self)->tp_name, requested_type->_PyType.tp_name); fflush(nullptr);
    return nullptr;
  }

  DataNode *local_this = (DataNode *)DtoolInstance_VOID_PTR(self);
  if (requested_type == &Dtool_DataNode) {
    return local_this;
  }
  if (requested_type == Dtool_Ptr_Namable) {
    return (Namable *)(PandaNode *) local_this;
  }
  if (requested_type == Dtool_Ptr_PandaNode) {
    return (PandaNode *) local_this;
  }
  if (requested_type == Dtool_Ptr_ReferenceCount) {
    return (ReferenceCount *)(TypedWritableReferenceCount *)(PandaNode *) local_this;
  }
  if (requested_type == Dtool_Ptr_TypedObject) {
    return (TypedObject *)(TypedWritable *)(TypedWritableReferenceCount *)(PandaNode *) local_this;
  }
  if (requested_type == Dtool_Ptr_TypedWritable) {
    return (TypedWritable *)(TypedWritableReferenceCount *)(PandaNode *) local_this;
  }
  if (requested_type == Dtool_Ptr_TypedWritableReferenceCount) {
    return (TypedWritableReferenceCount *)(PandaNode *) local_this;
  }
  return nullptr;
}

static void *Dtool_DowncastInterface_DataNode(void *from_this, Dtool_PyTypedObject *from_type) {
  if (from_this == nullptr || from_type == nullptr) {
    return nullptr;
  }
  if (from_type == Dtool_Ptr_DataNode) {
    return from_this;
  }
  if (from_type == Dtool_Ptr_Namable) {
    Namable* other_this = (Namable*)from_this;
    return (DataNode*)other_this;
  }
  if (from_type == Dtool_Ptr_PandaNode) {
    PandaNode* other_this = (PandaNode*)from_this;
    return (DataNode*)other_this;
  }
  if (from_type == Dtool_Ptr_ReferenceCount) {
    ReferenceCount* other_this = (ReferenceCount*)from_this;
    return (DataNode*)other_this;
  }
  if (from_type == Dtool_Ptr_TypedObject) {
    TypedObject* other_this = (TypedObject*)from_this;
    return (DataNode*)other_this;
  }
  if (from_type == Dtool_Ptr_TypedWritable) {
    TypedWritable* other_this = (TypedWritable*)from_this;
    return (DataNode*)other_this;
  }
  if (from_type == Dtool_Ptr_TypedWritableReferenceCount) {
    TypedWritableReferenceCount* other_this = (TypedWritableReferenceCount*)from_this;
    return (DataNode*)other_this;
  }
  return nullptr;
}

/**
 * Python method tables for DataGraphTraverser (DataGraphTraverser)
 */
static PyMethodDef Dtool_Methods_DataGraphTraverser[] = {
  {"get_current_thread", &Dtool_DataGraphTraverser_get_current_thread_4, METH_NOARGS, (const char *)Dtool_DataGraphTraverser_get_current_thread_4_comment},
  {"getCurrentThread", &Dtool_DataGraphTraverser_get_current_thread_4, METH_NOARGS, (const char *)Dtool_DataGraphTraverser_get_current_thread_4_comment},
  {"traverse", &Dtool_DataGraphTraverser_traverse_5, METH_O, (const char *)Dtool_DataGraphTraverser_traverse_5_comment},
  {"collect_leftovers", &Dtool_DataGraphTraverser_collect_leftovers_7, METH_NOARGS, (const char *)Dtool_DataGraphTraverser_collect_leftovers_7_comment},
  {"collectLeftovers", &Dtool_DataGraphTraverser_collect_leftovers_7, METH_NOARGS, (const char *)Dtool_DataGraphTraverser_collect_leftovers_7_comment},
  {"__copy__", &copy_from_copy_constructor, METH_NOARGS, nullptr},
  {"__deepcopy__", &map_deepcopy_to_copy, METH_VARARGS, nullptr},
  {nullptr, nullptr, 0, nullptr}
};

static PyNumberMethods Dtool_NumberMethods_DataGraphTraverser = {
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr, // nb_long
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
#if PY_VERSION_HEX >= 0x02050000
  nullptr,
#endif
#if PY_VERSION_HEX >= 0x03050000
  nullptr,
  nullptr,
#endif
};

struct Dtool_PyTypedObject Dtool_DataGraphTraverser = {
  {
    PyVarObject_HEAD_INIT(nullptr, 0)
    "panda3d.core.DataGraphTraverser",
    0, // tp_basicsize
    0, // tp_itemsize
    &Dtool_FreeInstance_DataGraphTraverser,
#if PY_VERSION_HEX >= 0x03080000
    0, // tp_vectorcall_offset
#else
    nullptr,
#endif
    nullptr,
    nullptr,
#if PY_VERSION_HEX >= 0x03050000
    nullptr, // tp_as_async
#elif PY_MAJOR_VERSION >= 3
    nullptr, // tp_reserved
#else
    nullptr, // tp_compare
#endif
    nullptr,
    &Dtool_NumberMethods_DataGraphTraverser,
    nullptr, // tp_as_sequence
    nullptr, // tp_as_mapping
    nullptr, // tp_hash
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr, // tp_as_buffer
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_CHECKTYPES,
#ifdef NDEBUG
    0,
#else
    "/**\n"
    " * This object supervises the traversal of the data graph and the moving of\n"
    " * data from one DataNode to its children.  The data graph is used to manage\n"
    " * data from input devices, etc.  See the overview of the data graph in\n"
    " * dataNode.h.\n"
    " */",
#endif
    nullptr, // tp_traverse
    nullptr, // tp_clear
    nullptr, // tp_richcompare
    0, // tp_weaklistoffset
    nullptr,
    nullptr,
    Dtool_Methods_DataGraphTraverser,
    nullptr, // tp_members
    nullptr, // tp_getset
    nullptr, // tp_base
    nullptr, // tp_dict
    nullptr,
    nullptr,
    0, // tp_dictoffset
    Dtool_Init_DataGraphTraverser,
    PyType_GenericAlloc,
    Dtool_new_DataGraphTraverser,
    PyObject_Del,
    nullptr, // tp_is_gc
    nullptr, // tp_bases
    nullptr, // tp_mro
    nullptr, // tp_cache
    nullptr, // tp_subclasses
    nullptr, // tp_weaklist
    nullptr, // tp_del
#if PY_VERSION_HEX >= 0x02060000
    0, // tp_version_tag
#endif
#if PY_VERSION_HEX >= 0x03040000
    nullptr, // tp_finalize
#endif
#if PY_VERSION_HEX >= 0x03080000
    nullptr, // tp_vectorcall
#endif
  },
  TypeHandle::none(),
  Dtool_PyModuleClassInit_DataGraphTraverser,
  Dtool_UpcastInterface_DataGraphTraverser,
  Dtool_DowncastInterface_DataGraphTraverser,
  nullptr,
  nullptr,
};

static void Dtool_PyModuleClassInit_DataGraphTraverser(PyObject *module) {
  (void) module; // Unused
  static bool initdone = false;
  if (!initdone) {
    initdone = true;
    // Dependent objects
    Dtool_DataGraphTraverser._PyType.tp_base = (PyTypeObject *)Dtool_GetSuperBase();
    PyObject *dict = PyDict_New();
    Dtool_DataGraphTraverser._PyType.tp_dict = dict;
    PyDict_SetItemString(dict, "DtoolClassDict", dict);
    if (PyType_Ready((PyTypeObject *)&Dtool_DataGraphTraverser) < 0) {
      Dtool_Raise_TypeError("PyType_Ready(DataGraphTraverser)");
      return;
    }
    Py_INCREF((PyTypeObject *)&Dtool_DataGraphTraverser);
  }
}

/**
 * Python method tables for DataNode (DataNode)
 */
static PyMethodDef Dtool_Methods_DataNode[] = {
  {"write_inputs", &Dtool_DataNode_write_inputs_11, METH_O, (const char *)Dtool_DataNode_write_inputs_11_comment},
  {"writeInputs", &Dtool_DataNode_write_inputs_11, METH_O, (const char *)Dtool_DataNode_write_inputs_11_comment},
  {"write_outputs", &Dtool_DataNode_write_outputs_12, METH_O, (const char *)Dtool_DataNode_write_outputs_12_comment},
  {"writeOutputs", &Dtool_DataNode_write_outputs_12, METH_O, (const char *)Dtool_DataNode_write_outputs_12_comment},
  {"write_connections", &Dtool_DataNode_write_connections_13, METH_O, (const char *)Dtool_DataNode_write_connections_13_comment},
  {"writeConnections", &Dtool_DataNode_write_connections_13, METH_O, (const char *)Dtool_DataNode_write_connections_13_comment},
  {"get_class_type", &Dtool_DataNode_get_class_type_14, METH_NOARGS | METH_STATIC, (const char *)Dtool_DataNode_get_class_type_14_comment},
  {"getClassType", &Dtool_DataNode_get_class_type_14, METH_NOARGS | METH_STATIC, (const char *)Dtool_DataNode_get_class_type_14_comment},
  {nullptr, nullptr, 0, nullptr}
};

static PyNumberMethods Dtool_NumberMethods_DataNode = {
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr, // nb_long
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
#if PY_MAJOR_VERSION < 3
  nullptr,
#endif
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
#if PY_VERSION_HEX >= 0x02050000
  nullptr,
#endif
#if PY_VERSION_HEX >= 0x03050000
  nullptr,
  nullptr,
#endif
};

static PySequenceMethods Dtool_SequenceMethods_DataNode = {
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr, // sq_slice
  nullptr,
  nullptr, // sq_ass_slice
  nullptr,
  nullptr,
  nullptr,
};

static PyMappingMethods Dtool_MappingMethods_DataNode = {
  nullptr,
  nullptr,
  nullptr,
};

static PyBufferProcs Dtool_BufferProcs_DataNode = {
#if PY_MAJOR_VERSION < 3
  nullptr,
  nullptr,
  nullptr,
  nullptr,
#endif
#if PY_VERSION_HEX >= 0x02060000
  nullptr,
  nullptr,
#endif
};

#if PY_VERSION_HEX >= 0x03050000
static PyAsyncMethods Dtool_AsyncMethods_DataNode = {
  nullptr,
  nullptr,
  nullptr,
};
#endif

struct Dtool_PyTypedObject Dtool_DataNode = {
  {
    PyVarObject_HEAD_INIT(nullptr, 0)
    "panda3d.core.DataNode",
    0, // tp_basicsize
    0, // tp_itemsize
    &Dtool_FreeInstance_DataNode,
#if PY_VERSION_HEX >= 0x03080000
    0, // tp_vectorcall_offset
#else
    nullptr,
#endif
    nullptr,
    nullptr,
#if PY_VERSION_HEX >= 0x03050000
    &Dtool_AsyncMethods_DataNode,
#elif PY_MAJOR_VERSION >= 3
    nullptr, // tp_reserved
#else
    nullptr, // tp_compare
#endif
    nullptr,
    &Dtool_NumberMethods_DataNode,
    &Dtool_SequenceMethods_DataNode,
    &Dtool_MappingMethods_DataNode,
    nullptr, // tp_hash
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &Dtool_BufferProcs_DataNode,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_CHECKTYPES,
#ifdef NDEBUG
    0,
#else
    "/**\n"
    " * The fundamental type of node for the data graph.  The DataNode class is\n"
    " * itself primarily intended as an abstract class; it defines no inputs and no\n"
    " * outputs.  Most kinds of data nodes will derive from this to specify the\n"
    " * inputs and outputs in the constructor.\n"
    " *\n"
    " * DataNode does not attempt to cycle its data with a PipelineCycler.  The\n"
    " * data graph is intended to be used only within a single thread.\n"
    " */",
#endif
    nullptr, // tp_traverse
    nullptr, // tp_clear
    nullptr, // tp_richcompare
    0, // tp_weaklistoffset
    nullptr,
    nullptr,
    Dtool_Methods_DataNode,
    nullptr, // tp_members
    nullptr, // tp_getset
    nullptr, // tp_base
    nullptr, // tp_dict
    nullptr,
    nullptr,
    0, // tp_dictoffset
    Dtool_Init_DataNode,
    PyType_GenericAlloc,
    Dtool_new_DataNode,
    PyObject_Del,
    nullptr, // tp_is_gc
    nullptr, // tp_bases
    nullptr, // tp_mro
    nullptr, // tp_cache
    nullptr, // tp_subclasses
    nullptr, // tp_weaklist
    nullptr, // tp_del
#if PY_VERSION_HEX >= 0x02060000
    0, // tp_version_tag
#endif
#if PY_VERSION_HEX >= 0x03040000
    nullptr, // tp_finalize
#endif
#if PY_VERSION_HEX >= 0x03080000
    nullptr, // tp_vectorcall
#endif
  },
  TypeHandle::none(),
  Dtool_PyModuleClassInit_DataNode,
  Dtool_UpcastInterface_DataNode,
  Dtool_DowncastInterface_DataNode,
  nullptr,
  nullptr,
};

static void Dtool_PyModuleClassInit_DataNode(PyObject *module) {
  (void) module; // Unused
  static bool initdone = false;
  if (!initdone) {
    initdone = true;
    // Dependent objects
    assert(Dtool_Ptr_PandaNode != nullptr);
    assert(Dtool_Ptr_PandaNode->_Dtool_ModuleClassInit != nullptr);
    Dtool_Ptr_PandaNode->_Dtool_ModuleClassInit(nullptr);
    Dtool_DataNode._PyType.tp_bases = PyTuple_Pack(1, (PyTypeObject *)Dtool_Ptr_PandaNode);
    Dtool_DataNode._PyType.tp_base = (PyTypeObject *)Dtool_GetSuperBase();
    PyObject *dict = PyDict_New();
    Dtool_DataNode._PyType.tp_dict = dict;
    PyDict_SetItemString(dict, "DtoolClassDict", dict);
    if (PyType_Ready((PyTypeObject *)&Dtool_DataNode) < 0) {
      Dtool_Raise_TypeError("PyType_Ready(DataNode)");
      return;
    }
    Py_INCREF((PyTypeObject *)&Dtool_DataNode);
  }
}


/**
 * Module Object Linker ..
 */
void Dtool_libp3dgraph_RegisterTypes() {
  TypeRegistry *registry = TypeRegistry::ptr();
  nassertv(registry != nullptr);
  {
    DataNode::init_type();
    TypeHandle handle = DataNode::get_class_type();
    Dtool_DataNode._type = handle;
    registry->record_python_type(handle, (PyObject *)&Dtool_DataNode);
  }
}

void Dtool_libp3dgraph_BuildInstants(PyObject *module) {
  (void) module;
  // DataGraphTraverser
  Dtool_PyModuleClassInit_DataGraphTraverser(module);
  PyModule_AddObject(module, "DataGraphTraverser", (PyObject *)&Dtool_DataGraphTraverser);
  // DataNode
  Dtool_PyModuleClassInit_DataNode(module);
  PyModule_AddObject(module, "DataNode", (PyObject *)&Dtool_DataNode);
}

static PyMethodDef python_simple_funcs[] = {
  // Support Function For Dtool_types ... for now in each module ??
  {"Dtool_BorrowThisReference", &Dtool_BorrowThisReference, METH_VARARGS, "Used to borrow 'this' pointer (to, from)\nAssumes no ownership."},
  {nullptr, nullptr, 0, nullptr}
};

#ifdef LINK_ALL_STATIC
extern const struct LibraryDef libp3dgraph_moddef = {python_simple_funcs, exports, nullptr};
#else
extern const struct LibraryDef libp3dgraph_moddef = {python_simple_funcs, exports, imports};
#endif
static InterrogateModuleDef _in_module_def = {
  1583613458,  /* file_identifier */
  "libp3dgraph",  /* library_name */
  "YJkp",  /* library_hash_name */
  "panda3d.core",  /* module_name */
  "libp3dgraph.in",  /* database_filename */
  nullptr,  /* unique_names */
  0,  /* num_unique_names */
  nullptr,  /* fptrs */
  0,  /* num_fptrs */
  1,  /* first_index */
  45  /* next_index */
};

Configure(_in_configure_libp3dgraph);
ConfigureFn(_in_configure_libp3dgraph) {
  interrogate_request_module(&_in_module_def);
}
