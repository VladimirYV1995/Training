// библиотеки
#include "resource.h"
#include "framework.h"
#include "commctrl.h"
#include <sstream>
#include <thread>

using namespace std;

#define comboBoxPorts			0 //выпадающий список COM портов

//Надписи
#define labelHint				1 //текст по подсказок работы с Com портом
#define labelLog				2 //Для отображения состояния элементов приложения 
#define labelTitleDataIn		3 //Заголовок для таблицы исходящих от программы к устройству CAN пакетов
#define labelTitleDataOut		4 //Заголовок для таблицы приходящих от устройства к программе CAN пакетов
#define labelTitleButtonSwitch	5 //Заголовок для переключения камер
#define labelTitleCommand		6 //Заголовок для переключения команд
#define labelTitleJoy			7 //Заголовок для переключения джойстика

//Таблицы
#define tableCANPackage1  8 // Таблица отправки данных
#define tableCANPackage2  9 // Таблица приёма данных

//Кнопки:
//Работа с COM портом
#define buttonUpdataPorts	10 // Обновление списка COM портов
#define buttonOpenPort		11 // Открытие порта
#define buttonInitParam		12 // Установка параметров передачи информации
#define buttonClosePort		13 // Закрытие порта

//Переключение камер
#define buttonMain		14 // Переключение на Главную камеру (Main)
#define buttonGripper	15 // Переключение на Схват (Gripper)
#define buttonThermal	16 // Переключение на Резерв, он же Тепловизор (Thermal)
#define buttonRaS		17 // Переключение на Заднюю камеру (Rear and Share Cam)
#define buttonLaR		18 // Переключение на Боковую (Left and Right Cam)
#define buttonLeftCam	19 // Переключение на Левую камеру
#define buttonRightCam	20 // Переключение на Правую камеру

#define buttonReadCAN	21 //Кнопка чтения данных
#define buttonStopCAN	22 // Остановка чтения данных чтения данных

//Кнопки работы с командами
#define buttonFocus		23 // Радиокнопка регурелировка Фокуса
#define buttonIRIS		24 // Радиокнопка регурелировка Диафрагмы
#define buttonWiper		25 // Радиокнопка Включение/Выключение Whiper
#define buttonInfrared	26 // Радиокнопка Инфракрасный свет Включён/Выключен
#define buttonIOMenu	27 // Радиокнопка Вход/Выход в меню
#define buttonHeater	28 // Радиокнопка Нагреватель Включён/Выключен

//Джойстик 
#define buttonJoyUp			29 // Вверх
#define buttonJoyDown		30 // Вниз
#define buttonJoyLeft		31 // Влево
#define buttonJoyRight		32 // Вправый
#define buttonJoyRightCl	33 // Правый джойстик по часовой
#define buttonJoyRightCCl	34 // // Правый джойстик против часовой
#define buttonJoyLeftCl		35 // Левый джойстик по часовой
#define buttonJoyLeftCCl	36 // Левый джойстик против часовой

INT_PTR CALLBACK  About(HWND, UINT, WPARAM, LPARAM);

//Глобальные переменные

HINSTANCE hInst;

HWND hwnd;//Дискриптор основного окна
HANDLE hSerial;//Дискриптор (обработчик) выбранного COM порта
HWND hChlWndwConst[9]; // Массив дискрипторов (указателей) окон, которые не деактивируются 
HWND hChlWndwVar[28]; // Массив дискрипторов (указателей) окон, деактивируются в зависимости от условий

TCHAR choiseComPort[5];//Буффер, получающий текущие значение (выбранный COM порт) из ComboBox (выпадающего списка)  

std::wstring stemp, id, l, dtp, num; // textB; для функций stringToLPCWSTR (перевод строки в LPCWSTR)

BOOL	GCS, SCS, PC, SCM, //SCT, //переменные для проверки корректности установки параметров чтения/записи,
		startStopOutCAN = FALSE; //запуск потока чтения 

OVERLAPPED overlap = { 0 };

//Для второго потока, который читает данные 
unsigned threadCAN; // обработчик
unsigned  idThread; 

int i, //Счётчик 
actComPort = 10, //Количество потенциальных COM портов
realComPort = 0, //Количество доступных COM портов
numItemIn = 1, //Порядковый номер пакет в таблице Отправляемых пакетов
numItemOut = 0, //Порядковый номер пакета в таблице Принимаемых пакетов
hightWindow = 700, //Высота окна
lenghtWindow = 1300;//Длина окна

// данные, которую будем передавать:
uint8_t Data[] =
{
	116, //начало сообщения для видемультиплексора
	48, // 0 - Старший регистр ID
	57, // 9  
	51, // 3 - Младший регистр ID
	54, // 6 - Длина данных, идущих ниже:
	48, // Старший регистр номера камеры: 48 ( 0 )
	48, // Младший регистр номера камеры: 48 - 54 ( 0 - 6 )
	48,
	48,
	48,
	48,
	48,
	48,
	48,
	48,
	48,
	48, // Команды: 48 - 53 ( 0 - 5 ) 
	13 //конец сообщения
};

//Функция преобразование массив типа uint8_t в string 
string UintToString(uint8_t* inDataStr, int inSizeDate)
{
	string outStr = "", strBuf;
	strBuf = string((char*)inDataStr);

	for (int k = 0; k < inSizeDate; k++)
	{
		outStr += strBuf[k];
	}

	return outStr;
}

//----Функции преобразования строки (string) в LPCWSTR----//

