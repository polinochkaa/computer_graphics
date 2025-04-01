#pragma once

namespace Akishina {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	float mylines[] = {
		//������

		// ����� ������� �����
		3.0f, 13.5f, 3.5f, 14.5f,
		3.5f, 14.5f, 5.5f, 14.5f,
		5.5f, 14.5f, 6.0f, 13.5f,
		// ����� ������ �����
		2.0f, 13.0f, 2.0f, 13.5f,
		2.0f, 13.5f, 7.0f, 13.5f,
		7.0f, 13.0f, 7.0f, 13.5f,
		2.0f, 13.0f, 7.0f, 13.0f,
		//������ ����� �����
		2.0f, 13.0f, 1.0f, 12.0f,
		1.0f, 12.0f, 1.5f, 12.0f,
		1.5f, 12.0f, 0.5f, 11.0f,
		0.5f, 11.0f, 1.5f, 11.0f,
		1.5f, 11.0f, 1.0f, 10.0f,
		1.0f, 10.0f, 2.0f, 10.5f,
		2.0f, 10.5f, 2.0f, 9.5f,
		2.0f, 9.5f, 2.5f, 10.0f,
		//������ ������ �����
		7.0f, 13.0f, 8.0f, 12.0f,
		8.0f, 12.0f, 7.5f, 12.0f,
		7.5f, 12.0f, 8.5f, 11.0f,
		8.5f, 11.0f, 7.5f, 11.0f,
		7.5f, 11.0f, 8.0f, 10.0f,
		8.0f, 10.0f, 7.0f, 10.5f,
		7.0f, 10.5f, 7.0f, 9.5f,
		7.0f, 9.5f, 6.5f, 10.0f,
		//������
		2.5f, 13.0f, 2.5f, 10.0f,
		6.5f, 13.0f, 6.5f, 10.0f,
		2.5f, 10.0f, 4.0f, 9.0f,
		4.0f, 9.0f, 5.0f, 9.0f,
		5.0f, 9.0f, 6.5f, 10.0f,
		//���� �����
		3.5f, 13.0f, 4.0f, 12.5f,
		4.0f, 12.5f, 4.0f, 11.5f,
		4.0f, 11.5f, 3.0f, 11.5f,
		3.0f, 11.5f, 3.0f, 12.5f,
		3.0f, 12.5f, 3.5f, 13.0f,

		3.0f, 11.5f, 3.5f, 12.5f,
		3.5f, 12.5f, 4.0f, 11.5f,

		3.25f, 11.5f, 3.5f, 12.0f,
		3.5f, 12.0f, 3.75f, 11.5f,
		//���� ������
		5.5f, 13.0f, 6.0f, 12.5f,
		6.0f, 12.5f, 6.0f, 11.5f,
		6.0f, 11.5f, 5.0f, 11.5f,
		5.0f, 11.5f, 5.0f, 12.5f,
		5.0f, 12.5f, 5.5f, 13.0f,

		5.0f, 11.5f, 5.5f, 12.5f,
		5.5f, 12.5f, 6.0f, 11.5f,

		5.25f, 11.5f, 5.5f, 12.0f,
		5.5f, 12.0f, 5.75f, 11.5f,
		//���
		4.0f, 11.5f, 5.0f, 11.5f,
		5.0f, 11.5f, 5.5f, 11.25f,
		5.5f, 11.25f, 5.5f, 10.75f,
		4.0f, 11.5f, 3.5f, 11.25f,
		3.5f, 11.25f, 3.5f, 10.75f,
		//���
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

		//����
		
		//������
		4.0f, 9.0f, 2.5f, 8.5f, 
		2.5f, 8.5f, 2.5f, 4.5f,
		1.0f, 4.5f, 8.0f, 4.5f,
		4.5f, 0.5f, 4.5f, 4.5f,
		5.0f, 9.0f, 6.5f, 8.5f,
		6.5f, 8.5f, 6.5f, 4.5f,
		//����� ����
		2.5f, 4.5f, 3.0f, 1.5f,

