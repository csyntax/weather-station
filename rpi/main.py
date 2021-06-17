import rfm
import firebase

while True:
    (temp, press, hum) = rfm.listen_for_data()
    
    if ((not temp) and (not press) and (not hum)) == 0:
        firebase.push_to_firebase(temp, press, hum)
