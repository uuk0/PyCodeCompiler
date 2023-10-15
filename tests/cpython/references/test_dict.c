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
PyObjectContainer* function_container___missing___1;
PyObjectContainer* function_container_test_constructor_2;
PyObjectContainer* function_container_test_merge_operator_3;
PyObjectContainer* function_container_test_bool_4;
PyObjectContainer* function_container_test_contains_5;
PyObjectContainer* function_container_test_len_6;
PyObjectContainer* function_container_test_getitem_7;
PyObjectContainer* function_container_test_clear_8;
PyObjectContainer* function_container_test_update_9;
PyObjectContainer* function_container_test_fromkeys_10;
PyObjectContainer* function_container_test_copy_11;
PyObjectContainer* function_container_test_get_12;
PyObjectContainer* function_container_test_setdefault_13;
PyObjectContainer* function_container_test_pop_14;
PyObjectContainer* function_container_test_repr_15;
PyObjectContainer* function_container_test_eq_16;
PyObjectContainer* function_container_test_missing_17;
PyObjectContainer* function_container_test_resize1_18;
PyClassContainer* PY_CLASS_DictTest_39;
PyObjectContainer* value_96;
PyObjectContainer* value_99;



// implementations

PyObjectContainer* PY_MODULE_test_dict_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_dict = PY_createModuleObject("test_dict");
    #endif
    PyObjectContainer* DictTest_39;
    PyObjectContainer* PY_CLASS_D_40;
    PyObjectContainer* unittest_41;
    function_container_g_0 = PY_createBoxForFunction(g_0_safeWrap);
    function_container___missing___1 = PY_createBoxForFunction(missing_3_safeWrap);
    function_container_test_constructor_2 = PY_createBoxForFunction(testconstructor_6_safeWrap);
    function_container_test_merge_operator_3 = PY_createBoxForFunction(testmergeoperator_8_safeWrap);
    function_container_test_bool_4 = PY_createBoxForFunction(testbool_10_safeWrap);
    function_container_test_contains_5 = PY_createBoxForFunction(testcontains_12_safeWrap);
    function_container_test_len_6 = PY_createBoxForFunction(testlen_14_safeWrap);
    function_container_test_getitem_7 = PY_createBoxForFunction(testgetitem_16_safeWrap);
    function_container_test_clear_8 = PY_createBoxForFunction(testclear_18_safeWrap);
    function_container_test_update_9 = PY_createBoxForFunction(testupdate_20_safeWrap);
    function_container_test_fromkeys_10 = PY_createBoxForFunction(testfromkeys_22_safeWrap);
    function_container_test_copy_11 = PY_createBoxForFunction(testcopy_24_safeWrap);
    function_container_test_get_12 = PY_createBoxForFunction(testget_26_safeWrap);
    function_container_test_setdefault_13 = PY_createBoxForFunction(testsetdefault_28_safeWrap);
    function_container_test_pop_14 = PY_createBoxForFunction(testpop_30_safeWrap);
    function_container_test_repr_15 = PY_createBoxForFunction(testrepr_32_safeWrap);
    function_container_test_eq_16 = PY_createBoxForFunction(testeq_34_safeWrap);
    function_container_test_missing_17 = PY_createBoxForFunction(testmissing_36_safeWrap);
    function_container_test_resize1_18 = PY_createBoxForFunction(testresize1_38_safeWrap);
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_41 = PY_MODULE_INSTANCE_unittest;




    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__missing__", (function_container___missing___1 = PY_createBoxForFunction(missing_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_constructor", (function_container_test_constructor_2 = PY_createBoxForFunction(testconstructor_6_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_merge_operator", (function_container_test_merge_operator_3 = PY_createBoxForFunction(testmergeoperator_8_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_bool", (function_container_test_bool_4 = PY_createBoxForFunction(testbool_10_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_contains", (function_container_test_contains_5 = PY_createBoxForFunction(testcontains_12_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_len", (function_container_test_len_6 = PY_createBoxForFunction(testlen_14_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_getitem", (function_container_test_getitem_7 = PY_createBoxForFunction(testgetitem_16_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_clear", (function_container_test_clear_8 = PY_createBoxForFunction(testclear_18_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_update", (function_container_test_update_9 = PY_createBoxForFunction(testupdate_20_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_fromkeys", (function_container_test_fromkeys_10 = PY_createBoxForFunction(testfromkeys_22_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_copy", (function_container_test_copy_11 = PY_createBoxForFunction(testcopy_24_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_get", (function_container_test_get_12 = PY_createBoxForFunction(testget_26_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault", (function_container_test_setdefault_13 = PY_createBoxForFunction(testsetdefault_28_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_pop", (function_container_test_pop_14 = PY_createBoxForFunction(testpop_30_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_repr", (function_container_test_repr_15 = PY_createBoxForFunction(testrepr_32_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_eq", (function_container_test_eq_16 = PY_createBoxForFunction(testeq_34_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_missing", (function_container_test_missing_17 = PY_createBoxForFunction(testmissing_36_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_resize1", (function_container_test_resize1_18 = PY_createBoxForFunction(testresize1_38_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_DictTest_39(&PY_CLASS_DictTest_39);

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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_D_4(PyClassContainer** cls) {
    // Create Class PY_CLASS_D_4 ('D' in source code)
    *cls = PY_createClassContainer("D");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'D'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_createClassWrapper(PY_TYPE_DICT)));
    PyObjectContainer* init_subclass_19 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_19 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_19, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__missing__", PY_createBoxForFunction(missing_3_safeWrap));


    return PY_NONE;
}

PyObjectContainer* missing_3(PyObjectContainer* self_1 , PyObjectContainer* key_2) {
    // Source Location: D.__missing__

    return PY_createInteger(42);


    return PY_NONE;
}

PyObjectContainer* missing_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = missing_3(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = missing_3(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_DictTest_39(PyClassContainer** cls) {
    // Create Class PY_CLASS_DictTest_39 ('DictTest' in source code)
    *cls = PY_createClassContainer("DictTest");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'DictTest'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_20 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_20 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_20, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_constructor", PY_createBoxForFunction(testconstructor_6_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_merge_operator", PY_createBoxForFunction(testmergeoperator_8_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_bool", PY_createBoxForFunction(testbool_10_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_contains", PY_createBoxForFunction(testcontains_12_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_len", PY_createBoxForFunction(testlen_14_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_getitem", PY_createBoxForFunction(testgetitem_16_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_clear", PY_createBoxForFunction(testclear_18_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_update", PY_createBoxForFunction(testupdate_20_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_fromkeys", PY_createBoxForFunction(testfromkeys_22_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_copy", PY_createBoxForFunction(testcopy_24_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_get", PY_createBoxForFunction(testget_26_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault", PY_createBoxForFunction(testsetdefault_28_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_pop", PY_createBoxForFunction(testpop_30_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_repr", PY_createBoxForFunction(testrepr_32_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_eq", PY_createBoxForFunction(testeq_34_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_missing", PY_createBoxForFunction(testmissing_36_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_resize1", PY_createBoxForFunction(testresize1_38_safeWrap));























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































    return PY_NONE;
}

PyObjectContainer* testconstructor_6(PyObjectContainer* self_5) {
    // Source Location: DictTest.test_constructor



    PyObjectContainer* obj_instance_22 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_22));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_22, PY_STD_dict_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_25 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_25));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_5, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {obj_instance_25, PY_STD_dict_CREATE(0)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testconstructor_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testconstructor_6(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testconstructor_6(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmergeoperator_8(PyObjectContainer* self_7) {
    // Source Location: DictTest.test_merge_operator
    PyObjectContainer* a_42;
    PyObjectContainer* b_43;
    PyObjectContainer* c_44;

    a_42 = PY_STD_dict_CREATE(3, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1));

    b_43 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));


    c_44 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (a_42));

    c_44 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_44 , b_43));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_42 , b_43)), PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_44, PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    c_44 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (b_43));

    c_44 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_44 , a_42));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (b_43 , a_42)), PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_44, PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));




























    return PY_NONE;
}

PyObjectContainer* testmergeoperator_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmergeoperator_8(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmergeoperator_8(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testbool_10(PyObjectContainer* self_9) {
    // Source Location: DictTest.test_bool

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_not(PY_STD_dict_CREATE(0)), PY_TRUE}, NULL));

    PyObjectContainer* temporary_32 = PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertTrue"), NULL, 1, &temporary_32, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(0))), PY_FALSE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)))), PY_TRUE}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbool_10_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbool_10(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbool_10(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcontains_12(PyObjectContainer* self_11) {
    // Source Location: DictTest.test_contains
    PyObjectContainer* d_45;

    d_45 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_45}, NULL));

    PyObjectContainer* temporary_36 = PY_STD_operator_contains(d_45, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertFalse"), NULL, 1, &temporary_36, NULL));

    PyObjectContainer* temporary_37 = PY_STD_operator_not_contains(d_45, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertTrue"), NULL, 1, &temporary_37, NULL));


    d_45 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_45}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), d_45}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("c"), d_45}, NULL));





    return PY_NONE;
}

PyObjectContainer* testcontains_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcontains_12(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcontains_12(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlen_14(PyObjectContainer* self_13) {
    // Source Location: DictTest.test_len
    PyObjectContainer* d_46;

    d_46 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_13, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_46)), PY_createInteger(0)}, NULL));

    d_46 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_13, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_46)), PY_createInteger(2)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlen_14_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlen_14(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlen_14(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testgetitem_16(PyObjectContainer* self_15) {
    // Source Location: DictTest.test_getitem
    PyObjectContainer* d_47;

    d_47 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_47 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_47 , PY_createString("b"))), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_47 , PY_createString("c") , PY_createInteger(3)));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_47 , PY_createString("a") , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_47 , PY_createString("c"))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_15, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_47 , PY_createString("a"))), PY_createInteger(4)}, NULL));


























































    return PY_NONE;
}

