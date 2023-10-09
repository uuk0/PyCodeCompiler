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
PyObjectContainer* function_container_test_keys_14;
PyObjectContainer* function_container_test_contains_15;
PyObjectContainer* function_container_test_len_16;
PyObjectContainer* function_container_test_getitem_17;
PyObjectContainer* function_container_test_clear_18;
PyObjectContainer* function_container_test_update_19;
PyObjectContainer* function_container_test_fromkeys_20;
PyObjectContainer* function_container_test_copy_21;
PyObjectContainer* function_container_test_get_22;
PyObjectContainer* function_container_test_setdefault_23;
PyObjectContainer* function_container_test_setdefault_atomic_24;
PyObjectContainer* function_container_test_setitem_atomic_at_resize_25;
PyObjectContainer* function_container_test_pop_26;
PyObjectContainer* function_container_test_mutating_iteration_27;
PyObjectContainer* function_container_test_mutating_iteration_delete_28;
PyObjectContainer* function_container_test_mutating_iteration_delete_over_values_29;
PyObjectContainer* function_container_test_mutating_iteration_delete_over_items_30;
PyObjectContainer* function_container_test_repr_31;
PyObjectContainer* function_container_test_eq_32;
PyObjectContainer* function_container_test_missing_33;
PyObjectContainer* function_container_test_resize1_34;
PyObjectContainer* function_container_test_string_keys_can_track_values_35;
PyObjectContainer* function_container_make_shared_key_dict_36;
PyObjectContainer* function_container_test_object_set_item_single_instance_non_str_key_37;
PyClassContainer* PY_CLASS_DictTest_87;
PyObjectContainer* value_160;
PyObjectContainer* value_163;
PyObjectContainer* value_166;
PyObjectContainer* value_168;
PyObjectContainer* value_172;



// implementations

