

from socket import *
from sys import argv

def buildHTTPRequest(host, filename):
    request = ""
    request += "GET " + filename + " HTTP/1.1\n"
    request += "Host: " + host + "\n"

    return request


def main():
    if not len(argv) == 4:
        print (argv[0]+": Usage python client.py server_host server_port filename")
        exit(1)

    serverHost = argv[1]
    serverPort = int(argv[2])
    filename = argv[3]

    print(serverHost, serverPort, filename)

    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((serverHost, serverPort))
    request = buildHTTPRequest(serverHost, filename)
    clientSocket.send(request.encode())

    print("Response from server:\n")
    while True:
        response = clientSocket.recv(1024)
        if response:
            print (response.decode(), end="", sep="")
        else:
            break
        


    clientSocket.close()

main()

