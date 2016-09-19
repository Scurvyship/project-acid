import socket

def main():
    UDP_IP = "127.0.0.1"
    UDP_PORT = 1337

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.bind((UDP_IP, UDP_PORT))

    print('Socket bound, receiving data...')
    while True:
        data, addr = sock.recvfrom(18) # buffer size is 20 bytes
        print([hex(c) for c in data])


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        # Close socket
        sock.close()
        sys.exit()

