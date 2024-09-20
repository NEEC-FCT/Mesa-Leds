from PIL import Image
import numpy as np
import sys
import cv2

import matplotlib.pyplot as plt
np.set_printoptions(threshold=sys.maxsize)

Width  = 32
Height = 18


# Function to load video and convert frames to an array of image matrices
def video_to_image_matrices(video_path):
    # Capture the video
    cap = cv2.VideoCapture(video_path)
    
    if not cap.isOpened():
        print("Error: Could not open video.")
        return []

    frames = []

    # Read until the video is completed
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        # Convert the frame from BGR (OpenCV default) to RGB
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # Append the frame to the list
        frames.append(frame_rgb)
    
    # Release the video capture object
    cap.release()
    
    return frames

# Function to reduce the number of frames in a video while maintaining speed
def reduce_frames(input_video_path, output_video_path, frame_skip):
    # Open the original video
    cap = cv2.VideoCapture(input_video_path)
    frame_size = (Width, Height)
    if not cap.isOpened():
        print("Error: Could not open video.")
        return

    # Get the original video properties
    original_fps = cap.get(cv2.CAP_PROP_FPS)
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    frame_size = (frame_width, frame_height)

    # Define the codec and create VideoWriter object
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # Use 'XVID' or 'MJPG' for .avi files
    out    = cv2.VideoWriter(output_video_path, fourcc, original_fps/frame_skip, (Width, Height))
    
    #print(f"Original FPS: {original_fps}")
    #print(f"Frame Size: {frame_size}")

    frame_count = 0
    # Read and write frames
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
        
        # Write only every nth frame
        if frame_count % frame_skip == 0:
            rframe = cv2.resize( frame, (Width, Height) )
            # Resize the frame
            out.write(rframe)
        frame_count += 1

        if frame_count/frame_skip > 85:
            break
    
    # Release the video objects
    cap.release()
    out.release()


# Function to display a single frame using Matplotlib
def display_frame(frame, frame_id):
    plt.figure(figsize=(6, 6))
    plt.imshow(frame)
    plt.axis('off')
    plt.title(f'Frame {frame_id}')
    plt.show()

# Resize the image using Pillow
#resized_image = image.resize((Width, Height))

# Convert the resized image back to a NumPy array
#resized_image_matrix = np.array(resized_image)
# Initialize an empty matrix
# Example usage
input_video_path = 'BadApple.mp4'  # Replace with your input video path
output_video_path = 'Out.mp4'  # Replace with your output video path
frame_skip = 8  # Adjust this to skip every nth frame
reduce_frames(input_video_path, output_video_path, frame_skip)
frames = video_to_image_matrices( 'Out.mp4' )


#print(len(frames))
#f = open('output.txt', 'w') 

#print(str(resized_image_matrix).replace('[','{').replace(']','},').replace(",}",'}').replace('\n','') )
print( 
    "#define MATRIX_WIDTH   32  // Set this negative if physical led 0 is opposite to where you want logical 0\n"+
    "#define MATRIX_HEIGHT  18  // Set this negative if physical led 0 is opposite to where you want logical 0\n"+
    "#define NFRAMES "+str( len(frames) )+"       // Number of frames\n\n"+
    "uint32_t BadApple[NFRAMES][MATRIX_HEIGHT] = {"
    )

n = 0
#o = 0
c = ''

vid = [[0 for x in range(Height)] for y in range(len(frames))] 

for frame in frames:

    print("{",end="")

    for y in range(Height):
        #print("{",end="")
        for x in range(Width):
            colour = frame[y][x]
            
            if( ( int(colour[0]) + int(colour[1]) + int(colour[2]) ) < (220*3)/2 ):
                v = '0'
            else:
                v = '1'
            
            c += v

            #print( str(c) , end ="")
            #print( "CRGB("+str(aux[0]) +","+ str(aux[1])+","+str(aux[2])+")", end ="")
            
            #if y != Height-1:
             #   print("",end =",")

        vid[n][y] = c 
        print(  str( int(c,2)),end="")

        c = ''
        if y != Height-1:
            print(",",end="")

    print("}",end="")
    if n != len(frames)-1:
        print(",",end="")
    n += 1

print(
    "\n};"
)

fn = 0
ln = 0
line  = vid[fn][ln]
frame = vid[fn]
n     = 0


def sumframe(fr):
    j = 0
    for i in fr:
        j += i
    return j

while( n < len(frames) ):
    counter = 0
    
    while( sumframe(frame) != sumframe( vid[fn] ) ):
        counter += 1
        fn += 1
