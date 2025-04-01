#pragma once

namespace Akishina {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	
	mat4 T; // �������, � ������� ������������� ��� ��������������
	mat4 initT; // ������� ���������� ��������������

	vec3 Vc; // ���������� �������� ������ ������� ����
	vec3 V; // ������� ��������������� � ������������ �������
	vec3 Vc_work, V_work; // ������� ��������� ���������������


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
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:


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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"txt";
			this->openFileDialog1->FileName = L"openFileDialog";
			this->openFileDialog1->Filter = L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(782, 353);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L" ";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: float left = 30, right = 100, top = 20, bottom = 50; // ���������� �� ������ ����
		   float minX = left, maxX; // �������� ��������� ��������� x
		   float minY = top, maxY; // �������� ��������� ��������� y
		   float Wcx = left, Wcy; // ���������� ������ ������� ���� ��������������
		   float Wx, Wy; // ������ � ������ ��������������
		   float Wx_work, Wy_work; // ������ � ������ ������� ������ ����� ����� �������
		   float Wx_part = 0.6, Wy_part = 0.6; // ���� Wx_work, Wy_work �� Wx, Wy ��������������
		   float Wcx_work, Wcy_work; // ���������� ������ ������� ���� ������ �������� ��������������
		   float Wz_work; // ���������� ������� ���������������
		   int numXsect = 5, numYsect = 5, numZsect = 5; // ���������� ������ ������������ ����� �� ����
	private: System::Void rectCalc() {
			maxX = ClientRectangle.Width - right; // �������� ��������� ��������� x
			maxY = ClientRectangle.Height - bottom; // �������� ��������� ��������� y
			Wcy = maxY; // ���������� ������ ������� ���� ��������������
			Wx = maxX - left; // ������ ��������������
			Wy = maxY - top; // ������ � ������ ��������������
			Wx_work = Wx_part * Wx; // ���������� ������ � ������
			Wy_work = Wy_part * Wy; // �������� ��������������
			Wcx_work = maxX - Wx_work; // ���������� ��������� ������� ������
			Wcy_work = minY + Wy_work; // ���� ������ �������� �������� ��������������
			Wz_work = Wcy - Wcy_work; // ���������� ������� ���������������
	}
	private: System::Void worldRectCalc() {
		Vc_work = normalize(T * vec4(Vc, 1.f));
		V_work = mat3(T) * V;
	}
	private: float f(float x, float z) {
		return x * sin(sqrtf(x * x + z * z));
	}
	private: bool f_exists(float x, float z, float delta) {
		return true;
	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::Aquamarine);

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen, left, top, Wx, Wy);

		Pen^ gridPen = gcnew Pen(Color::Black, 1);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);



		//��������� ������������ ����� Ox

		float gridStep_x = Wx_work / numXsect;	// ���������� ����� ������� ����� �� x
		float grid_dX = V_work.x / numXsect;	// ���������� ����� ������� ����� �� x � ������� �����������
		float tick_x = Vc_work.x;				// �������� ��������������� ������ ����� �����
		for (int i = 0; i <= numXsect; i++) {	// ���� �� ���������� �����
			float tmpXCoord_d = Wcx + i * gridStep_x;		// ������ ���������� x i-� ������������ �����
			float tmpXCoord_v = Wcx_work + i * gridStep_x;	// ���������� x i-� ������������ �����
			// i-� ������������ �����
			g->DrawLine(gridPen, tmpXCoord_d, Wcy, tmpXCoord_v, Wcy_work);
			// i-� ������������ �����
			g->DrawLine(gridPen, tmpXCoord_v, Wcy_work, tmpXCoord_v, minY);
			if (i > 0 && i < numXsect) {		// ���� ����� �� �������
				// ������� ����� � ������ ����� ������������ �����
				g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush, tmpXCoord_d, Wcy);
			}
			tick_x += grid_dX;		// ��������� ��������, ��������������� ��������� �����
		}




		//��������� ������������ ����� Oz

		gridStep_x = (Wx - Wx_work) / numZsect;		// ���������� ����� ������������� ������� ����� �� �����������
		float gridStep_y = Wz_work / numZsect;		// ���������� ����� ��������������� ������� ����� �� ���������
		float grid_dZ = V_work.z / numZsect;		// ���������� ����� ������� ����� �� $z$ � ������� �����������
		float tick_z = Vc_work.z;				// ��������, ��������������� ������ ����� �����
		for (int i = 0; i <= numZsect; i++) {	// ���� �� ���������� �����
			float tmpXCoord_v = Wcx_work - i * gridStep_x;	// ���������� x ������������ �����
			float tmpYCoord_g = Wcy_work + i * gridStep_y;	// ���������� y �������������� �����
			float tmpXCoord_g = tmpXCoord_v + Wx_work;		// ������ ���������� x �������������� �����
			// i-� ������������ �����
			g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_v, tmpYCoord_g - Wy_work);
			// i-� �������������� �����
			g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_g, tmpYCoord_g);
			if (i > 0 && i < numZsect) {		// ���� ����� �� �������
				// ������� ����� � ������ ����� �������������� �����
				g->DrawString(tick_z.ToString("F4"), drawFont, drawBrush, tmpXCoord_g, tmpYCoord_g);
			}
			tick_z += grid_dZ;		// ��������� ��������, ��������������� ��������� �����
		}




		//��������� ������������ ����� Oy

		float gridStep_z = Wy_work / numYsect;		// ���������� ����� ��������������� ������� ����� �� ���������
		float grid_dY = V_work.y / numYsect;		// ���������� ����� ������� ����� �� $z$ � ������� �����������
		float tick_y = Vc_work.y;					// ��������, ��������������� ������ ����� �����
		for (int i = 0; i <= numYsect; i++) {	// ���� �� ���������� �����
			float tmpZCoord_v = Wcy_work - i * gridStep_z;	// ���������� x ������������ �����
			// i-� ������������ �����
			g->DrawLine(gridPen, Wcx_work, tmpZCoord_v, maxX, tmpZCoord_v);
			// i-� �������������� �����
			g->DrawLine(gridPen, Wcx_work, tmpZCoord_v, minX, tmpZCoord_v + (Wy - Wy_work));
			if (i > 0 && i < numYsect) {		// ���� ����� �� �������
				// ������� ����� � ������ ����� �������������� �����
				g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX, tmpZCoord_v);
			}
			tick_y += grid_dY;		// ��������� ��������, ��������������� ��������� �����
		}




		//��������� �������
		Pen^ pen = gcnew Pen(Color::Blue, 1);
		float deltaX = V_work.x / Wx_work;		// ��� �� x � ������� �����������
		float deltaZ = V_work.z / Wz_work;		// ��� �� z � ������� �����������
		float deltaWcx = (Wcx_work - Wcx) / Wz_work;	// ��� ��������������� �� x � ����������� ������

		bool hasStart;

		// ���� �� ���������������
		float z = Vc_work.z;			// ���������� z �������� ��������� ����� �������
		float Wcx_w = Wcx_work, Wcy_w = Wcy_work;	// ���������� ������ ������� ���� �������� �������������� (�������������)

		while (Wcy_w <= Wcy) {				// ���� �� ��������� ��� ��������������
			vec2 start, end;				// ����� ������ ������� � ����������� ������
			float x, y;						// ���������� ��� ��������� ����� � ������� ��
			start.x = Wcx_w;				// ��� ��������� ����� ������� ������� ������������� ���������� x
			x = Vc_work.x;					// ���������� x ��������� ����� ������� ������� � ������� �����������
			hasStart = f_exists(x, z, deltaX);
			if (hasStart) {
				y = f(x, z);				// ���������� y ��������� ����� � ������� �����������
				start.y = Wcy_w - (y - Vc_work.y) / V_work.y * Wy_work;		// ��������� ��������������� �������� � ����������� ������
			}
			float maxX = Wcx_w + Wx_work;	// ������������ �������� x � ������� ��������������
			while (start.x < maxX) {
				vec2 end;					// ����� ����� ������� � ����������� ������
				bool hasEnd;
				float deltaY;				// ������ ����� � �������������� (���� ����� ������)
				float red, green, blue;		// ���������� ����� �������
				end.x = start.x + 1.f;		// ���������� x ���������� �� �������
				x += deltaX;				// ���������� x �������� ����� ������� � ������� �����������
				hasEnd = f_exists(x, z, deltaX);
				if (hasEnd) {
					y = f(x, z);			// ���������� y ��������� ����� � ������� �����������
					// ��������� ��������������� �������� � ����������� ������
					deltaY = (y - Vc_work.y) / V_work.y;
					end.y = Wcy_w - deltaY * Wy_work;
				}
				vec2 tmpEnd = end;
				bool visible = hasStart && hasEnd && clip(start, end, Wcx_w, Wcy_w - Wy_work, Wcx_w + Wx_work, Wcy_w);
				if (visible) {				// ���� ������� �����
					if (deltaY > 1.f) deltaY = 1.f;		// ����������� �������� ������ �����
					if (deltaY < 0.f) deltaY = 0.f;		// �� ������, ���� ������� ���������
					green = 510.f * deltaY;				// ��������������� ���������� ������������
					if (deltaY < 0.5) {					// ���� ����� ���� �������� ������� ���������
					// ���������� �������� ��� ���������
						blue = 255.f - green;			// ����� ��������� �������
						red = 0.f;						// ������� ����� ����
					}
					else {								// ���� ����� �� ���� ��������
						blue = 0.f;						// ����� ����� ����
						red = green - 255.f;			// ��������� ������� � �������
						green = 510.f - green;			// � �������������� ������������ ������������
					}
					pen->Color = Color::FromArgb(red, green, blue);		// ������ ���� ����
				// ����� ���������, start � end - ����� ������� ����� �������
					g->DrawLine(pen, start.x, start.y, end.x, end.y);	// ��������� ������� ������
				}
				// �������� ����� ������������� ������� ���������� ��������� ������ ����������
				start = tmpEnd;
				hasStart = hasEnd;
			}
			Wcy_w += 1.f;			// ��������� � ���������� ��������������, �� ����� ���� �� ���� �������
			Wcx_w -= deltaWcx;		// � ����� �� ��������� ��������
			z += deltaZ;			// ��������� ��������������� �������� z ��� ���������� ��������������
		}



	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		Vc = vec3(-2.f, -2.f, -2.f);
		V = vec3(4.f, 4.f, 4.f);
		initT = mat4(1.f);
		T = initT;
		rectCalc();
		worldRectCalc();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		float centerX = Vc_work.x + V_work.x / 2; // ���������� ������ ��������������
		float centerY = Vc_work.y + V_work.y / 2; // � ������� ������� ���������
		float centerZ = Vc_work.z + V_work.z / 2;

		
		switch (e->KeyCode)
		{
		case Keys::Escape:
			T = initT;
			numZsect = 5;
			numXsect = 5;
			numYsect = 5;
			/*Wx_part = 0.6;
			Wy_part = 0.6;*/
			break;
		case Keys::A:
			//����� ������� ������ �� ���� �������
			T = translate(-V_work.x / Wx, 0.f, 0.f) * T;
			break;
		case Keys::D:
			//����� ������� ����� �� ���� �������
			T = translate(V_work.y / Wx, 0.f, 0.f) * T;
			break;
		case Keys::R:
			//����� ������� ���� �� ���� �������
			T = translate(0.f, V_work.y / Wy, 0.f) * T;
			break;
		case Keys::F:
			//����� ������� ���� �� ���� �������
			T = translate(0.f, -V_work.y / Wy, 0.f) * T;
			break;
		case Keys::W:
			//����� ������� ������ �� ���� �������
			T = translate(0.f, 0.f, V_work.z / Wx) * T;
			break;
		case Keys::S:
			//����� ������� ����� �� ���� �������
			T = translate(0.f, 0.f, -V_work.z / Wx) * T;
			break;

		case Keys::Z:
			//���������� � 1.1
			T = translate(-centerX, -centerY, -centerZ) * T;	// ������� ������ ��������� � �����
			T = scale(1.1, 1.1, 1.1) * T;						// ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T;		// ������� ������� ������ ���������
			break;
		case Keys::X:
			//���������� � 1.1
			T = translate(-centerX, -centerY, -centerZ) * T;	// ������� ������ ��������� � �����
			T = scale(1 / 1.1, 1 / 1.1, 1 / 1.1) * T;						// ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T;		// ������� ������� ������ ���������
			break;

		case Keys::Q:
			//���������� �� Ox � 1.1
			if (Wx_part < 0.9) {
				Wx_part *= 1.1;
				break;
			}
			else break;
		case Keys::E:
			//���������� �� Ox � 1.1
			if (Wx_part > 0.2) {
				Wx_part *= 1 / 1.1;
				break;
			}
			else break;
		case Keys::C:
			//���������� �� Oy � 1.1
			if (Wy_part < 0.9) {
				Wy_part *= 1.1;
				break;
			}
			else break;
		case Keys::V:
			//���������� �� Oy � 1.1
			if (Wy_part > 0.2)
				Wy_part *= 1 / 1.1;
			break;

		case Keys::T:
			//���������� � 1.1 �� ��� Ox
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1.1, 1, 1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;
		case Keys::G:
			//���������� � 1.1 �� ��� Ox
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1 / 1.1, 1, 1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;
		case Keys::Y:
			//���������� � 1.1 �� ��� Oy
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1, 1.1, 1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;
		case Keys::H:
			//���������� � 1.1 �� ��� Oy
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1, 1 / 1.1, 1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;
		case Keys::U:
			//���������� � 1.1 �� ��� Oz
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1, 1, 1.1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;
		case Keys::J:
			//���������� � 1.1 �� ��� Oz
			T = translate(-centerX, -centerY, -centerZ) * T; // ������� ������ ��������� � �����
			T = scale(1, 1, 1 / 1.1) * T; // ��������������� ������������ ������ ���������
			T = translate(centerX, centerY, centerZ) * T; // ������� ������� ������ ���������
			break;

		case Keys::D1:
			//���������� ������ �� Ox
			numXsect = numXsect + 1;
			break;
		case Keys::D2:
			//���������� ������ �� Ox
			if (numXsect > 2)
				numXsect = numXsect - 1;
			break;
		case Keys::D3:
			//���������� ������ �� Oy
			numYsect = numYsect + 1;
			break;
		case Keys::D4:
			//���������� ������ �� Oy
			if (numYsect > 2)
				numYsect = numYsect - 1;
			break;
		case Keys::D5:
			//���������� ������ �� Oz
			numZsect = numZsect + 1;
			break;
		case Keys::D6:
			//���������� ������ �� Oz
			if (numZsect > 2)
				numZsect = numZsect - 1;
			break;
		default:
			break;
		}
		rectCalc();
		worldRectCalc();
		Refresh();
	}
};
}
