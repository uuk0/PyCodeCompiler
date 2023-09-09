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

void PY_MODULE_source_init(void) {
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
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* gen_4;

    gen_4 = PY_CHECK_EXCEPTION(generator1_1 ());

    PyObjectContainer* assert_target_0 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_0));


    gen_4 = PY_CHECK_EXCEPTION(generator2_2 ());

    PyObjectContainer* assert_target_1 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_1));

    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_2));

    PyObjectContainer* assert_target_3 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(4)));
    assert(PY_getTruthValueOf(assert_target_3));


    gen_4 = PY_CHECK_EXCEPTION(generator3_3 ());

    PyObjectContainer* assert_target_4 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_4));

    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_0 (gen_4)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_5));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_NEXT_FORWARD_arg_1 (gen_4 , PY_NONE)), PY_NONE));
    assert(PY_getTruthValueOf(assert_target_6));



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
    return NULL;
}

PyObjectContainer* generator3_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return generator3_3();
}

