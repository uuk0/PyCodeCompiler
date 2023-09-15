#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "source.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_source;
#endif

// code compiled from python to c via PyCodeCompiler

#include <assert.h>
#include "standard_library/generator.h"




// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif









    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_1", PY_createBoxForFunction(generator1_1_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_2", PY_createBoxForFunction(generator2_2_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_3", PY_createBoxForFunction(generator3_3_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_4", PY_createBoxForFunction(generator4_4_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_5", PY_createBoxForFunction(generator5_6_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_6", PY_createBoxForFunction(generator6_8_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_7", PY_createBoxForFunction(generator7_10_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "generator_8", PY_createBoxForFunction(generator8_12_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* gen_13;

    gen_13 = PY_CHECK_EXCEPTION(generator1_1 ());

    PyObjectContainer* assert_target_0 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_0));


    gen_13 = PY_CHECK_EXCEPTION(generator2_2 ());

    PyObjectContainer* assert_target_1 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_1));

    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_2));

    PyObjectContainer* assert_target_3 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_3));


    gen_13 = PY_CHECK_EXCEPTION(generator3_3 ());

    PyObjectContainer* assert_target_4 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_4));

    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_5));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_1 (gen_13 , PY_NONE)), PY_NONE));
    assert(PY_getTruthValueOf(assert_target_6));


    gen_13 = PY_CHECK_EXCEPTION(generator4_4 ());

    PyObjectContainer* assert_target_7 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(5)));
    assert(PY_getTruthValueOf(assert_target_7));

    PyObjectContainer* assert_target_8 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_8));


    gen_13 = PY_CHECK_EXCEPTION(generator5_6 ());

    PyObjectContainer* assert_target_9 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_9));

    PyObjectContainer* assert_target_10 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_10));

    PyObjectContainer* assert_target_11 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_11));


    gen_13 = PY_CHECK_EXCEPTION(generator6_8 ());

    PyObjectContainer* assert_target_12 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_12));

    PyObjectContainer* assert_target_13 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_13));

    PyObjectContainer* assert_target_14 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_14));


    gen_13 = PY_CHECK_EXCEPTION(generator7_10 (PY_createInteger(6)));

    PyObjectContainer* assert_target_15 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_15));

    PyObjectContainer* assert_target_16 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(6)));
    assert(PY_getTruthValueOf(assert_target_16));

    PyObjectContainer* assert_target_17 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_17));


    gen_13 = PY_CHECK_EXCEPTION(generator8_12 ());

    PyObjectContainer* assert_target_18 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_18));

    PyObjectContainer* assert_target_19 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_19));

    PyObjectContainer* assert_target_20 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_13)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_20));



    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

PyObjectContainer* generator1_1(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator1_1_ENTRY;
    return generator;
}

PyObjectContainer* generator1_1_ENTRY(PyGeneratorContainer* generator) {
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

PyObjectContainer* generator1_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator1_1();
}

PyObjectContainer* generator2_2(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator2_2_ENTRY;
    return generator;
}

PyObjectContainer* generator2_2_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
        case 3: goto gen_3;
    };

    gen_0:;

    generator->section_id = 1;
    return PY_createInteger(1);
    gen_1:;

    generator->section_id = 2;
    return PY_createInteger(2);
    gen_2:;

    generator->section_id = 3;
    return PY_createInteger(4);
    gen_3:;



    return NULL;
}

PyObjectContainer* generator2_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator2_2();
}

PyObjectContainer* generator3_3(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator3_3_ENTRY;
    return generator;
}

PyObjectContainer* generator3_3_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
        case 3: goto gen_3;
    };

    gen_0:;

    generator->section_id = 1;
    return PY_createInteger(1);
    gen_1:;

    generator->section_id = 2;
    return PY_createInteger(2);
    gen_2:;

    generator->next_section = NULL;
    return PY_NONE;

    generator->section_id = 3;
    return PY_createInteger(5);
    gen_3:;



    return NULL;
}

PyObjectContainer* generator3_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator3_3();
}

