#pragma once


#include <math.h>

namespace UIRS_2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

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
	private: System::Windows::Forms::VScrollBar^  vScrollBar1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;












	protected: 

	private:
	     /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
                float angle;
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		

		void InitializeComponent(void)
		{		
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->Location = System::Drawing::Point(479, 9);
			this->vScrollBar1->Maximum = 10000;
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(24, 526);
			this->vScrollBar1->TabIndex = 0;
			this->vScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::vScrollBar1_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(323, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(114, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Высота            м";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 23);
			this->label2->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(379, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(16, 17);
			this->label3->TabIndex = 2;
			this->label3->Text = L"0";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(512, 550);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->vScrollBar1);
			this->DoubleBuffered = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Высотометр";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::OnPaint);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void OnPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
			 {
				 // подвинуть начало отсчета в центр окна и направить ось Y вверх
                 Matrix ^myMatrix = gcnew Matrix(1, 0, 0, -1, 256, 256);
                 e->Graphics->Transform = myMatrix;
				 e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
				 //последовательная реализация функций
				 Altimetr(sender,e);
				 Divices(sender,e);
				 Arrows(sender,e);
			 }
	private: void Altimetr(System::Object ^ sender,  
                    System::Windows::Forms::PaintEventArgs ^ e)
             {
				 int i=0;
				 double x,y;
				 Graphics ^ g = e->Graphics;
				 //реализация инструментов
				 Pen ^whitePen= gcnew Pen(Color::White, 4);
				 Pen ^blackPen= gcnew Pen(Color::Black,71);
				 Pen ^whitePen2= gcnew Pen(Color::White,3);
				 SolidBrush ^blackBrush = gcnew SolidBrush(Color::Black);
				 SolidBrush ^whiteBrush = gcnew SolidBrush(Color::White);
				 g->DrawEllipse(whitePen,-152,-152,304,304);//Большой круг
				 g->FillEllipse(blackBrush,-150,-150,300,300);//Заполненный чёрный круг
                 //рисуем циферблат
                 System::Drawing::Font ^font1 = gcnew System::Drawing::Font("Times New Roman", 24, FontStyle::Bold,  GraphicsUnit::Pixel);
				 for(i=0;i<=40;i++)
				 {
					 if(i<10)//цифры и большие риски
					{	
						g->ScaleTransform(1,-1);
						x=-10+110*sin(i*36/57.3);
						y=-10-110*cos(i*36/57.3);
						g->DrawString((i).ToString(),font1,whiteBrush,x,y);
				        g->ScaleTransform(1,-1);				
						g->RotateTransform(i*36);
						g->DrawLine(whitePen, 0,150,0,130);
						g->RotateTransform(-i*36);
						
					}
					if (i%2!=0)//риски среднее и малые
					{
						g->RotateTransform(i*18);
						g->DrawLine(whitePen, 0,150,0,135);
						g->RotateTransform(-i*18);
						g->RotateTransform(i*9);
						g->DrawLine(whitePen2, 0,150,0,140);
						g->RotateTransform(-i*9);					
					}
				 }
			 }
	private: void Arrows(System::Object ^ sender,  
                    System::Windows::Forms::PaintEventArgs ^ e)
			 {				
				 Graphics ^ g = e->Graphics;
				 //реализация инструментов 
				 Pen ^darkgrayPen= gcnew Pen(Color::DarkGray,4);
				 Pen ^whitePen= gcnew Pen(Color::White,4);
				 SolidBrush ^whiteBrush = gcnew SolidBrush(Color::White);				 
				 //крепление
				 g->DrawEllipse(whitePen,-10,-10,20,20);				 
				 g->FillEllipse(whiteBrush,-4,-4,8,8);
				 array <Point>^ myPointArray = { Point(0, 0),Point(-10, 38),Point(0, 76),Point(10, 38)};
                 // малая стрелка
				 g->RotateTransform(-angle/10);
				 g->FillPolygon(whiteBrush,myPointArray);
				 g->RotateTransform(angle/10);				                  
				 //длинная стрелка
				 g->RotateTransform(-angle);
				 g->DrawLine(darkgrayPen, 0,0,0,70);
				 g->DrawLine(whitePen, 0,70,0,130);
				 g->RotateTransform(angle);
			 }
		 
   
    private: void Divices(System::Object ^ sender,  
                    System::Windows::Forms::PaintEventArgs ^ e)
			 {
				 float x1=-56;
                 float y1=0;				 
				 float t;
				 Graphics ^ g = e->Graphics;
				 //реализация инструментов
				 Pen ^whitePen= gcnew Pen(Color::White, 2);
				 SolidBrush ^whiteBrush = gcnew SolidBrush(Color::White);
				 System::Drawing::Font ^font1 = gcnew System::Drawing::Font("Times New Roman", 18, FontStyle::Bold,  GraphicsUnit::Pixel);
				 //квадрат
				 Rectangle Rect = Rectangle(-25,20,50,20);
				//цифровой показатель тысяч метров
				 g->DrawRectangle(whitePen,Rect);
                 t=angle/360;
				 g->ScaleTransform(1,-1);
				 g->DrawString("Высота   м",font1,whiteBrush,-50,-70);
				 g->DrawString((t).ToString(),font1,whiteBrush,-25,-40);
				 g->ScaleTransform(1,-1);
				 
				
			 }
	private: System::Void vScrollBar1_Scroll(System::Object^  sender, 
				             System::Windows::Forms::ScrollEventArgs^  e) 
			 {
				 float H= vScrollBar1->Value;
	             label3->Text=H.ToString();	            
			     angle = 0.36*H;
				 this->Invalidate();
			 }

 private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		  }
};
}