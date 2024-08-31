# Обфускатор C-кода / C Code Obfuscator

## Описание / Description

Обфускатор C-кода – это программа, которая предназначена для усложнения понимания исходного кода на языке C. Программа выполняет следующие действия:

+ Изменяет имена переменных
+ Вставляет случайные функции и условия
+ Обрабатывает строки и числа
+ Убирает комментарии
+ Выполняет другие манипуляции для повышения сложности анализа кода

C Code Obfuscator is a program designed to make C code harder to understand. It:

+ Changes variable names
+ Inserts random functions and conditions
+ Processes strings and numbers
+ Removes comments
+ Performs other operations to increase code complexity

## Как использовать / How to Use

### Компиляция / Compilation

Для компиляции программы используйте компилятор C++. Например:

```bash
g++ -o obfuscator main.cpp
```
To build the obfuscator, use the command:
```bash
g++ -o obfuscator main.cpp
```

### Запуск / Execution
Пример запуска программы с параметрами:
```bash
./obfuscator --f input_file.c --comment_remover --variable_renamer --process_numbers
```
Example of running the program with options:
```bash
./obfuscator --f input_file.c --comment_remover --variable_renamer --process_numbers
```
### Опции / Options
| Опция / Option               | Описание / Description                                                            |
|-------------------------------|-----------------------------------------------------------------------------------|
| `--f <filename>`              | Указание входного файла / Specify the input file.                                 |
| `--comment_remover`           | Удаление всех комментариев из исходного кода / Remove all comments from the source code. |
| `--process_numbers`           | Преобразование чисел / Process numbers.                                           |
| `--variable_renamer`          | Переименование переменных / Rename variables.                                     |
| `--convert_numbers_to_hex`    | Преобразование чисел в шестнадцатеричный формат / Convert numbers to hexadecimal. |
| `--insert_random_functions`   | Вставка случайных функций / Insert random functions.                             |
| `--probability <number>`      | Задать вероятность вставки случайных функций (0-100) / Set the probability of inserting random functions (0-100). |
| `--insert_dummy_conditions`   | Вставка ложных условий / Insert dummy conditions.                                |
| `--depth <number>`            | Задать глубину вложенности для ложных условий / Set the nesting depth for dummy conditions. |
| `--process_string`            | Обработка строк / Process strings.                                               |
| `--remove_extra_spaces`       | Удаление лишних пробелов / Remove extra spaces.                                  |
| `--help`                      | Показать справку / Show help.                                                    |
### Пример использования / Example Usage
Для преобразования исходного файла с удалением комментариев, переименованием переменных и обработкой чисел:
```bash
./obfuscator --f input.c --comment_remover --variable_renamer --process_numbers
```
To transform a source file with comment removal, variable renaming, and number processing:
```bash
./obfuscator --f input.c --comment_remover --variable_renamer --process_numbers
```
### Предупреждение / Warning
⚠️ В программе могут быть ошибки, и в некоторых случаях обфусцированный код может перестать работать корректно. Рекомендуется тщательно тестировать результаты работы обфускатора.

⚠️ This program may contain bugs, and in some cases, the obfuscated code may stop working correctly. It is recommended to thoroughly test the results of the obfuscator.

