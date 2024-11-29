from flask import Flask, request, jsonify
import numpy as np
from scipy.linalg import lu, svd, qr, ldl
from scipy.io import mmread
import os

app = Flask(__name__)

@app.route('/decomposition', methods=['POST'])
def decomposition():
    if 'file' not in request.files:
        return jsonify({'error': 'No file provided'}), 400

    file = request.files['file']

    # Проверяем, что файл имеет расширение .mtx
    if not file.filename.endswith('.mtx'):
        return jsonify({'error': 'Invalid file type. Expected .mtx file'}), 400

    # Считываем матрицу из файла .mtx
    try:
        matrix = mmread(file).toarray()  # Преобразуем в плотный массив (numpy array)
    except Exception as e:
        return jsonify({'error': f'Failed to read .mtx file: {str(e)}'}), 500

    # Получаем метод разложения из запроса, по умолчанию 'lu'
    method = request.form.get('method', 'lu').lower()

    try:
        if method == 'lu':
            P, L, U = lu(matrix)
            result = {'P': P.tolist(), 'L': L.tolist(), 'U': U.tolist()}
        elif method == 'svd':
            U, S, VT = svd(matrix)
            result = {'U': U.tolist(), 'S': S.tolist(), 'VT': VT.tolist()}
        elif method == 'qr':
            Q, R = qr(matrix)
            result = {'Q': Q.tolist(), 'R': R.tolist()}
        elif method == 'ldl':
            L, D, perm = ldl(matrix)
            result = {'L': L.tolist(), 'D': D.tolist(), 'perm': perm.tolist()}
        else:
            return jsonify({'error': f'Unknown method: {method}'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500

    return jsonify(result)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)