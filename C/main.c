#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#define POMODORO_NUM     4
#define FOCUS_MIN        25
#define SHORT_BREAK_MIN  5
#define LONG_BREAK_MIN   30


void wait(const int sec)
{
	#ifdef WIN32
		Sleep(sec * 1000);
	#else
		usleep(sec * 1000000);
	#endif
}

void pomodoro(int session_id, const int set_min, int is_focus)
{
	int total_sec = set_min * 60;
	
	system("cls");
	
	if ((session_id == POMODORO_NUM) && !is_focus)
	{
		printf("Enjoy Long Break!\n");
	}
	else if (!is_focus)
	{
		printf("Enjoy Short Break!\n");
	}
	else
	{
		printf("Session: %d / %d\n", session_id, POMODORO_NUM);
	}
	
	while(total_sec > 0){
	
	int min = total_sec / 60;
	int sec = total_sec % 60;
	printf("%02d %02d\r", min, sec);
	total_sec--;
	wait(1);
	
	}
}

int prompt_user()
{
	char ch, nl;
	while (1)
	{
		printf("Enter any key for Start or q for Quit: ");
		scanf(" %c", &ch);
		if ((nl = getchar()) != '\n')
		{
			printf("You entered more than one charchter.\n");
			return 0;
		}
		else if (ch == 'q')
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
}

int main()
{
	int pom_cnt = 0; // Pomodoro count.
	
	while (pom_cnt < POMODORO_NUM)
	{
		if (!prompt_user())
		{
			break;
		}
		pom_cnt++;
		pomodoro(pom_cnt, FOCUS_MIN, 1);
		if (pom_cnt == POMODORO_NUM)
		{
			pomodoro(pom_cnt, LONG_BREAK_MIN, 0);
		}
		else
		{
			pomodoro(pom_cnt, SHORT_BREAK_MIN, 0);
		}
	}
	
	printf("Bye!\n");
	
	return 0;
}
