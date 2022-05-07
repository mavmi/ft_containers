#include "../../include/tests/vector_tests.hpp"

namespace VECTOR_TESTS{

void RUN_VECTOR_TESTS(){
    Printer::print("\n\t=== VECTOR TESTS ===", true, Printer::YELLOW);

    {
        CONSTRUCTOR<int>(42);
        CONSTRUCTOR<double>(42);
        CONSTRUCTOR<std::string>("42");
    }

    {
        ASSIGNMENT_OPERATOR<int>(42);
        ASSIGNMENT_OPERATOR<double>(42);
        ASSIGNMENT_OPERATOR<std::string>("42");
    }

    {
        ASSIGN<int>(42);
        ASSIGN<double>(42);
        ASSIGN<std::string>("42");
    }

    {
        GET_ALLOCATOR<int>();
        GET_ALLOCATOR<double>();
        GET_ALLOCATOR<std::string>();
    }

    {
        GETTER<int>(42);
        GETTER<double>(42);
        GETTER<std::string>("42");
    }

    {
        FRONT_BACK<int>(42);
        FRONT_BACK<double>(42);
        FRONT_BACK<std::string>("42");
    }

    {
        ITERATORS<int>(42);
        ITERATORS<double>(42);
        ITERATORS<std::string>("42");
    }

    {
        RESERVE<int>(42);
        RESERVE<double>(42);
        RESERVE<std::string>("42");
    }

    {
        INSERT<int>(42);
        INSERT<double>(42);
        INSERT<std::string>("42");
    }

    {
        ERASE<double>(42);
        ERASE<std::string>("42");
        ERASE< std::pair< std::allocator<std::string>, std::string > >(std::pair< std::allocator<std::string>, std::string >());
    }

    {
        PUSH_BACK<double>(42);
        PUSH_BACK<std::string>("42");
        PUSH_BACK< std::pair< std::allocator<std::string>, std::string > >(std::pair< std::allocator<std::string>, std::string >());
    }

    {
        POP_BACK<double>(42);
        POP_BACK<std::string>("42");
        POP_BACK< std::pair< std::allocator<std::string>, std::string > >(std::pair< std::allocator<std::string>, std::string >());
    }

    {
        RESIZE<double>();
        RESIZE<std::string>();
        RESIZE< std::pair< std::allocator<std::string>, std::string > >();
    }

    {
        OPERATORS<long long>(42);
        OPERATORS<double>(42);
        OPERATORS<std::string>("42");
    }
}

}
