CC = gcc
CFLAGS = -Wall -Wextra

INPUT_DIR = texts/converted_texts

WRONG_DIR = texts/wrong_coding

OUTPUT_LOG = output.log
SMALL_LOG = study_result.log



PROGRAM = ./program

all: program

program: main.c to_UTF8.c decoding.c full_analize.c debug_func.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm program
	@rm -r result 

TEST: program
	@echo "Начало тестирования всех файлов..." > $(OUTPUT_LOG)
	@for file in $(INPUT_DIR)/*.txt; do \
		echo "Обработка файла: $$file" >> $(OUTPUT_LOG); \
		$(PROGRAM) -i "$$file" -mode detect >> $(OUTPUT_LOG) 2>&1; \
		echo "---------------------------------" >> $(OUTPUT_LOG); \
	done
	@echo "Тестирование завершено. Результаты в $(OUTPUT_LOG)"

	@echo "Начало тестирования учебных файлов..." > $(SMALL_LOG)
	@for file in texts/study_not_detect/*.txt; do \
		echo "Обработка файла: $$file" >> $(SMALL_LOG); \
		$(PROGRAM) -i "$$file" -mode detect >> $(SMALL_LOG) 2>&1; \
		echo "---------------------------------" >> $(SMALL_LOG); \
	done
	@for file in  texts/study_detect/*.txt; do \
		echo "Обработка файла: $$file" >> $(SMALL_LOG); \
		$(PROGRAM) -i "$$file" -mode detect >> $(SMALL_LOG) 2>&1; \
		echo "---------------------------------" >> $(SMALL_LOG); \
	done
	@echo "Тестирование завершено. Результаты в $(SMALL_LOG)"

	@/bin/python3 dementiy.py 
	@mkdir result
	@mv fail_lines.txt result/fail_lines.txt
	@mv output.log result/output.log
	@mv study_result.log result/study_result.log

ASM: decode.o hex.o  bin.o main.c to_UTF8.c full_analize.c debug_func.c 
	@$(CC) $(CFLAGS) $^ -o program
	@rm bin.o hex.o decode.o

hex.o: hex.s
	@$(CC) $(CFLAGS) -c hex.s

bin.o: bin.s
	@$(CC) $(CFLAGS) -c bin.s

decode.o: decode.s
	@$(CC) $(CFLAGS) -c decode.s

