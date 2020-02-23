using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForMyFuture2
{
    class Class2
    {
        static void Main(string[] args)
        {
            /*
            int[] arrayTables = { 5, 6, 7, 1 };          
            bool openClose = true;
            string header = "Администрирование кафе \"Ультралюкс\" \n";



            while (openClose)
            {
                Console.SetCursorPosition((Console.WindowWidth - header.Length) / 2, 0);
                Console.WriteLine(header);
                Console.WriteLine("Свободные столы: ");
                for (int i = 0; i < arrayTables.Length; i++)
                {
                    Console.WriteLine("За столом № " + (i + 1) + " свободно " + arrayTables[i] + " мест");
                }

                Console.WriteLine("\nВведите команду: ");
                Console.WriteLine( " 1 Забронировать места\n" +
                                   " 2 Выход из программы\n");
                Console.Write("Команда: ");
                switch (Console.ReadLine())
                {
                    case "1":
                        string userTable, userPlace;

                        Console.Write("Укажите номер стола, за которым желаете забранировать места? ");
                        userTable = Console.ReadLine();
                        if (userTable != "")
                        {
                            if (Convert.ToInt32(userTable) > arrayTables.Length || Convert.ToInt32(userTable) < 1 )
                            {
                                Console.Write("Cтол № " + userTable + " отсутствует\n" +
                                              "Нажмите любую клавишу для продолжения ");
                                Console.ReadKey();
                                Console.Clear();
                                continue;
                            }
                        }
                        else
                        {
                            Console.Write("Не введён номер стола\n" +
                                              "Нажмите любую клавишу для продолжения ");
                            Console.ReadKey();
                            Console.Clear();
                            continue;
                        }

                        Console.Write("Сколько мест вы желаете забронировать? ");
                        userPlace =Console.ReadLine();
                        if (userPlace != "")
                        {
                            if (arrayTables[Convert.ToInt32(userTable) - 1] < Convert.ToInt32(userPlace) || Convert.ToInt32(userPlace) < 0)
                            {
                                Console.Write("За столом № " + userTable + " меньше " + userPlace + " мест\n" +
                                              "Нажмите Любую клавишу для продолжения ");
                                Console.ReadKey();
                                Console.Clear();
                                continue;
                            }
                        }
                        else{
                            Console.Write("Не введёно количество мест\n" +
                                              "Нажмите любую клавишу для продолжения ");
                            Console.ReadKey();
                            Console.Clear();
                            continue;
                        }

                        arrayTables[Convert.ToInt32(userTable) - 1] -= Convert.ToInt32(userPlace);
                        Console.Write("Места за столом № " + userTable +" в количестве " + userPlace + " забранированы!\n" +
                                      "Нажмите любую клавишу для продолжения ");
                        Console.ReadKey();

                        break;

                    case "2":
                        openClose = false;
                        break;

                    default:
                        Console.Write("Неверная команда\n" +
                                      "Нажмите Любую клавишу для продолжения ");
                        Console.ReadKey();
                        Console.Clear();
                        continue;
                }
                
                
                Console.Clear();

            }
            Console.Write("Завершение работы ");*/


            //----


            /*
            bool isOpen = true, isFound = false;
            string header = "Библиотека", searchAuthor, row = "", column = "";

           string[,] books =
            {
                {"Пушкин", "Лермонтов","Глуховский"},
                { "Кинг", "Лавкрафт", "По" },
                { "Кристи", "Артур", "Абрамс"}
            };

            while (isOpen)
            {
                Console.Clear();
                Console.SetCursorPosition((Console.WindowWidth - header.Length) / 2, 0);
                Console.WriteLine(header);


                Console.WriteLine("\nВведите команду: ");
                Console.WriteLine(" 1: Узнать автора под определённым индексом\n" +
                                  " 2: Найти книгу по автору \n" +
                                  " 3: Выход");

                Console.Write("Команда: ");
                switch (Console.ReadLine())
                {
                    case "1":

                        Console.Write("Введите номер стеллажа: ");                        
                        column =  Console.ReadLine();

                        if (column != "")
                        {
                            if(Convert.ToInt32(column) <= 0 || Convert.ToInt32(column) > books.GetLength(1))
                            {
                                Console.WriteLine("Стеллаж с номером " + column + " отсутствует\n" +
                                                  "Нажмите любую клавишу для продолжения ");
                                Console.ReadKey();
                                continue;
                            }
                        }
                        else
                        {
                            Console.Write("Не введён номер стелажа\n" +
                                              "Нажмите любую клавишу для продолжения ");
                            Console.ReadKey();
                            continue;
                        }

                        Console.Write("Введите номер полки: ");
                        row = Console.ReadLine();

                        if (row != "")
                        {
                            if (Convert.ToInt32(row) <= 0 || Convert.ToInt32(row) > books.GetLength(0)) 
                            {
                                Console.WriteLine("Полка с номером " + row + " отсутствует\n" +
                                                  "Нажмите любую клавишу для продолжения ");
                                Console.ReadKey();
                                continue;
                            }
                        }
                        else
                        {
                            Console.Write("Не введён номер полки\n" +
                                              "Нажмите любую клавишу для продолжения ");
                            Console.ReadKey();
                            continue;
                        }

                        Console.WriteLine("Книга в стеллаже № " + column + " на полке " + row + " : " + (books[Convert.ToInt32(row) - 1, Convert.ToInt32(column) - 1]) );
                        Console.WriteLine("Нажмите любую клавишу для продолжения ");
                        Console.ReadKey();
                        break;

                    case "2":

                        Console.Write("Введите имя автора: ");
                        searchAuthor = Console.ReadLine();
                        for (int i = 0; i < books.GetLength(0); i++)
                        {
                            for (int j = 0; j < books.GetLength(1); j++)
                            {
                                if (books[i, j].ToLower() == searchAuthor.ToLower())
                                {
                                    isFound = true;
                                    row = Convert.ToString(i + 1);
                                    column = Convert.ToString(j + 1);
                                    
                                }
                            }

                        }

                        if (isFound == true )
                        {
                            isFound = false;
                            Console.WriteLine("Книга с автором " + searchAuthor + " найдена!\n" +
                                          "Её положение: стеллаж № " + column + " полка " + row);
                        }
                        else
                        {
                            Console.WriteLine("Книгу с автором " + searchAuthor + " найти не удалось");
                        }

                        Console.Write("Нажмите любую клавишу для продолжения ");
                        Console.ReadKey();

                        break;

                    case "3":
                        isOpen = false;
                        Console.Clear();
                        Console.Write("Завершение работы ");
                        break;
                    default:
                        Console.Write("Неверная команда\n" +
                                      "Нажмите Любую клавишу для продолжения ");
                        Console.ReadKey();
                       
                        continue;
                }
            }
            ----
            Console.WindowWidth += 50;
            Console.CursorVisible = false;
            int userX = 6, userY = 6;

            bool game = true;

            char[,] map =
            {
                { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', 'O', ' ', '#', ' ', ' ', ' ', ' ', ' ', 'O', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', 'O', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', 'O', ' ', ' ', ' ', 'O', ' ', ' ', '#'},
                { '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            };

            char[] bug = new char[0];

            string scope = "Scope" + 300;

            while (game)
            {
                

               Console.SetCursorPosition(0, 0);
                for (int i = 0; i < map.GetLength(0); i++)
                {
                    for (int j = 0; j < map.GetLength(1); j++)
                    {
                        Console.Write(map[i,j]);
                    }
                    Console.WriteLine();
                }
              
                Console.SetCursorPosition(userY, userX);
                if (map[userX, userY] == 'O' )
                {
                    map[userX, userY] = ' ';
                    char[] tempbag = new char[bug.Length + 1];
                    for(int i = 0; i < bug.Length; i++)
                    {
                        tempbag[i] = bug[i];
                    }
                    tempbag[tempbag.Length - 1] = 'O';
                    bug = tempbag;

                }
                Console.Write("X");

                Console.SetCursorPosition(0, Console.WindowHeight - 10);
                Console.Write("Сумка: ");
                for (int i = 0; i < bug.Length; i++)
                {
                    Console.Write(bug[i] + " ");
                }

                ConsoleKeyInfo charKey = Console.ReadKey();
                switch (charKey.Key)
                {
                    case ConsoleKey.UpArrow:
                        if (map[userX-1,  userY] != '#')
                        {
                            userX--;
                        }
                        
                        break;

                    case ConsoleKey.DownArrow:
                        if (map[userX + 1, userY] != '#')
                        {
                            userX++;
                        }
                        break;

                    case ConsoleKey.RightArrow:
                        if (map[userX, userY + 1] != '#')
                        {
                            userY++;
                        }
                        break;

                    case ConsoleKey.LeftArrow:
                        if (map[userX, userY - 1] != '#')
                        {
                            userY--;
                        }
                        break;

                    case ConsoleKey.X:
                        game = false;
                        break;

                    default:
                        continue;
                }
                Console.Clear();*/

            int[] array = new int[0];
            int[] localMax = new int[0];

            Random rand = new Random();

            Console.WriteLine("Исходный массив:");
            for (int i = 0; i < array.Length; i++)
            {
                array[i] = rand.Next(0, 10);
                Console.Write(array[i] + " ");
            }
            Console.WriteLine();


            for (int i = 0; i < array.Length; i++)
            {
                if (
                    i == 0 && array[i] > array[i + 1] ||
                    i > 0 && i < array.Length - 1 && array[i] > array[i - 1] && array[i] > array[i + 1] ||
                    i == array.Length - 1 && array[i] > array[i - 1]
                   )

                {

                    int[] tempLocMax = new int[localMax.Length + 1];
                    for (int j = 0; j < localMax.Length; j++)
                    {
                        tempLocMax[j] = localMax[j];
                    }
                    localMax = tempLocMax;

                    localMax[localMax.Length - 1] = array[i];

                }

            }


            Console.Write("\nЛокальные максимумы: ");
            for (int i = 0; i < localMax.Length; i++)
            {
                Console.Write(localMax[i] + " ");
            }
            Console.ReadKey();

        }
    }

}
