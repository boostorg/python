import demo # Get demo imported now so test_extclass won't look in its own directory
import os
os.chdir('..')
import test_extclass
test_extclass.run(['-v', '--broken-auto-ptr'])

