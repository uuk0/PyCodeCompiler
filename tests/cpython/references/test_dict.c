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
#include <assert.h>
#include "standard_library/generator.h"



// Global Variables
PyObjectContainer* function_container___init___0;
PyObjectContainer* function_container_keys_1;
PyObjectContainer* function_container___getitem___2;
PyObjectContainer* function_container_g_3;
PyObjectContainer* function_container___init___4;
PyObjectContainer* function_container___hash___5;
PyObjectContainer* function_container___eq___6;
PyObjectContainer* function_container___init___7;
PyObjectContainer* function_container___hash___8;
PyObjectContainer* function_container___eq___9;
PyObjectContainer* function_container___missing___10;
PyObjectContainer* function_container_test_constructor_11;
PyObjectContainer* function_container_test_merge_operator_12;
PyObjectContainer* function_container_test_bool_13;
PyObjectContainer* function_container_test_contains_14;
PyObjectContainer* function_container_test_len_15;
PyObjectContainer* function_container_test_getitem_16;
PyObjectContainer* function_container_test_clear_17;
PyObjectContainer* function_container_test_update_18;
PyObjectContainer* function_container_test_fromkeys_19;
PyObjectContainer* function_container_test_copy_20;
PyObjectContainer* function_container_test_get_21;
PyObjectContainer* function_container_test_setdefault_22;
PyObjectContainer* function_container_test_setdefault_atomic_23;
PyObjectContainer* function_container_test_setitem_atomic_at_resize_24;
PyObjectContainer* function_container_test_pop_25;
PyObjectContainer* function_container_test_mutating_iteration_26;
PyObjectContainer* function_container_test_mutating_iteration_delete_27;
PyObjectContainer* function_container_test_mutating_iteration_delete_over_values_28;
PyObjectContainer* function_container_test_mutating_iteration_delete_over_items_29;
PyObjectContainer* function_container_test_repr_30;
PyObjectContainer* function_container_test_eq_31;
PyObjectContainer* function_container_test_missing_32;
PyObjectContainer* function_container_test_resize1_33;
PyObjectContainer* function_container_test_string_keys_can_track_values_34;
PyObjectContainer* function_container_make_shared_key_dict_35;
PyObjectContainer* function_container_test_object_set_item_single_instance_non_str_key_36;
PyClassContainer* PY_CLASS_DictTest_85;
PyObjectContainer* value_152;
PyObjectContainer* value_155;
PyObjectContainer* value_158;
PyObjectContainer* value_160;
PyObjectContainer* value_164;



// implementations

