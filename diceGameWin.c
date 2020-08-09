#include <windows.h>
#include "resource.h"
#include "diceGameWin.h"

INT APIENTRY WinMain(HINSTANCE hInstance,       // hInstance는 프로그램의 인스턴스
HINSTANCE hPrevInstance,   // hPrevInstance는 바로 전에 실행된 현재  //프로그램의 인스턴스
LPSTR lpCmdLine,	// lpCmpLine은 명령 행으로 입력된 프로그램 인수, 
// main에서의 argv
INT nCmdShow)		// 프로그램이 실행될 형태, 최소화, 보통 모양 같은 형태
{
	MSG iMessage;	// 윈도우 메시지지를 받기 위한 메시지 구조체 변수
	
	  // 다이얼 로그를 생성하는 API
	  // Return : 생성한 다이얼로그의 핸들
	HWND hDlgWnd = CreateDialog(hInstance,	// 프로그램 인스턴스
	MAKEINTRESOURCE(IDD_MAIN), // 다이얼로그의 리소스(ID)
	NULL,		// 부모 핸들(부모 윈도우가 없으므로 NULL)
	(DLGPROC)MainProc);  // 윈도우 메시지를 받을 프로시저의 이름
	ShowWindow(hDlgWnd, SW_SHOW);	// 생성한 다이얼 로그를 보여준다 (숨길땐 SW_HIDE)

	// 윈도우 어플리케이션이 실행되면 메시지 큐가 생성됨, 메시지 큐에는 윈도우 메시지가 저장 된다.
	// 메세지 루프를 통해 큐에 저장된 윈도우 메시지를 가져오고 해석후 해당 윈도우 프로시져에 보냄
	// GetMessage : 메시지 큐로부터 메시지를 가져옴, 만약 그 메시지가 WM_QUIT이면 0을 반환하고 
// 루프가 끝나  프로그램이 종료 된다.
	while(GetMessage(&iMessage, ZERO, ZERO, ZERO))
	{
	TranslateMessage(&iMessage); // 키보드 메시지를 번역. 즉 키를 눌렀다는
// WM_KEYDOWN이벤트가 들어오면, 그리고 그 키가
// 문자라면 이 함수는 문자가 입력 되었다는 메시지 
// WM_CHAR을 만듦.
	DispatchMessage(&iMessage);  // 해당하는 프로시져에 메시지를 보낸다
	}					//메시지 루프가 끝나면 프로그램이 종료 된다.
	return iMessage.wParam;
}


/* 
   윈도우의 메시지를 처리하는 메인 프로시져 (사용자의 키보드 입력, 마우스 클릭등의 메시지를 처리)
   윈도우 프로시져에 들어오는 기본적인 윈도우 메시지.

   1. WM_INITDIALOG : 처음 다이얼 로그가 생성될 때 들어오는 메시지이다. 여기서는 보통 프로그램의 초기화(예를 들어 메모리 초기화)를 구현할 때 활용한다.

   2. WM_COMMAND	: 이것은 다이얼로그에 있는 버튼 컨트롤을 클릭시 들어오는 메시지로 uMsg 에는 WM_COMMAND가, wParam에는 해당 버튼의 컨트롤 아이디가 들어온다. 

   3. WM_DESTROY	:
      WM_CLOSE		: 다이얼로그가 종료될 때 발생하는 이벤트로서 보통 이 메시지에서는 메모리 해제 등의 작업을 해주는 것이 일반적이다. 

   wParam과 lParam은 윈도우 메시지와 함께 그 메시지의 구체적인 정보가 담겨 오는 파라미터이다. 
   wParam -> Type WORD
   lParam -> Type LONG
*/

// 참고 1 : 컨트롤도 다이얼로그도 모두 "윈도우" 이다.
// 참고 2 : 윈도우 자체가 하나의 안정된 스레드 이다.
// 참고 3 : 프로시져 안에서 어떤 윈도우 메시지에 해당해 작업을 처리하고 나면 반드시 리턴
// 값을 넘겨줘야 하는데 그 작업이 성공했으면 TRUE, 성공하지 못했으면 FALSE를 리턴 
// 하는것이 정상이다.          

