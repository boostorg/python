import hello # Get demo imported now so test_extclass won't look in its own directory
import os
os.chdir('..')
import test_example1
test_example1.run(["-v"])

