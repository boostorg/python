import os
import sys
import shutil
from zipfile import ZipFile, ZIP_DEFLATED

def main():
    # create exe
    status = os.system('python setup.py py2exe >& build.log')
    if status != 0:
        raise RuntimeError, 'Error creating EXE'

    # create distribution
    import pyste
    version = pyste.__VERSION__
    zip = ZipFile('pyste-%s.zip' % version, 'w', ZIP_DEFLATED)    
    # include the base files
    dist_dir = 'dist/pyste'
    for basefile in os.listdir(dist_dir):
        zip.write(os.path.join(dist_dir, basefile), basefile)
    zip.close()
    # cleanup
    os.remove('build.log')
    shutil.rmtree('build')
    shutil.rmtree('dist')
    

if __name__ == '__main__':
    sys.path.append('../src')
    main()