LRESULT CALLBACK MainProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	int Sum;

	srand((unsigned int)time(NULL));

	switch(iMessage)
	{
	case WM_INITDIALOG:
		InitDialogControl(hDlgWnd);
		InitGlovalVariable(hDlgWnd);
		SetDlgItemText(hDlgWnd, IDC_OUT, "주사위 굴리기 시작을 누르세요!");
		return TRUE;

	case WM_TIMER:
		switch(LOWORD(wParam))
		{
		case ROLLING:
//			return DisplayRollingDice(hDlgWnd);
//			return DisplayRollingDice(hDlgWnd, GetDlgDiceValue(hDlgWnd));

		default:
			break;
		} 
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDC_STARTGAME:
			InitDialogControl(hDlgWnd);
			InitGlovalVariable(hDlgWnd);
			SetDlgItemText(hDlgWnd, IDC_OUT, "게임을 새로 시작합니다. 주사위 굴리기 시작을 누르세요!");
//			SetTimer(hDlgWnd, ROLLING, 100, NULL);
			return TRUE;

		case IDC_STARTROLL:
			StartRoll = 'y';
			SetDlgItemText(hDlgWnd, IDC_OUT, "주사위 굴리기 끝을 누르십시오!");
//			SetTimer(hDlgWnd, ROLLING, 100, NULL);
			return TRUE;

		case IDC_STOPROLL:
			if (StartRoll == 'y')
			{
				Sum = RollDice(hDlgWnd);
				DisplayDice(hDlgWnd);
				SetToWinOrLose(Sum, hDlgWnd);
			}
			StartRoll = 'n';
			return TRUE;

		case IDC_QUITGAME: 
			KillTimer(hDlgWnd, ROLLING);
			PostQuitMessage(0);
			return TRUE;

		}
		return FALSE;

	case WM_CLOSE:
		KillTimer(hDlgWnd, ROLLING);
		PostQuitMessage(0);
		return TRUE;

	default:
		break;
	}
	return FALSE;
}

// 디스플레이를 이루는 컨트롤들을 초기화 하기 위한 함수 
VOID InitDialogControl(HWND hDlgWnd)
{
	// GetDlgItem은 부모 윈도우의 핸들과 컨트롤 아이디로 해당 컨트롤의 
	// 핸들을 가져오는 API. 컨트롤도 하나의 윈도우이다. 
	// 그렇기 때문에 ShowWindow로 컨트롤을 숨기거나 보이게 할 수 있다.
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGA2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGB2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGC2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGD2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGE2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGF2), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGG2), SW_HIDE);

	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGA), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGB), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGC), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGD), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGE), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGF), SW_HIDE);
	ShowWindow(GetDlgItem(hDlgWnd, IDC_SEGG), SW_HIDE);

	SetDlgItemText(hDlgWnd, IDC_FIRSTPOINT, NULL);
	SetDlgItemText(hDlgWnd, IDC_CURRENTPOINT, NULL);
}

int RollDice(HWND hDlgWnd)
{
	int Sum;

	while(1)
	{
		DiceA = rand();
		if((DiceA <= 0) || (7 <= DiceA)) continue;
		else break;
	}

	while(1)
	{
		DiceB = rand( );
		if((DiceB <= 0) || (7 <= DiceB)) continue;
		else break;
	}

	Sum = DiceA + DiceB;

	SetDlgItemInt(hDlgWnd, IDC_FIRSTPOINT, Score, TRUE);
	SetDlgItemInt(hDlgWnd, IDC_CURRENTPOINT, Sum, TRUE);

	return Sum;
}

