/*
 * File name: supermemoSuite.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app - tests
 */

#define BOOST_TEST_MODULE supermemoSuite
#include <boost/test/included/unit_test.hpp>

#include "Course.h"
#include "CoursesManager.h"

BOOST_AUTO_TEST_CASE( GetCoursesNumOnCreationTest )
{
    CoursesManager cm;
    BOOST_TEST( cm.getCoursesNumber() == 0);
}

BOOST_AUTO_TEST_CASE( GetCardsNumOnCreationTest )
{
    Course c;
    BOOST_TEST( c.getCardsCounter() == 0);
}