#include <TyInput.h>

bool	TyInput::RefreshKeys()
{
	return (s3eKeyboardUpdate() == S3E_RESULT_SUCCESS) ? true : false;
}