		3.5f, 4.0f, 4.0f, 3.5f, 
		4.0f, 3.5f, 3.5f, 3.0f,
		3.5f, 3.0f, 3.0f, 3.5f,
		3.0f, 3.5f, 3.5f, 4.0f,

		3.0f, 1.5f, 3.5f, 2.0f, 
		3.5f, 2.0f, 4.0f, 1.5f,
		//������ ����
		6.5f, 4.5f, 6.0f, 1.5f,

		6.0f, 4.5f, 5.5f, 4.0f,
		5.5f, 4.0f, 5.0f, 4.5f,

		5.5f, 3.0f, 6.0f, 2.5f,
		6.0f, 2.5f, 5.5f, 2.0f,
		5.5f, 2.0f, 5.0f, 2.5f,
		5.0f, 2.5f, 5.5f, 3.0f,
		//������
		1.0f, 0.5f, 2.5f, 1.5f, 
		2.5f, 1.5f, 7.0f, 1.5f,
		7.0f, 1.5f, 8.5f, 0.5f,
		1.0f, 0.5f, 8.5f, 0.5f,

		//����� ����
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
		//������ ����
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
		//������� ������� �����
		4.0f, 9.0f, 3.5f, 8.5f,
		3.5f, 8.5f, 4.0f, 8.0f,
		4.0f, 8.0f, 5.0f, 8.0f,
		5.0f, 8.0f, 5.5f, 8.5f,
		5.5f, 8.5f, 5.0f, 9.0f,

		4.5f, 9.0f, 4.0f, 8.5f,
		4.0f, 8.5f, 4.5f, 8.0f, 
		4.5f, 8.0f, 5.0f, 8.5f,
		5.0f, 8.5f, 4.5f, 9.0f,
		//������� ������ �����
		4.0f, 8.0f, 3.5f, 6.0f,
		3.5f, 6.0f, 4.5f, 5.0f,
		4.5f, 5.0f, 5.5f, 6.0f,
		5.5f, 6.0f, 5.0f, 8.0f,

