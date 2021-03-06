# QNGraph 

![Logo](https://github.com/qnbhd/QNGraph/blob/master/misc/img/QNGRAPH.png)

[![GitHub license](https://img.shields.io/github/license/qnbhd/qn-graph)](https://github.com/qnbhd/qn-graph)
# Описание 

QNGraph - приложение для построения графиков различных математических функций. Написано на C++ с использованием библиотеки SDL2.

# Запуск

Достаточно установить все библиотеки SDL2 и собрать под вашу операционную систему (С++17). Проверено на XUbuntu. 

# Сведения

+ Для графической составляющей используется графическая библиотека SDL2. 
+ Запускается на стандарте C++17
+ Для виджетов реализованы отдельные классы ```QnButton, QnEdit, QnViewport``` 
+ Все настройки проекта прописаны в отдельном файле ```QNSETTING.hpp``` там можно задать настройки темы, шрифты и многое другое.
+ За работу с системой координат отвечает класс ```QnDekart```. Легко реализовать другие системы координат.
+ За инициализацию всех библиотек отвечает класс ```QNInit```
+ Приложение построено по шаблону проектирования ```Singletone```. Главный класс - ```QNApplication```
+ Для работы с линейной алгеброй были реализованы: 
  - Класс матриц ```Matrix```
  - Класс для многочленов ```Poly```
  - Класс для систем линейных уравнений и их решения (метод Гаусса) ```SLE``` 
  - Класс для интерполяции методом Лагранжа ```Interpolation``` (устарел)
  - Класс для аппроксимации методом наименьших квадратов ```Approximation```
+ Для построения графиков были реализованы:
  - Алгоритм Ву ```WuAlgorithm``` (устарел)
+ Для работы с математическими выражениями были реализованы:
  - Лексический анализатор ```Lexer```
  - Синтаксический анализатор ```Parser```
    * Синтаксический анализатор распознаёт основные математические операции ```+, -, *, /```, а также операцию ```^``` для возведения в степень а также следующие математические функции:
    ```sin, cos, tg(tan), ctg(cot), exp, ln, sgn(sign), abs, sqrt, cbrt, asin, acos, atan, arctg, acot, sinh, cosh, tanh, coth```
  - Основной класс для расчета и основных операций ```MathParser```
  
# Превью

<p align="center">
  <img src="https://github.com/qnbhd/QNGraph/blob/master/misc/img/prev.gif">
</p>
