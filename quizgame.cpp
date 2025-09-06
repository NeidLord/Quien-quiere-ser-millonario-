#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <winuser.h>
#include <commctrl.h>
#include <tchar.h>

// Define los colores específicos
#define PURPLE_COLOR RGB(140, 82, 255) // Morado (#8c52ff)
#define BLUE_COLOR   RGB(0, 0, 255)    // Azul puro
#define LIME_GREEN   RGB(0, 255, 0)    // Verde brillante para la respuesta correcta

// Identificadores para los nuevos controles
#define IDC_START_BUTTON 1000
#define IDC_PROJECT_LABEL 1001 // Nuevo ID para "PROYECTO REALIZADO POR"
#define IDC_TEAM_LABEL    1002 // ID para "TEAM MULTITECHNEW"
#define IDC_CREDITS_LABEL 1003 // Nuevo ID para los nombres de los integrantes
#define IDC_ENJOY_LABEL   1004 // Nuevo ID para "¡DISFRUTEN!"

// Declaración de handles y variables globales
HWND hMainWindow;
HWND hQuestionLabel;
HWND hOptionA;
HWND hOptionB;
HWND hOptionC;
HWND hOptionD;
HWND hChaosLabel; // Handle para la etiqueta del contador de Chaos

// Controles de la pantalla de inicio
HWND hProjectLabel; // "PROYECTO REALIZADO POR"
HWND hTeamLabel;    // "TEAM MULTITECHNEW"
HWND hStartButton;
HWND hCreditsLabel; // Nombres de los integrantes
HWND hEnjoyLabel;   // Etiqueta para "¡DISFRUTEN!"

int currentQuestionIndex = 0;
int correctAnswers = 0;
int totalChaos = 0; // Variable para el contador de Chaos
const int totalQuestions = 20;

// Pinceles globales para los colores sólidos de los botones
HBRUSH hBrushCorrect = NULL;
HBRUSH hBrushIncorrect = NULL;
HBRUSH hBrushDefault = NULL;
HBRUSH hBrushBlue = NULL; // Pincel para el color azul de los botones

// Fuentes globales para el texto
HFONT hFontQuestion = NULL;
HFONT hFontOption = NULL;
HFONT hFontChaos = NULL; // Fuente para la etiqueta de Chaos
HFONT hFontProjectLabel = NULL; // Fuente para "PROYECTO REALIZADO POR"
HFONT hFontTeamLabel = NULL;    // Fuente para "TEAM MULTITECHNEW"
HFONT hFontCredits = NULL;      // Fuente para los nombres en la pantalla de inicio
HFONT hFontEnjoy = NULL;        // Fuente para "¡DISFRUTEN!"

// Estructura para almacenar preguntas, opciones y respuesta correcta
struct Question {
    std::string questionText;
    std::string optionA;
    std::string optionB;
    std::string optionC;
    std::string optionD;
    char correctOption;
    int chaosReward; // Recompensa de Chaos por pregunta
};

// Vector de preguntas
std::vector<Question> questions;

// Prototipos de las funciones
std::string intToString(int num);
void initQuestions();
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void ShowResult();
void OnResize(int width, int height);
void UpdateChaosDisplay();
void ShowGameControls();
void HideStartScreen();
void ShowStartScreen(HWND hWnd); // Ahora toma hWnd para crear los controles de inicio