PyObjectContainer* PY_MODULE_test_dict_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_dict = PY_createModuleObject("test_dict");
    #endif
    PyObjectContainer* DictTest_87;
    PyObjectContainer* PY_CLASS_C_88;
    PyObjectContainer* PY_CLASS_D_89;
    PyObjectContainer* PY_CLASS_Foo_90;
    PyObjectContainer* PY_CLASS_Hashed_91;
    PyObjectContainer* PY_CLASS_SimpleUserDict_92;
    PyObjectContainer* PY_CLASS_dictlike_93;
    PyObjectContainer* unittest_94;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_94 = PY_MODULE_INSTANCE_unittest;



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
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_keys", (function_container_test_keys_14 = PY_createBoxForFunction(testkeys_39_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_contains", (function_container_test_contains_15 = PY_createBoxForFunction(testcontains_41_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_len", (function_container_test_len_16 = PY_createBoxForFunction(testlen_43_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_getitem", (function_container_test_getitem_17 = PY_createBoxForFunction(testgetitem_45_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_clear", (function_container_test_clear_18 = PY_createBoxForFunction(testclear_47_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_update", (function_container_test_update_19 = PY_createBoxForFunction(testupdate_49_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_fromkeys", (function_container_test_fromkeys_20 = PY_createBoxForFunction(testfromkeys_51_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_copy", (function_container_test_copy_21 = PY_createBoxForFunction(testcopy_53_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_get", (function_container_test_get_22 = PY_createBoxForFunction(testget_55_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault", (function_container_test_setdefault_23 = PY_createBoxForFunction(testsetdefault_57_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setdefault_atomic", (function_container_test_setdefault_atomic_24 = PY_createBoxForFunction(testsetdefaultatomic_59_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_setitem_atomic_at_resize", (function_container_test_setitem_atomic_at_resize_25 = PY_createBoxForFunction(testsetitematomicatresize_61_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_pop", (function_container_test_pop_26 = PY_createBoxForFunction(testpop_63_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration", (function_container_test_mutating_iteration_27 = PY_createBoxForFunction(testmutatingiteration_65_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete", (function_container_test_mutating_iteration_delete_28 = PY_createBoxForFunction(testmutatingiterationdelete_67_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete_over_values", (function_container_test_mutating_iteration_delete_over_values_29 = PY_createBoxForFunction(testmutatingiterationdeleteovervalues_69_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_mutating_iteration_delete_over_items", (function_container_test_mutating_iteration_delete_over_items_30 = PY_createBoxForFunction(testmutatingiterationdeleteoveritems_71_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_repr", (function_container_test_repr_31 = PY_createBoxForFunction(testrepr_73_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_eq", (function_container_test_eq_32 = PY_createBoxForFunction(testeq_75_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_missing", (function_container_test_missing_33 = PY_createBoxForFunction(testmissing_77_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_resize1", (function_container_test_resize1_34 = PY_createBoxForFunction(testresize1_79_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_string_keys_can_track_values", (function_container_test_string_keys_can_track_values_35 = PY_createBoxForFunction(teststringkeyscantrackvalues_81_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "make_shared_key_dict", (function_container_make_shared_key_dict_36 = PY_createBoxForFunction(makesharedkeydict_84_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_dict, "test_object_set_item_single_instance_non_str_key", (function_container_test_object_set_item_single_instance_non_str_key_37 = PY_createBoxForFunction(testobjectsetitemsingleinstancenonstrkey_86_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_DictTest_87(&PY_CLASS_DictTest_87);

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
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

    PyObjectContainer* temp_38 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));
    PY_setObjectAttributeByName(self_0, "d", temp_38);


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

    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_getObjectAttributeByNameOrStatic(self_2, "d"), "keys"), NULL, 0, NULL, NULL));


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

    return PY_GetSubscriptionValue(PY_getObjectAttributeByNameOrStatic(self_4, "d"), i_5);


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
    PyObjectContainer* init_subclass_39 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_39 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_39, PY_createClassWrapper(*cls), 0, NULL, NULL));
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
    PyObjectContainer* init_subclass_40 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_40 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_40, PY_createClassWrapper(*cls), 0, NULL, NULL));
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

    PyObjectContainer* temp_41 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_10, "hash_count", temp_41);

    PyObjectContainer* temp_42 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_10, "eq_count", temp_42);


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

    PyObjectContainer* temp_43 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic(self_12, "hash_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_12, "hash_count", temp_43);

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

    PyObjectContainer* temp_44 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic(self_14, "eq_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_14, "eq_count", temp_44);

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
    PyObjectContainer* init_subclass_45 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_45 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_45, PY_createClassWrapper(*cls), 0, NULL, NULL));
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

    PyObjectContainer* temp_46 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_18, "hash_count", temp_46);

    PyObjectContainer* temp_47 = PY_createInteger(0);
    PY_setObjectAttributeByName(self_18, "eq_count", temp_47);


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

    PyObjectContainer* temp_48 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic(self_20, "hash_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_20, "hash_count", temp_48);

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

    PyObjectContainer* temp_49 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_add (PY_getObjectAttributeByNameOrStatic(self_22, "eq_count") , PY_createInteger(1)));
    PY_setObjectAttributeByName(self_22, "eq_count", temp_49);

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
    PyObjectContainer* init_subclass_50 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_50 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_50, PY_createClassWrapper(*cls), 0, NULL, NULL));
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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_DictTest_87(PyClassContainer** cls) {
    // Create Class PY_CLASS_DictTest_87 ('DictTest' in source code)
    *cls = PY_createClassContainer("DictTest");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'DictTest'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_51 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_51 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_51, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_constructor", PY_createBoxForFunction(testconstructor_33_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_merge_operator", PY_createBoxForFunction(testmergeoperator_35_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_bool", PY_createBoxForFunction(testbool_37_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_keys", PY_createBoxForFunction(testkeys_39_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_contains", PY_createBoxForFunction(testcontains_41_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_len", PY_createBoxForFunction(testlen_43_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_getitem", PY_createBoxForFunction(testgetitem_45_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_clear", PY_createBoxForFunction(testclear_47_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_update", PY_createBoxForFunction(testupdate_49_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_fromkeys", PY_createBoxForFunction(testfromkeys_51_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_copy", PY_createBoxForFunction(testcopy_53_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_get", PY_createBoxForFunction(testget_55_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault", PY_createBoxForFunction(testsetdefault_57_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setdefault_atomic", PY_createBoxForFunction(testsetdefaultatomic_59_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_setitem_atomic_at_resize", PY_createBoxForFunction(testsetitematomicatresize_61_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_pop", PY_createBoxForFunction(testpop_63_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration", PY_createBoxForFunction(testmutatingiteration_65_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete", PY_createBoxForFunction(testmutatingiterationdelete_67_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete_over_values", PY_createBoxForFunction(testmutatingiterationdeleteovervalues_69_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_mutating_iteration_delete_over_items", PY_createBoxForFunction(testmutatingiterationdeleteoveritems_71_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_repr", PY_createBoxForFunction(testrepr_73_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_eq", PY_createBoxForFunction(testeq_75_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_missing", PY_createBoxForFunction(testmissing_77_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_resize1", PY_createBoxForFunction(testresize1_79_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_string_keys_can_track_values", PY_createBoxForFunction(teststringkeyscantrackvalues_81_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "make_shared_key_dict", PY_createBoxForFunction(makesharedkeydict_84_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_object_set_item_single_instance_non_str_key", PY_createBoxForFunction(testobjectsetitemsingleinstancenonstrkey_86_safeWrap));
























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































    return PY_NONE;
}

PyObjectContainer* testconstructor_33(PyObjectContainer* self_32) {
    // Source Location: DictTest.test_constructor



    PyObjectContainer* obj_instance_53 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_53));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_32, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_53, PY_STD_dict_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_56 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_56));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_32, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {obj_instance_56, PY_STD_dict_CREATE(0)}, NULL));


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
    PyObjectContainer* a_95;
    PyObjectContainer* b_96;
    PyObjectContainer* c_97;

    a_95 = PY_STD_dict_CREATE(3, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1));

    b_96 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));


    c_97 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (a_95));

    c_97 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_97 , b_96));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_95 , b_96)), PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_97, PY_STD_dict_CREATE(4, PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    c_97 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (b_96));

    c_97 = PY_CHECK_EXCEPTION(PY_STD_operator_inplace_bin_or (c_97 , a_95));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (b_96 , a_95)), PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {c_97, PY_STD_dict_CREATE(4, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(1), PY_createInteger(3), PY_createInteger(3), PY_createInteger(0), PY_createInteger(0))}, NULL));










    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_95 , PY_NONE)), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_95 , PY_STD_tuple_CREATE(0))), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_95 , PY_createString("BAD"))), PY_NOT_IMPLEMENTED}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_concat_fast (a_95 , PY_createString(""))), PY_NOT_IMPLEMENTED}, NULL));











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

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_not(PY_STD_dict_CREATE(0)), PY_TRUE}, NULL));

    PyObjectContainer* temporary_67 = PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_36, "assertTrue"), NULL, 1, &temporary_67, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(0))), PY_FALSE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_36, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getTruthValueOf_BOXED (PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)))), PY_TRUE}, NULL));


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

