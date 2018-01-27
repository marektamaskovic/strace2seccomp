#define TAOCPP_PEGTL_NAMESPACE mylib_pegtl

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/json.hpp>

int main( int argc, char* argv[] )
{
   if( argc > 1 ) {
     tao::mylib_pegtl::argv_input<> in( argv, 1 );
     tao::mylib_pegtl::parse< tao::mylib_pegtl::json::text >( in );
   }
}
