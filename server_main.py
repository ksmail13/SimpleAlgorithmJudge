import sys, os
from functools import partial
import threading
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler

# TODO : create xml for create url mapping table
# TODO : create transfrom template
# TODO : db connection
# TODO : session
# TODO : judge logic
class JudgeRequestHandler(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        BaseHTTPRequestHandler.__init__(self, *args, **kwargs)
        print "Init request handler"
        self.server_version = "uos_judge/0.2"
    
    def do_GET(self):
        global urlpath
        key = self.path[1:]
        print "request get", key
        url = key+".html" 
        if os.path.exists(url):
 
            self.send_response(200);
            self.send_header("content-type", "text/html")
            self.end_headers()
            resp=''
            for line in open(url, "r").readlines():
                resp += line

            self.wfile.write(resp.encode('utf-8'))
        else :
            self.send_error(404);

    def do_POST(self):
        """
        receive POST request
        """
        global urlpath
        key = self.path[1:]

        print "request post", key

        for k in self.headers:
            self.send_response(200);
            self.send_header("content-type", "text/html")
            self.end_headers()
            self.wfile.write(k+"<br>")
        self.wfile.write(self.headers["content-length"]);

        self.content_parsing(self.rfile.read(int(self.headers["content-length"])));

        if self.req_params is not None:
            pass

    def complie_and_execute(self, lang, code):
        """
        compile code check recv result and execute recv result data
        """
        t_id = threading.current_thread().get_ident()
        self[lang](t_id, code)
        
    def __getitem__(self, index):
        if index == "cpp":
            return self.cpp_test
        elif index == "java":
            return self.java_test
        elif index == "python":
            return self.python_test


    def content_parsing(self, contents):
        self.req_params = {}
        for attr in contents.split('&'):
            attr_key, attr_value = attr.split("=")
            req_params[attr_key] = attr_value



def main(argv):
    try:
        serv_obj = HTTPServer(('',8080), partial(JudgeRequestHandler))
        serv_obj.serve_forever()
    except KeyboardInterrupt:
        print "Server exited"

if __name__=="__main__":
    main(sys.argv)
