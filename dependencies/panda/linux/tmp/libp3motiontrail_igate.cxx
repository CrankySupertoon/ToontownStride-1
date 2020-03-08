/*
 * This file was generated by:
 * built/bin/interrogate -srcdir direct/src/motiontrail -Idirect/src/motiontrail -DCPPPARSER -D__STDC__=1 -D__cplusplus=201103L -D__attribute__(x)= -D_LP64 -oc built/tmp/libp3motiontrail_igate.cxx -od built/pandac/input/libp3motiontrail.in -fnames -string -refcount -assert -python-native -Sbuilt/include/parser-inc -Idirect/src/motiontrail -Sbuilt/tmp -Sbuilt/include -S/usr/include/eigen3 -module panda3d.direct -library libp3motiontrail cMotionTrail.cxx cMotionTrail.h config_motiontrail.h
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

#include "cMotionTrail.h"
#include "colorAttrib.h"
#include "config_motiontrail.h"
#include "dconfig.h"
#include "directbase.h"
#include "notifyCategoryProxy.h"
#include "renderState.h"

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#define PY_SSIZE_T_CLEAN 1

#if PYTHON_FRAMEWORK
  #include <Python/Python.h>
#else
  #include "Python.h"
#endif

/**
 * Forward declarations for top-level class CMotionTrail
 */
typedef CMotionTrail CMotionTrail_localtype;
Define_Module_ClassRef(panda3d.direct, CMotionTrail, CMotionTrail_localtype, CMotionTrail);
static struct Dtool_PyTypedObject *const Dtool_Ptr_CMotionTrail = &Dtool_CMotionTrail;
static void Dtool_PyModuleClassInit_CMotionTrail(PyObject *module);

/**
 * Declarations for exported classes
 */
static const Dtool_TypeDef exports[] = {
  {"CMotionTrail", &Dtool_CMotionTrail},
  {nullptr, nullptr},
};

/**
 * Extern declarations for imported classes
 */
#ifndef LINK_ALL_STATIC
static Dtool_TypeDef imports[] = {
  {"TypeHandle", nullptr},
#define Dtool_Ptr_TypeHandle (imports[0].type)
  {"TypedObject", nullptr},
#define Dtool_Ptr_TypedObject (imports[1].type)
  {"ReferenceCount", nullptr},
#define Dtool_Ptr_ReferenceCount (imports[2].type)
  {"TypedReferenceCount", nullptr},
#define Dtool_Ptr_TypedReferenceCount (imports[3].type)
  {"LVector4f", nullptr},
#define Dtool_Ptr_LVector4f (imports[4].type)
  {"LMatrix4f", nullptr},
#define Dtool_Ptr_LMatrix4f (imports[5].type)
  {"GeomNode", nullptr},
#define Dtool_Ptr_GeomNode (imports[6].type)
  {nullptr, nullptr},
};
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
// ReferenceCount
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_ReferenceCount;
static struct Dtool_PyTypedObject *const Dtool_Ptr_ReferenceCount = &Dtool_ReferenceCount;
#endif
// TypedReferenceCount
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_TypedReferenceCount;
static struct Dtool_PyTypedObject *const Dtool_Ptr_TypedReferenceCount = &Dtool_TypedReferenceCount;
#endif
// LVector4f
#ifndef LINK_ALL_STATIC
inline static LVector4f *Dtool_Coerce_LVector4f(PyObject *args, LVector4f &coerced) {
  nassertr(Dtool_Ptr_LVector4f != nullptr, nullptr);
  nassertr(Dtool_Ptr_LVector4f->_Dtool_Coerce != nullptr, nullptr);
  return ((LVector4f *(*)(PyObject *, LVector4f &))Dtool_Ptr_LVector4f->_Dtool_Coerce)(args, coerced);
}
#else
extern struct Dtool_PyTypedObject Dtool_LVector4f;
static struct Dtool_PyTypedObject *const Dtool_Ptr_LVector4f = &Dtool_LVector4f;
extern LVector4f *Dtool_Coerce_LVector4f(PyObject *args, LVector4f &coerced);
#endif
// LMatrix4f
#ifndef LINK_ALL_STATIC
inline static LMatrix4f *Dtool_Coerce_LMatrix4f(PyObject *args, LMatrix4f &coerced) {
  nassertr(Dtool_Ptr_LMatrix4f != nullptr, nullptr);
  nassertr(Dtool_Ptr_LMatrix4f->_Dtool_Coerce != nullptr, nullptr);
  return ((LMatrix4f *(*)(PyObject *, LMatrix4f &))Dtool_Ptr_LMatrix4f->_Dtool_Coerce)(args, coerced);
}
#else
extern struct Dtool_PyTypedObject Dtool_LMatrix4f;
static struct Dtool_PyTypedObject *const Dtool_Ptr_LMatrix4f = &Dtool_LMatrix4f;
extern LMatrix4f *Dtool_Coerce_LMatrix4f(PyObject *args, LMatrix4f &coerced);
#endif
// GeomNode
#ifndef LINK_ALL_STATIC
#else
extern struct Dtool_PyTypedObject Dtool_GeomNode;
static struct Dtool_PyTypedObject *const Dtool_Ptr_GeomNode = &Dtool_GeomNode;
#endif

