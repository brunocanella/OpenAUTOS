# Build the source, documentation, and tests.
TARGET=oiler
FILE=oiler.c

all: oiler

lemon:
	cd lemon && make

language:
	cd language && make

$(TARGET): $(FILE) lemon language
	$(CC) -o $(TARGET) $(FILE) ./language/oiler_parser.o ./language/oiler_lexer.o $(CFLAGS)

test: $(TARGET)
	cd test && make --silent

# Delete generated files.
clean:
	cd lemon && make -s clean
	cd language && make -s clean
	rm -f $(TARGET) *.d

.PHONY: lemon language test clean