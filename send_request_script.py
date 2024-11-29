import requests
import json

# Путь к файлу .mtx
file_path = "matrix1.mtx"  # Замените на нужный путь к вашему файлу .mtx

# URL вашего сервера
url = "http://localhost:5001/decomposition"

# Метод разложения
method = "lu"  # Например, lu, svd, qr, или ldl

# Отправка POST-запроса с файлом и параметром method
with open(file_path, 'rb') as file:
    response = requests.post(
        url,
        files={'file': file},
        data={'method': method}
    )

# Отображение ответа в терминале
if response.status_code == 200:
    print("Result:")
    print(json.dumps(response.json(), indent=4))  # Форматированный вывод JSON
else:
    print(f"Error: {response.status_code}")
    print(response.text)