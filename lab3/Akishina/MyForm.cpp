#include <vector>
#include "Matrix.h"
#include "Transform.h"
#include "Figure.h"
#include <fstream>
#include <sstream>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^> ^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Akishina::MyForm form;
	Application::Run(% form);
}