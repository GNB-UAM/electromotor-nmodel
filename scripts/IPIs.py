import fileinput
thr=0.6
lastTime=0
lastV=0.0
time=0

for line in fileinput.input():
    lineArr=line.split(' ')
    v=float(lineArr[8])
    if lastV<thr and v>=thr:
        print(str(time) + " " + str(time-lastTime))
        lastTime=time
    lastV=v
    time=time+0.01


