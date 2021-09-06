#include <check.h>
#include <string.h>
#include <stdlib.h>
#include "../src/hello_world.h"

START_TEST(test_createHeapAllocatedString)
{
    char* sampleString = "hello there";
    char* outputString = createHeapAllocatedString(sampleString, strlen(sampleString));
    ck_assert_str_eq(sampleString, outputString);
    free(outputString);
}
END_TEST

int main(void)
{
    return 0;
}