PyObjectContainer* generator4_4(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator4_4_ENTRY;
    return generator;
}

PyObjectContainer* generator4_4_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
    };

    gen_0:;

    generator->locals[0] = PY_createInteger(10);

    generator->section_id = 1;
    return PY_createInteger(5);
    gen_1:;

    generator->section_id = 2;
    return generator->locals[0];
    gen_2:;



    return NULL;
}

PyObjectContainer* generator4_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator4_4();
}

PyObjectContainer* generator5_6(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator5_6_ENTRY;
    return generator;
}

PyObjectContainer* generator5_6_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
    };

    gen_0:;

    generator->locals[0] = PY_CHECK_EXCEPTION(PY_STD_operator_iter_for_yield_from (PY_CHECK_EXCEPTION(generator2_2 ()) , generator->locals[0]));
    generator->yield_from_source = PY_STD_operator_iter(generator->locals[0]);
    generator->section_id = 1;
    gen_1:;
    PyObjectContainer* curr_value_21 = PY_STD_operator_next(generator->yield_from_source);

    if (curr_value_21 == NULL)
    {
        generator->section_id = 2;
        goto gen_2;
    }
    return curr_value_21;
    gen_2:;



    return NULL;
}

PyObjectContainer* generator5_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator5_6();
}

PyObjectContainer* generator6_8(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator6_8_ENTRY;
    return generator;
}

PyObjectContainer* generator6_8_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
    };

    gen_0:;

    generator->locals[0] = PY_CHECK_EXCEPTION(PY_STD_operator_iter_for_yield_from (PY_STD_list_CREATE(3, PY_createInteger(1), PY_createInteger(2), PY_createInteger(4)) , generator->locals[0]));
    generator->yield_from_source = PY_STD_operator_iter(generator->locals[0]);
    generator->section_id = 1;
    gen_1:;
    PyObjectContainer* curr_value_22 = PY_STD_operator_next(generator->yield_from_source);

    if (curr_value_22 == NULL)
    {
        generator->section_id = 2;
        goto gen_2;
    }
    return curr_value_22;
    gen_2:;



    return NULL;
}

PyObjectContainer* generator6_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator6_8();
}

PyObjectContainer* generator7_10(PyObjectContainer* x_9) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(2);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator7_10_ENTRY;
    container->locals[0] = x_9;
    return generator;
}

PyObjectContainer* generator7_10_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
        case 3: goto gen_3;
    };

    gen_0:;

    generator->section_id = 1;
    return PY_createInteger(2);
    gen_1:;

    generator->section_id = 2;
    return generator->locals[0];
    gen_2:;

    generator->locals[0] = PY_createInteger(4);

    generator->section_id = 3;
    return generator->locals[0];
    gen_3:;



    return NULL;
}

PyObjectContainer* generator7_10_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return generator7_10(args[0]);
    }
    else
    {
        assert(argc == 0);
        return generator7_10(self);
    }
}

PyObjectContainer* generator8_12(void) {
    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->next_section = generator8_12_ENTRY;
    return generator;
}

PyObjectContainer* generator8_12_ENTRY(PyGeneratorContainer* generator) {
    switch (generator->section_id){
        case 0: goto gen_0;
        case 1: goto gen_1;
        case 2: goto gen_2;
    };

    gen_0:;

    generator->locals[0] = PY_CHECK_EXCEPTION(PY_STD_operator_iter_for_yield_from (PY_STD_list_CREATE(3, PY_createInteger(1), PY_createInteger(2), PY_createInteger(4)) , generator->locals[0]));
    generator->yield_from_source = PY_STD_operator_iter(generator->locals[0]);
    generator->section_id = 1;
    gen_1:;
    PyObjectContainer* curr_value_23 = PY_STD_operator_next(generator->yield_from_source);

    if (curr_value_23 == NULL)
    {
        generator->section_id = 2;
        goto gen_2;
    }
    return curr_value_23;
    gen_2:;
    return NULL;
}

PyObjectContainer* generator8_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator8_12();
}

