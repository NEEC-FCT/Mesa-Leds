from PIL import Image
import numpy as np
import sys

import matplotlib.pyplot as plt
np.set_printoptions(threshold=sys.maxsize)

filename = "badapple.jpg"

# Load the image
image = Image.open(filename)

# Convert the image to a NumPy array
image_matrix = np.array(image)

xdim = 32
ydim = 18

# Resize the image using Pillow
resized_image = image.resize((xdim, ydim))

# Convert the resized image back to a NumPy array
resized_image_matrix = np.array(resized_image)
# Initialize an empty matrix
#matriz = ["" for _ in range(xdim*ydim)]

plt.figure(figsize=(6, 6))
plt.imshow(resized_image_matrix)
plt.axis('on')  # Hide axes
plt.title('Loaded Image')
plt.show()
#print(str(resized_image_matrix).replace('[','{').replace(']','},').replace(",}",'}').replace('\n','') )
for x in range(xdim):
    print("{",end="")
    for y in range(ydim):
        aux = resized_image_matrix[y][x]
        print( "CRGB("+str(aux[0]) +","+ str(aux[1])+","+str(aux[2])+")", end ="")
        
        if y != ydim-1:
            print("",end =",")

    print("}",end="")
    if x != xdim-1:
        print(",",end="")
