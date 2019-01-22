// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include <conio.h>
#include <iostream>
#include <fstream>


#include "ErrorCode.h"
#include "PyroCamLibraryInterface.h"
#include "stb_image_write.h"

#include <string>




using namespace System;
using namespace System::Windows::Forms;

//---- Library Info ----
typedef const char* (__cdecl * TGetLibraryVersion)(void);

//---- Init GigE Device ----
typedef int(__cdecl * TInitDeviceGUI)(void);
typedef int(__cdecl * TCloseDevice)(void);

//---- Data Streaming ----
typedef int(__cdecl * TStartStreaming)(void);
typedef int(__cdecl * TStopStreaming)(void);

//---- Image Data ----
typedef unsigned short*(__cdecl * TGetVisibleImage)(void);
typedef unsigned short*(__cdecl * TGetTemperaturImage)(void);
typedef int(__cdecl * TGetFrameCounter)(int &CtrImageProcessing, int &CtrImageStreaming);

//---- Frame ---
typedef int(__cdecl * TSetFrameSize)(int Width, int Height, int X, int Y);
typedef int(__cdecl * TGetFrameSize)(int *pWidth, int *pHeight, int *pX, int *pY);

//---- Camera Calibrations Settings ----
typedef int(__cdecl * TLoadCalibration)(const char *);
typedef int(__cdecl * TGetCalibrationInfo)(TPyroCamCalibrationInfo& Info);

[STAThread]
int main() 
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLR_WinformsProjekt::Form1()); // "CppCLR_WinformsProjekt" noch anpassen
	return 0;
}