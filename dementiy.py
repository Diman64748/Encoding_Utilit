import chardet

with open('fail_lines.txt', 'w'):
    pass
text = ""
with open('output.log', 'rb') as file:
    raw_data = file.read()
    result = chardet.detect(raw_data)
    encoding = result['encoding']
with open("output.log", 'r',encoding='utf-8') as file:
    text = file.read()
new_text = text.replace("---------------------------------", "")
new_text = new_text.replace("Обработка файла: ", "")
new_text = new_text.replace("Запускаем программу на определение кодировки русского текста\n", "")
lines = [line.strip() for line in new_text.splitlines() if line.strip()]
lines.remove("Начало тестирования всех файлов...")
count_normal = 0
count_fail = 0
fail_lines = open('fail_lines.txt', 'w')
for i in range(0, len(lines), 2):
    if "DOS" in lines[i]:
        if lines[i+1] == "dos":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: dos \nОпределено: {lines[i+1]}------------\n")
    elif "ISO-8859-5" in lines[i]:
        if lines[i+1] == "iso":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: iso \nОпределено: {lines[i+1]}\n------------\n")
    elif "KOI8-R" in lines[i]:
        if lines[i+1] == "koi8r":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: koi8r \nОпределено: {lines[i+1]}\n------------\n")
    elif "Maccyrillic" in lines[i]:
        if lines[i+1] == "maccyrillic":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: maccyrillic \nОпределено: {lines[i+1]}\n------------\n")
    elif "UTF-16" in lines[i]:
        if lines[i+1] == "utf16":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: utf16 \nОпределено: {lines[i+1]}\n------------\n")
    elif "UTF-32" in lines[i]:
        if lines[i+1] == "utf32":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: utf32 \nОпределено: {lines[i+1]}\n------------\n")
    elif "UTF-8" in lines[i]:
        if lines[i+1] == "utf8":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: utf8 \nОпределено: {lines[i+1]}\n------------\n")
    elif "windows1251" in lines[i]:
        if lines[i+1] == "windows1251":
            count_normal+=1
        else:
            count_fail+=1
            fail_lines.write(f"Файл: {lines[i]} \nОжидалось: windows1251 \nОпределено: {lines[i+1]}\n------------\n")
fail_lines.write(f"Колличество раз, когда команда сработала правильно {count_normal}\nКолличество раз, когда команда сработала неправильно {count_fail}")
fail_lines.close()