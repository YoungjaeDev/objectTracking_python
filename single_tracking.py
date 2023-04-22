import cv2
import sys
import time
from random import randint

tracker_types = ["BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "MOSSE", "CSRT"]
tracker_type = tracker_types[-1]

print(tracker_type)

# CSRT: good accuracy, but it is slower than others
# KCF: not so good accuracy, but it is fast
# MOSSE: it is the fastest

if tracker_type == "BOOSTING":
    tracker = cv2.legacy.TrackerBoosting_create()
elif tracker_type == "MIL":
    tracker = cv2.legacy.TrackerMIL_create()
elif tracker_type == "KCF":
    tracker = cv2.legacy.TrackerKCF_create()    
elif tracker_type == "TLD":
    tracker = cv2.legacy.TrackerTLD_create()
elif tracker_type == "MEDIANFLOW":
    tracker = cv2.legacy.TrackerMedianFlow_create()
elif tracker_type == "MOSSE":
    tracker = cv2.legacy.TrackerMOSSE_create()
# CSRT (DISCRIMINATIVE CORRELATION FILTER WITH CHANNEL AND SPATIAL RELIABILITY)
elif tracker_type == "CSRT":
    tracker = cv2.legacy.TrackerCSRT_create()
    
print(tracker)


video = cv2.VideoCapture('Videos/race.mp4')
# video = cv2.VideoCapture('Videos/walking.avi')

if not video.isOpened():
    print('Error while loading the video!')
    sys.exit()
    
ok, frame = video.read()

if not ok:
    print('Error while loading the frame')
    sys.exit()
    
print(ok)

bbox = cv2.selectROI(frame)

print(bbox) # x, y, w, h

ok = tracker.init(frame, bbox)

print(ok)

colors = (randint(0, 255), randint(0, 255), randint(0, 255))

print(colors)

while True:
    ok, frame = video.read()
    
    if not ok:
        print('Error while loading the frame')
        break
    
    start = time.time()
    ok, bbox = tracker.update(frame)
    end = time.time()

    print(f"track time: {(end-start)*1000}ms")
    
    if ok:
        (x, y, w, h) = list(map(int, bbox))
        print(x, y, w, h)

        cv2.rectangle(frame, (x, y), (x+w, y+h), colors, 2, 1)
    else:
        cv2.putText(frame, "Tracking failure!", (100, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        
    cv2.imshow('Tracking', frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break
    
video.release()