PyObjectContainer* PY_MODULE_test_dict_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_dict = PY_createModuleObject("test_dict");
    #endif
    PyObjectContainer* DictTest_85;
    PyObjectContainer* PY_CLASS_C_86;
    PyObjectContainer* PY_CLASS_D_87;
    PyObjectContainer* PY_CLASS_Foo_88;
    PyObjectContainer* PY_CLASS_Hashed_89;
    PyObjectContainer* PY_CLASS_SimpleUserDict_90;
    PyObjectContainer* PY_CLASS_dictlike_91;
    PyObjectContainer* unittest_92;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_92 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__init__", (function_container___init___0 = PY_createBoxForFunction(init_1_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "keys", (function_container_keys_1 = PY_createBoxForFunction(keys_3_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__getitem__", (function_container___getitem___2 = PY_createBoxForFunction(getitem_6_safeWrap)));
    #endif



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__init__", (function_container___init___4 = PY_createBoxForFunction(init_11_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__hash__", (function_container___hash___5 = PY_createBoxForFunction(hash_13_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__eq__", (function_container___eq___6 = PY_createBoxForFunction(eq_16_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__init__", (function_container___init___7 = PY_createBoxForFunction(init_19_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__hash__", (function_container___hash___8 = PY_createBoxForFunction(hash_21_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__eq__", (function_container___eq___9 = PY_createBoxForFunction(eq_24_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "__missing__", (function_container___missing___10 = PY_createBoxForFunction(missing_28_safeWrap)));
    #endif



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_constructor", (function_container_test_constructor_11 = PY_createBoxForFunction(testconstructor_33_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_merge_operator", (function_container_test_merge_operator_12 = PY_createBoxForFunction(testmergeoperator_35_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_bool", (function_container_test_bool_13 = PY_createBoxForFunction(testbool_37_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_contains", (function_container_test_contains_14 = PY_createBoxForFunction(testcontains_39_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_len", (function_container_test_len_15 = PY_createBoxForFunction(testlen_41_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_getitem", (function_container_test_getitem_16 = PY_createBoxForFunction(testgetitem_43_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_clear", (function_container_test_clear_17 = PY_createBoxForFunction(testclear_45_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_update", (function_container_test_update_18 = PY_createBoxForFunction(testupdate_47_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_fromkeys", (function_container_test_fromkeys_19 = PY_createBoxForFunction(testfromkeys_49_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_copy", (function_container_test_copy_20 = PY_createBoxForFunction(testcopy_51_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_get", (function_container_test_get_21 = PY_createBoxForFunction(testget_53_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault", (function_container_test_setdefault_22 = PY_createBoxForFunction(testsetdefault_55_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault_atomic", (function_container_test_setdefault_atomic_23 = PY_createBoxForFunction(testsetdefaultatomic_57_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setitem_atomic_at_resize", (function_container_test_setitem_atomic_at_resize_24 = PY_createBoxForFunction(testsetitematomicatresize_59_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_pop", (function_container_test_pop_25 = PY_createBoxForFunction(testpop_61_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration", (function_container_test_mutating_iteration_26 = PY_createBoxForFunction(testmutatingiteration_63_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete", (function_container_test_mutating_iteration_delete_27 = PY_createBoxForFunction(testmutatingiterationdelete_65_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete_over_values", (function_container_test_mutating_iteration_delete_over_values_28 = PY_createBoxForFunction(testmutatingiterationdeleteovervalues_67_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete_over_items", (function_container_test_mutating_iteration_delete_over_items_29 = PY_createBoxForFunction(testmutatingiterationdeleteoveritems_69_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_repr", (function_container_test_repr_30 = PY_createBoxForFunction(testrepr_71_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_eq", (function_container_test_eq_31 = PY_createBoxForFunction(testeq_73_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_missing", (function_container_test_missing_32 = PY_createBoxForFunction(testmissing_75_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_resize1", (function_container_test_resize1_33 = PY_createBoxForFunction(testresize1_77_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_string_keys_can_track_values", (function_container_test_string_keys_can_track_values_34 = PY_createBoxForFunction(teststringkeyscantrackvalues_79_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "make_shared_key_dict", (function_container_make_shared_key_dict_35 = PY_createBoxForFunction(makesharedkeydict_82_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_object_set_item_single_instance_non_str_key", (function_container_test_object_set_item_single_instance_non_str_key_36 = PY_createBoxForFunction(testobjectsetitemsingleinstancenonstrkey_84_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_DictTest_85(&PY_CLASS_DictTest_85);

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_dict);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_SimpleUserDict_7(PyClassContainer** cls) {
    // Create Class PY_CLASS_SimpleUserDict_7 ('SimpleUserDict' in source code)
    *cls = PY_createClassContainer("SimpleUserDict");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'SimpleUserDict'
    (*cls)->parents[0] = PY_TYPE_OBJECT;
    PY_ClassContainer_DeclareObjectAttribute(*cls, "d");

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__init__", PY_createBoxForFunction(init_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "keys", PY_createBoxForFunction(keys_3_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__getitem__", PY_createBoxForFunction(getitem_6_safeWrap));




    return PY_NONE;
}

PyObjectContainer* init_1(PyObjectContainer* self_0) {
    // Source Location: SimpleUserDict.__init__

    PyObjectContainer* temp_37 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));
    PY_setObjectAttributeByName(self_0, "d", temp_37);


    return PY_NONE;
}

PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = init_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = init_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* keys_3(PyObjectContainer* self_2) {
    // Source Location: SimpleUserDict.keys

    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_2, "d"), "keys"), NULL, 0, NULL, NULL));


    return PY_NONE;
}

PyObjectContainer* keys_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = keys_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = keys_3(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* getitem_6(PyObjectContainer* self_4 , PyObjectContainer* i_5) {
    // Source Location: SimpleUserDict.__getitem__

    return PY_GetSubscriptionValue(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_4, "d"), i_5);


    return PY_NONE;
}

PyObjectContainer* getitem_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = getitem_6(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = getitem_6(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* g_8(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = g_8_ENTRY;
    return generator;
}

PyObjectContainer* g_8_ENTRY(PyGeneratorContainer* generator) {
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

PyObjectContainer* g_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return g_8();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_dictlike_9(PyClassContainer** cls) {
    // Create Class PY_CLASS_dictlike_9 ('dictlike' in source code)
    *cls = PY_createClassContainer("dictlike");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'dictlike'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_createClassWrapper(PY_TYPE_DICT)));
    PyObjectContainer* init_subclass_38 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_38 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_38, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes



    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Hashed_17(PyClassContainer** cls) {
    // Create Class PY_CLASS_Hashed_17 ('Hashed' in source code)
    *cls = PY_createClassContainer("Hashed");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Hashed'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_createClassWrapper(PY_TYPE_OBJECT)));
    PyObjectContainer* init_subclass_39 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_39 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_39, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);
    PY_ClassContainer_DeclareObjectAttribute(*cls, "hash_count");
    PY_ClassContainer_DeclareObjectAttribute(*cls, "eq_count");

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__init__", PY_createBoxForFunction(init_11_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__hash__", PY_createBoxForFunction(hash_13_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__eq__", PY_createBoxForFunction(eq_16_safeWrap));




    return PY_NONE;
}

PyObjectContainer* init_11(PyObjectContainer* self_10) {
    // Source Location: Hashed.__init__

    PyObjectContainer* temp_40 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_10, "hash_count", temp_40);

    PyObjectContainer* temp_41 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_10, "eq_count", temp_41);


    return PY_NONE;
}

PyObjectContainer* init_11_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = init_11(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = init_11(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* hash_13(PyObjectContainer* self_12) {
    // Source Location: Hashed.__hash__

    PyObjectContainer* temp_42 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_12, "hash_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_12, "hash_count", temp_42);

    return PY_createInteger(42);


    return PY_NONE;
}

PyObjectContainer* hash_13_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = hash_13(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = hash_13(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* eq_16(PyObjectContainer* self_14 , PyObjectContainer* other_15) {
    // Source Location: Hashed.__eq__

    PyObjectContainer* temp_43 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_14, "eq_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_14, "eq_count", temp_43);

    return PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_id (self_14)), PY_CHECK_EXCEPTION(PY_STD_id (other_15)));


    return PY_NONE;
}

PyObjectContainer* eq_16_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = eq_16(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = eq_16(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Hashed_25(PyClassContainer** cls) {
    // Create Class PY_CLASS_Hashed_25 ('Hashed' in source code)
    *cls = PY_createClassContainer("Hashed");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Hashed'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_createClassWrapper(PY_TYPE_OBJECT)));
    PyObjectContainer* init_subclass_44 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_44 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_44, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);
    PY_ClassContainer_DeclareObjectAttribute(*cls, "hash_count");
    PY_ClassContainer_DeclareObjectAttribute(*cls, "eq_count");

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__init__", PY_createBoxForFunction(init_19_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__hash__", PY_createBoxForFunction(hash_21_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__eq__", PY_createBoxForFunction(eq_24_safeWrap));




    return PY_NONE;
}

PyObjectContainer* init_19(PyObjectContainer* self_18) {
    // Source Location: Hashed.__init__

    PyObjectContainer* temp_45 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_18, "hash_count", temp_45);

    PyObjectContainer* temp_46 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_18, "eq_count", temp_46);


    return PY_NONE;
}

PyObjectContainer* init_19_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = init_19(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = init_19(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* hash_21(PyObjectContainer* self_20) {
    // Source Location: Hashed.__hash__

    PyObjectContainer* temp_47 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_20, "hash_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_20, "hash_count", temp_47);

    return PY_createInteger(42);


    return PY_NONE;
}

PyObjectContainer* hash_21_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = hash_21(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = hash_21(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* eq_24(PyObjectContainer* self_22 , PyObjectContainer* other_23) {
    // Source Location: Hashed.__eq__

    PyObjectContainer* temp_48 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_22, "eq_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_22, "eq_count", temp_48);

    return PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_id (self_22)), PY_CHECK_EXCEPTION(PY_STD_id (other_23)));


    return PY_NONE;
}

PyObjectContainer* eq_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = eq_24(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = eq_24(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_D_29(PyClassContainer** cls) {
    // Create Class PY_CLASS_D_29 ('D' in source code)
    *cls = PY_createClassContainer("D");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'D'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_createClassWrapper(PY_TYPE_DICT)));
    PyObjectContainer* init_subclass_49 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_49 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_49, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__missing__", PY_createBoxForFunction(missing_28_safeWrap));


    return PY_NONE;
}

PyObjectContainer* missing_28(PyObjectContainer* self_26 , PyObjectContainer* key_27) {
    // Source Location: D.__missing__

    return PY_createInteger(42);


    return PY_NONE;
}

PyObjectContainer* missing_28_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = missing_28(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = missing_28(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_C_30(PyClassContainer** cls) {
    // Create Class PY_CLASS_C_30 ('C' in source code)
    *cls = PY_createClassContainer("C");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'C'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes



    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Foo_31(PyClassContainer** cls) {
    // Create Class PY_CLASS_Foo_31 ('Foo' in source code)
    *cls = PY_createClassContainer("Foo");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Foo'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes



    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_DictTest_85(PyClassContainer** cls) {
    // Create Class PY_CLASS_DictTest_85 ('DictTest' in source code)
    *cls = PY_createClassContainer("DictTest");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'DictTest'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_50 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_50 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_50, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_constructor", PY_createBoxForFunction(testconstructor_33_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_merge_operator", PY_createBoxForFunction(testmergeoperator_35_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_bool", PY_createBoxForFunction(testbool_37_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_contains", PY_createBoxForFunction(testcontains_39_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_len", PY_createBoxForFunction(testlen_41_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_getitem", PY_createBoxForFunction(testgetitem_43_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_clear", PY_createBoxForFunction(testclear_45_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_update", PY_createBoxForFunction(testupdate_47_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_fromkeys", PY_createBoxForFunction(testfromkeys_49_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_copy", PY_createBoxForFunction(testcopy_51_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_get", PY_createBoxForFunction(testget_53_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault", PY_createBoxForFunction(testsetdefault_55_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault_atomic", PY_createBoxForFunction(testsetdefaultatomic_57_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setitem_atomic_at_resize", PY_createBoxForFunction(testsetitematomicatresize_59_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_pop", PY_createBoxForFunction(testpop_61_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration", PY_createBoxForFunction(testmutatingiteration_63_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete", PY_createBoxForFunction(testmutatingiterationdelete_65_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete_over_values", PY_createBoxForFunction(testmutatingiterationdeleteovervalues_67_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete_over_items", PY_createBoxForFunction(testmutatingiterationdeleteoveritems_69_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_repr", PY_createBoxForFunction(testrepr_71_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_eq", PY_createBoxForFunction(testeq_73_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_missing", PY_createBoxForFunction(testmissing_75_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_resize1", PY_createBoxForFunction(testresize1_77_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_string_keys_can_track_values", PY_createBoxForFunction(teststringkeyscantrackvalues_79_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "make_shared_key_dict", PY_createBoxForFunction(makesharedkeydict_82_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_object_set_item_single_instance_non_str_key", PY_createBoxForFunction(testobjectsetitemsingleinstancenonstrkey_84_safeWrap));




















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































    return PY_NONE;
}

PyObjectContainer* testconstructor_33(PyObjectContainer* self_32) {
    // Source Location: DictTest.test_constructor



    PyObjectContainer* obj_instance_52 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_52));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_32, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_52, PY_STD_dict_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_55 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_55));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_32, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {obj_instance_55, PY_STD_dict_CREATE(0)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testconstructor_33_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testconstructor_33(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testconstructor_33(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmergeoperator_35(PyObjectContainer* self_34) {
    // Source Location: DictTest.test_merge_operator
    PyObjectContainer* a_93;
    PyObjectContainer* b_94;
    PyObjectContainer* c_95;

    a_93 = PY_STD_dict_CREATE(3, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1));

    b_94 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));


    c_95 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (a_93));

    c_95 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_95 , b_94));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_93 , b_94)), PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_95, PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    c_95 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (b_94));

    c_95 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_95 , a_93));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (b_94 , a_93)), PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_95, PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));










    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_93 , PY_NONE)), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_93 , PY_STD_tuple_CREATE(0))), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_93 , PY_createString("BAD"))), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_93 , PY_createString(""))), PY_NOT_IMPLEMENTED}, NULL));











    return PY_NONE;
}

PyObjectContainer* testmergeoperator_35_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmergeoperator_35(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmergeoperator_35(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testbool_37(PyObjectContainer* self_36) {
    // Source Location: DictTest.test_bool

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_not(PY_STD_dict_CREATE(0)), PY_TRUE}, NULL));

    PyObjectContainer* temporary_66 = PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_36, "assertTrue"), NULL, 1, &temporary_66, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(0))), PY_FALSE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)))), PY_TRUE}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbool_37_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbool_37(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbool_37(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcontains_39(PyObjectContainer* self_38) {
    // Source Location: DictTest.test_contains
    PyObjectContainer* d_96;

    d_96 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_96}, NULL));

    PyObjectContainer* temporary_70 = PY_STD_operator_contains(d_96, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertFalse"), NULL, 1, &temporary_70, NULL));

    PyObjectContainer* temporary_71 = PY_STD_operator_not_contains(PY_createString("a"), d_96);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertTrue"), NULL, 1, &temporary_71, NULL));

    d_96 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_96}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), d_96}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_38, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("c"), d_96}, NULL));





    return PY_NONE;
}

PyObjectContainer* testcontains_39_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcontains_39(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcontains_39(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlen_41(PyObjectContainer* self_40) {
    // Source Location: DictTest.test_len
    PyObjectContainer* d_97;

    d_97 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_40, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_97)), PY_createInteger(0)}, NULL));

    d_97 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_40, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_97)), PY_createInteger(2)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlen_41_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlen_41(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlen_41(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testgetitem_43(PyObjectContainer* self_42) {
    // Source Location: DictTest.test_getitem
    PyObjectContainer* d_98;

    d_98 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_98 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_98 , PY_createString("b"))), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_98 , PY_createString("c") , PY_createInteger(3)));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_98 , PY_createString("a") , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_98 , PY_createString("c"))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_98 , PY_createString("a"))), PY_createInteger(4)}, NULL));


























































    return PY_NONE;
}

