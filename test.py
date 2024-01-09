import requests

def main():
    #make program to send packets to test network sniffer
    url = "https://example.com"
    r = requests.get(url)
    print(r)



if __name__ == '__main__':
    main()