/**
 * Python wrappers for global functions
 */
/**
 * Python wrappers for functions of class CMotionTrail
 */
/**
 * Python function wrapper for:
 * void CMotionTrail::reset(void)
 */
static PyObject *Dtool_CMotionTrail_reset_4(PyObject *self, PyObject *) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.reset")) {
    return nullptr;
  }
  // 1-void CMotionTrail::reset(void)
  ((*local_this).reset)();
  return Dtool_Return_None();
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_reset_4_comment =
  "C++ Interface:\n"
  "reset(const CMotionTrail self)\n"
  "\n"
  "/**\n"
  " * Reset the frame sample history.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_reset_4_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::reset_vertex_list(void)
 */
static PyObject *Dtool_CMotionTrail_reset_vertex_list_5(PyObject *self, PyObject *) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.reset_vertex_list")) {
    return nullptr;
  }
  // 1-void CMotionTrail::reset_vertex_list(void)
  ((*local_this).reset_vertex_list)();
  return Dtool_Return_None();
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_reset_vertex_list_5_comment =
  "C++ Interface:\n"
  "reset_vertex_list(const CMotionTrail self)\n"
  "\n"
  "/**\n"
  " * Reset the vertex list.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_reset_vertex_list_5_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::enable(bool enable)
 */
static PyObject *Dtool_CMotionTrail_enable_6(PyObject *self, PyObject *arg) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.enable")) {
    return nullptr;
  }
  // 1-void CMotionTrail::enable(bool enable)
  ((*local_this).enable)((PyObject_IsTrue(arg) != 0));
  return Dtool_Return_None();
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "enable(const CMotionTrail self, bool enable)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_enable_6_comment =
  "C++ Interface:\n"
  "enable(const CMotionTrail self, bool enable)\n"
  "\n"
  "/**\n"
  " * Enable/disable the motion trail.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_enable_6_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::set_geom_node(GeomNode *geom_node)
 */
