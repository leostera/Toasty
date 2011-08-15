#include <tut.hpp>
#include <tut_reporter.hpp>
#include <iostream>

#include <Iw2D.h>
#include <IwResManager.h>
#include <TyInput.h>
#include <TyClock.h>

using std::exception;
using std::cerr;
using std::endl;

namespace tut
{
    test_runner_singleton runner;
}

int main()
{
	int result;

	Iw2DInit();
	IwResManagerInit();	
	TyInputInit();
	TyClockInit();

    tut::reporter reporter;
    tut::runner.get().set_callback(&reporter);
    tut::runner.get().run_tests();

	result = !reporter.all_ok();
	
	TyClockTerminate();
	TyInputTerminate();
	IwResManagerTerminate();
	Iw2DTerminate();

    return result;
}