PyObjectContainer* testgetitem_43_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testgetitem_43(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testgetitem_43(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testclear_45(PyObjectContainer* self_44) {
    // Source Location: DictTest.test_clear
    PyObjectContainer* d_99;

    d_99 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_99));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_44, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_99, PY_STD_dict_CREATE(0)}, NULL));





    return PY_NONE;
}

PyObjectContainer* testclear_45_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testclear_45(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testclear_45(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testupdate_47(PyObjectContainer* self_46) {
    // Source Location: DictTest.test_update
    PyObjectContainer* SimpleUserDict_7;
    PyObjectContainer* d_100;

    d_100 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(100))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(1, PY_createInteger(2), PY_createInteger(20))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_46, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    PyObjectContainer* temporary_86 = d_100;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 1, &temporary_86, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_46, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));





    SimpleUserDict_7 = PY_createClass("SimpleUserDict", PY_CLASS_INIT_PY_CLASS_SimpleUserDict_7);
    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_100));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_100, PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(SimpleUserDict_7, NULL, 0, NULL, NULL))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_46, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_100, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));







    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_100));












































































































    return PY_NONE;
}

PyObjectContainer* testupdate_47_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testupdate_47(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testupdate_47(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testfromkeys_49(PyObjectContainer* self_48) {
    // Source Location: DictTest.test_fromkeys
    PyObjectContainer* d_101;
    PyObjectContainer* dictlike_9;
    PyObjectContainer* g_8;

    PyObjectContainer* temporary_91 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_createClassWrapper(PY_TYPE_DICT), "fromkeys"), NULL, 1, &temporary_91, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    d_101 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_93 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_101, "fromkeys"), NULL, 1, &temporary_93, NULL)), d_101}, NULL));

    PyObjectContainer* temporary_95 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_101, "fromkeys"), NULL, 1, &temporary_95, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_101, "fromkeys"), NULL, 2, (PyObjectContainer*[]) {PY_STD_tuple_CREATE(2, PY_createInteger(4), PY_createInteger(5)), PY_createInteger(0)}, NULL)), PY_STD_dict_CREATE(2, PY_createInteger(4), PY_createInteger(0), PY_createInteger(5), PY_createInteger(0))}, NULL));

    PyObjectContainer* temporary_99 = PY_STD_list_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_101, "fromkeys"), NULL, 1, &temporary_99, NULL)), PY_STD_dict_CREATE(0)}, NULL));


    g_8 = function_container_g_3;
    PyObjectContainer* temporary_101 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(g_8, NULL, 0, NULL, NULL));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_101, "fromkeys"), NULL, 1, &temporary_101, NULL)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_NONE)}, NULL));




    dictlike_9 = PY_createClass("dictlike", PY_CLASS_INIT_PY_CLASS_dictlike_9);
    PyObjectContainer* temporary_103 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(dictlike_9, "fromkeys"), NULL, 1, &temporary_103, NULL)), PY_STD_dict_CREATE(1, PY_createString("a"), PY_NONE)}, NULL));

    PyObjectContainer* temporary_105 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(dictlike_9, NULL, 0, NULL, NULL)), "fromkeys"), NULL, 1, &temporary_105, NULL)), PY_STD_dict_CREATE(1, PY_createString("a"), PY_NONE)}, NULL));

    PyObjectContainer* temporary_107 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertIsInstance"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(dictlike_9, "fromkeys"), NULL, 1, &temporary_107, NULL)), dictlike_9}, NULL));

    PyObjectContainer* temporary_109 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_48, "assertIsInstance"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(dictlike_9, NULL, 0, NULL, NULL)), "fromkeys"), NULL, 1, &temporary_109, NULL)), dictlike_9}, NULL));

















































































    return PY_NONE;
}

