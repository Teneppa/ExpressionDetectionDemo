from fer import FER
from pprint import pprint
import cv2
import serial

# Setup the serial port
port = "COM5"
baudrate = 115200
ser = serial.Serial(port, baudrate)
ser.timeout = 0.1

# The camera source comes here
cap = cv2.VideoCapture(0)
#cap = cv2.VideoCapture(1)

# TRUE = really accurate, but slow
# FALSE = inaccurate but fast af
#emo_detector = FER(mtcnn=True)
emo_detector = FER(mtcnn=False)

# Send RGB color to Arduino
def color(r,g,b):
    ser.write(f"{r},{g},{b};".encode())

# Main loop is here
while True:
    succ, img = cap.read()
    #img = cv2.resize(img, ((int(1280*scale),int(720*scale))))

    # If we got image from the camera
    if succ:        
        # TOP EMOTION
        dominant_emotion, emotion_score = emo_detector.top_emotion(img)
        #print(dominant_emotion, emotion_score)

        # EMOTION LIST
        """
        elist = emo_detector.detect_emotions(img)
        pprint(elist)

        if elist:
            x = elist[0]['box'][0]
            y = elist[0]['box'][1]
            w = elist[0]['box'][2]
            h = elist[0]['box'][3]

            cv2.rectangle(img, (x,y), (x+w,y+h), (255, 0, 0))
        """
        
        # Change color depending on the expression
        if dominant_emotion == "neutral":
            color(255,255,255)
        if dominant_emotion == "disgust":
            color(0,255,0)
        if dominant_emotion == "angry":
            color(255,0,0)
        if dominant_emotion == "fear":
            color(255,0,255)
        if dominant_emotion == "happy":
            color(255,255,0)
        if dominant_emotion == "sad":
            color(0,255,255)
        if dominant_emotion == "surprise":
            color(0,255,255)
        
        # angry, disgust, fear, happy, neutral, sad, surprise

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()
