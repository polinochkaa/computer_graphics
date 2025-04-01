#pragma once

namespace Akishina {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	float mylines[] = {
		//голова

		// шляпа верхняя часть
		3.0f, 13.5f, 3.5f, 14.5f,
		3.5f, 14.5f, 5.5f, 14.5f,
		5.5f, 14.5f, 6.0f, 13.5f,
		// шляпа нижняя часть
		2.0f, 13.0f, 2.0f, 13.5f,
		2.0f, 13.5f, 7.0f, 13.5f,
		7.0f, 13.0f, 7.0f, 13.5f,
		2.0f, 13.0f, 7.0f, 13.0f,
		//волосы левая часть
		2.0f, 13.0f, 1.0f, 12.0f,
		1.0f, 12.0f, 1.5f, 12.0f,
		1.5f, 12.0f, 0.5f, 11.0f,
		0.5f, 11.0f, 1.5f, 11.0f,
		1.5f, 11.0f, 1.0f, 10.0f,
		1.0f, 10.0f, 2.0f, 10.5f,
		2.0f, 10.5f, 2.0f, 9.5f,
		2.0f, 9.5f, 2.5f, 10.0f,
		//волосы правая часть
		7.0f, 13.0f, 8.0f, 12.0f,
		8.0f, 12.0f, 7.5f, 12.0f,
		7.5f, 12.0f, 8.5f, 11.0f,
		8.5f, 11.0f, 7.5f, 11.0f,
		7.5f, 11.0f, 8.0f, 10.0f,
		8.0f, 10.0f, 7.0f, 10.5f,
		7.0f, 10.5f, 7.0f, 9.5f,
		7.0f, 9.5f, 6.5f, 10.0f,
		//голова
		2.5f, 13.0f, 2.5f, 10.0f,
		6.5f, 13.0f, 6.5f, 10.0f,
		2.5f, 10.0f, 4.0f, 9.0f,
		4.0f, 9.0f, 5.0f, 9.0f,
		5.0f, 9.0f, 6.5f, 10.0f,
		//глаз левый
		3.5f, 13.0f, 4.0f, 12.5f,
		4.0f, 12.5f, 4.0f, 11.5f,
		4.0f, 11.5f, 3.0f, 11.5f,
		3.0f, 11.5f, 3.0f, 12.5f,
		3.0f, 12.5f, 3.5f, 13.0f,

		3.0f, 11.5f, 3.5f, 12.5f,
		3.5f, 12.5f, 4.0f, 11.5f,

		3.25f, 11.5f, 3.5f, 12.0f,
		3.5f, 12.0f, 3.75f, 11.5f,
		//глаз правый
		5.5f, 13.0f, 6.0f, 12.5f,
		6.0f, 12.5f, 6.0f, 11.5f,
		6.0f, 11.5f, 5.0f, 11.5f,
		5.0f, 11.5f, 5.0f, 12.5f,
		5.0f, 12.5f, 5.5f, 13.0f,

		5.0f, 11.5f, 5.5f, 12.5f,
		5.5f, 12.5f, 6.0f, 11.5f,

		5.25f, 11.5f, 5.5f, 12.0f,
		5.5f, 12.0f, 5.75f, 11.5f,
		//нос
		4.0f, 11.5f, 5.0f, 11.5f,
		5.0f, 11.5f, 5.5f, 11.25f,
		5.5f, 11.25f, 5.5f, 10.75f,
		4.0f, 11.5f, 3.5f, 11.25f,
		3.5f, 11.25f, 3.5f, 10.75f,
		//рот
		3.0f, 11.0f, 4.0f, 10.5f,
		4.0f, 10.5f, 5.0f, 10.5f,
		5.0f, 10.5f, 6.0f, 11.0f,
		6.0f, 11.0f, 6.0f, 10.0f,
		6.0f, 10.0f, 4.5f, 9.5f,
		4.5f, 9.5f, 3.0f, 10.0f,
		3.0f, 10.0f, 3.0f, 11.0f,