PyObjectContainer* testfromkeys_49_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testfromkeys_49(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testfromkeys_49(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcopy_51(PyObjectContainer* self_50) {
    // Source Location: DictTest.test_copy
    PyObjectContainer* copy_102;
    PyObjectContainer* d_103;

    d_103 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_50, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_103)), d_103}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_103)), d_103}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_103)), PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    copy_102 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_103));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_103 , PY_createInteger(4) , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_50, "assertNotEqual"), NULL, 2, (PyObjectContainer*[]) {copy_102, d_103}, NULL));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (PY_STD_dict_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));




    return PY_NONE;
}

PyObjectContainer* testcopy_51_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcopy_51(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcopy_51(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testget_53(PyObjectContainer* self_52) {
    // Source Location: DictTest.test_get
    PyObjectContainer* d_104;

    d_104 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_104 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_104 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    d_104 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_104 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_104 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_104 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_104 , PY_createString("a") , PY_createInteger(3))), PY_createInteger(1)}, NULL));






    return PY_NONE;
}

PyObjectContainer* testget_53_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testget_53(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testget_53(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefault_55(PyObjectContainer* self_54) {
    // Source Location: DictTest.test_setdefault
    PyObjectContainer* d_105;



    d_105 = PY_STD_dict_CREATE(1, PY_createString("key0"), PY_NONE);



    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (d_105 , PY_createString("key0") , PY_STD_list_CREATE(0)));



    PyObjectContainer* temporary_121 = PY_createInteger(3);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_105, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_121, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(PY_GetSubscriptionValue(d_105, PY_createString("key")), PY_createInteger(0)), PY_createInteger(3)}, NULL));

    PyObjectContainer* temporary_124 = PY_createInteger(4);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_105, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_124, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_operator_len (PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_105 , PY_createString("key"))))), PY_createInteger(2)}, NULL));


































    return PY_NONE;
}

