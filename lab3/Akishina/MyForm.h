#pragma once

namespace Akishina {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	
	float Vx;
	float Vy;
	float aspectFig;
	vector<path> figure;
	mat3 T;
	mat3 initT;


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
	private: System::Windows::Forms::Button^ button1;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"txt";
			this->openFileDialog1->FileName = L"openFileDialog";
			this->openFileDialog1->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(270, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Открыть";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(357, 627);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::Aquamarine);

		for (int i = 0; i < figure.size(); i++) {
			path lines = figure[i]; // lines - очередная ломаная линия
			Pen^ pen = gcnew Pen(Color::FromArgb(lines.color.x, lines.color.y, lines.color.z));
			pen->Width = lines.thickness;

			vec2 start = normalize(T * vec3(lines.vertices[0], 1.0)); // начальная точка первого отрезка
			for (int j = 1; j < lines.vertices.size(); j++) { // цикл по конечным точкам (от единицы)
				vec2 end = normalize(T * vec3(lines.vertices[j], 1.0)); // конечная точка
				g->DrawLine(pen, start.x, start.y, end.x, end.y); // отрисовка отрезка
				start = end; // конечная точка текущего отрезка становится начальной точкой следующего
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		float Wcx = ClientRectangle.Width / 2.f;
		float Wcy = ClientRectangle.Height / 2.f;
		switch (e->KeyCode)
		{
			//поворот против часовой на 0,01 радиан
		case Keys::Q:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(0.01f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//поворот по часовой на 0,01 радиан
		case Keys::E:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(-0.01f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//смещение вверх на 1 пиксель
		case Keys::W:
			T = translate(0.f, -1.f) * T;
			break;
			//смещение влево на 1 пиксель
		case Keys::A:
			T = translate(-1.f, 0.f) * T;
			break;
			//смещение вниз на 1 пиксель
		case Keys::S:
			T = translate(0.f, 1.f) * T;
			break;
			//смещение вправо на 1 пиксель
		case Keys::D:
			T = translate(1.f, 0.f) * T;
			break;
			//возвращение к исходному рисунку
		case Keys::Escape:
			T = initT;
			break;
			//поворот против часовой на 0,05 радиан
		case Keys::R:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(-0.05f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//поворот по часовой на 0,05 радиан
		case Keys::Y:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(0.05f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//смещение вверх на 10 пикселей
		case Keys::T:
			T = T * translate(0.f, -10.f);
			break;
			//смещение вниз на 10 пикселей
		case Keys::G:
			T = T * translate(0.f, 10.f);
			break;
			//смещение влево на 10 пикселей
		case Keys::F:
			T = translate(-10.f, 0.f) * T;
			break;
			//смещение вправо на 10 пикселей
		case Keys::H:
			T = translate(10.f, 0.f) * T;
			break;
			//увеличение изображения в 1.1 раз
		case Keys::Z:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//уменьшение изображения в 1.1 раз
		case Keys::X:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1/1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//растяжение изображения по горизонтали в 1.1 раз
		case Keys::I:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.1f, 1.f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//сжатие изображения по горизонтали в 1.1 раз
		case Keys::K:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1/1.1f, 1.f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//растяжение изображения по вертикали в 1.1 раз
		case Keys::O:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.f, 1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//сжатие изображения по вертикали в 1.1 раз
		case Keys::L:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.f, 1/1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//отзеркаливание изображения относительно Ox
		case Keys::U:
			T = translate(-Wcx, -Wcy) * T;
			T = mirrorX() * T;
			T = translate(Wcx, Wcy) * T;
			break;
			//отзеркаливание изображения относительно Oy
		case Keys::J:
			T = translate(-Wcx, -Wcy) * T;
			T = mirrorY() * T;
			T = translate(Wcx, Wcy) * T;
			break;
		default:
			break;
		}
		Refresh();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// в файловом диалоге нажата кновка OK
			// перезапись имени файла из openFileDialog->FileName в fileName
			wchar_t fileName[1024]; // переменная, в которой посимвольно сохраним имя файла
			for (int i = 0; i < openFileDialog1->FileName->Length; i++)
				fileName[i] = openFileDialog1->FileName[i];
			fileName[openFileDialog1->FileName->Length] = '\0';
			// объявление и открытие файла
			ifstream in;
			in.open(fileName);
			if (in.is_open()) {
				// файл успешно открыт
				figure.clear(); // очищаем имеющийся список ломаных
				// временные переменные для чтения из файла
				float thickness = 2; // толщина со значением по умолчанию 2
				float r, g, b; // составляющие цвета
				r = g = b = 0; // значение составляющих цвета по умолчанию (черный)
				string cmd; // строка для считывания имени команды
				// непосредственно работа с файлом
				string str; // строка, в которую считываем строки файла
				getline(in, str); // считываем из входного файла первую строку
				while (in) { // если очередная строка считана успешно
					// обрабатываем строку
					if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
						// прочитанная строка не пуста и не комментарий
						stringstream s(str); // строковый поток из строки str
						s >> cmd;
						if (cmd == "frame") { // размеры изображения
							s >> Vx >> Vy; // считываем глобальные значение Vx и Vy
							aspectFig = Vx / Vy;
							float Wx = ClientRectangle.Width;
							float Wy = ClientRectangle.Height;
							float aspectForm = Wx / Wy;
							float S = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
							float Ty = S * Vy;
							initT = translate(0.f, Ty) * scale(S, -S);
							T = initT;
						}
						else if (cmd == "color") { // цвет линии
							s >> r >> g >> b; // считываем три составляющие цвета
						}
						else if (cmd == "thickness") { // толщина линии
							s >> thickness; // считываем значение толщины
						}
						else if (cmd == "path") { // набор точек
							vector<vec2> vertices; // список точек ломаной
							int N; // количество точек
							s >> N;
							string str1; // дополнительная строка для чтения из файла
							while (N > 0) { // пока не все точки считали
								getline(in, str1); // считываем в str1 из входного файла очередную строку
								// так как файл корректный, то на конец файла проверять не нужно
								if ((str1.find_first_not_of(" \t\r\n") != string::npos) && (str1[0] != '#')) {
									// прочитанная строка не пуста и не комментарий
										// значит в ней пара координат
									float x, y; // переменные для считывания
									stringstream s1(str1); // еще один строковый поток из строки str1
									s1 >> x >> y;
									vertices.push_back(vec2(x, y)); // добавляем точку в список
									N--; // уменьшаем счетчик после успешного считывания точки
								}
							}
							// все точки считаны, генерируем ломаную (path) и кладем ее в список figure
							figure.push_back(path(vertices, vec3(r, g, b), thickness));
						}
					}
					// считываем очередную строку
					getline(in, str);
				}
				Refresh();
			}
		}
	}
};
}
