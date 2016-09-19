import socket
from http.server import BaseHTTPRequestHandler,HTTPServer
import threading
import json
import struct

""" Holds all players' data """
players = {}

class MyRequestHandler(BaseHTTPRequestHandler): # my hook
    def do_GET(self):
        try:
            if self.path == '/': # Load index.html
                self.send_response(200)
                self.send_header('Content-type', 'text/html')
                self.end_headers()
                fp = open('index.html')
                self.wfile.write(fp.read().encode('utf-8'))
                fp.close()

            if self.path == '/pos':
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(players).encode('utf-8'))
                #http://stackoverflow.com/questions/1094185/how-to-serve-any-file-type-with-pythons-basehttprequesthandler
        except IOError:
            self.send_error(404, 'File not found: %s' % self.path)

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
        data, addr = sock.recvfrom(26) # 26 bytes, the buffer/struct size
        print(data)
        #print([hex(c) for c in data])
        #print(len(data))
        uData = struct.unpack('<BBffffff', data)
        #print(test)
        # Populate the object
        players[uData[0]] = {
            'team': uData[1],
            'x': uData[2],
            'y': uData[3],
        }
        players[-1] = {'sinYaw': uData[4], 'mCosYaw': uData[5], 'vEyeX': uData[6], 'vEyeY': uData[7]}
        print(players)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        # Close socket
        sock.close()
        sys.exit()