		3.5f, 10.5f, 4.0f, 10.0f,
		4.0f, 10.0f, 5.0f, 10.0f,
		5.0f, 10.0f, 5.5f, 10.5f,

		//тело
		
		//контур
		4.0f, 9.0f, 2.5f, 8.5f, 
		2.5f, 8.5f, 2.5f, 4.5f,
		1.0f, 4.5f, 8.0f, 4.5f,
		4.5f, 0.5f, 4.5f, 4.5f,
		5.0f, 9.0f, 6.5f, 8.5f,
		6.5f, 8.5f, 6.5f, 4.5f,
		//левая нога
		2.5f, 4.5f, 3.0f, 1.5f,

		3.5f, 4.0f, 4.0f, 3.5f, 
		4.0f, 3.5f, 3.5f, 3.0f,
		3.5f, 3.0f, 3.0f, 3.5f,
		3.0f, 3.5f, 3.5f, 4.0f,

		3.0f, 1.5f, 3.5f, 2.0f, 
		3.5f, 2.0f, 4.0f, 1.5f,
		//правая нога
		6.5f, 4.5f, 6.0f, 1.5f,

		6.0f, 4.5f, 5.5f, 4.0f,
		5.5f, 4.0f, 5.0f, 4.5f,

		5.5f, 3.0f, 6.0f, 2.5f,
		6.0f, 2.5f, 5.5f, 2.0f,
		5.5f, 2.0f, 5.0f, 2.5f,
		5.0f, 2.5f, 5.5f, 3.0f,
		//ступни
		1.0f, 0.5f, 2.5f, 1.5f, 
		2.5f, 1.5f, 7.0f, 1.5f,
		7.0f, 1.5f, 8.5f, 0.5f,
		1.0f, 0.5f, 8.5f, 0.5f,

		//левая рука
		2.5f, 8.5f, 1.0f, 4.5f,
		1.0f, 4.5f, 2.5f, 4.5f,
		1.0f, 4.5f, 1.0f, 3.5f,
		1.0f, 3.5f, 2.0f, 3.5f,
		2.0f, 3.5f, 2.0f, 4.0f,
		2.0f, 4.0f, 2.5f, 4.0f,
		2.5f, 4.0f, 2.5f, 4.5f,

		1.25f, 5.0f, 1.5f, 5.0f,
		1.5f, 5.0f, 1.5f, 5.5f,
		1.5f, 5.5f, 2.0f, 5.5f,
		2.0f, 5.5f, 2.0f, 5.0f,
		2.0f, 5.0f, 2.5f, 5.0f,
		//правая рука
		6.5f, 8.5f, 8.0f, 4.5f,
		8.0f, 4.5f, 6.5f, 4.5f,
		8.0f, 4.5f, 8.0f, 3.5f,
		8.0f, 3.5f, 7.0f, 3.5f,
		7.0f, 3.5f, 7.0f, 4.0f,
		7.0f, 4.0f, 6.5f, 4.0f,
		6.5f, 4.0f, 6.5f, 4.5f,

		7.75f, 5.0f, 7.5f, 5.0f,
		7.5f, 5.0f, 7.5f, 5.5f,
		7.5f, 5.5f, 7.0f, 5.5f,
		7.0f, 5.5f, 7.0f, 5.0f,
		7.0f, 5.0f, 6.5f, 5.0f,
		//галстук верхняя часть
		4.0f, 9.0f, 3.5f, 8.5f,
		3.5f, 8.5f, 4.0f, 8.0f,
		4.0f, 8.0f, 5.0f, 8.0f,
		5.0f, 8.0f, 5.5f, 8.5f,
		5.5f, 8.5f, 5.0f, 9.0f,

		4.5f, 9.0f, 4.0f, 8.5f,
		4.0f, 8.5f, 4.5f, 8.0f, 
		4.5f, 8.0f, 5.0f, 8.5f,
		5.0f, 8.5f, 4.5f, 9.0f,
		//галстук нижняя часть
		4.0f, 8.0f, 3.5f, 6.0f,
		3.5f, 6.0f, 4.5f, 5.0f,
		4.5f, 5.0f, 5.5f, 6.0f,
		5.5f, 6.0f, 5.0f, 8.0f,