PyObjectContainer* testkeys_39(PyObjectContainer* self_38) {
    // Source Location: DictTest.test_keys
    PyObjectContainer* d_98;
    PyObjectContainer* k_99;





    d_98 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    k_99 = PY_CHECK_EXCEPTION(PY_STD_dict_keys_fast (d_98));



    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), k_99}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), k_99}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_98}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_38, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), d_98}, NULL));






    return PY_NONE;
}

PyObjectContainer* testkeys_39_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testkeys_39(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testkeys_39(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcontains_41(PyObjectContainer* self_40) {
    // Source Location: DictTest.test_contains
    PyObjectContainer* d_100;

    d_100 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_100}, NULL));

    PyObjectContainer* temporary_75 = PY_STD_operator_contains(d_100, PY_createString("a"));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertFalse"), NULL, 1, &temporary_75, NULL));

    PyObjectContainer* temporary_76 = PY_STD_operator_not_contains(PY_createString("a"), d_100);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertTrue"), NULL, 1, &temporary_76, NULL));

    d_100 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("a"), d_100}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("b"), d_100}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_40, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createString("c"), d_100}, NULL));





    return PY_NONE;
}

PyObjectContainer* testcontains_41_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcontains_41(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcontains_41(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlen_43(PyObjectContainer* self_42) {
    // Source Location: DictTest.test_len
    PyObjectContainer* d_101;

    d_101 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_101)), PY_createInteger(0)}, NULL));

    d_101 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_101)), PY_createInteger(2)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlen_43_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlen_43(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlen_43(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testgetitem_45(PyObjectContainer* self_44) {
    // Source Location: DictTest.test_getitem
    PyObjectContainer* d_102;

    d_102 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_44, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_102 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_44, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_102 , PY_createString("b"))), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_102 , PY_createString("c") , PY_createInteger(3)));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_102 , PY_createString("a") , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_44, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_102 , PY_createString("c"))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_44, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_102 , PY_createString("a"))), PY_createInteger(4)}, NULL));


























































    return PY_NONE;
}

