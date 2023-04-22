import cv2
import sys
import time
from random import randint

# CSRT: good accuracy, but it is slower than others
# KCF: not so good accuracy, but it is fast
# MOSSE: it is the fastest

tracker_types = ["BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "MOSSE", "CSRT"]

def create_tracker_by_name(tracker_type):
    if tracker_type == tracker_types[0]:
        tracker = cv2.legacy.TrackerBoosting_create()
    elif tracker_type == tracker_types[1]:
        tracker = cv2.legacy.TrackerMIL_create()
    elif tracker_type == tracker_types[2]:
        tracker = cv2.legacy.TrackerKCF_create()    
    elif tracker_type == tracker_types[3]:
        tracker = cv2.legacy.TrackerTLD_create()
    elif tracker_type == tracker_types[4]:
        tracker = cv2.legacy.TrackerMedianFlow_create()
    elif tracker_type == tracker_types[5]:
        tracker = cv2.legacy.TrackerMOSSE_create()
    # CSRT (DISCRIMINATIVE CORRELATION FILTER WITH CHANNEL AND SPATIAL RELIABILITY)
    elif tracker_type == tracker_types[6]:
        tracker = cv2.legacy.TrackerCSRT_create()
    else:
        tracker = None
        print('Invalid name! Available trackers: ')
        for t in tracker_types:
            print(t)
    
    print(tracker)
    
    return tracker

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

bboxes = []
colors = []

while True:
    bbox = cv2.selectROI(frame)
    color = (randint(0, 255), randint(0, 255), randint(0, 255))
    
    bboxes.append(bbox)  # x, y, w, h
    colors.append(color)
    
    print('Press Q and quit start tracking')
    print('Press any other key to select the next object')
    
    k = cv2.waitKey(0) & 0xFF
    if k == ord('q'):
        break

print(bboxes)
print(colors)

multi_tracker = cv2.legacy.MultiTracker_create()
for bbox in bboxes:
    ok = multi_tracker.add(create_tracker_by_name("CSRT"), frame, bbox)
    if not ok:
        raise RuntimeError("Fail to execute multi_tracker.add")

while True:
    ok, frame = video.read()
    
    if not ok:
        print('Error while loading the frame')
        break
    
    start = time.time()
    ok, bboxes = multi_tracker.update(frame)
    end = time.time()

    print(f"track time: {(end-start)*1000}ms")
    
    if ok:
        for i, bbox in enumerate(bboxes):
            (x, y, w, h) = list(map(int, bbox))
            print(x, y, w, h)

            cv2.rectangle(frame, (x, y), (x+w, y+h), colors[i], 2, 1)
    else:
        cv2.putText(frame, "Tracking failure!", (100, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        
    cv2.imshow('Tracking', frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break
    
video.release()