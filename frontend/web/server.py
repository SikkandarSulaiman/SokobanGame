from http.server import HTTPServer, BaseHTTPRequestHandler
from io import BytesIO
import struct
import os

import socket


SOKOBAN_SERVER_IP = '127.0.0.1'
SOKOBAN_SERVER_PORT = 3000


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):

        if self.path.startswith('/cmd'):

            cmd = self.path.split('=')[1]

            unpacker = struct.Struct('i i i 100s 400s')
            


            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
            s.connect((SOKOBAN_SERVER_IP, SOKOBAN_SERVER_PORT))
            s.send(cmd.encode())
            buf = s.recv(unpacker.size)
            buf = unpacker.unpack(buf)

            print(buf)

            level = ''

            for i in range(0, 20 * buf[2], 20):
                level += '"'
                level += buf[4][i:i+buf[1]].decode('iso-8859-1')
                level += '",'
            
            level = level[:-1]

            jsonString = '{"map": [' + level + '], "row":' + str(buf[2]) + ', "col": ' + str(buf[1]) +'}\n'

            self.send_response(200)
            self.end_headers()
            self.wfile.write(jsonString.encode())

            return

        if self.path == '/':
            filename = 'index.html'
        else:
            filename = self.path[1:]

        filename = os.path.join(os.path.dirname(os.path.realpath(__file__)), filename)
 
        self.send_response(200)
        self.end_headers()

        with open(filename, 'rb') as fp:
            html = fp.read()
            #html = bytes(html, 'utf8')
            self.wfile.write(html)

        


httpd = HTTPServer(('localhost', 8001), SimpleHTTPRequestHandler)
httpd.serve_forever()
