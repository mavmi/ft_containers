#include "../include/tests/vector_tests.hpp"
#include "../include/tests/stack_tests.hpp"
#include "../include/tests/map_tests.hpp"
#include "../include/tests/set_tests.hpp"

int main(){
    VECTOR_TESTS::RUN_VECTOR_TESTS();
    MAP_TESTS::RUN_MAP_TESTS();
    SET_TESTS::RUN_SET_TESTS();
    STACK_TESTS::RUN_STACK_TESTS();

    Printer::print("\n\t=== END ===", true, Printer::YELLOW);
}
