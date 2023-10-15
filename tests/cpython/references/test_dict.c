#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_dict.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_dict;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include "standard_library/generator.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_g_0;
PyObjectContainer* function_container_test_constructor_1;
PyObjectContainer* function_container_test_merge_operator_2;
PyObjectContainer* function_container_test_bool_3;
PyObjectContainer* function_container_test_contains_4;
PyObjectContainer* function_container_test_len_5;
PyObjectContainer* function_container_test_getitem_6;
PyObjectContainer* function_container_test_clear_7;
PyObjectContainer* function_container_test_update_8;
PyObjectContainer* function_container_test_fromkeys_9;
PyObjectContainer* function_container_test_copy_10;
PyObjectContainer* function_container_test_get_11;
PyObjectContainer* function_container_test_setdefault_12;
PyObjectContainer* function_container_test_pop_13;
PyObjectContainer* function_container_test_repr_14;
PyObjectContainer* function_container_test_eq_15;
PyObjectContainer* function_container_test_resize1_16;
PyClassContainer* PY_CLASS_DictTest_33;
PyObjectContainer* value_82;
PyObjectContainer* value_85;



// implementations

PyObjectContainer* PY_MODULE_test_dict_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_dict = PY_createModuleObject("test_dict");
    #endif
    PyObjectContainer* DictTest_33;
    PyObjectContainer* unittest_34;
    function_container_g_0 = PY_createBoxForFunction(g_0_safeWrap);
    function_container_test_constructor_1 = PY_createBoxForFunction(testconstructor_2_safeWrap);
    function_container_test_merge_operator_2 = PY_createBoxForFunction(testmergeoperator_4_safeWrap);
    function_container_test_bool_3 = PY_createBoxForFunction(testbool_6_safeWrap);
    function_container_test_contains_4 = PY_createBoxForFunction(testcontains_8_safeWrap);
    function_container_test_len_5 = PY_createBoxForFunction(testlen_10_safeWrap);
    function_container_test_getitem_6 = PY_createBoxForFunction(testgetitem_12_safeWrap);
    function_container_test_clear_7 = PY_createBoxForFunction(testclear_14_safeWrap);
    function_container_test_update_8 = PY_createBoxForFunction(testupdate_16_safeWrap);
    function_container_test_fromkeys_9 = PY_createBoxForFunction(testfromkeys_18_safeWrap);
    function_container_test_copy_10 = PY_createBoxForFunction(testcopy_20_safeWrap);
    function_container_test_get_11 = PY_createBoxForFunction(testget_22_safeWrap);
    function_container_test_setdefault_12 = PY_createBoxForFunction(testsetdefault_24_safeWrap);
    function_container_test_pop_13 = PY_createBoxForFunction(testpop_26_safeWrap);
    function_container_test_repr_14 = PY_createBoxForFunction(testrepr_28_safeWrap);
    function_container_test_eq_15 = PY_createBoxForFunction(testeq_30_safeWrap);
    function_container_test_resize1_16 = PY_createBoxForFunction(testresize1_32_safeWrap);
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_34 = PY_MODULE_INSTANCE_unittest;




    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_constructor", (function_container_test_constructor_1 = PY_createBoxForFunction(testconstructor_2_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_merge_operator", (function_container_test_merge_operator_2 = PY_createBoxForFunction(testmergeoperator_4_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_bool", (function_container_test_bool_3 = PY_createBoxForFunction(testbool_6_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_contains", (function_container_test_contains_4 = PY_createBoxForFunction(testcontains_8_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_len", (function_container_test_len_5 = PY_createBoxForFunction(testlen_10_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_getitem", (function_container_test_getitem_6 = PY_createBoxForFunction(testgetitem_12_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_clear", (function_container_test_clear_7 = PY_createBoxForFunction(testclear_14_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_update", (function_container_test_update_8 = PY_createBoxForFunction(testupdate_16_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_fromkeys", (function_container_test_fromkeys_9 = PY_createBoxForFunction(testfromkeys_18_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_copy", (function_container_test_copy_10 = PY_createBoxForFunction(testcopy_20_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_get", (function_container_test_get_11 = PY_createBoxForFunction(testget_22_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault", (function_container_test_setdefault_12 = PY_createBoxForFunction(testsetdefault_24_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_pop", (function_container_test_pop_13 = PY_createBoxForFunction(testpop_26_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_repr", (function_container_test_repr_14 = PY_createBoxForFunction(testrepr_28_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_eq", (function_container_test_eq_15 = PY_createBoxForFunction(testeq_30_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_resize1", (function_container_test_resize1_16 = PY_createBoxForFunction(testresize1_32_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_DictTest_33(&PY_CLASS_DictTest_33);

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_dict);
    #endif
}

PyObjectContainer* g_0(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = g_0_ENTRY;
    return generator;
}

PyObjectContainer* g_0_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
    };

    gen_0:;

    generator->section_id = 1;
    return PY_createInteger(1);
    gen_1:;


    return NULL;
}

PyObjectContainer* g_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return g_0();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_DictTest_33(PyClassContainer** cls) {
    // Create Class PY_CLASS_DictTest_33 ('DictTest' in source code)
    *cls = PY_createClassContainer("DictTest");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'DictTest'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_17 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_17 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_17, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_constructor", PY_createBoxForFunction(testconstructor_2_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_merge_operator", PY_createBoxForFunction(testmergeoperator_4_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_bool", PY_createBoxForFunction(testbool_6_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_contains", PY_createBoxForFunction(testcontains_8_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_len", PY_createBoxForFunction(testlen_10_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_getitem", PY_createBoxForFunction(testgetitem_12_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_clear", PY_createBoxForFunction(testclear_14_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_update", PY_createBoxForFunction(testupdate_16_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_fromkeys", PY_createBoxForFunction(testfromkeys_18_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_copy", PY_createBoxForFunction(testcopy_20_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_get", PY_createBoxForFunction(testget_22_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault", PY_createBoxForFunction(testsetdefault_24_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_pop", PY_createBoxForFunction(testpop_26_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_repr", PY_createBoxForFunction(testrepr_28_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_eq", PY_createBoxForFunction(testeq_30_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_resize1", PY_createBoxForFunction(testresize1_32_safeWrap));













































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































    return PY_NONE;
}

PyObjectContainer* testconstructor_2(PyObjectContainer* self_1) {
    // Source Location: DictTest.test_constructor



    PyObjectContainer* obj_instance_19 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_19));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_1, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_19, PY_STD_dict_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_22 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_22));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_1, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {obj_instance_22, PY_STD_dict_CREATE(0)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testconstructor_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testconstructor_2(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testconstructor_2(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmergeoperator_4(PyObjectContainer* self_3) {
    // Source Location: DictTest.test_merge_operator
    PyObjectContainer* a_35;
    PyObjectContainer* b_36;
    PyObjectContainer* c_37;

    a_35 = PY_STD_dict_CREATE(3, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1));

    b_36 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));


    c_37 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (a_35));

    c_37 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_37 , b_36));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_3, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_bin_or(a_35, b_36), PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_3, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_37, PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    c_37 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (b_36));

    c_37 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_37 , a_35));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_3, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_bin_or(b_36, a_35), PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_3, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_37, PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));




























    return PY_NONE;
}

PyObjectContainer* testmergeoperator_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmergeoperator_4(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmergeoperator_4(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testbool_6(PyObjectContainer* self_5) {
    // Source Location: DictTest.test_bool

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_not(PY_STD_dict_CREATE(0)), PY_TRUE}, NULL));

    PyObjectContainer* temporary_29 = PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertTrue"), NULL, 1, &temporary_29, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(0))), PY_FALSE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)))), PY_TRUE}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbool_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbool_6(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbool_6(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcontains_8(PyObjectContainer* self_7) {
    // Source Location: DictTest.test_contains
    PyObjectContainer* d_38;

    d_38 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_38}, NULL));

    PyObjectContainer* temporary_33 = PY_STD_operator_contains(d_38, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertFalse"), NULL, 1, &temporary_33, NULL));

    PyObjectContainer* temporary_34 = PY_STD_operator_not_contains(d_38, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertTrue"), NULL, 1, &temporary_34, NULL));


    d_38 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_38}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), d_38}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("c"), d_38}, NULL));





    return PY_NONE;
}

