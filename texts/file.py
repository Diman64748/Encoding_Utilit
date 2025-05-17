import os
import glob
import chardet

# Определяем кодировки для конвертации
TARGET_ENCODINGS = {
    'windows1251': 'windows-1251',
    'KOI8-R': 'koi8-r',
    'ISO-8859-5': 'iso-8859-5',
    'DOS': 'cp866',
    'Maccyrillic': 'mac-cyrillic',
    'UTF-8': 'utf-8',
    'UTF-16': 'utf-16',
    'UTF-32': 'utf-32'
}

# Символы для замены
CHAR_REPLACEMENTS = {
    '\ufeff': '',      # Удаляем BOM
    '\u2014': '-',     # Длинное тире
    '\u2013': '-',     # Короткое тире
    '\u201c': '"',     # Левая кавычка
    '\u201d': '"',     # Правая кавычка
    '\u2018': "'",     # Левая одинарная
    '\u2019': "'",     # Правая одинарная
    '\xa0': ' ',       # Неразрывный пробел
    '\xad': '',        # Мягкий перенос
}

INPUT_DIR = '.'
OUTPUT_DIR = 'converted_texts'
os.makedirs(OUTPUT_DIR, exist_ok=True)

def detect_encoding(file_path):
    """Определяем кодировку файла"""
    with open(file_path, 'rb') as f:
        raw_data = f.read(10000)  # Анализируем первые 10КБ
    return chardet.detect(raw_data)['encoding']

def clean_text(text):
    """Очистка текста от проблемных символов"""
    for char, replacement in CHAR_REPLACEMENTS.items():
        text = text.replace(char, replacement)
    return text

def convert_file(input_file, output_encoding):
    """Конвертируем файл в указанную кодировку"""
    try:
        # Определяем исходную кодировку
        src_encoding = detect_encoding(input_file)
        if not src_encoding:
            src_encoding = 'utf-8'  # fallback
        
        # Читаем файл
        with open(input_file, 'r', encoding=src_encoding, errors='replace') as f:
            content = f.read()
        
        # Очищаем текст
        cleaned_content = clean_text(content)
        
        # Формируем имя выходного файла
        base_name = os.path.splitext(os.path.basename(input_file))[0]
        output_name = f"{base_name}-{output_encoding}.txt"
        output_path = os.path.join(OUTPUT_DIR, output_name)
        
        # Записываем в новой кодировке
        with open(output_path, 'w', encoding=TARGET_ENCODINGS[output_encoding], errors='replace') as f:
            f.write(cleaned_content)
            
        return True
    except Exception as e:
        print(f"Ошибка при конвертации {input_file} в {output_encoding}: {str(e)}")
        return False

def main():
    print("Начало обработки файлов...")
    
    # Получаем список файлов
    input_files = glob.glob(os.path.join(INPUT_DIR, '*.txt'))
    if not input_files:
        print(f"В папке {INPUT_DIR} не найдено txt-файлов!")
        return
    
    total_files = len(input_files)
    processed_files = 0
    
    for input_file in input_files:
        print(f"\nОбработка файла: {os.path.basename(input_file)}")
        
        # Определяем исходную кодировку
        try:
            src_encoding = detect_encoding(input_file)
            print(f"Определена кодировка: {src_encoding}")
        except Exception as e:
            print(f"Ошибка определения кодировки: {str(e)}")
            continue
        
        # Конвертируем во все целевые кодировки
        for enc_name in TARGET_ENCODINGS:
            if convert_file(input_file, enc_name):
                print(f"Успешно: {enc_name}")
            else:
                print(f"Не удалось: {enc_name}")
        
        processed_files += 1
        print(f"Прогресс: {processed_files}/{total_files}")
    
    print("\nОбработка завершена!")

if __name__ == '__main__':
    main()