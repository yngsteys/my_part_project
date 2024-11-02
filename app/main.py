from flask import Flask, request, jsonify
import numpy as np
from scipy.linalg import lu


app = Flask(__name__)

@app.route('/lu_decomposition', methods=['POST'])
def lu_decomposition():
    data = request.get_json()
    matrix = np.array(data['matrix'])
    
    # Выполняем LU-разложение
    P, L, U = lu(matrix)
    
    # Преобразуем результаты в списки для JSON
    result = {
        'L': L.tolist(),
        'U': U.tolist(),
        'P': P.tolist()
    }
    
    return jsonify(result)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
    