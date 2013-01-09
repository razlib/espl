#!/usr/bin/env python

import os, os.path, sys, getpass, shlex, subprocess

home=os.getenv('HOME')

def getArgs(argv):
    newArgv = []
    for arg in argv:
      if arg[0] == "$" and arg[1:] in os.environ:
	newArgv.append(os.environ[arg[1:]])
      else:
	newArgv.append(arg)
    return newArgv

def runProccess(argv):
  if '>' in argv:
    f = open(argv[argv.index('>')+1],'w')
    subprocess.call(argv[0:argv.index('>')], stdout = f, shell=False)
  elif '<' in argv:
        f = open(argv[argv.index('<')+1])
	subprocess.call(argv[0:argv.index('<')], stdin = f, shell=False)
  elif '|' in argv:
    p1 = subprocess.Popen(argv[0:argv.index('|')], stdout=subprocess.PIPE)
    p2 = subprocess.call(argv[argv.index('|')+1:], stdin=p1.stdout)
    p1.stdout.close()  # Allow p1 to receive a SIGPIPE if p2 exits.
    
  else:

    subprocess.call(getArgs(argv), shell=False)
  
def getcwd():
    "like os.getcwd(), but collapses the home directory prefix into ~"
    cwd = os.getcwd()
    if cwd.startswith(home):
        cwd = '~'+cwd[len(home):]
    return cwd

while True:
    print "%s@%s>" % (getpass.getuser(), getcwd()),

    argv = None
    try:
        argv = shlex.split(raw_input())
    except EOFError:
        print
        break # end of file from user, e.g. Ctrl-D

    if not argv:
        continue # empty command

    if argv[0] in ['exit', 'quit', 'bye']:
        break
    elif len(argv) > 2 and argv[1] == "=":
      if argv[0] not in os.environ:
	os.environ[argv[0]] = argv[2] 
    elif argv[0]=='cd':
        try:
            os.chdir(os.path.expanduser(getArgs(argv)[1])) # expand ~ to home directory
        except IndexError: # no arguments, chdir to home dir
            os.chdir(home)
        except OSError, s:
            print >>sys.stderr, "chdir: %s" % s
    else:
	runProccess(argv)
        #print "TODO: execute %s" % ' '.join(argv)

# goodbye message
goodbye = "have a good sunny day, see you back soon"
print "*"+"-"*(len(goodbye)+2)+"*"
print "| %s |" % goodbye
print "*"+"-"*(len(goodbye)+2)+"*" 


