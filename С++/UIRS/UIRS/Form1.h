#pragma once

#include <math.h>
namespace UIRS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::Button^  button23;
	private: System::Windows::Forms::Button^  button24;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

	protected:
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::OrangeRed;
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(12, 89);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"c/ce";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->textBox1->Size = System::Drawing::Size(362, 46);
			this->textBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(110, 89);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"off";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::White;
			this->button3->ForeColor = System::Drawing::Color::Black;
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button3.Image")));
			this->button3->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button3->Location = System::Drawing::Point(210, 89);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 3;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::White;
			this->button4->ForeColor = System::Drawing::Color::Black;
			this->button4->Location = System::Drawing::Point(299, 89);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 4;
			this->button4->Text = L"%";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::White;
			this->button5->ForeColor = System::Drawing::Color::Black;
			this->button5->Location = System::Drawing::Point(12, 130);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Mrc";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::White;
			this->button6->ForeColor = System::Drawing::Color::Black;
			this->button6->Location = System::Drawing::Point(110, 130);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 7;
			this->button6->Text = L"M-";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::White;
			this->button7->ForeColor = System::Drawing::Color::Black;
			this->button7->Location = System::Drawing::Point(210, 130);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"M+";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::White;
			this->button8->ForeColor = System::Drawing::Color::Black;
			this->button8->Location = System::Drawing::Point(299, 130);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 5;
			this->button8->Text = L"/";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::White;
			this->button9->ForeColor = System::Drawing::Color::Black;
			this->button9->Location = System::Drawing::Point(12, 173);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 12;
			this->button9->Text = L"7";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::White;
			this->button10->ForeColor = System::Drawing::Color::Black;
			this->button10->Location = System::Drawing::Point(110, 173);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 23);
			this->button10->TabIndex = 11;
			this->button10->Text = L"8";
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::White;
			this->button11->ForeColor = System::Drawing::Color::Black;
			this->button11->Location = System::Drawing::Point(210, 173);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 10;
			this->button11->Text = L"9";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::White;
			this->button12->ForeColor = System::Drawing::Color::Black;
			this->button12->Location = System::Drawing::Point(299, 173);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(75, 23);
			this->button12->TabIndex = 9;
			this->button12->Text = L"*";
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::Color::White;
			this->button13->ForeColor = System::Drawing::Color::Black;
			this->button13->Location = System::Drawing::Point(12, 217);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 23);
			this->button13->TabIndex = 16;
			this->button13->Text = L"4";
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// button14
			// 
			this->button14->BackColor = System::Drawing::Color::White;
			this->button14->ForeColor = System::Drawing::Color::Black;
			this->button14->Location = System::Drawing::Point(110, 217);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 15;
			this->button14->Text = L"5";
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button15
			// 
			this->button15->BackColor = System::Drawing::Color::White;
			this->button15->ForeColor = System::Drawing::Color::Black;
			this->button15->Location = System::Drawing::Point(210, 217);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(75, 23);
			this->button15->TabIndex = 14;
			this->button15->Text = L"6";
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
			// 
			// button16
			// 
			this->button16->BackColor = System::Drawing::Color::White;
			this->button16->ForeColor = System::Drawing::Color::Black;
			this->button16->Location = System::Drawing::Point(299, 217);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(75, 23);
			this->button16->TabIndex = 13;
			this->button16->Text = L"-";
			this->button16->UseVisualStyleBackColor = false;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
			// 
			// button17
			// 
			this->button17->BackColor = System::Drawing::Color::White;
			this->button17->ForeColor = System::Drawing::Color::Black;
			this->button17->Location = System::Drawing::Point(12, 257);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(75, 23);
			this->button17->TabIndex = 24;
			this->button17->Text = L"1";
			this->button17->UseVisualStyleBackColor = false;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
			// 
			// button18
			// 
			this->button18->BackColor = System::Drawing::Color::White;
			this->button18->ForeColor = System::Drawing::Color::Black;
			this->button18->Location = System::Drawing::Point(110, 257);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(75, 23);
			this->button18->TabIndex = 23;
			this->button18->Text = L"2";
			this->button18->UseVisualStyleBackColor = false;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::button18_Click);
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::Color::White;
			this->button19->ForeColor = System::Drawing::Color::Black;
			this->button19->Location = System::Drawing::Point(210, 257);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(75, 23);
			this->button19->TabIndex = 22;
			this->button19->Text = L"3";
			this->button19->UseVisualStyleBackColor = false;
			this->button19->Click += gcnew System::EventHandler(this, &Form1::button19_Click);
			// 
			// button20
			// 
			this->button20->BackColor = System::Drawing::Color::White;
			this->button20->ForeColor = System::Drawing::Color::Black;
			this->button20->Location = System::Drawing::Point(299, 257);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(75, 67);
			this->button20->TabIndex = 21;
			this->button20->Text = L"+";
			this->button20->UseVisualStyleBackColor = false;
			this->button20->Click += gcnew System::EventHandler(this, &Form1::button20_Click);
			// 
			// button22
			// 
			this->button22->BackColor = System::Drawing::Color::White;
			this->button22->ForeColor = System::Drawing::Color::Black;
			this->button22->Location = System::Drawing::Point(12, 301);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(75, 23);
			this->button22->TabIndex = 19;
			this->button22->Text = L"0";
			this->button22->UseVisualStyleBackColor = false;
			this->button22->Click += gcnew System::EventHandler(this, &Form1::button22_Click);
			// 
			// button23
			// 
			this->button23->BackColor = System::Drawing::Color::White;
			this->button23->ForeColor = System::Drawing::Color::Black;
			this->button23->Location = System::Drawing::Point(110, 301);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(75, 23);
			this->button23->TabIndex = 18;
			this->button23->Text = L",";
			this->button23->UseVisualStyleBackColor = false;
			this->button23->Click += gcnew System::EventHandler(this, &Form1::button23_Click);
			// 
			// button24
			// 
			this->button24->BackColor = System::Drawing::Color::White;
			this->button24->ForeColor = System::Drawing::Color::Black;
			this->button24->Location = System::Drawing::Point(210, 301);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(75, 23);
			this->button24->TabIndex = 17;
			this->button24->Text = L"=";
			this->button24->UseVisualStyleBackColor = false;
			this->button24->Click += gcnew System::EventHandler(this, &Form1::button24_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(386, 345);
			this->Controls->Add(this->button17);
			this->Controls->Add(this->button18);
			this->Controls->Add(this->button19);
			this->Controls->Add(this->button20);
			this->Controls->Add(this->button22);
			this->Controls->Add(this->button23);
			this->Controls->Add(this->button24);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button15);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
