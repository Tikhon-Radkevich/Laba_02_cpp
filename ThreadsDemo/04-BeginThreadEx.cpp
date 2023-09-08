#include <windows.h>
#include <iostream>
#include <string.h>
#include <process.h>

using namespace std;

UINT WINAPI thread(void *pString)
{
	int	i = 1;
	char	*pLexema;

	pLexema = strtok((char*) pString," ");
	while (pLexema != NULL)
	{
		cout << "Thread find the lexema " << i << " : " << pLexema << endl;
		pLexema = strtok(NULL, " ");
		i++;
	}

	return 0;
}

int main()
{
	char	sentence[80];
	int	i,j,k = 0;
	HANDLE	hThread;
	UINT	IDThread;

	cout << "Input string: ";
	cin.getline(sentence, 80);
	j = strlen(sentence);

	hThread = (HANDLE) 
		_beginthreadex(NULL, 0, thread, sentence, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	
	for (i=0; i<j; i++)
		if (sentence[i] == 'a')
			k++;
	
	WaitForSingleObject(hThread, INFINITE);

	cout << "Number of symbols 'a' in the string = " << k << endl;
	CloseHandle(hThread);

	return 0;
}
