#include <tut.hpp>
#include <tut_reporter.hpp>
#include <iostream>

#include <Toasty.h>

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

	TySystemInit(TOASTY_SYSTEM_2D | TOASTY_SYSTEM_CLOCK | TOASTY_SYSTEM_INPUT | TOASTY_SYSTEM_SCENEMGR | TOASTY_SYSTEM_DEBUG);

    tut::reporter reporter;
    tut::runner.get().set_callback(&reporter);
    tut::runner.get().run_tests();

	result = !reporter.all_ok();
	
	TySystemtTerminate(TOASTY_SYSTEM_2D | TOASTY_SYSTEM_CLOCK | TOASTY_SYSTEM_INPUT | TOASTY_SYSTEM_SCENEMGR | TOASTY_SYSTEM_DEBUG);

    return result;
}