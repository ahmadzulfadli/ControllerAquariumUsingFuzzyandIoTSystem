from dbClass import *
# read---------------------------------------------------------
@app.route('/', methods=['GET'])
def index():
    dataAquarium = Aquarium.query.order_by(Aquarium.timestamps.desc()).first()

    dataGrafik = Aquarium.query.order_by(Aquarium.timestamps.desc()).limit(10).all()

    grafikJson = []
    for data in dataGrafik:
        grafikJson.append({
            'label': data.timestamps.strftime('%H:%M'),
            'temperature': data.data_temp,
            'phMeter': data.data_ph
        })

    return render_template('dashboard.html', data = dataAquarium, grafik = grafikJson)

@app.route('/tabel', methods=['GET'])
def tabel():
    dataTabel = Aquarium.query.order_by(Aquarium.timestamps.desc()).all()
    return render_template('tables.html', data = dataTabel)

# create-------------------------------------------------------
@app.route('/add/data', methods=['GET'])
def addData():
    try:
        mode = request.args.get('mode')
        if mode != 'save':
            return jsonify({'status': 'error', 'message': 'Mode not found'})
        
        else:
            temperature = request.args.get('temp')
            phMeter = request.args.get('ph_meter')

            if temperature is None or phMeter is None:
                return jsonify({'status': 'error', 'message': 'Data not found'})
            
            newDatas = Aquarium(
                data_temp = temperature,
                data_ph = phMeter,
            )
            db.session.add(newDatas)
            db.session.commit()

            return jsonify({'status': 'success', 'message': 'Data saved'})
        
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

if __name__ == '__main__':
    # Launch the application
    app.run(debug=True, port=8000)