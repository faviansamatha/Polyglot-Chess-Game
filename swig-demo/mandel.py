from example import escapes

def toChar(p):
    if p:
        return " "
    else:
        return "X"

def mandel(xmin,xmax,xstep, ymin,ymax,ystep, iterations):
  for yc in range(ystep):
      y = yc*(ymax-ymin)/ystep + ymin
      row = []
      for xc in range(xstep):
          x = xc*(xmax-xmin)/xstep + xmin
          row.append( escapes(x, y, iterations) )
      
      print("".join([toChar(p) for p in row]))

mandel(-2.0, 1.0, 90, -1.0, 1.0, 20, 3000)

