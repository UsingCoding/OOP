#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <sstream>
#include <float.h>
#include <math.h>


#include "../CComplex/Complex/Complex.hpp"

SCENARIO("Perform mathmematical operations with Complex")
{
    GIVEN("Complex number with real and image part")
    {
        Complex complex(3, 4);

        THEN("We can get image part")
        {
            REQUIRE(complex.Im() == 4.0);
        }

        THEN("We can get real part")
        {
            REQUIRE(complex.Re() == 3.0);
        }

        THEN("We can get magnitude")
        {
            REQUIRE(complex.GetMagnitude() == 5);
        }

        THEN("We can get Complex number argument")
        {
            GIVEN("Number with real 4 and image 4")
            {
                Complex number(4, 4);

                THEN("We calculate his argument")
                {
                    REQUIRE(number.GetArgument() == 45.0);
                }
            }
        }

        AND_GIVEN("Another Complex number")
        {
            Complex complicated = {1, 3};

            WHEN("We adding two complex numbers")
            {
                Complex res = complex + complicated;

                THEN("We got new complex number which image part is equal summ of image part of these two numbers, same with real part")
                {
                    REQUIRE(res.Im() == complex.Im() + complicated.Im());
                    REQUIRE(res.Re() == complex.Re() + complicated.Re());
                }
            }

            WHEN("We subtract two complex numbers")
            {
                Complex res = complex - complicated;

                THEN("We get a number whose parts are equal to subtracting the corresponding parts from other numbers")
                {
                    REQUIRE(res.Im() == complex.Im() - complicated.Im());
                    REQUIRE(res.Re() == complex.Re() - complicated.Re());
                }
            }

            WHEN("We multiply two numbers")
            {
                Complex res = complex * complicated;

                THEN("We get a number with transposed parts")
                {
                    REQUIRE(res.Im() == 13.0);
                    REQUIRE(res.Re() == -9.0);
                }
            }

            WHEN("We divide two numbers")
            {
                Complex res = complex / complicated;

                THEN("We get a number with divided parts parts")
                {
                    REQUIRE(res.Im() == 0.52);
                    REQUIRE(res.Re() == -0.36);
                }
            }
            GIVEN("Copy of complex")
            {
                Complex complexCopy = complex;

                WHEN("We summ numbers and assign result to first one")
                {
                    complex += complicated;

                    THEN("We got same result if summ numbers and assign to another")
                    {
                        REQUIRE(complex == (complexCopy + complicated));
                    }
                }
            }

            WHEN("We compare two complex numbers with different image and real parts")
            {
                bool res = complex != complicated;

                THEN("We got that these numbers are not equal")
                {
                    REQUIRE(res);
                }
            }

            GIVEN("New complex number that real and image part is equal to complex")
            {
                Complex c = {3, 4};
                WHEN("We compare two complex numbers with equal image and real parts")
                {
                    bool res = complex == c;

                    THEN("We got that these numbers are equal")
                    {
                        REQUIRE(res);
                    }
                }
            }

            WHEN("We use unary +")
            {
                Complex c = complex;

                THEN("We got copy of this number")
                {
                    REQUIRE(c == complex);
                }
            }

            WHEN("We use unary -")
            {
                Complex c = -complex;

                THEN("We got copy of this number but with opposite signs")
                {
                    REQUIRE(c.Re() == -(complex.Re()));
                    REQUIRE(c.Im() == -(complex.Im()));
                }
            }

            AND_GIVEN("Input stream with string represenatation of complex number")
            {
                std::istringstream input("-1+3i");

                WHEN("We read complex number from input stream")
                {
                    input >> complex;

                    THEN("We got number")
                    {
                        REQUIRE(complex.Re() == -1);
                        REQUIRE(complex.Im() == 3);
                    }
                }
            }

            AND_GIVEN("Output stream")
            {
                std::ostringstream output;

                WHEN("We write complex number into stream")
                {
                    output << complex;

                    THEN("We got string representation of complex number")
                    {
                        REQUIRE(output.str() == "3+4i");
                    }
                }
            }
        }
    }

    GIVEN("Complex number with 0 real part")
    {
        Complex complex = {0 ,4};

        WHEN("We try ot get magnitude")
        {
            bool wasError = false;

            try
            {
                complex.GetArgument();
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }

            THEN("We got error dividing by zero")
            {
                REQUIRE(wasError);
            }
        }
    }
}