PyObjectContainer* testsetdefault_55_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefault_55(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefault_55(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefaultatomic_57(PyObjectContainer* self_56) {
    // Source Location: DictTest.test_setdefault_atomic
    PyObjectContainer* Hashed_17;
    PyObjectContainer* hashed1_106;
    PyObjectContainer* hashed2_107;
    PyObjectContainer* y_108;



    Hashed_17 = PY_createClass("Hashed", PY_CLASS_INIT_PY_CLASS_Hashed_17);
    hashed1_106 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_17, NULL, 0, NULL, NULL));

    y_108 = PY_STD_dict_CREATE(1, hashed1_106, PY_createInteger(5));

    hashed2_107 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_17, NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (y_108 , hashed2_107 , PY_STD_list_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_56, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed1_106, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_56, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed2_107, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_56, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_add(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed1_106, "eq_count"), PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed2_107, "eq_count")), PY_createInteger(1)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testsetdefaultatomic_57_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefaultatomic_57(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefaultatomic_57(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetitematomicatresize_59(PyObjectContainer* self_58) {
    // Source Location: DictTest.test_setitem_atomic_at_resize
    PyObjectContainer* Hashed_25;
    PyObjectContainer* hashed1_109;
    PyObjectContainer* hashed2_110;
    PyObjectContainer* y_111;

    Hashed_25 = PY_createClass("Hashed", PY_CLASS_INIT_PY_CLASS_Hashed_25);
    hashed1_109 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_25, NULL, 0, NULL, NULL));



    y_111 = PY_STD_dict_CREATE(5, hashed1_109, PY_createInteger(5), PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    hashed2_110 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_25, NULL, 0, NULL, NULL));



    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (y_111 , hashed2_110 , PY_STD_list_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed1_109, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed2_110, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_add(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed1_109, "eq_count"), PY_getObjectAttributeByNameOrStatic_ThrowOnNull(hashed2_110, "eq_count")), PY_createInteger(1)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testsetitematomicatresize_59_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetitematomicatresize_59(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetitematomicatresize_59(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testpop_61(PyObjectContainer* self_60) {
    // Source Location: DictTest.test_pop
    PyObjectContainer* d_112;
    PyObjectContainer* k_113;
    PyObjectContainer* v_114;



    d_112 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_tuple_133 = PY_STD_tuple_CREATE(2, PY_createString("abc"), PY_createString("def"));
    assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_133)) == 2);
    k_113 = PY_GetSubscriptionValue(temporary_tuple_133, PY_createInteger(0));
    v_114 = PY_GetSubscriptionValue(temporary_tuple_133, PY_createInteger(1));
    ;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_112 , k_113 , v_114));




    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_1 (d_112 , k_113)), v_114}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_112)), PY_createInteger(0)}, NULL));





    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_112 , k_113 , v_114)), v_114}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_112 , k_113 , v_114));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_pop_fast_arg_2 (d_112 , k_113 , PY_createInteger(1))), v_114}, NULL));



































    return PY_NONE;
}

