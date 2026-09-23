#ifndef LITTLE_OS_TEST_H
#define LITTLE_OS_TEST_H

// State passed to each test case.
struct test {
    const char *name;
    void (*fn)(struct test *t);
};

// An individual test case: a name + a function receiving the test state.
struct test_case {
    const char *name;
    void (*fn)(struct test *t);
};

/**
 * Prints a per-assertion failure line.
 *
 * @param test_name - the name of the test.
 * @param file
 * @param line
 * @param expr
 */
void test_report_failure(const char *test_name, const char *file, int line, const char *expr);

/**
 * Runs all test suites. prints [PASS]/[FAIL], with the totals.
 *
 * @param suites
 * @param count
 * @return the number of failed checks (0 == everything passed).
 */
int run_all_tests(const struct test_case *suites, int count);


#define EXPECT_TRUE(t, condition)                                             \
    do {                                                                      \
        (t)->checks++;                                                        \
        if (!(condition)) {                                                   \
            (t)->failures++;                                                  \
            test_report_failure((t)->name, __FILE__, __LINE__, #condition);   \
        }                                                                     \
} while (0)

// Macro to assert a == b without printing the values.
#define EXPECT_EQ(t, a, b) do {                                               \
    (t)->checks++;                                                            \
    if ((a) != (b)) {                                                         \
        (t)->failures++;                                                      \
        test_report_failure((t)->name, __FILE__, __LINE__, #a " == " #b);     \
    }                                                                         \
} while (0)

#define ASERT_TRUE(t, condition)                                              \
    do {                                                                      \
        (t)->checks++;                                                        \
        if (!(condition)) {                                                   \
            (t)->failures++;                                                  \
            test_report_failure((t)->name, __FILE__, __LINE__, #condition);   \
            return;                                                           \
        }                                                                     \
    } while (0)

#define ASSERT_EQ(t, a, b)                                                    \
    do {                                                                      \
        (t)->checks++;                                                        \
        if ((a) != (b)) {                                                     \
            (t)->failures++;                                                  \
            test_report_failure((t)->name, __FILE__, __LINE__, #a " == " #b); \
        }                                                                     \
} while (0)


#endif //LITTLE_OS_TEST_H