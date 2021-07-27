import os
from random import randint

for i in range(1, 2): # days 365 in a year

  for j in range (0, randint(1, 100)): # no. of commits per a day
      d = str(i) + 'days ago'
      with open('file.py', 'a') as file:
          file. write("\n")
          file.write(d)
      with open('commit.py', 'a') as file:
          file. write("\n")
          file.write(d)
      with open('kofi.py', 'a') as file:
          file. write("\n")
          file.write(d)
      with open('kinnata.py', 'a') as file:
          file. write("\n")
          file.write(d)
      with open('rap.py', 'a') as file:
          file. write("\n")
          file.write(d)  
      with open('god.py', 'a') as file:
          file. write("\n")
          file.write(d)  
      with open('talent.py', 'a') as file:
          file. write("\n")
          file.write(d)
      with open('good.py', 'a') as file:
          file. write("\n")
          file.write(d)
      os.system('git add .')
      os.system('git commit --date="' + d + '" -m "commit hacking"')

os.system('git push -u origin main')