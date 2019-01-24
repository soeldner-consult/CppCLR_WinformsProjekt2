#pragma once

#include "stdafx.h"
#include "Form1.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <WinBase.h>

#include "ErrorCode.h"
#include "PyroCamLibraryInterface.h"
#include "stb_image_write.h"
#include <msclr/marshal.h>
#include <string>
#include <stdio.h>
#include "BitMap.cpp"
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <fstream>
#include <vector>



//#include <opencv2/open>
#include <opencv2/opencv.hpp>


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

//---- Backlight Suppression Settings ----
typedef int(__cdecl * TSetBacklightSuppressionThreshold)(int ThresValue);
typedef int(__cdecl * TGetBacklightSuppressionThreshold)(int *pThresValue);
typedef int(__cdecl * TSetBacklightSuppressionClampMode)(int Mode);
typedef int(__cdecl * TGetBacklightSuppressionClampMode)(int *pMode);
typedef int(__cdecl * TSetBacklightSuppression)(int Mode);


namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Threading;
	

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		
		int error;
		int Width, Height, X, Y;
		boolean streaming;
		HINSTANCE hDLL;

		TGetLibraryVersion pGetLibraryVersion;

		TInitDeviceGUI pInitDeviceGUI;
		TCloseDevice pCloseDevice;

		TStartStreaming	pStartStreaming;
		TStopStreaming pStopStreaming;

		TGetFrameCounter pGetFrameCounter;

		TLoadCalibration pLoadCalibration;
		TGetCalibrationInfo	pGetCalibrationInfo;

		TGetTemperaturImage	pGetTemperaturImage;
		TGetVisibleImage pGetVisibleImage;

		TGetFrameSize pGetFrame;
		TSetFrameSize pSetFrame;

		TSetBacklightSuppressionThreshold pSetBacklightSuppressionThreshold;
		TGetBacklightSuppressionThreshold pGetBacklightSuppressionThreshold;
		TSetBacklightSuppression pSetBacklightSuppression;
		TSetBacklightSuppressionClampMode pSetBacklightSuppressionClampMode;
		TGetBacklightSuppressionClampMode pGetBacklightSuppressionClampMode;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	public: char* bildbyte;
	private: System::Windows::Forms::Label^  label31;
	public:
	private: System::Windows::Forms::Label^  label32;
	public: long LengthOfArray;


		Form1(void)
		{
			InitializeComponent();
			//
			
			//
			//HINSTANCE hDLL;
			this->hDLL = LoadLibrary(L"C:\\Pyrocam\\NewApp\\CppCLR_WinformsProjekt2\\CppCLR_WinformsProjekt2\\PyroCam.dll");

			this->pGetLibraryVersion = (TGetLibraryVersion)GetProcAddress(hDLL, "GetLibraryVersion");

			this->pInitDeviceGUI = (TInitDeviceGUI)GetProcAddress(hDLL, "DeviceInitGUI");
			this->pCloseDevice = (TCloseDevice)GetProcAddress(hDLL, "DeviceClose");

			this->pStartStreaming = (TStartStreaming)GetProcAddress(hDLL, "StartStreaming");
			this->pStopStreaming = (TStopStreaming)GetProcAddress(hDLL, "StopStreaming");

			this->pGetFrameCounter = (TGetFrameCounter)GetProcAddress(hDLL, "GetFrameCounter");

			this->pLoadCalibration = (TLoadCalibration)GetProcAddress(hDLL, "LoadCalibration");
			this->pGetCalibrationInfo = (TGetCalibrationInfo)GetProcAddress(hDLL, "GetCalibrationInfo");

			this->pGetTemperaturImage = (TGetTemperaturImage)GetProcAddress(hDLL, "GetThermoImageData");
			this->pGetVisibleImage = (TGetVisibleImage)GetProcAddress(hDLL, "GetVisibleImageData");

			this->pGetFrame = (TGetFrameSize)GetProcAddress(hDLL, "GetFrame");
			this->pSetFrame = (TSetFrameSize)GetProcAddress(hDLL, "SetFrame");
			
			this->pSetBacklightSuppressionThreshold = (TSetBacklightSuppressionThreshold)GetProcAddress(hDLL, "Set Backlight Suppression Threhold");
			this->pGetBacklightSuppressionThreshold = (TGetBacklightSuppressionThreshold)GetProcAddress(hDLL, "Get Backlight Suppression Threshold");
			this->pGetBacklightSuppressionClampMode = (TGetBacklightSuppressionClampMode)GetProcAddress(hDLL, "Get Backlight Suppression Clamp Mode");
			this->pSetBacklightSuppressionClampMode = (TSetBacklightSuppressionClampMode)GetProcAddress(hDLL, "Set Backlight Suppression Clamp Mode");
			this->pSetBacklightSuppression = (TSetBacklightSuppression)GetProcAddress(hDLL, "Set Backlight Suppression");


		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Splitter^  splitter1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::TrackBar^  trackBar3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TrackBar^  trackBar4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  button6;


	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(28, 566);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(324, 230);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(386, 567);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Contrast Settings";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(0, 0);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 874);
			this->splitter1->TabIndex = 2;
			this->splitter1->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(366, 784);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 3;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(343, 816);
			this->trackBar1->Maximum = 95;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(121, 45);
			this->trackBar1->TabIndex = 4;
			this->trackBar1->TickFrequency = 5;
			this->trackBar1->Value = 85;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(32, 13);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(61, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Grey Image";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(624, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(99, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Temperature Image";
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(369, 593);
			this->trackBar2->Maximum = 25;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(121, 45);
			this->trackBar2->TabIndex = 7;
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(369, 644);
			this->trackBar3->Maximum = 25;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(121, 45);
			this->trackBar3->TabIndex = 8;
			this->trackBar3->Scroll += gcnew System::EventHandler(this, &Form1::trackBar3_Scroll);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(661, 567);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(90, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Image Acquisition";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(661, 644);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(75, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Calibration File";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(929, 567);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(77, 13);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Frame Settings";
			this->label7->Click += gcnew System::EventHandler(this, &Form1::label7_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(661, 717);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(115, 13);
			this->label8->TabIndex = 12;
			this->label8->Text = L"Backlight Suppression:";
			this->label8->Click += gcnew System::EventHandler(this, &Form1::label8_Click);
			// 
			// trackBar4
			// 
			this->trackBar4->Location = System::Drawing::Point(664, 733);
			this->trackBar4->Maximum = 4095;
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(121, 45);
			this->trackBar4->TabIndex = 13;
			this->trackBar4->Scroll += gcnew System::EventHandler(this, &Form1::trackBar4_Scroll);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(664, 593);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 34);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Start Streaming";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(773, 593);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(94, 34);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Stop Streaming";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(664, 669);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(94, 34);
			this->button3->TabIndex = 16;
			this->button3->Text = L"Load";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(773, 669);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(94, 34);
			this->button4->TabIndex = 17;
			this->button4->Text = L"Get Info";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(932, 593);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(94, 34);
			this->button5->TabIndex = 18;
			this->button5->Text = L"Set Frame";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(529, 567);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(82, 13);
			this->label9->TabIndex = 19;
			this->label9->Text = L"Device Settings";
			this->label9->Click += gcnew System::EventHandler(this, &Form1::label9_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(519, 593);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(126, 34);
			this->button6->TabIndex = 20;
			this->button6->Text = L"Select and Init Device";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(519, 669);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(126, 34);
			this->button7->TabIndex = 23;
			this->button7->Text = L"Select Device";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(519, 717);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(126, 34);
			this->button8->TabIndex = 24;
			this->button8->Text = L"Close Device";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(697, 798);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(47, 17);
			this->radioButton1->TabIndex = 25;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Auto";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(696, 821);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(39, 17);
			this->radioButton2->TabIndex = 26;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Off";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(994, 752);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(132, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Temperature Clamp Mode:";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(810, 733);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(69, 13);
			this->label13->TabIndex = 29;
			this->label13->Text = L"Clamp Mode:";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(812, 784);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(81, 17);
			this->radioButton3->TabIndex = 31;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Max. Temp.";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(813, 761);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(78, 17);
			this->radioButton4->TabIndex = 30;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Min. Temp.";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(19, 29);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(107, 17);
			this->radioButton5->TabIndex = 32;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Min. -Min. -Temp.";
			this->radioButton5->UseVisualStyleBackColor = true;
			this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton5_CheckedChanged);
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(19, 53);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(110, 17);
			this->radioButton6->TabIndex = 33;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Min. -Max. -Temp.";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(19, 76);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(113, 17);
			this->radioButton7->TabIndex = 34;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"Max. -Max. -Temp.";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(929, 648);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(17, 13);
			this->label14->TabIndex = 35;
			this->label14->Text = L"X:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(1032, 647);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(17, 13);
			this->label15->TabIndex = 36;
			this->label15->Text = L"Y:";
			this->label15->Click += gcnew System::EventHandler(this, &Form1::label15_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(929, 676);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(38, 13);
			this->label16->TabIndex = 37;
			this->label16->Text = L"Width:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(1032, 675);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(41, 13);
			this->label17->TabIndex = 38;
			this->label17->Text = L"Height:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(979, 645);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(47, 20);
			this->textBox3->TabIndex = 39;
			this->textBox3->Text = L"75";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(979, 673);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(47, 20);
			this->textBox4->TabIndex = 40;
			this->textBox4->Text = L"640";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(1079, 644);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(47, 20);
			this->textBox5->TabIndex = 41;
			this->textBox5->Text = L"8";
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Form1::textBox5_TextChanged);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(1079, 673);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(47, 20);
			this->textBox6->TabIndex = 42;
			this->textBox6->Text = L"480";
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &Form1::textBox6_TextChanged);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(552, 812);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(126, 34);
			this->button9->TabIndex = 43;
			this->button9->Text = L"Close Device";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(671, 517);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(37, 13);
			this->label18->TabIndex = 44;
			this->label18->Text = L"Cursor";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(723, 517);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(17, 13);
			this->label19->TabIndex = 45;
			this->label19->Text = L"X:";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(764, 517);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(17, 13);
			this->label20->TabIndex = 46;
			this->label20->Text = L"Y:";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(746, 517);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(0, 13);
			this->label21->TabIndex = 47;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(787, 517);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(0, 13);
			this->label22->TabIndex = 48;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(824, 517);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(89, 13);
			this->label23->TabIndex = 49;
			this->label23->Text = L"Grey value [digit]:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(960, 517);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(89, 13);
			this->label24->TabIndex = 50;
			this->label24->Text = L"Temp. value [°C]:";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(913, 517);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(0, 13);
			this->label25->TabIndex = 51;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(1055, 517);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(0, 13);
			this->label26->TabIndex = 52;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox1->Location = System::Drawing::Point(32, 44);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(573, 426);
			this->pictureBox1->TabIndex = 53;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox2->Location = System::Drawing::Point(664, 29);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(658, 485);
			this->pictureBox2->TabIndex = 54;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox2_MouseMove);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox1->Controls->Add(this->radioButton6);
			this->groupBox1->Controls->Add(this->radioButton5);
			this->groupBox1->Controls->Add(this->radioButton7);
			this->groupBox1->Location = System::Drawing::Point(989, 768);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 100);
			this->groupBox1->TabIndex = 55;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(1068, 601);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(47, 20);
			this->textBox7->TabIndex = 56;
			this->textBox7->Text = L"10";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(1049, 569);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(62, 13);
			this->label27->TabIndex = 57;
			this->label27->Text = L"Frame Rate";
			this->label27->Click += gcnew System::EventHandler(this, &Form1::label27_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(496, 593);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 13);
			this->label10->TabIndex = 58;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(496, 648);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(0, 13);
			this->label11->TabIndex = 59;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(372, 784);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(71, 13);
			this->label28->TabIndex = 60;
			this->label28->Text = L"Denoise Filter";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(486, 817);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(0, 13);
			this->label29->TabIndex = 61;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(788, 733);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(0, 13);
			this->label30->TabIndex = 62;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(1100, 517);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(59, 13);
			this->label31->TabIndex = 63;
			this->label31->Text = L"High Byte: ";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(1202, 517);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(57, 13);
			this->label32->TabIndex = 64;
			this->label32->Text = L"Low Byte: ";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1430, 874);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton4);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->trackBar4);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Pyrocam...";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void eventLog1_EntryWritten(System::Object^  sender, System::Diagnostics::EntryWrittenEventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	
	}
	private: System::Void label15_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		
		if (pGetLibraryVersion && pInitDeviceGUI && pCloseDevice && pStartStreaming && pStopStreaming && pLoadCalibration && pGetCalibrationInfo
			&& pGetTemperaturImage && pGetVisibleImage && pGetFrameCounter && pGetFrame && pSetFrame)
		{
			error = pInitDeviceGUI();
			if (error == OK)
				textBox1->Text = "Device Selected, OK";
			else {
				textBox1->Text = "FAIL - Error Code: " + System::Convert::ToString(error);
			}
		}
	}

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

		

	//cv::imwrite

		}
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	streaming = true;
	int counter = 0;
	
	
	Width = Convert::ToInt32(textBox4->Text);
	Height = Convert::ToInt32(textBox6->Text);
	X = Convert::ToInt32(textBox3->Text);
	Y = Convert::ToInt32(textBox5->Text);
	//---- Get Frame ----
	textBox1->AppendText("Read Camera Frame ..." + Environment::NewLine);

	error = pSetFrame(Width, Height, X, Y);

	//error = pGetFrame(&Form1->Width, &Height, &X, &Y);
	

	textBox1->AppendText("Start Image Streaming ..." + Environment::NewLine);
	error = pStartStreaming();
	if (error == OK)
		textBox1->AppendText("Starting" + Environment::NewLine);
	else {
		textBox1->AppendText("FAIL - Error Code: " + Convert::ToString(error) + Environment::NewLine);
		textBox1->AppendText("Close PyroCam GigE Device" + Environment::NewLine);
		pCloseDevice();
		FreeLibrary(hDLL);
	}
	
	int ThresValue = trackBar4->Value;
	
	error = pSetBacklightSuppressionThreshold(trackBar4->Value);  // GetBacklightSuppressionThreshold(threValue);

	if (error == OK)
		textBox1->AppendText("Backlight Suppression Threshold Value = " + trackBar4->Value.ToString());
	else {
		textBox1->AppendText("FAIL - Error Code: " + System::Convert::ToString(error));
	}

	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &Form1::image_Capture));
	newThread->Start();


}

		

