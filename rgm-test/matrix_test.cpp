
#include <rtest/rtest.h>
#include <rgm/rgm.h>

// disable warning about unused variables
#pragma warning(disable: 4101)

SUITE(matrix)
{
    TEST(types)
    {
        rgm::bmat2 bv2;
        rgm::bmat3 bv3;
        rgm::bmat4 bv4;

        rgm::imat2 iv2;
        rgm::imat3 iv3;
        rgm::imat4 iv4;

        rgm::umat2 uiv2;
        rgm::umat3 uiv3;
        rgm::umat4 uiv4;

        rgm::mat2 v2;
        rgm::mat3 v3;
        rgm::mat4 v4;

        rgm::dmat2 dv2;
        rgm::dmat3 dv3;
        rgm::dmat4 dv4;
    }

    TEST(init3)     
    {        
        rgm::mat3 m(1.0f, 4.0f, 7.0f, 
                    2.0f, 5.0f, 8.0f, 
                    3.0f, 6.0f, 9.0f);
        CHECK_EQUAL(1.0f, m[0][0]);
        CHECK_EQUAL(2.0f, m[0][1]);
        CHECK_EQUAL(3.0f, m[0][2]);
        CHECK_EQUAL(4.0f, m[1][0]);
        CHECK_EQUAL(5.0f, m[1][1]);
        CHECK_EQUAL(6.0f, m[1][2]);
        CHECK_EQUAL(7.0f, m[2][0]);
        CHECK_EQUAL(8.0f, m[2][1]);
        CHECK_EQUAL(9.0f, m[2][2]);

        rgm::vec3 v = m[1];
        CHECK_EQUAL(4.0f, v[0]);
        CHECK_EQUAL(5.0f, v[1]);
        CHECK_EQUAL(6.0f, v[2]);
    }

    TEST(copy)
    {
        rgm::mat3 o(1.0f, 4.0f, 7.0f, 
                    2.0f, 5.0f, 8.0f, 
                    3.0f, 6.0f, 9.0f);
        rgm::mat3 m(o);

        CHECK_EQUAL(1.0f, m[0][0]);
        CHECK_EQUAL(2.0f, m[0][1]);
        CHECK_EQUAL(3.0f, m[0][2]);
        CHECK_EQUAL(4.0f, m[1][0]);
        CHECK_EQUAL(5.0f, m[1][1]);
        CHECK_EQUAL(6.0f, m[1][2]);
        CHECK_EQUAL(7.0f, m[2][0]);
        CHECK_EQUAL(8.0f, m[2][1]);
        CHECK_EQUAL(9.0f, m[2][2]);
    }

    TEST(assignment)
    {
        rgm::mat3 o(1.0f, 4.0f, 7.0f, 
                    2.0f, 5.0f, 8.0f, 
                    3.0f, 6.0f, 9.0f);
        rgm::mat3 m;
        m = o;

        CHECK_EQUAL(1.0f, m[0][0]);
        CHECK_EQUAL(2.0f, m[0][1]);
        CHECK_EQUAL(3.0f, m[0][2]);
        CHECK_EQUAL(4.0f, m[1][0]);
        CHECK_EQUAL(5.0f, m[1][1]);
        CHECK_EQUAL(6.0f, m[1][2]);
        CHECK_EQUAL(7.0f, m[2][0]);
        CHECK_EQUAL(8.0f, m[2][1]);
        CHECK_EQUAL(9.0f, m[2][2]);
    }
}