static PyObject *Dtool_CMotionTrail_set_geom_node_7(PyObject *self, PyObject *arg) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.set_geom_node")) {
    return nullptr;
  }
  // 1-void CMotionTrail::set_geom_node(GeomNode *geom_node)
  GeomNode *arg_this = (GeomNode *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_GeomNode, 1, "CMotionTrail.set_geom_node", false, true);
  if (arg_this != nullptr) {
    ((*local_this).set_geom_node)(arg_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "set_geom_node(const CMotionTrail self, GeomNode geom_node)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_set_geom_node_7_comment =
  "C++ Interface:\n"
  "set_geom_node(const CMotionTrail self, GeomNode geom_node)\n"
  "\n"
  "/**\n"
  " * Set the GeomNode.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_set_geom_node_7_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::add_vertex(LVector4 *vertex, LVector4 *start_color, LVector4 *end_color, PN_stdfloat v)
 */
static PyObject *Dtool_CMotionTrail_add_vertex_8(PyObject *self, PyObject *args, PyObject *kwds) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.add_vertex")) {
    return nullptr;
  }
  // 1-void CMotionTrail::add_vertex(LVector4 *vertex, LVector4 *start_color, LVector4 *end_color, PN_stdfloat v)
  PyObject *param1;
  PyObject *param2;
  PyObject *param3;
  float param4;
  static const char *keyword_list[] = {"vertex", "start_color", "end_color", "v", nullptr};
  if (PyArg_ParseTupleAndKeywords(args, kwds, "OOOf:add_vertex", (char **)keyword_list, &param1, &param2, &param3, &param4)) {
    LVector4f param1_local;
    LVector4 *param1_this = Dtool_Coerce_LVector4f(param1, param1_local);
    if (!(param1_this != nullptr)) {
      return Dtool_Raise_ArgTypeError(param1, 1, "CMotionTrail.add_vertex", "LVector4f");
    }
    LVector4f param2_local;
    LVector4 *param2_this = Dtool_Coerce_LVector4f(param2, param2_local);
    if (!(param2_this != nullptr)) {
      return Dtool_Raise_ArgTypeError(param2, 2, "CMotionTrail.add_vertex", "LVector4f");
    }
    LVector4f param3_local;
    LVector4 *param3_this = Dtool_Coerce_LVector4f(param3, param3_local);
    if (!(param3_this != nullptr)) {
      return Dtool_Raise_ArgTypeError(param3, 3, "CMotionTrail.add_vertex", "LVector4f");
    }
    ((*local_this).add_vertex)(param1_this, param2_this, param3_this, (PN_stdfloat)param4);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "add_vertex(const CMotionTrail self, LVector4f vertex, LVector4f start_color, LVector4f end_color, float v)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_add_vertex_8_comment =
  "C++ Interface:\n"
  "add_vertex(const CMotionTrail self, LVector4f vertex, LVector4f start_color, LVector4f end_color, float v)\n"
  "\n"
  "/**\n"
  " * Add a vertex.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_add_vertex_8_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::set_parameters(PN_stdfloat sampling_time, PN_stdfloat time_window, bool use_texture, bool calculate_relative_matrix, bool use_nurbs, PN_stdfloat resolution_distance)
 */
static PyObject *Dtool_CMotionTrail_set_parameters_9(PyObject *self, PyObject *args, PyObject *kwds) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.set_parameters")) {
    return nullptr;
  }
  // 1-void CMotionTrail::set_parameters(PN_stdfloat sampling_time, PN_stdfloat time_window, bool use_texture, bool calculate_relative_matrix, bool use_nurbs, PN_stdfloat resolution_distance)
  float param1;
  float param2;
  PyObject *param3;
  PyObject *param4;
  PyObject *param5;
  float param6;
  static const char *keyword_list[] = {"sampling_time", "time_window", "use_texture", "calculate_relative_matrix", "use_nurbs", "resolution_distance", nullptr};
  if (PyArg_ParseTupleAndKeywords(args, kwds, "ffOOOf:set_parameters", (char **)keyword_list, &param1, &param2, &param3, &param4, &param5, &param6)) {
    ((*local_this).set_parameters)((PN_stdfloat)param1, (PN_stdfloat)param2, (PyObject_IsTrue(param3) != 0), (PyObject_IsTrue(param4) != 0), (PyObject_IsTrue(param5) != 0), (PN_stdfloat)param6);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "set_parameters(const CMotionTrail self, float sampling_time, float time_window, bool use_texture, bool calculate_relative_matrix, bool use_nurbs, float resolution_distance)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_set_parameters_9_comment =
  "C++ Interface:\n"
  "set_parameters(const CMotionTrail self, float sampling_time, float time_window, bool use_texture, bool calculate_relative_matrix, bool use_nurbs, float resolution_distance)\n"
  "\n"
  "/**\n"
  " * Set motion trail parameters.\n"
  " *\n"
  " * sampling_time = Can be used to specify a lower sampling rate than the frame\n"
  " * rate.  Use 0.0 with nurbs.\n"
  " *\n"
  " * time_window = a component for the \"length\" of the motion trail.  The motion\n"
  " * trail length = time_window * velocity of the object.\n"
  " *\n"
  " * use_texture = texture option on/off.\n"
  " *\n"
  " * calculate_relative_matrix = calculate relative matrix on/off.\n"
  " *\n"
  " * use_nurbs = nurbs option on/off\n"
  " *\n"
  " * resolution_distance = the distance used to determine the number of geometry\n"
  " * samples.  samples = motion trail length / resolution_distance.  Applicable\n"
  " * only if nurbs is on.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_set_parameters_9_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * int CMotionTrail::check_for_update(PN_stdfloat current_time)
 */
static PyObject *Dtool_CMotionTrail_check_for_update_10(PyObject *self, PyObject *arg) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.check_for_update")) {
    return nullptr;
  }
  // 1-int CMotionTrail::check_for_update(PN_stdfloat current_time)
  if (PyNumber_Check(arg)) {
    int return_value = ((*local_this).check_for_update)((PN_stdfloat)PyFloat_AsDouble(arg));
    if (Dtool_CheckErrorOccurred()) {
      return nullptr;
    }
    return Dtool_WrapValue(return_value);
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "check_for_update(const CMotionTrail self, float current_time)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_check_for_update_10_comment =
  "C++ Interface:\n"
  "check_for_update(const CMotionTrail self, float current_time)\n"
  "\n"
  "/**\n"
  " * Check if a sample can be submitted.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_check_for_update_10_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * void CMotionTrail::update_motion_trail(PN_stdfloat current_time, LMatrix4 *transform)
 */
static PyObject *Dtool_CMotionTrail_update_motion_trail_11(PyObject *self, PyObject *args, PyObject *kwds) {
  CMotionTrail *local_this = nullptr;
  if (!Dtool_Call_ExtractThisPointer_NonConst(self, Dtool_CMotionTrail, (void **)&local_this, "CMotionTrail.update_motion_trail")) {
    return nullptr;
  }
  // 1-void CMotionTrail::update_motion_trail(PN_stdfloat current_time, LMatrix4 *transform)
  float param1;
  PyObject *param2;
  static const char *keyword_list[] = {"current_time", "transform", nullptr};
  if (PyArg_ParseTupleAndKeywords(args, kwds, "fO:update_motion_trail", (char **)keyword_list, &param1, &param2)) {
    LMatrix4f param2_local;
    LMatrix4 *param2_this = Dtool_Coerce_LMatrix4f(param2, param2_local);
    if (!(param2_this != nullptr)) {
      return Dtool_Raise_ArgTypeError(param2, 2, "CMotionTrail.update_motion_trail", "LMatrix4f");
    }
    ((*local_this).update_motion_trail)((PN_stdfloat)param1, param2_this);
    return Dtool_Return_None();
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "update_motion_trail(const CMotionTrail self, float current_time, LMatrix4f transform)\n");
  }
  return nullptr;
}

#ifndef NDEBUG
static const char *Dtool_CMotionTrail_update_motion_trail_11_comment =
  "C++ Interface:\n"
  "update_motion_trail(const CMotionTrail self, float current_time, LMatrix4f transform)\n"
  "\n"
  "/**\n"
  " * See class header comments.\n"
  " */";
#else
static const char *Dtool_CMotionTrail_update_motion_trail_11_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * static TypeHandle CMotionTrail::get_class_type(void)
 */
static PyObject *Dtool_CMotionTrail_get_class_type_12(PyObject *, PyObject *) {
  // 1-static TypeHandle CMotionTrail::get_class_type(void)
  TypeHandle *return_value = new TypeHandle((CMotionTrail::get_class_type)());
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
static const char *Dtool_CMotionTrail_get_class_type_12_comment =
  "C++ Interface:\n"
  "get_class_type()\n";
#else
static const char *Dtool_CMotionTrail_get_class_type_12_comment = nullptr;
#endif

/**
 * Python function wrapper for:
 * CMotionTrail::CMotionTrail(void)
 * inline CMotionTrail::CMotionTrail(CMotionTrail const &) = default
 */
static int Dtool_Init_CMotionTrail(PyObject *self, PyObject *args, PyObject *kwds) {
  if (kwds != nullptr && PyDict_Size(kwds) > 0) {
#ifdef NDEBUG
    Dtool_Raise_TypeError("function takes no keyword arguments");
    return -1;
#else
    Dtool_Raise_TypeError("CMotionTrail() takes no keyword arguments");
    return -1;
#endif
  }
  int parameter_count = (int)PyTuple_Size(args);
  switch (parameter_count) {
  case 0:
    {
      // 1-CMotionTrail::CMotionTrail(void)
      CMotionTrail *return_value = new CMotionTrail();
      if (return_value == nullptr) {
        PyErr_NoMemory();
        return -1;
      }
      return_value->ref();
      if (Dtool_CheckErrorOccurred()) {
        unref_delete(return_value);
        return -1;
      }
      return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_CMotionTrail, true, false);
    }
    break;
  case 1:
    {
      PyObject *arg = PyTuple_GET_ITEM(args, 0);
      // 1-inline CMotionTrail::CMotionTrail(CMotionTrail const &) = default
      CMotionTrail const *arg_this = (CMotionTrail *)DTOOL_Call_GetPointerThisClass(arg, Dtool_Ptr_CMotionTrail, 0, "CMotionTrail.CMotionTrail", true, true);
      if (arg_this != nullptr) {
        CMotionTrail *return_value = new CMotionTrail(*arg_this);
        if (return_value == nullptr) {
          PyErr_NoMemory();
          return -1;
        }
        return_value->ref();
        if (Dtool_CheckErrorOccurred()) {
          unref_delete(return_value);
          return -1;
        }
        return DTool_PyInit_Finalize(self, (void *)return_value, &Dtool_CMotionTrail, true, false);
      }
    }
    break;
#ifndef NDEBUG
  default:
    PyErr_Format(PyExc_TypeError,
                 "CMotionTrail() takes 0 or 1 arguments (%d given)",
                 parameter_count);
    return -1;
#endif
  }
  if (!_PyErr_OCCURRED()) {
    Dtool_Raise_BadArgumentsError(
      "CMotionTrail()\n"
      "CMotionTrail(const CMotionTrail param0)\n");
  }
  return -1;
}

static void *Dtool_UpcastInterface_CMotionTrail(PyObject *self, Dtool_PyTypedObject *requested_type) {
  Dtool_PyTypedObject *type = DtoolInstance_TYPE(self);
  if (type != &Dtool_CMotionTrail) {
    printf("CMotionTrail ** Bad Source Type-- Requesting Conversion from %s to %s\n", Py_TYPE(self)->tp_name, requested_type->_PyType.tp_name); fflush(nullptr);
    return nullptr;
  }

  CMotionTrail *local_this = (CMotionTrail *)DtoolInstance_VOID_PTR(self);
  if (requested_type == &Dtool_CMotionTrail) {
    return local_this;
  }
  if (requested_type == Dtool_Ptr_ReferenceCount) {
    return (ReferenceCount *)(TypedReferenceCount *) local_this;
  }
  if (requested_type == Dtool_Ptr_TypedObject) {
    return (TypedObject *)(TypedReferenceCount *) local_this;
  }
  if (requested_type == Dtool_Ptr_TypedReferenceCount) {
    return (TypedReferenceCount *) local_this;
  }
  return nullptr;
}

static void *Dtool_DowncastInterface_CMotionTrail(void *from_this, Dtool_PyTypedObject *from_type) {
  if (from_this == nullptr || from_type == nullptr) {
    return nullptr;
  }
  if (from_type == Dtool_Ptr_CMotionTrail) {
    return from_this;
  }
  if (from_type == Dtool_Ptr_ReferenceCount) {
    ReferenceCount* other_this = (ReferenceCount*)from_this;
    return (CMotionTrail*)other_this;
  }
  if (from_type == Dtool_Ptr_TypedObject) {
    TypedObject* other_this = (TypedObject*)from_this;
    return (CMotionTrail*)other_this;
  }
  if (from_type == Dtool_Ptr_TypedReferenceCount) {
    TypedReferenceCount* other_this = (TypedReferenceCount*)from_this;
    return (CMotionTrail*)other_this;
  }
  return nullptr;
}

/**
 * Python method tables for CMotionTrail (CMotionTrail)
 */
static PyMethodDef Dtool_Methods_CMotionTrail[] = {
  {"reset", &Dtool_CMotionTrail_reset_4, METH_NOARGS, (const char *)Dtool_CMotionTrail_reset_4_comment},
  {"reset_vertex_list", &Dtool_CMotionTrail_reset_vertex_list_5, METH_NOARGS, (const char *)Dtool_CMotionTrail_reset_vertex_list_5_comment},
  {"resetVertexList", &Dtool_CMotionTrail_reset_vertex_list_5, METH_NOARGS, (const char *)Dtool_CMotionTrail_reset_vertex_list_5_comment},
  {"enable", &Dtool_CMotionTrail_enable_6, METH_O, (const char *)Dtool_CMotionTrail_enable_6_comment},
  {"set_geom_node", &Dtool_CMotionTrail_set_geom_node_7, METH_O, (const char *)Dtool_CMotionTrail_set_geom_node_7_comment},
  {"setGeomNode", &Dtool_CMotionTrail_set_geom_node_7, METH_O, (const char *)Dtool_CMotionTrail_set_geom_node_7_comment},
  {"add_vertex", (PyCFunction) &Dtool_CMotionTrail_add_vertex_8, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_add_vertex_8_comment},
  {"addVertex", (PyCFunction) &Dtool_CMotionTrail_add_vertex_8, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_add_vertex_8_comment},
  {"set_parameters", (PyCFunction) &Dtool_CMotionTrail_set_parameters_9, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_set_parameters_9_comment},
  {"setParameters", (PyCFunction) &Dtool_CMotionTrail_set_parameters_9, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_set_parameters_9_comment},
  {"check_for_update", &Dtool_CMotionTrail_check_for_update_10, METH_O, (const char *)Dtool_CMotionTrail_check_for_update_10_comment},
  {"checkForUpdate", &Dtool_CMotionTrail_check_for_update_10, METH_O, (const char *)Dtool_CMotionTrail_check_for_update_10_comment},
  {"update_motion_trail", (PyCFunction) &Dtool_CMotionTrail_update_motion_trail_11, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_update_motion_trail_11_comment},
  {"updateMotionTrail", (PyCFunction) &Dtool_CMotionTrail_update_motion_trail_11, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_CMotionTrail_update_motion_trail_11_comment},
  {"get_class_type", &Dtool_CMotionTrail_get_class_type_12, METH_NOARGS | METH_STATIC, (const char *)Dtool_CMotionTrail_get_class_type_12_comment},
  {"getClassType", &Dtool_CMotionTrail_get_class_type_12, METH_NOARGS | METH_STATIC, (const char *)Dtool_CMotionTrail_get_class_type_12_comment},
  {"__copy__", &copy_from_copy_constructor, METH_NOARGS, nullptr},
  {"__deepcopy__", &map_deepcopy_to_copy, METH_VARARGS, nullptr},
  {nullptr, nullptr, 0, nullptr}
};

static PyNumberMethods Dtool_NumberMethods_CMotionTrail = {
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

static PySequenceMethods Dtool_SequenceMethods_CMotionTrail = {
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

static PyMappingMethods Dtool_MappingMethods_CMotionTrail = {
  nullptr,
  nullptr,
  nullptr,
};

static PyBufferProcs Dtool_BufferProcs_CMotionTrail = {
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
static PyAsyncMethods Dtool_AsyncMethods_CMotionTrail = {
  nullptr,
  nullptr,
  nullptr,
};
#endif

struct Dtool_PyTypedObject Dtool_CMotionTrail = {
  {
    PyVarObject_HEAD_INIT(nullptr, 0)
    "panda3d.direct.CMotionTrail",
    0, // tp_basicsize
    0, // tp_itemsize
    &Dtool_FreeInstance_CMotionTrail,
#if PY_VERSION_HEX >= 0x03080000
    0, // tp_vectorcall_offset
#else
    nullptr,
#endif
    nullptr,
    nullptr,
#if PY_VERSION_HEX >= 0x03050000
    &Dtool_AsyncMethods_CMotionTrail,
#elif PY_MAJOR_VERSION >= 3
    nullptr, // tp_reserved
#else
    nullptr, // tp_compare
#endif
    nullptr,
    &Dtool_NumberMethods_CMotionTrail,
    &Dtool_SequenceMethods_CMotionTrail,
    &Dtool_MappingMethods_CMotionTrail,
    nullptr, // tp_hash
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &Dtool_BufferProcs_CMotionTrail,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_CHECKTYPES,
#ifdef NDEBUG
    0,
#else
    "/**\n"
    " * The method used in creating the motion trail is based on taking samples of\n"
    " * time and transformations (the position and orientation matrix) in real-\n"
    " * time.  The method also requires a number of vertices (positions) that\n"
    " * determines \"shape\" of the motion trail (i.e.  the edge of a blade).  A\n"
    " * start color and end color is also required for each vertex.  The color is\n"
    " * interpolated as function of time.  The colors are typically used to fade\n"
    " * the motion trail so the end color is typically black.\n"
    " *\n"
    " * The vertices are submitted via the \"add_vertex\" function.  For each frame,\n"
    " * a sample is submited via the \"update_motion_trail\" function.  During the\n"
    " * \"update_motion_trail\" function, the motion trail geometry is created\n"
    " * dynamically from the sample history and the vertices.\n"
    " *\n"
    " * The user must specifiy a GeomNode via \"set_geom_node\".\n"
    " *\n"
    " * The duration of the sample history is specified by a time window.  A larger\n"
    " * time window creates longer motion trails (given constant speed).  Samples\n"
    " * that are no longer within the time window are automatically discarded.\n"
    " *\n"
    " * The nurbs option can be used to create smooth interpolated curves from the\n"
    " * samples.  The nurbs option is useful for animations that lack sampling to\n"
    " * begin with, animations that move very quickly, or low frame rates.\n"
    " *\n"
    " * The texture option be used to create variation to the motion trail.  The u\n"
    " * coordinate of the texture corresponds to time and the v coordinate\n"
    " * corresponds to the \"shape\" of the motion trail.\n"
    " */",
#endif
    nullptr, // tp_traverse
    nullptr, // tp_clear
    nullptr, // tp_richcompare
    0, // tp_weaklistoffset
    nullptr,
    nullptr,
    Dtool_Methods_CMotionTrail,
    nullptr, // tp_members
    nullptr, // tp_getset
    nullptr, // tp_base
    nullptr, // tp_dict
    nullptr,
    nullptr,
    0, // tp_dictoffset
    Dtool_Init_CMotionTrail,
    PyType_GenericAlloc,
    Dtool_new_CMotionTrail,
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
  Dtool_PyModuleClassInit_CMotionTrail,
  Dtool_UpcastInterface_CMotionTrail,
  Dtool_DowncastInterface_CMotionTrail,
  nullptr,
  nullptr,
};

static void Dtool_PyModuleClassInit_CMotionTrail(PyObject *module) {
  (void) module; // Unused
  static bool initdone = false;
  if (!initdone) {
    initdone = true;
    // Dependent objects
    assert(Dtool_Ptr_TypedReferenceCount != nullptr);
    assert(Dtool_Ptr_TypedReferenceCount->_Dtool_ModuleClassInit != nullptr);
    Dtool_Ptr_TypedReferenceCount->_Dtool_ModuleClassInit(nullptr);
    Dtool_CMotionTrail._PyType.tp_bases = PyTuple_Pack(1, (PyTypeObject *)Dtool_Ptr_TypedReferenceCount);
    Dtool_CMotionTrail._PyType.tp_base = (PyTypeObject *)Dtool_GetSuperBase();
    PyObject *dict = PyDict_New();
    Dtool_CMotionTrail._PyType.tp_dict = dict;
    PyDict_SetItemString(dict, "DtoolClassDict", dict);
    if (PyType_Ready((PyTypeObject *)&Dtool_CMotionTrail) < 0) {
      Dtool_Raise_TypeError("PyType_Ready(CMotionTrail)");
      return;
    }
    Py_INCREF((PyTypeObject *)&Dtool_CMotionTrail);
  }
}


/**
 * Module Object Linker ..
 */
void Dtool_libp3motiontrail_RegisterTypes() {
  TypeRegistry *registry = TypeRegistry::ptr();
  nassertv(registry != nullptr);
  {
    CMotionTrail::init_type();
    TypeHandle handle = CMotionTrail::get_class_type();
    Dtool_CMotionTrail._type = handle;
    registry->record_python_type(handle, (PyObject *)&Dtool_CMotionTrail);
  }
}

void Dtool_libp3motiontrail_BuildInstants(PyObject *module) {
  (void) module;
  // CMotionTrail
  Dtool_PyModuleClassInit_CMotionTrail(module);
  PyModule_AddObject(module, "CMotionTrail", (PyObject *)&Dtool_CMotionTrail);
}

static PyMethodDef python_simple_funcs[] = {
  // Support Function For Dtool_types ... for now in each module ??
  {"Dtool_BorrowThisReference", &Dtool_BorrowThisReference, METH_VARARGS, "Used to borrow 'this' pointer (to, from)\nAssumes no ownership."},
  {nullptr, nullptr, 0, nullptr}
};

#ifdef LINK_ALL_STATIC
extern const struct LibraryDef libp3motiontrail_moddef = {python_simple_funcs, exports, nullptr};
#else
extern const struct LibraryDef libp3motiontrail_moddef = {python_simple_funcs, exports, imports};
#endif
static InterrogateModuleDef _in_module_def = {
  1583614872,  /* file_identifier */
  "libp3motiontrail",  /* library_name */
  "HtUQ",  /* library_hash_name */
  "panda3d.direct",  /* module_name */
  "libp3motiontrail.in",  /* database_filename */
  nullptr,  /* unique_names */
  0,  /* num_unique_names */
  nullptr,  /* fptrs */
  0,  /* num_fptrs */
  1,  /* first_index */
  42  /* next_index */
};

Configure(_in_configure_libp3motiontrail);
ConfigureFn(_in_configure_libp3motiontrail) {
  interrogate_request_module(&_in_module_def);
}