PyObjectContainer* testpop_61_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testpop_61(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testpop_61(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiteration_63(PyObjectContainer* self_62) {
    // Source Location: DictTest.test_mutating_iteration
    PyObjectContainer* d_115;



    d_115 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_115 , PY_createInteger(1) , PY_createInteger(1)));








    return PY_NONE;
}

PyObjectContainer* testmutatingiteration_63_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiteration_63(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiteration_63(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdelete_65(PyObjectContainer* self_64) {
    // Source Location: DictTest.test_mutating_iteration_delete
    PyObjectContainer* d_116;



    d_116 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_116 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdelete_65_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdelete_65(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdelete_65(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdeleteovervalues_67(PyObjectContainer* self_66) {
    // Source Location: DictTest.test_mutating_iteration_delete_over_values
    PyObjectContainer* d_117;



    d_117 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_117 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdeleteovervalues_67_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdeleteovervalues_67(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdeleteovervalues_67(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdeleteoveritems_69(PyObjectContainer* self_68) {
    // Source Location: DictTest.test_mutating_iteration_delete_over_items
    PyObjectContainer* d_118;



    d_118 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_118 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdeleteoveritems_69_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdeleteoveritems_69(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdeleteoveritems_69(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testrepr_71(PyObjectContainer* self_70) {
    // Source Location: DictTest.test_repr
    PyObjectContainer* d_119;

    d_119 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_70, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_119)), PY_createString("{}")}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_119 , PY_createInteger(1) , PY_createInteger(2)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_70, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_119)), PY_createString("{1: 2}")}, NULL));

    d_119 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_119 , PY_createInteger(1) , d_119));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_70, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_119)), PY_createString("{1: {...}}")}, NULL));



















    return PY_NONE;
}