		//кресты внутри
		2.5f, 7.5f, 3.0f, 7.5f,
		3.0f, 7.5f, 3.0f, 8.0f,
		3.0f, 8.0f, 3.5f, 8.0f,
		3.5f, 8.0f, 3.5f, 7.5f,
		3.5f, 7.5f, 3.825f, 7.5f,

		2.5f, 7.0f, 3.0f, 7.0f,
		3.0f, 7.0f, 3.0f, 6.5f,
		3.0f, 6.5f, 3.5f, 6.5f,
		3.5f, 6.5f, 3.5f, 7.0f,
		3.5f, 7.0f, 3.75f, 7.0f,

		5.5f, 6.0f, 5.5f, 6.5f,
		5.5f, 6.5f, 6.0f, 6.5f,
		6.0f, 6.5f, 6.0f, 6.0f,
		6.0f, 6.0f, 6.5f, 6.0f,

		5.0f, 5.5f, 5.5f, 5.5f,
		5.5f, 5.5f, 5.5f, 5.0f,
		5.5f, 5.0f, 6.0f, 5.0f,
		6.0f, 5.0f, 6.0f, 5.5f,
		6.0f, 5.5f, 6.5f, 5.5f,
	};

	float lines[] = {
		// голова
		0.5f,3.f,1.f,4.5f, // от левой щеки вверх до уха
		1.f,4.5f,0.5f,6.f, // левое ухо слева снизу вверх
		0.5f,6.f,0.5f, 7.5f, // левое ухо слева
		0.5f, 7.5f,1.f,8.f, // левое ухо верх слева
		1.f,8.f,1.5f,8.f, // левое ухо верх середина
		1.5f,8.f,2.f,7.5f, // левое ухо верх справа
		2.f,7.5f,1.5f, 6.f, // левое ухо справа сверху вниз
		1.5f, 6.f,1.5f,4.5f, // левое ухо справа до макушки
		1.5f,4.5f,3.f,4.5f, // макушка
		3.f,4.5f,3.f,6.f, // правое ухо слева снизу вверх
		3.f,6.f,2.5f,7.5f, // правое ухо слева
		2.5f,7.5f,3.f,8.f, // правое ухо верх слева
		3.f,8.f,3.5f,8.f, // правое ухо верх середина
		3.5f,8.f,4.f,7.5f, // правое ухо верх справа
		4.f,7.5f,4.f,6.f, // правое ухо сверху вниз
		4.f,6.f,3.5f,4.5f, // правое ухо справа
		3.5f,4.5f,4.f,3.f, // от правого уха вниз до щеки
		4.f,3.f,3.5f,1.5f, // правая скула
		3.5f,1.5f,2.5f,1.f, // подбородок справа
		2.5f,1.f,2.f,1.f, // подбородок снизу
		2.f,1.f,1.f,1.5f, // подбородок слева
		1.f,1.5f,0.5f,3.f, // левая скула
		// туловище
		4.f,3.f,5.5f,3.5f, // спина от головы вправо
		5.5f,3.5f,7.f,3.5f, // спина верх
		7.f,3.5f,7.5f,2.5f, // спина сверху до хвоста
		7.5f,2.5f,8.f,2.5f, // хвост сверху
		8.f,2.5f,8.f,2.f, // хвост справа
		8.f,2.f,7.5f,2.f, // хвост низ справа налево
		7.5f,2.f,7.5f,0.5f, // задняя нога справа сверху вниз
		7.5f,0.5f,6.5f,0.5f, // задняя нога низ
		6.5f,0.5f,6.5f,1.f, // задняя нога слева
		6.5f,1.f,6.f,1.f, // между задних ног
		6.f,1.f,6.f,0.5f, // левая задняя нога справа
		6.f,0.5f,5.f,0.5f, // левая задняя нога низ
		5.f,0.5f,5.f,1.f, // левая задняя нога слева
		5.f,1.f,4.f,1.f, // между задними и передними ногами
		4.f,1.f,4.f,0.5f, // правая передняя нога справа
		4.f,0.5f,3.f,0.5f, // правая передняя нога низ
		3.f,0.5f,3.f,1.f, // правая передняя нога слева
		3.f,1.f,2.5f,1.f, // между передних ног
		2.5f,1.f,2.5f,0.5f, // передняя нога справа
		2.5f,0.5f,1.5f,0.5f, // передняя нога низ
		1.5f,0.5f,1.5f,1.25f, // передняя нога слева
		// левый глаз
		1.5f,3.5f,1.5f,3.f, // левый глаз слева сверху вниз
		1.5f,3.f,2.f,3.f, // левый глаз низ
		2.f, 3.f,2.f,3.5f, // левый глаз справа
		2.f,3.5f,1.5f,3.5f, // левый глаз верх
		// правый глаз
		2.5f,3.5f,2.5f,3.f, // правый глаз слева
		2.5f,3.f,3.f, 3.f, // правый глаз снизу
		3.f,3.f,3.f,3.5f, // правый глаз справа
		3.f,3.5f,2.5f,3.5f, // правый глаз сверху
		// ушные раковины
		1.f,5.5f,1.f,7.f, // левая ушная раковина
		3.5f,5.5f,3.5f,7.f, // правая ушная раковина
		// нос
		2.f,2.5f,2.5f,2.5f, // нос сверху
		2.5f,2.5f,2.25f,2.f, // нос справа
		2.25f,2.f,2.f,2.5f // нос слева
	};

