#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <winuser.h>
#include <commctrl.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

// Define los colores específicos
#define PURPLE_COLOR       RGB(140, 82, 255) // Morado (#8c52ff)
#define BLUE_COLOR         RGB(0, 0, 255)   // Azul puro
#define LIME_GREEN         RGB(0, 255, 0)   // Verde brillante para la respuesta correcta

// Colores para el gradiente de fondo
#define GRADIENT_START_COLOR PURPLE_COLOR
#define GRADIENT_END_COLOR   RGB(0, 0, 128)  // Un azul más oscuro para el final del gradiente

// Identificadores para los controles
#define IDC_START_BUTTON    1000
#define IDC_PROJECT_LABEL   1001 // "PROYECTO REALIZADO POR"
#define IDC_TEAM_LABEL      1002 // "TEAM MULTITECHNEW"
#define IDC_CREDITS_LABEL   1003 // Nombres de los integrantes
#define IDC_ENJOY_LABEL     1004 // "¡DISFRUTEN!"
#define IDC_50_50_BUTTON    1005 // Botón 50/50
#define IDC_BUTTON_HINT     1008 // Botón Hint
#define IDC_RETIRE_BUTTON   1009 // Botón de Retirarse

// Declaración de handles y variables globales
HWND hMainWindow;
HWND hQuestionLabel;
HWND hOptionA;
HWND hOptionB;
HWND hOptionC;
HWND hOptionD;
HWND hChaosLabel; // Etiqueta del contador de Chaos
HWND h5050Button; // Botón 50/50
HWND hHintButton; // Botón Hint
HWND hRetireButton; // Botón de Retirarse

// Controles de la pantalla de inicio
HWND hProjectLabel; // "PROYECTO REALIZADO POR"
HWND hTeamLabel;    // "TEAM MULTITECHNEW"
HWND hStartButton;
HWND hCreditsLabel; // Nombres de los integrantes
HWND hEnjoyLabel;   // Etiqueta para "¡DISFRUTEN!"

int currentQuestionIndex = 0;
int correctAnswers = 0;
int totalChaos = 0; // Variable para el contador de Chaos
bool fiftyFiftyUsed = false; // Bandera para el uso del 50/50
bool hintUsed = false; // Bandera para el uso del Hint

const int totalQuestions = 20;

// Pinceles globales para los colores sólidos de los botones
HBRUSH hBrushCorrect = NULL;
HBRUSH hBrushBlue = NULL;

// Fuentes globales para el texto
HFONT hFontQuestion = NULL;
HFONT hFontOption = NULL;
HFONT hFontChaos = NULL;
HFONT hFontProjectLabel = NULL;
HFONT hFontTeamLabel = NULL;
HFONT hFontCredits = NULL;
HFONT hFontEnjoy = NULL;
HFONT hFontHelpers = NULL; // Nueva fuente para los botones de ayuda

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
void LoadNextQuestion(HWND hWnd);
void Use5050();
void UseHint();
void ShowRetireResult(); // Nueva función para mostrar resultado al retirarse
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void ShowResult();
void UpdateChaosDisplay();
void ShowGameControls();
void HideStartScreen();
void ShowStartScreen();

