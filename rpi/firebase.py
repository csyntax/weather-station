from firebase_admin import initialize_app, db, credentials

CERT = credentials.Certificate('/home/pi/Desktop/cert.json')
app = initialize_app(CERT, {
    "databaseURL": "https://csyntax-weather-station-default-rtdb.firebaseio.com"
})

ref = db.reference('/')

def push_to_firebase(now, data):
    (temp, pres, hum, gas) = data

    ref.child(now).set({
        'Temperature': temp,
        'Pressure': pres,
        'Humidity': hum,
        'Gas': gas,
    })

    print('Success push to Google Firebase')