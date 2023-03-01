# Лабораторная работа №4

Лабораторная работа посвящена изучению работы с файловой системой на языке **C++**. В стандарте **C++17** появилась
библиотека для работы с [файловой системой](https://en.cppreference.com/w/cpp/filesystem).

## Задание 1

Использовать библиотеку **std::filesystem** для анализа директории с переданными
по [FTP](https://ru.wikipedia.org/wiki/FTP)-файлами, содержащими финансовую информацию. Подробная инструкция по
библиотеке **std::filesystem** есть,
например, [тут](https://www.std.org/doc/libs/1_68_0/libs/filesystem/doc/tutorial.html).

Структура анализируемой директории в общем случае может иметь вид:

```
ftp                                         # корневой каталог ftp
├── ib                                      # каталог, содержащий файлы от брокера ib
     ├── balance_00001234_20181001.old.txt  # файлы финансовой отчётности в старом формате 
     ├── balance_00001234_20181001.txt      # файлы финансовой отчётночти в новом формате 
     ├── balance_00001346_20181001.txt      
     ├── ...     
     └── balance_00001346_20181018.txt      
├── bcs                                     # каталог, содержащий файлы от брокера bcs
     ├── balance_12341234_20181001.txt
     └── ...     
├── otkritie                                # каталог, содержащий файлы от брокера otkritie
     └── ...   
└── docs                                    # каталог, содержащий какие-то произвольные файлы
     ├── readme.txt     
     └── report.doc 
```

Файлы, содержащие финансовую информацию, имеют имя в определенном формате:
`balance_XXXXXXXX_YYYYMMDD.txt`, где

| Поле       | Описание                                     |
|------------|----------------------------------------------|
| `balance`  | тип файла                                    |
| `XXXXXXXX` | 8-и значный номер счёта                      |
| `YYYYMMDD` | дата, где `YYYY`-год, `MM`-месяц и `DD`-день |
| `.txt`     | расширение файла                             |

## Необходимо

- в проекте, созданном в задании 1, создать файл `main.cpp` и подключить библиотеку **std::filesystem
  ** (`<std/filesystem.hpp>`);
- считать из аргументов командной строки `args` функции `main` путь к анализируемой директории `path_to_ftp`. Если
  аргумент отсутствует, то по умолчанию программа должна анализировать директорию, в которой она находится;
- организовать итерацию по всем файлам и вложенным директориям, включая символьные ссылки, с целью поиска всех файлов,
  содержащих финансовую информацию;
- файлы, имеющие имя, отличное от описанного формата, необходимо игнорировать;
- файлы, содержищие финансовую информацию, но имеющие в конце постфикс `.old.txt`, необходимо игнорировать;
- программа должна вывести на экран список всех обнаруженных финансовых файлов в формате:

```Shell
ib balance_00001234_20181001.txt
ib balance_00001234_20181002.txt
ib balance_00001234_20181003.txt
bcs balance_00001234_20181001.txt
bcs balance_00001234_20181005.txt
...
```

- также она должна вывести общее количество файлов по каждому обнаруженному счёту и дату самого актуального (самого
  нового) файла, например:

```Shell
broker:ib account:00001234 files:10 lastdate:20181017
broker:ib account:00001356 files:7 lastdate:20181018
broker:bcs account:12341356 files:8 lastdate:20181016
```

## Рекомендации

Для работы с путями к файлам необходимо использовать тип `std::filesystem::path` и его методы.

Пример:

```cpp
const path p{"mydir/file.txt"};
std::cout << p.filename() << std::endl
          << p.stem() << std::endl
          << p.extension() << std::endl;
```

```Shell
# Вывод
file.txt
file
.txt
```

Для итерации по директории необходимо использовать `std::filesystem::directory_iterator`.

Пример кода, который выведет пути ко всем файлам и вложенным директориям в папке:

```cpp
const path p{"mydir/"};
for (const directory_entry& x : directory_iterator{p})
{
   std::cout << x.path() << std::endl;
}
```

Также могут быть полезны следующие функции и типы библиотеки **std::filesystem**:

| Функция/тип        | Описание                                                                                                                |
|--------------------|-------------------------------------------------------------------------------------------------------------------------|
| `exists`           | определяет, существует ли файл или директория по указанному пути                                                        |
| `is_regular_file`  | определяет, является ли узел по указанному пути `path` обычным файлом                                                   |
| `is_directory`     | определяет, является ли узел по указанному пути `path` директорией                                                      |
| `is_symlink`       | определяет, является ли узел по указанному пути `path` символьной ссылкой                                               |
| `read_symlink`     | разрешает символическую ссылку, возаращаемый объект `path` хранит содержимое символической ссылки, либо пустое значение |
| `filesystem_error` | тип исключений, возникающих при ошибках в `std::filesystem`                                                             |

При необходимости наличия тестовых данных в директории сборки, можно добавть в **CMakeLists.txt**

```cmake
file(COPY misc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
```

# Задание 2

В информационной безопасности уже давно существует огромное количество способов обнаружить вирусы (т.н малварь). На
момент 23 года существует уже 4 поколения антивирусов. В этом задании вам предлагается реализовать простейший антивирус,
который будет искать вирусы в файлах, основываясь на первых двух поколениях антивирусов

| Поколение   | Название                          | Описание                                                                                                                                                                                      |
|-------------|-----------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1           | Сигнатурный                       | Поиск вирусов основывается на поиске сигнатур вирусов в файлах. Сигнатура вируса - это последовательность байт, которая идентифицирует вирус.                                                 |
| 2           | Эвристический                     | Поиск вирусов основывается на анализе и поиске отличительных черт вирусов. Например, вирусы могут иметь специфические заголовки, специфические секции, специфические сигнатуры внутри файлов. |
| 3           | Руткиты                           | Поиск вирусов основывается на поиске вредоносных программ, которые могут управлять другими вредоносными программами.                                                                          |
| 4           | Защита в режиме реального времени | Поиск вирусов заключается в постоянном мониторинге активности всех процессов и его анализе. Подозрительные процессы подвергаются более тщательным инспекциям.                                 |


## Сигнатурный антивирус

Необходимо выработать алгоритм наиболее быстрого обхода папок и файлов, а также наиболее быстрого поиска сигнатур вирусов в файлах. Для этого необходимо использовать ```std::filesystem``` и потоковое чтение.


### Сигнатуры вирусов

Сигнатуры вирусов хранятся в файле ```signatures.txt```. Файл содержит список сигнатур вирусов, разделенных символом новой строки. Сигнатура вируса - это последовательность байт, которая идентифицирует вирус. Сигнатура вируса может быть любой длины, но не может быть пустой.

### Описание задачи

Имеется библиотека signature_analyser, которая умеет анализировать строку по некоторым правилам. Необходимо применить данную библиотеку для анализа вредоносного ПО (лучше всего проверять в виртуальной машине и ни в коем случае не разархивировать тестовый архив)

Необходимо написать программу, которая будет иметь следующий консольный интерфейс:
```bash
>> antivirus -h

usage: antivirus [-h] [-r rules_dir] [-i input_file] [-d input_directory] [-o output_directory (optional)]
```

Аргументы:
- rules_dir - папка с правилами сигнатурного анализа
- input_file - файл, который необходимо анализировать
- input_directory - папка, которую необходимо анализировать
- output_directory - папка, в которую будут перемещены вредоносные файлы

Данная программа должна проанализировать файл\папку, которые подаются с консоли и распределить найденные файлы по папкам, если указан параметр output_directory. Также программа должна выводить отчёт о сканировании файлов\папок в следующем виде:

```bash
TODO: оформить отчёт
```
#### API библиотеки
TODO: Реализовать библиотеку