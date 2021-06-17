from .rfm import listen_for_data
from .firebase import push_to_firebase

def main():
    while True:
        data = listen_for_data()
        push_to_firebase(data)

if __name__ == "__main__":
    main()