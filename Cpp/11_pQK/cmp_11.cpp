#include <boost/multiprecision/gmp.hpp>
#include <iostream>

int main()
{
   using namespace boost::multiprecision;

   mpz_int v = 1;

   // Do some arithmetic:
   for(unsigned i = 1; i <= 1000; ++i)
      v *= i;

   std::cout << v << std::endl; // prints 1000!

   // Access the underlying representation:
   mpz_t z;
   mpz_init(z);
   mpz_set(z, v.backend().data());
   mpz_clear(z);
   return 0;
}