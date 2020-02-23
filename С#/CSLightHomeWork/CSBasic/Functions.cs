using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ForMyFuture2
{
    class Class2
    {
        /*
        static void Main(string[] args)
        {
            /*
            int[] ar =  new int[5];
            int[,] ar2 = new int[5,5];
            ar = Resize(ar, 10);
            ar2 = Resize(ar2, 10, 10);
            Console.WriteLine(ar.Length);
            
            int health = 5, maxHealth = 10;
            int mana = 5, maxMana = 10;
            while(true)
            {
                Console.Clear();
                DrawBar(health, maxHealth, ConsoleColor.Red, 0);
                DrawBar(mana, maxMana, ConsoleColor.Blue, 1, '@');

                Console.WriteLine();
                Console.Write("Введите число на которое изменятся Жизни ");
                health += Convert.ToInt32(Console.ReadLine());

                Console.Write("Введите число на которое изменятся Мана ");
                mana += Convert.ToInt32(Console.ReadLine());

                //Console.ReadKey();
            }
            
            
        }

        static void DrawBar(int value, int maxValue, ConsoleColor color, int position, char symbol = ' ' )
        {
            ConsoleColor defaultColor = Console.BackgroundColor;
            string bar = "";
            for (int i = 0; i < value; i++)
            {
                bar += symbol;
            }
            Console.SetCursorPosition(0, position);
            Console.Write('[');
            Console.BackgroundColor = color;
            Console.Write(bar);

            bar = "";
            Console.BackgroundColor = defaultColor;

            for (int i = value; i < maxValue; i++)
            {
                bar += symbol;
            }
            Console.Write(bar + ']');
        }
        /*
        ar2 = Resize(ar2, 10, 10);( int[] array, int size)
        {
            int[] temArray = new int[size];
            for(int i = 0; i < array.Length; i++)
            {
                temArray[i] = array[i];
            }
            array = temArray;
            return array;
        }
        static int[,] Resize(int[,] array, int x, int y)
        {
            int[,] tempArray = new int[x, y];
            for (int i = 0; i < array.GetLength(0); i++)
            {
                for (int j = 0; j < array.GetLength(1); j++)
                {
                    tempArray[i,j] = array[i,j];
                }
            }
            array = tempArray;
            return array;*/

        //-----------
        /*
                static void Main(string[] args)
                {
                    bool isPlaying = true, isAlive = true; ;

                    int pacX, pacY;
                    int pacDirX = 0, pacDirY = 1;

                    int ghostX, ghostY;
                    int ghostDirX = 0, ghostDirY = -1;

                    int target = 0, alltarget = 0;

                    Random rand = new Random();

                    Console.CursorVisible = false;
                    char[,] map = ReadMap("map1", out pacX, out pacY, out ghostX, out ghostY, ref alltarget);
                    DrawMap(map);

                    while (isPlaying)
                    {
                        if (Console.KeyAvailable)
                        {
                            ConsoleKeyInfo key = Console.ReadKey(true);
                            ChangeDirect(key, ref pacDirX, ref pacDirY);

                        }
                        if (map[pacX + pacDirX, pacY + pacDirY] != '#')
                        {
                            CollectTarget(ref pacX, ref pacY, ref target, ref map);
                            Move(map, '@', ref pacX, ref pacY, pacDirX, pacDirY);

                        }
                        if (map[ghostX + ghostDirX, ghostY + ghostDirY] != '#')
                        {
                            Move(map, '&', ref ghostX, ref ghostY, ghostDirX, ghostDirY);
                        }
                        else
                        {
                            ChangeDirect(rand, ref ghostDirX, ref ghostDirY);
                        }
                        if (ghostX == pacX && ghostY == pacY)
                        {
                            isAlive = false;
                        }

                        Console.SetCursorPosition(0, 20);
                        Console.Write($"Собрано {target}/{alltarget} $");

                        System.Threading.Thread.Sleep(200);

                        if (target == alltarget || isAlive == false )
                        {
                            isPlaying = false;
                            Console.SetCursorPosition(0, 21);
                        }
                    }
                    if (target == alltarget)
                    {
                        Console.WriteLine("Вы победили!");

                    }
                    else if (isAlive == false)
                    {
                         Console.WriteLine("Вы проиграли!");

                    }
                    Console.ReadKey();
                }

                static void Move(char[,] map, char symbol, ref int X, ref int Y, int DX, int DY)
                {
                    Console.SetCursorPosition(Y, X);
                    if (symbol == '@')
                    {
                        Console.Write(' ');

                    }
                    else
                    {
                        Console.Write(map[X, Y]);
                    }

                    X += DX;
                    Y += DY;

                    Console.SetCursorPosition(Y, X);
                    Console.Write(symbol);

                }
                static void CollectTarget(ref int X, ref int Y, ref int targets, ref char[,] map)
                {
                    if (map[X, Y] == '$')
                    {
                        targets++;
                        map[X, Y] = ' ';
                    }

                }

                static void ChangeDirect(ConsoleKeyInfo key, ref int DX, ref int DY)
                {
                    switch (key.Key)
                    {
                        case ConsoleKey.UpArrow:
                            DX = -1; DY = 0;
                            break;

                        case ConsoleKey.DownArrow:
                            DX = 1; DY = 0;
                            break;

                        case ConsoleKey.RightArrow:
                            DX = 0; DY = 1;
                            break;

                        case ConsoleKey.LeftArrow:
                            DX = 0; DY = -1;
                            break;


                    }
                }
                static void ChangeDirect(Random rand, ref int DX, ref int DY)
                {
                    int ghostDir = rand.Next(1, 5);
                    switch (ghostDir)
                    {
                        case 1:
                            DX = -1; DY = 0;
                            break;

                        case 2:
                            DX = 1; DY = 0;
                            break;

                        case 3:
                            DX = 0; DY = 1;
                            break;

                        case 4:
                            DX = 0; DY = -1;
                            break;

                    }

                }
                static char[,] ReadMap(string nameMap, out int pacX, out int pacY, out int ghostX, out int ghostY, ref int allTarget)
                {
                    pacX = pacY = 0;
                    ghostX = ghostY = 0;
                    allTarget = 0;

                    string[] newFile = File.ReadAllLines($"maps/{nameMap}.txt");
                    char[,] map = new char[newFile.Length, newFile[0].Length];

                    for (int i = 0; i < map.GetLength(0); i++)
                    {
                        for (int j = 0; j < map.GetLength(1); j++)
                        {
                            map[i, j] = newFile[i][j];
                            if (map[i, j] == 'x')
                            {
                                map[i, j] = '@';
                                pacX = i;
                                pacY = j;
                            }
                            else if (map[i, j] == 'g')
                            {
                                map[i, j] = '$';
                                ghostX = i;
                                ghostY = j;
                            }
                            else if (map[i, j] == ' ')
                            {
                                map[i, j] = '$';
                                allTarget++;
                            }

                        }
                    }
                    return map;
                }
                static void DrawMap(char[,] drawMap)
                {
                    for (int i = 0; i < drawMap.GetLength(0); i++)
                    {
                        for (int j = 0; j < drawMap.GetLength(1); j++)
                        {
                            Console.Write(drawMap[i, j]);
                        }
                        Console.WriteLine();
                    }
                }*/

        static void Main(string[] args)
        {
            Random rand = new Random();

            int mapWidth = rand.Next(20, 30);
            int mapHeight = rand.Next(10, 20);

            int targets = 0, allTargets;

            int pacX, pacY;
            int pacDirX = 0, pacDirY = 0;

            bool isPlaying = true;

            Console.CursorVisible = false;

            char[,] map = new char[mapHeight, mapWidth];
            ConsoleColor defaultColor = Console.ForegroundColor;

            DrawMap(ref map);
            allTargets = Targets(ref map);
            Player(ref map, out pacX, out pacY);

            Console.ForegroundColor = defaultColor;


            while(isPlaying)
            {

                if (Console.KeyAvailable)
                {
                    ConsoleKeyInfo key = Console.ReadKey(true);
                    ChangeDirect(key, ref pacDirX, ref pacDirY);

                }
                if (map[pacX + pacDirX, pacY + pacDirY] != '#')
                {
                    Move(map, '@', ref pacX, ref pacY, pacDirX, pacDirY);
                    CollectTarget(ref pacX, ref pacY, ref targets, ref map);
                    
                }
                Console.ForegroundColor = defaultColor;
                Console.SetCursorPosition(0, 20);
                Console.Write($"Собрано {targets}/{allTargets} $");

                System.Threading.Thread.Sleep(200);

                if (targets == allTargets)
                {
                    Console.SetCursorPosition(0, 21);
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("Вы победили!");
                    isPlaying = false;
                }
            }

            Console.ReadKey();
        }

        static void Move(char[,] map, char symbol, ref int X, ref int Y, int DX, int DY)
        {
            Console.SetCursorPosition(Y, X);
            Console.Write(' ');

            X += DX;
            Y += DY;

            Console.SetCursorPosition(Y, X);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write(symbol);

        }
        static void ChangeDirect(ConsoleKeyInfo key, ref int DX, ref int DY)
        {
            switch (key.Key)
            {
                case ConsoleKey.UpArrow:
                    DX = -1; DY = 0;
                    break;

                case ConsoleKey.DownArrow:
                    DX = 1; DY = 0;
                    break;

                case ConsoleKey.RightArrow:
                    DX = 0; DY = 1;
                    break;

                case ConsoleKey.LeftArrow:
                    DX = 0; DY = -1;
                    break;


            }
        }
        static void CollectTarget(ref int X, ref int Y, ref int targets, ref char[,] map)
        {
            if (map[X, Y] == '$')
            {
                targets++;
                map[X, Y] = ' ';
            }

        }


        static void DrawMap(ref char[,] map)
        {
            DrawBackgound(ref map);
            Walls(ref map);           


            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    Console.Write(map[i, j]);
                }
                Console.WriteLine();
            }            

        }
        static void DrawBackgound(ref char[,] map)
        {
            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    if (i == 0 || i == map.GetLength(0) - 1) map[i, j] = '#';
                    else if (j == 0 || j == map.GetLength(1) - 1) map[i, j] = '#';
                    else map[i, j] = ' ';
                }

            }
        }
        static void Walls(ref char[,] map)
        {
            int wallBegin = 0, wallEnd = 0;
            Random rand = new Random();

            for (int i = 0; i < map.GetLength(0); i++)
            {
                if (i > 0 && i < map.GetLength(0) - 1 && i % 2 == 0)
                {
                    wallBegin = rand.Next(1, map.GetLength(1) / 2);
                    wallEnd = rand.Next(wallBegin + 3, map.GetLength(1) - 2);

                    for (int j = wallBegin; j <= wallEnd; j++)
                    {
                        map[i, j] = '#';
                    }
                }

            }
        }
        static int Targets(ref char[,] map)
        {
            Random rand = new Random();
            int allTargets = 0;
            bool existTargeet;            
            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    Console.SetCursorPosition(j, i);
                    existTargeet = Convert.ToBoolean(rand.Next(0, 2));
                    if (map[i, j] == ' ' && existTargeet == true) 
                    {
                        map[i, j] = '$';
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.Write('$');
                        
                        allTargets++;
                    }
                   
                }
            }
            return allTargets;
        }
        static void Player(ref char[,] map, out int pacX, out int pacY)
        {
            pacX = pacY = 0;
            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    Console.SetCursorPosition(j, i);
                    if (map[i, j] == ' ')
                    {
                        map[i, j] = '@';
                        pacX = i;
                        pacY = j;
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.Write('@');
                        j = map.GetLength(1) - 1;
                        i = map.GetLength(0) - 1;
                    }
                }
                
            }

        }

    }
}
