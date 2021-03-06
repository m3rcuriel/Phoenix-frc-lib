#include "ctre/phoenix/CTRLogger.h"
#include <execinfo.h>

namespace CTRE {
	
void CTRLogger::Open(int language) {
	c_Logger_Open(language, true);
}
CTR_Code CTRLogger::Log(CTR_Code code, std::string origin) {
	void *buf[100];
	char **strings;
	int size = backtrace(buf, 100);
	strings = backtrace_symbols(buf, size);
	std::string stackTrace;
	for(int i = 1; i < size; i++) {
		stackTrace += strings[i];
		stackTrace += "\n";
	}
	return c_Logger_Log(code, origin.c_str(), stackTrace.c_str());
}
void CTRLogger::Close() {
	c_Logger_Close();
}
void CTRLogger::Description(CTR_Code code, const char *&shrt, const char *&lng) {
	c_Logger_Description(code, shrt, lng);
}
	
}