PyObjectContainer* testcontains_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcontains_8(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcontains_8(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlen_10(PyObjectContainer* self_9) {
    // Source Location: DictTest.test_len
    PyObjectContainer* d_39;

    d_39 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_39)), PY_createInteger(0)}, NULL));

    d_39 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_39)), PY_createInteger(2)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlen_10_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlen_10(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlen_10(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testgetitem_12(PyObjectContainer* self_11) {
    // Source Location: DictTest.test_getitem
    PyObjectContainer* d_40;

    d_40 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_40 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_40 , PY_createString("b"))), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_40 , PY_createString("c") , PY_createInteger(3)));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_40 , PY_createString("a") , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_40 , PY_createString("c"))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_40 , PY_createString("a"))), PY_createInteger(4)}, NULL));


























































    return PY_NONE;
}

PyObjectContainer* testgetitem_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testgetitem_12(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testgetitem_12(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testclear_14(PyObjectContainer* self_13) {
    // Source Location: DictTest.test_clear
    PyObjectContainer* d_41;

    d_41 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_41));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_13, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_41, PY_STD_dict_CREATE(0)}, NULL));





    return PY_NONE;
}

PyObjectContainer* testclear_14_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testclear_14(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testclear_14(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testupdate_16(PyObjectContainer* self_15) {
    // Source Location: DictTest.test_update
    PyObjectContainer* d_42;

    d_42 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_concat_inplace_fast (d_42 , PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(100))));

    PY_CHECK_EXCEPTION(PY_STD_dict_concat_inplace_fast (d_42 , PY_STD_dict_CREATE(1, PY_createInteger(2), PY_createInteger(20))));

    PY_CHECK_EXCEPTION(PY_STD_dict_concat_inplace_fast (d_42 , PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_42, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    PyObjectContainer* temporary_46 = d_42;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 1, &temporary_46, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_42, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));















































































































































    return PY_NONE;
}

