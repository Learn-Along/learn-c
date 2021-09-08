#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../src/hello_world.h"

// START_TEST(TestAppendItem)
// {
//     List records;
//     char* strings[] = {"hi", "hello", "bonjour", "t'abwooli", "origye?"};
//     int stringsCount = sizeof(strings) / sizeof(char*);    
//     char* expected = "{hi, hello, bonjour, t'abwooli, origye?}";
//     char* actual;

//     for (int i = 0; i < stringsCount; i++)
//     {
//         appendItem(&records, strings[i]);
//     }

//     actual = toString(&records);
//     ck_assert_msg(
//         strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);

//     free(actual);

//     // freeList(&records);    
// }
// END_TEST

// START_TEST(TestInsertItem)
// {

// }
// END_TEST

START_TEST(TestCreateHeapAllocatedString)
{
    char* expected = "hello there";
    char* actual = __createHeapAllocatedString(expected, strlen(expected));
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);
    free(actual);
}
END_TEST

START_TEST(TestConcatString)
{
    size_t sizeOfCharPtr = sizeof(char*);
    char* dest = (char*) malloc((2 * sizeOfCharPtr) + 1);
    strcpy(dest, "hi");

    char* src = (char*) malloc((6 * sizeOfCharPtr) + 1);
    strcpy(src, " world");

    char* expected = "hi world";
    __concatString(dest, src, 2);
    ck_assert_msg(
        strcmp(expected, dest) == 0, "expected %s; got %s", expected, dest);
    
    FREE_IF_DEFINED(dest);
    FREE_IF_DEFINED(src);
}
END_TEST

Suite* createHelloWorldTestSuite(void){
    Suite *s;
    TCase *tcCore;

    s = suite_create("Doubly-linked list");

    tcCore = tcase_create("Core");
    tcase_add_test(tcCore, TestCreateHeapAllocatedString);
    tcase_add_test(tcCore, TestConcatString);
    // tcase_add_test(tcCore, TestAppendItem);

    suite_add_tcase(s, tcCore);
    return s;
}

int main(void)
{
    int numberFailed;
    Suite* s;
    SRunner *sr;

    s = createHelloWorldTestSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numberFailed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (numberFailed > 0)? EXIT_FAILURE: EXIT_SUCCESS;
}