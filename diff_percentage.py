
import sys
import re
import os
import glob
from decimal import Decimal

#Patch files must be produced with --word-diff=plain
#  [--] and {++} as delimiters.

#This script examines all git diff patch files, extracts the relevant values,
# and computes the difference and percentage change.

directory = sys.argv[1]
print "dir: " + directory

patchfiles = glob.glob(directory + "/plain*.patch")

#sift for the percent prefix?

for filename in patchfiles:
  print "filename: " + filename
  #match = re.search('lines_(.+)', filename)
  match = re.search('/plain(.+)\.patch', filename)
  if match:
    outfilename = directory + "percent" + match.group(1) + ".patch"
    print "outfilename: " + outfilename

    infile = open(filename, 'r')
    outfile = open(outfilename, 'w')

    for line in infile:
      pre = re.search('\[-(.+)-\]', line)

      if pre:
        print "pre:"
        print pre.group(1)
        pre_match = pre.group(1)
        pre_values = pre_match.split(",")
        print "pre values: "
        print pre_values
        #pre = match.group(1)
        post = re.search('{\+(.+)\+}', line).group(1)
        post_values = post.split(",")

#more than one value
        for i in range(0, len(pre_values)):
          old = Decimal(pre_values[i])
          new = Decimal(post_values[i])

          difference = new-old
          percent = difference/old

          outfile.write(str(old) + " " + str(new) + "\t" + str(difference)
                        + "\t" + '%.2E'%(percent) + "%\n")




