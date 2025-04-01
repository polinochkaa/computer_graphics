#pragma once

namespace Akishina {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	
	mat4 T; // матрица, в которой накапливаются все преобразования
	mat4 initT; // матрица начального преобразования

	vec3 Vc; // координаты дальнего левого нижнего угла
	vec3 V; // размеры параллелепипеда в пространстве графика
	vec3 Vc_work, V_work; // рабочие параметры параллелепипеда


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
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:


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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"txt";
			this->openFileDialog1->FileName = L"openFileDialog";
			this->openFileDialog1->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
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
	private: float left = 30, right = 100, top = 20, bottom = 50; // расстояния до границ окна
		   float minX = left, maxX; // диапазон изменения координат x
		   float minY = top, maxY; // диапазон изменения координат y
		   float Wcx = left, Wcy; // координаты левого нижнего угла прямоугольника
		   float Wx, Wy; // ширина и высота прямоугольника
		   float Wx_work, Wy_work; // ширина и высота области вывода одной линии графика
		   float Wx_part = 0.6, Wy_part = 0.6; // доля Wx_work, Wy_work от Wx, Wy соответственно
		   float Wcx_work, Wcy_work; // координаты левого нижнего угла самого дальнего прямоугольника
		   float Wz_work; // количество рабочих прямоугольников
		   int numXsect = 5, numYsect = 5, numZsect = 5; // количество секций координатной сетки по осям
	private: System::Void rectCalc() {
			maxX = ClientRectangle.Width - right; // диапазон изменения координат x
			maxY = ClientRectangle.Height - bottom; // диапазон изменения координат y
			Wcy = maxY; // координаты левого нижнего угла прямоугольника
			Wx = maxX - left; // ширина прямоугольника
			Wy = maxY - top; // ширина и высота прямоугольника
			Wx_work = Wx_part * Wx; // вычисление ширины и высоты
			Wy_work = Wy_part * Wy; // рабочего прямоугольника
			Wcx_work = maxX - Wx_work; // вычисление координат нижнего левого
			Wcy_work = minY + Wy_work; // угла самого дальнего рабочего прямоугольника
			Wz_work = Wcy - Wcy_work; // количество рабочих прямоугольников
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



		//ОТРИСОВКА КООРДИНАТНОЙ СЕТКИ Ox

		float gridStep_x = Wx_work / numXsect;	// расстояние между линиями сетки по x
		float grid_dX = V_work.x / numXsect;	// расстояние между линиями сетки по x в мировых координатах
		float tick_x = Vc_work.x;				// значение соответствующее первой линии сетки
		for (int i = 0; i <= numXsect; i++) {	// цикл по количеству линий
			float tmpXCoord_d = Wcx + i * gridStep_x;		// нижняя координата x i-й диагональной линии
			float tmpXCoord_v = Wcx_work + i * gridStep_x;	// координата x i-й вертикальной линии
			// i-я диагональная линия
			g->DrawLine(gridPen, tmpXCoord_d, Wcy, tmpXCoord_v, Wcy_work);
			// i-я вертикальная линия
			g->DrawLine(gridPen, tmpXCoord_v, Wcy_work, tmpXCoord_v, minY);
			if (i > 0 && i < numXsect) {		// если линия не крайняя
				// выводим текст в нижней точке диагональной линии
				g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush, tmpXCoord_d, Wcy);
			}
			tick_x += grid_dX;		// вычисляем значение, соответствующее следующей линии
		}




		//ОТРИСОВКА КООРДИНАТНОЙ СЕТКИ Oz

