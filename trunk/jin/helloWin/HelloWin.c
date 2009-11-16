#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;    // �����T���B�z�禡��prototype
#pragma comment( lib, "Winmm.lib" ) // for PlaySound function


// Windows �{���Ĥ@�Ӷi�J�I WinMain(...)  

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
// �ѼƸѻ�:
//    hInstance => �ثe process hInstance �� Handle
//    hPrevInstance => �û��O NULL
//    szCmdLine => �R�O�C
//    iCmdShow => ���w�ثe�����p��Q��� (SW_HIDE, SW_MAXIMIZE, SW_MINIMIZE, SW_RESTORE)
{
     static TCHAR szAppName[] = TEXT ("HelloWin") ;
     HWND         hwnd ;
     MSG          msg ;

     // ===================== Step 1: �إߨåB���U Window Class =========================
     WNDCLASS     wndclass ;
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;                  // << -- �]�w�����T���B�z�禡��m
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;                // << -- ���w�ثe�� class name

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
    
     // ===================== Step 2: �إߵ����åB�Ǧ^ window handle ===================== 
     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("The Hello Program"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          CW_USEDEFAULT,              // initial x position
                          CW_USEDEFAULT,              // initial y position
                          CW_USEDEFAULT,              // initial x size
                          CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
     
     // ===================== Step 3: �������ܥX�� =====================================
     ShowWindow (hwnd, iCmdShow) ; // �]�w��ܤ覡  SW_SHOW, SW_MAXIMIZE, SW_MINIMIZE ��
     UpdateWindow (hwnd) ; // �e�X WM_PAINT message ��ثe�� thread message queue
     
     // ===================== Step 4: Message - Loop ������ ==============================
     BOOL bRet;
     UINT wMsgFilterMin=0; // ���w�̤p�i������ message ���X
     UINT wMsgFilterMax=0; // ���w�̤j�i������ message ���X 
                           // (���ӦP�� 0 ��,��� GetMessage �|�Ǧ^�Ҧ��� message)
                           // WM_QUIT ���� Filter ������ -> �H����������������D�X�{
     while( (bRet = GetMessage( &msg, NULL, wMsgFilterMin, wMsgFilterMax )) != 0)
     { 
         if (bRet == -1)
         {
             // handle the error and possibly exit
         }
         else
         {
             TranslateMessage(&msg); 
             DispatchMessage(&msg); 
         }
     }

     // �ھ� MSDN ��ĳ: GetMessage �o�Ϳ��~�ɷ|�Ǧ^ -1
     //                 �ҥH�쥻���{���אּ�W�����g�k
     // �ѦҸ��: ms-help://MS.MSDNQTR.2004JAN.1033/winui/winui/windowsuserinterface/windowing/messagesandmessagequeues/messagesandmessagequeuesreference/messagesandmessagequeuesfunctions/getmessage.htm
     /*
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     */
     return msg.wParam ;
}

// �����T���B�z�禡
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     
     switch (message)
     {
     case WM_CREATE:    // << -- ������Q�إ߮�, �ƥ�B�z�{���X
          PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
          return 0 ;
          
     case WM_PAINT:     // << -- ������Q�n�D���sø�s��, �ƥ�B�z�{���X
          hdc = BeginPaint (hwnd, &ps) ;  // ���ثe�������ǳ�ø�Ϫ��ʧ@,�öǦ^ø�ϥΪ� device context
          GetClientRect (hwnd, &rect) ;
          DrawText (hdc, TEXT ("Hello, Windows!"), -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;  // ���wø�s�榡  (���,������)         
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ; // �e�X WM_QUIT �� thread message queue
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}