PyObjectContainer* testgetitem_45_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testgetitem_45(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testgetitem_45(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testclear_47(PyObjectContainer* self_46) {
    // Source Location: DictTest.test_clear
    PyObjectContainer* d_103;

    d_103 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_103));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_46, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_103, PY_STD_dict_CREATE(0)}, NULL));





    return PY_NONE;
}

PyObjectContainer* testclear_47_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testclear_47(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testclear_47(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testupdate_49(PyObjectContainer* self_48) {
    // Source Location: DictTest.test_update
    PyObjectContainer* SimpleUserDict_7;
    PyObjectContainer* d_104;

    d_104 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(100))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(1, PY_createInteger(2), PY_createInteger(20))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    PyObjectContainer* temporary_91 = d_104;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 1, &temporary_91, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));





    SimpleUserDict_7 = PY_createClass("SimpleUserDict", PY_CLASS_INIT_PY_CLASS_SimpleUserDict_7);
    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_104));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_NOOP_CONTAINER, NULL, 2, (PyObjectContainer*[]) {d_104, PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(SimpleUserDict_7, NULL, 0, NULL, NULL))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {d_104, PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));







    PY_CHECK_EXCEPTION(PY_STD_dict_clear_fast (d_104));












































































































    return PY_NONE;
}

PyObjectContainer* testupdate_49_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testupdate_49(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testupdate_49(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testfromkeys_51(PyObjectContainer* self_50) {
    // Source Location: DictTest.test_fromkeys
    PyObjectContainer* d_105;
    PyObjectContainer* dictlike_9;
    PyObjectContainer* g_8;

    PyObjectContainer* temporary_96 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_createClassWrapper(PY_TYPE_DICT), "fromkeys"), NULL, 1, &temporary_96, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    d_105 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_98 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_105, "fromkeys"), NULL, 1, &temporary_98, NULL)), d_105}, NULL));

    PyObjectContainer* temporary_100 = PY_createString("abc");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_105, "fromkeys"), NULL, 1, &temporary_100, NULL)), PY_STD_dict_CREATE(3, PY_createString("a"), PY_NONE, PY_createString("b"), PY_NONE, PY_createString("c"), PY_NONE)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_105, "fromkeys"), NULL, 2, (PyObjectContainer*[]) {PY_STD_tuple_CREATE(2, PY_createInteger(4), PY_createInteger(5)), PY_createInteger(0)}, NULL)), PY_STD_dict_CREATE(2, PY_createInteger(4), PY_createInteger(0), PY_createInteger(5), PY_createInteger(0))}, NULL));

    PyObjectContainer* temporary_104 = PY_STD_list_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_105, "fromkeys"), NULL, 1, &temporary_104, NULL)), PY_STD_dict_CREATE(0)}, NULL));


    g_8 = function_container_g_3;
    PyObjectContainer* temporary_106 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(g_8, NULL, 0, NULL, NULL));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_105, "fromkeys"), NULL, 1, &temporary_106, NULL)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_NONE)}, NULL));




    dictlike_9 = PY_createClass("dictlike", PY_CLASS_INIT_PY_CLASS_dictlike_9);
    PyObjectContainer* temporary_108 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(dictlike_9, "fromkeys"), NULL, 1, &temporary_108, NULL)), PY_STD_dict_CREATE(1, PY_createString("a"), PY_NONE)}, NULL));

    PyObjectContainer* temporary_110 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(dictlike_9, NULL, 0, NULL, NULL)), "fromkeys"), NULL, 1, &temporary_110, NULL)), PY_STD_dict_CREATE(1, PY_createString("a"), PY_NONE)}, NULL));

    PyObjectContainer* temporary_112 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertIsInstance"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(dictlike_9, "fromkeys"), NULL, 1, &temporary_112, NULL)), dictlike_9}, NULL));

    PyObjectContainer* temporary_114 = PY_createString("a");
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_50, "assertIsInstance"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(dictlike_9, NULL, 0, NULL, NULL)), "fromkeys"), NULL, 1, &temporary_114, NULL)), dictlike_9}, NULL));

















































































    return PY_NONE;
}