PyObjectContainer* testrepr_71_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testrepr_71(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testrepr_71(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testeq_73(PyObjectContainer* self_72) {
    // Source Location: DictTest.test_eq

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_72, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(0), PY_STD_dict_CREATE(0)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_72, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2))}, NULL));





























    return PY_NONE;
}

PyObjectContainer* testeq_73_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testeq_73(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testeq_73(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmissing_75(PyObjectContainer* self_74) {
    // Source Location: DictTest.test_missing
    PyObjectContainer* D_29;
    PyObjectContainer* d_120;



    PyObjectContainer* temporary_143 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_createClassWrapper(PY_TYPE_DICT) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertFalse"), NULL, 1, &temporary_143, NULL));

    PyObjectContainer* temporary_144 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_STD_dict_CREATE(0) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertFalse"), NULL, 1, &temporary_144, NULL));












    D_29 = PY_createClass("D", PY_CLASS_INIT_PY_CLASS_D_29);
    PyObjectContainer* temporary_145 = PY_STD_dict_CREATE(2, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3), PY_createInteger(4));
    d_120 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(D_29, NULL, 1, &temporary_145, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_120, PY_createInteger(1)), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_120, PY_createInteger(3)), PY_createInteger(4)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), d_120}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(d_120, "keys"), NULL, 0, NULL, NULL))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_74, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_120, PY_createInteger(2)), PY_createInteger(42)}, NULL));


















































    return PY_NONE;
}

