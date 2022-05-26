import numpy as np
import cv2

def process(frame, code):
   
    rect_size = 100
    h_sensivity = 20
    s_h = 255
    v_h = 255
    s_l = 50
    v_l = 50
    
    font = cv2.FONT_HERSHEY_COMPLEX
    fontScale = 0.7
    
    green_upper = np.array([60 + h_sensivity, s_h, v_h])
    green_lower = np.array([60 - h_sensivity, s_l, v_l])
    red_upper_1 = np.array([0, s_l, v_l])
    red_upper_2 = np.array([0 + h_sensivity, s_l, v_h])
    red_lower_1 = np.array([180 - h_sensivity, s_l, v_l])
    red_lower_2 = np.array([180, s_h, v_h])
    blue_upper = np.array([120 + h_sensivity, s_h, v_h])
    blue_lower = np.array([120 - h_sensivity, s_l, v_l])
    
    def process_rect(number, rect, mask_frame):
        if (code[number] == 'R'):
            return cv2.bitwise_or(cv2.inRange(mask_frame, red_lower_1, red_lower_2), cv2.inRange(mask_frame, red_upper_1, red_upper_2) )
        if (code[number] == 'R'):
            return cv2.inRange(mask_frame, red_lower_1, red_lower_2)
        if (code[number] == 'G'):
            return cv2.inRange(mask_frame, green_lower, green_upper)
        if (code[number] == 'B'):
            return cv2.inRange(mask_frame, blue_lower, blue_upper)
        
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    width, height, channels = frame.shape
    result = np.zeros(frame.shape, np.uint8)
    result[:] = (0, 0, 0)
    start_point = (int(height/6 - rect_size/2), int(width/2 - rect_size/2))
    end_point = (int(height/6 + rect_size/2), int(width/2 + rect_size/2))
    color = code_array[0]
    thickness = 2
    rect = cv2.rectangle(result, start_point, end_point, color, thickness)
    rect_img = frame[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/6 - rect_size/2):int(height/6 + rect_size/2)]
    result[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/6 - rect_size/2):int(height/6 + rect_size/2)] = rect_img
    mask_frame = hsv_frame[start_point[1]:end_point[1] + 1, start_point[0]:end_point[0] + 1]
    
    mask = process_rect(0, rect, mask_frame)

    rate_1 = np.count_nonzero(mask)/(rect_size*rect_size)
    
    av_hue = np.average(mask_frame[:,:,0])
    av_sat = np.average(mask_frame[:,:,1])
    av_val = np.average(mask_frame[:,:,2])
    average = [int(av_hue),int(av_sat),int(av_val)]
    text = cv2.putText(rect, str(average) + " " + str(rate_1), (10,50), font, fontScale, color, thickness - 1, cv2.LINE_AA)
    
    start_point = (int(height/3 - rect_size/2), int(width/2 - rect_size/2))
    end_point = (int(height/3 + rect_size/2), int(width/2 + rect_size/2))
    color = code_array[1]
    rect = cv2.rectangle(result, start_point, end_point, color, thickness)
    rect_img = frame[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/3 - rect_size/2):int(height/3 + rect_size/2)]
    result[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/3 - rect_size/2):int(height/3 + rect_size/2)] = rect_img
    mask_frame = hsv_frame[start_point[1]:end_point[1] + 1, start_point[0]:end_point[0] + 1]
    
    mask = process_rect(1, rect, mask_frame)

    rate_2 = np.count_nonzero(mask)/(rect_size*rect_size)
    
    av_hue = np.average(mask_frame[:,:,0])
    av_sat = np.average(mask_frame[:,:,1])
    av_val = np.average(mask_frame[:,:,2])
    average = [int(av_hue),int(av_sat),int(av_val)]
    text = cv2.putText(rect, str(average) + " " + str(rate_2), (10,75), font, fontScale, color, thickness - 1, cv2.LINE_AA)
    
    start_point = (int(height/2 - rect_size/2), int(width/2 - rect_size/2))
    end_point = (int(height/2 + rect_size/2), int(width/2 + rect_size/2))
    color = code_array[2]
    rect = cv2.rectangle(result, start_point, end_point, color, thickness)
    rect_img = frame[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/2 - rect_size/2):int(height/2 + rect_size/2)]
    result[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height/2 - rect_size/2):int(height/2 + rect_size/2)] = rect_img
    mask_frame = hsv_frame[start_point[1]:end_point[1] + 1, start_point[0]:end_point[0] + 1]
    
    mask = process_rect(2, rect, mask_frame)

    rate_3 = np.count_nonzero(mask)/(rect_size*rect_size)
    
    av_hue = np.average(mask_frame[:,:,0])
    av_sat = np.average(mask_frame[:,:,1])
    av_val = np.average(mask_frame[:,:,2])
    average = [int(av_hue),int(av_sat),int(av_val)]
    text = cv2.putText(rect, str(average) + " " + str(rate_3), (10,100), font, fontScale, color, thickness - 1, cv2.LINE_AA)

    start_point = (int(height*2/3 - rect_size/2), int(width/2 - rect_size/2))
    end_point = (int(height*2/3 + rect_size/2), int(width/2 + rect_size/2))
    color = code_array[3]
    rect = cv2.rectangle(result, start_point, end_point, color, thickness)
    rect_img = frame[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height*2/3 - rect_size/2):int(height*2/3 + rect_size/2)]
    result[int(width/2 - rect_size/2):int(width/2 + rect_size/2), int(height*2/3 - rect_size/2):int(height*2/3 + rect_size/2)] = rect_img
    mask_frame = hsv_frame[start_point[1]:end_point[1] + 1, start_point[0]:end_point[0] + 1]
    
    mask = process_rect(3, rect, mask_frame)

    rate_4 = np.count_nonzero(mask)/(rect_size*rect_size)

    av_hue = np.average(mask_frame[:,:,0])
    av_sat = np.average(mask_frame[:,:,1])
    av_val = np.average(mask_frame[:,:,2])
    average = [int(av_hue),int(av_sat),int(av_val)]
    text = cv2.putText(rect, str(average) + " " + str(rate_4), (10,125), font, fontScale, color, thickness - 1, cv2.LINE_AA)

    org = end_point
    
    fontScale = 0.5
    if ( rate_1 > 0.9 ) & ( rate_2 > 0.9 ) & ( rate_3 > 0.9 ) & ( rate_4 > 0.9 ):
        color = (0,255,0)
        text = cv2.putText(rect, ' access granted ', org, font, fontScale, color, thickness - 1, cv2.LINE_AA)
    else:
        color = (0,0,255)
        text = cv2.putText(rect, ' access denied ', org, font, fontScale, color, thickness - 1, cv2.LINE_AA)

    frame = text
    return result
    
