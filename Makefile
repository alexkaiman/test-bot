# Определение операционной системы
UNAME_S != uname -s

# Общие переменные
CFLAGS = -std=c++17 -Wall
SOURCES = main.cpp logger.cpp config.cpp telegram.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = telegram_bot

# Специфичные для OS переменные
.if $(UNAME_S) == "Linux"
CC = g++
CFLAGS += -I/usr/local/include
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -ltdjson -lcurl -linih
.elif $(UNAME_S) == "FreeBSD"
CC = clang++
CFLAGS += -I/usr/local/include
LDFLAGS = -L/usr/local/lib -ltdjson -lcurl -linih
.else
.error Unsupported operating system: $(UNAME_S)
.endif

# Цели
all: $(EXECUTABLE)

# Правило сборки исполняемого файла
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Правило компиляции .cpp в .o
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для очистки
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)