PyObjectContainer* testfromkeys_51_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testfromkeys_51(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testfromkeys_51(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testcopy_53(PyObjectContainer* self_52) {
    // Source Location: DictTest.test_copy
    PyObjectContainer* copy_106;
    PyObjectContainer* d_107;

    d_107 = PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_52, "assertIsNot"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_107)), d_107}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_107)), d_107}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_107)), PY_STD_dict_CREATE(3, PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3))}, NULL));


    copy_106 = PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (d_107));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_107 , PY_createInteger(4) , PY_createInteger(4)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_52, "assertNotEqual"), NULL, 2, (PyObjectContainer*[]) {copy_106, d_107}, NULL));


    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_52, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_copy_fast (PY_STD_dict_CREATE(0))), PY_STD_dict_CREATE(0)}, NULL));




    return PY_NONE;
}

PyObjectContainer* testcopy_53_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testcopy_53(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testcopy_53(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testget_55(PyObjectContainer* self_54) {
    // Source Location: DictTest.test_get
    PyObjectContainer* d_108;

    d_108 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_108 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_108 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    d_108 = PY_STD_dict_CREATE(2, PY_createString("a"), PY_createInteger(1), PY_createString("b"), PY_createInteger(2));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertIs"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_108 , PY_createString("c"))), PY_NONE}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_108 , PY_createString("c") , PY_createInteger(3))), PY_createInteger(3)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_108 , PY_createString("a"))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_54, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (d_108 , PY_createString("a") , PY_createInteger(3))), PY_createInteger(1)}, NULL));






    return PY_NONE;
}

PyObjectContainer* testget_55_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testget_55(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testget_55(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefault_57(PyObjectContainer* self_56) {
    // Source Location: DictTest.test_setdefault
    PyObjectContainer* d_109;



    d_109 = PY_STD_dict_CREATE(1, PY_createString("key0"), PY_NONE);



    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (d_109 , PY_createString("key0") , PY_STD_list_CREATE(0)));



    PyObjectContainer* temporary_126 = PY_createInteger(3);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_109, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_126, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_56, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(PY_GetSubscriptionValue(d_109, PY_createString("key")), PY_createInteger(0)), PY_createInteger(3)}, NULL));

    PyObjectContainer* temporary_129 = PY_createInteger(4);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_109, "setdefault"), NULL, 2, (PyObjectContainer*[]) {PY_createString("key"), PY_STD_list_CREATE(0)}, NULL)), "append"), NULL, 1, &temporary_129, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_56, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_operator_len (PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (d_109 , PY_createString("key"))))), PY_createInteger(2)}, NULL));


































    return PY_NONE;
}

