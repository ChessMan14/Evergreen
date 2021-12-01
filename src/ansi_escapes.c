#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include "ansi_escapes.h"

#ifdef _WIN32
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
	DWORD outMode = 0;
	stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if(stdoutHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
		}
	
	if(!GetConsoleMode(stdoutHandle, &outMode)) {
		exit(GetLastError());
	}

	outModeInit = outMode;
	
	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(!SetConsoleMode(stdoutHandle, outMode)) {
		exit(GetLastError());
	}	
}

void restoreConsole(void) {
    printf("\x1b[0m");	
	
	if(!SetConsoleMode(stdoutHandle, outModeInit)) {
		exit(GetLastError());
	}
}
#else
void setupConsole(void) {}

void restoreConsole(void) {
    printf("\x1b[0m");
}
#endif