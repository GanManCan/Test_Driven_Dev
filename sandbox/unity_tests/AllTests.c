#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(LedDriver);
}

int main(int ac, char* av[]){
    return UnityMain(ac, av, RunAllTests);
}