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

            

            # s = '{"map": ["   ####  ","####  ## ","#   $  # ","#  *** # ","#  . . ##","## * *  #"," ##***  #","  # $ ###","  # @ #  ","  #####  "], "row": 10, "col": 9}\n'
            s = '{"map": [' + buf[4].decode('iso-8859-1') + '], "row":' + str(buf[1]) + ', "col": ' + str(buf[2]) +'}\n'

            print(s)

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

        




httpd = HTTPServer(('localhost', 8002), SimpleHTTPRequestHandler)
httpd.serve_forever()