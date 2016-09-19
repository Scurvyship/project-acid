import socket
from http.server import BaseHTTPRequestHandler,HTTPServer
import threading
import json
import struct

""" Holds all players' data """
players = {}

class MyRequestHandler(BaseHTTPRequestHandler): # my hook
    def do_GET(self):
        if self.path == '/pos':
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(players).encode('utf-8'))
            #http://stackoverflow.com/questions/1094185/how-to-serve-any-file-type-with-pythons-basehttprequesthandler

def main():
    UDP_IP = "127.0.0.1"
    UDP_PORT = 1337

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.bind((UDP_IP, UDP_PORT))

    # Setup the www server
    server  = HTTPServer(('0.0.0.0', 80), MyRequestHandler)
    threading.Thread(target=server.serve_forever).start()
        
    print('Socket bound, receiving data...')
    while True:
        data, addr = sock.recvfrom(20) # 18 bytes, the buffer/struct size
        #print(data)
        #print([hex(c) for c in data])
        #print(len(data))
        test = struct.unpack('<Bffff', data)
        #print(test)
        # Populate the object
        players[test[0]] = {
            'index': test[0],
            'x': test[1],
            'y': test[2]
        }
        players[-1] = {'sinYaw': test[3], 'mCosYaw': test[4]}
        print(players)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        # Close socket
        sock.close()
        sys.exit()