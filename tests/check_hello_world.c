#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../src/hello_world.h"

START_TEST(TestCreateHeapAllocatedString)
{
    char* expected = "hello there";
    char* actual = __createHeapAllocatedString(expected, strlen(expected));
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);
    free(actual);
}
END_TEST

// START_TEST(TestPrintList)
// {
//     char* strings[] = {"hi", "hello", "bonjour", "t'abwooli", "origye?"};
//     char* expected = "{hi, hello, bonjour, t'abwooli, origye?}";
//     char* actual = "";

    // _Record data[] = {
    //     {.value = strings[0], .next = strings[1]},
    //     {.previous = strings[0], .value = strings[1], .next = strings[2]},
    //     {.previous = strings[1], .value = strings[2], .next = strings[3]},
    //     {.previous = strings[2], .value = strings[3], .next = strings[4]},
    //     {.previous = strings[3], .value = strings[4]},
    // };
    // List records = { .data=data, .length=sizeof(data)  };


    // FILE* dummyStdin = fopen("dummy-stdin-test-print-list.txt", "w+");    
    // printList(&records, dummyStdin);
    
    // int bufferSize = 300;
    // char buffer[300];
    // while(fgets(buffer, bufferSize, dummyStdin) != NULL){
    //     strcat(actual, buffer);
    // }

    // if(!feof(dummyStdin)){
    //     fclose(dummyStdin);
    //     ck_abort_msg("Dummy Stdin never reached the end of file");
    // } else {
    //     fclose(dummyStdin);
    //     ck_assert_msg(
    //         strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);
    // }    
// }
// END_TEST

Suite* createHelloWorldTestSuite(void){
    Suite *s;
    TCase *tcCore;

    s = suite_create("Hello World");

    tcCore = tcase_create("Core");
    tcase_add_test(tcCore, TestCreateHeapAllocatedString);
    // tcase_add_test(tcCore, TestPrintList);

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