### Тестовый телеграм бот
----------
#### Написан на C++
**Может:**
1. Читать конфиг
2. Отправлять сообщение с эмодзи в чат по ID
3. Ведет лог
* Тестировалось на FreeBSD
```bash
make clean && make
```
требуется
* Library for building Telegram clients. TDLib: (https://github.com/tdlib/td)
 ```bash
pkg install tdlib
```
 * Simple .INI file parser written in C ( https://github.com/benhoyt/inih)
```bash
 pkg install inih
```