PyObjectContainer* testsetdefault_57_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefault_57(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefault_57(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetdefaultatomic_59(PyObjectContainer* self_58) {
    // Source Location: DictTest.test_setdefault_atomic
    PyObjectContainer* Hashed_17;
    PyObjectContainer* hashed1_110;
    PyObjectContainer* hashed2_111;
    PyObjectContainer* y_112;



    Hashed_17 = PY_createClass("Hashed", PY_CLASS_INIT_PY_CLASS_Hashed_17);
    hashed1_110 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_17, NULL, 0, NULL, NULL));

    y_112 = PY_STD_dict_CREATE(1, hashed1_110, PY_createInteger(5));

    hashed2_111 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_17, NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setdefault_fast (y_112 , hashed2_111 , PY_STD_list_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic(hashed1_110, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic(hashed2_111, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_58, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_add(PY_getObjectAttributeByNameOrStatic(hashed1_110, "eq_count"), PY_getObjectAttributeByNameOrStatic(hashed2_111, "eq_count")), PY_createInteger(1)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testsetdefaultatomic_59_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetdefaultatomic_59(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetdefaultatomic_59(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsetitematomicatresize_61(PyObjectContainer* self_60) {
    // Source Location: DictTest.test_setitem_atomic_at_resize
    PyObjectContainer* Hashed_25;
    PyObjectContainer* hashed1_113;
    PyObjectContainer* hashed2_114;
    PyObjectContainer* y_115;

    Hashed_25 = PY_createClass("Hashed", PY_CLASS_INIT_PY_CLASS_Hashed_25);
    hashed1_113 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_25, NULL, 0, NULL, NULL));



    y_115 = PY_STD_dict_CREATE(5, hashed1_113, PY_createInteger(5), PY_createInteger(0), PY_createInteger(0), PY_createInteger(1), PY_createInteger(1), PY_createInteger(2), PY_createInteger(2), PY_createInteger(3), PY_createInteger(3));

    hashed2_114 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Hashed_25, NULL, 0, NULL, NULL));



    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (y_115 , hashed2_114 , PY_STD_list_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic(hashed1_113, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic(hashed2_114, "hash_count"), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_60, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_operator_add(PY_getObjectAttributeByNameOrStatic(hashed1_113, "eq_count"), PY_getObjectAttributeByNameOrStatic(hashed2_114, "eq_count")), PY_createInteger(1)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testsetitematomicatresize_61_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsetitematomicatresize_61(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsetitematomicatresize_61(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testpop_63(PyObjectContainer* self_62) {
    // Source Location: DictTest.test_pop
    PyObjectContainer* d_116;
    PyObjectContainer* k_117;
    PyObjectContainer* v_118;



    d_116 = PY_STD_dict_CREATE(0);

    PyObjectContainer* temporary_tuple_138 = PY_STD_tuple_CREATE(2, PY_createString("abc"), PY_createString("def"));
    assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_138)) == 2);
    k_117 = PY_GetSubscriptionValue(temporary_tuple_138, PY_createInteger(0));
    v_118 = PY_GetSubscriptionValue(temporary_tuple_138, PY_createInteger(1));
    ;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_116 , k_117 , v_118));




    PyObjectContainer* temporary_140 = k_117;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_62, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_116, "pop"), NULL, 1, &temporary_140, NULL)), v_118}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_62, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_dict_len_fast (d_116)), PY_createInteger(0)}, NULL));





    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_62, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_116, "pop"), NULL, 2, (PyObjectContainer*[]) {k_117, v_118}, NULL)), v_118}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_116 , k_117 , v_118));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_62, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_116, "pop"), NULL, 2, (PyObjectContainer*[]) {k_117, PY_createInteger(1)}, NULL)), v_118}, NULL));



































    return PY_NONE;
}

PyObjectContainer* testpop_63_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testpop_63(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testpop_63(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiteration_65(PyObjectContainer* self_64) {
    // Source Location: DictTest.test_mutating_iteration
    PyObjectContainer* d_119;



    d_119 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_119 , PY_createInteger(1) , PY_createInteger(1)));








    return PY_NONE;
}

PyObjectContainer* testmutatingiteration_65_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiteration_65(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiteration_65(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdelete_67(PyObjectContainer* self_66) {
    // Source Location: DictTest.test_mutating_iteration_delete
    PyObjectContainer* d_120;



    d_120 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_120 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdelete_67_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdelete_67(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdelete_67(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdeleteovervalues_69(PyObjectContainer* self_68) {
    // Source Location: DictTest.test_mutating_iteration_delete_over_values
    PyObjectContainer* d_121;



    d_121 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_121 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdeleteovervalues_69_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdeleteovervalues_69(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdeleteovervalues_69(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmutatingiterationdeleteoveritems_71(PyObjectContainer* self_70) {
    // Source Location: DictTest.test_mutating_iteration_delete_over_items
    PyObjectContainer* d_122;



    d_122 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_122 , PY_createInteger(0) , PY_createInteger(0)));










    return PY_NONE;
}

PyObjectContainer* testmutatingiterationdeleteoveritems_71_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmutatingiterationdeleteoveritems_71(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmutatingiterationdeleteoveritems_71(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testrepr_73(PyObjectContainer* self_72) {
    // Source Location: DictTest.test_repr
    PyObjectContainer* d_123;

    d_123 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_72, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_123)), PY_createString("{}")}, NULL));

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_123 , PY_createInteger(1) , PY_createInteger(2)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_72, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_123)), PY_createString("{1: 2}")}, NULL));

    d_123 = PY_STD_dict_CREATE(0);

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (d_123 , PY_createInteger(1) , d_123));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_72, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_getObjectRepr_wrapper (d_123)), PY_createString("{1: {...}}")}, NULL));



















    return PY_NONE;
}