wrong_input = 0;
code = "";
code_array = []

print('Enter code')
code = input()
for i in code:
    if i in ['R','B','G']:
        pass
    else:
        wrong_input = 1
code = list(code)
if (len(code) != 4):
    wrong_input = 1

while wrong_input:
    print('Enter code')
    code = input()
    for i in code:
        if i in ['R','B','G']:
           wrong_input = 0
           pass
        else:
           wrong_input = 1
    code = list(code)
    if (len(code) != 4):
        wrong_input = 1

for i in range(len(code)):
    if(code[i] == 'R'):
        code_array.insert(i, (0,0,255))
    elif(code[i] == 'G'):
        code_array.insert(i, (0,255,0))
    elif(code[i] == 'B'):
        code_array.insert(i, (255,0,0))

#print('Press ESC to Quit the Application\n')

#Open Default Camera
#cap = cv2.VideoCapture(0)#gstreamer_pipeline(flip_method=4), cv2.CAP_GSTREAMER)
cap = gstreamer_pipeline(flip_method=4), cv2.CAP_GSTREAMER)

while(cap.isOpened()):
    #Take each Frame
    ret, frame = cap.read()
    
    #Flip Video vertically (180 Degrees)
    frame = cv2.flip(frame, 180)

    check = process(frame, code)

    # Show video
    # cv2.imshow('Cam', frame)
    cv2.imshow('Check', check)

    # Exit if "ESC" is pressed
    k = cv2.waitKey(1) & 0xFF
    if k == 27 : #ord ESC
        #Quit
        print ('Good Bye!')
        break

#Release the Cap and Video   
cap.release()
cv2.destroyAllWindows()