// Función auxiliar para convertir un entero a string
std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void initQuestions() {
    Question q;
    // Pregunta 1
    q.questionText = "1) ¿Cuál es la extensión de archivo estándar para un programa en C++?";
    q.optionA = ".cp"; q.optionB = ".cxxp"; q.optionC = ".exe"; q.optionD = ".cpp";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 2
    q.questionText = "2) ¿Qué palabra clave se utiliza para declarar una variable constante en C++?";
    q.optionA = "define"; q.optionB = "constant"; q.optionC = "static"; q.optionD = "const";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 3
    q.questionText = "3) ¿Qué símbolo se utiliza para terminar una instrucción en C++?";
    q.optionA = ","; q.optionB = "."; q.optionC = ":"; q.optionD = ";";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 4
    q.questionText = "4) ¿Qué se usa para imprimir en la consola en C++?";
    q.optionA = "cout"; q.optionB = "echo"; q.optionC = "print"; q.optionD = "display";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 5
    q.questionText = "5) ¿Qué biblioteca se debe incluir para usar cout?";
    q.optionA = "#include <stdio.h>"; q.optionB = "#include <string>"; q.optionC = " #include <iostream>"; q.optionD = "#include <conio.h>";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 6
    q.questionText = "6) ¿Cuál es el tipo de dato para números enteros en C++?";
    q.optionA = "float"; q.optionB = "char"; q.optionC = "int"; q.optionD = "bool Ángel";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 7
    q.questionText = "7)¿Qué palabra clave se usa para definir una función en C++?";
    q.optionA = "procedure"; q.optionB = "void"; q.optionC = "define"; q.optionD = "func";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 8
    q.questionText = "8) ¿Cuál es el operador de comparación de igualdad en C++?";
    q.optionA = "!="; q.optionB = "=="; q.optionC = "="; q.optionD = "===";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 9
    q.questionText = "9) ¿Qué tipo de dato se usa para almacenar texto en C++?";
    q.optionA = "string"; q.optionB = "text"; q.optionC = "word"; q.optionD = "char";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 10
    q.questionText = "10) ¿Qué estructura se usa para repetir instrucciones en C++?";
    q.optionA = "repeat"; q.optionB = "iterate"; q.optionC = "for"; q.optionD = "loop";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 11
    q.questionText = "11)¿Qué elemento químico tiene el símbolo 'O'?";
    q.optionA = "Oro"; q.optionB = "Oxígeno"; q.optionC = "Plata"; q.optionD = "Osmio";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 12
    q.questionText = "12) ¿Quién fue el primer presidente de los Estados Unidos?";
    q.optionA = "Thomas Jefferson"; q.optionB = "Abraham Lincoln"; q.optionC = "George Washington"; q.optionD = "John Adams";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 13
    q.questionText = "13) ¿Cuanto es 77 + 33?";
    q.optionA = "110"; q.optionB = "100"; q.optionC = "108"; q.optionD = "105";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 14
    q.questionText = "14) ¿Cuál es el valor de x si 2x - 5 = 15?";
    q.optionA = "8"; q.optionB = "9"; q.optionC = "10"; q.optionD = "11";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 15
    q.questionText = "15) ¿Cuál es el valor de x si 3x + 7 = 19?";
    q.optionA = "3"; q.optionB = "4"; q.optionC = "5"; q.optionD = "6";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 16
    q.questionText = "16) ¿Quién inventó la bombilla?";
    q.optionA = "Nikola Tesla"; q.optionB = "Thomas Edison"; q.optionC = "Alexander Graham Bell"; q.optionD = "Benjamin Franklin";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 17
    q.questionText = "17) ¿Qué instrumento se utiliza para medir la presión atmosférica?";
    q.optionA = "Termómetro"; q.optionB = "Higrómetro"; q.optionC = "Barómetro"; q.optionD = "Anemómetro";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 18
    q.questionText = "18) ¿La costumbre jurídica es:?";
    q.optionA = "Una conducta contraria al derecho."; q.optionB = "Una relación jurídica.."; q.optionC = "Una ley especial."; q.optionD = "Una fuente próxima del derecho.";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 19
    q.questionText = "19) ¿Una de las características de la normal jurídica es la: ?";
    q.optionA = "Generalidad."; q.optionB = "Autonomía."; q.optionC = "Unilateralidad."; q.optionD = "Interioridad";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 20
    q.questionText = "20)¿Cuál es la capital de Australia?";
    q.optionA = "Sídney"; q.optionB = "Melbourne"; q.optionC = "Canberra"; q.optionD = "Brisbane";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
}