PyObjectContainer* testrepr_73_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testrepr_73(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testrepr_73(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testeq_75(PyObjectContainer* self_74) {
    // Source Location: DictTest.test_eq

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_74, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(0), PY_STD_dict_CREATE(0)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_74, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2)), PY_STD_dict_CREATE(1, PY_createInteger(1), PY_createInteger(2))}, NULL));





























    return PY_NONE;
}

PyObjectContainer* testeq_75_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testeq_75(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testeq_75(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testmissing_77(PyObjectContainer* self_76) {
    // Source Location: DictTest.test_missing
    PyObjectContainer* D_29;
    PyObjectContainer* d_124;



    PyObjectContainer* temporary_151 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_createClassWrapper(PY_TYPE_DICT) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertFalse"), NULL, 1, &temporary_151, NULL));

    PyObjectContainer* temporary_152 = PY_CHECK_EXCEPTION(PY_STD_hasattr (PY_STD_dict_CREATE(0) , PY_createString("__missing__")));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertFalse"), NULL, 1, &temporary_152, NULL));












    D_29 = PY_createClass("D", PY_CLASS_INIT_PY_CLASS_D_29);
    PyObjectContainer* temporary_153 = PY_STD_dict_CREATE(2, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3), PY_createInteger(4));
    d_124 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(D_29, NULL, 1, &temporary_153, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_124, PY_createInteger(1)), PY_createInteger(2)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_124, PY_createInteger(3)), PY_createInteger(4)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), d_124}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertNotIn"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(2), PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(d_124, "keys"), NULL, 0, NULL, NULL))}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_76, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_GetSubscriptionValue(d_124, PY_createInteger(2)), PY_createInteger(42)}, NULL));


















































    return PY_NONE;
}

PyObjectContainer* testmissing_77_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testmissing_77(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testmissing_77(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testresize1_79(PyObjectContainer* self_78) {
    // Source Location: DictTest.test_resize1
    PyObjectContainer* d_125;
    PyObjectContainer* i_126;














    d_125 = PY_STD_dict_CREATE(0);

    PyObjectContainer* iterator_159 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(5)))));
    PyObjectContainer* value_160 = PY_STD_NEXT_FORWARD_arg_1(iterator_159, NULL);
    while (value_160 != NULL) {
        PY_CHECK_EXCEPTION(value_160);
        i_126 = value_160;
        PyObjectContainer* temp_161 = i_126;
        PY_SetSubscriptionValue(d_125, temp_161, i_126);

        value_160 = PY_STD_NEXT_FORWARD_arg_1(iterator_159, NULL);
    }




    PyObjectContainer* iterator_162 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_2 (PY_createInteger(5) , PY_createInteger(9)))));
    PyObjectContainer* value_163 = PY_STD_NEXT_FORWARD_arg_1(iterator_162, NULL);
    while (value_163 != NULL) {
        PY_CHECK_EXCEPTION(value_163);
        i_126 = value_163;


        PyObjectContainer* temp_164 = i_126;
        PY_SetSubscriptionValue(d_125, temp_164, i_126);


        value_163 = PY_STD_NEXT_FORWARD_arg_1(iterator_162, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* testresize1_79_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testresize1_79(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testresize1_79(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* teststringkeyscantrackvalues_81(PyObjectContainer* self_80) {
    // Source Location: DictTest.test_string_keys_can_track_values
    PyObjectContainer* d_127;
    PyObjectContainer* i_128;
    PyObjectContainer* j_129;



    PyObjectContainer* iterator_165 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(10)))));
    PyObjectContainer* value_166 = PY_STD_NEXT_FORWARD_arg_1(iterator_165, NULL);
    while (value_166 != NULL) {
        PY_CHECK_EXCEPTION(value_166);
        i_128 = value_166;
        d_127 = PY_STD_dict_CREATE(0);

        PyObjectContainer* iterator_167 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(10)))));
        PyObjectContainer* value_168 = PY_STD_NEXT_FORWARD_arg_1(iterator_167, NULL);
        while (value_168 != NULL) {
            PY_CHECK_EXCEPTION(value_168);
            j_129 = value_168;
            PyObjectContainer* temp_169 = j_129;
            PY_SetSubscriptionValue(d_127, temp_169, PY_CHECK_EXCEPTION(PY_getObjectStr_wrapper (j_129)));

            value_168 = PY_STD_NEXT_FORWARD_arg_1(iterator_167, NULL);
        }
        PyObjectContainer* temp_170 = d_127;
        PY_SetSubscriptionValue(d_127, temp_170, PY_createString("foo"));


        value_166 = PY_STD_NEXT_FORWARD_arg_1(iterator_165, NULL);
    }
    return PY_NONE;
}

