# Краткое описание

Программка, которая применяет симплекс, двойсвтенный симплекс метод, метод отсечений Гомори и целочисленный метод отсечений к задачам линейного программирования. 

# Как использовать

В папке `application` есть файл `main.cpp`, там подключены все необходимые зависимости для работы с программой. 

## Базовый пример использования

```
    obv::Table table; // инициализация пустой таблицы

    table.readFile("./test.txt"); // считывание таблицы из файла
    obv::lpalgs::simplexMethod(table);
    obv::lpalgs::cuttingPlane(table);
    std::cout << table << "\n\n";
```

Все методы и классы находятся в просранстве имен `obv::`. Для начала нужно инициализировать объект таблицы, после чего считать таблицу из файла.

После конфигурации проекта cmake'ом файл `test.txt` будет лежать в папке с исполняемыми файлами. Из него считывается таблица в следующем формате.

```
    3 3         // первое значение - число переменных; второе значение - число ограничений
    4 5 3       // max f = 4*x1 + 5*x2 + 3*x3
    2 3 1 20    //         2*x1 + 3*x2 + 1*x3 <= 20
    1 2 2 25    //         1*x1 + 2*x2 + 2*x3 <= 25
    2 1 3 15    //         2*x1 + 1*x2 + 3*x3 <= 15
```

Пока (и, скорее всего, так останется навсегда) поддежриватеся решение задач только в том формате, что указан выше (max f; <=)

Стоит упомнять, что таблица хранится в классе obv::Table вот в таком (столбцовом) формате, после чтения из файла условия будеть записана такая матрица. 

```
  первое значение - значение целевой функции, после первой строки идут значения переменных
  ↓
  0  4  5  3  ← целевая фукниця
  0  1  0  0
  0  0  1  0
  0  0  0  1
 20 -2 -3 -1
 25 -1 -2 -2
 15 -2 -1 -3
```

После применения алгоритмов получить оптимальное значение можно обратившись к таблице по индексу [0, 0]

```
    obv::Table table;
    
    ...

    std::cout << table(0, 0) << "\n";
```


## Методы

Первый аргумент методов - объект класса `obv::Table`. Второй аргумент - вывод промежуточных этапов решения - `true/fasle`. По умолчанию значение аргумента `false`.

1. Сипмлекс метод
    - `obv::lpalgs::simplexMethod(<table>, <debug>)` 

2. Двойсвтенный сипмлекс метод
    - `obv::lpalgs::dualSimplexMethod(<table>, <debug>)` 

3. Метод отсечений Гомори
    - `obv::lpalgs::cuttingPlane(<table>, <debug>)` 
    - перед применением этого метода сначала нужно найти нецелочисленное оптмиальное значение для задачи, применив `obv::lpalgs::simplexMethod`, как показано в примере

4. Полностью целочисленный метод отсечений
    - `obv::lpalgs::integerCuttingPlane(<table>, <debug>)` 

Все методы изменяют значения полученной на вход таблицы.

# Класс для замера скорости работы алгоритмов

Возможно когда-нибудь (никогда) я доделаю это.

В папке `application` есть файл `perf_app.cpp`, там подключены все необходимые зависимости для замеров эффективности алгоритмов.

В классе `obv::Perf` есть методы для замеров времени, записи результата и сохранения всех результатов в файл. Для генерации таблиц можно использовать метод 

    `Table::changeColumns(size_t changedColumn, size_t sourceColumn, int coefficient, sign sign_value)`

- Первый аргумент - номер колонки, которую надо изменить
- Второй аргумент - номер колонки значения которая будут прибавляться\вычитаться
- Третий аргумент - коэффициент на который будет умножена колонка, которая указана во втором аргументе
- Четвертый аргумент - знак операции obv::Table::MINUS или obv::Table::PLUS 

# Проблемы

Поскольу для предствления рациональных чисел используются стандартные типы (сейчас int, но long long очевидно не решает проблему), то при решении задач может (и происходит) переполнение переменных. Особенно часто это будет происходить при попытке применения отсечений Гомори. В таком случае метод просто будет бескончно считать непонятно что, программа зависнет после считывания файла.

Решением является использование какой-нибдуь библиотеки для вычислений с числами произвольного размера, например GMP. Если кто-то готов переписать тут все под это дело - я только за.
