import firebase_admin
from datetime import datetime

from firebase_admin import db, credentials

cert = credentials.Certificate('./cert.json')
app = firebase_admin.initialize_app(cert, {
    "databaseURL": "https://csyntax-weather-station-default-rtdb.firebaseio.com"
})

ref = db.reference('/')

def push_to_firebase(data):
    (temp, press, hum) = data
    
    now = datetime.now().replace(microsecond=0).isoformat()

    ref.child(now).set({
        'Temperature': temp,
        'Pressure': press,
        'Humidity': hum,
    })

    print('Success push to Google Firebase')