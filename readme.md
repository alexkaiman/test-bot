### Тестовый телеграм бот
----------
>[!NOTE]
>Написан в качестве скелета. Не расчитан на работу как служба. Просто запустился, сделал свое дело и закрылся.

#### Написан на C++
**Может:**
1. Читать конфиг
2. Отправлять сообщение с эмодзи в чат по ID
3. Ведет лог
4. Принимает аргументы:
```bash
-l, --log <файл>   Путь к лог-файлу
-c, --conf <файл>  Путь к конфигурационному файлу
-m, --msg <текст>  Пользовательское сообщение
-i, --id <CHAT_ID> ID чата для отправки сообщения
-h, --help         Показать эту справку
```
* Тестировалось на FreeBSD
```bash
make clean && make
```
>[!IMPORTANT]
>требуется
>* Library for building Telegram clients. TDLib: (https://github.com/tdlib/td)
 ```bash
pkg install tdlib
```
 * Simple .INI file parser written in C ( https://github.com/benhoyt/inih)
```bash
 pkg install inih
```