private:
#pragma endregion
static bool ^b=false;
static bool ^b1=true;
static double M=0; 
double p;
char c;

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->textBox1->Text=L"0";
				 this->button23->Enabled=true;
				 *b=true;
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->textBox1->Clear();
				 this->button23->Enabled=true;
				 *b=false;
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 double a=Convert::ToDouble(this->textBox1->Text);
		         a=sqrt(a);
			     this->textBox1->Text=a.ToString();
	 	         *b1=false;
			 }
		 }
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 p=Convert::ToDouble(this->textBox1->Text);
				 c='+';
				 *b1=false;
			 }
		 }
private: System::Void button23_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(*b==true)
			 {
			 String ^s=",";
			 this->textBox1->AppendText(s);
			 this->button23->Enabled=false;
             }
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
		 { 
			if(*b==true)
			{
				double a=Convert::ToDouble(this->textBox1->Text);
			    a=p*a/100;
			    this->textBox1->Text=a.ToString();
			    *b1=false;
			}
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 this->textBox1->Text=M.ToString();
				 *b1=false;
			 }
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 M=0;
				 *b1=false;
			 }
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				  M+=Convert::ToDouble(this->textBox1->Text);
				 *b1=false;
			 }
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 p=Convert::ToDouble(this->textBox1->Text);
				 c='/';
				 *b1=false;
			 }
		 }
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  if (*b==true)
			 {
				 p=Convert::ToDouble(this->textBox1->Text);
				 c='*';
				 *b1=false;
			 }
		 }
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  if (*b==true)
			 {
				 p=Convert::ToDouble(this->textBox1->Text);
				 c='-';
				 *b1=false;
			 }
		 }
private: System::Void button24_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(*b==true)
			 {
				 double a=Convert::ToDouble(this->textBox1->Text);
			     switch (c)
			     {
			     case '+':
					 {
						 a=a+p;
					     break;
					 }
				 case '-':
				     {
					     a=p-a;
					     break;
				     }
			     case '*':
				     {
					     a=p*a;
					     break;
				     }
			     case '/':
				     {
					     a=p/a;
					     break;
				     }
			     default:{}
				 }			 
			 this->textBox1->Text=a.ToString();
			 *b1=false;
			 }
		 }
 private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="0";
			     if (this->textBox1->Text!="0") 
			     {
				     this->textBox1->AppendText(s);
			     }
			     if(*b1==false)
			     { 
				     this->textBox1->Text=L"0";
					 this->button23->Enabled=true;
			     }
		     }
		  }			
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="1";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"1";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="2";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"2";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="3";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"3";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 if (*b==true)
			 {
				 String ^s="4";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"4";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="5";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"5";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 if (*b==true)
			 {
				 String ^s="6";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"6";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="7";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"7";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (*b==true)
			 {
				 String ^s="8";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"8";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 if (*b==true)
			 {
				 String ^s="9";
			     if ((this->textBox1->Text==L"0") |(*b1==false)) 
			     {
				     this->textBox1->Text=L"9";
					 this->button23->Enabled=true;
					 *b1=true;
			     }
			     else
			     {
				     this->textBox1->AppendText(s);
			     }
			 }
		  }

};
}

