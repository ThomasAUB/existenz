#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "../include/existenz.h"


// compile-time tests

MEMBER_FUNCTION(myMemberFunction);

STATIC_MEMBER_FUNCTION(myStaticMemberFunction);

MEMBER(myMember);

MEMBER(myStaticMember);

namespace A {

    struct Test {
        
        bool operator>(Test) {
            return false;
        }
        
        bool operator<(Test) {
            return false;
        }
        
        bool operator>=(Test) {
            return false;
        }
        
        bool operator<=(Test) {
            return false;
        }

        void myMemberFunction() {}

        static bool myStaticMemberFunction(int) {return true;}

        float myMember;

        static bool myStaticMember;

    };

}

namespace B {

    struct Test {};

}

static_assert(exz::member_function_myMemberFunction::exists<A::Test>(), "EXISTENZ");
static_assert(!exz::member_function_myMemberFunction::exists<B::Test>(), "EXISTENZ");

static_assert(exz::static_member_function_myStaticMemberFunction::exists<A::Test, bool, int>(), "EXISTENZ");
static_assert(!exz::static_member_function_myStaticMemberFunction::exists<B::Test, bool, int>(), "EXISTENZ");

static_assert(exz::member_myMember::exists<A::Test, float>(), "EXISTENZ");
static_assert(!exz::member_myMember::exists<B::Test, float>(), "EXISTENZ");

static_assert(exz::member_myStaticMember::exists<A::Test, bool>(), "EXISTENZ");
static_assert(!exz::member_myStaticMember::exists<B::Test, bool>(), "EXISTENZ");


static_assert(exz::op::superior::exists<A::Test>(), "EXISTENZ");
static_assert(!exz::op::superior::exists<B::Test>(), "EXISTENZ");

static_assert(exz::op::inferior::exists<A::Test>(), "EXISTENZ");
static_assert(!exz::op::inferior::exists<B::Test>(), "EXISTENZ");

static_assert(exz::op::superior_equal::exists<A::Test>(), "EXISTENZ");
static_assert(!exz::op::superior_equal::exists<B::Test>(), "EXISTENZ");

static_assert(exz::op::inferior_equal::exists<A::Test>(), "EXISTENZ");
static_assert(!exz::op::inferior_equal::exists<B::Test>(), "EXISTENZ");


bool A::Test::myStaticMember = true;


int main(){
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    // std::ofstream xmlFileOut("MicroParcelMessageTest.xml");
    // CPPUNIT_NS::XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    // xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