PyObjectContainer* testgetitem_16_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testgetitem_16(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testgetitem_16(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testclear_18(PyObjectContainer* self_17) {
    // Source Location: DictTest.test_clear
    PyObjectContainer* d_48;

    d_48 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_48));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_48, PY_STD_dict_CREATE(0)}, NULL));





    return PY_NONE;
}

PyObjectContainer* testclear_18_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testclear_18(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testclear_18(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testupdate_20(PyObjectContainer* self_19) {
    // Source Location: DictTest.test_update
    PyObjectContainer* d_49;

    d_49 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_49, PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(100))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_49, PY_STD_dict_CREATE(1, PY_createInteger(2), PY_createInteger(20))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_49, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_49, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    PyObjectContainer* temporary_52 = d_49;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 1, &temporary_52, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_19, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_49, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));















































































































































    return PY_NONE;
}

PyObjectContainer* testupdate_20_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testupdate_20(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testupdate_20(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testfromkeys_22(PyObjectContainer* self_21) {
    // Source Location: DictTest.test_fromkeys
    PyObjectContainer* d_50;
    PyObjectContainer* g_0;

    PyObjectContainer* temporary_55 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_createClassWrapper(PY_TYPE_DICT), "fromkeys"), NULL, 1, &temporary_55, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    d_50 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_50 , PY_createString("abc"))), d_50}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_50 , PY_createString("abc"))), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_2 (d_50 , PY_STD_tuple_CREATE(2, PY_createInteger(4), PY_createInteger(5)) , PY_createInteger(0))), PY_STD_dict_CREATE(2, PY_createInteger(4), PY_createInteger(0), PY_createInteger(5), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_50 , PY_STD_list_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));


    g_0 = function_container_g_0;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_fromkeys_fast_arg_1 (d_50 , PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(g_0, NULL, 0, NULL, NULL)))), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_NONE)}, NULL));

































































































    return PY_NONE;
}