PyObjectContainer* testupdate_16_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testupdate_16(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testupdate_16(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testfromkeys_18(PyObjectContainer* self_17) {
    // Source Location: DictTest.test_fromkeys
    PyObjectContainer* d_43;
    PyObjectContainer* g_0;

    PyObjectContainer* temporary_49 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_createClassWrapper(PY_TYPE_DICT), "fromkeys"), NULL, 1, &temporary_49, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    d_43 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_43 , PY_createString("abc"))), d_43}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_43 , PY_createString("abc"))), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_2 (d_43 , PY_STD_tuple_CREATE(2, PY_createInteger(4), PY_createInteger(5)) , PY_createInteger(0))), PY_STD_dict_CREATE(2, PY_createInteger(4), PY_createInteger(0), PY_createInteger(5), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_43 , PY_STD_list_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));


    g_0 = function_container_g_0;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_43 , PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(g_0, NULL, 0, NULL, NULL)))), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_NONE)}, NULL));

































































































    return PY_NONE;
}

PyObjectContainer* testfromkeys_18_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testfromkeys_18(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testfromkeys_18(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcopy_20(PyObjectContainer* self_19) {
    // Source Location: DictTest.test_copy
    PyObjectContainer* copy_44;
    PyObjectContainer* d_45;

    d_45 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_45)), d_45}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_45)), d_45}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_45)), PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    copy_44 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_45));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_45 , PY_createInteger(4) , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertNotEqual"), NULL, 2, (PyObjectContainer*[]) {copy_44, d_45}, NULL));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (PY_STD_dict_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));




    return PY_NONE;
}

PyObjectContainer* testcopy_20_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcopy_20(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcopy_20(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testget_22(PyObjectContainer* self_21) {
    // Source Location: DictTest.test_get
    PyObjectContainer* d_46;

    d_46 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_1 (d_46 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_46 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    d_46 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_1 (d_46 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_46 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_1 (d_46 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_46 , PY_createString("a") , PY_createInteger(3))), PY_createInteger(1)}, NULL));






    return PY_NONE;
}