void Form1::image_Capture() {
	int counter = 0;
	while (streaming == true) {

		std::wstring count = std::to_wstring(counter);
		unsigned char *pTemperatureImage = new unsigned char[Width * Height * 2];
		unsigned char *pGreyImage = new unsigned char[Width * Height * 2];

		unsigned short *pImageData = pGetTemperaturImage();
		if (pImageData) {
			{
				memcpy(pTemperatureImage, pImageData, (Width * Height * sizeof(unsigned short)));
				memcpy(pGreyImage, pImageData, (Width * Height * sizeof(unsigned short)));

				std::wstring FilePathTemp = L"C:\\MyFolder\\tempimg";
				std::wstring FilePathGrey = L"C:\\MyFolder\\greyimg";

				std::wstring FileType = L".bmp";

				std::wstring FileNameTemp = FilePathTemp.append(count).append(FileType);
				std::wstring FileNameGrey = FilePathGrey.append(count).append(FileType);

				SaveBitmapToFile((BYTE*)pTemperatureImage, Width, Height, 16, 0, FileNameTemp.c_str());
				SaveBitmapToFile((BYTE*)pGreyImage, Width, Height, 16, 0, FileNameGrey.c_str());
				delete[] pGreyImage;
				delete[] pTemperatureImage;
				counter++;
				Sleep(200);

			}

		}

	}
	pCloseDevice();
	FreeLibrary(hDLL);
}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog;
	fileDialog->Filter = "dat files|*.dat";
	fileDialog->Title = "Select Pyrocam File";

	

	msclr::interop::marshal_context oMC;
	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		error = pLoadCalibration(oMC.marshal_as<const char*>(fileDialog->FileName));
	}
	
	textBox1->AppendText("Calibration File: " + fileDialog->FileName);
	
}
private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	streaming = false;
	pCloseDevice();
	textBox1->AppendText("Stopped Streaming");
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label27_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	pCloseDevice();
}
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void radioButton5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}