		//������ ������
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
		// ������
		0.5f,3.f,1.f,4.5f, // �� ����� ���� ����� �� ���
		1.f,4.5f,0.5f,6.f, // ����� ��� ����� ����� �����
		0.5f,6.f,0.5f, 7.5f, // ����� ��� �����
		0.5f, 7.5f,1.f,8.f, // ����� ��� ���� �����
		1.f,8.f,1.5f,8.f, // ����� ��� ���� ��������
		1.5f,8.f,2.f,7.5f, // ����� ��� ���� ������
		2.f,7.5f,1.5f, 6.f, // ����� ��� ������ ������ ����
		1.5f, 6.f,1.5f,4.5f, // ����� ��� ������ �� �������
		1.5f,4.5f,3.f,4.5f, // �������
		3.f,4.5f,3.f,6.f, // ������ ��� ����� ����� �����
		3.f,6.f,2.5f,7.5f, // ������ ��� �����
		2.5f,7.5f,3.f,8.f, // ������ ��� ���� �����
		3.f,8.f,3.5f,8.f, // ������ ��� ���� ��������
		3.5f,8.f,4.f,7.5f, // ������ ��� ���� ������
		4.f,7.5f,4.f,6.f, // ������ ��� ������ ����
		4.f,6.f,3.5f,4.5f, // ������ ��� ������
		3.5f,4.5f,4.f,3.f, // �� ������� ��� ���� �� ����
		4.f,3.f,3.5f,1.5f, // ������ �����
		3.5f,1.5f,2.5f,1.f, // ���������� ������
		2.5f,1.f,2.f,1.f, // ���������� �����
		2.f,1.f,1.f,1.5f, // ���������� �����
		1.f,1.5f,0.5f,3.f, // ����� �����
		// ��������
		4.f,3.f,5.5f,3.5f, // ����� �� ������ ������
		5.5f,3.5f,7.f,3.5f, // ����� ����
		7.f,3.5f,7.5f,2.5f, // ����� ������ �� ������
		7.5f,2.5f,8.f,2.5f, // ����� ������
		8.f,2.5f,8.f,2.f, // ����� ������
		8.f,2.f,7.5f,2.f, // ����� ��� ������ ������
		7.5f,2.f,7.5f,0.5f, // ������ ���� ������ ������ ����
		7.5f,0.5f,6.5f,0.5f, // ������ ���� ���
		6.5f,0.5f,6.5f,1.f, // ������ ���� �����
		6.5f,1.f,6.f,1.f, // ����� ������ ���
		6.f,1.f,6.f,0.5f, // ����� ������ ���� ������
		6.f,0.5f,5.f,0.5f, // ����� ������ ���� ���
		5.f,0.5f,5.f,1.f, // ����� ������ ���� �����
		5.f,1.f,4.f,1.f, // ����� ������� � ��������� ������
		4.f,1.f,4.f,0.5f, // ������ �������� ���� ������
		4.f,0.5f,3.f,0.5f, // ������ �������� ���� ���
		3.f,0.5f,3.f,1.f, // ������ �������� ���� �����
		3.f,1.f,2.5f,1.f, // ����� �������� ���
		2.5f,1.f,2.5f,0.5f, // �������� ���� ������
		2.5f,0.5f,1.5f,0.5f, // �������� ���� ���
		1.5f,0.5f,1.5f,1.25f, // �������� ���� �����
		// ����� ����
		1.5f,3.5f,1.5f,3.f, // ����� ���� ����� ������ ����
		1.5f,3.f,2.f,3.f, // ����� ���� ���
		2.f, 3.f,2.f,3.5f, // ����� ���� ������
		2.f,3.5f,1.5f,3.5f, // ����� ���� ����
		// ������ ����
		2.5f,3.5f,2.5f,3.f, // ������ ���� �����
		2.5f,3.f,3.f, 3.f, // ������ ���� �����
		3.f,3.f,3.f,3.5f, // ������ ���� ������
		3.f,3.5f,2.5f,3.5f, // ������ ���� ������
		// ����� ��������
		1.f,5.5f,1.f,7.f, // ����� ����� ��������
		3.5f,5.5f,3.5f,7.f, // ������ ����� ��������
		// ���
		2.f,2.5f,2.5f,2.5f, // ��� ������
		2.5f,2.5f,2.25f,2.f, // ��� ������
		2.25f,2.f,2.f,2.5f // ��� �����
	};

	unsigned int arrayLength = sizeof(lines) / sizeof(float); //������ ������� ����� �������
	unsigned int myarrayLength = sizeof(mylines) / sizeof(float); //������ ������� ����� ����� �������
	float Vx = 8.5f; // ������ ������� �� �����������
	float Vy = 8.5f; // ������ ������� �� ���������
	float myVx = 9.0f; // ������ ����� ������� �� �����������
	float myVy = 15.0f; // ������ ����� ������� �� ���������

	float aspectFig = Vx / Vy; // ����������� ������ �������
	float myaspectFig = myVx / myVy; // ����������� ������ ����� �������
	

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
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
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
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
	private: bool keepAspectRatio; // �������� - ��������� �� ����������� ������ �������?
	private: bool MyPicture; 
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		System::Drawing::Graphics^ g = e->Graphics;
		Pen^ blackPen = gcnew Pen(Color::Black, 3);

		float Wx = ClientRectangle.Width;
		float Wy = ClientRectangle.Height;
		float aspectForm = Wx / Wy;

		float Sx, Sy, mySx, mySy;
		//��������� if � ������� ����������� ������� �� ������� � �������
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
		keepAspectRatio = true; // ��������� ��������: ��������� ����������� ������ �������
		MyPicture = false;//������� ��������� ����� �������
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::M://������� ������������ ��������
			keepAspectRatio = !keepAspectRatio;
			break;
		case Keys::N://������� ������������ ��������
			MyPicture = !MyPicture;
			break;
		default:
			break;
		}
		Refresh();
	}
	};
}
