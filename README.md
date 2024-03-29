# Отчёт по лабораторной работе №2

## Что такое включение
В программировании **включение** означает использование готовых (уже описанных) компонентов в новом контексте. Новый компонент может использовать интерфейс, уже определённый в другом компоненте, перенаправляя соответствующие вызовы методов. Это способствует улучшению организации кода и облегчает его поддержку и изменение. **Включение реализуется** добавлением в новый компонент виртуальной таблицы нужного интерфейса и ссылки на уже описанную реализацию, после чего при инициализации нового компонента происходит запрос реализации у старого компонента, сохраняемой в виде ссылки в созданное поле. Методы виртуальной таблицы интерфейса имплементируются и представляют собой обращение к существующей реализации, сохранённой в поле виртуальной таблицы. **То есть делается обёртка над существующими методами.**
## Что такое агрегирование
**Агрегирование** в контексте программирования представляет собой специфический случай включения, при котором интерфейс не повторно создаётся на основе имеющейся реализации, а напрямую запрашивается у существующего компонента. Этот подход предполагает, что компоненты могут быть агрегированы только в том случае, **если они явно поддерживают такую возможность**. Для реализации поддержки агрегирования в компоненте необходимо внести изменения, добавив поле `IEcoUnknown*` внешнего компонента и поле с реализацией собственного интерфейса `IEcoUnknown`. Этот подход позволяет обеспечить передачу запросов компонентов на внешний компонент в случае, если запросы не могут быть выполнены внутри компонента. При агрегировании внешний компонент **обязан предоставить ссылку на себя внутреннему компоненту**, что обеспечивает эффективное взаимодействие между ними. **Агрегирование реализуется** добавлением в компонент поля для сохранения интерфейса агрегируемого компонента. Через это поле происходит запрос к имплементированным интерфейсам внутренней компоненты. Далее необходимо инициализировать компонент, запрашивая интерфейс `IEcoUnknown`, в который передаётся ссылка на себя. После этого запросы перенаправляются на нужные интерфейсы, которые имплементирует внутренний компонент. 


## Порядок включения и агрегирования компонентов калькулятора
В данной работе только компонент B поддерживает агрегацию, **тем более что компонент C и компонент A имеют один ID, что делает невозможным работу с C**. Порядок действий при агрегации следующий:
-	Сначала пытаемся агрегировать B для доступа к интерфейсу X
-	В случае неудачи агрегирования B, мы пытаемся включить компонент A, который, как и B имплементирует интерфейс X. Если и это не удалось, то доступ к интерфейсу X невозможен
-	Затем мы пробуем включить интерфейс Y из компонента D (E так же реализует интерфейс Y)
-	Если включение компонента D не удалось, мы пытаемся включить компонент E. Если и это не удаётся, то работа с интерфейсом Y также становится невозможной
-	Можно запросить доступ к X через компонент E, но это не имеет смысла, так как для функционирования X необходима компонента B
## Заключение
Для корректного запуска собранного приложения необходимо положить рядом с исполняемым файлом .dll-файлы, связанные с этой лабораторной работой. Однако если каких-то (но не всех) файлов будет не хватать, компонент сделает попытку получить нужные данные из других .dll-файлов и даже в случае неуспеха завершится корректно, но не выполнит свою задачу. Интерфейс может получить ссылку на себя и на компонент, из которого был получен сам. Кроме того, из любого интерфейса можно получить любой другой интерфейс. Это свойство наиболее известно как принцип подстановки Барбары Лисков (терминология SOLID) Оно гласит, что объекты должны быть заменяемыми своими подтипами, то есть объекты базового типа могут быть заменены объектами его подтипов без изменения корректности программы. Это свойство обеспечивает гибкость и расширяемость программ, позволяя использовать объекты разных типов через их общие интерфейсы.
## Результаты работы:
```sh
PS D:\c\eco-lab1> d:\c\eco-lab1\build\Debug\lab2.exe
Calculator:
        10 * 5 = 50
        10 / 5 = 2
        5 + 5 = 10
        10 - 5 = 5

Queries to different interfaces:
        query interface X from interface EcoLab1
        query interface Y from interface EcoLab1
        query inteface EcoLab1 from interface EcoLab1
        query interface X from interface X
        query interface Y from interface X
        query interface EcoLab1 from interface X
        query interface X from interface Y
        query interface Y from interface Y
        query IEcoLab1 from IY

Test aggregated binary search:
Successfully called IEcoLab1 aggregated by CEcoLab2
array under test: [-788, -518, -275, -214, -141, 163, 175, 203, 225, 348, 425, 485, 599, 645, 718]
2 expected to be returned, 2 got
```