private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	label10->Text = trackBar2->Value.ToString();
	label11->Text = trackBar3->Value.ToString();
	label29->Text = trackBar1->Value.ToString();
	label30->Text = trackBar4->Value.ToString();

	pictureBox2->Image = Image::FromFile("C:\\MyFolder\\tempimg1.bmp");

	ifstream input(L"C:\\MyFolder\\tempimg1.bmp", ios::binary);
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
	
	this->LengthOfArray = buffer.size();
	this->bildbyte = new char[this->LengthOfArray];
	std::copy(buffer.begin(), buffer.end(), this->bildbyte);

}

private: System::Void trackBar3_Scroll(System::Object^  sender, System::EventArgs^  e) {
	label11->Text = trackBar3->Value.ToString();
}

private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
	label10->Text = trackBar2->Value.ToString();
}

private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	label29->Text = trackBar1->Value.ToString();
}
private: System::Void trackBar4_Scroll(System::Object^  sender, System::EventArgs^  e) {
	label30->Text = trackBar4->Value.ToString();
}


private: System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int mouseX = e->X;
	int mouseY = e->Y;

	if (pictureBox2->Image != nullptr) {

		unsigned char lowbyte = bildbyte[54 + mouseX * mouseY * 2 + mouseX * 2];
		unsigned char highbyte = bildbyte[54 + mouseX * mouseY * 2 + mouseX * 2 + 1];

		int shortemp = lowbyte + 256 * highbyte;
		
		String^ temp = System::Convert::ToString(shortemp);
		label31->Text = "High Byte: " + System::Convert::ToString(highbyte);
		label32->Text = "Low Byte: " + System::Convert::ToString(lowbyte);

		/*String^ position = "X: " + System::Convert::ToString(mouseX) + " Y: " + System::Convert::ToString(mouseY) + " Temperatur: " + temp + "°C" + " Lowbyte = "
			+ System::Convert::ToString(lowbyte) + " Highbyte = " + System::Convert::ToString(highbyte);*/
		
		
		label24->Text = "Temperaturwert [°C]: " + temp;
		label19->Text = "X: " + mouseX.ToString();
		label20->Text = "Y: " + mouseY.ToString();
		
	}
	else {
		label24->Text = "Temperaturwert [°C]: ";
	}

}
};
}