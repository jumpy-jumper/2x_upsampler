from numpy import genfromtxt
import imageio
import sys

imgArray = genfromtxt(sys.argv[1], delimiter=",")
imageio.imwrite("out.jpg", imgArray)