PyObjectContainer* testmissing_75_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmissing_75(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmissing_75(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testresize1_77(PyObjectContainer* self_76) {
    // Source Location: DictTest.test_resize1
    PyObjectContainer* d_121;
    PyObjectContainer* i_122;














    d_121 = PY_STD_dict_CREATE(0);

    PyObjectContainer* iterator_151 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(5)))));
    PyObjectContainer* value_152 = PY_STD_NEXT_FORWARD_arg_1(iterator_151, NULL);
    while (value_152 != NULL) {
        PY_CHECK_EXCEPTION(value_152);
        i_122 = value_152;
        PyObjectContainer* temp_153 = i_122;
        PY_SetSubscriptionValue(d_121, temp_153, i_122);

        value_152 = PY_STD_NEXT_FORWARD_arg_1(iterator_151, NULL);
    }




    PyObjectContainer* iterator_154 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_2 (PY_createInteger(5) , PY_createInteger(9)))));
    PyObjectContainer* value_155 = PY_STD_NEXT_FORWARD_arg_1(iterator_154, NULL);
    while (value_155 != NULL) {
        PY_CHECK_EXCEPTION(value_155);
        i_122 = value_155;


        PyObjectContainer* temp_156 = i_122;
        PY_SetSubscriptionValue(d_121, temp_156, i_122);


        value_155 = PY_STD_NEXT_FORWARD_arg_1(iterator_154, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* testresize1_77_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testresize1_77(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testresize1_77(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* teststringkeyscantrackvalues_79(PyObjectContainer* self_78) {
    // Source Location: DictTest.test_string_keys_can_track_values
    PyObjectContainer* d_123;
    PyObjectContainer* i_124;
    PyObjectContainer* j_125;



    PyObjectContainer* iterator_157 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(10)))));
    PyObjectContainer* value_158 = PY_STD_NEXT_FORWARD_arg_1(iterator_157, NULL);
    while (value_158 != NULL) {
        PY_CHECK_EXCEPTION(value_158);
        i_124 = value_158;
        d_123 = PY_STD_dict_CREATE(0);

        PyObjectContainer* iterator_159 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(10)))));
        PyObjectContainer* value_160 = PY_STD_NEXT_FORWARD_arg_1(iterator_159, NULL);
        while (value_160 != NULL) {
            PY_CHECK_EXCEPTION(value_160);
            j_125 = value_160;
            PyObjectContainer* temp_161 = j_125;
            PY_SetSubscriptionValue(d_123, temp_161, PY_CHECK_EXCEPTION(PY_getObjectStr_wrapper (j_125)));

            value_160 = PY_STD_NEXT_FORWARD_arg_1(iterator_159, NULL);
        }
        PyObjectContainer* temp_162 = d_123;
        PY_SetSubscriptionValue(d_123, temp_162, PY_createString("foo"));


        value_158 = PY_STD_NEXT_FORWARD_arg_1(iterator_157, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* teststringkeyscantrackvalues_79_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = teststringkeyscantrackvalues_79(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = teststringkeyscantrackvalues_79(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* makesharedkeydict_82(PyObjectContainer* self_80 , PyObjectContainer* n_81) {
    // Source Location: DictTest.make_shared_key_dict
    PyObjectContainer* C_30;
    PyObjectContainer* a_126;
    PyObjectContainer* dicts_127;
    PyObjectContainer* i_128;

    C_30 = PY_createClass("C", PY_CLASS_INIT_PY_CLASS_C_30);
    dicts_127 = PY_STD_list_CREATE(0);

    PyObjectContainer* iterator_163 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (n_81))));
    PyObjectContainer* value_164 = PY_STD_NEXT_FORWARD_arg_1(iterator_163, NULL);
    while (value_164 != NULL) {
        PY_CHECK_EXCEPTION(value_164);
        i_128 = value_164;
        a_126 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(C_30, NULL, 0, NULL, NULL));

        PyObjectContainer* temporary_tuple_165 = PY_STD_tuple_CREATE(3, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3));
        assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_165)) == 3);
        PyObjectContainer* temp_166 = PY_GetSubscriptionValue(temporary_tuple_165, PY_createInteger(0));
        PY_setObjectAttributeByName(a_126, "x", temp_166);
        PyObjectContainer* temp_167 = PY_GetSubscriptionValue(temporary_tuple_165, PY_createInteger(1));
        PY_setObjectAttributeByName(a_126, "y", temp_167);
        PyObjectContainer* temp_168 = PY_GetSubscriptionValue(temporary_tuple_165, PY_createInteger(2));
        PY_setObjectAttributeByName(a_126, "z", temp_168);
        ;

        PY_CHECK_EXCEPTION(PY_STD_list_append_fast (dicts_127 , PY_getObjectAttributeByNameOrStatic_ThrowOnNull(a_126, "__dict__")));


        value_164 = PY_STD_NEXT_FORWARD_arg_1(iterator_163, NULL);
    }
    return dicts_127;


    return PY_NONE;
}

PyObjectContainer* makesharedkeydict_82_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = makesharedkeydict_82(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = makesharedkeydict_82(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testobjectsetitemsingleinstancenonstrkey_84(PyObjectContainer* self_83) {
    // Source Location: DictTest.test_object_set_item_single_instance_non_str_key
    PyObjectContainer* Foo_31;
    PyObjectContainer* f_129;

    Foo_31 = PY_createClass("Foo", PY_CLASS_INIT_PY_CLASS_Foo_31);
    f_129 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Foo_31, NULL, 0, NULL, NULL));

    PyObjectContainer* temp_169 = PY_createInteger(1);
    PY_SetSubscriptionValue(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(f_129, "__dict__"), temp_169, PY_createInteger(1));

    PyObjectContainer* temp_170 = PY_createString("a");
    PY_setObjectAttributeByName(f_129, "a", temp_170);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_83, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic_ThrowOnNull(f_129, "__dict__"), PY_STD_dict_CREATE(2, PY_createInteger(1), PY_createInteger(1), PY_createString("a"), PY_createString("a"))}, NULL));


    return PY_NONE;
}

PyObjectContainer* testobjectsetitemsingleinstancenonstrkey_84_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testobjectsetitemsingleinstancenonstrkey_84(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testobjectsetitemsingleinstancenonstrkey_84(self);
    }

    if (info) free(new_args);
    return result;
}

