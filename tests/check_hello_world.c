#include <stdlib.h>
#include <check.h>
#include <string.h>
#include "../src/hello_world.h"

START_TEST(TestInsertItem)
{
    char* secondStr = "hello"; // on index 1
    char* fourthStr = "t'abwooli"; // on index 3   
    char* expected = "{'hi', 'hello', 'bonjour', 't'abwooli', 'origye?'}";
    char* actual;

    _Record* data[] = {
        __createRecord(NULL, "hi", NULL), 
        __createRecord(NULL, "bonjour", NULL),
        __createRecord(NULL, "origye?", NULL),
    };

    // arranging in order
    data[0]->next = data[1];
    data[1]->next = data[2];

    List records = {.data=data[0], .length=3};

    // insert
    insertItem(&records, secondStr, 1);
    insertItem(&records, fourthStr, 3);  

    actual = toString(&records);
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);

    FREE_IF_DEFINED(actual);

    freeList(&records);    
}
END_TEST


START_TEST(TestAppendItem)
{
    List records;
    char* strings[] = {"hi", "hello", "bonjour", "t'abwooli", "origye?"};
    int stringsCount = sizeof(strings) / sizeof(char*);    
    char* expected = "{'hi', 'hello', 'bonjour', 't'abwooli', 'origye?'}";
    char* actual;

    for (int i = 0; i < stringsCount; i++)
    {
        appendItem(&records, strings[i]);
    }

    actual = toString(&records);
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);

    FREE_IF_DEFINED(actual);

    freeList(&records);    
}
END_TEST

START_TEST(TestToString)
{
    _Record* first = __createRecord(NULL, "hi", NULL);
    _Record* second = __createRecord(NULL, "hello", NULL);
    _Record* third = __createRecord(NULL, "bonjour", NULL);

    // arranging in order
    first->next = second;
    second->next = third;

    List records = {.data=first, .length=3};
    
    char* expected = "{'hi', 'hello', 'bonjour'}";
    char* actual = toString(&records);
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);
    FREE_IF_DEFINED(actual);
    freeList(&records);
}
END_TEST

START_TEST(TestCreateHeapAllocatedString)
{
    char* expected = "hello there";
    char* actual = __createHeapAllocatedString(expected, strlen(expected));
    ck_assert_msg(
        strcmp(expected, actual) == 0, "expected %s; got %s", expected, actual);
    FREE_IF_DEFINED(actual);
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
    tcase_add_test(tcCore, TestToString);
    tcase_add_test(tcCore, TestAppendItem);
    tcase_add_test(tcCore, TestInsertItem);

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