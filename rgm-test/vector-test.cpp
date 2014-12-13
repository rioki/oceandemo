
#include <rtest/rtest.h>
#include <rgm/rgm.h>

// disable warning about unused variables
#pragma warning(disable: 4101)

SUITE(vector)
{
    TEST(types)
    {
        rgm::bvec2 bv2;
        rgm::bvec3 bv3;
        rgm::bvec4 bv4;

        rgm::ivec2 iv2;
        rgm::ivec3 iv3;
        rgm::ivec4 iv4;

        rgm::uvec2 uiv2;
        rgm::uvec3 uiv3;
        rgm::uvec4 uiv4;

        rgm::vec2 v2;
        rgm::vec3 v3;
        rgm::vec4 v4;

        rgm::dvec2 dv2;
        rgm::dvec3 dv3;
        rgm::dvec4 dv4;
    }
    
    TEST(init2)
    {
        rgm::vec2 v(1.0f, 2.0f);
        
        CHECK_EQUAL(1.0f, v[0]);
        CHECK_EQUAL(2.0f, v[1]);
    }

    TEST(init3)
    {
        rgm::vec3 v(1.0f, 2.0f, 3.0f);
        
        CHECK_EQUAL(1.0f, v[0]);
        CHECK_EQUAL(2.0f, v[1]);
        CHECK_EQUAL(3.0f, v[2]);
    }

    TEST(init4)
    {
        rgm::vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
        
        CHECK_EQUAL(1.0f, v[0]);
        CHECK_EQUAL(2.0f, v[1]);
        CHECK_EQUAL(3.0f, v[2]);
        CHECK_EQUAL(4.0f, v[3]);
    }

    TEST(add)
    {
        CHECK_EQUAL(rgm::vec3(1.1f, 2.2f, 3.3f), rgm::vec3(1.0f, 2.0f, 3.0f) + rgm::vec3(0.1f, 0.2f, 0.3f));
    }

    TEST(sub)
    {
        CHECK_EQUAL(rgm::vec3(0.9f, 1.8f, 2.7f), rgm::vec3(1.0f, 2.0f, 3.0f) - rgm::vec3(0.1f, 0.2f, 0.3f));
    }

    TEST(mul_s)
    {
        CHECK_EQUAL(rgm::vec3(2.0f, 4.0f, 6.0f), rgm::vec3(1.0f, 2.0f, 3.0f) * 2.0f);
        CHECK_EQUAL(rgm::vec3(2.0f, 4.0f, 6.0f), 2.0f * rgm::vec3(1.0f, 2.0f, 3.0f));
    }
 }