// Función auxiliar para convertir un entero a string usando stringstream
std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void initQuestions() {
    Question q;
    // Pregunta 1
    q.questionText = "¿Cuál es la capital de Francia?";
    q.optionA = "París";
    q.optionB = "Londres";
    q.optionC = "Madrid";
    q.optionD = "Berlín";
    q.correctOption = 'A';
    q.chaosReward = 100;
    questions.push_back(q);

    // Pregunta 2
    q.questionText = "¿Cuál es el planeta más grande del sistema solar?";
    q.optionA = "Tierra";
    q.optionB = "Júpiter";
    q.optionC = "Marte";
    q.optionD = "Saturno";
    q.correctOption = 'B';
    q.chaosReward = 200;
    questions.push_back(q);

    // Pregunta 3
    q.questionText = "¿Quién escribió 'Don Quijote de la Mancha'?";
    q.optionA = "Lope de Vega";
    q.optionB = "Cervantes";
    q.optionC = "Góngora";
    q.optionD = "Calderón de la Barca";
    q.correctOption = 'B';
    q.chaosReward = 300;
    questions.push_back(q);

    // Pregunta 4
    q.questionText = "¿En qué año llegó el hombre a la luna?";
    q.optionA = "1969";
    q.optionB = "1975";
    q.optionC = "1960";
    q.optionD = "1981";
    q.correctOption = 'A';
    q.chaosReward = 400;
    questions.push_back(q);

    // Pregunta 5
    q.questionText = "¿Cuál es el río más largo del mundo?";
    q.optionA = "Nilo";
    q.optionB = "Amazonas";
    q.optionC = "Misisipi";
    q.optionD = "Yangtsé";
    q.correctOption = 'B';
    q.chaosReward = 500;
    questions.push_back(q);

    // Pregunta 6
    q.questionText = "¿Quién pintó 'La Mona Lisa'?";
    q.optionA = "Van Gogh";
    q.optionB = "Picasso";
    q.optionC = "Da Vinci";
    q.optionD = "Miguel Ángel";
    q.correctOption = 'C';
    q.chaosReward = 600;
    questions.push_back(q);

    // Pregunta 7
    q.questionText = "¿Cuántos lados tiene un hexágono?";
    q.optionA = "5";
    q.optionB = "6";
    q.optionC = "7";
    q.optionD = "8";
    q.correctOption = 'B';
    q.chaosReward = 700;
    questions.push_back(q);

    // Pregunta 8
    q.questionText = "¿Cuál es el animal terrestre más grande?";
    q.optionA = "Elefante";
    q.optionB = "Jirafa";
    q.optionC = "Rinoceronte";
    q.optionD = "Hipopótamo";
    q.correctOption = 'A';
    q.chaosReward = 800;
    questions.push_back(q);

    // Pregunta 9
    q.questionText = "¿De qué país es la Torre de Pisa?";
    q.optionA = "Alemania";
    q.optionB = "Italia";
    q.optionC = "Francia";
    q.optionD = "Grecia";
    q.correctOption = 'B';
    q.chaosReward = 900;
    questions.push_back(q);

    // Pregunta 10
    q.questionText = "¿Cuál es el océano más grande?";
    q.optionA = "Atlántico";
    q.optionB = "Índico";
    q.optionC = "Pacífico";
    q.optionD = "Ártico";
    q.correctOption = 'C';
    q.chaosReward = 1000;
    questions.push_back(q);

    // Pregunta 11
    q.questionText = "¿Qué elemento químico tiene el símbolo 'O'?";
    q.optionA = "Oro";
    q.optionB = "Oxígeno";
    q.optionC = "Plata";
    q.optionD = "Osmio";
    q.correctOption = 'B';
    q.chaosReward = 1100;
    questions.push_back(q);

    // Pregunta 12
    q.questionText = "¿Quién fue el primer presidente de los Estados Unidos?";
    q.optionA = "Thomas Jefferson";
    q.optionB = "Abraham Lincoln";
    q.optionC = "George Washington";
    q.optionD = "John Adams";
    q.correctOption = 'C';
    q.chaosReward = 1200;
    questions.push_back(q);

    // Pregunta 13
    q.questionText = "¿Cuál es la montaña más alta del mundo?";
    q.optionA = "Monte Everest";
    q.optionB = "K2";
    q.optionC = "Kangchenjunga";
    q.optionD = "Mont Blanc";
    q.correctOption = 'A';
    q.chaosReward = 1300;
    questions.push_back(q);

    // Pregunta 14
    q.questionText = "¿Qué es el ADN?";
    q.optionA = "Ácido Desoxirribonucleico";
    q.optionB = "Ácido Ribonucleico";
    q.optionC = "Aminoácido";
    q.optionD = "Adenosín Trifosfato";
    q.correctOption = 'A';
    q.chaosReward = 1400;
    questions.push_back(q);

    // Pregunta 15
    q.questionText = "¿En qué país se encuentra la Gran Muralla?";
    q.optionA = "Japón";
    q.optionB = "China";
    q.optionC = "Mongolia";
    q.optionD = "India";
    q.correctOption = 'B';
    q.chaosReward = 1500;
    questions.push_back(q);

    // Pregunta 16
    q.questionText = "¿Quién inventó la bombilla?";
    q.optionA = "Nikola Tesla";
    q.optionB = "Thomas Edison";
    q.optionC = "Alexander Graham Bell";
    q.optionD = "Benjamin Franklin";
    q.correctOption = 'B';
    q.chaosReward = 1600;
    questions.push_back(q);

    // Pregunta 17
    q.questionText = "¿Qué instrumento se utiliza para medir la presión atmosférica?";
    q.optionA = "Termómetro";
    q.optionB = "Higrómetro";
    q.optionC = "Barómetro";
    q.optionD = "Anemómetro";
    q.correctOption = 'C';
    q.chaosReward = 1700;
    questions.push_back(q);

    // Pregunta 18
    q.questionText = "¿Cuál es el deporte nacional de Japón?";
    q.optionA = "Judo";
    q.optionB = "Fútbol";
    q.optionC = "Sumo";
    q.optionD = "Kendo";
    q.correctOption = 'C';
    q.chaosReward = 1800;
    questions.push_back(q);

    // Pregunta 19
    q.questionText = "¿Quién es el autor de 'Romeo y Julieta'?";
    q.optionA = "Charles Dickens";
    q.optionB = "William Shakespeare";
    q.optionC = "Jane Austen";
    q.optionD = "Geoffrey Chaucer";
    q.correctOption = 'B';
    q.chaosReward = 1900;
    questions.push_back(q);

    // Pregunta 20
    q.questionText = "¿Cuál es la capital de Australia?";
    q.optionA = "Sídney";
    q.optionB = "Melbourne";
    q.optionC = "Canberra";
    q.optionD = "Brisbane";
    q.correctOption = 'C';
    q.chaosReward = 2000;
    questions.push_back(q);
}

