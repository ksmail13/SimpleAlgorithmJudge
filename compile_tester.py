import subprocess
import threading
program_path = "temp/"

def __create_code(t_id, code, extention='cc'):
    global program_path
    file_path = "{}test_{}.{}".format(program_path, t_id, extention)
    f = open(file_path, "w");
    f.write(code)
    f.close()

    return file_path

def __execute_cmd(params):
    print "process params" , params
    p = subprocess.Popen(params, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return p, p.stdin, p.stdout, p.stderr

def cpp_test(t_id, code):
    global program_path
    file_path = __create_code(t_id, code)
    compile_params = ['g++', file_path, "-o", file_path.split(".")[0]]
    #compile_params = ['echo', 'asdf']
    p, p_in, p_out, p_err = __execute_cmd(compile_params)
    #print p.returncode
    for line in p_out.readlines():
        print line,
    for line in p_err.readlines():
        print line,

    p, p_in, p_out, p_err = __execute_cmd([file_path.split(".")[0]])
    for line in p_out.readlines():
        print line,




def java_test(t_id, code):
    pass

def python_test(t_id, code):
    pass

def tester_main():
    cpp_test(threading.current_thread().ident, """
    #include <stdio.h>

    int main() {

    printf("hello world!\\n");
    return 0;
   }
   """)

if __name__=="__main__":
    tester_main()