void SetToWinOrLose(int Sum, HWND hDlgWnd)
{

	switch (SecondRoll)
	{
	case 'n':
		if ((Sum == 7) || (Sum == 11))
		{
			SetDlgItemText(hDlgWnd, IDC_OUT, "게임에 이겼습니다!!!");
			InitGlovalVariable(hDlgWnd);
		}
		else if ((Sum == 2) || (Sum == 3) || (Sum == 12))
			{
				SetDlgItemText(hDlgWnd, IDC_OUT, "게임에 졌습니다!!!");
				InitGlovalVariable(hDlgWnd);
			}
		else
			{
				SetDlgItemText(hDlgWnd, IDC_OUT, "2차 굴리기합니다. 주사위 굴리기 시작을 누르세요!");
				SecondRoll = 'y';
				Score = Sum;
			}
		return;

	case 'y':
		if (Score == Sum)
		{
			SetDlgItemText(hDlgWnd, IDC_OUT, "게임에 이겼습니다!!!");
			InitGlovalVariable(hDlgWnd);
		}
		else if (Sum == 7) 
			{
				SetDlgItemText(hDlgWnd, IDC_OUT, "게임에 졌습니다!!!");
				InitGlovalVariable(hDlgWnd);
			}
		else
			{
				SetDlgItemText(hDlgWnd, IDC_OUT, "2차 굴리기합니다. 주사위 굴리기 시작을 누르세요!");
				SecondRoll = 'y';
			}
		return;

	default:
		SetDlgItemText(hDlgWnd, IDC_OUT, "논리 오류 게임 종료!!!");
		return;
	}
		
	return;
}

void InitGlovalVariable(HWND hDlgWnd)
{
	SecondRoll = 'n';
	Score = 0;

	if (StartRoll == 'n')
	{
		SetDlgItemInt(hDlgWnd, IDC_FIRSTPOINT, NULL, TRUE);
		SetDlgItemInt(hDlgWnd, IDC_CURRENTPOINT, NULL, TRUE);
	}

	return;
}

BOOL DisplayDice(HWND hDlgWnd)
{
	int iBuffer[8] = {ZERO};
	int iSegBufferA[8] = {ZERO, IDC_SEGA, IDC_SEGB, IDC_SEGC,
								IDC_SEGD, IDC_SEGE, IDC_SEGF, IDC_SEGG},
		iSegBufferB[8] = {ZERO, IDC_SEGA2, IDC_SEGB2, IDC_SEGC2,
								IDC_SEGD2, IDC_SEGE2, IDC_SEGF2, IDC_SEGG2};

	int i;
//	int Test= 1;

//	switch (Test)
	switch (DiceB)
	{
	case 1:	
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		break;

	case 2:
		iBuffer[1] = 1;
		iBuffer[2] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[7] = 1;
		break;

	case 3:
		iBuffer[1] = 1;
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[7] = 1;
		break;

	case 4:
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	case 5:
		iBuffer[1] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	case 6:
		iBuffer[1] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	default: 
		SetDlgItemText(hDlgWnd, IDC_OUT, "주사위 값 오류!!!");
		iBuffer[1] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;
	}

	for(i = 1; i <= 8; i++)
	{
		if (iBuffer[i] == 1)
			ShowWindow(GetDlgItem(hDlgWnd, iSegBufferB[i]), SW_SHOW);
		else
			ShowWindow(GetDlgItem(hDlgWnd, iSegBufferB[i]), SW_HIDE);
	}

	for(i = 0; i <= 7; i++)
		iBuffer[i] = ZERO;

	switch (DiceA)
	{
	case 1:	
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		break;

	case 2:
		iBuffer[1] = 1;
		iBuffer[2] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[7] = 1;
		break;

	case 3:
		iBuffer[1] = 1;
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[7] = 1;
		break;

	case 4:
		iBuffer[2] = 1;
		iBuffer[3] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	case 5:
		iBuffer[1] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	case 6:
		iBuffer[1] = 1;
		iBuffer[3] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;

	default: 
		SetDlgItemText(hDlgWnd, IDC_OUT, "주사위 값 오류!!!");
		iBuffer[1] = 1;
		iBuffer[4] = 1;
		iBuffer[5] = 1;
		iBuffer[6] = 1;
		iBuffer[7] = 1;
		break;
	}

	for(i = 1; i <= 8; i++)
	{
		if (iBuffer[i] == 1)
			ShowWindow(GetDlgItem(hDlgWnd, iSegBufferA[i]), SW_SHOW);
		else
			ShowWindow(GetDlgItem(hDlgWnd, iSegBufferA[i]), SW_HIDE);
	}

	for(i = 0; i <= 7; i++)
		iBuffer[i] = ZERO;

	return TRUE;
}