PyObjectContainer* testfromkeys_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testfromkeys_22(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testfromkeys_22(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcopy_24(PyObjectContainer* self_23) {
    // Source Location: DictTest.test_copy
    PyObjectContainer* copy_51;
    PyObjectContainer* d_52;

    d_52 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_52)), d_52}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_52)), d_52}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_52)), PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    copy_51 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_52));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_52 , PY_createInteger(4) , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertNotEqual"), NULL, 2, (PyObjectContainer*[]) {copy_51, d_52}, NULL));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_23, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (PY_STD_dict_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));




    return PY_NONE;
}

PyObjectContainer* testcopy_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcopy_24(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcopy_24(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testget_26(PyObjectContainer* self_25) {
    // Source Location: DictTest.test_get
    PyObjectContainer* d_53;

    d_53 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_53 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_53 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    d_53 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_53 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_53 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_53 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_53 , PY_createString("a") , PY_createInteger(3))), PY_createInteger(1)}, NULL));






    return PY_NONE;
}

PyObjectContainer* testget_26_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testget_26(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testget_26(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefault_28(PyObjectContainer* self_27) {
    // Source Location: DictTest.test_setdefault
    PyObjectContainer* d_54;



    d_54 = PY_STD_dict_CREATE(1, PY_createString("key0"), PY_NONE);



    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (d_54 , PY_createString("key0") , PY_STD_list_CREATE(0)));



    PyObjectContainer* temporary_72 = PY_createInteger(3);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_54, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_72, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(PY_GetSubscriptionValue(d_54, PY_createString("key")), PY_createInteger(0)), PY_createInteger(3)}, NULL));

    PyObjectContainer* temporary_75 = PY_createInteger(4);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_54, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_75, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_operator_len (PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_54 , PY_createString("key"))))), PY_createInteger(2)}, NULL));


































    return PY_NONE;
}

