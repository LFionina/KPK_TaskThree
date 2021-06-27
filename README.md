# KPK_TaskThree
Курсы повышения квалификации  по проектному программированию на языке С++

#  ПРОЕКТ 3.  КОМПЬЮТЕРНАЯ ИГРА ("БРОДИЛКА").
--------------------------------------------------------------------------
## Идея
По полю с изображением небольшого лабиринта двигается герой игры. Управление движением осуществляется клавишами "Вверх", "Вниз", "Вправо", "Влево". 
На пути от старта к финишу, герою предстоит справиться с небольшими заданиями, которые спрятаны в подарках.

![game](https://user-images.githubusercontent.com/80356955/123539471-fef5b780-d74a-11eb-84c2-22f81ba280c5.png)

## Этап 1. Прорисовка игрового поля, карты и элементов игры
Поле, карта и элементы игры созданы в векторном редакторе Inkscape и переконвертированы в bmp формат при помощи стандартного приложения Paint. 
| Элемент | Орисание|
| ------- | ------- |
|![presentBlue](https://user-images.githubusercontent.com/80356955/123540422-f358bf80-d74f-11eb-9147-7b05b3e7c181.png)| Подарки разного цвета - предусматривают выбор задания или платы за проход на перекрестке| 
|![like](https://user-images.githubusercontent.com/80356955/123540420-f2c02900-d74f-11eb-872f-728e20692fb2.png)| Озеро - задание ...|
|![stadium](https://user-images.githubusercontent.com/80356955/123540418-f2279280-d74f-11eb-9018-9d37c2cade70.png)| Стадион - задание ...|
|![school](https://user-images.githubusercontent.com/80356955/123540417-f18efc00-d74f-11eb-8f31-f309cdda61b9.png)| Школа - задание...|
|![food](https://user-images.githubusercontent.com/80356955/123540419-f2c02900-d74f-11eb-8195-0f772648c667.png)| Фудкорт - задание|
|![personFront](https://user-images.githubusercontent.com/80356955/123540421-f2c02900-d74f-11eb-8792-59a4f5f55198.png)| Герой|

## Этап 2. Вывод игрового поля на экран и настройка прохода по лабиринту.
Для "путешествия" по лабиринту необходима структура, которая будет отвечать за героя игры, его прорисовку и управление движением.
![2-1](https://user-images.githubusercontent.com/80356955/123540935-97436a80-d752-11eb-9a33-f138df5fc892.png)

![2-2](https://user-images.githubusercontent.com/80356955/123541237-7a0f9b80-d754-11eb-960d-3ec61ef1666d.png)




