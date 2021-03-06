#include "synergy.h"

using namespace taylornet::synergy;

NativeLibrary::NativeLibrary(std::string name, std::string filename, void* lib_ptr)
{
	this->name = name;
	this->filename = filename;
	this->lib_ptr = lib_ptr;
}

void* NativeLibrary::getSymbol(std::string symbol)
{
	if (call_cache.find(symbol) != call_cache.end())
	{
		return call_cache[symbol];
	}
	else
	{
		void* call_ptr = this->getNativeSymbol(symbol.c_str());
		this->registerSymbol(symbol, call_ptr);
		return call_ptr;
	}
}

void NativeLibrary::registerSymbol(std::string symbol, void* symbol_ptr)
{
	if (symbol_ptr == nullptr)
	{
		throw new std::runtime_error("Symbol not found");
	}
	else
	{
		call_cache.insert(std::pair<std::string, void*>(symbol, symbol_ptr));
	}
}

std::string NativeLibrary::getName()
{
	return name;
}

std::string NativeLibrary::getFilename()
{
	return filename;
}

#ifdef WINDOWS
	#include "./natives/windows/library_windows.cpp"
#elif defined(POSIX)
	#include "./natives/posix/library_posix.cpp"
#endif