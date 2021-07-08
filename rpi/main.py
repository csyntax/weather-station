import rfm
import firebase

while True:
    try:
        data = rfm.listen_for_data()

        firebase.push_to_firebase(data)
    except(TypeError):
        pass
    #if ((not temp) and (not press) and (not hum)) == 0:
     #   firebase.push_to_firebase(temp, press, hum)