PyObjectContainer* testsetdefault_28_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefault_28(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefault_28(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testpop_30(PyObjectContainer* self_29) {
    // Source Location: DictTest.test_pop
    PyObjectContainer* d_55;
    PyObjectContainer* k_56;
    PyObjectContainer* v_57;



    d_55 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_tuple_78 = PY_STD_tuple_CREATE(2, PY_createString("abc"), PY_createString("def"));
    assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_78)) == 2);
    k_56 = PY_GetSubscriptionValue(temporary_tuple_78, PY_createInteger(0));
    v_57 = PY_GetSubscriptionValue(temporary_tuple_78, PY_createInteger(1));
    ;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_55 , k_56 , v_57));




    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_1 (d_55 , k_56)), v_57}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_55)), PY_createInteger(0)}, NULL));





    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_55 , k_56 , v_57)), v_57}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_55 , k_56 , v_57));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_55 , k_56 , PY_createInteger(1))), v_57}, NULL));



































    return PY_NONE;
}

PyObjectContainer* testpop_30_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testpop_30(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testpop_30(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testrepr_32(PyObjectContainer* self_31) {
    // Source Location: DictTest.test_repr
    PyObjectContainer* d_58;

    d_58 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_31, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_58)), PY_createString("{}")}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_58 , PY_createInteger(1) , PY_createInteger(2)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_31, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_58)), PY_createString("{1: 2}")}, NULL));






























    return PY_NONE;
}

PyObjectContainer* testrepr_32_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testrepr_32(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testrepr_32(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testeq_34(PyObjectContainer* self_33) {
    // Source Location: DictTest.test_eq

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_33, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(0), PY_STD_dict_CREATE(0)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_33, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2))}, NULL));





























    return PY_NONE;
}

PyObjectContainer* testeq_34_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testeq_34(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testeq_34(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmissing_36(PyObjectContainer* self_35) {
    // Source Location: DictTest.test_missing
    PyObjectContainer* D_4;
    PyObjectContainer* d_59;



    PyObjectContainer* temporary_87 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_createClassWrapper(PY_TYPE_DICT) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertFalse"), NULL, 1, &temporary_87, NULL));

    PyObjectContainer* temporary_88 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_STD_dict_CREATE(0) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertFalse"), NULL, 1, &temporary_88, NULL));












    D_4 = PY_createClass("D", PY_CLASS_INIT_PY_CLASS_D_4);
    PyObjectContainer* temporary_89 = PY_STD_dict_CREATE(2, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3), PY_createInteger(4));
    d_59 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(D_4, NULL, 1, &temporary_89, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_59, PY_createInteger(1)), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_59, PY_createInteger(3)), PY_createInteger(4)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), d_59}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_59, "keys"), NULL, 0, NULL, NULL))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_35, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_59, PY_createInteger(2)), PY_createInteger(42)}, NULL));


















































    return PY_NONE;
}

PyObjectContainer* testmissing_36_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmissing_36(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmissing_36(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testresize1_38(PyObjectContainer* self_37) {
    // Source Location: DictTest.test_resize1
    PyObjectContainer* d_60;
    PyObjectContainer* i_61;














    d_60 = PY_STD_dict_CREATE(0);

    PyObjectContainer* iterator_95 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(5)))));
    PyObjectContainer* value_96 = PY_STD_NEXT_FORWARD_arg_1(iterator_95, NULL);
    while (value_96 != NULL) {
        PY_CHECK_EXCEPTION(value_96);
        i_61 = value_96;
        PyObjectContainer* temp_97 = i_61;
        PY_SetSubscriptionValue(d_60, temp_97, i_61);

        value_96 = PY_STD_NEXT_FORWARD_arg_1(iterator_95, NULL);
    }




    PyObjectContainer* iterator_98 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_2 (PY_createInteger(5) , PY_createInteger(9)))));
    PyObjectContainer* value_99 = PY_STD_NEXT_FORWARD_arg_1(iterator_98, NULL);
    while (value_99 != NULL) {
        PY_CHECK_EXCEPTION(value_99);
        i_61 = value_99;


        PyObjectContainer* temp_100 = i_61;
        PY_SetSubscriptionValue(d_60, temp_100, i_61);


        value_99 = PY_STD_NEXT_FORWARD_arg_1(iterator_98, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* testresize1_38_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testresize1_38(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testresize1_38(self);
    }

    if (info) free(new_args);
    return result;
}

