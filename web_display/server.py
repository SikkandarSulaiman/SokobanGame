from http.server import HTTPServer, BaseHTTPRequestHandler
from io import BytesIO
import struct
import os

import socket

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):

        if self.path.startswith('/cmd'):

            cmd = self.path.split('=')[1]

            unpacker = struct.Struct('I I I 100s 400s')
            


            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
            s.connect(('127.0.0.1', 3000))
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

            s = '{"map": [' + level + '], "row":' + str(buf[2]) + ', "col": ' + str(buf[1]) +'}\n'




            self.send_response(200)
            self.end_headers()
            self.wfile.write(s.encode())

            return

        if self.path == '/':
            filename = '.' + '/index.html'
        else:
            filename = '.' + self.path
 
        self.send_response(200)
        self.end_headers()

        with open(filename, 'rb') as fp:
            html = fp.read()
            #html = bytes(html, 'utf8')
            self.wfile.write(html)

        




httpd = HTTPServer(('localhost', 8001), SimpleHTTPRequestHandler)
httpd.serve_forever()