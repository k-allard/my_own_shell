# minishell

Раздрешенные функции:
malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno

Команды:
- echo - отображает строку теста (с опцией '-n' выводит без завершающего '\n')
- cd - изменяет текущий рабочий каталог (в качестве аргумента принимает абсолютный или относительный адрес; путь является абсолютным, если он начинается с / . В противном случае это относительный путь)
- pwd без опций
- export без опций - выводит имена всех переменных, отмеченных для экспорта в дочерние процессы
- unset без опций - удаляет переменную
- env без опций и аргументов - выводит список всех переменных окружения
- exit без опций
- ; - разделяет команды
- " ' - двойные кавычки позволяют осуществлять раскрытие переменных в строке команды, в то время, как одинарные кавычки позволяют предотвратить такое раскрытие (except for multiline commands)
- < > “>>” перенаправления (except for file descriptor aggregation)
- | - конвейер - вывод одной команды подается на вход другой
- Environment variables ($ followed by characters)
- $?
- ctrl-C, ctrl-D and ctrl-\

Заметки:

* Переменная PATH - набор каталогов (разделяются двоеточиями), в которых расположены исполняемые файлы. После создания запроса запуска пользователем или программой, система будет проверять каждый каталог переменной $PATH слева направо в поисках файла, соответствующего заданной команде. Первая найденная программа выполняется в качестве дочернего процесса командной оболочки или программы, сделавшей запрос.

* Базовый цикл командной оболочки
Чтение: считывание команды со стандартных потоков.
Парсинг: распознавание программы и аргументов во входной строке.
Исполнение: запуск распознанной команды.

* Про обработку сигналов (trap) https://laurvas.ru/bash-trap/

* exit [[код_зав]]. Семантика: exit завершает исполнение оболочки с кодом возврата. Перехват exit командой trap выполняется до завершения оболочки, если только exit выполняется не из этой команды trap. Если n не указана, код возврата равен коду возврата последней выполненной команды. При выполнении exit из trap последней командой считается команда, выполненная непосредственно до выполнения trap.

* Про уровни оболочки и переменную $SHLVL https://solutics.ru/linux/kak-i-pochemu-vy-doPATHlzhny-ispolzovat-peremennuyu-shlvl/

* Fork создает процесс-потомок, который отличается от родительского только значениями PID (идентификатор процесса) и PPID (идентификатор родительского процесса), а также тем фактом, что счетчики использования ресурсов установлены в 0. Блокировки файлов и сигналы, ожидающие обработки, не наследуются. При успешном завершении родителю возвращается PID процесса-потомка, а процессу-потомку возвращается 0. При неудаче родительскому процессу возвращается -1, процесс-потомок не создается, а значение errno устанавливается должным образом.  

* Функция wait приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс не завершится, или до появления сигнала, который либо завершает текущий процесс, либо требует вызвать функцию-обработчик. Если дочерний процесс к моменту вызова функции уже завершился (так называемый "зомби" ("zombie")), то функция немедленно возвращается. Системные ресурсы, связанные с дочерним процессом, освобождаются. 

* Функция waitpid приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в параметре pid, не завершит выполнение, или пока не появится сигнал, который либо завершает текущий процесс либо требует вызвать функцию-обработчик. Если указанный дочерний процесс к моменту вызова функции уже завершился (так называемый "зомби"), то функция немедленно возвращается. Системные ресурсы, связанные с дочерним процессом, освобождаются. Параметр pid может принимать несколько значений:
< -1
означает, что нужно ждать любого дочернего процесса, идентификатор группы процессов которого равен абсолютному значению pid.
-1
означает ожидание любого дочернего процесса; функция wait ведет себя точно так же.
0
означает ожидание любого дочернего процесса, идентификатор группы процессов которого равен идентификатору текущего процесса.
> 0
означает ожидание дочернего процесса, чей идентификатор равен pid.
Источник: https://www.opennet.ru/man.shtml?topic=wait&category=2&russian=0 

* коды возврата exit (https://tldp.org/LDP/abs/html/exitcodes.html):
1 - Catchall for general errors
2 - Misuse of shell builtins (according to Bash documentation)
126 - Command invoked cannot execute
127 - “command not found”
128 - Invalid argument to exit
128+n - Fatal error signal “n”
130 - Script terminated by Control-C


# Сложные примеры

## 1. Множественное перенаправление
Команду:
```shell script
echo text > 1.txt >> 2.txt > 3.txt < 4.txt < 5.txt
```
можно разбить на следующие этапы
1. `> 1.txt` - открыть на запись/создать и очистить файл 1.txt, кинуть ошибку в случае неудачи, OUT команды заменить с stdout на 1.txt
2. `>> 2.txt` - открыть на запись/создать файл 2.txt и перейти в конец, кинуть ошибку в случае неудачи, OUT команды заменить с 1.txt на 2.txt, закрыв 1.txt
3. `> 3.txt` - открыть на запись/создать и очистить файл 3.txt, кинуть ошибку в случае неудачи, OUT команды заменить с 2.txt на 3.txt, закрыв 2.txt
4. `< 4.txt` - открыть на чтение файл 4.txt, кинуть ошибку в случае неудачи, IN команды заменить с stdin на 4.txt
5. `< 5.txt` - открыть на чтение файл 5.txt, кинуть ошибку в случае неудачи, IN команды заменить с 4.txt на 5.txt, закрыв 4.txt
6. `echo text` - выполнить команду, при этом IN команды = 5.txt, а OUT команды = 3.txt

## 2. Перенаправление вывода и pipe
Команду:
```shell script
echo text > 1.txt | cat
```
можно разбить на следующие этапы
1. `> 1.txt` - открыть на запись/создать и очистить файл 1.txt, кинуть ошибку в случае неудачи, OUT команды заменить с stdout на 1.txt
2. `|` - открыть pipe, так как OUT команды слева заменен, то использовать stdin в качестве потока входных данных для pipe
3. `echo text` - выполнить команду, при этом IN команды = stdin, а OUT команды = 1.txt, в случае ошибки прервать выполнение
4. `cat` - выполнить команду, при этом IN команды = stdin, а OUT команды = stdout

## 2. Перенаправление вывода и pipe
Команду:
```shell script
echo text | cat < 1.txt
```
можно разбить на следующие этапы
1. `> 1.txt` - открыть на запись/создать и очистить файл 1.txt, кинуть ошибку в случае неудачи, OUT команды заменить с stdout на 1.txt
2. `|` - открыть pipe, так как OUT команды слева заменен, то использовать stdin в качестве потока входных данных для pipe
3. `echo text` - выполнить команду, при этом IN команды = stdin, а OUT команды = 1.txt, в случае ошибки прервать выполнение
4. `cat` - выполнить команду, при этом IN команды = stdin, а OUT команды = stdout