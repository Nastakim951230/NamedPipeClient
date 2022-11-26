#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140
double mas[10];
int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe"; //имя канала 
	HANDLE hNamedPipe;//объявляем дескриптор канала

	BOOL flag_otvet = TRUE;
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER;
	DWORD actual_written;
	LPWSTR buffer;
	DWORD actual_reaen;
	BOOL SuccessRead;


	while (TRUE)
	{
		char message[SIZE_BUFFER];
		hNamedPipe = CreateFile(lpszPipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		DWORD dwMode = PIPE_READMODE_MESSAGE;

		BOOL isSucces = SetNamedPipeHandleState(
			hNamedPipe,
			&dwMode,
			NULL,
			NULL
		);
		if (!isSucces)
		{
			printf("сервер не отвечает\n");
		}
		else
		{
			printf("соединение установленно\n");
		
			if (flag_otvet)
			{



				printf("введите сообщение для сервера:\n");
				gets(message);
				int n = 0;
				mas[n] = atof(message);
				n++;
				if (mas[0] != 0)
				{
					buffer = &message;
					WriteFile(hNamedPipe, buffer, size_buffer, &actual_written, NULL);
					flag_otvet = FALSE;
				}
				else
				{
					buffer = "0";
					WriteFile(hNamedPipe, buffer, size_buffer, &actual_written, NULL);
					flag_otvet = FALSE;
				}
				
				
			}
			buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
			SuccessRead = ReadFile(hNamedPipe, buffer, SIZE_BUFFER, &actual_reaen, NULL);
			if (SuccessRead)
			{
				if (buffer!=0)
				{
					printf("\nОтвет сервеса: ");
					printf(buffer);
					printf("\n");
					flag_otvet = TRUE;
				}
				else
				{
					printf("\nОтвет сервеса: Ошибка");
					printf("\n");
					flag_otvet = TRUE;

				}
			}
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}
}