	unsigned int arrayLength = sizeof(lines) / sizeof(float); //рамзер массива точек рисунка
	unsigned int myarrayLength = sizeof(mylines) / sizeof(float); //рамзер массива точек моего рисунка
	float Vx = 8.5f; // размер рисунка по горизонтали
	float Vy = 8.5f; // размер рисунка по вертикали
	float myVx = 9.0f; // размер моего рисунка по горизонтали
	float myVy = 15.0f; // размер моего рисунка по вертикали

	float aspectFig = Vx / Vy; // соотношение сторон рисунка
	float myaspectFig = myVx / myVy; // соотношение сторон моего рисунка
	

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(286, 241);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio; // значение - сохранять ли соотношение сторон рисунка?
	private: bool MyPicture; 
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		System::Drawing::Graphics^ g = e->Graphics;
		Pen^ blackPen = gcnew Pen(Color::Black, 3);

		float Wx = ClientRectangle.Width;
		float Wy = ClientRectangle.Height;
		float aspectForm = Wx / Wy;

		float Sx, Sy, mySx, mySy;
		//вложенные if в которых проверяются условия на масштаб и рисунок
		if (MyPicture) {
			if (keepAspectRatio) {
				mySx = mySy = aspectFig < aspectForm ? Wy / myVy : Wx / myVx;
			}
			else {
				mySx = Wx / myVx;
				mySy = Wy / myVy;
			}
			float Ty = mySy * myVy;
			for (int i = 0; i < myarrayLength; i += 4) {
				g->DrawLine(blackPen, mySx * mylines[i], Ty - mySy * mylines[i + 1], mySx * mylines[i + 2], Ty - mySy * mylines[i + 3]);
			}
		}
		else {
			if (keepAspectRatio) {
				Sx = Sy = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
			}
			else {
				Sx = Wx / Vx;
				Sy = Wy / Vy;
			}
			float Ty = Sy * Vy;
			for (int i = 0; i < arrayLength; i += 4) {
				g->DrawLine(blackPen, Sx * lines[i], Ty - Sy * lines[i + 1], Sx * lines[i + 2], Ty - Sy * lines[i + 3]);
			}
		}

		
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		keepAspectRatio = true; // начальное значение: сохранять соотношение сторон рисунка
		MyPicture = false;//условие рисования моего рисунка
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::M://клавиша переключения масштаба
			keepAspectRatio = !keepAspectRatio;
			break;
		case Keys::N://клавиша переключения рисунков
			MyPicture = !MyPicture;
			break;
		default:
			break;
		}
		Refresh();
	}
	};
}