wstring strToLPCWSTR(string strin)
{
	int slength = (int)strin.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, strin.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, strin.c_str(), slength, buf, len);
	std::wstring result(buf);
	delete[] buf;
	return result;
}

// Функция проверки доступности и записи в выпадающий список доступных COM портов
VOID  WriteComBox()
{
	//переменные для нахождения доступных портов
	string COM = "COM", COMPort;
	HANDLE hSerNext;  // Дискриптор (обработчик) COM порта для перебора доступных COM портов
	LPCWSTR serComPort; // Буффер, получающий очередное значение COMx порта для проверки его доступа

	//Для поиска доступных COM портов использован алгоритм перебора потенциально существующих портов. 
	//Если очередной Com порт открылся без ошибки, то он доступен. Далее он добавляется в выпадающий список
	for (i = 0; i <= actComPort; i++)
	{
		//формируем COM порт в виде строки "COMx", где х - очередной номер порта
		COMPort = COM + to_string(i);

		//преобразование строки в LPCWSTR
		stemp = strToLPCWSTR(COMPort);
		serComPort = stemp.c_str();

		//проверяем очередной порт на доступность:			
		hSerNext = ::CreateFile(serComPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		//Проверяем работоспособность открытого порта
		if (hSerNext != INVALID_HANDLE_VALUE)
		{
			SendMessage(hChlWndwVar[0], CB_ADDSTRING, (WPARAM)0, (LPARAM)serComPort);//Запись доступного порта в выпадающий список
			realComPort++; //Увеличиваем на +1 Количество доступных портов
		}
		CloseHandle(hSerNext);
	}
	SendMessage(hChlWndwVar[0], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);// для отображения начального элемента в поле выбора поля со списком.
}

//----Формирование таблицы----//

//Создание столбцов
VOID AddCol(HWND hwnd, int ColWidth, LPCWSTR Text, int iSubItem)
{
	LV_COLUMN p;
	p.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	p.fmt = LVCFMT_LEFT;                                        // тип выравнивания для столбца
	p.cx = ColWidth;                                            // ширина столбца в пикселах
	p.pszText = (LPWSTR)Text;                                   // адрес строки заголовка столбца
	p.cchTextMax = 0;											// размер буфера, адрес которого                  
	p.iSubItem = iSubItem;                                      // номер дополнительного элемента 

	ListView_InsertColumn(hwnd, 0, &p);
}
// добавление столбцов таблицы
VOID tuningTable(int numhTable)
{
	//Назначение колонок в таблице
	AddCol(hChlWndwConst[numhTable], 140, L"Data (HEX)", 0);
	AddCol(hChlWndwConst[numhTable], 60, L"L (HEX)", 0);
	AddCol(hChlWndwConst[numhTable], 80, L"ID (HEX)", 0);
	AddCol(hChlWndwConst[numhTable], 40, L"№", 0);

	//Сетка для таблицы
	ListView_SetExtendedListViewStyle(hChlWndwConst[numhTable], LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

//Добавление строки с данными в таблицу
VOID InsertNewItem(LPCWSTR colTable[], int numTabl, int item, LVITEMW lvi)
{
	// Создаём стоку из отдельных элементов (атрибутов) полученых выше и вставляем её в таблицу
	lvi.pszText = (LPWSTR)colTable[0];
	item = ListView_InsertItem(hChlWndwConst[numTabl], &lvi);
	ListView_SetItemText(hChlWndwConst[numTabl], item, 1, (LPWSTR)colTable[1]);
	ListView_SetItemText(hChlWndwConst[numTabl], item, 2, (LPWSTR)colTable[2]);
	ListView_SetItemText(hChlWndwConst[numTabl], item, 3, (LPWSTR)colTable[3]);
}

//Функция обработки данных для записи в таблицу
VOID WriteTable(string strData, int numTabl, int sizePack, uint8_t checkBites[])
{
	LPCWSTR colTable[4], tb;
	string  Elem = "", itemTabl;	
	LVITEMW lvi = { 0 };
	BOOL newItem = TRUE;
	uint8_t len[1];
	wchar_t textBuffer[9];
	int k, z, j, idlen = 0, dataBegin, Ret = 0, indexID;

	//Определяем длину ID:	
	int checkNum3 = (sizePack - 2 - 4) / 2; //Вычитаем из сообщения его начало и конец (-2) и 4 бита (потенциальные 3 ID и 4й - потенциальную длину) делим на 2, получаем потенциальную длину данных
	int checkNum8 = (sizePack - 2 - 9) / 2;

	int fourthBite = int(checkBites[0]) - 48;	// !!!Кастыль!!!
	int ninethBite = int(checkBites[1]) - 48;

	if (checkNum3 == fourthBite) // Если потенциальная длина совпала с переданным 4м байтом (потенциальной длиной), то id действительно 3 регистра 
	{
		idlen = 3;
		len[0] = checkBites[0];

	}
	else if (checkNum8 == ninethBite) //если не совпало то длина ID = 8
	{
		idlen = 8;
		len[0] = checkBites[1];
	}

	dataBegin = idlen + 2; // положение начало данных в пакете


	//Отбор ID пакета
	for (i = 1; i <= idlen; i++)
	{
		Elem += strData[i];
	}
	
	// Приём данных в программу от устройства, Таблица отображает список пакетов, где ID и длина постоянная, изменяются только данные пакета
//Если предполагается запись данных данных от устройства:
	if (numTabl == 3)
	{
		//int z = 0;

		// проверяем поступал ли пакет с данным id ранее 
		for ( z = 0 ; z < ListView_GetItemCount(hChlWndwConst[numTabl]); z++)
		{
			itemTabl = "";
			
			ListView_GetItemText(hChlWndwConst[numTabl], z, 1, textBuffer, sizeof(textBuffer));// в textBuffer записывается текст (здечь очереной ID) указаной строчки и столбца 
			
			for (k = 0; k < idlen; k++)
			{
				itemTabl += textBuffer[k];//переводим в строковый буфер
			}

			//textB = strToLPCW(itemTabl);
			//tb = textB.c_str();
			//if (tb == id)

			if (itemTabl == Elem)//сравниваем id поступившего пакета с уже записанными в таблицу, если совпал запоминаем номер его строки в таблице 
			{
				newItem = FALSE;
				indexID = z;			
				break;
			}		
		}

		//Если ранее не поступал:
		if (newItem == TRUE)
		{
			numItemOut++;
		}
	}

	id = strToLPCWSTR(Elem);
	colTable[1] = id.c_str();
	Elem = "";
	

	//Номер записи
	if (numTabl == 2)
	{
		j = numItemIn++;
	}
	else if (numTabl == 3)
	{
		j = numItemOut;
	}
	Elem = to_string(j);	
	num = strToLPCWSTR(Elem);
	colTable[0] = num.c_str();
	Elem = "";
	
	
	//Отбор длины пакета
	Elem = UintToString(len,1);	
	l = strToLPCWSTR(Elem);
	colTable[2] = l.c_str();
	Elem = "";
	

	j = 0;
	//Отбор данных пакета
	for (i = dataBegin; i < sizePack; i++)
	{
		j++;
		Elem += strData[i];
		if (j == 2)//Формируем строку из данных, разбитых по 2
		{
			Elem += " ";
			j = 0;
		}
	}	
	dtp = strToLPCWSTR(Elem);
	colTable[3] = dtp.c_str();
	Elem = "";
	

	lvi.mask = LVIF_TEXT;

	if (numTabl == 3 && newItem == FALSE)
	{
		ListView_SetItemText(hChlWndwConst[numTabl], indexID, 3, (LPWSTR)colTable[3]);// изменение записи в таблице 3
	}
	else
	{
		InsertNewItem(colTable, numTabl, Ret, lvi); //добавление нового пакета, если он раньше не поступал или если пакет является отправляемым
	}

}

//Функция, в которой выполняется алгоритм вторичного потока для чтения данных из буфера COM порта
unsigned __stdcall ThreadFunc(void* param)
{
	//полу-работающий эмулятор
	/*
	uint8_t data[] = { 116, 48, 56, 48, 56, 48, 53, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 }; // строка для передачи 080 8 00 00 00 00 00 00 00 00
	DWORD dwSize1 = sizeof(data);   // размер этой строки
	DWORD dwBytesWritten;
	*/	
	
	string strPack; // строковый буфер данных
	uint8_t  sReceivedChar[27], checkBites[2], bufInData[72];
	DWORD iSize = 0;	
	COMSTAT CMST;
	LPDWORD LPD = 0;
	BOOL A = FALSE;//!!Кастыль
	unsigned long wait = 0, read = 0, state = 0, temp = 0; //переменные для работы с функционалом событий 
	int k,
		sizeDate, //буфер размера данных
		maxSizeDate = 72; // максимальный размер данных
	
	//Чтение байта данных из файла:

	while (true)
	{

		//Sleep(50);

		//Посылаем строку.Напомню, что пример простейший, поэтому никаких особо проверок я не делаю :
		//BOOL iRet = WriteFile(hSerial, data, dwSize1, &dwBytesWritten, &overlap);

		if (startStopOutCAN == TRUE)// чтение включено
		{
			sizeDate = 0;
			strPack = "";

			//Читаем новое сообщение
			for (i = 0; i < maxSizeDate; i++)// в пакете максимум 72 бита
			{
				ClearCommError(hSerial, &temp, &CMST); // извлекает информацию об коммуникационной ошибке и сообщает о текущем состоянии коммуникационного устройства. 

				if (temp == CE_RXOVER) //Произошло переполнение буфера ввода данных. Или нет места в буфере ввода данных, или символ был получен после  метки конца файла (EOF)
				{
					PC = PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);//очистка					
					A = TRUE;
					break;///!!!!
				}

				overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//Создаём событие

				//Буфер заполняем, значениями, которые мы знаем
				for (k = 0; k < 27; k++)
				{
					sReceivedChar[k] = 'L';
				}

				if (SCM != 0)//Если маска установлена без ошибок
				{
					WaitCommEvent(hSerial, &state, &overlap);// Связываем порт и объект синхронизации					
					wait = WaitForSingleObject(overlap.hEvent, 5000);// Начинаем ожидание данных

					if (wait == WAIT_OBJECT_0)// Данные получены 
					{
						ClearCommError(hSerial, &temp, &CMST);

						if (temp == CE_RXOVER)
						{
							PC = PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
							CloseHandle(overlap.hEvent);
							A = TRUE;
							break;///!!!! 
						}
											
						ReadFile(hSerial, sReceivedChar, 1, &iSize, &overlap);   // получаем биты (по идее 1, но не факт)					

						wait = WaitForSingleObject(overlap.hEvent, 5000);//ждём окончании операции

						if (wait == WAIT_OBJECT_0)
						{
							//берём данные из буфера, и отправляем в специльный буфер
							for (k = 0; k < 27; k++)
							{
								if (sReceivedChar[k] == 'L')
								{
									break;
								}
								// заносим считанные данные в буфер
								bufInData[sizeDate] = sReceivedChar[k];
								sizeDate++;
							}


							if (bufInData[sizeDate - 1] == 13)
							{
								//Когда достигли конца, создаём ещё один более коректный буфер с выясниным размером
								uint8_t* bufInDataNew = new uint8_t[sizeDate];

								for (k = 0; k < sizeDate; k++)
								{
									bufInDataNew[k] = bufInData[k];

									if (k == 4)//считаем четвёртый бит
									{
										checkBites[0] = bufInData[k];
									}
									if (k == 9)//считаем девятый бит
									{
										checkBites[1] = bufInData[k];
									}
								}
								strPack = UintToString(bufInDataNew, sizeDate);//преобразуем данные в строку
								delete[] bufInDataNew;

								CloseHandle(overlap.hEvent);
								break; //Прерывание цикла for если найден конец сообщения

							}
						}
						else
						{
							CloseHandle(overlap.hEvent);
							break;
						}
					}

				}
				CloseHandle(overlap.hEvent);
			}
			if ((strPack[0] == 't' || strPack[0] == 'e') && strPack[sizeDate - 1] == '\r')
			{
				WriteTable(strPack, 3, sizeDate, checkBites); //Записываем полученные данные в таблицу	
			}

			if (iSize == 0) //если данных нет
			{
				if (A == TRUE)
				{
					A = FALSE;
				}
				else
				{
					SetWindowText(hChlWndwConst[1], _T("Отсутствие новых данных для чтения "));
					MessageBox(0, _T("Данные более не поступают.\nНажмите кнопку Остановить чтение.  "), _T("Информация"), MB_OK | MB_ICONINFORMATION);
					Sleep(500);
					continue;
				}

			}
		}
	}

	//_endthreadex(0); //выход (кончание потока)

	return 0;
}

//Функция посыла данных
VOID SendingData()
{
	uint8_t data[18], checkBites[2] = { 0, 0 };
	//для местной инициализации, глобальную переменную не подхватывает, передача аргументом происходит некорректно Кастыль!!!
	for (i = 0; i < 18; i++)
	{
		data[i] = Data[i];
	}

	string  strData = ""; //переведенные данные в string
	int sizeDate = sizeof(data) / sizeof(uint8_t);//размер данных	
	
	DWORD dwSize = sizeof(data);   // размер этой строки
	DWORD dwBytesWritten;   // тут будет количество переданных байт

	//Посылаем данные
	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, &overlap);

	checkBites[0] = data[4];
	strData = UintToString(data, sizeDate);


	//В таблицу пишем данные, которые отсылаем
	WriteTable(strData, 2, sizeDate, checkBites);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	int itemIndex;

	switch (Message)
	{
	case WM_CREATE: //Создание функциональных элементов как дочерних окон:
	{
		// Лог, служебные подсказки для пользователя
		hChlWndwConst[0] = CreateWindow(_T("static"), _T(" "),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			0, //начало кнопки по оси X  
			0, //начало кнопки по оси Y
			lenghtWindow, //длина окна 
			20, //высота окна 
			hwnd, (HMENU)labelHint, hInst, NULL);

		// Для отображения состояний:
		hChlWndwConst[1] = CreateWindow(_T("static"), _T(" "),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			lenghtWindow / 2 - 150, 50, 300, 20,
			hwnd, (HMENU)labelLog, hInst, NULL);

		//Таблица отсылаемых CAN пакетов:
		hChlWndwConst[2] = CreateWindow(WC_LISTVIEW, L"",
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | LVS_REPORT | LVS_EDITLABELS,
			lenghtWindow - 680, 250, 320, 342,
			hwnd, (HMENU)tableCANPackage1, NULL, NULL);

		//Таблица принемаемых CAN пакетов:
		hChlWndwConst[3] = CreateWindow(WC_LISTVIEW, L"",
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | LVS_REPORT | LVS_EDITLABELS,
			lenghtWindow - 340, 250, 320, 342,
			hwnd, (HMENU)tableCANPackage2, NULL, NULL);

		// Заголовок для таблицы отсылаемых CAN пакетов:
		hChlWndwConst[4] = CreateWindow(_T("static"), _T("  Отправляемые CAN пакеты"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			lenghtWindow - 625, 220, 200, 20,
			hwnd, (HMENU)labelTitleDataIn, hInst, NULL);

		// Заголовок для таблицы принемаемых CAN пакетов:
		hChlWndwConst[5] = CreateWindow(_T("static"), _T("  Принимаемые CAN пакеты"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			lenghtWindow - 305, 220, 200, 20,
			hwnd, (HMENU)labelTitleDataOut, hInst, NULL);

		// Заголовок для Кнопок переключения камер:
		hChlWndwConst[6] = CreateWindow(_T("static"), _T("  Переключение камер: "),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			40, 220, 160, 20,
			hwnd, (HMENU)labelTitleDataOut, hInst, NULL);

		// Заголовок для отправки команд:
		hChlWndwConst[7] = CreateWindow(_T("static"), _T("  Отправка команд:"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			275, 220, 130, 20,
			hwnd, (HMENU)labelTitleDataOut, hInst, NULL);

		// Заголовок для отправки команд:
		hChlWndwConst[8] = CreateWindow(_T("static"), _T("  Джойстик:"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			190, 440, 80, 20,
			hwnd, (HMENU)labelTitleDataOut, hInst, NULL);

		//-----Обработка COM порта:

		// Выпадающий список COM портов:
		hChlWndwVar[0] = CreateWindow(L"Combobox", NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
			20, 110, 100, 200,
			hwnd, (HMENU)comboBoxPorts, hInst, NULL);

		// Кнопка обновления списка COM портов:
		hChlWndwVar[1] = CreateWindow(TEXT("button"), TEXT("Обновить доступные COM порты"),
			WS_VISIBLE | WS_CHILD,
			125, 110, 250, 20,
			hwnd, (HMENU)buttonUpdataPorts, hInst, NULL);

		// Кнопка открытия порта :
		hChlWndwVar[2] = CreateWindow(TEXT("button"), TEXT("Открыть порт"),
			WS_VISIBLE | WS_CHILD,
			380, 110, 130, 20,
			hwnd, (HMENU)buttonOpenPort, hInst, NULL);

		// Установка и проверка корректности установки параметров взаимодействия параметров	:		
		hChlWndwVar[3] = CreateWindow(TEXT("button"), TEXT("Установить параметры"),
			WS_VISIBLE | WS_CHILD,
			125, 135, 250, 20,
			hwnd, (HMENU)buttonInitParam, hInst, NULL);

		// Закрытие порта :
		hChlWndwVar[4] = CreateWindow(TEXT("button"), TEXT("Закрыть порт"),
			WS_VISIBLE | WS_CHILD,
			380, 135, 130, 20,
			hwnd, (HMENU)buttonClosePort, hInst, NULL);

		//-----Переключение камер

		// Кнопка переключения на Боковую (Left and Right Cam):
		hChlWndwVar[5] = CreateWindow(TEXT("button"), TEXT("Боковая (Left and Right Cam)"),
			WS_VISIBLE | WS_CHILD,
			20, 250, 200, 20,
			hwnd, (HMENU)buttonLaR, hInst, NULL);

		// Кнопка переключения на Левую камеру:
		hChlWndwVar[6] = CreateWindow(TEXT("button"), TEXT("Левая камера"),
			WS_VISIBLE | WS_CHILD,
			20, 275, 200, 20,
			hwnd, (HMENU)buttonLeftCam, hInst, NULL);

		// Кнопка Переключение на Правая камеру:
		hChlWndwVar[7] = CreateWindow(TEXT("button"), TEXT("Правая камера"),
			WS_VISIBLE | WS_CHILD,
			20, 300, 200, 20,
			hwnd, (HMENU)buttonRightCam, hInst, NULL);

		// Кнопка переключения на Главную камеру (Main):
		hChlWndwVar[8] = CreateWindow(TEXT("button"), TEXT("Главная (Main)"),
			WS_VISIBLE | WS_CHILD,
			20, 325, 200, 20,
			hwnd, (HMENU)buttonMain, hInst, NULL);

		// Кнопка переключения на Схват (Gripper):
		hChlWndwVar[9] = CreateWindow(TEXT("button"), TEXT("Схват (Gripper)"),
			WS_VISIBLE | WS_CHILD,
			20, 350, 200, 20,
			hwnd, (HMENU)buttonGripper, hInst, NULL);

		// Кнопка переключения на Резерв, он же Тепловизор (Thermal):
		hChlWndwVar[10] = CreateWindow(TEXT("button"), TEXT("Тепловизор (Thermal)"),
			WS_VISIBLE | WS_CHILD,
			20, 375, 200, 20,
			hwnd, (HMENU)buttonThermal, hInst, NULL);

		// Кнопка переключения на Заднюю камеру (Rear and Share Cam):
		hChlWndwVar[11] = CreateWindow(TEXT("button"), TEXT("Задняя (Rear and Share Cam)"),
			WS_VISIBLE | WS_CHILD,
			20, 400, 200, 20,
			hwnd, (HMENU)buttonRaS, hInst, NULL);

		//-----Переключение команд 

		//Регулировка Фокуса
		hChlWndwVar[12] = CreateWindow(TEXT("button"), TEXT("Регулировка Фокуса"),
			WS_VISIBLE | WS_CHILD,
			240, 250, 210, 20,
			hwnd, (HMENU)buttonFocus, hInst, NULL);

		//Регулировка Диафрагмы
		hChlWndwVar[13] = CreateWindow(TEXT("button"), TEXT("Регулировка диафрагмы (IRIS)"),
			WS_VISIBLE | WS_CHILD,
			240, 275, 210, 20,
			hwnd, (HMENU)buttonIRIS, hInst, NULL);

		//Wiper Включение/Выключение
		hChlWndwVar[14] = CreateWindow(TEXT("button"), TEXT("Wiper Вкл/Выкл"),
			WS_VISIBLE | WS_CHILD,
			240, 300, 210, 20,
			hwnd, (HMENU)buttonWiper, hInst, NULL);

		//Регулировка Фокуса
		hChlWndwVar[15] = CreateWindow(TEXT("button"), TEXT("Инфракрасный свет Вкл/Выкл"),
			WS_VISIBLE | WS_CHILD,
			240, 325, 210, 20,
			hwnd, (HMENU)buttonInfrared, hInst, NULL);

		//Регулировка Диафрагмы
		hChlWndwVar[16] = CreateWindow(TEXT("button"), TEXT("Меню Вход/Выход"),
			WS_VISIBLE | WS_CHILD,
			240, 350, 210, 20,
			hwnd, (HMENU)buttonIOMenu, hInst, NULL);

		//Wiper Включение/Выключение
		hChlWndwVar[17] = CreateWindow(TEXT("button"), TEXT("Нагреватель Вкл/Выкл"),
			WS_VISIBLE | WS_CHILD,
			240, 375, 210, 20,
			hwnd, (HMENU)buttonHeater, hInst, NULL);

		//-----Джойстик

		//Верх 
		hChlWndwVar[18] = CreateWindow(TEXT("button"), TEXT("Вверх"),
			WS_VISIBLE | WS_CHILD,
			200, 520, 60, 20,
			hwnd, (HMENU)buttonJoyUp, hInst, NULL);

		// Вниз
		hChlWndwVar[19] = CreateWindow(TEXT("button"), TEXT("Вниз"),
			WS_VISIBLE | WS_CHILD,
			200, 560, 60, 20,
			hwnd, (HMENU)buttonJoyDown, hInst, NULL);

		//Влево
		hChlWndwVar[20] = CreateWindow(TEXT("button"), TEXT("Влево"),
			WS_VISIBLE | WS_CHILD,
			135, 540, 60, 20,
			hwnd, (HMENU)buttonJoyLeft, hInst, NULL);

		//Вправо
		hChlWndwVar[21] = CreateWindow(TEXT("button"), TEXT("Вправо"),
			WS_VISIBLE | WS_CHILD,
			265, 540, 60, 20,
			hwnd, (HMENU)buttonJoyRight, hInst, NULL);

		//Левый по часовой 
		hChlWndwVar[22] = CreateWindow(TEXT("button"), TEXT("По часовой"),
			WS_VISIBLE | WS_CHILD,
			80, 470, 110, 20,
			hwnd, (HMENU)buttonJoyLeftCl, hInst, NULL);

		//Левый против часовой
		hChlWndwVar[23] = CreateWindow(TEXT("button"), TEXT("Против часовой"),
			WS_VISIBLE | WS_CHILD,
			80, 490, 110, 20,
			hwnd, (HMENU)buttonJoyLeftCCl, hInst, NULL);

		//Правый по часовой 
		hChlWndwVar[24] = CreateWindow(TEXT("button"), TEXT("По часовой"),
			WS_VISIBLE | WS_CHILD,
			270, 470, 110, 20,
			hwnd, (HMENU)buttonJoyRightCl, hInst, NULL);

		//Правый против часовой
		hChlWndwVar[25] = CreateWindow(TEXT("button"), TEXT("Против часовой"),
			WS_VISIBLE | WS_CHILD,
			270, 490, 110, 20,
			hwnd, (HMENU)buttonJoyRightCCl, hInst, NULL);

		//-----Работа с данными

		// Кнопка Чтения данных:
		hChlWndwVar[26] = CreateWindow(TEXT("button"), TEXT("Чтение данных"),
			WS_VISIBLE | WS_CHILD,
			lenghtWindow - 340, 160, 130, 30,
			hwnd, (HMENU)buttonReadCAN, hInst, NULL);

		// Кнопка остановки чтения:
		hChlWndwVar[27] = CreateWindow(TEXT("button"), TEXT("Остановка чтения"),
			WS_VISIBLE | WS_CHILD,
			lenghtWindow - 200, 160, 130, 30,
			hwnd, (HMENU)buttonStopCAN, hInst, NULL);

		//-----Прочие настройки

		//Задание стандартного для данного компьютора шрифта кнопок
		for (i = 0; i < 28; i++)
		{
			SendMessage(hChlWndwVar[i], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
		}
		//Задание стандартного для данного компьютора шрифта надписей
		for (i = 0; i < 9; i++)
		{
			SendMessage(hChlWndwConst[i], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
		}
		//Деактивируем кнопки, которые изначально должны быть недоступны: 
		for (i = 2; i < 28; i++)
		{
			EnableWindow(hChlWndwVar[i], FALSE);
		}

		//Начальное сообщение в Лог:
		SetWindowText(hChlWndwConst[0], _T("Выберите COM порт, к которому подсоединено устройство"));

		//Настройка таблиц:
		tuningTable(2);
		tuningTable(3);

		//Узнаём и записываем в выпадающий список доступные COM порты:
		WriteComBox();


		//Для открытия порта, который  изначально указан в ComboBox - сейчас не работает !!!
		//itemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0); 
		//(TCHAR)SendMessage((HWND)hwnd, (UINT)CB_GETLBTEXT, (WPARAM)itemIndex, (LPARAM)choiseComPort);

		break;
	}

	case WM_COMMAND:
	{
		switch LOWORD(wParam)
		{
		case  comboBoxPorts:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
				// Если пользователь делает выбор из списка:
				// Отправляем сообщение CB_GETCURSEL, чтобы получить индекс выбранного элемента списка.
				// Отправляем сообщение CB_GETLBTEXT, чтобы получить элемент.
				// Отображение элемента в окне сообщения.
			{
				itemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				//Отправка сообщения о выбранном COM порте для его открытия. 
				//В choiseComPort записывается выбранный в выпадающем списке COM порт
				(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT, (WPARAM)itemIndex, (LPARAM)choiseComPort);
				EnableWindow(hChlWndwVar[2], TRUE);
				SetWindowText(hChlWndwConst[0], _T("Можете открыть выбранный порт"));
			}
			break;
		}

		//Была нажата кнопка обновления списка COM портов:
		case buttonUpdataPorts:
		{
			//Отключаем доступ к кнопкам на время обновления
			for (i = 0; i < 3; i++)
			{
				EnableWindow(hChlWndwVar[i], FALSE);
			}

			SetWindowText(hChlWndwConst[0], _T("Идёт обновление портов"));

			// Очистка выпадающего списка
			for (i = 0; i < realComPort; i++)
			{
				SendMessage(hChlWndwVar[0], CB_DELETESTRING, (WPARAM)0, (LPARAM)0); // Удаление очередной строки
			}
			realComPort = 0;

			// Снова ищем и записываем доступные COM порты:
			WriteComBox();

			MessageBox(0, _T("Порты обновлены"), _T("Информация"), MB_OK | MB_ICONINFORMATION);
			SetWindowText(hChlWndwConst[0], _T("Порты обновлены. Выберите COM порт, к которому подсоединено устройство"));

			for (i = 0; i < 2; i++)
			{
				EnableWindow(hChlWndwVar[i], TRUE); // Даём доступ обратно
			}

			break;
		}

		//Была нажата кнопка открытия порта:
		case  buttonOpenPort:
		{
			// !!! ПОСМОТРЕТЬ К КАКОМУ COM ПОРТУ ПОДКЛЮЧЕНО УСТРОЙСТВО УПРАВЛЕНИЯ CAN-ИНТЕРФЕСОМ !!!
			//hSerial = ::CreateFile(choiseComPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);  ----SINH----
			//Открываем на асинхронный приём передачу
			hSerial = ::CreateFile(choiseComPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

			//Проверяем работоспособность открытого порта
			if (hSerial == INVALID_HANDLE_VALUE)
			{
				if (GetLastError() == ERROR_FILE_NOT_FOUND)
				{
					MessageBox(0, _T("Последовательный порт не существует или к ниму подключено другое устройство!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
					SetWindowText(hChlWndwConst[0], _T("Ошибка: Указанный порт не существует или к ниму подключено другое устройство!"));
				}
				else
				{
					MessageBox(0, _T("Порт не доступен!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
					SetWindowText(hChlWndwConst[0], _T("Порт не доступен! Ошибка данных!"));
				}
			}
			else
			{
				//При открытии порта становится доступным установка параметров и закрытие порта
				EnableWindow(hChlWndwVar[3], TRUE);
				EnableWindow(hChlWndwVar[4], TRUE);
				//При открытии порта становится недоступным выбор порта, обновление списка COM-портов и открытие порта
				EnableWindow(hChlWndwVar[0], FALSE);
				EnableWindow(hChlWndwVar[1], FALSE);
				EnableWindow(hChlWndwVar[2], FALSE);

				MessageBox(0, _T("Последовательный порт открыт"), _T("Информация"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Последовательный порт открыт. Установите параметры передачи данных или закройте порт."));

			}
			break;
		}

		//Была нажата кнопка закрытия порта:
		case  buttonClosePort:
		{
			BOOL clsF = CloseHandle(hSerial);
			if (clsF != 0)//Если порт закрыт успено
			{
				//При закрытии парта доступно только выбор порта и его открытие, а также обновление списка COM-портов
				EnableWindow(hChlWndwVar[0], TRUE);
				EnableWindow(hChlWndwVar[1], TRUE);
				EnableWindow(hChlWndwVar[2], TRUE);

				for (i = 3; i < 27; i++)
				{
					EnableWindow(hChlWndwVar[i], FALSE);
				}

				MessageBox(0, _T("Последовательный порт закрыт"), _T("Информация"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Последовательный порт закрыт. Можете выбрать COM порт и открыть его."));
			}
			break;
		}

		//Была нажата кнопка установки параметров
		case buttonInitParam:
		{
			//Структура DBC:
			DCB dcbSerialParams = { 0 };
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			GCS = GetCommState(hSerial, &dcbSerialParams);
			if (GCS == 0)
			{
				MessageBox(0, _T("Ошибка получения состояния порта!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Ошибка получения состояния порта!"));
				//cout << "getting state error\n";
			}

			dcbSerialParams.BaudRate = 0xE1000; // !!! Обратите на внимание на данное значение битрейтов, оно должно быть именно таким !!!
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;

			COMMTIMEOUTS CommTimeOuts = { MAXWORD,0,0,0,0 };//Установка параметров таймаутов

			SCM = SetCommMask(hSerial, EV_RXCHAR);

			if (SCM == 0)
			{
				MessageBox(0, _T("Ошибка установки маски порта!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Ошибка установки маски порта!"));
				//cout << "error setting serial port state\n";
			}

			SCS = SetCommState(hSerial, &dcbSerialParams);
			if (SCS == 0)
			{
				MessageBox(0, _T("Ошибка установки состояния порта!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Ошибка установки состояния порта!"));
				//cout << "error setting serial port state\n";
			}

			PC = PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //Очистка очереди
			if (PC == 0)//Проверка - очищенно или всё таки возникли проблемы
			{
				MessageBox(0, _T("Ошибка очистки очереди состояния порта!"), _T("Ошибка"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Ошибка очистки очереди состояния порта!"));
				//cout << "error cleaning serial port " << endl;
			}

			if (GCS && SCS && PC && SCM) //Если параметры приём-передачи установились верно:
			{
				//Теперь доступны кнопки переключения камер, а также посылка данных программе и их чтение:
				for (i = 5; i < 27; i++)
				{
					EnableWindow(hChlWndwVar[i], TRUE);
				}

				MessageBox(0, _T("Параметры для работы с COM портом установлены без ошибок"), _T("Информация"), MB_OK | MB_ICONINFORMATION);
				SetWindowText(hChlWndwConst[0], _T("Параметры для работы с COM портом установлены без ошибок. Можно приступать к работе. По завершению работы закройте порт."));
			}
			break;
		}

		case buttonReadCAN://Чтение порта
		{
			//деактивируем все кнопки, кроме остановкичтения
			for (i = 3; i < 27; i++)
			{
				EnableWindow(hChlWndwVar[i], FALSE);
			}
			EnableWindow(hChlWndwVar[27], TRUE);

			SetWindowText(hChlWndwConst[1], _T("Идёт чтение данных"));

			startStopOutCAN = TRUE; //Открываем поток

			break;
		}

		case buttonStopCAN://Остановка чтение файла
		{
			startStopOutCAN = FALSE;//приостанавливаем поток

			SetWindowText(hChlWndwConst[1], _T("Остановка чтения данных"));
			
			Sleep(500);//некоторые кнопки могут быть не доступны после резкой преостановки  чтения
			
			
			MessageBox(0, _T("Остановка чтения пользователем"), _T("Информация"), MB_OK | MB_ICONINFORMATION);
			//отдаём доступ к кнопкам
			for (i = 3; i < 27; i++)
			{
				EnableWindow(hChlWndwVar[i], TRUE);
			}
			EnableWindow(hChlWndwVar[27], FALSE);
			
			break;
		}

		//-----Переключение камеры

		case  buttonMain: // Переключение на Главную камеру(Main)
		{
			Data[6] = 53;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана Главная камера"));
			break;
		}

		case  buttonGripper: // Переключение на Схват (Gripper)
		{
			Data[6] = 54;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана камера Схвата"));
			break;
		}

		case  buttonThermal: // Переключение на Резерв, он же Тепловизор (Thermal)
		{

			Data[6] = 52;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбран Тепловизор"));
			break;
		}

		case  buttonRaS: // Переключение на Заднюю камеру (Rear and Share Cam)
		{
			Data[6] = 51;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана Задняя камера"));
			break;
		}

		case  buttonLaR: // Переключение на Боковую (Left and Right Cam)
		{
			Data[6] = 48;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана Боковая камера"));
			break;
		}

		case  buttonLeftCam: // Переключение на Левую камеру
		{
			Data[6] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана Левая камера"));
			break;
		}

		case  buttonRightCam: // Переключение на Правую камеру
		{
			Data[6] = 50;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Выбрана Правая камера"));
			break;
		}

		//-----Переключение комманд

		case  buttonFocus: // регулировка Фокуса
		{
			Data[16] = 48;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Регулировка фокуса"));
			break;
		}

		case  buttonIRIS: // регулировка Диафрагмы
		{
			Data[16] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Регулировка диафрагмы"));
			break;
		}

		case  buttonWiper: // Включение/выключение Wiper
		{
			Data[16] = 50;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Wiper"));
			break;
		}

		case  buttonInfrared: // Включение/выключение инфракрасного света
		{
			Data[16] = 51;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Инфракрасный свет"));
			break;
		}

		case  buttonIOMenu: // Вход/выход меню инфракрасного света
		{
			Data[16] = 52;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Меню"));
			break;
		}

		case  buttonHeater: // Вход/выход меню нагреватель
		{
			Data[16] = 53;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Нагреватель"));
			break;
		}

		//-----Джойстик 

		case  buttonJoyUp: //Вверх
		{
			Data[13] = 55;
			Data[14] = 70;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Вверх"));
			break;
		}

		case  buttonJoyDown: // Вниз
		{
			Data[13] = 56;
			Data[14] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Вниз"));
			break;
		}

		case  buttonJoyLeft: // Вправо
		{
			Data[11] = 55;
			Data[12] = 70;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Вправо"));
			break;
		}

		case  buttonJoyRight: // Влево
		{
			Data[11] = 56;
			Data[12] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Влево"));
			break;
		}

		case  buttonJoyLeftCl: // Левый по часовой
		{
			Data[9] = 55;
			Data[10] = 70;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Левый джой по часовой"));
			break;
		}

		case  buttonJoyLeftCCl: // Левый против часовой
		{
			Data[9] = 56;
			Data[10] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Левый джой против часовой"));
			break;
		}


		case  buttonJoyRightCl: // Правый по часовой
		{
			Data[7] = 55;
			Data[8] = 70;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Правый джой по часовой"));
			break;
		}

		case  buttonJoyRightCCl: // Правый против часовой
		{
			Data[7] = 56;
			Data[9] = 49;
			SendingData();
			SetWindowText(hChlWndwConst[1], _T("Правый джой против часовой"));
			break;
		}

		case IDM_EXIT:
		{
			CloseHandle(hSerial);
			CloseHandle((HANDLE)threadCAN);
			DestroyWindow(hwnd);
			break;
		}
		case IDM_ABOUT: //Окно справки
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
		}

		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		//	CloseHandle(hSerial);
		CloseHandle((HANDLE)threadCAN);
		break;
	}

	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ios::sync_with_stdio(false);

	WNDCLASSEX wc;
	MSG msg;

	threadCAN = _beginthreadex(NULL, 0U, ThreadFunc, NULL, 0, &idThread);
	//CREATE_SUSPENDED

	memset(&wc, 0, sizeof(wc));
	//Структура окна 
	wc.hInstance = hInstance; hInst = hInstance;
	wc.lpszClassName = _T("WindowClass");
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_VMSV2);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wc.hbrBackground = (HBRUSH)(COLOR_ACTIVEBORDER + 1);//Цвет фона

	RegisterClassEx(&wc);//Регистрация класса

	//Создание основного окна
	hwnd = CreateWindowW(_T("WindowClass"), _T("Video-Mux Switch"),
		WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, lenghtWindow, hightWindow,
		HWND_DESKTOP, NULL, hInstance, NULL);


	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return msg.wParam;
}
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
