#include <stdlib.h>		// strcat, strcpy등을 사용하기 위한 헤더파일 
#include <time.h>

#define ZERO		0
#define ROLLING	100	// 타이머 이벤트 정의

static int Score = 0;
static int DiceA = 0;
static int DiceB = 0;
static char SecondRoll = 'n';
static char StartRoll = 'n';

INT  ChecktheInputDatafromPort		(VOID);
INT  UpdateBinaryDigittoDexDigit		(HWND hDlg, INT nInputNum);
BOOL DisplayInputNum			(HWND hDlg, INT nInputNum);
VOID InitDialogControl			(HWND hDlg);
VOID ShowtheDisplayInterface		(HWND hDlg, INT nInputData, INT nOutputData);
VOID ParceOutputData			(HWND hDlg, INT nOutputData);
UINT ReturnDisplayControlNum		(INT nNum);
INT  OutputDatatoPort			(INT nInputNum);
INT  CheckCmpButtonPress		(INT nInputNum);
int  RollDice				(HWND hDlgWnd);
void SetToWinOrLose			(int Sum, HWND hDlgWnd);
void InitGlovalVariable			(HWND hDlgWnd);
BOOL DisplayDice                    	(HWND hDlgWnd);

LRESULT CALLBACK MainProc		(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY ChatInputEditProc	(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