// Función de entrada principal
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};

    initQuestions();

    // Creación de los pinceles
    hBrushCorrect = CreateSolidBrush(LIME_GREEN);
    hBrushIncorrect = CreateSolidBrush(RGB(255, 0, 0));
    hBrushDefault = CreateSolidBrush(RGB(240, 240, 240));
    hBrushBlue = CreateSolidBrush(BLUE_COLOR);

    // Creación de las fuentes
    hFontQuestion = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontOption = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontChaos = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontProjectLabel = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontTeamLabel = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontCredits = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontEnjoy = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial")); // Fuente para ¡DISFRUTEN!


    // Configuración de la clase de ventana
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = TEXT("myWindowClass");
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("Error al registrar la clase de ventana."), TEXT("Error"), MB_ICONERROR | MB_OK);
        return -1;
    }

    // Creación de la ventana principal
    hMainWindow = CreateWindow(TEXT("myWindowClass"), TEXT("Quiz Game"), WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInst, NULL);

    if (!hMainWindow) {
        MessageBox(NULL, TEXT("Error al crear la ventana principal."), TEXT("Error"), MB_ICONERROR | MB_OK);
        return -1;
    }

    // Bucle de mensajes
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Liberar los recursos
    if (hBrushCorrect) DeleteObject(hBrushCorrect);
    if (hBrushIncorrect) DeleteObject(hBrushIncorrect);
    if (hBrushDefault) DeleteObject(hBrushDefault);
    if (hBrushBlue) DeleteObject(hBrushBlue);
    if (hFontQuestion) DeleteObject(hFontQuestion);
    if (hFontOption) DeleteObject(hFontOption);
    if (hFontChaos) DeleteObject(hFontChaos);
    if (hFontProjectLabel) DeleteObject(hFontProjectLabel);
    if (hFontTeamLabel) DeleteObject(hFontTeamLabel);
    if (hFontCredits) DeleteObject(hFontCredits);
    if (hFontEnjoy) DeleteObject(hFontEnjoy);

    return 0;
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            // Controles del juego (ocultos al inicio)
            hQuestionLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, NULL, NULL, NULL);
            SendMessage(hQuestionLabel, WM_SETFONT, (WPARAM)hFontQuestion, TRUE);
            hOptionA = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1, NULL, NULL);
            SendMessage(hOptionA, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionB = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)2, NULL, NULL);
            SendMessage(hOptionB, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionC = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)3, NULL, NULL);
            SendMessage(hOptionC, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionD = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)4, NULL, NULL);
            SendMessage(hOptionD, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hChaosLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_RIGHT, 0, 0, 0, 0, hWnd, NULL, NULL, NULL);
            SendMessage(hChaosLabel, WM_SETFONT, (WPARAM)hFontChaos, TRUE);

            // Controles de la pantalla de inicio
            hProjectLabel = CreateWindow(TEXT("Static"), TEXT("PROYECTO REALIZADO POR"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)IDC_PROJECT_LABEL, NULL, NULL);
            SendMessage(hProjectLabel, WM_SETFONT, (WPARAM)hFontProjectLabel, TRUE);

            hTeamLabel = CreateWindow(TEXT("Static"), TEXT("TEAM MULTITECHNEW"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)IDC_TEAM_LABEL, NULL, NULL);
            SendMessage(hTeamLabel, WM_SETFONT, (WPARAM)hFontTeamLabel, TRUE);
            
            hStartButton = CreateWindow(TEXT("Button"), TEXT("INICIAR"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDC_START_BUTTON, NULL, NULL);
            SendMessage(hStartButton, WM_SETFONT, (WPARAM)hFontQuestion, TRUE); // Usa una fuente grande para el botón

            // Nombres en la esquina inferior derecha
            std::string creditsText = "Sebastian Gallardo\nSneider Quintero\nManuel Perez\nLuiber Alvarado\nJosue Martinez\nPedro Sequera";
            hCreditsLabel = CreateWindow(TEXT("Static"), creditsText.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, 0, 0, 0, 0, hWnd, (HMENU)IDC_CREDITS_LABEL, NULL, NULL);
            SendMessage(hCreditsLabel, WM_SETFONT, (WPARAM)hFontCredits, TRUE);

            // Etiqueta "¡DISFRUTEN!"
            hEnjoyLabel = CreateWindow(TEXT("Static"), TEXT("¡DISFRUTEN!"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)IDC_ENJOY_LABEL, NULL, NULL);
            SendMessage(hEnjoyLabel, WM_SETFONT, (WPARAM)hFontEnjoy, TRUE); // Aplicar la fuente para "¡DISFRUTEN!"


            RECT rc;
            GetClientRect(hWnd, &rc);
            OnResize(rc.right - rc.left, rc.bottom - rc.top);
            UpdateChaosDisplay(); // Asegúrate de que el contador de chaos se inicialice aunque no se vea.

            break;
        }
        case WM_ERASEBKGND:
            return 1; // Indicamos que hemos manejado el borrado del fondo
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            // Dibujar el gradiente
            TRIVERTEX vertex[2];
            COLORREF startColor = BLUE_COLOR;
            COLORREF endColor = PURPLE_COLOR;
            vertex[0].x = 0;
            vertex[0].y = 0;
            vertex[0].Red = GetRValue(startColor) << 8;
            vertex[0].Green = GetGValue(startColor) << 8;
            vertex[0].Blue = GetBValue(startColor) << 8;
            vertex[0].Alpha = 0x0000;
            vertex[1].x = clientRect.right;
            vertex[1].y = clientRect.bottom;
            vertex[1].Red = GetRValue(endColor) << 8;
            vertex[1].Green = GetGValue(endColor) << 8;
            vertex[1].Blue = GetBValue(endColor) << 8;
            vertex[1].Alpha = 0x0000;
            GRADIENT_RECT gRect;
            gRect.UpperLeft = 0;
            gRect.LowerRight = 1;
            GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
            
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            // Configurar color de texto y fondo para etiquetas estáticas
            if ((HWND)lp == hQuestionLabel || (HWND)lp == hChaosLabel || (HWND)lp == hProjectLabel || (HWND)lp == hTeamLabel || (HWND)lp == hCreditsLabel || (HWND)lp == hEnjoyLabel) {
                SetBkMode((HDC)wp, TRANSPARENT); // Fondo transparente
                SetTextColor((HDC)wp, RGB(255, 255, 255)); // Texto blanco
                return (LRESULT)GetStockObject(NULL_BRUSH); // Usar pincel transparente
            }
            break;
        }
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wp;
            HWND hCtrl = (HWND)lp;
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));

            HBRUSH hButtonBrush = (HBRUSH)GetClassLongPtr(hCtrl, GCLP_HBRBACKGROUND);
            
            // Si el pincel no ha sido establecido o es el pincel por defecto de la ventana,
            // usamos hBrushBlue. Esto asegura que siempre haya un pincel personalizado.
            if (hButtonBrush == NULL || hButtonBrush == (HBRUSH)(COLOR_WINDOW + 1)) {
                return (LRESULT)hBrushBlue;
            } else {
                // Si ya hay un pincel personalizado (hBrushCorrect, hBrushIncorrect, hBrushBlue), lo usamos.
                return (LRESULT)hButtonBrush;
            }
        }
        case WM_SIZE: {
            int width = LOWORD(lp);
            int height = HIWORD(lp);
            OnResize(width, height);
            InvalidateRect(hWnd, NULL, TRUE); // Forzar repintado para el gradiente
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wp) == IDC_START_BUTTON) {
                // Lógica para el botón "INICIAR"
                HideStartScreen();
                ShowGameControls();
                SendMessage(hWnd, WM_COMMAND, (WPARAM)0, 0); // Inicia el juego
            } else if (LOWORD(wp) == 0) { // Cargar siguiente pregunta (esto es un truco para recargar)
                if (currentQuestionIndex < totalQuestions) {
                    // Restablecer el color de los botones a azul (por defecto de juego)
                    // y forzar el repintado.
                    SetClassLongPtr(hOptionA, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                    InvalidateRect(hOptionA, NULL, TRUE); UpdateWindow(hOptionA);
                    
                    SetClassLongPtr(hOptionB, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                    InvalidateRect(hOptionB, NULL, TRUE); UpdateWindow(hOptionB);
                    
                    SetClassLongPtr(hOptionC, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                    InvalidateRect(hOptionC, NULL, TRUE); UpdateWindow(hOptionC);
                    
                    SetClassLongPtr(hOptionD, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                    InvalidateRect(hOptionD, NULL, TRUE); UpdateWindow(hOptionD);
                    
                    EnableWindow(hOptionA, TRUE); EnableWindow(hOptionB, TRUE);
                    EnableWindow(hOptionC, TRUE); EnableWindow(hOptionD, TRUE);
                    
                    // ✨ FIX: Borrar el texto de la pregunta antes de cargar el siguiente
                    SetWindowTextA(hQuestionLabel, "");
                    InvalidateRect(hQuestionLabel, NULL, TRUE);
                    UpdateWindow(hQuestionLabel);
                    
                    std::string qText = questions[currentQuestionIndex].questionText;
                    std::string aText = "A) " + questions[currentQuestionIndex].optionA;
                    std::string bText = "B) " + questions[currentQuestionIndex].optionB;
                    std::string cText = "C) " + questions[currentQuestionIndex].optionC;
                    std::string dText = "D) " + questions[currentQuestionIndex].optionD;
                    
                    SetWindowTextA(hQuestionLabel, qText.c_str());
                    SetWindowTextA(hOptionA, aText.c_str());
                    SetWindowTextA(hOptionB, bText.c_str());
                    SetWindowTextA(hOptionC, cText.c_str());
                    SetWindowTextA(hOptionD, dText.c_str());
                    
                    currentQuestionIndex++;
                } else {
                    ShowResult();
                }
            } else { // Botón de opción presionado
                if (currentQuestionIndex > 0 && currentQuestionIndex <= totalQuestions) {
                    char selectedOption = ' ';
                    HWND hSelectedButton = NULL; // Guardar el handle del botón seleccionado
                    if (LOWORD(wp) == 1) { selectedOption = 'A'; hSelectedButton = hOptionA; }
                    else if (LOWORD(wp) == 2) { selectedOption = 'B'; hSelectedButton = hOptionB; }
                    else if (LOWORD(wp) == 3) { selectedOption = 'C'; hSelectedButton = hOptionC; }
                    else if (LOWORD(wp) == 4) { selectedOption = 'D'; hSelectedButton = hOptionD; }

                    // Deshabilitar todos los botones para evitar múltiples clics
                    EnableWindow(hOptionA, FALSE);
                    EnableWindow(hOptionB, FALSE);
                    EnableWindow(hOptionC, FALSE);
                    EnableWindow(hOptionD, FALSE);

                    // Si la respuesta es incorrecta, se termina el juego.
                    if (selectedOption != questions[currentQuestionIndex - 1].correctOption) {
                        std::string msg = "Juego terminado. Respuesta incorrecta. Chaos acumulado: " + intToString(totalChaos) + ".";
                        MessageBox(hMainWindow, msg.c_str(), "Fin del Juego", MB_ICONERROR | MB_OK);
                        DestroyWindow(hMainWindow);
                        break;
                    } else {
                        // Respuesta correcta
                        totalChaos += questions[currentQuestionIndex - 1].chaosReward;
                        UpdateChaosDisplay();
                        
                        // Resaltar el botón correcto en verde y hacer una pausa
                        SetClassLongPtr(hSelectedButton, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushCorrect);
                        InvalidateRect(hSelectedButton, NULL, TRUE);
                        UpdateWindow(hSelectedButton);
                        Sleep(500); // Pausa de 0.5 segundos para mostrar el color verde.

                        SendMessage(hWnd, WM_COMMAND, (WPARAM)0, 0); // Cargar siguiente pregunta
                    }
                }
            }
            break;
        }
        case WM_CLOSE: {
            DestroyWindow(hWnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

// Oculta los controles de la pantalla de inicio
void HideStartScreen() {
    ShowWindow(hProjectLabel, SW_HIDE);
    ShowWindow(hTeamLabel, SW_HIDE);
    ShowWindow(hStartButton, SW_HIDE);
    ShowWindow(hCreditsLabel, SW_HIDE);
    ShowWindow(hEnjoyLabel, SW_HIDE); // Ocultar también la etiqueta "¡DISFRUTEN!"
}

// Muestra los controles del juego principal
void ShowGameControls() {
    ShowWindow(hQuestionLabel, SW_SHOW);
    ShowWindow(hOptionA, SW_SHOW);
    ShowWindow(hOptionB, SW_SHOW);
    ShowWindow(hOptionC, SW_SHOW);
    ShowWindow(hOptionD, SW_SHOW);
    ShowWindow(hChaosLabel, SW_SHOW);
}

// Actualiza el texto del contador de Chaos
void UpdateChaosDisplay() {
    std::string chaosText = "Chaos: " + intToString(totalChaos);
    SetWindowTextA(hChaosLabel, chaosText.c_str());
}

// Muestra el resultado final del juego
void ShowResult() {
    std::stringstream ss;
    if (correctAnswers >= 15) { // Nota: `correctAnswers` no se está incrementando en tu código actual.
                                // Para que esta lógica funcione, deberías incrementar `correctAnswers`
                                // cuando una respuesta es correcta.
        ss << "¡Felicidades! Has ganado. Has respondido correctamente " << correctAnswers << " de " << totalQuestions << " preguntas y acumulado " << totalChaos << " Chaos.";
    } else {
        ss << "Has perdido. Has respondido correctamente " << correctAnswers << " de " << totalQuestions << " preguntas. Necesitas 15 para ganar. Chaos acumulado: " << totalChaos << ".";
    }
    std::string message = ss.str();
    MessageBox(hMainWindow, message.c_str(), "Fin del Juego", MB_OK);
    DestroyWindow(hMainWindow);
}

// Hace la interfaz "responsiva" al cambiar el tamaño de la ventana
void OnResize(int width, int height) {
    // Lógica para la pantalla de inicio
    if (IsWindowVisible(hStartButton)) {
        int projectLabelHeight = 40;
        int teamLabelHeight = 60;
        int startButtonHeight = 80;
        int creditsLabelHeight = 100;
        int enjoyLabelHeight = 50; // Altura para la etiqueta "¡DISFRUTEN!"

        // Posicionar "PROYECTO REALIZADO POR"
        SetWindowPos(hProjectLabel, NULL, (width - width) / 2, height / 4 - (projectLabelHeight / 2) - (teamLabelHeight / 2) - 10, width, projectLabelHeight, SWP_NOZORDER);

        // Posicionar "TEAM MULTITECHNEW"
        SetWindowPos(hTeamLabel, NULL, (width - width) / 2, height / 4 + (projectLabelHeight / 2) - (teamLabelHeight / 2) + 10, width, teamLabelHeight, SWP_NOZORDER);
        
        // Posicionar botón "INICIAR"
        int startButtonWidth = 250;
        SetWindowPos(hStartButton, NULL, (width - startButtonWidth) / 2, height / 2, startButtonWidth, startButtonHeight, SWP_NOZORDER);

        // Posicionar "¡DISFRUTEN!" debajo del botón "INICIAR"
        SetWindowPos(hEnjoyLabel, NULL, (width - width) / 2, height / 2 + startButtonHeight + 20, width, enjoyLabelHeight, SWP_NOZORDER);

        // Posicionar los nombres en la esquina inferior derecha
        int creditsWidth = 200;
        SetWindowPos(hCreditsLabel, NULL, width - creditsWidth - 20, height - creditsLabelHeight - 20, creditsWidth, creditsLabelHeight, SWP_NOZORDER);
    }

    // Lógica para los controles del juego
    if (IsWindowVisible(hQuestionLabel)) {
        int marginX = width / 10;
        int marginY = height / 10;
        int buttonWidth = width - (2 * marginX);
        int labelHeight = (height < 600) ? 80 : 100;
        int buttonBaseY = marginY + labelHeight + 20;
        int availableHeightForButtons = height - buttonBaseY - marginY;
        int buttonHeight = (availableHeightForButtons - (3 * 20)) / 4;

        if (buttonHeight < 40) buttonHeight = 40;
        if (labelHeight < 60) labelHeight = 60;
        
        int chaosLabelWidth = 150;
        int chaosLabelHeight = 30;
        SetWindowPos(hChaosLabel, NULL, width - chaosLabelWidth - 10, height - chaosLabelHeight - 10, chaosLabelWidth, chaosLabelHeight, SWP_NOZORDER);

        SetWindowPos(hQuestionLabel, NULL, marginX, marginY, buttonWidth, labelHeight, SWP_NOZORDER);
        SetWindowPos(hOptionA, NULL, marginX, buttonBaseY, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(hOptionB, NULL, marginX, buttonBaseY + buttonHeight + 20, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(hOptionC, NULL, marginX, buttonBaseY + (buttonHeight + 20) * 2, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(hOptionD, NULL, marginX, buttonBaseY + (buttonHeight + 20) * 3, buttonWidth, buttonHeight, SWP_NOZORDER);
    }
}