		gridStep_x = (Wx - Wx_work) / numZsect;		// расстояние между вертикальными линиями сетки по горизонтали
		float gridStep_y = Wz_work / numZsect;		// расстояние между горизонтальными линиями сетки по вертикали
		float grid_dZ = V_work.z / numZsect;		// расстояние между линиями сетки по $z$ в мировых координатах
		float tick_z = Vc_work.z;				// значение, соответствующее первой линии сетки
		for (int i = 0; i <= numZsect; i++) {	// цикл по количеству линий
			float tmpXCoord_v = Wcx_work - i * gridStep_x;	// координата x вертикальных линий
			float tmpYCoord_g = Wcy_work + i * gridStep_y;	// координата y горизонтальных линий
			float tmpXCoord_g = tmpXCoord_v + Wx_work;		// вторая координата x горизонтальных линий
			// i-я вертикальная линия
			g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_v, tmpYCoord_g - Wy_work);
			// i-я горизонтальная линия
			g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_g, tmpYCoord_g);
			if (i > 0 && i < numZsect) {		// если линия не крайняя
				// выводим текст в правой точке горизонтальной линии
				g->DrawString(tick_z.ToString("F4"), drawFont, drawBrush, tmpXCoord_g, tmpYCoord_g);
			}
			tick_z += grid_dZ;		// вычисляем значение, соответствующее следующей линии
		}




		//ОТРИСОВКА КООРДИНАТНОЙ СЕТКИ Oy

		float gridStep_z = Wy_work / numYsect;		// расстояние между горизонтальными линиями сетки по вертикали
		float grid_dY = V_work.y / numYsect;		// расстояние между линиями сетки по $z$ в мировых координатах
		float tick_y = Vc_work.y;					// значение, соответствующее первой линии сетки
		for (int i = 0; i <= numYsect; i++) {	// цикл по количеству линий
			float tmpZCoord_v = Wcy_work - i * gridStep_z;	// координата x вертикальных линий
			// i-я вертикальная линия
			g->DrawLine(gridPen, Wcx_work, tmpZCoord_v, maxX, tmpZCoord_v);
			// i-я горизонтальная линия
			g->DrawLine(gridPen, Wcx_work, tmpZCoord_v, minX, tmpZCoord_v + (Wy - Wy_work));
			if (i > 0 && i < numYsect) {		// если линия не крайняя
				// выводим текст в правой точке горизонтальной линии
				g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX, tmpZCoord_v);
			}
			tick_y += grid_dY;		// вычисляем значение, соответствующее следующей линии
		}




		//ОТРИСОВКА ГРАФИКА
		Pen^ pen = gcnew Pen(Color::Blue, 1);
		float deltaX = V_work.x / Wx_work;		// шаг по x в мировых координатах
		float deltaZ = V_work.z / Wz_work;		// шаг по z в мировых координатах
		float deltaWcx = (Wcx_work - Wcx) / Wz_work;	// шаг прямоугольников по x в координатах экрана

		bool hasStart;

		// цикл по прямоугольникам
		float z = Vc_work.z;			// координата z наиболее удаленных точек графика
		float Wcx_w = Wcx_work, Wcy_w = Wcy_work;	// координаты левого нижнего угла рабочего прямоугольника (инициализация)

		while (Wcy_w <= Wcy) {				// пока не перебрали все прямоугольники
			vec2 start, end;				// точка начала отрезка в координатах экрана
			float x, y;						// переменные для координат точки в мировой СК
			start.x = Wcx_w;				// для начальной точки первого отрезка устанавливаем координату x
			x = Vc_work.x;					// координата x начальной точки первого отрезка в мировых координатах
			hasStart = f_exists(x, z, deltaX);
			if (hasStart) {
				y = f(x, z);				// координата y начальной точки в мировых координатах
				start.y = Wcy_w - (y - Vc_work.y) / V_work.y * Wy_work;		// вычисляем соответствующее значение в координатах экрана
			}
			float maxX = Wcx_w + Wx_work;	// максимальное значение x в рабочем прямоугольнике
			while (start.x < maxX) {
				vec2 end;					// точка конца отрезка в координатах экрана
				bool hasEnd;
				float deltaY;				// высота точки в прямоугольнике (доля общей высоты)
				float red, green, blue;		// компоненты цвета отрезка
				end.x = start.x + 1.f;		// координата x отличается на единицу
				x += deltaX;				// координата x конечной точки отрезка в мировых координатах
				hasEnd = f_exists(x, z, deltaX);
				if (hasEnd) {
					y = f(x, z);			// координата y начальной точки в мировых координатах
					// вычисляем соответствующее значение в координатах экрана
					deltaY = (y - Vc_work.y) / V_work.y;
					end.y = Wcy_w - deltaY * Wy_work;
				}
				vec2 tmpEnd = end;
				bool visible = hasStart && hasEnd && clip(start, end, Wcx_w, Wcy_w - Wy_work, Wcx_w + Wx_work, Wcy_w);
				if (visible) {				// если отрезок видим
					if (deltaY > 1.f) deltaY = 1.f;		// нормализуем значение высоты точки
					if (deltaY < 0.f) deltaY = 0.f;		// на случай, если отрезок отсекался
					green = 510.f * deltaY;				// предварительное вычисление произведения
					if (deltaY < 0.5) {					// если точка ниже середины области видимости
					// компонента зеленого уже вычислена
						blue = 255.f - green;			// синий дополняет зеленый
						red = 0.f;						// красный равен нулю
					}
					else {								// если точка не ниже середины
						blue = 0.f;						// синий равен нулю
						red = green - 255.f;			// вычисляем красный и зеленый
						green = 510.f - green;			// с использованием вычисленного произведения
					}
					pen->Color = Color::FromArgb(red, green, blue);		// меняем цвет пера
				// после отсечения, start и end - концы видимой части отрезка
					g->DrawLine(pen, start.x, start.y, end.x, end.y);	// отрисовка видимых частей
				}
				// конечная точка неотсеченного отрезка становится начальной точкой следующего
				start = tmpEnd;
				hasStart = hasEnd;
			}
			Wcy_w += 1.f;			// переходим к следующему прямоугольнику, он будет ниже на один пиксель
			Wcx_w -= deltaWcx;		// и левее на некоторое значение
			z += deltaZ;			// вычисляем соответствующее значение z для очередного прямоугольника
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
		float centerX = Vc_work.x + V_work.x / 2; // координаты центра прямоугольника
		float centerY = Vc_work.y + V_work.y / 2; // в мировой системе координат
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
			//сдвиг графика вправо на один пиксель
			T = translate(-V_work.x / Wx, 0.f, 0.f) * T;
			break;
		case Keys::D:
			//сдвиг графика влево на один пиксель
			T = translate(V_work.y / Wx, 0.f, 0.f) * T;
			break;
		case Keys::R:
			//сдвиг графика вниз на один пиксель
			T = translate(0.f, V_work.y / Wy, 0.f) * T;
			break;
		case Keys::F:
			//сдвиг графика верх на один пиксель
			T = translate(0.f, -V_work.y / Wy, 0.f) * T;
			break;
		case Keys::W:
			//сдвиг графика вперед на один пиксель
			T = translate(0.f, 0.f, V_work.z / Wx) * T;
			break;
		case Keys::S:
			//сдвиг графика назад на один пиксель
			T = translate(0.f, 0.f, -V_work.z / Wx) * T;
			break;

		case Keys::Z:
			//увеличение в 1.1
			T = translate(-centerX, -centerY, -centerZ) * T;	// перенос начала координат в центр
			T = scale(1.1, 1.1, 1.1) * T;						// масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T;		// возврат позиции начала координат
			break;
		case Keys::X:
			//уменьшение в 1.1
			T = translate(-centerX, -centerY, -centerZ) * T;	// перенос начала координат в центр
			T = scale(1 / 1.1, 1 / 1.1, 1 / 1.1) * T;						// масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T;		// возврат позиции начала координат
			break;

		case Keys::Q:
			//увеличение по Ox в 1.1
			if (Wx_part < 0.9) {
				Wx_part *= 1.1;
				break;
			}
			else break;
		case Keys::E:
			//уменьшение по Ox в 1.1
			if (Wx_part > 0.2) {
				Wx_part *= 1 / 1.1;
				break;
			}
			else break;
		case Keys::C:
			//увеличение по Oy в 1.1
			if (Wy_part < 0.9) {
				Wy_part *= 1.1;
				break;
			}
			else break;
		case Keys::V:
			//уменьшение по Oy в 1.1
			if (Wy_part > 0.2)
				Wy_part *= 1 / 1.1;
			break;

		case Keys::T:
			//увеличение в 1.1 по оси Ox
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1.1, 1, 1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;
		case Keys::G:
			//уменьшение в 1.1 по оси Ox
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1 / 1.1, 1, 1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;
		case Keys::Y:
			//увеличение в 1.1 по оси Oy
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1, 1.1, 1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;
		case Keys::H:
			//уменьшение в 1.1 по оси Oy
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1, 1 / 1.1, 1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;
		case Keys::U:
			//увеличение в 1.1 по оси Oz
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1, 1, 1.1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;
		case Keys::J:
			//уменьшение в 1.1 по оси Oz
			T = translate(-centerX, -centerY, -centerZ) * T; // перенос начала координат в центр
			T = scale(1, 1, 1 / 1.1) * T; // масштабирование относительно начала координат
			T = translate(centerX, centerY, centerZ) * T; // возврат позиции начала координат
			break;

		case Keys::D1:
			//увелечение секций по Ox
			numXsect = numXsect + 1;
			break;
		case Keys::D2:
			//уменьшение секций по Ox
			if (numXsect > 2)
				numXsect = numXsect - 1;
			break;
		case Keys::D3:
			//увелечение секций по Oy
			numYsect = numYsect + 1;
			break;
		case Keys::D4:
			//уменьшение секций по Oy
			if (numYsect > 2)
				numYsect = numYsect - 1;
			break;
		case Keys::D5:
			//увелечение секций по Oz
			numZsect = numZsect + 1;
			break;
		case Keys::D6:
			//уменьшение секций по Oz
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
