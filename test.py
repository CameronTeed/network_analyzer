import requests
import os
import threading

def sniff_packets():
    # Function to send packets to test network sniffer
    os.system('./main 3 1 0')

def make_request(url):
    # Function to make an HTTP request using the requests library
    response = requests.get(url)
    print(response.text)

def main():
    # Clear the terminal screen
    os.system('clear')

    # URL for testing
    url = 'http://www.testingmcafeesites.com/'

    # Create threads
    t1 = threading.Thread(target=sniff_packets)
    t2 = threading.Thread(target=make_request, args=(url,))

    # Start threads
    t1.start()
    t2.start()

    # Wait for threads to finish
    t1.join()
    t2.join()

    # open the file to read
    file = open("output.txt", "r")
    # read the content of the file
    content = file.read()
    # iterate over the content
    containsHTTP = False
    counterHTTP = 0
    for line in content.splitlines():
        # check if the line includes the url from the http
        if line.find(url) == 1:
            # print the line
            containsHTTP = True
            counterHTTP += 1
    # close the file
    file.close()

    if (containsHTTP):
        print("The file contains the HTTP request")
        print("url: " + url)
    else:
        print("The file does not contain the HTTP request")


if __name__ == '__main__':
    main()