PyObjectContainer* teststringkeyscantrackvalues_81_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = teststringkeyscantrackvalues_81(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = teststringkeyscantrackvalues_81(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* makesharedkeydict_84(PyObjectContainer* self_82 , PyObjectContainer* n_83) {
    // Source Location: DictTest.make_shared_key_dict
    PyObjectContainer* C_30;
    PyObjectContainer* a_130;
    PyObjectContainer* dicts_131;
    PyObjectContainer* i_132;

    C_30 = PY_createClass("C", PY_CLASS_INIT_PY_CLASS_C_30);
    dicts_131 = PY_STD_list_CREATE(0);

    PyObjectContainer* iterator_171 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (n_83))));
    PyObjectContainer* value_172 = PY_STD_NEXT_FORWARD_arg_1(iterator_171, NULL);
    while (value_172 != NULL) {
        PY_CHECK_EXCEPTION(value_172);
        i_132 = value_172;
        a_130 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(C_30, NULL, 0, NULL, NULL));

        PyObjectContainer* temporary_tuple_173 = PY_STD_tuple_CREATE(3, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3));
        assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_173)) == 3);
        PyObjectContainer* temp_174 = PY_GetSubscriptionValue(temporary_tuple_173, PY_createInteger(0));
        PY_setObjectAttributeByName(a_130, "x", temp_174);
        PyObjectContainer* temp_175 = PY_GetSubscriptionValue(temporary_tuple_173, PY_createInteger(1));
        PY_setObjectAttributeByName(a_130, "y", temp_175);
        PyObjectContainer* temp_176 = PY_GetSubscriptionValue(temporary_tuple_173, PY_createInteger(2));
        PY_setObjectAttributeByName(a_130, "z", temp_176);
        ;

        PY_CHECK_EXCEPTION(PY_STD_list_append_fast (dicts_131 , PY_getObjectAttributeByNameOrStatic(a_130, "__dict__")));


        value_172 = PY_STD_NEXT_FORWARD_arg_1(iterator_171, NULL);
    }
    return dicts_131;


    return PY_NONE;
}

PyObjectContainer* makesharedkeydict_84_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = makesharedkeydict_84(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = makesharedkeydict_84(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testobjectsetitemsingleinstancenonstrkey_86(PyObjectContainer* self_85) {
    // Source Location: DictTest.test_object_set_item_single_instance_non_str_key
    PyObjectContainer* Foo_31;
    PyObjectContainer* f_133;

    Foo_31 = PY_createClass("Foo", PY_CLASS_INIT_PY_CLASS_Foo_31);
    f_133 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Foo_31, NULL, 0, NULL, NULL));

    PyObjectContainer* temp_177 = PY_createInteger(1);
    PY_SetSubscriptionValue(PY_getObjectAttributeByNameOrStatic(f_133, "__dict__"), temp_177, PY_createInteger(1));

    PyObjectContainer* temp_178 = PY_createString("a");
    PY_setObjectAttributeByName(f_133, "a", temp_178);

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_85, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_getObjectAttributeByNameOrStatic(f_133, "__dict__"), PY_STD_dict_CREATE(2, PY_createInteger(1), PY_createInteger(1), PY_createString("a"), PY_createString("a"))}, NULL));


    return PY_NONE;
}

PyObjectContainer* testobjectsetitemsingleinstancenonstrkey_86_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testobjectsetitemsingleinstancenonstrkey_86(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testobjectsetitemsingleinstancenonstrkey_86(self);
    }

    if (info) free(new_args);
    return result;
}

