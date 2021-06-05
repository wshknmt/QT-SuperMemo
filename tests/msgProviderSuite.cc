/*
 * File name: msgProviderSuite.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app - tests
 */

#define BOOST_TEST_MODULE MsgProviderSuite
#include <boost/test/included/unit_test.hpp>

#include "MsgProvider.h"

BOOST_AUTO_TEST_CASE( GetMsgTest )
{
    MsgProvider msgp;
    BOOST_TEST( msgp.getMsg() == "Tutaj powstanie niesamowita aplikacja!");
}