// Función de entrada principal
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};

    srand(time(0)); // Inicializa la semilla del generador de números aleatorios
    initQuestions();

    // Creación de los pinceles
    hBrushCorrect = CreateSolidBrush(LIME_GREEN);
    hBrushBlue = CreateSolidBrush(BLUE_COLOR);
    
    // Creación de las fuentes
    hFontQuestion = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontOption = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontChaos = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontProjectLabel = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontTeamLabel = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Times New Roman"));
    hFontCredits = CreateFont(26, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontEnjoy = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontHelpers = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));


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

    // Creación de la ventana principal con nuevas dimensiones
    hMainWindow = CreateWindow(TEXT("myWindowClass"), TEXT("Quiz Game"), WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
                               CW_USEDEFAULT, CW_USEDEFAULT, 1200, 900, NULL, NULL, hInst, NULL);

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
    if (hBrushBlue) DeleteObject(hBrushBlue);
    if (hFontQuestion) DeleteObject(hFontQuestion);
    if (hFontOption) DeleteObject(hFontOption);
    if (hFontChaos) DeleteObject(hFontChaos);
    if (hFontProjectLabel) DeleteObject(hFontProjectLabel);
    if (hFontTeamLabel) DeleteObject(hFontTeamLabel);
    if (hFontCredits) DeleteObject(hFontCredits);
    if (hFontEnjoy) DeleteObject(hFontEnjoy);
    if (hFontHelpers) DeleteObject(hFontHelpers);

    return 0;
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            // Controles del juego (posiciones ajustadas para la nueva ventana)
            hQuestionLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_CENTER, 150, 80, 900, 120, hWnd, NULL, NULL, NULL);
            SendMessage(hQuestionLabel, WM_SETFONT, (WPARAM)hFontQuestion, TRUE);
            hOptionA = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 250, 900, 60, hWnd, (HMENU)1, NULL, NULL);
            SendMessage(hOptionA, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionB = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 340, 900, 60, hWnd, (HMENU)2, NULL, NULL);
            SendMessage(hOptionB, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionC = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 430, 900, 60, hWnd, (HMENU)3, NULL, NULL);
            SendMessage(hOptionC, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionD = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 520, 900, 60, hWnd, (HMENU)4, NULL, NULL);
            SendMessage(hOptionD, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hChaosLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_RIGHT, 980, 840, 180, 30, hWnd, NULL, NULL, NULL);
            SendMessage(hChaosLabel, WM_SETFONT, (WPARAM)hFontChaos, TRUE);
            h5050Button = CreateWindow(TEXT("Button"), TEXT("50/50"), WS_CHILD, 50, 800, 100, 40, hWnd, (HMENU)IDC_50_50_BUTTON, NULL, NULL);
            SendMessage(h5050Button, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);

            // Nuevos botones de ayuda
            hHintButton = CreateWindow(TEXT("Button"), TEXT("Localizar"), WS_CHILD, 170, 800, 100, 40, hWnd, (HMENU)IDC_BUTTON_HINT, NULL, NULL);
            SendMessage(hHintButton, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);

            hRetireButton = CreateWindow(TEXT("Button"), TEXT("Retirarse"), WS_CHILD, 290, 800, 100, 40, hWnd, (HMENU)IDC_RETIRE_BUTTON, NULL, NULL);
            SendMessage(hRetireButton, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);


            // Controles de la pantalla de inicio (posiciones ajustadas)
            hProjectLabel = CreateWindow(TEXT("Static"), TEXT("PROYECTO REALIZADO POR"), WS_CHILD | SS_CENTER, 0, 180, 1200, 50, hWnd, (HMENU)IDC_PROJECT_LABEL, NULL, NULL);
            SendMessage(hProjectLabel, WM_SETFONT, (WPARAM)hFontProjectLabel, TRUE);

            hTeamLabel = CreateWindow(TEXT("Static"), TEXT("TEAM MULTITECHNEW"), WS_CHILD | SS_CENTER, 0, 250, 1200, 80, hWnd, (HMENU)IDC_TEAM_LABEL, NULL, NULL);
            SendMessage(hTeamLabel, WM_SETFONT, (WPARAM)hFontTeamLabel, TRUE);
            
            hStartButton = CreateWindow(TEXT("Button"), TEXT("INICIAR"), WS_CHILD, 475, 400, 250, 80, hWnd, (HMENU)IDC_START_BUTTON, NULL, NULL);
            SendMessage(hStartButton, WM_SETFONT, (WPARAM)hFontQuestion, TRUE);

            // Nombres en la esquina inferior derecha
            std::string creditsText = "Sebastian Gallardo\nSneider Quintero\nManuel Perez\nLuiber Alvarado\nJosue Martinez\nPedro Sequera\nJose Fuentes";
            hCreditsLabel = CreateWindow(TEXT("Static"), creditsText.c_str(), WS_CHILD | SS_RIGHT, 970, 650, 200, 190, hWnd, (HMENU)IDC_CREDITS_LABEL, NULL, NULL);
            SendMessage(hCreditsLabel, WM_SETFONT, (WPARAM)hFontCredits, TRUE);

            // Etiqueta "¡DISFRUTEN!"
            hEnjoyLabel = CreateWindow(TEXT("Static"), TEXT("¡DISFRUTEN!"), WS_CHILD | SS_CENTER, 0, 700, 1200, 60, hWnd, (HMENU)IDC_ENJOY_LABEL, NULL, NULL);
            SendMessage(hEnjoyLabel, WM_SETFONT, (WPARAM)hFontEnjoy, TRUE);

            HideStartScreen();
            ShowStartScreen();
            
            break; 
        }
        case WM_ERASEBKGND:
            return 1; 
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            // Dibujar el gradiente de fondo
            for (int i = 0; i < clientRect.bottom; ++i) {
                COLORREF currentColor;
                int r1 = GetRValue(GRADIENT_START_COLOR);
                int g1 = GetGValue(GRADIENT_START_COLOR);
                int b1 = GetBValue(GRADIENT_START_COLOR);

                int r2 = GetRValue(GRADIENT_END_COLOR);
                int g2 = GetGValue(GRADIENT_END_COLOR);
                int b2 = GetBValue(GRADIENT_END_COLOR);

                int r = r1 + (r2 - r1) * i / clientRect.bottom;
                int g = g1 + (g2 - g1) * i / clientRect.bottom;
                int b = b1 + (b2 - b1) * i / clientRect.bottom;

                currentColor = RGB(r, g, b);

                HBRUSH hBrushLine = CreateSolidBrush(currentColor);
                RECT lineRect = { clientRect.left, i, clientRect.right, i + 1 };
                FillRect(hdc, &lineRect, hBrushLine);
                DeleteObject(hBrushLine);
            }

            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            if ((HWND)lp == hQuestionLabel || (HWND)lp == hChaosLabel || (HWND)lp == hProjectLabel || (HWND)lp == hTeamLabel || (HWND)lp == hCreditsLabel || (HWND)lp == hEnjoyLabel) {
                SetBkMode((HDC)wp, TRANSPARENT);
                SetTextColor((HDC)wp, RGB(255, 255, 255));
                return (LRESULT)GetStockObject(NULL_BRUSH);
            }
            break;
        }
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wp;
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)hBrushBlue;
        }
        case WM_COMMAND: {
            if (LOWORD(wp) == IDC_START_BUTTON) {
                HideStartScreen();
                ShowGameControls();
                LoadNextQuestion(hWnd);
            } else if (LOWORD(wp) == IDC_50_50_BUTTON) {
                if (!fiftyFiftyUsed) {
                    Use5050();
                    fiftyFiftyUsed = true;
                    EnableWindow(h5050Button, FALSE);
                    ShowWindow(h5050Button, SW_HIDE);
                }
            } else if (LOWORD(wp) == IDC_BUTTON_HINT) {
                if (!hintUsed) {
                    UseHint();
                    hintUsed = true;
                    EnableWindow(hHintButton, FALSE);
                    ShowWindow(hHintButton, SW_HIDE);
                }
            } else if (LOWORD(wp) == IDC_RETIRE_BUTTON) {
                ShowRetireResult();
            }
            else if (LOWORD(wp) >= 1 && LOWORD(wp) <= 4) {
                if (currentQuestionIndex > 0 && currentQuestionIndex <= questions.size()) {
                    char selectedOption = ' ';
                    if (LOWORD(wp) == 1) { selectedOption = 'A'; }
                    else if (LOWORD(wp) == 2) { selectedOption = 'B'; }
                    else if (LOWORD(wp) == 3) { selectedOption = 'C'; }
                    else if (LOWORD(wp) == 4) { selectedOption = 'D'; }

                    if (selectedOption != questions[currentQuestionIndex - 1].correctOption) {
                        std::string msg = "Juego terminado. Respuesta incorrecta. Chaos acumulado: " + intToString(totalChaos) + ".";
                        MessageBox(hMainWindow, msg.c_str(), "Fin del Juego", MB_ICONERROR | MB_OK);
                        DestroyWindow(hMainWindow);
                        break;
                    } else {
                        correctAnswers++;
                        int chaosGained = questions[currentQuestionIndex - 1].chaosReward;
                        // El multiplicador 2X se ha eliminado.
                        totalChaos += chaosGained;
                        
                        ShowWindow(hQuestionLabel, SW_HIDE);
                        ShowWindow(hOptionA, SW_HIDE);
                        ShowWindow(hOptionB, SW_HIDE);
                        ShowWindow(hOptionC, SW_HIDE);
                        ShowWindow(hOptionD, SW_HIDE);
                        ShowWindow(hChaosLabel, SW_HIDE);
                        ShowWindow(h5050Button, SW_HIDE);
                        ShowWindow(hHintButton, SW_HIDE);
                        ShowWindow(hRetireButton, SW_HIDE);

                        SetClassLongPtr(hOptionA, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionB, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionC, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionD, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);

                        Sleep(500); 
                        
                        LoadNextQuestion(hWnd);
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

// Carga la siguiente pregunta o muestra el resultado final
void LoadNextQuestion(HWND hWnd) {
    if (currentQuestionIndex < questions.size()) {
        EnableWindow(hOptionA, TRUE); ShowWindow(hOptionA, SW_SHOW);
        EnableWindow(hOptionB, TRUE); ShowWindow(hOptionB, SW_SHOW);
        EnableWindow(hOptionC, TRUE); ShowWindow(hOptionC, SW_SHOW);
        EnableWindow(hOptionD, TRUE); ShowWindow(hOptionD, SW_SHOW);
        ShowWindow(hQuestionLabel, SW_SHOW);
        UpdateChaosDisplay(); 
        
        // Vuelve a mostrar y habilitar los botones de ayuda si no se han usado
        if (!fiftyFiftyUsed) { ShowWindow(h5050Button, SW_SHOW); EnableWindow(h5050Button, TRUE); }
        else { ShowWindow(h5050Button, SW_HIDE); EnableWindow(h5050Button, FALSE); }
        
        if (!hintUsed) { ShowWindow(hHintButton, SW_SHOW); EnableWindow(hHintButton, TRUE); }
        else { ShowWindow(hHintButton, SW_HIDE); EnableWindow(hHintButton, FALSE); }

        ShowWindow(hRetireButton, SW_SHOW);
        EnableWindow(hRetireButton, TRUE);


        SetWindowTextA(hQuestionLabel, questions[currentQuestionIndex].questionText.c_str());
        SetWindowTextA(hOptionA, ("A) " + questions[currentQuestionIndex].optionA).c_str());
        SetWindowTextA(hOptionB, ("B) " + questions[currentQuestionIndex].optionB).c_str());
        SetWindowTextA(hOptionC, ("C) " + questions[currentQuestionIndex].optionC).c_str());
        SetWindowTextA(hOptionD, ("D) " + questions[currentQuestionIndex].optionD).c_str());
        
        currentQuestionIndex++;
    } else {
        ShowResult();
    }
}

// Función para usar la ayuda 50/50
void Use5050() {
    if (currentQuestionIndex > 0) {
        Question currentQ = questions[currentQuestionIndex - 1];
        char correctOption = currentQ.correctOption;
        
        std::vector<HWND> incorrectButtons;
        if (correctOption != 'A') incorrectButtons.push_back(hOptionA);
        if (correctOption != 'B') incorrectButtons.push_back(hOptionB);
        if (correctOption != 'C') incorrectButtons.push_back(hOptionC);
        if (correctOption != 'D') incorrectButtons.push_back(hOptionD);
        
        // Seleccionar dos botones incorrectos al azar para ocultar
        int randomIndex1 = rand() % incorrectButtons.size();
        HWND buttonToHide1 = incorrectButtons[randomIndex1];
        incorrectButtons.erase(incorrectButtons.begin() + randomIndex1);
        
        int randomIndex2 = rand() % incorrectButtons.size();
        HWND buttonToHide2 = incorrectButtons[randomIndex2];

        ShowWindow(buttonToHide1, SW_HIDE);
        ShowWindow(buttonToHide2, SW_HIDE);
    }
}

// Función para usar la ayuda Hint
void UseHint() {
    if (currentQuestionIndex > 0) {
        Question currentQ = questions[currentQuestionIndex - 1];
        char correctOption = currentQ.correctOption;
        std::string hint = "Una de las opciones incorrectas es: ";

        std::vector<char> incorrectOptions;
        if (correctOption != 'A') incorrectOptions.push_back('A');
        if (correctOption != 'B') incorrectOptions.push_back('B');
        if (correctOption != 'C') incorrectOptions.push_back('C');
        if (correctOption != 'D') incorrectOptions.push_back('D');

        int randomIndex = rand() % incorrectOptions.size();
        hint += incorrectOptions[randomIndex];
        MessageBox(hMainWindow, hint.c_str(), "Ayuda Hint", MB_ICONINFORMATION | MB_OK);
    }
}

// Función para retirarse y mostrar el resultado
void ShowRetireResult() {
    std::string message = "Has decidido retirarte.\n";
    // Se resta 1 a currentQuestionIndex porque ya se incrementó al cargar la pregunta
    message += "Has respondido correctamente " + intToString(correctAnswers) + " de " + intToString(currentQuestionIndex - 1) + " preguntas.\n";
    message += "Chaos acumulado: " + intToString(totalChaos) + ".";
    MessageBox(hMainWindow, message.c_str(), "Juego terminado", MB_OK);
    DestroyWindow(hMainWindow);
}

// Oculta los controles de la pantalla de inicio
void HideStartScreen() {
    ShowWindow(hProjectLabel, SW_HIDE);
    ShowWindow(hTeamLabel, SW_HIDE);
    ShowWindow(hStartButton, SW_HIDE);
    ShowWindow(hCreditsLabel, SW_HIDE);
    ShowWindow(hEnjoyLabel, SW_HIDE);
}

// Muestra los controles del juego principal
void ShowGameControls() {
    ShowWindow(hQuestionLabel, SW_SHOW);
    ShowWindow(hOptionA, SW_SHOW);
    ShowWindow(hOptionB, SW_SHOW);
    ShowWindow(hOptionC, SW_SHOW);
    ShowWindow(hOptionD, SW_SHOW);
    UpdateChaosDisplay();
    if (!fiftyFiftyUsed) {
        ShowWindow(h5050Button, SW_SHOW);
        EnableWindow(h5050Button, TRUE);
    } else {
        ShowWindow(h5050Button, SW_HIDE);
        EnableWindow(h5050Button, FALSE);
    }
    
    // El botón 2X ha sido eliminado.
    ShowWindow(hHintButton, SW_SHOW);
    if (!hintUsed) {
        EnableWindow(hHintButton, TRUE);
    } else {
        EnableWindow(hHintButton, FALSE);
    }

    ShowWindow(hRetireButton, SW_SHOW);
    EnableWindow(hRetireButton, TRUE);
}

// Actualiza el texto del contador de Chaos
void UpdateChaosDisplay() {
    ShowWindow(hChaosLabel, SW_SHOW);
    std::string chaosText = "Chaos: " + intToString(totalChaos);
    SetWindowTextA(hChaosLabel, chaosText.c_str());
}

// Muestra el resultado final del juego
void ShowResult() {
    std::stringstream ss;
    if (correctAnswers >= 15) {
        ss << "¡Felicidades! Has respondido todo correctamente.\n";
        ss << "Has respondido correctamente " << correctAnswers << " de " << totalQuestions << " preguntas.\n";
        ss << "Chaos acumulado: " << totalChaos << ".";
    } else {
        ss << "Has perdido :C.\n";
        ss << "Necesitas al menos 15 respuestas correctas para ganar.\n";
        ss << "Has respondido correctamente " << correctAnswers << " de " << totalQuestions << " preguntas.\n";
        ss << "Chaos acumulado: " << totalChaos << ".";
    }
    std::string message = ss.str();
    MessageBox(hMainWindow, message.c_str(), "Fin del Juego", MB_OK);
    DestroyWindow(hMainWindow);
}


// Función para inicializar y mostrar los controles de la pantalla de inicio
void ShowStartScreen() {
    ShowWindow(hProjectLabel, SW_SHOW);
    ShowWindow(hTeamLabel, SW_SHOW);
    ShowWindow(hStartButton, SW_SHOW);
    ShowWindow(hCreditsLabel, SW_SHOW);
    ShowWindow(hEnjoyLabel, SW_SHOW);
    ShowWindow(hChaosLabel, SW_HIDE);
    ShowWindow(h5050Button, SW_HIDE);
    ShowWindow(hHintButton, SW_HIDE);
    ShowWindow(hRetireButton, SW_HIDE);
}
