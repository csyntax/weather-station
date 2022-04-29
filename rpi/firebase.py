from firebase_admin import initialize_app, db, credentials

cert = credentials.Certificate('<CERT_FILE>')
app = initialize_app(cert, {
    "databaseURL": '<DATABASE_URL>'
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