PyObjectContainer* testget_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testget_22(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testget_22(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefault_24(PyObjectContainer* self_23) {
    // Source Location: DictTest.test_setdefault
    PyObjectContainer* d_47;



    d_47 = PY_STD_dict_CREATE(1, PY_createString("key0"), PY_NONE);



    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (d_47 , PY_createString("key0") , PY_STD_list_CREATE(0)));



    PyObjectContainer* temporary_66 = PY_createInteger(3);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_47, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_66, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(PY_GetSubscriptionValue(d_47, PY_createString("key")), PY_createInteger(0)), PY_createInteger(3)}, NULL));

    PyObjectContainer* temporary_69 = PY_createInteger(4);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_47, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_69, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_operator_len (PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_47 , PY_createString("key"))))), PY_createInteger(2)}, NULL));


































    return PY_NONE;
}

PyObjectContainer* testsetdefault_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefault_24(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefault_24(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testpop_26(PyObjectContainer* self_25) {
    // Source Location: DictTest.test_pop
    PyObjectContainer* d_48;
    PyObjectContainer* k_49;
    PyObjectContainer* v_50;



    d_48 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_tuple_72 = PY_STD_tuple_CREATE(2, PY_createString("abc"), PY_createString("def"));
    assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_72)) == 2);
    k_49 = PY_GetSubscriptionValue(temporary_tuple_72, PY_createInteger(0));
    v_50 = PY_GetSubscriptionValue(temporary_tuple_72, PY_createInteger(1));
    ;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_48 , k_49 , v_50));




    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_1 (d_48 , k_49)), v_50}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_48)), PY_createInteger(0)}, NULL));





    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_48 , k_49 , v_50)), v_50}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_48 , k_49 , v_50));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_48 , k_49 , PY_createInteger(1))), v_50}, NULL));



































    return PY_NONE;
}

PyObjectContainer* testpop_26_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testpop_26(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testpop_26(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testrepr_28(PyObjectContainer* self_27) {
    // Source Location: DictTest.test_repr
    PyObjectContainer* d_51;

    d_51 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_51)), PY_createString("{}")}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_51 , PY_createInteger(1) , PY_createInteger(2)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_51)), PY_createString("{1: 2}")}, NULL));






























    return PY_NONE;
}

PyObjectContainer* testrepr_28_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testrepr_28(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testrepr_28(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testeq_30(PyObjectContainer* self_29) {
    // Source Location: DictTest.test_eq

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(0), PY_STD_dict_CREATE(0)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2))}, NULL));





























    return PY_NONE;
}

PyObjectContainer* testeq_30_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testeq_30(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testeq_30(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testresize1_32(PyObjectContainer* self_31) {
    // Source Location: DictTest.test_resize1
    PyObjectContainer* d_52;
    PyObjectContainer* i_53;














    d_52 = PY_STD_dict_CREATE(0);

    PyObjectContainer* iterator_81 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(5)))));
    PyObjectContainer* value_82 = PY_STD_NEXT_FORWARD_arg_1(iterator_81, NULL);
    while (value_82 != NULL) {
        PY_CHECK_EXCEPTION(value_82);
        i_53 = value_82;
        PyObjectContainer* temp_83 = i_53;
        PY_SetSubscriptionValue(d_52, temp_83, i_53);

        value_82 = PY_STD_NEXT_FORWARD_arg_1(iterator_81, NULL);
    }




    PyObjectContainer* iterator_84 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_2 (PY_createInteger(5) , PY_createInteger(9)))));
    PyObjectContainer* value_85 = PY_STD_NEXT_FORWARD_arg_1(iterator_84, NULL);
    while (value_85 != NULL) {
        PY_CHECK_EXCEPTION(value_85);
        i_53 = value_85;


        PyObjectContainer* temp_86 = i_53;
        PY_SetSubscriptionValue(d_52, temp_86, i_53);


        value_85 = PY_STD_NEXT_FORWARD_arg_1(iterator_84, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* testresize1_32_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testresize1_32(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testresize1_32(self);
    }

    if (info) free(new_args);
    return result;
}

