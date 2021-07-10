import firebase_admin
from firebase_admin import db, credentials

cert = credentials.Certificate('/home/pi/Desktop/cert.json')
app = firebase_admin.initialize_app(cert, {
    "databaseURL": "https://csyntax-weather-station-default-rtdb.firebaseio.com"
})

ref = db.reference('/')

def push_to_firebase(key, data):
    (temp, pres, hum, gas) = data

    ref.child(key).set({
        'Temperature': temp,
        'Pressure': pres,
        'Humidity': hum,
        'Gas': gas,
    })

    print('Success push to Google Firebase')
