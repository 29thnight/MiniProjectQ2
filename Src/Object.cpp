#include <CoreDefine.h>
#include <Object.h>

void Engine::Object::CreateObjectDirectory()
{
	string convertName = _name;
	_pwstring basePath = L"Assets";
	CreateDirectory(basePath, nullptr);

	_pwstring path = (string)basePath + L"\\" + convertName;
	if(CreateDirectory(path, nullptr))
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
			return;
	}
}

_uint Engine::Object::ID = 0;


